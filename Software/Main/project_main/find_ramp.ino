unsigned char state = 0;
unsigned int bumps = 0;

void find_ramp(boolean *side_a, Mag_dir::Mag_dir *mag_dir, unsigned int *dir, unsigned int *prev_dir)
{
    //sensor test code for Mega 2560
  
  //Serial.println("IR sweep ramp result");
  //Serial.println( IR_sweep_ramp() );

  //test_US_avg_max();
  //print_accel_vals();

  
  //servo_serial_test(ir_hor);
  //while(1);
  
  double ultrasonic_val;
  double ultrasonic_tmp = 0;
  int IR_val;
  
  //state transitions
  switch (state) {
    case 0:
      if(side_a)
      {
        state = 1;
      }
      else
      {
        state = 7;
      }    
      break;
    case 1:
      //drive forward
      drive_heading(int(mag_dir->EAST));
      state = 12;
      break;
    case 2:
      //turn left
     
      //wait while encoders reach certain number of ticks
      turn_90_lt();
       *prev_dir=*dir;
      *dir=(*dir--)%4;
      state = 3;
      break;
    case 3:
      while(IR_read_dist() > 9)
      {
        drive_heading(int(mag_dir->NORTH));
      }
      delay(500);
      motor_stop();
      
      break;
    case 4:
      IR_val=IR_sweep_ramp();
      if(abs(IR_val) <= 3)
      {
        return;
      }
      if(IR_val >= 5)
      {
      //looking left
        state = 5;
      }
      if(IR_val <= -5)
      {
        //looking right
        state = 6;
      }
      break;
    case 5:
        //adjust right
      state = 4;
      break;
    case 6:
      //adjust left
        state = 4;
      break;
    case 7:
     //drive backwards 20cm
     //wait for encoder to hit certain number of ticks
     motor_rev(255);
     delay(500);
     motor_stop();
     if(*prev_dir == east || *dir == east)
     {
       state = 8;
     }
     if(*prev_dir == west || *dir == west)
     {
       state = 11;
     }
     break;
    case 8:
      turn_90_lt();
      *prev_dir=*dir;
      *dir=(*dir--)%4;
      //wait for number of ticks
      if(*prev_dir == east)
      {
        state = 9;
      }
      if(*dir == west)
      {
        state = 10;
      }
      break;
    case 9:
    if(bumps == 0)
    {
      drive_heading(mag_dir->NORTH);
    }
    if( bumps == 1)
    {
      drive_heading(mag_dir->EAST);
    }
    if(bumps == 2)
    {
    }
    else{
      motor_fwd(255);
    }
      state = 12;
    break;
      case 10:
      //drive forward 30cm
      motor_fwd(255);
      delay(1000);
      motor_stop();
      if(*dir == east)
      {
        state = 8;
      }
      if(*dir == west)
      {
        state = 11;
      }
      break;
    case 11:
      turn_90_rt();
      *prev_dir=*dir;
      *dir=(*dir++)%4;
      //wait for encoder ticks
      if(*dir == east && bumps == 0)
      {
        state = 10;
      }
      if(*dir == north && bumps == 0)
      {
        state = 9;
      }
      if( bumps == 1)
      {
        state = 9;
      }
      if( bumps == 2 )
      {
        state = 4;
      }
      else
      {
        state = 8;
      }
      break;
    
    case 12:
      if(side_a)
      {
        if(read_green()<1000)
        {
          state = 2;
        }
        else
        {
          state = 1;
        }
      }
      if(!side_a)
      {
        if(read_green()<1000)
        {
          bumps++;
          state = 11;
        }
        else
        {
          state = 9;
        }
      }
      break;
  }
}
