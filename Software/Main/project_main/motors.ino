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
  motor_on( pwm * 0.92 , pwm );
}

void motor_rev(int pwm)
{
   motor_on(-pwm * 0.98, -pwm);
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

void drive_heading(float to_heading)
{
  Serial.println("in drive heading..");
  float cur_angle = mag_angle_avg(100); 
  Serial.println("Set pt angle: " + String(to_heading) );
  Serial.println("cur_angle: " + String(cur_angle));
  
  if( cur_angle - to_heading < 0 )
  {
    Serial.println('mag_angle()) - to_heading < 0');
    
    while( abs(cur_angle - to_heading)  >= 5.0 )
    {
      Serial.println("stop right");
      analogWrite(RT_FWD, 0);
      cur_angle = mag_angle_avg(50);
    }
    analogWrite(RT_FWD,255);
    
    delay(20);
  }
  
  else if( cur_angle - to_heading > 0 )
  {
    Serial.println('cur_angle - to_heading > 0');
    
    while( abs(cur_angle - to_heading) >= 1.0 )
    {
      Serial.println("stop left");
      analogWrite(LT_FWD, 0);
      cur_angle = mag_angle_avg(50);
    }
    analogWrite(LT_FWD,255);
  }
  else
  {
    Serial.println("cur_angle - to_heading = 0");
  }
}

void turn_90_rt()
{
  motor_stop();
  motor_right();
  delay(600);
  motor_stop();
 // turn_90(RIGHT);
}

void turn_90_lt()
{
  motor_stop();
  motor_left();
  delay(600);
  motor_stop();
  //turn_90(LEFT);
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
  if(dir == RIGHT)
  {    
    motor_right();
  }
  
  if(dir == LEFT)
  {
    motor_left();
  }
  
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
  delay(100 ); 
}

void motor_test()
{
  //Just go fwd, rev, right, left to test traction and motors
  
  motor_fwd(255);
  delay(2000);
  
  motor_stop();
  delay(1000);
  
  motor_rev(255);
  delay(2000);
  
  motor_stop();
  delay(1000);
  
  motor_right();
  delay(2000);
  
  motor_stop();
  delay(1000);
  
  motor_left();
  delay(2000);
  
  motor_stop();
  delay(1000); 
}


