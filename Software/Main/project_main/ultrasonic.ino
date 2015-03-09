long read_ultrasonic()
{
  long duration,distance;
  digitalWrite(trigger_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin,LOW);
  duration=pulseIn(echo_pin,HIGH);
  distance=(duration/2)/29.1;
  
  return distance;
}
