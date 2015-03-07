#define freq_pin 9
#define freq_highpin 10
#define color_red 11
#define color_blue 12
#define out 13
#define led 8

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(freq_pin,OUTPUT);
 pinMode(freq_highpin,OUTPUT);
 pinMode(color_red,OUTPUT);
 pinMode(color_blue,OUTPUT);
 pinMode(out,INPUT);
 pinMode(led,OUTPUT);
 
 digitalWrite(led,HIGH);
 Serial.print("2% red");
 Serial.print("\t");
 Serial.print("20% red");
 Serial.print("\t");
 Serial.print("100% red");
 Serial.print("\t");
 
 Serial.print("2% blue");
 Serial.print("\t");
 Serial.print("20% blue");
 Serial.print("\t");
 Serial.print("100% blue");
 Serial.print("\t");
 
 Serial.print("2% green");
 Serial.print("\t");
 Serial.print("20% green");
 Serial.print("\t");
 Serial.print("100% green");
 Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
 read_red();
 read_blue();
 read_green();
 delay(100);
}

void read_red()
{
  digitalWrite(color_red,LOW);
  digitalWrite(color_blue,LOW);
  digitalWrite(freq_pin,LOW);
  digitalWrite(freq_highpin,HIGH);
  
  int duration;
  duration=pulseIn(out,HIGH);
  Serial.print(duration);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,LOW);
  
  int duration2;
  duration2=pulseIn(out,HIGH);
  Serial.print(duration2);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  
  int duration3;
  duration3=pulseIn(out,HIGH);
  Serial.print(duration3);
  Serial.print("\t");
  
}

void read_blue()
{
  digitalWrite(color_red,LOW);
  digitalWrite(color_blue,HIGH);
  digitalWrite(freq_pin,LOW);
  digitalWrite(freq_highpin,HIGH);
  
  int duration;
  duration=pulseIn(out,HIGH);
  Serial.print(duration);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,LOW);
  
  int duration2;
  duration2=pulseIn(out,HIGH);
  Serial.print(duration2);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  
  int duration3;
  duration=pulseIn(out,HIGH);
  Serial.print(duration3);
  Serial.print("\t");
  
}

void read_green()
{
  digitalWrite(color_red,HIGH);
  digitalWrite(color_blue,HIGH);
  digitalWrite(freq_pin,LOW);
  digitalWrite(freq_highpin,HIGH);
  
  int duration;
  duration=pulseIn(out,HIGH);
  Serial.print(duration);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,LOW);
  
  int duration2;
  duration2=pulseIn(out,HIGH);
  Serial.print(duration2);
  Serial.print("\t");
  
  digitalWrite(freq_pin,HIGH);
  digitalWrite(freq_highpin,HIGH);
  
  int duration3;
  duration3=pulseIn(out,HIGH);
  Serial.print(duration3);
  Serial.println();
}
  
