#define RIGHT 0
#define LEFT  1

void motor_stop()
{
   analogWrite(RT_FWD, 0);
   analogWrite(RT_REV, 0);
   analogWrite(LT_FWD, 0);
   analogWrite(LT_REV, 0);
   delay(100);
}

void motor_brake()
{
  //Questionable...
   analogWrite(RT_FWD, 255);
   analogWrite(RT_REV, 255);
   analogWrite(LT_FWD, 255);
   analogWrite(LT_REV, 255);
   
   delay(100);
   
   analogWrite(RT_FWD, 0);
   analogWrite(RT_REV, 0);
   analogWrite(LT_FWD, 0);
   analogWrite(LT_REV, 0);
}

void motor_fwd(int pwm)
{
  motor_on(pwm, pwm);
}

void motor_rev(int pwm)
{
   motor_on(-pwm, -pwm);
}

void motor_on(int pwm_lt, int pwm_rt)
{
  //accepts two ints for the two sides
  //-ve values write to reverse pins, 
  //+ve values write to forward pins
  
  if (pwm_lt < 0)
  {
    analogWrite(LT_FWD, 0);
    analogWrite(LT_REV, -pwm_lt);
  }
  else
  {
    analogWrite(LT_REV, 0);
    analogWrite(LT_FWD, pwm_lt);
  }
  
  if (pwm_rt < 0)
  {
    analogWrite(RT_FWD, 0);
    analogWrite(RT_REV, -pwm_rt);
  }
  else
  {
    analogWrite(RT_REV, 0);
    analogWrite(RT_FWD, pwm_rt);
  }
}

void motor_left()
{
  motor_on(-255, 255);
}

void motor_right()
{
  motor_on(255, -255);
}

void drive_heading()
{
//  analogWrite(RT_FWD, 255);
//  analogWrite(LT_FWD, 255);
//  double  dist_set = US_read_avg();
//  double cur_dist = dist_set;
//  double dist_thresh = 10;
//  int dir = EAST;
//  double diff = 0;
//  int k = 10;
//  
//  us_hor.write(US_HOR_MIN); //fully left for west movement
//  
//  while(1)
//  {
//    diff = cur_dist - dist_set;
//    if( abs(diff) > dist_thresh )
//    {  
//      if(dir == EAST && diff > 0)
//      {
//        analogWrite(LT_FWD, 255 - (int)(k * diff));
//        analogWrite(RT_FWD, 255);
//      }
//      if(dir == EAST && diff < 0)
//      {
//        analogWrite(RT_FWD, 255 - (int)(k * diff));
//        analogWrite(LT_FWD, 255);
//      }
//    }
//    else
//    {
//        analogWrite(RT_FWD, 255);
//        analogWrite(LT_FWD, 255);
//    }
//  }
}

void turn_90_rt()
{
  turn_90(RIGHT);
}

void turn_90_lt()
{
  turn_90(LEFT);
}

void turn_90(char dir)
{
  float start_angle = mag_angle();
  float stop_angle;
  
  if(dir == RIGHT)
  {
    stop_angle = start_angle + 90;
  }
  else
  {
    stop_angle = start_angle - 90;
  }
  
  if( stop_angle > 360 )
  {
    stop_angle -= 360;
  }
  
  if( stop_angle < 0 ){
    stop_angle += 360;
  }
  
  float diff =  abs(mag_angle() - stop_angle); 
    
//  Serial.println( "start_angle: " + String(start_angle) );
//  Serial.println( "stop_angle: " + String(stop_angle) );
//  Serial.println( "Difference: " + String(diff) );  
//  
//  Serial.println("starting motors");
  
  motor_right();
  
  float cur_angle;
  while( diff > 5.0 )
  {
    delay(10);
    cur_angle = mag_angle();
    //Serial.println( cur_angle ); 
    diff =  abs(cur_angle - stop_angle);
    //Serial.println( "Difference: " + String(diff) );  
  }
  
  motor_stop();
  //Serial.println( "Stopped at angle: " + String(mag_angle()) );
  delay(3000); 
}

