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
  // put your main code here, to run repeatedly:
 
}


ISR(TIMER1_COMPA_vect)
{//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)

   
}
  




