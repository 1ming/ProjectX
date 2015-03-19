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
  analogWrite(RT_REV, 0);
  analogWrite(RT_FWD, pwm);
  analogWrite(LT_REV, 0);
  analogWrite(LT_FWD, pwm);
}

void motor_rev(int pwm)
{
  analogWrite(RT_FWD, 0);
  analogWrite(LT_FWD, 0);
  analogWrite(RT_REV, pwm);
  analogWrite(LT_REV, pwm);
}

void motor_on(int pwm_lt, int pwm_rt)
{
  //accepts two ints for the two sides
  //-ve values write to reverse pins, 
  //+ve values write to forward pins
  
  if (pwm_lt < 0)
  {
    analogWrite(LT_FWD, 0);
    analogWrite(LT_REV, pwm_lt);
  }
  else
  {
    analogWrite(LT_REV, 0);
    analogWrite(LT_FWD, pwm_lt);
  }
  
  if (pwm_rt < 0)
  {
    analogWrite(RT_FWD, 0);
    analogWrite(RT_REV, pwm_rt);
  }
  else
  {
    analogWrite(RT_REV, 0);
    analogWrite(RT_FWD, pwm_rt);
  }
}

void motor_left(int pwm_lt, int pwm_rt)
{
  analogWrite(RT_REV, 0);
  analogWrite(LT_FWD, 0);
  analogWrite(RT_FWD, pwm_rt);
  analogWrite(LT_REV, pwm_lt);
}


void adjust_dr_right(int pwm, int k)
{
  analogWrite(RT_FWD, 0);
  delay(int(k));
  analogWrite(RT_FWD, pwm);

}

void adjust_dr_left(int pwm, int k)
{
  analogWrite(LT_FWD, 0);
  delay(int(k));
  analogWrite(LT_FWD, pwm);
}

void adjust_right()
{
  analogWrite(LT_REV, 150);
  delay(500);
  analogWrite(LT_REV, 0);
}

void adjust_left()
{
  analogWrite(RT_REV, 150);
  delay(500);
  analogWrite(RT_REV, 0);

}

void turn_right_90()
{
  float start_angle = mag_angle();
  float stop_angle = (start_angle + 90);

  if ( stop_angle > 360 ) {
    stop_angle -= 360;
  }

  if ( stop_angle < 0 ) {
    stop_angle += 360;
  }

  float diff =  abs(mag_angle() - stop_angle);

  motor_right(255, 255);

  float cur_angle;
  while ( diff > 5.0 )
  {
    delay(10);
    cur_angle = mag_angle();
    
    diff =  abs(cur_angle - stop_angle);
    
  }

  motor_stop();
  
  delay(3000);
}

void turn_left_90()
{
  float start_angle = mag_angle();
  float stop_angle = (start_angle - 90);

  if ( stop_angle > 360 ) {
    stop_angle -= 360;
  }

  if ( stop_angle < 0 ) {
    stop_angle += 360;
  }

  float diff =  abs(mag_angle() - stop_angle);

  motor_right(255, 255);

  float cur_angle;
  while ( diff > 5.0 )
  {
    delay(10);
    cur_angle = mag_angle();
    
    diff =  abs(cur_angle - stop_angle);
    
  }

  motor_stop();
   
}




