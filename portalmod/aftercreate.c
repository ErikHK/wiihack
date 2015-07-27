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
  
  int *portalnum = (int*)(base_addr+2);
  
  float *tmp = (float*)(base_addr+22);
  float *tmp2 = (float*)(base_addr+23);
  int *tmpint = (int*)(base_addr+24);
  
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
  if(*(*created_actor + 2) == *tmpint)
  {
    //newly created is a bobomb
    if(*portalnum == 0)
    {
      *first_portal_addr = *created_actor_addr;
      *portalnum = 1;
    }
    else if(*portalnum == 1)
    {
      *second_portal_addr = *created_actor_addr;
      *portalnum = 2;
    }
    else if(*portalnum == 2)
    {
      *first_portal_addr = *created_actor_addr;
      *portalnum = 1;
    }
      
  }
  
  return 0;
}

