
__asm__("lis 5, 0x802f;stw 3, 0x6958(5)");

int main(void)
{
  //delete actor function, execute this to kill things!
  int (*delete_actor)(int *addr) = 0x80162650;
  //float * (*get_player)(int ID) = 0x8005FB90;
  
  float *base_addr = (float*)0x802f6900;
  int ** created_actor = (int**)(0x802f6958);
  int * created_actor_addr = (int*)(0x802f6958);
  float ** created_actorf = (float**)(0x802f6958);
  
  int * button_store = (int*)(base_addr+4);
  
  int ** swooper_addr = (int**)(base_addr+26);
  
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
  
  float *tmp = (float*)(base_addr+23);
  float *tmp2 = (float*)(base_addr+24);
  int *tmpint = (int*)(base_addr+25);
  
  int * player_addr = (int*)(base_addr+11);
  float * player_addrf;
  
  //null pointer
  if(*created_actor == 0)
    return 0;
	

  if((*(*created_actor + 2) & 0xffff0000) == 0x00830000)
  {
	//swooper here, set it to non-hurting/non-interacting!
	*(*created_actor + 121) = 0;
	
	*swooper_addr = *created_actor;
  }
  
  // *tmpint = 0x01240000;
  //if micro goomba
  if((*(*created_actor + 2) & 0xffff0000) == 0x01240000)
  {
    //make it non-interactive
	*(*created_actor + 121) = 0;
     
    //*tmpint = 0;
    if(*first_goomba == 0)
	{
	  *first_goomba = *created_actor_addr;
	}
    else if(*second_goomba == 0)
	{
      *second_goomba = *created_actor_addr;
	}
    else if(*third_goomba == 0)
	{
      *third_goomba = *created_actor_addr;
	}
  }
  
  if((*(*created_actor + 2) == 0x00380000))
  {
	//make invisible
	*(*created_actor + 73) = 0;
        
    //make untouchable
    //*(*created_actor + 121) = 0;
	
	//return 0;
  }
  
  
  //NULL pointer!
  if(*player_addr == 0)
    return 0;
  
  player_addrf = *player_addr;
  
  int * player_dir_addr = (int*)(player_addrf+64);
  int * button_presses = (int*)(player_addrf+938);
  //int * player_dir_addr = (int*)0x8154b904;
  
  int *portalnum = (int*)(base_addr+2);
  
  
  //check if buzzy beetle instead
  *tmpint = 0x00380000;
  if((*(*created_actor + 2) == 0x00380000)
  &&
  (*button_presses & 0x06000000) == 0x06000000)
  {
  /*
  if((*button_presses & 0x06000000) != 0x06000000)
  {
	//was not shot from the portal gun, make it invisible!
	*(*created_actor + 73) = 0;
        
    //make untouchable
    *(*created_actor + 121) = 0;
	
	return 0;
  }
  */
	
    //newly created is a portal and was shot from the portal gun
    //move it up from the bottom of Mario where it's created,
	//and make it visible again
	*(*created_actor + 73) = 0x01000000;
    *tmp2 = 15.0;
    *tmp = *(*created_actorf + 44);
    *(*created_actorf + 44) = *tmp + *tmp2;
    
    if(*player_dir_addr == 0x00003000)
    {
      *tmp2 = 15.0;
      *tmp = *(*created_actorf + 43);
      *(*created_actorf + 43) = *tmp + *tmp2;
    }
    else
    {
      *tmp2 = 15.0;
      *tmp = *(*created_actorf + 43);
      *(*created_actorf + 43) = *tmp - *tmp2;
    }
    
    if(*portalnum == 0 || *portalnum == 2)
    {
      if(*first_portal_addr == 0)
        *first_portal_addr = *created_actor_addr;
      else
      {
        //delete!
        //*(*first_portal+1) = 0;
        //(*delete_actor)(*first_portal_addr);
      
        //make old one invisible
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
        
        //delete
        //*(*second_portal+1) = 0;
        //(*delete_actor)(*second_portal_addr);
        
        *second_portal_addr = *created_actor_addr;
      }
      *portalnum = 2;
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