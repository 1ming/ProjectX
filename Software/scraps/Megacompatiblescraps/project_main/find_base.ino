void find_base(boolean *side_a, unsigned int *dir, unsigned int *prev_dir)
{
  int ultrasonic_val;
  int ultrasonic_tmp;
  unsigned int state =0;
    switch (state) {
    case 0:
      if(side_a)
        {
          state = 1;
        }
        else
        {
          state = 2;
        }   
      break;
    case 1:
      //turn right
      *prev_dir=*dir;
      *dir=(*dir++)%4;
      state = 11;
      break;
    case 2:
      //turn left
      *prev_dir=*dir;
      *dir=(*dir--)%4;
      break;
    case 3:
      //drive forward
      if(*dir == WEST)
      {
        state = 12;
      }
      if(*dir == EAST)
      {
        state = 15;
      }
      break;
    case 4:
        //begin turn around
      break;
    case 5:
      
      break;
    case 6:
     
     break;
    case 7:
      
      break;
    case 8:
      
      break;
    case 9:
      
      break;
    case 10:
      
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
        if(read_green()<600)
        {
          //turn around state
        }
        if(read_green()<2200 && read_green()>1500)
        {
          state = 10;
        }
        else
        {
          state = 1;
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
    case 15:
      if(IR_ramp_incoming)
      {
        //turn around state
      }
      else
      {
        state = 12;
      }
  }
}


