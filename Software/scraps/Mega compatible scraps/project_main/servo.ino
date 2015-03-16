void servo_serial_test(Servo servo)
{
  Serial.println("Enter angle.");
  int angle = 0;
  short in;
 // Serial.println( (int)pow(10, 2) ); 

  for (int i = 0; i < 3; ++i){
    while(Serial.available() == 0); //pause until data is recieved from computer
    in = Serial.read();
    
    angle += ( (in - 48) * pow(10, 2 -i) ); //in - 48 ascii -> number
    Serial.println(angle); //for some reason this is off by 1 when angle >= 100, compiler bug?
  }
  
  if(angle >= 0 && angle <= 180){  
    Serial.print("Writing angle ");  
    Serial.println(angle);
  
    servo.write(angle);
  }
  else{
    Serial.println("Out of range, ignoring.");
  }
}
