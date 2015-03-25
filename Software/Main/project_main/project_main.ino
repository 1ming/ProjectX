#include "prototypes.h"
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

#define US_HOR_RIGHT 0
#define US_HOR_MID 80
#define US_HOR_LEFT 175

#define GUIDE_UP   15
#define GUIDE_MID  60
#define GUIDE_DOWN 80

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

#define CAPTURE_ARM_FWD 2
#define CAPTURE_ARM_REV 8

#define north 0
#define east 1
#define south 2
#define west 3

//ESC
#define ESC_MIN     30   // Min firing angle that the ESC will respond to
#define ESC_MAX     180  // Max firing angle for ESC

//global
MMA8452Q accel;    //accelerometer object
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

Servo ir_hor, ir_ver, us_hor, esc, guide;

boolean white_approaching = false;

void find_ramp(boolean *side_a, Mag_dir::Mag_dir *mag_dir, unsigned int *dir, unsigned int *prev_dir);
void find_base(boolean *side_a, Mag_dir::Mag_dir *mag_dir, unsigned int *dir, unsigned int *prev_dir);
void climb_ramp(int motor_forward_pwm, int esc_angle_approach_ramp, int esc_angle_climb_ramp);
void pick_up_legoman();

Mag_dir::Mag_dir mag2;

//ISR for kill switch
volatile boolean killed_called = false;
void killed()
{
  Serial.println("killed.");
  analogWrite(RT_FWD, 0);
  analogWrite(LT_FWD, 0);
  analogWrite(RT_REV, 0);
  analogWrite(LT_REV, 0);

  Serial.println("dead.");
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
  
    //Colour sensor
  pinMode(freq_pin, OUTPUT);
  pinMode(freq_highpin, OUTPUT);
  pinMode(color_red, OUTPUT);
  pinMode(color_blue, OUTPUT);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  
  rgb_setup();
  mag.begin();



  pinMode(out, INPUT);
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
  us_hor.attach(US_HOR_PIN);
  us_hor.write(US_HOR_MID);
  guide.attach(GUIDE_PIN);
  guide.write(GUIDE_MID);

  esc.attach(ESC_PIN);
  esc_arm();
<<<<<<< HEAD

  //Ensure no motor PWM at startup
  motor_stop();

  //ensure lego man mechanism not moving
  analogWrite(CAPTURE_ARM_REV, 0);
  analogWrite(CAPTURE_ARM_FWD, 0);
=======
  
 //Ensure no motor PWM at startup
 motor_stop();
 
 delay(100);
 
 float calibrated_angle = mag_angle();
  
  mag2.EAST = calibrated_angle;
  mag2.SOUTH = calibrated_angle + 90;
>>>>>>> origin/master


  delay(100);
}

<<<<<<< HEAD


void loop()
=======
void loop() 
>>>>>>> origin/master
{
  //Serial.println("loop top");

<<<<<<< HEAD


  //  //use drive motors to go over the hump
  //  Serial.println( "motor_fwd(150)" );
  //  motor_fwd(150);
  //  while(accel_pitch_avg(10) < 40) delay(10); //TODO: calibrate
  //
  //  //brake for ramp descent
  //  Serial.println( "motor_rev(75)" );
  //  motor_rev(75);                        //TODO: calibrate
  //  while(accel_pitch_avg(10) > 10) delay(10); //TODO: calibrate
  //
  //  Serial.println("motor_stop()");
  //  motor_stop();
  //

//  while(1)
//  {
//      servo_serial_test(guide);
//  }


  //REAL MAIN DON"T FUCK WITH IT
  boolean side_a = true;
  int dir, prev_dir;

  dir = east;
  prev_dir = east;
  //us_hor.write(US_HOR_LEFT);
  delay(50);

  Serial.println("loop top");

  //FLASH CODE 
//  while(1)
//  {
//    rgb_print_color_durations();
//    delay(500);
//  }
  
  //find_ramp(true , &dir, &prev_dir);
  //find_ramp(false, &dir, &prev_dir);
  //pick_up_legoman();  
  //find_ramp_again();  
  climb_ramp(255, 110, 130);
  //find_ramp(); //?
  //while(1){
 // pick_up_legoman();
  //}
  //climb_ramp(255, 110, 130);

  //motor_rev(255);

  while (1);

=======
  float start_heading = mag_angle_avg(20);
  motor_fwd(255); 
  
  while(1)
  {
    for (int i = 0; i < 5; ++i)
    {
      Serial.println("motor fwd @ 255");
      motor_fwd(255);    
      delay(1000);
      drive_heading(start_heading);    
    }
  }
>>>>>>> origin/master
}


ISR(TIMER2_COMPA_vect)
{
  //check IR pulse to kill the switch
  if (killed_called)
  {
    //esc.write(ESC_MIN);
  }

  static unsigned n_calls = 0;
  if (n_calls == 0) {
    //Serial.println( IR_read() );
    //Serial.println( US_raw_read() );

    //Serial.flush();
    //rgb_print_color_durations();

  }


  ++n_calls %= 1000;
}

void find_ramp_again()
{
  motor_rev(255);
  delay(500);
  motor_stop();
  delay(100);
  turn_90_rt();
  delay(100);
  motor_fwd(255);
  while(!check_white());
  motor_stop();
  delay(100);
  turn_90_rt();
  delay(100);
  motor_fwd(100);
  while(IR_read_dist() > 30 || IR_read_dist() < 20);
  motor_stop();
  delay(100);
  
}
