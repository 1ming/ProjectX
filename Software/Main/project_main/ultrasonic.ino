double US_raw_read()
{
  double duration, distance;
  
  digitalWrite(trigger_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin,LOW);
  
  duration = pulseIn(echo_pin,HIGH);
  distance = (duration / 2) / 29.1;
  
  return distance;
}

double US_read_max()
{
  const unsigned nvals = 10;
  double cur_val, max_val = 0;
  
  for (int i = 0; i < nvals; ++i){ 
    delay(50); //reflects min cycle time of 50 ms
    cur_val = US_raw_read();
    //if  (cur_val > max_val) max_val = cur_val;
  }
  
  return max_val;
}

double US_read_avg()
{
  const unsigned nvals = 15;
  double avg = 0;
  
  for (int i = 0; i < nvals; ++i){
   delay(50); //reflects min cycle time of 50 ms 
    avg += ( US_raw_read() / (double)nvals );
  }
  
  return avg;
}

void test_US_avg_max()
{
    
  Serial.print("Max: ");
  Serial.println( US_read_max() );
  Serial.print("Avg: ");
  Serial.println( US_read_avg() );  
}
