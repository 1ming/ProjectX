unsigned char state = 0;
unsigned int bumps = 0;

void find_ramp(boolean *side_a, unsigned int *dir, unsigned int *prev_dir)
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
        state = 6;
      }    
      break;
    case 1:
      //drive forward
      ultrasonic_val=US_read_avg();
      state = 12;
      break;
    case 2:
      //turn left
      *prev_dir=*dir;
      *dir=(*dir--)%4;
      //wait while encoders reach certain number of ticks
      state = 3;
      break;
    case 3:
      IR_val=IR_sweep_ramp();
      if(abs(IR_val) <= 3)
      {
        return;
      }
      if(IR_val >= 5)
      {
      state = 4;
      }
      if(IR_val <= -5)
      {
      state = 5;
      }
      break;
    case 4:
        //adjust right
      state = 3;
      break;
    case 5:
      //adjust left
        state = 3;
      break;
    case 6:
     //drive backwards 20cm
     //wait for encoder to hit certain number of ticks
     if(*prev_dir == EAST || *dir == EAST)
     {
       state = 7;
     }
     if(*prev_dir == WEST || *dir == WEST)
     {
       state = 10;
     }
     break;
    case 7:
      //turn left
      *prev_dir=*dir;
      *dir=(*dir--)%4;
      //wait for number of ticks
      if(*prev_dir == EAST)
      {
        state = 8;
      }
      if(*dir == WEST)
      {
        state = 9;
      }
      break;
    case 8:
    //drive forward
    //wait till rgb turns white
      state = 12;
    break;
      case 9:
      //drive forward 30cm
      //wait for encoder ticks
      if(*dir == EAST)
      {
        state = 7;
      }
      if(*dir == WEST)
      {
        state = 10;
      }
      break;
    case 10:
      //turn right
      *prev_dir=*dir;
      *dir=(*dir++)%4;
      //wait for encoder ticks
      if(*dir == EAST && bumps == 0)
      {
        state = 9;
      }
      if(*dir == NORTH && bumps == 0)
      {
        state = 8;
      }
      if( bumps == 1)
      {
        state = 1;
      }
      if( bumps == 2 )
      {
        state = 3;
      }
      else
      {
        state = 8;
      }
      break;
    case 11:
      ultrasonic_tmp=US_read_avg(); 
      if(*dir == EAST)
      {
        if(side_a)
        {
          //set ultrasonic north degrees (towards wall)
          if(ultrasonic_tmp - ultrasonic_val >= 5)
          {
            state = 14;
          }
          if(ultrasonic_tmp - ultrasonic_val <= 5)
          {
            state = 13;
          }
        }
        else
        {
          //set ultrasonic servo south towards wall
          if(ultrasonic_tmp - ultrasonic_val >= 5)
          {
            state = 13;
          }
          if(ultrasonic_tmp - ultrasonic_val <= 5)
          {
            state = 14;
          }
        }
      }
      if(*dir == WEST)
      {
        if(side_a)
        {
          //set ultrasonic servo north towards wall
          if(ultrasonic_tmp - ultrasonic_val >= 5)
          {
            state = 13;
          }
          if(ultrasonic_tmp - ultrasonic_val <= 5)
          {
            state = 14;
          }
        }
        else
        {
          //set ultrasonic servo south towards wall
          if(ultrasonic_tmp - ultrasonic_val >= 5)
          {
            state = 14;
          }
          if(ultrasonic_tmp - ultrasonic_val <= 5)
          {
            state = 13;
          }
        }
      }
        
      break;
    case 12:
      if(side_a)
      {
        if(read_green()<1000)
        {
          state = 10;
        }
        else
        {
          state = 11;
        }
      }
      if(!side_a)
      {
        if(read_green()<1000)
        {
          bumps++;
          state = 10;
        }
        else
        {
          if(bumps==1)
          {
            state = 1;
          }
          else
          {
            state = 8;
          }
        }
      }
      break;
    case 13:
      //adjust right
      state = 1;
    case 14:
      //adjust left
      state = 1;
      break;
  }
}
