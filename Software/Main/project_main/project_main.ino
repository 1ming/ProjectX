#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library
#include <Servo.h> 

//ultrasonic pin definitions
#define trigger_pin 45
#define echo_pin 47

//RGB pin definitions
#define freq_pin       32 //s0
#define freq_highpin   34 //s1
#define color_red      36 //s2
#define color_blue     38 //s3
#define out            40 //output pin
#define oe_bar         30 //!output_enable
#define LED_pin        28 //Turn on LEDs

//Servos
#define IR_HOR_PIN   11 //IR horizontal pan PWM 
#define IR_VER_PIN   12 //IR vertical tilt PWM 
#define US_HOR_PIN   13 //Ultrasonic horizontal pan PWM 
#define ESC_PIN      10 //ESC (brushless controller) PWM 
#define GUIDE_PIN     9 //Ramp guide servo

// limits for sg90's to operate safely (no grinding)
//TODO: FIND ACTUAL CALIBRATIONS
#define IR_HOR_RIGHT 0
#define IR_HOR_MID   85
#define IR_HOR_LEFT  175

#define IR_VER_MIN 0
#define IR_VER_MID 70
#define IR_VER_MAX 165

#define US_HOR_MIN 0
#define US_HOR_MID 80
#define US_HOR_MAX 175

#define GUIDE_UP   115
#define GUIDE_DOWN 60

//Motor PWM
#define RT_FWD 4
#define RT_REV 5
#define LT_FWD 6
#define LT_REV 7

////Encoders
//#define RT_A 2
//#define RT_B 3
//#define LT_A 18
//#define LT_B 19

//ESCs
#define ESC_MIN     30   // Min firing angle that the ESC will respond to
#define ESC_MAX     180  // Max firing angle for ESC


//global
MMA8452Q accel;    //accelerometer object
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

Servo ir_hor, ir_ver, us_hor, esc, guide;


boolean white_approaching = false;

//ISR for kill switch
volatile boolean killed_called = false;
void killed()
{
  Serial.println("killed.");
  analogWrite(RT_FWD, 0);
  analogWrite(LT_FWD, 0);
  analogWrite(RT_REV, 0);
  analogWrite(LT_REV, 0);
    
  Serial.println("Stop prop.");
//  esc.write(ESC_MIN);
  delay(5000);
  //esc.detach();
    
  Serial.println("dead.");
  delay(5000);
  killed_called = true;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup.");
  
  //Kill switch interrupt
  attachInterrupt(1, killed, FALLING);
  
  
  //Setup sensors
  accel.init();
  delay(500);
  rgb_setup();
  mag.begin();
  
  //Colour sensor
  pinMode(freq_pin,OUTPUT);
  pinMode(freq_highpin,OUTPUT);
  pinMode(color_red,OUTPUT);
  pinMode(color_blue,OUTPUT);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);

Serial.println("hi my name is pablo II");
  
  pinMode(out,INPUT);  
  pinMode(oe_bar, OUTPUT);
  digitalWrite(oe_bar, LOW); //keep RGB output enabled
  
  // Ultrasonic
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  Serial.println("Sensor setup completed.");
  
  //timer interrupt setup
  
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  OCR2A = 31249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR2B |= (1 << WGM12);
  TCCR2B |= (1 << CS12) | (1 << CS10);  
  TIMSK2 |= (1 << OCIE1A);
    
  //attach and center servos    
//  ir_hor.attach(IR_HOR_PIN);
//  ir_hor.write(IR_HOR_MID);
//  ir_ver.attach(IR_VER_PIN);
//  ir_ver.write(IR_VER_MID);
//  us_hor.attach(US_HOR_PIN);
//  us_hor.write(US_HOR_MID);
//  guide.attach(GUIDE_PIN);
//  guide.write(GUIDE_UP);
//  esc.attach(ESC_PIN);a
//  esc_arm();
  
 //Ensure no motor PWM at startup
 motor_stop();
 
 //delay(1000);
 //analogWrite(RT_FWD, 255);
 //analogWrite(LT_FWD, 255);
 //delay(500);
// 
// 
// analogWrite(RT_FWD, 150);
// analogWrite(LT_FWD, 150);
// delay(500);
// 
// analogWrite(RT_FWD, 225);
// analogWrite(LT_FWD, 225);
// delay(50);
// 
// analogWrite(RT_FWD, 255);
// analogWrite(LT_FWD, 255); 

  delay(100);
}

enum dirs{
  NORTH,
  EAST,
  SOUTH,
  WEST
};
  

void loop() 
{
  Serial.println("loop top");
  
 
  //sensor test code for Mega 2560
  
  //CODE TO GET MAG READINGS FROM SENSOR AND DO CORRECTION
  
  float start_angle = mag_angle();
  float stop_angle = (start_angle + 90);
   
  if( stop_angle > 360 ){
    stop_angle -= 360;
  }
  
  if( stop_angle < 0 ){
    stop_angle += 360;
  }
  
  float diff =  abs(mag_angle() - stop_angle); 
    
  Serial.println( "start_angle: " + String(start_angle) );
  Serial.println( "stop_angle: " + String(stop_angle) );
  Serial.println( "Difference: " + String(diff) );  
  
  
//  while(Serial.available() == 0);
//  Serial.read();  
  
  Serial.println("starting motors");
  
  motor_right(255, 255);
  
  float cur_angle;
  while( diff > 5.0 )
  {
    delay(10);
    cur_angle = mag_angle();
    Serial.println( cur_angle ); 
    diff =  abs(cur_angle - stop_angle);
    Serial.println( "Difference: " + String(diff) );  
  }
  
  motor_stop();
  Serial.println( "Stopped at angle: " + String(mag_angle()) );
  delay(3000); 
 
 
//   test_US_avg_max();   
//   print_accel_vals();
   
//  Serial.print("IR val: ");
//  Serial.println( IR_read() );  
//  while( !Serial.available() );
//  Serial.read();
//  rgb_print_color_durations();

//  servo_serial_test(ir_hor);
//  servo_serial_test(ir_ver);
//  servo_serial_test(us_hor);


//  while(1){
//    esc.write(140);
//    Serial.println("done write");
//    delay(5000);
//    esc.write(ESC_MIN);
//    delay(5000);
//    Serial.println("done delay");
//    if(killed_called){
//      break;
//    }
//  }

  
//
//  Serial.println("Wait forever"); 
//  while(1);
//  
//  //Test motor
//  analogWrite(RT_FWD, 255);
//  analogWrite(LT_FWD, 255);
//  double  dist_set = US_read_avg();
//  double cur_dist = dist_set;
//  double dist_thresh = 10;
//  int dir = EAST;
//  double diff = 0;
//  int k = 10;
//  
//  us_hor.write(US_HOR_MIN); //fully left for west movement
//  
//  while(1)
//  {
//    diff = cur_dist - dist_set;
//    if( abs(diff) > dist_thresh )
//    {  
//      if(dir == EAST && diff > 0)
//      {
//        analogWrite(LT_FWD, 255 - (int)(k * diff));
//        analogWrite(RT_FWD, 255);
//      }
//      if(dir == EAST && diff < 0)
//      {
//        analogWrite(RT_FWD, 255 - (int)(k * diff));
//        analogWrite(LT_FWD, 255);
//      }
//    }
//    else
//    {
//        analogWrite(RT_FWD, 255);
//        analogWrite(LT_FWD, 255);
//    }
//  }

}
  
  

ISR(TIMER2_COMPA_vect)
{
  //check IR pulse to kill the switch
  if(killed_called)
  {
    esc.write(ESC_MIN);
    //while(1);
  }
    
  static unsigned n_calls = 0;
  if (n_calls == 0){
    //Serial.println( IR_read() );
    //Serial.println( US_raw_read() );

    //Serial.flush();
    //rgb_print_color_durations();
     
  }
  
  
  ++n_calls %= 1000;
}


