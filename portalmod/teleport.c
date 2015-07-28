//store colliding adresses to 802f6950 and -54
/*
#define BASE_ADDR 0x802f6900
#define MARIO_ADDR 0x8154b804
#define XSPEED  67
#define YSPEED  59
*/

__asm__("lis 5, 0x802f;lwz 4, 4(23);lwz 3, 4(24);stw 3, 0x6950(5);stw 4, 0x6954(5)");

int main(void)
{ 
  float *base_addr;// = (float*)0x802f6940;
  //base_addr = (float*)BASE_ADDR;
  base_addr = (float*)0x802f6900;
  int * collider1 = (int*)0x802f6950;
  int * collider2 = (int*)0x802f6954;
  
  int ** collider1_addr = (int**)0x802f6950;
  int ** collider2_addr = (int**)0x802f6954;
  
  float ** collider1f = (float**)(0x802f6950);
  float ** collider2f = (float**)(0x802f6954);
  
  //float * mario = (float*)MARIO_ADDR;
  
  float *tmp = (float*)(base_addr+37); //0x802f6994
  float *tmp2 = (float*)(base_addr+38); //0x802f6998
  int *tmpint = (int*)(base_addr+39); //0x802f699c
  int *timer = (int*)(base_addr+40); //0x802f69a0
  int *has_teleported = (int*)(base_addr+41);
  
  int * portal1_addr = (int*)(base_addr);
  int * portal2_addr = (int*)(base_addr+1);
  
  float ** teleporter = (float**)collider1f;
  
  //*tmpint = 0;
  
  float *angle = (float*)(0x802f6800);
  float cosx = fabs((*angle)*(*angle)*(*angle));
	*tmp = 12.0f;
  *tmp2 = cosx;
	cosx = *tmp2/(*tmp);
	*tmp = 1.0f;
  *tmp2 = cosx;
  cosx = *tmp + *tmp2; //cosx = 1+a^3/12;
	*tmp = 2.0f;
  *tmp2 = cosx;
	cosx = *tmp2 - (*angle)*(*angle)/(*tmp); //finito
	
	*tmp = cosx;
  
  float ** first_portalf = (float**)(base_addr);
  float ** second_portalf = (float**)(base_addr+1);
  
  int ** first_portal = (int**)(base_addr);
  int ** second_portal = (int**)(base_addr+1);
  
  //INCREASE TIMER IN GAME LOOP!!!
  //*tmpint = 32;
  
  //make sure that one of them isn't a micro goomba
  if(*(*collider1_addr + 2) != 0x01240100 && *(*collider2_addr + 2) != 0x01240100)
  {
    //check if one of the colliders is a portal
    if(*collider1 == *portal1_addr && *collider2 != *portal2_addr && *timer > 32
    && *(*collider1_addr + 73) != 0 && *(*collider2_addr + 73) != 0)
    {
      //set to non-hurting
      //*(*collider1f + 227) = 0;
      //*(*collider2f + 227) = 0;

      //null pointer
      if(*portal2_addr == 0)
        return 0;
      
      //move collider2 to portal 2 if there is one
      *(*collider2f + 43) = *(*second_portalf + 43);
      *(*collider2f + 44) = *(*second_portalf + 44);
      
      
      teleporter = collider2f;
            
      //reset timer
      *tmpint = 0;
      *timer = *tmpint;
      *has_teleported = 1;
    }
	
    if(*collider1 == *portal2_addr && *collider2 != *portal1_addr && *timer > 32
    && *(*collider1_addr + 73) != 0 && *(*collider2_addr + 73) != 0)
    {

      //null pointer
      if(*portal1_addr == 0)
        return 0;
        
      //move collider2 to portal 1 if the portal is not dead
       *(*collider2f + 43) = *(*first_portalf + 43);
       *(*collider2f + 44) = *(*first_portalf + 44);
       
       teleporter = collider2f;
       
       //reset timer
       *tmpint = 0;
       *timer = *tmpint;
       *has_teleported = 1;
    }
	
	
    if(*collider2 == *portal2_addr && *collider1 != *portal1_addr && *timer > 32
    && *(*collider1_addr + 73) != 0 && *(*collider2_addr + 73) != 0)
    {
      
      //null pointer
      if(*portal1_addr == 0)
        return 0;
        
      //move collider1 to portal 1 if there is one
      *(*collider1f + 43) = *(*first_portalf + 43);
      *(*collider1f + 44) = *(*first_portalf + 44);
      
      teleporter = collider1f;
      
      //reset timer
      *tmpint = 0;
      *timer = *tmpint;
      *has_teleported = 1;
    }
    
    if(*collider2 == *portal1_addr && *collider1 != *portal2_addr && *timer > 32
    && *(*collider1_addr + 73) != 0 && *(*collider2_addr + 73) != 0)
    {
      //null pointer
      if(*portal2_addr == 0)
        return 0;
    
      //move collider1 to portal 2 if there is one
      *(*collider1f + 43) = *(*second_portalf + 43);
      *(*collider1f + 44) = *(*second_portalf + 44);
      
      teleporter = collider1f;
      
      //reset timer
       *tmpint = 0;
       *timer = *tmpint;
       *has_teleported = 1;
    }
    
    
    
    if(*has_teleported)
    {
      //check orientation of portals
      //_  _, flip y speed
      if(*(*second_portal + 157) == 0x2000 && *(*first_portal + 157) == 0x2000)
      {
        //check for ~zero speed
        *tmp = 3.0;
        *tmp2 = 5.0;
        if(fabs(*(*teleporter + 59)) < *tmp)
          *(*teleporter + 59) = *tmp2;
        else
        {
          *tmp = -1.0;
          *(*teleporter + 59) *= *tmp; //flip y
        }
      }
      
      //^ ^, flip y speed
      else if(*(*second_portal + 157) >= 0x4000000 && *(*first_portal + 157) >= 0x4000000)
      {
        //check for ~zero speed
        *tmp = .5;
        *tmp2 = 2.0;
        if(fabs(*(*teleporter + 59)) < *tmp)
          *(*teleporter + 59) = -*tmp2;
        else
        {
          *tmp = -1.0;
          *(*teleporter + 59) *= *tmp; //flip y
        }
      }
      
      //_|  _|, flip x speed
      else if(*(*second_portal + 157) == 0x28 && *(*first_portal + 157) == 0x28)
      {
        //check for ~zero speed
        *tmp = .5;
        *tmp2 = 2.0;
        if(fabs(*(*teleporter + 67)) < *tmp)
          *(*teleporter + 67) = *tmp2;
        else
        {
          *tmp = -1.0;
          *(*teleporter + 67) *= *tmp; //flip x
        }
      }
      
      // |_  |_, flip x speed
      else if(*(*first_portal + 157) == 0x14 && *(*second_portal + 157) == 0x14)
      {
        //check for ~zero speed
        *tmp = .5;
        *tmp2 = 2.0;
        if(fabs(*(*teleporter + 67)) < *tmp)
          *(*teleporter + 67) = -*tmp2;
        else
        {
          *tmp = -1.0;
          *(*teleporter + 67) *= *tmp; //flip x
        }
      }
      
      
      //_| _  flip y and x and neg
      else if( (*(*second_portal + 157) == 0x28 && *(*first_portal + 157) == 0x2000) ||
      (*(*first_portal + 157) == 0x28 && *(*second_portal + 157) == 0x2000))
      {
        *tmp2 = -1.0;
        
        *tmp = *(*teleporter + 59);
        *(*teleporter + 59) = *(*teleporter + 67)*(*tmp2);
        *(*teleporter + 67) = *tmp*(*tmp2);
      }
      
      //_| ^ OR |_ _, flip y and x
      else if((*(*second_portal + 157) == 0x28 && *(*first_portal + 157) == 0x2000)
      || (*(*second_portal + 157) == 0x2000 && *(*first_portal + 157) == 0x28)
      || (*(*second_portal + 157) == 0x14 && *(*first_portal + 157) == 0x2000)
      || (*(*second_portal + 157) == 0x2000 && *(*first_portal + 157) == 0x14))
      {
        *tmp = *(*teleporter + 59);
        *(*teleporter + 59) = *(*teleporter + 67);
        *(*teleporter + 67) = *tmp;
      }
      
    
    }
    }
	
	//reset colliders
	*tmpint = 0;
	*collider1 = *tmpint;
	*collider2 = *tmpint;
  
  *has_teleported = *tmpint;
  
  return 0;
}

