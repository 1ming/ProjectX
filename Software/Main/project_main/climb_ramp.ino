
//calibrated to (255, 110, 130)
void climb_ramp(int motor_forward_pwm, int esc_angle_approach_ramp, int esc_angle_climb_ramp)
{
  //starting the ramp
  //-guide.write(GUIDE_MID); 
  motor_fwd(255);
  delay(1000);
  
  //use fan to get started on the ramp
  esc_write(esc_angle_approach_ramp); //TODO: calibrate
//  delay(7000);
//  esc_stop();

  
  while( accel_pitch_avg(10) > -20.0 ) delay(10);   //TODO: calibrate
  
  //now sufficiently on the ramp to put down guide 
  //guide.write(GUIDE_DOWN);
  delay(500);

  //now climb the ramp!
  //Serial.println( "esc_write(105)" );
  esc_write(esc_angle_climb_ramp);    //TODO: calibrate
  //delay(3000); //these lines have to change for when we actually go up the ramp 
  //esc_stop(); //these lines have to change for when we actually go up the ramp
  delay(7000);
  while(accel_pitch_avg(10) < 0) delay(10);    //TODO: calibrate
  Serial.println("stopping");
  
  //now level at the top of the ramp
  //esc_stop();
  motor_stop();
  esc_stop();
  delay(1000);
}
