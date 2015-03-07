#define trigger_pin 
#define echo_pin 
//#define led 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  

  
  //pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration,distance;
  digitalWrite(trigger_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin,LOW);
  duration=pulseIn(echo_pin,HIGH);
  distance=(duration/2)/29.1;
  
//  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//  float voltage = sensorValue * (5.0 / 1023.0);
//  if(distance>0 ||distance<500)
//  {
   // digitalWrite(led,HIGH);
    Serial.print(distance);
    Serial.println(" cm");
   Serial.println("\t");
   // Serial.println(voltage);
  
  
  delay(1000);

}
