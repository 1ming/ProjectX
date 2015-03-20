void find_base(boolean *side_a, Mag_dir::Mag_dir *mag2, unsigned int *dir, unsigned int *prev_dir)
{
  
  unsigned int state = 0;
  unsigned int go = 0;
  
  while(1)
  {
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
      if(go == 1)
      {
        state = 2;
      }
      else
      {
      state = 4;
      } 
      break;
    case 2:
      //drive forward
      go=2;
      motor_fwd(255);
      break;
    case 3:
      turn_90_lt();
      *prev_dir=*dir;
      *dir=(*dir--)%4; 
      if(go == 1)
      {
        state = 2;
      }
      else
      {
      state = 4;
      }     
      break;
    case 4:
        motor_fwd(255);
        delay(2000);
        motor_stop();
      break;
    case 5:
    
    if(read_green()>1500)
        {
          return;
        }
      if(*dir == south)
      {
       
        if(IR_read_dist() <= 15 || IR_read_dist() >= 10)
        {
          state = 1;
        }
        else
        {
          motor_stop();
          state = 2;
        }
      }
      if(*dir == north)
      {
        if(read_green() < 1000)
        {
          state = 1;
        }
        else
        {
          motor_stop();
          state = 3;
        }
      }
      break;
  }
  }
}


