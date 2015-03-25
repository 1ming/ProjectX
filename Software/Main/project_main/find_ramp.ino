unsigned char state = 0;
unsigned int bumps = 0;


int adjust_pwm = 255;

void find_ramp(boolean side_a,  int *dir,  int *prev_dir)
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
  const unsigned k = 15;
  const unsigned for_k= 200;

  while (1)
  {
    //state transitions
    switch (state) {
      case 0:
        if (side_a)
        {
          state = 1;
        ultrasonic_val = US_read_avg();
        guide.write(GUIDE_UP);

        }
        else
        {
          state = 6;
        }
        break;
      case 1:
        //drive forward
        motor_fwd(255);
        delay(for_k);        
        state = 12;
        break;
      case 2:
      if(side_a)
      {
        Serial.println("case 2, turn left");
        turn_90_lt();
        Serial.println("stop");
        motor_stop();
        delay(500);
        //*prev_dir = *dir;
        //*dir = (((*dir--) % 4) + 4) % 4;
        //wait while encoders reach certain number of ticks
        
        Serial.println("fwd until 30 cm");
        motor_fwd(255);
        
        while(IR_read_dist() > 30 || IR_read_dist() < 20);
        motor_stop();
        return;
      }
      else
      {
        motor_stop();
        return;
      }
       
      case 3:
        IR_val = IR_sweep_ramp();
        if (abs(IR_val) <= 3)
        {
          return;
        }
        if (IR_val >= 5)
        {
          state = 4;
        }
        if (IR_val <= -5)
        {
          state = 5;
        }
        break;
      case 4:
        //adjust right
        motor_on(255, 0);
        delay(250);
        motor_stop();
        state = 3;
        break;
      case 5:
        //adjust left
        motor_on(0, 255);
        delay(250);
        motor_stop();
        state = 3;
        break;
      case 6:
       motor_stop();
       motor_fwd(255);
       state = 12;
      case 7:
        //turn left
        *prev_dir = *dir;
        *dir = (((*dir--) % 4) + 4) % 4;
        //wait for number of ticks
        if (*prev_dir == east)
        {
          state = 8;
        }
        if (*dir == west)
        {
          state = 9;
        }
        break;
      case 8:
         motor_fwd(255);
          delay(50);
        
        state = 12;
        break;
      case 9:
        motor_fwd(255);
        delay(2000);
        motor_stop();
        //wait for encoder ticks
        if (*dir == east)
        {
          state = 7;
        }
        if (*dir == west)
        {
          state = 10;
        }
        break;
      case 10:
        turn_90_lt();
        *prev_dir = *dir;
        *dir = (((*dir++) % 4) + 4) % 4;
        //wait for encoder ticks
        if (*dir == east && bumps == 0)
        {
          state = 9;
        }
        if (*dir == north && bumps == 0)
        {
          state = 8;
        }
        if ( bumps == 1)
        {
          state = 1;
        }
        if ( bumps == 2 )
        {
          state = 3;
        }
        else
        {
          state = 8;
        }
        break;
      case 11:
        motor_stop();
        delay(50);
        ultrasonic_tmp = US_read_avg();
        adjust_pwm = k * (abs(ultrasonic_tmp - ultrasonic_val));
        if(adjust_pwm > 255) adjust_pwm = 255;
        
        
          if (side_a)
          {          
            us_hor.write(US_HOR_LEFT);
            if (ultrasonic_tmp - ultrasonic_val >= 2.5)
            {
              Serial.println("adjust left");
              //motor_stop();  
              delay(50);            
              motor_on(-adjust_pwm, 255);
              delay(75);              
              motor_stop();
              delay(50);       
              state = 1;
            }
            if (ultrasonic_tmp - ultrasonic_val <= 2.5)
            {
              Serial.println("adjust right");
              motor_stop();
              motor_on(255, -adjust_pwm);
              delay(75); 
              motor_stop();
              delay(50);
              state = 1;
            }
          }
          else
          {
            us_hor.write(US_HOR_LEFT);
            if (ultrasonic_tmp - ultrasonic_val >= 2.5)
            {
             motor_stop();
              motor_on(255, -adjust_pwm);
              delay(75); 
              motor_stop();
              delay(50);
              state = 1;
            }
            if (ultrasonic_tmp - ultrasonic_val <= 2.5)
            {
              delay(50);            
              motor_on(-adjust_pwm, 255);
              delay(75);              
              motor_stop();
              delay(50);       
              state = 1;
            }
          }

        break;
      case 12:
        if(side_a)
        {
          if (check_white() )
          {
            state = 2;
            Serial.println("white is checked");
          }
          else
          {
            state = 11;
          }
        }
        else
        {
          if (read_green() >1700)
          {
            state = 2;
          }
          else
          {
            state = 11;
          }
        }
        
        break;
    }
  }
}


