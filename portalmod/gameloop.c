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
  
  int * curr_portal = (int*)(base_addr+2);
  //float * player_addr = (float*)0x8154b804;
  float * player_addr;
  //int * player_addri;
  
  int * player_store_addr = (int*)(base_addr+11);
  int * get_player_timer = (int*)(base_addr+16);
  
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
  if(*player_store_addr == 0)
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
  
  *tmpint = 1;
  *timer += *tmpint;
  
  *tmp2 = 1.7;
  float ** wiimoteptr = (float **)(0x80377F88);
  
  //choose id 0
  float * tilt_addr = (float *)((*wiimoteptr+0) + 11);
  //float * tilt_addr = (float*)0x807612c8;
  
  float * angle = (float*)(base_addr+24);
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
  
  
  if( *goomba_addri != 0 && *(goomba_addri+1) != 0 &&  *(goomba_addri+2) != 0) //null pointer check
  {
    //make crosshairs visible when B is held down, invisible otherwise!
    if(((*button_presses & 0x04000000) == 0x04000000))
	{
      *(*goomba_addrii + 73) = 0x01000000;
	  *(*(goomba_addrii+1) + 73) = 0x01000000;
	  *(*(goomba_addrii+2) + 73) = 0x01000000;
	}
	else
	{
	  *(*goomba_addrii + 73) = 0;
	  *(*(goomba_addrii+1) + 73) = 0;
	  *(*(goomba_addrii+2) + 73) = 0;
	  *dist = 0.1;
	}
  
    //move crosshairs outwards!
	*tmp = 200.0f;
	*tmp2 = 4.0f;
	*tmp3 = 200.0f;
	if(*(*goomba_addrii + 157) == 0
	 && *dist < (*tmp)) //is free to move
	{
	  //*dist += *tmp2;
	  //*tmp = (*dist + *tmp2); //dist = currdist
	  //*tmp = *tmp / (*tmp3);  //tmp3 = currdist / maxdist
	  *dist += *tmp2; //dist += 1 / (currdist/maxdist)
	}
	else
	{
	  //*tmp = (*dist + *tmp2);
	  //*tmp = (*tmp) / (*tmp3);
	  //*dist -= *tmp2 / (*tmp);
	  *dist -= *tmp2;
	}
  
  
  *tmp = 20.0;
  *tmp = 15.0;
  float marioy = *(player_addr + 44);
  float distancey = (*dist) * (*sin_addr);
  
  if(*player_dir_addr == 0x00003000)
  {
    *(*goomba_addr + 44) = marioy + distancey;
	*(*goomba_addr + 44) += *tmp;
	
	*(*(goomba_addr+1) + 44) = marioy + *tmp;
	*tmp2 = 2.0;
	*(*(goomba_addr+2) + 44) = distancey;
	*(*(goomba_addr+2) + 44) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 44) += marioy + *tmp; //marioy+ distance/2 + tmp
  }
  else
  {
    *(*goomba_addr + 44) = marioy - distancey;
	*(*goomba_addr + 44) += *tmp;
	
	*(*(goomba_addr+1) + 44) = marioy + *tmp;
	*tmp2 = -2.0;
	*(*(goomba_addr+2) + 44) = distancey;
	*(*(goomba_addr+2) + 44) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 44) += marioy + *tmp; //marioy+ distance/2 + tmp
  }
  
   //= *tmp2; //store sin etc
  //*tmp3 = marioy + *tmp;
  //*(*(goomba_addr+1) + 44) = *tmp3;
  //*tmp = 15.0;
  //*tmp2 = *(*goomba_addr + 44);
  //*(*goomba_addr + 44) = *tmp2 + *tmp;
  
  float goombay = *(*goomba_addr + 44);
  float mariox = *(player_addr + 43);
  float distancex = (*dist) * (*cos_addr);
  
  //check direction of mario!	
  if(*(player_dir_addr) == 0x00003000) //stands to the right
  {
	*(*goomba_addr + 43) = mariox + (*dist) * (*cos_addr) + *tmp;
	*(*(goomba_addr+1) + 43) = mariox + *tmp;
	*tmp2 = 2.0;
	*(*(goomba_addr+2) + 43) = distancex;
	*(*(goomba_addr+2) + 43) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 43) += mariox + *tmp; //marioy+ distance/2 + tmp
	
  }
  else
  {
	*(*goomba_addr + 43) = mariox - (*dist) * (*cos_addr) - *tmp;
	*(*(goomba_addr+1) + 43) = mariox - *tmp;
	*tmp2 = -2.0;
	*(*(goomba_addr+2) + 43) = distancex;
	*(*(goomba_addr+2) + 43) /= *tmp2; //distance/2
	*(*(goomba_addr+2) + 43) += mariox - *tmp; //marioy+ distance/2 + tmp
  }
   
  }
  
  if(*last_direction != *player_dir_addr)
  {
    *dist = 0.1;
  }
  
  *last_direction = *player_dir_addr;
  
  //increase timer
  *tmpint = 1;
  *portal_timer += *tmpint;
  
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
	float ** first_portalf = (float**)(base_addr);
	float ** second_portalf = (float**)(base_addr+1);
	*tmpint = 0x00380100;

	
	//null pointer check!!
	if(*first_portal_addr == 0)
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
	  }else if( *(*first_portal+4) == 0)
    {
      *first_portal_addr = 0;
	  *curr_portal = 2;
      return 0;
    }
  
  
  //*tmpint = 0x04000000;
  if(*(*first_portal + 157) >= 0x04000000)
    *(*first_portal + 64) = 0x80008000;
    
  //side left
  //*tmpint = 0x28;
  if(*(*first_portal + 157) == 0x28)
    *(*first_portal + 64) = 0xC000C000;
    
  //side right
  //*tmpint = 0x14;
  if(*(*first_portal + 157) == 0x14)
    *(*first_portal + 64) = 0x4000C000;
  
  
  //null pointer
  if(*second_portal_addr == 0)
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
    if( *(*second_portal+4) == 0)
    {
      *second_portal_addr = 0;
	  *curr_portal = 1;
      return 0;
    }
  
  //rotate it correctly!
  //up
  if(*(*second_portal + 157) >= 0x04000000)
    *(*second_portal + 64) = 0x80008000;
    
  //side left
  if(*(*second_portal + 157) == 0x28)
    *(*second_portal + 64) = 0xC000C000;
    
  //side right
  if(*(*second_portal + 157) == 0x14)
    *(*second_portal + 64) = 0x4000C000;
  
  return 0;
}
