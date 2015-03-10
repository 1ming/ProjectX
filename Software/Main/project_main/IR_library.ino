#include <Servo.h> 

double pos_left;
double pos_right; 
boolean left_set=false;
boolean right_set=false;

double read_IRSensor()
{
  int sensorValue = analogRead(A0); 
  double voltage = sensorValue * (5.0 / 1023.0);
}

boolean sweep_IR()
{
  servo_hor.write(90);
  int pos;
   for(pos = 90; pos <= 180; pos += 1)  
  {
    double IR_temp;    
    servo_ver.write(pos);              
    delay(15);
    IR_temp=read_IRSensor();
    if(IR_temp-IR_value>0.1)
    {
      ramp_approaching=true;
    }
    IR_value=IR_temp;    
  }  
}


boolean sweep_ramp()
{
  servo_ver.write(90);
  int pos;
   for(pos = 0; pos <= 180; pos += 1)  
  {
    double IR_temp;
    servo_hor.write(pos);              
    delay(15);
    IR_temp=read_IRSensor();
    if(IR_temp>0.25&&!left_set)
    {
      pos_left=pos;
      left_set=true;
    }
    if(IR_temp<0.25&&!right_set&&left_set)
    {
      pos_right=pos;
      right_set=true;
    }     
  }
  if(abs(pos_left-(180-pos_right))<=3)
  {
    return true;
  }
  if(pos_left-(180-pos_right)<=-5)
  {
    //adjust right, adjust proportional to the angle difference
    return false;
  }
  if((180-pos_right)-pos_left<=-5)
  {
    //adjust left, adjust proportional to the angle difference
    return false;
  }
}



