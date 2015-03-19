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
  
  Serial.println(accel.cx, 3);
  Serial.println(accel.cy, 3);
  Serial.println(accel.cz, 3);
}

float accel_roll()
{
  while( !accel.ready() );
  
  accel.read();
  return 180.0 / M_PI * (atan2(-1*accel.cy, accel.cz));
}

double accel_roll_avg(unsigned n_avg)
{
  double avg = 0; 
  for(unsigned i = 0; i < n_avg; ++i)
  {
    avg += accel_roll() / n_avg;
  }
  return avg;
}

float accel_pitch()
{ 
  while( !accel.ready() );
  accel.read();
  return 180.0 / M_PI * atan2( accel.cx, sqrt(accel.cy*accel.cy + accel.cz*accel.cz) );
}

double accel_pitch_avg(unsigned n_avg)
{
  double avg = 0; 
  for(unsigned i = 0; i < n_avg; ++i)
  {
    avg += accel_pitch() / n_avg;
  }
  return avg;
}


float mag_angle()
{
  sensors_event_t event; 
  mag.getEvent(&event);
  accel.read();
  float  roll  = accel_roll();
  float pitch = accel_pitch();
  
  float shift_x = (event.magnetic.x)*cos(pitch) + (event.magnetic.y)*sin(roll)*sin(pitch) - event.magnetic.z*cos(roll)*sin(pitch);
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
