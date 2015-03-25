namespace Mag_dir {
    typedef struct 
    {
      float NORTH;
      float SOUTH;
      float EAST;
      float WEST;
    } Mag_dir;
  
}

float head_dir(Mag_dir::Mag_dir *mag2, unsigned int next_dir)
   {
     if(next_dir == 0)
     {
       return mag2->NORTH;
     }
     if(next_dir == 1)
     {
       return mag2->EAST;
     }
     if(next_dir == 2)
     {
       return mag2->SOUTH;
     }
     if(next_dir == 3)
     {
       return mag2->WEST;
     }
   }
