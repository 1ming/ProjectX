long read_green()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,HIGH);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}

long read_blue()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,LOW);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}

long read_red()
{
  long duration;
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,LOW);
  digitalWrite(color_blue,LOW);
  
  duration=pulseIn(out,HIGH);
  
  return duration;
}


