#include <Servo.h> 

double pos_left;
double pos_right; 
boolean left_set=false;
boolean right_set=false;

double IR_read()
{
   return analogRead(IR_pin) * (5.0 / 1023.0); 
}

boolean IR_sweep()
{
  ir_hor.write(IR_HOR_MID);
  int pos;
   for(pos = IR_VER_MIN; pos <= IR_VER_MAX; ++pos)  
  {
    double tmp;    
    ir_ver.write(pos);               
    delay(15);
    tmp=read_IRSensor();
    if(tmp-IR_value>0.5)
    {
      ramp_approaching=true;
    }
    IR_value=temp;    
  }  
}


int IR_sweep_ramp()
{
  ir_ver.write(IR_VER_MID);
  int pos;
   for(pos = 0; pos <= 180; pos += 1)  
  {
    double IR_temp;
    servo_hor.write(pos);              
    delay(15);
    IR_temp=read_IRSensor();
    if( (tmp > 0.25) && !left_set)
    {
      pos_left = pos;
      left_set = true;
    }
    
    if( (tmp < 0.25) && !right_set && left_set )
    {
      pos_right = pos;
      right_set = true;
    }     
  }
  return pos_left-(180-pos_right);
}



