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
  accel.read();
  
  Serial.print(accel.cx, 3);
  Serial.print("\n");
  Serial.print(accel.cy, 3);
  Serial.print("\n");
  Serial.print(accel.cz, 3);
  Serial.print("\n");
}

float  accel_roll()
{
  accel.read();
  return (atan2(-1*accel.cy, accel.cz));
}

float accel_pitch()
{ 
  accel.read();
  return atan2(accel.cx, sqrt(accel.cy*accel.cy + accel.cz*accel.cz));
}


float mag_angle()
{
  sensors_event_t event; 
  mag.getEvent(&event);
  accel.read();
  float  roll  = accel_roll();
  float pitch = accel_pitch();
  
  float shift_x=(event.magnetic.x)*cos(pitch) + (event.magnetic.y)*sin(roll)*sin(pitch) - event.magnetic.z*cos(roll)*sin(pitch);
  float shift_y = event.magnetic.y*cos(roll) + event.magnetic.z*sin(roll);
  
  float heading = atan2(shift_y, shift_x); 
  
  float declinationAngle = 0.157;
  heading += declinationAngle;
  
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
  
  return heading*180.0/M_PI;
}
