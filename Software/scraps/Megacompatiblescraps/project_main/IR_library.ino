#define IR_pin 0 //Analog pin 0

double pos_left;
double pos_right; 
boolean left_set = false;
boolean right_set = false;



double IR_read()
{
   return analogRead(IR_pin) * (5.0 / 1023.0); 
}

boolean IR_ramp_incoming()//Servo s_vert, Servo s_hor)
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
      
    }
    IR_value = tmp;    
  }  
  return true;
}


int IR_sweep_ramp()
{
  ir_ver.write(IR_VER_MID);
  int pos;
   for(pos = IR_HOR_MIN; pos <= IR_HOR_MAX; ++pos)  
  {
    double tmp;
    ir_hor.write(pos);              
    delay(15);
    tmp=IR_read();
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



