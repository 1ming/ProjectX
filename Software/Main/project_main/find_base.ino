void find_base(boolean *side_a, Mag_dir::Mag_dir *mag2, unsigned int *dir, unsigned int *prev_dir)
{

  unsigned int state = 0;
  unsigned int go = 0;
  double US_tmp=0;
  double US_val;
  int adjust_pwm;

  while (1)
  {
    switch (state) {
      case 0:
        if (side_a)
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
        drive_heading(head_dir(mag2, ((*dir)++) % 4));
        *prev_dir = *dir;
        *dir = ((*dir ++)%4 +4) % 4;
        if (go == 1)
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
        motor_fwd(255);
        delay(2000);
        motor_stop();
        state = 3;
        break;
      case 3:
        //turn 180  CCW
        //turn left
        *prev_dir = *dir;
        *dir = ((*dir --)%4 +4) % 4;
        motor_fwd(255);
        delay(2000);
        motor_stop();
        // turn left
        *prev_dir = *dir;
        *dir = ((*dir --)%4 +4) % 4;
        state = 4;
        break;
      case 4:
        while (US_read_avg() > 10)
        {
          motor_fwd(255);
        }
        //turn right
        *prev_dir = *dir;
        *dir = (*dir ++) % 4;
        state = 5;
        break;
      case 5:
        
        if (*dir == west)
        {
          
          US_val = US_read_avg();
          motor_fwd(255);
          state = 6;
        }
        if (*dir == east)
        {
          
          motor_fwd(255);
          state = 8;
        }

        break;
      case 6:
        if (*dir == west)
        {
          if (read_green() < 1000)
          {
            state = 7;
          }
          if (read_green() < 1500)
          {
            //check ultrasonic
            state = 9;
          }
          if (read_green() <2000)
          {
            motor_stop();
            return;

          }
        }
        if (*dir == east)
        {
          if (read_green() < 1000)
          {
            state = 7;
          }
          if(read_green() < 1500)
          {
            state = 9;
          }
          if (read_green() < 2200)
          {
            motor_stop();
            
            if(IR_is_ramp() == true)
            {
              state = 3;
            }            
            else
            {
              return;
            }
          }
        }
        break;
      case 7:
        //turn 180  CW
        //turn right
        *prev_dir = *dir;
        *dir = ((*dir ++)%4 +4) % 4;
        motor_fwd(255);
        delay(2000);
        motor_stop();
        // turn right
        *prev_dir = *dir;
        *dir = ((*dir ++)%4 +4) % 4;
        state = 5;
        break;
      case 8:
        
        break;
      case 9:
        US_tmp=US_read_avg(); 
      if(*dir == east)
      {
        if(side_a)
        {
          //set ultrasonic north degrees (towards wall)
          if(US_tmp - US_val >= 5)
          {
            motor_stop();
            motor_on(0,adjust_pwm);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
          if(US_tmp - US_val <= 5)
          {
            motor_stop();
            motor_on(adjust_pwm,0);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
        }
        else
        {
          //set ultrasonic servo south towards wall
          if(US_tmp - US_val >= 5)
          {
            motor_stop();
            motor_on(adjust_pwm,0);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
          if(US_tmp - US_val <= 5)
          {
            motor_stop();
            motor_on(0,adjust_pwm);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
        }
      }
      if(*dir == west)
      {
        if(side_a)
        {
          //set ultrasonic servo north towards wall
          if(US_tmp - US_val >= 5)
          {
            motor_stop();
            motor_on(adjust_pwm,0);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
          if(US_tmp - US_val <= 5)
          {
            motor_stop();
            motor_on(0,adjust_pwm);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
        }
        else
        {
          //set ultrasonic servo south towards wall
          if(US_tmp - US_val >= 5)
          {
            motor_stop();
            motor_on(0,adjust_pwm);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
          if(US_tmp - US_val <= 5)
          {
            motor_stop();
            motor_on(adjust_pwm,0);
            delay(500);
            motor_stop();
            delay(50);
            state = 5;
          }
        }
      }
        break;
    }
  }
}


