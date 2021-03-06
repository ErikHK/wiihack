//int main(int argc, char *argv[])
//#include<stdio.h>

typedef unsigned short u16;

//active wiimote = 8042A748

//Addresses, easily converted to NTSC this way!
#define GET_PLAYER		0x8005fb90
#define BASE_ADDR		0x802f6900
#define CREATE_ACTOR	0x80064610
#define WIIMOTE_PTR		0x80377F88

int main(void)
{

  //create actor
  int (*CreateActor)(u16 classID, int settings, float * pos, char rot, char layer) = 0x80064610;
  //int (*get_player)(int ID, int some_addr, int one1, int zero, int one2) = 0x8005FB90;
  int (*get_player)(int ID) = 0x8005fb90;
  
  float *base_addr;// = (float*)0x802f6940;
  base_addr = (float*)BASE_ADDR;
  float ** goomba_addr = (float**)(base_addr+12);
  int * goomba_addri = (int*)(base_addr+12);
  int ** goomba_addrii = (int**)(base_addr+12);
  
  //int ** swooper_addr = (int**)(base_addr+26);
  //float ** swooper_addrf = (float**)(base_addr+26);

  
  int * button_store = (int*)(base_addr+4);
  
  int * tmpint = (int*)(base_addr+6);
  int ** created_actor = (int**)(base_addr+6);
  //int ** created_actor = (int**)(base_addr+22);
  
  float * tmp = (float*)(base_addr+5);
  float * tmp2 = (float*)(base_addr+7);
  float * tmp3 = (float*)(base_addr+9);
  int * portal_timer = (int*)(base_addr+8);
  int ** first_portal = (int**)(base_addr);
  int ** second_portal = (int**)(base_addr+1);
  
  int * first_portal_addr = (int*)(base_addr);
  int * second_portal_addr = (int*)(base_addr+1);
  int * last_direction = (int*)(base_addr+15);
  
  int * teleporting_to = (int*)(base_addr + 27);
  int ** teleporter = (int*)(base_addr + 26);
  float ** teleporterf = (int*)(base_addr + 26);
  
  int * curr_portal = (int*)(base_addr+2);
  
  float ** first_portalf = (float**)(base_addr);
  float ** second_portalf = (float**)(base_addr+1);
  //float * player_addr = (float*)0x8154b804;
  float * player_addr;
  //int * player_addri;
  
  int * player_store_addr = (int*)(base_addr+11);
  int * get_player_timer = (int*)(base_addr+16);
  
  int *has_teleported = (int*)(base_addr+41); //0x802f69a4
  
  *get_player_timer += 1;
  if(*get_player_timer > 100)
  {
    //get pointer to player number 0, always mario?
    //this isn't that reliable, it gives 0 sometimes, when?
	//I think this crashes everything sometimes as well..
    *player_store_addr = get_player(0);
    *get_player_timer = 0;
  }
  
  
  //*player_store_addr = 0x8154b804;

  //NULL pointer!
  if(*player_store_addr < 0x81500000)
  {
    return 0;
  }
  
  player_addr = *player_store_addr;
  
  //*player_store_addr = player_addr;
  
  //if((int*)player_addr == 0)
  //  return 0;
  
  int * player_free_addr = (int*)(player_addr+157);
  int * player_dir_addr = (int*)(player_addr+64);
  //int * button_presses = (int*)0x8154c6ac;
  int * button_presses = (int*)(player_addr+938);
  float * dist = (float*)(base_addr+10);
  
  int *timer = (int*)(base_addr+40); //0x802f69a0
  
  float * sin_addr = (float*)(base_addr+28);
  float * cos_addr = (float*)(base_addr+29);
  
  float * static_sin_addr = (float*)(base_addr+32);
  float * static_cos_addr = (float*)(base_addr+33);
  
  //int * goomba = *goomba_addr;
  
  //*tmpint = 1;
  //*timer += *tmpint;
  *timer += 1;
  
  *tmp2 = 1.7;
  float ** wiimoteptr = (float **)(0x80377F88);
  
  //choose id 0
  float * tilt_addr = (float *)((*wiimoteptr+0) + 11);
  //float * tilt_addr = (float*)0x807612c8;
  
  float * angle = (float*)(base_addr+24);
  int * anglei = (int*)(base_addr+24);
  //*(base_addr+5) = 1.571;	//pi/2
  *tmp = *tmp2;	//pi/2 + x
  
  *angle = (*tilt_addr);	//pi/2
  *angle *= *tmp;
  
  
  //SINE
  *tmp = 7.0;
  *tmp2 = 1.0;
  //float sinx = (*angle)* (*tmp2 - (*angle)*(*angle)/(*tmp));
  *sin_addr =  (*angle)*(*angle)/(*tmp);
  *tmp = *sin_addr; //*tmp = a^2/7
  *sin_addr = *tmp2 - *tmp; //1 - a^2/7
  *tmp = *sin_addr;
  *sin_addr = *tmp * (*angle);
  
  //COSINE!
  *cos_addr = fabs((*angle)*(*angle)*(*angle));
  *tmp = 12.0;
  *tmp2 = *cos_addr;
  *cos_addr = *tmp2/(*tmp); //cosx = x^3/12
  *tmp2 = 1.0;
  *tmp = *cos_addr;
  *cos_addr = *tmp + *tmp2; //cosx = 1+x^3/12
  *tmp2 = -2;
  *tmp = (*angle)*(*angle);
  *tmp3 = *tmp/(*tmp2); //*tmp3 = -x^2/2
  *tmp = *cos_addr; //*tmp = 1+x^3/12
  *cos_addr = *tmp + *tmp3; //yey, cosx = 1+x^3/12-x^2/2
  
  /*
  if(*swooper_addr > 0x81500000)
  {
	*(*swooper_addrf + 43) = *(player_addr + 43);
	*(*swooper_addrf + 44) = *(player_addr + 44);
  }
  */
  
  if( *goomba_addri > 0x81500000 && *(goomba_addri+1) > 0x81500000 &&  *(goomba_addri+2) > 0x81500000) //sanity check
  {
    //make crosshairs visible when B is held down, invisible otherwise!
    if(((*button_presses & 0x04000000) == 0x04000000))
	{
      *(*goomba_addrii + 73) = 0x01000000;
	  //*(*(goomba_addrii+1) + 73) = 0x01000000;
	  *(*(goomba_addrii+2) + 73) = 0x01000000;
	  //*(*swooper_addr + 73) = 0x01000000;
	}
	else
	{
	  *(*goomba_addrii + 73) = 0;
	  *(*(goomba_addrii+1) + 73) = 0;
	  *(*(goomba_addrii+2) + 73) = 0;
	  //*(*swooper_addr + 73) = 0;
	  *dist = 15.0;
	}
  
    //move crosshairs outwards!
	*tmp = 200.0f;
	*tmp2 = 4.0f;
	*tmp3 = 200.0f;
	//*tmp3 = 15.0f;
	if(*(*goomba_addrii + 157) == 0
	 && *dist < (*tmp)) //is free to move
	{
	  //*dist += *tmp2;
	  //*tmp = (*dist + *tmp2); //dist = currdist
	  //*tmp = *tmp / (*tmp3);  //tmp3 = currdist / maxdist
	  *dist += *tmp2; //dist += 1 / (currdist/maxdist)
	}
	else if(*dist > (*tmp2)*(*tmp2))
	{
	  //*tmp = (*dist + *tmp2);
	  //*tmp = (*tmp) / (*tmp3);
	  //*dist -= *tmp2 / (*tmp);
	  *dist -= *tmp2;
	}
  
  
  //*tmp = 20.0;
  *tmp = 15.0;
  float marioy = *(player_addr + 44);
  float distancey = (*dist) * (*sin_addr);
  
  
  *tmp = 15.0;
  if(*player_dir_addr == 0x00003000)
  {
    *(*goomba_addr + 44) = marioy + distancey;
	*(*goomba_addr + 44) += *tmp;
	
	//*(*(goomba_addr+1) + 44) = marioy + *tmp;
	*tmp2 = 2.0;
	*(*(goomba_addr+2) + 44) = distancey;
	*(*(goomba_addr+2) + 44) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 44) += marioy + *tmp; //marioy+ distance/2 + tmp
  }
  else
  {
    *(*goomba_addr + 44) = marioy - distancey;
	*(*goomba_addr + 44) += *tmp;
	
	//*(*(goomba_addr+1) + 44) = marioy + *tmp;
	*tmp2 = -2.0;
	*(*(goomba_addr+2) + 44) = distancey;
	*(*(goomba_addr+2) + 44) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 44) += marioy + *tmp; //marioy+ distance/2 + tmp
  }
  
  
  float goombay = *(*goomba_addr + 44);
  float mariox = *(player_addr + 43);
  float distancex = (*dist) * (*cos_addr);
  //*tmp = 2.0;
  *tmp2 = 2.0;
  //check direction of mario!	
  if(*(player_dir_addr) == 0x00003000) //stands to the right
  {
	*(*goomba_addr + 43) = mariox + (*dist) * (*cos_addr);
	*(*goomba_addr + 43) += *tmp2;
	//*(*(goomba_addr+1) + 43) = mariox + *tmp;
	//*tmp2 = 2.0;
	*(*(goomba_addr+2) + 43) = distancex;
	*(*(goomba_addr+2) + 43) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 43) += mariox + *tmp2; //marioy+ distance/2 + tmp
	
  }
  else //stands to the left
  {
	*(*goomba_addr + 43) = mariox - (*dist) * (*cos_addr);
	*(*goomba_addr + 43) -= *tmp2;
	//*(*(goomba_addr+1) + 43) = mariox - *tmp;
	*tmp2 = -2.0;
	*(*(goomba_addr+2) + 43) = distancex;
	*(*(goomba_addr+2) + 43) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 43) += mariox + *tmp2; //marioy+ distance/2 + tmp
  }
   
  }
  
  if(*last_direction != *player_dir_addr)
  {
    *dist = 15.0;
  }
  
  *last_direction = *player_dir_addr;
  
  //increase timer
  //*tmpint = 1;
  //*portal_timer += *tmpint;
  *portal_timer += 1;
  
  
  //here we should teleport if teleporting_to is 1 or 2!
  if( (*teleporting_to == 1 || *teleporting_to == 2) && *first_portal != 0 && second_portal != 0)
  {
    //*(*teleporterf + 62) = 0.0; //gravity = 0
	
	int ** enter_portal;// = (int**)collider1_addr;
	int ** exit_portal;// = (int**)collider2_addr;
	
	float ** enter_portalf;
	float ** exit_portalf;
	
	double distx, disty;
    if(*teleporting_to == 1)
	{
	  enter_portal = second_portal;
	  exit_portal = first_portal;
	  
	  enter_portalf = second_portalf;
	  exit_portalf = first_portalf;
	  *tmp = -(*(*teleporterf + 43) - *(*first_portalf + 43));
	  
	  distx = *(*teleporterf + 43) - *(*first_portalf + 43);
	  disty = *(*teleporterf + 44) - *(*first_portalf + 44);
	  *tmp2 = fabs(distx*distx + disty*disty);
	  __asm__("frsqrte 0,0 stfs 0,8(30)");
	  
	  *tmp3 = (*tmp);
	  *tmp3 = (*tmp3)*(*tmp2);
	  *tmp2 = 8.0;
	  *tmp = (*tmp3);
	  *tmp = (*tmp)*(*tmp2);
	  *(*teleporterf + 43) += (*tmp);
	  
	  *tmp = -(*(*teleporterf + 44) - *(*first_portalf + 44));
	  distx = *(*teleporterf + 43) - *(*first_portalf + 43);
	  disty = *(*teleporterf + 44) - *(*first_portalf + 44);
	  *tmp2 = fabs(distx*distx + disty*disty);
	  __asm__("frsqrte 2,2 stfs 2,8(30)");
	  
	  *tmp3 = (*tmp);
	  *tmp3 = (*tmp3)*(*tmp2);
	  *tmp2 = 8.0;
	  *tmp = (*tmp3);
	  *tmp = (*tmp)*(*tmp2);
	  *(*teleporterf + 44) += *tmp;
	  
	}
	
	
	else // *teleporting_to == 2 here
	{
	  enter_portal = first_portal;
	  exit_portal = second_portal;
	  
	  enter_portalf = first_portalf;
	  exit_portalf = second_portalf;
	  *tmp = -(*(*teleporterf + 43) - *(*second_portalf + 43));
	  distx = *(*teleporterf + 43) - *(*second_portalf + 43);
	  disty = *(*teleporterf + 44) - *(*second_portalf + 44);
	  *tmp2 = fabs(distx*distx + disty*disty);
	  __asm__("frsqrte 0,0 stfs 0,8(30)");
	  //*tmp2 = fabs((*(*teleporterf + 43))*(*(*teleporterf + 43)) + (*(*second_portalf + 43))*(*(*second_portalf + 43)));
	  //*tmp2 = fabs((*(*teleporterf + 43)) + (*(*second_portalf + 43)));
	  *tmp3 = (*tmp);
	  *tmp3 = (*tmp3)*(*tmp2);
	  *tmp2 = 8.0;
	  *tmp = (*tmp3);
	  *tmp = (*tmp)*(*tmp2);
	  *(*teleporterf + 43) += (*tmp);
	  
	  *tmp = -(*(*teleporterf + 44) - *(*second_portalf + 44));
	  distx = *(*teleporterf + 43) - *(*second_portalf + 43);
	  disty = *(*teleporterf + 44) - *(*second_portalf + 44);
	  *tmp2 = fabs(distx*distx + disty*disty);
	  __asm__("frsqrte 2,2 stfs 2,8(30)");
	  //*tmp2 = fabs(distx*distx + disty*disty);
	  //*tmp2 = fabs((*(*teleporterf + 44)) + (*(*second_portalf + 44)));
	  *tmp3 = (*tmp);
	  *tmp3 = (*tmp3)*(*tmp2);
	  *tmp2 = 8.0;
	  *tmp = (*tmp3);
	  *tmp = (*tmp)*(*tmp2);
	  *(*teleporterf + 44) += *tmp;
	}
	
	*tmp3 = fabs(distx*distx + disty*disty);
	__asm__("nop");
	*tmpint = (*tmp3); //cast to int, can't compare otherwise, for some reason
	if(*tmpint < 30000)
	{
	  //probably safe to move the teleporter to the exit portal now?
	  *(*teleporterf + 44) = *(*exit_portalf + 44);
	  *(*teleporterf + 43) = *(*exit_portalf + 43);
	  *has_teleported = 1;
	  *(*teleporter + 227) = 0x01000000;
	}
	
	if(*has_teleported == 0)
	{
	  *(*teleporterf + 59) = 0.0; //y speed
	  *(*teleporterf + 67) = 0.0; //x speed
	  *(*teleporter + 227) = 1; //interactiveness, 1 = fall through it all
	}
	else // *has_teleported == 1
	{
	  *teleporting_to = 0;
	  
	  
	  //first take care of moving and minimum speed
    //TODO: MAX SPEED!
    
    //if exit portal is on the ground, move teleporter up
    //TODO: move to the side if possible!
    if(*(*exit_portal + 157) == 0x2000)
    {
      *tmp2 = 15.0;
      *tmp = *(*teleporterf + 44);
      *tmp += *tmp2;
      *(*teleporterf + 44) = *tmp;
    }
    
    //if exit portal is up, move teleporter down
    else if(*(*exit_portal + 157) >= 0x04000000)
    {
      *tmp2 = -15.0;
      *tmp = *(*teleporterf + 44);
      *tmp += *tmp2;
      *(*teleporterf + 44) = *tmp;
    }
    
    //if exit portal is to the left, move teleporter right
    else if(*(*exit_portal + 157) == 0x28)
    {
      *tmp2 = 15.0;
      *tmp = *(*teleporterf + 43);
      *tmp += *tmp2;
      *(*teleporterf + 43) = *tmp;
    }
  
    //if exit portal is to the right, move teleporter left
    else if(*(*exit_portal + 157) == 0x14)
    {
      *tmp2 = -15.0;
      *tmp = *(*teleporterf + 43);
      *tmp += *tmp2;
      *(*teleporterf + 43) = *tmp;
    }
	
	//check orientation of portals
    //_  _ flip y speed	
    if((*(*first_portal + 157) & 0x0000f000) != 0 && (*(*second_portal + 157) & 0x0000f000) != 0)
    {
	  *tmp = -3.0;
	  *tmp3 = 5.0;
	  *tmp2 = *(*teleporterf + 59);
	  if(*tmp2 > *tmp)
      {
        
		*(*teleporterf + 59) = *tmp3; //flip y
      }
	  else
	  {
	    *tmp3 = -1.0;
	    *(*teleporterf + 59) *= *tmp3; //flip y
	  }
	  
	  //give a little x speed so he won't fall down the portal again!	  
	  *tmp = 1.0;
      *(*teleporterf + 67) = *tmp;
    }
	
	//^ ^, flip y speed
	if( (*(*first_portal + 157) >= 0x04000000 && *(*second_portal + 157) >= 0x04000000))
	{
	    *tmp = -1.0;
	    *(*teleporterf + 59) *= *tmp; //flip y
	}
	
    //_|  _| OR |_ |_ flip x speed
    if( (*(*enter_portal + 157) == 0x28 && *(*exit_portal + 157) == 0x28)
    || (*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) == 0x14))
    {
      *tmp = -1.0;
      *(*teleporterf + 67) *= *tmp; //flip x
    }
    
    //enter to right, exit from up 
    //yspeed = xspeed
    //xspeed = 0
    if(*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) >= 0x04000000)
    {
      *tmp = *(*teleporterf + 67); // *tmp = xspeed
      *(*teleporterf + 59) *= *tmp; //yspeed = xspeed
      
      *tmp = 0;
      *(*teleporterf + 67) = *tmp;
      *(*teleporterf + 58) = *tmp;
      
    }
	
	//enter to right, exit from down
	//yspeed = xspeed
    //xspeed = 1 for mario
	//xspeed = yspeed for others
	
	if(*(*enter_portal + 157) == 0x14 && (*(*exit_portal + 157) & 0x0000f000) != 0)
	{
	  int ** teleporteri = (int**)teleporter;
	  *tmp = 3.0;
	  *tmp2 = *(*teleporterf + 67);
	  *tmp3 = 5.0;
	  if(*(*teleporteri + 2) == 0x000d0100) //IF MARIO or other player
	  {
	    if(*tmp2 < *tmp) //if xspeed < 3
	    {
	      
		  *(*teleporterf + 59) = *tmp3;
        }
	    else
	    {
	      *tmp = *(*teleporterf + 67); // *tmp = xspeed
          *(*teleporterf + 59) *= *tmp; //yspeed = xspeed
	    }
	  
	    //give a little x speed so he won't fall down the portal again!	  
	    *tmp = 1.0;
        *(*teleporterf + 67) = *tmp;
	  }
	  else //NOT a player, it's an enemy or similar!
	  {
	    *tmp = *(*teleporterf + 58); // *tmp = xspeed
		*(*teleporterf + 58) = *(*teleporterf + 59); //xspeed = yspeed
        *(*teleporterf + 59) = *tmp; //yspeed = xspeed 
	  }
	  
	}
	
    
    //enter to up, exit from left
    //xspeed = yspeed
    //yspeed = 0
    if(*(*enter_portal + 157) >= 0x04000000 && *(*exit_portal + 157) == 0x28)
    {
      *tmp2 = 1.0;
      *tmp = *(*teleporterf + 59); // *tmp = yspeed
      
      //check if |yspeed| > 1.0
      if(*tmp > *tmp2)
      {
        //*tmp2 = 1.0;
        *(*teleporterf + 67) = *tmp2; //xspeed = 1.0
        *(*teleporterf + 58) = *tmp2; //xspeed = 1.0
      }
      else
      {
        *(*teleporterf + 67) = *tmp; //xspeed = yspeed
        *(*teleporterf + 58) = *tmp; //xspeed = yspeed
      }
	  *tmp = 0;
	  *(*teleporterf + 59) = *tmp; //yspeed = 0
    }
	
	//enter to up, exit from right OR enter to down, exit from left
    //xspeed = -yspeed
    if((*(*enter_portal + 157) >= 0x04000000 && *(*exit_portal + 157) == 0x14)
    || ( (*(*enter_portal + 157) & 0x0000f000) != 0 && *(*exit_portal + 157) == 0x28))
    {
      *tmp2 = -1.0;
      *tmp = *(*teleporterf + 59) * (*tmp2); // *tmp = -yspeed
      
	  //check if |yspeed| > 1.0
      if(*tmp > fabs(*tmp2))
      {
        *(*teleporterf + 67) = fabs(*tmp2); //xspeed = 1.0
      }
      *(*teleporterf + 67) = *tmp; //xspeed = -yspeed
    }
    
    //enter to right, exit from up
    //yspeed = -xspeed
	//xspeed = 0
    if(*(*enter_portal + 157) == 0x14 && *(*exit_portal + 157) >= 0x04000000)
    {
      *tmp2 = -1.0;
      *tmp = *(*teleporterf + 67); // *tmp = yspeed
      *(*teleporterf + 59) = *tmp * (*tmp2); //yspeed = -xspeed
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
	  *tmp2 = *(*teleporterf + 67);
	  
	  if(*tmp2 > *tmp) //if |xspeed| < 3
	  {
	    *tmp2 = 5.0;
		*(*teleporterf + 59) = *tmp2;
		
      }
	  else
	  {
	  
	    *tmp2 = -1.0;
        *tmp = *(*teleporterf + 67); // *tmp = xspeed
        *(*teleporterf + 59) = *tmp * (*tmp2); //yspeed = -xspeed
	  }
	  
	  //give a little x speed so he won't fall down the portal again!
	  *tmp = -1.0;
      *(*teleporterf + 67) = *tmp;
	  
	  }
	  else //not mario or other player!
	  {
	    *tmp2 = -1.0;
        *tmp = *(*teleporterf + 58); // *tmp = xspeed
		*(*teleporterf + 58) = *(*teleporterf + 59); //xspeed = yspeed
		*(*teleporterf + 58) *= *tmp2;	//xspeed = -yspeed
        *(*teleporterf + 59) = *tmp * (*tmp2); //yspeed = -xspeed
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
	    *tmp = *(*teleporterf + 59);
		*tmp /= *tmp2;	//*tmp = yspeed/2
		*(*teleporterf + 59) = 0;
		*(*teleporterf + 67) = *tmp;
	    
	  }
	  else //if enemy or similar!
	  {
	    //*tmp = -.6;
		//*tmp2 = *(*teleporterf + 59);
		*(*teleporterf + 59) = *(*teleporterf + 58); //yspeed = xspeed
	  }
	  
	  *tmp2 = -fabs(*(*teleporterf + 58));
		
      //flip x!
	  *(*teleporterf + 58) = *tmp2;
	  
	}
	
	
	
	
	
	}
	
	//*teleporting_to = 0;
	//*has_teleported
  }
  
  
  
  //store button presses as a 1 if the button is held down, and its
  //value is already zero, so as to shoot just one portal at a time.
  //0x02000000 on the wii, 0x06000000 in dolphin!
  if(((*button_presses & 0x06000000) == 0x06000000)
  //  || (*button_presses & 0x02020000) == 0x02020000)
  && *button_store == 0 && (*player_free_addr & 0x000000ff) == 0)
  {
    *created_actor = (*CreateActor)(0x38, 0x1000, (player_addr+43), 0, 0);
    *button_store = 1;
	
	//tag the newly created beetle as being shot from the portal gun!
	//seems to be overwritten anyway, scrap this?
	//if(*created_actor != 0)
	//{
	//  *(*created_actor + 193) = 0x00000001;
	//}
  }
    
  //clear *button_store if button 1 is released
  if((*button_presses & 0x02000000) == 0)
    *button_store = 0;
  
  //if(*curr_portal == *tmpint) //place first portal
  //{
  //int ** first_portal = (int**)(base_addr);
	
	//*tmpint = 0x00380100;

	
	//null pointer check!!
	if(*first_portal_addr < 0x81500000)
	  return 0;
	  
    *tmp = 7.0;
	*tmp2 = 0.1;
	
    if( *(*first_portal+2) == 0x00380100) //it's a living buzzy beetle
	  {
      if(*(*first_portal+157) == 0) //and we can move it!
      {
	    //*tmp2 = 0.25;
	    //scale in x dir
	    *(*first_portalf + 57) = (*tmp2);
		*(*first_portalf + 56) = (*tmp2);
		
		*(*first_portal + 64) += 0x05000500;
	    //*tmp = 7.0;
        *(*first_portalf + 58) = (*tmp) * (*static_cos_addr);
        *(*first_portalf + 59) = (*tmp) * (*static_sin_addr);
      }
        
        //TODO: check if it landed on a legal place!
        else if(*(*first_portal+157+8) == 2 || //hangs under
        (*(*first_portal+157+2) == 8) ||  //ground
        (*(*first_portal+157+10) == 2) || //right
        (*(*first_portal+157+11) == 2)) //left, ILLEGAL PLACE?
        {
          *(*first_portal + 73) = 0; //make invisible
          *first_portal_addr = 0;
		  *curr_portal = 2;
          return 0;
        }
        
        else 
        {
		  *tmp = 1.0;
		  *tmp2 = 0.0;
		  *(*first_portalf + 56) = *tmp; //yscale = 1
		  *(*first_portalf + 57) = *tmp; //xscale = 1
          *(*first_portalf + 62) = *tmp2; //gravity = 0
          *(*first_portalf + 58) = *tmp2; //hastx = 0
          *(*first_portalf + 59) = *tmp2; //hasty = 0
        }
        
      
      //gone?
	  }
	  else if( *(*first_portal+2) == 0x00380200)
    {
      *first_portal_addr = 0;
	  *curr_portal = 2;
      //return 0;
    }
  
  //rotate correctly!
  
  //*tmpint = 0x04000000;
  if(*(*first_portal + 157) >= 0x04000000)
    *(*first_portal + 64) = 0x80008000;
    
  //side left
  //*tmpint = 0x28;
  else if(*(*first_portal + 157) == 0x28)
    *(*first_portal + 64) = 0xC000C000;
    
  //side right
  //*tmpint = 0x14;
  else if(*(*first_portal + 157) == 0x14)
    *(*first_portal + 64) = 0x4000C000;

  //ground
  else if((*(*first_portal + 157) & 0x0000f000) != 0)
    *(*first_portal + 64) = 0;

  //null pointer
  if(*second_portal_addr < 0x81500000)
	  return 0;
    
	*tmp = 7.0;
	*tmp2 = 0.1;
	if( *(*second_portal+2) == 0x00380100)  
	  {
      if(*(*second_portal+157) == 0) //can move
      {
	    //*tmp2 = 0.25;
	    //scale in x dir
	    *(*second_portalf + 57) = (*tmp2);
		*(*second_portalf + 56) = (*tmp2);
	    //*tmp = 7.0;
		*(*second_portal + 64) += 0x05000500;
		
        *(*second_portalf + 58) = (*tmp) * (*static_cos_addr);
        *(*second_portalf + 59) = (*tmp) * (*static_sin_addr);
      }
      
      //check illegalcheck.txt for info
      
      else if(*(*second_portal+157+8) == 2 || //hangs under
        ((*(*second_portal+157+2) == 8) || //ground
        (*(*second_portal+157+10) == 2)) ) //right
        //(*(*second_portal+157+11) == 2)) //left, ILLEGAL PLACE?
      {
        //make portal invisible!
        *(*second_portal + 73) = 0;
        *second_portal_addr = 0;
		*curr_portal = 1;
        return 0;
      }
      
      else 
      {
	    *tmp = 1.0;
		*tmp2 = 0.0;
		*(*second_portalf + 56) = *tmp; //yscale = 1
	    *(*second_portalf + 57) = *tmp; //xscale = 1
        *(*second_portalf + 62) = *tmp2; //gravity = 0
        *(*second_portalf + 58) = *tmp2; //hastx = 0
        *(*second_portalf + 59) = *tmp2; //hasty = 0
      }
      
	  }
	//gone?
    //if( *(*second_portal+4) == 0)
	else if( *(*second_portal+2) == 0x00380200) 
    {
      *second_portal_addr = 0;
	  *curr_portal = 1;
      //return 0;
    }
  
  //rotate it correctly!
  //up
  if(*(*second_portal + 157) >= 0x04000000)
    *(*second_portal + 64) = 0x80008000;
    
  //side left
  else if(*(*second_portal + 157) == 0x28)
    *(*second_portal + 64) = 0xC000C000;
    
  //side right
  else if(*(*second_portal + 157) == 0x14)
    *(*second_portal + 64) = 0x4000C000;
	
  //ground
  else if((*(*second_portal + 157) & 0x0000f000) != 0)
    *(*second_portal + 64) = 0;
  
  return 0;
}
