__asm__("lis 5, 0x802f;stw 3, 0x6958(5)");

int main(void)
{ 
  float *base_addr = (float*)0x802f6900;
  int ** created_actor = (int**)(0x802f6958);
  int * created_actor_addr = (int*)(0x802f6958);
  float ** created_actorf = (float**)(0x802f6958);
  
  int * first_portal_addr = (int*)(base_addr);
  int * second_portal_addr = (int*)(base_addr+1);
  
  int ** first_portal = (int**)(base_addr);
  int ** second_portal = (int**)(base_addr+1);
  
  float ** first_portalf = (float**)(base_addr);
	float ** second_portalf = (float**)(base_addr+1);
  
  int * first_goomba = (int*)(base_addr+12);
  int * second_goomba = (int*)(base_addr+13);
  int * third_goomba = (int*)(base_addr+14);
  
  float * sin_addr = (float*)(base_addr+28);
  float * cos_addr = (float*)(base_addr+29);
  
  float * static_sin_addr = (float*)(base_addr+32);
  float * static_cos_addr = (float*)(base_addr+33);
  
  int * player_dir_addr = (int*)0x8154b904;
  
  int *portalnum = (int*)(base_addr+2);
  
  float *tmp = (float*)(base_addr+22);
  float *tmp2 = (float*)(base_addr+23);
  int *tmpint = (int*)(base_addr+24);
  
  //null pointer
  if(*created_actor == 0)
    return 0;
  
  *tmpint = 0x01240000;
  //if micro goomba
  if(*(*created_actor + 2) == *tmpint)
  {
    *tmpint = 0;
    if(*first_goomba == *tmpint)
      *first_goomba = *created_actor_addr;
    else if(*second_goomba == *tmpint)
      *second_goomba = *created_actor_addr;
    else if(*third_goomba == *tmpint)
      *third_goomba = *created_actor_addr;
  }
  
  //check if bobomb instead
  *tmpint = 0x00850000;
  if((*(*created_actor + 2) & 0xffff0000) == *tmpint)
  {
    //newly created is a bobomb
    //move it up from the bottom of Mario where it's created
    //*tmp2 = 10.0;
    //*tmp = *(*created_actorf + 44);
    //*(*created_actorf + 44) = *tmp + *tmp2;
    
    if(*portalnum == 0)
    {
      if(*first_portal_addr == 0)
        *first_portal_addr = *created_actor_addr;
      else
      {
        //make old one invisible
        //TODO: Delete!
        *(*first_portal + 73) = 0;
        //make old one untouchable
        *(*first_portal + 121) = 0;
        //set a new one!
        *first_portal_addr = *created_actor_addr;
      }
      
      *portalnum = 1;
    }
    else if(*portalnum == 1)
    {
      if(*second_portal_addr == 0)
        *second_portal_addr = *created_actor_addr;
      else
      {
        //make invisible
        *(*second_portal + 73) = 0;
        //make untouchable
        *(*second_portal + 121) = 0;
        *second_portal_addr = *created_actor_addr;
      }
      *portalnum = 2;
    }
    else if(*portalnum == 2)
    {
      if(*first_portal_addr == 0)
        *first_portal_addr = *created_actor_addr;
      else
      {
        //make invisible
        *(*first_portal + 73) = 0;
        //make untouchable
        *(*first_portal + 121) = 0;
        //*(*first_portal + 349) = 0;
        *first_portal_addr = *created_actor_addr;
      }
      *portalnum = 1;
    }
      
    
    if(*player_dir_addr == 0x00003000)
    {  
      *static_cos_addr = *cos_addr;
      *static_sin_addr = *sin_addr;
    }else
    {
      *tmp = -1.0;
      *static_cos_addr = *cos_addr*(*tmp);
      *static_sin_addr = *sin_addr*(*tmp);
    }
    
  }
  
  return 0;
}