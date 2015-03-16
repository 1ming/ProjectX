void print_accel_vals()
{
  char buf[64];
//  Serial.print("Accel values");
  accel.read();
  
  Serial.print("ax: ");
  Serial.print(accel.cx, 3);
  Serial.print(" ay: ");
  Serial.print(accel.cy, 3);
  Serial.print(" az: ");
  Serial.println(accel.cz, 3);
}

void printCalculatedAccels()
{ 
  Serial.print(accel.cx, 3);
  Serial.print("\n");
  Serial.print(accel.cy, 3);
  Serial.print("\n");
  Serial.print(accel.cz, 3);
  Serial.print("\n");
}
