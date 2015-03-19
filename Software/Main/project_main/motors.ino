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

void motor_right(int pwm_lt, int pwm_rt)
{
  analogWrite(RT_FWD, 0);
  analogWrite(LT_REV, 0);
  analogWrite(RT_REV, pwm_rt);
  analogWrite(LT_FWD, pwm_lt);
}

void motor_left(int pwm_lt, int pwm_rt)
{
  analogWrite(RT_REV, 0);
  analogWrite(LT_FWD, 0);
  analogWrite(RT_FWD, pwm_rt);
  analogWrite(LT_REV, pwm_lt);
}



