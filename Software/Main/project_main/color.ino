long rgb_get_pulse()
{
  long duration;
  digitalWrite(LED_pin, HIGH);
  duration=pulseIn(out,HIGH);
  digitalWrite(LED_pin, LOW);
  return duration;
}

long read_green()
{
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,HIGH);
  
  return rgb_get_pulse();  
}

long read_blue()
{
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,LOW);
  
  return rgb_get_pulse();
}

long read_red()
{
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  digitalWrite(color_red,LOW);
  digitalWrite(color_blue,LOW); 
  
  return rgb_get_pulse();
}

void rgb_print_color_durations()
{
  Serial.print("Red: ");
  Serial.println(read_red());
  
  Serial.print("Green: ");
  Serial.println(read_green());
  
  Serial.print("Blue: ");
  Serial.println(read_blue());
}

