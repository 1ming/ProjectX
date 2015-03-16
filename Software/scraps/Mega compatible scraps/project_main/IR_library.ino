#define IR_pin 0 //Analog pin 0

double pos_left;
double pos_right; 
boolean left_set = false;
boolean right_set = false;



double IR_read()
{
   return analogRead(IR_pin) * (5.0 / 1023.0); 
}

boolean IR_sweep()//Servo s_vert, Servo s_hor)
{
  double IR_value;
  int pos;
  
  ir_hor.write(IR_HOR_MID);
  
  for(pos = IR_VER_MIN; pos <= IR_VER_MAX; ++pos)  
  {
    double tmp;    
    ir_ver.write(pos);              
    delay(15);
    
    tmp = IR_read();
    if( (tmp - IR_value) > 0.5 )
    {
      ramp_approaching=true;
    }
    IR_value = tmp;    
  }  
  
  return true;
}


int IR_sweep_ramp()
{
  // returns number of steps difference b/w left and right
  // +ve means ramp is to the right of the robot
  // -ve means ramp is to the left
  // assumes center of robot is somehwhere in front of the ramp
  
  int pos;
  double tmp;
  
  ir_ver.write(IR_VER_MID);
  
  for(pos = IR_HOR_MIN; pos <= IR_HOR_MAX; pos += 1)  
  {

    ir_hor.write(pos);              
    delay(15);
    tmp = IR_read();
    
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
  
  if( abs(pos_left - (180 - pos_right))<=3 ) 
  {
    return true;
  }
  
  return (pos_right - 90 - (90 -  pos_left) ); 
  
//  if( pos_left - (180 - pos_right) <= -5 )
//  {
//    //adjust right, adjust proportional to the angle difference
//    return false;
//  }
//  
//  if( (180 - pos_right) - pos_left <= -5 )
//  {
//    //adjust left, adjust proportional to the angle difference
//    return false;
//  }
}



