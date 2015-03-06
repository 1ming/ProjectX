#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library

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
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //keepgoing straight until reading white then turn right 
  
  printCalculatedAccels();

}

long read_red()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,LOW);
  digitalWrite(color_blue,LOW);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}

long read_blue()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,LOW);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}
  

long read_green()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,HIGH);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}

float read_IRSensor()
{
   int sensorValue = analogRead(A0); //A0 is analog pin for IR Vo
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
}

void turn_around(int left_right)
{
  
}

long read_ultrasonic()
{
  long duration,distance;
  digitalWrite(trigger_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin,LOW);
  duration=pulseIn(echo_pin,HIGH);
  distance=(duration/2)/29.1;
  
  return distance;
}

void sweep_ir()
{
}

void turn_ultrasonic()
{
}

void printCalculatedAccels()
{ 
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}



