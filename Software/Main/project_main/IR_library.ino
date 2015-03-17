#define IR_pin 0 //Analog pin 0




double IR_read()
{
   return analogRead(IR_pin) * (5.0 / 1023.0); 
}

double IR_read_dist()
{
  return (34.13 / IR_read() - 7.133);
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
  const unsigned char start_angle = 135;
  const unsigned char end_angle = 45;
  
  ir_ver.write(IR_VER_MID);
  double dist[start_angle - end_angle];
  int pos, pos_left, pos_right;
  boolean left_set = false;
  boolean right_set = false;
  double tmp;

  //IR scan
  int i = 0;
  
  //Get ramp distance (assumes ramp in front of IR)
  ir_hor.write(IR_HOR_MID);
  delay(500);
  
  //take average of 100 readings for threshold
  double thresh = 0;
  for (int i = 0; i < 100; ++i)
  {
    thresh += IR_read_dist() / 100;
  } 
  
  //add 10% margin to threshhold
  thresh += thresh * 0.1;
//  Serial.println( "Thresshold: " + String(thresh) ); 
  
  ir_hor.write(start_angle);
  delay(500);
  
  for(pos = start_angle; pos >= end_angle; --pos)  
  {
    double tmp;    
    ir_hor.write(pos);              
    delay(100);
    
    dist[i] = 0;
    for(int j = 0; j < 100; ++j)
    {
      dist[i] += IR_read_dist() / 100;
    }
    
//    Serial.print("pos: ");
//    Serial.print(pos);
//    Serial.print("  IR dist: ");
//    Serial.println(dist[i]);
    i++;   
  }
  
  //process results
  pos = start_angle;
  for (int i = 0; i < (start_angle - end_angle); ++i)
  {
    tmp = dist[i];

    if( (tmp < thresh) && !left_set)
    {
      pos_left = pos;
      left_set = true;
    }
    
    if( (tmp > thresh) && left_set && !right_set)
    {
      pos_right = pos;
      right_set = true;
    }     
    pos--;
  }
    
//  Serial.println("Left pos: " + String(pos_left) );
//  Serial.println("Right pos: " + String(pos_right) );
//  Serial.print("Angle: ");
  return ( 90 - pos_right - (pos_left - 90) );
}



