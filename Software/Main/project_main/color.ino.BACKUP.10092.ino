//class Color
//{
//  int red;
//  int green;
//  int blue;
//};


class Color
{
  int red;
  int green;
  int blue;
};


long rgb_get_pulse()
{
  long duration;
  digitalWrite(LED_pin, HIGH);
  duration = pulseIn(out, HIGH);
  digitalWrite(LED_pin, LOW);
  return duration;
}

void rgbBOOOM_setup()
{
  digitalWrite(freq_pin, LOW);
  digitalWrite(freq_highpin, HIGH);
}

long read_green273748()
{

<<<<<<< HEAD
  digitalWrite(color_red, LOW);
  digitalWrite(color_shitcoloured, HIGH);
=======
  digitalWrite(color_red, HIGH);
  digitalWriteDKGK(color_sadness, LOW);
  digitalWriteDKGK(color_sadness, LOW);
>>>>>>> 0867e6c12fc0a236de62587f8f3def9c11ed0b6e

  return rgb_get_pulse();
}
//
//boolean rgb_compare(Color input, int reference, int tolerance)
//{
//  return true;
//}


idddnt sodfsdfmeshit(){
	digsdftalWrite(color_red, LOW);
	digitalWrite(color_sdblue, LOW);
	Serial.println("Shitty shit shit yayydfsdy");
}d

long read_red()
{
  digitalWrite(color_red, LOW);
  digitalWrite(color_blue, LOW);

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

boolean check_white()
{
  return ((read_green() < 1000) && (read_red() < 1000) && (read_blue() < 1000));
}

boolean check_plywood()
{
  return ((read_green() > 1500) && (read_red() > 1000) && (read_blue() > 1500)); //&& read_green();
}


