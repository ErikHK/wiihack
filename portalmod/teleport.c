
//#define BASE_ADDR	0x802f6900
//#define ANGLE		0x802f6800

typedef unsigned short u16;

//store colliding adresses to 802f6950 and -54
__asm__("lis 5, 0x802f;lwz 4, 4(23);lwz 3, 4(24);stw 3, 0x6950(5);stw 4, 0x6954(5)");

int main(void)
{
  int (*CreateActor)(u16 classID, int settings, float * pos, char rot, char layer) = 0x80064610;
  float *base_addr;// = (float*)0x802f6940;
  //base_addr = (float*)BASE_ADDR;
  base_addr = (float*)0x802f6900;
  int * collider1 = (int*)(base_addr + 20);
  int * collider2 = (int*)(base_addr + 21);
  
  int ** collider1_addr = (int**)(base_addr + 20);
  int ** collider2_addr = (int**)(base_addr + 21);
  
  float ** collider1f = (float**)(base_addr + 20);
  float ** collider2f = (float**)(base_addr + 21);
  
  //float * mario = (float*)MARIO_ADDR;
  
  int * teleporting_to = (int*)(base_addr + 27);
  int * teleporter_addr = (int*)(base_addr + 26);
  
  float *tmp = (float*)(base_addr+37); //0x802f6994
  float *tmp2 = (float*)(base_addr+38); //0x802f6998
  float *tmp3 = (float*)(base_addr+42); //
  int *tmpint = (int*)(base_addr+39); //0x802f699c
  int *timer = (int*)(base_addr+40); //0x802f69a0
  int *has_teleported = (int*)(base_addr+41); //0x802f69a4
  
  int * portal1_addr = (int*)(base_addr);
  int * portal2_addr = (int*)(base_addr+1);
  
  float ** teleporter = (float**)collider1f;
  float ** enter_portalf = (float**)collider2f;
  float ** exit_portalf = (float**)collider2f;
  
  int ** enter_portal = (int**)collider1_addr;
  int ** exit_portal = (int**)collider2_addr;
  
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
  
  //make sure that one of them isn't a micro goomba
  if(*(*collider1_addr + 2) == 0x01240100 || *(*collider2_addr + 2) == 0x01240100)
    return 0;
    
  //make sure both of them aren't portals!
  if(*(*collider1_addr + 2) == 0x00380100 && *(*collider2_addr + 2) == 0x00380100)
    return 0;
  
  //check if one or the other (or both) are invisible
  if(*(*collider1_addr + 73) == 0 || *(*collider2_addr + 73) == 0)
    return 0;
    
  //make sure the portals are stationary, you shouldn't be able to teleport
  //when the portal is flying!
  //BUG!!!! ONE OF THEM CAN BE MARIO, HE SHOULD BE ABLE TO FLY!!!
  //|| *(*collider2_addr + 157) == 0)
  //  return 0;
  
  //check if one of the colliders is a stored portal
  if(*collider1 == *portal1_addr && *collider2 != *portal2_addr && *timer > 10)
  {
    //if portal is flying, can't teleport
    if(*(*collider1_addr + 157) == 0)
       return 0;
	
	//check if the other portal is flying!
	if(*(*second_portal + 157) == 0)
	  return 0;
  
    //null pointer
    if(*portal2_addr == 0)
      return 0;
      
    //move collider2 to portal 2 if there is one
    //*(*collider2f + 43) = *(*second_portalf + 43);
    //*(*collider2f + 44) = *(*second_portalf + 44);
	
	*teleporting_to = 2;
	*teleporter_addr = *collider2;
    
    teleporter = collider2f;
    enter_portalf = collider1f;
    enter_portal = collider1_addr;
    
    exit_portalf = second_portalf;
    exit_portal = second_portal;
            
    //reset timer
    *tmpint = 0;
    *timer = *tmpint;
    //*has_teleported = 1;
  }
  
  else if(*collider1 == *portal2_addr && *collider2 != *portal1_addr && *timer > 10)
  {
  
    //if portal is flying, can't teleport
    if(*(*collider1_addr + 157) == 0)
      return 0;
	  
	//check if the other portal is flying! not tried!
	if(*(*first_portal + 157) == 0)
	  return 0;
  
    //null pointer
    if(*portal1_addr == 0)
      return 0;
        
    //move collider2 to portal 1 if the portal is not dead
    *(*collider2f + 43) = *(*first_portalf + 43);
    *(*collider2f + 44) = *(*first_portalf + 44);
	
	*teleporting_to = 1;
	*teleporter_addr = *collider2;
	
    teleporter = collider2f;
    enter_portalf = collider1f;
    enter_portal = collider1_addr;
    exit_portalf = first_portalf;
    exit_portal = first_portal;
       
    //reset timer
    *tmpint = 0;
    *timer = *tmpint;
    *has_teleported = 1;
  }
  
  
  else if(*collider2 == *portal2_addr && *collider1 != *portal1_addr && *timer > 10)
  {
    //if portal is flying, can't teleport
    if(*(*collider2_addr + 157) == 0)
      return 0;
  
    //null pointer
    if(*portal1_addr == 0)
      return 0;
        
    //move collider1 to portal 1 if there is one
    *(*collider1f + 43) = *(*first_portalf + 43);
    *(*collider1f + 44) = *(*first_portalf + 44);
      
	*teleporting_to = 1;
	*teleporter_addr = *collider1;
	  
    teleporter = collider1f;
    enter_portalf = collider2f;
    enter_portal = collider2_addr;
    exit_portalf = first_portalf;  
    exit_portal = first_portal;
    
    //reset timer
    *tmpint = 0;
    *timer = *tmpint;
    *has_teleported = 1;
  }
    
  else if(*collider2 == *portal1_addr && *collider1 != *portal2_addr && *timer > 10)
  {
    //if portal is flying, can't teleport
    if(*(*collider2_addr + 157) == 0)
      return 0;
      
    //null pointer
    if(*portal2_addr == 0)
      return 0;
    
    //move collider1 to portal 2 if there is one
    *(*collider1f + 43) = *(*second_portalf + 43);
    *(*collider1f + 44) = *(*second_portalf + 44);
      
	*teleporting_to = 2;
	
	*teleporter_addr = *collider1;
	  
    teleporter = collider1f;
    enter_portalf = collider2f;
    enter_portal = collider2_addr;
    exit_portalf = second_portalf;
    exit_portal = second_portal;
    
    //reset timer
    *tmpint = 0;
    *timer = *tmpint;
    //*has_teleported = 1;
  }
    
    
  //here it has teleported through the portal,
  //move it out from the portal and mirror/switch speed,
  //and make sure the speed isn't zero!
  //entered portal is enter_portal, actor is teleporter,
  //destination is exit_portal
  if(*has_teleported)
  {
    
    //first take care of moving and minimum speed
    //TODO: MAX SPEED!
    
    //if exit portal is on the ground, move teleporter up
    //TODO: move to the side if possible!
    if(*(*exit_portal + 157) == 0x2000)
    {
      *tmp2 = 15.0;
      *tmp = *(*teleporter + 44);
      *tmp += *tmp2;
      *(*teleporter + 44) = *tmp;
    }
    
    //if exit portal is up, move teleporter down
    else if(*(*exit_portal + 157) >= 0x04000000)
    {
      *tmp2 = -15.0;
      *tmp = *(*teleporter + 44);
      *tmp += *tmp2;
      *(*teleporter + 44) = *tmp;
    }
    
    //if exit portal is to the left, move teleporter right
    else if(*(*exit_portal + 157) == 0x28)
    {
      *tmp2 = 15.0;
      *tmp = *(*teleporter + 43);
      *tmp += *tmp2;
      *(*teleporter + 43) = *tmp;
    }
  
    //if exit portal is to the right, move teleporter left
    else if(*(*exit_portal + 157) == 0x14)
    {
      *tmp2 = -15.0;
      *tmp = *(*teleporter + 43);
      *tmp += *tmp2;
      *(*teleporter + 43) = *tmp;
    }
    
	
    //check orientation of portals
    //_  _ flip y speed	
    if((*(*first_portal + 157) & 0x0000f000) != 0 && (*(*second_portal + 157) & 0x0000f000) != 0)
    {
	  *tmp = -3.0;
	  *tmp3 = 5.0;
	  *tmp2 = *(*teleporter + 59);
	  if(*tmp2 > *tmp)
      {
        
		*(*teleporter + 59) = *tmp3; //flip y
      }
	  else
	  {
	    *tmp3 = -1.0;
	    *(*teleporter + 59) *= *tmp3; //flip y
	  }
	  
	  //give a little x speed so he won't fall down the portal again!	  
	  *tmp = 1.0;
      *(*teleporter + 67) = *tmp;
    }
	
	//^ ^, flip y speed
	if( (*(*first_portal + 157) >= 0x04000000 && *(*second_portal + 157) >= 0x04000000))
	{
	    *tmp = -1.0;
	    *(*teleporter + 59) *= *tmp; //flip y
	}
	
    //_|  _| OR |_ |_ flip x speed
    if( (*(*enter_portal + 157) == 0x28 && *(*exit_portal + 157) == 0x28)
    || (*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) == 0x14))
    {
      *tmp = -1.0;
      *(*teleporter + 67) *= *tmp; //flip x
    }
    
    //enter to right, exit from up 
    //yspeed = xspeed
    //xspeed = 0
    if(*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) >= 0x04000000)
    {
      *tmp = *(*teleporter + 67); // *tmp = xspeed
      *(*teleporter + 59) *= *tmp; //yspeed = xspeed
      
      *tmp = 0;
      *(*teleporter + 67) = *tmp;
      *(*teleporter + 58) = *tmp;
      
    }
	
	//enter to right, exit from down
	//yspeed = xspeed
    //xspeed = 1 for mario
	//xspeed = yspeed for others
	
	if(*(*enter_portal + 157) == 0x14 && (*(*exit_portal + 157) & 0x0000f000) != 0)
	{
	  int ** teleporteri = (int**)teleporter;
	  *tmp = 3.0;
	  *tmp2 = *(*teleporter + 67);
	  *tmp3 = 5.0;
	  if(*(*teleporteri + 2) == 0x000d0100) //IF MARIO or other player
	  {
	    if(*tmp2 < *tmp) //if xspeed < 3
	    {
	      
		  *(*teleporter + 59) = *tmp3;
        }
	    else
	    {
	      *tmp = *(*teleporter + 67); // *tmp = xspeed
          *(*teleporter + 59) *= *tmp; //yspeed = xspeed
	    }
	  
	    //give a little x speed so he won't fall down the portal again!	  
	    *tmp = 1.0;
        *(*teleporter + 67) = *tmp;
	  }
	  else //NOT a player, it's an enemy or similar!
	  {
	    *tmp = *(*teleporter + 58); // *tmp = xspeed
		*(*teleporter + 58) = *(*teleporter + 59); //xspeed = yspeed
        *(*teleporter + 59) = *tmp; //yspeed = xspeed 
	  }
	  
	}
	
    
    //enter to up, exit from left
    //xspeed = yspeed
    //yspeed = 0
    if(*(*enter_portal + 157) >= 0x04000000 && *(*exit_portal + 157) == 0x28)
    {
      *tmp2 = 1.0;
      *tmp = *(*teleporter + 59); // *tmp = yspeed
      
      //check if |yspeed| > 1.0
      if(*tmp > *tmp2)
      {
        //*tmp2 = 1.0;
        *(*teleporter + 67) = *tmp2; //xspeed = 1.0
        *(*teleporter + 58) = *tmp2; //xspeed = 1.0
      }
      else
      {
        *(*teleporter + 67) = *tmp; //xspeed = yspeed
        *(*teleporter + 58) = *tmp; //xspeed = yspeed
      }
	  *tmp = 0;
	  *(*teleporter + 59) = *tmp; //yspeed = 0
    }
	
	//enter to up, exit from right OR enter to down, exit from left
    //xspeed = -yspeed
    if((*(*enter_portal + 157) >= 0x04000000 && *(*exit_portal + 157) == 0x14)
    || ( (*(*enter_portal + 157) & 0x0000f000) != 0 && *(*exit_portal + 157) == 0x28))
    {
      *tmp2 = -1.0;
      *tmp = *(*teleporter + 59) * (*tmp2); // *tmp = -yspeed
      
	  //check if |yspeed| > 1.0
      if(*tmp > fabs(*tmp2))
      {
        *(*teleporter + 67) = fabs(*tmp2); //xspeed = 1.0
      }
      *(*teleporter + 67) = *tmp; //xspeed = -yspeed
    }
    
    //enter to right, exit from up
    //yspeed = -xspeed
	//xspeed = 0
    if(*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) >= 0x04000000)
    {
      *tmp2 = -1.0;
      *tmp = *(*teleporter + 67); // *tmp = yspeed
      *(*teleporter + 59) = *tmp * (*tmp2); //yspeed = -xspeed
    }
	
	//enter to left, exit from down
	//yspeed = -xspeed
	//xspeed = -1 for mario
	//xspeed = -yspeed for others
	
	if(*(*enter_portal + 157) == 0x28 && (*(*exit_portal + 157) & 0x0000f000) != 0)
	{
	  int ** teleporteri = (int**)teleporter;
	  
	  if(*(*teleporteri + 2) == 0x000D0100)
	  {
	  
	  *tmp = -3;
	  *tmp2 = *(*teleporter + 67);
	  
	  if(*tmp2 > *tmp) //if |xspeed| < 3
	  {
	    *tmp2 = 5.0;
		*(*teleporter + 59) = *tmp2;
		
      }
	  else
	  {
	  
	    *tmp2 = -1.0;
        *tmp = *(*teleporter + 67); // *tmp = xspeed
        *(*teleporter + 59) = *tmp * (*tmp2); //yspeed = -xspeed
	  }
	  
	  //give a little x speed so he won't fall down the portal again!
	  *tmp = -1.0;
      *(*teleporter + 67) = *tmp;
	  
	  }
	  else //not mario or other player!
	  {
	    *tmp2 = -1.0;
        *tmp = *(*teleporter + 58); // *tmp = xspeed
		*(*teleporter + 58) = *(*teleporter + 59); //xspeed = yspeed
		*(*teleporter + 58) *= *tmp2;	//xspeed = -yspeed
        *(*teleporter + 59) = *tmp * (*tmp2); //yspeed = -xspeed
	  }
	  
	}
	
	
	//enter to down, exit from right
	//xspeed = yspeed for mario
	//xspeed = yspeed for others
	//yspeed = 0 for mario
	//yspeed = xspeed for others
	if(*(*enter_portal + 157) == 0x2000 && *(*exit_portal + 157) == 0x14)
	{
	  int ** teleporteri = (int**)teleporter;
	  
	  //if mario or other player
	  if(*(*teleporteri + 2) == 0x000D0100)
	  {
	    *tmp2 = 2.0;
	    *tmp = *(*teleporter + 59);
		*tmp /= *tmp2;	//*tmp = yspeed/2
		*(*teleporter + 59) = 0;
		*(*teleporter + 67) = *tmp;
	    
	  }
	  else //if enemy or similar!
	  {
	    //*tmp = -.6;
		//*tmp2 = *(*teleporter + 59);
		*(*teleporter + 59) = *(*teleporter + 58); //yspeed = xspeed
	  }
	  
	  *tmp2 = -fabs(*(*teleporter + 58));
		
      //flip x!
	  *(*teleporter + 58) = *tmp2;
	  
	}
	
    
  }
    
  //reset colliders
  //*tmpint = 0;
  *collider1 = 0;
  *collider2 = 0;
  
  *has_teleported = 0;
  
  return 0;
}

