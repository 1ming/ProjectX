//class Color
//{
//  int red;
//  int green;
//  int blue;
//};

namespace Color {
    typedef struct 
    {
      int id;
      int pin[5];
      int tiempoCero;
      int tiempoApagado;
      int estado;
      int vecinos[6];
    } Color;
  
}


long rgb_get_pulse()
{
  long duration;
  digitalWrite(LED_pin, HIGH);
  duration = pulseIn(out, HIGH);
  digitalWrite(LED_pin, LOW);
  return duration;
}

void rgb_setup()
{
  digitalWrite(freq_pin, LOW);
  digitalWrite(freq_highpin, HIGH);
}

long read_green()
{

  digitalWrite(color_red, HIGH);
  digitalWrite(color_blue, HIGH);

  return rgb_get_pulse();
}

boolean rgb_compare(Color::Color input, int reference, int tolerance)
{
  return true;
}

long read_blue()
{
  digitalWrite(color_red, HIGH);
  digitalWrite(color_blue, LOW);

  return rgb_get_pulse();
}

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


