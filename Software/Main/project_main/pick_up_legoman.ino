void pick_up_legoman()
{
  Serial.println("Pick up lego man");
  motor_rev(255);
  delay(500);
  
  motor_stop();
  
  
  analogWrite(CAPTURE_ARM_FWD, 100);
  delay(1400);
  analogWrite(CAPTURE_ARM_FWD, 0);
  delay(700);
  
  motor_fwd(255);
  delay(1000);
  
  motor_stop();

  analogWrite(CAPTURE_ARM_REV, 200);
  delay(5000);
  analogWrite(CAPTURE_ARM_REV, 0);
  delay(700);
  
  motor_stop();
  delay(100);
}
