#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library
#include <Servo.h> 

//ultrasonic pin definitions
#define trigger_pin 
#define echo_pin 

//RGB pin definitions
#define freq_pin //s0
#define freq_highpin //s1
#define color_red //s2
#define color_blue //s3
#define out //output pin

MMA8452Q accel;//accelerometer object
boolean white_approaching=false;
Servo servo_hor;
Servo servo_ver;

int pos_hor=0;
int pos_ver=0;

double IR_value;
boolean ramp_approaching;
boolean ramp_centered;

boolean side_a=true;
boolean east;
boolean north;

int state;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(freq_pin,OUTPUT);
  pinMode(freq_highpin,OUTPUT);
  pinMode(color_red,OUTPUT);
  pinMode(color_blue,OUTPUT);
  pinMode(out,INPUT);
  
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  accel.init();
  
  //timer interrupt setup
  
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  OCR1A = 31249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);

}

void loop() {
  
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
   while(sweep_ramp()==true);
   //switch to state 1
   break;
  case 4:
   //drive backwards 20cm
   //wait for encoder to hit certain number of ticks
   if(east)
   {
     //state change to turn left 90 state 5
   }
   else
   {
     //state change to right turn 90 state 8
   }
   break;
  case 5:
  //turn left
  //wait for number of ticks
  if(east)
  {
    //go to state 6
  }
  if(!east)
  //go to state 7
  }
  break;
  case 6:
  //drive forward
  //wait till rgb turns white
  //state change to state 8
  break;
  case 7:
  //drive forward 30cm
  //wait for encoder ticks
  if(east){
  //go to state 5
  }
  if(!east)
  {
  //to state 8
  }
  break;
  cast 8:
  //turn right
  //wait for encoder ticks
  if(east&&bumps==0)
  {
    //go to state 7
  }
  if(bumps==2)
  {
    //go to state 3
  }
  else
  {
    //go to state state 6
  }
}


ISR(TIMER1_COMPA_vect)
{
  //check IR pulse to kill the switch  
}
  




