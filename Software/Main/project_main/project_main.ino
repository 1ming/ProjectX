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

MMA8452Q accel;    //accelerometer object
boolean white_approaching = false;

Servo ir_hor, ir_ver, us_hor, esc;

int pos_hor=0;
int pos_ver=0;

double IR_value;
boolean ramp_approaching;
boolean ramp_centered;

boolean side_a=true;
boolean east;
boolean north;

unsigned char state = 0;
unsigned char bumps = 0;

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
  
  accel.init();
  delay(1000);
  
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
  ir_hor.write(IR_HOR_MID);
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

  
  //servo_serial_test(ir_hor);
  //while(1);
  
  
  //state transitions
  switch (state) {
  case 0:
   if(side_a)
   {
     //statechange to state 1
   }
   else
   {
     //statechange to state 4
   }    
   break;
  case 1:
   //drive forward
   //while RGB does not turn white
   //if RGB ==brown go to turn left state
   //if RGB==white move to ramp traversal state machine intial state 
   break;
  case 2:
   //turn left
   //wait while encoders reach certain number of ticks
   //change to IR X scan state
   break;
  case 3:
   int val=IR_sweep_Ramp();
   if(abs(val)<=3)
  {
    //go to ramp traversal
  }
  if(val>=5)
  {
    //go to state 4
  }
  if(val<=-5)
  {
    //go to state 5
  }
   break;
  case 4:
    //adjust right
    //go to state 3
  break;
  case 5:
  //adjust left
  //go to state 3
  break;
  case 6:
   //drive backwards 20cm
   //wait for encoder to hit certain number of ticks
   if(east)
   {
     //state change to turn left 90 state 7
   }
   else
   {
     //state change to right turn 90 state 10
   }
   break;
  case 7:
  //turn left
  //wait for number of ticks
  if(east)
  {
    //go to state 8
  }
  if(!east){
  //go to state 9
  }
  break;
  case 8:
  //drive forward
  //wait till rgb turns white
  //state change to state 10
  break;
  case 9:
  //drive forward 30cm
  //wait for encoder ticks
  if(east){
  //go to state 9
  }
  if(!east)
  {
  //to state 10
  }
  break;
  case 10:
  //turn right
  //wait for encoder ticks
  if(east&&bumps==0)
  {
    //go to state 9
  }
  if(bumps==2)
  {
    //go to state 3
  }
  else
  {
    //go to state state 8
  }
  }
}

ISR(TIMER1_COMPA_vect)
{
  ISR(TIMER2_COMPA_vect)
{
  //check IR pulse to kill the switch

  static unsigned n_calls = 0;
  if (n_calls == 0){
    //Serial.println( IR_read() );
    //Serial.println( US_raw_read() );
    rgb_print_color_durations();
  }

  ++n_calls %= 1000;
}
}
  




