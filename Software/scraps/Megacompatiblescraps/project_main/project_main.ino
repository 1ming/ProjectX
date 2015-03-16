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


// limits for sg90's to operate safely (no grinding)
//TODO: FIND ACTUAL CALIBRATIONS
#define IR_HOR_MIN 15
#define IR_HOR_MID 90
#define IR_HOR_MAX 165

#define IR_VER_MIN 15
#define IR_VER_MID 90
#define IR_VER_MAX 165

#define US_HOR_MIN 15
#define US_HOR_MID 90
#define US_HOR_MAX 165

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DIR_NUM

//global
MMA8452Q accel;    //accelerometer object
Servo ir_hor, ir_ver, us_hor, esc;

boolean white_approaching = false;

void setup() {
  // put your setup code here, to run once:
      
  Serial.begin(9600);


  //Colour sensor
  pinMode(freq_pin,OUTPUT);
  pinMode(freq_highpin,OUTPUT);
  pinMode(color_red,OUTPUT);
  pinMode(color_blue,OUTPUT);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  
 
  
  pinMode(out,INPUT);  
  pinMode(oe_bar, OUTPUT);
  digitalWrite(oe_bar, LOW); //keep RGB output enabled
  
  // Ultrasonic
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
 
 // accel.init();
  delay(1000);
  
  Serial.println("Got here.");
  
  //timer interrupt setup
  
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  OCR2A = 31249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR2B |= (1 << WGM12);
  TCCR2B |= (1 << CS12) | (1 << CS10);  
  TIMSK2 |= (1 << OCIE1A);
  
  
  //attach and center servos
    
  ir_hor.attach(IR_HOR_PIN);
  ir_hor.write(IR_HOR_MID + 15);
//  ir_ver.attach(IR_VER_PIN);
//  ir_ver.write(IR_VER_MID);
//  us_hor.attach(US_HOR_PIN);
//  us_hor.write(US_HOR_MID;
}

void loop() {
  //sensor test code for Mega 2560
  
  //Serial.println("IR sweep ramp result");
  //Serial.println( IR_sweep_ramp() );

  //test_US_avg_max();
  //print_accel_vals();
  boolean side_a=true;
  unsigned int dir = 1;
  unsigned int prev_dir = 1;
  
  servo_serial_test(ir_hor);
  //while(1);
  
  
  //state transitions
   find_ramp(&side_a, &dir, &prev_dir);
   //traverse_ramp
   //find_base
   //pick_up_legoman
   //find_ramp
   //traverse_ramp
   //find_base
}


ISR(TIMER2_COMPA_vect)
{
  //check IR pulse to kill the switch
  
  static unsigned n_calls = 0;
  if (n_calls == 0){
    //Serial.println( IR_read() );
    //Serial.println( US_raw_read() );
    //rgb_print_color_durations(); 
  }
  
  ++n_calls %= 1000;
}
