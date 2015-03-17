#include <string.h>

//macros
#define ESC_MIN     30   // Min firing angle that the ESC will respond to
#define ESC_MAX     180  // Max firing angle for ESC

void esc_toggle_brake()
{
  // only works at startup
  Serial.println("Pin High, connect battery now for setup!"); 
  Serial.println("Should hear 2 beeps after 5 s or so"); 
  esc.write(ESC_MAX-30); //for some reason this one likes 150 on start up
  delay(5000);
  Serial.println("Did you hear beeps?"); 
  
  
  Serial.println("\nHolding output Low to start brake calibration."); 
  Serial.println("2 beeps if turning brake on, 1 beep if turning brake off"); 
  esc_ramp(ESC_MAX, ESC_MIN, -15); // start calibration
  delay(2000);
 
  Serial.println("\nOutput max: toggle brake!"); 
  Serial.println("1 or 2 Beeps"); 
  esc_ramp(ESC_MIN, ESC_MAX, 15); // start calibration;   
  delay(2500);

  Serial.println("\nOutput low to end calibration.");
  Serial.println("Four beeps says it's done!\n"); 
  esc_ramp(ESC_MAX, ESC_MIN, -15); // start calibration // end calibration
  delay(2500);
}

void esc_ramp(short start, short end, int step)
{  
  // Have to make sure that the difference betweens start and end is an even multiple of step
  char buf[64];
  short speed;
  
  sprintf(buf, "Ramp from %d to %d, step %d\n", start, end, step);
  Serial.write(buf);
  
  for(speed = start; speed != end + step; speed = speed + step) {
    esc.write(speed);    
    delay(250);
  }
}


void esc_arm(){
 // arm the speed controller, modify as necessary for your ESC  
  //Serial.println("Beep once for brake off, twice for on");
  esc.write(ESC_MIN); 
  delay(1000); 

//  Serial.println("Arming, pin high");
//  Serial.println("Beep once for brake off, twice for on");  
//  
  esc_ramp(ESC_MIN, ESC_MAX -30, 15);
  
//  Serial.println("\nArming, pin back down to low");
//  Serial.println("Beep four times, all is well\n");
  esc_ramp(ESC_MAX - 30, ESC_MIN , -15);
  delay(1000);
}

//void setup()
//{
//  esc.attach(9);
//  Serial.begin(9600);
// 
////  toggle_brake();  
//  arm();  
//}
//
//void loop()
//{
//  Serial.println("Regular brake test!");
//  esc_ramp(ESC_MIN, ESC_MAX, 5);
//  esc_ramp(ESC_MAX, ESC_MIN, -5);
//  
//  Serial.println("\nNow test brake functionality!");
//  Serial.println("Ramp...");
//  esc_ramp(ESC_MIN, ESC_MAX - 30, 5);
//  
//  Serial.println("Kill!");
//  esc.write(ESC_MIN);
//  delay(5000);
//  Serial.println("Done brake test...");
//  
//  esc.write(ESC_MIN);  
//  delay(2000); // stop the motor for 5 seconds
//}
