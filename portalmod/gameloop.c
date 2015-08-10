//int main(int argc, char *argv[])
//#include<stdio.h>

typedef unsigned short u16;

//active wiimote = 8042A748


int main(void)
{
  //create actor
  int (*CreateActor)(u16 classID, int settings, float * pos, char rot, char layer) = 0x80064610;
  int (*get_player)(int ID) = 0x8005FB90;
  
  float *base_addr;// = (float*)0x802f6940;
  base_addr = (float*)0x802f6900;
  float ** goomba_addr = (float**)0x802f6930;
  int * goomba_addri = (int*)0x802f6930;
  
  int * button_store = (int*)(base_addr+4);
  
  int * tmpint = (int*)(base_addr+6);
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
  
  //get pointer to player number 0, always mario?
  *player_store_addr = get_player(0);
  
  //*player_store_addr = 0x8154b804;
  
  //NULL pointer!
  if(*player_store_addr == 0)
    return 0;
  
  player_addr = *player_store_addr;
  
  //*player_store_addr = player_addr;
  
  //if((int*)player_addr == 0)
  //  return 0;
  
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
  float ** wiimoteptr = (float **)0x80377F88;
  
  //choose id 0
  float * tilt_addr = (float *)((*wiimoteptr+0) + 11);
  //float * tilt_addr = (float*)0x807612c8;
  
  float * angle = (float*)(base_addr+24);
  //*(base_addr+5) = 1.571;	//pi/2
  *tmp = *tmp2;	//pi/2 + x
  
  *angle = (*tilt_addr);	//pi/2
  *angle *= *tmp;
  
  //float * goomba = &goomba_addr;
  //float *tmp = base_addr+5;
  
  // *tmpint = 0;
  
  if( *goomba_addri == 0) //null pointer check
    return 0;
	//COSINE!
	//float cosx = fabs((*angle)*(*angle)*(*angle));
  
	//*tmp = 12.0f;
	//cosx = cosx/(*tmp);
	//*tmp = 1.0f;
	//cosx = *tmp + cosx; //cosx = 1+a^3/12;
	//*tmp = 2.0f;
	//cosx = cosx - (*angle)*(*angle)/(*tmp); //finito, 1+a^3/12-a^2/2
	
	//*cos_addr = cosx;
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
  
  
  

	
  if(*last_direction != *player_dir_addr)
  {
    *dist = 0;
  }
  
  *last_direction = *player_dir_addr;
  
	//move crosshairs outwards!
	*tmp = 100.0f;
	*tmp2 = 6.0f;
	*tmp3 = 100.0f;
	if(*(goomba_addri + 157) == 0
	 && *dist < (*tmp)) //is free to move
	{
	  *dist += *tmp2;
	}
	else
	  *dist -= *tmp2;
    
    
	//SINE
	*tmp = 7.0;
	*tmp2 = 1.0;
	//float sinx = (*angle)* (*tmp2 - (*angle)*(*angle)/(*tmp));
  *sin_addr =  (*angle)*(*angle)/(*tmp);
  *tmp = *sin_addr; //*tmp = a^2/7
  *sin_addr = *tmp2 - *tmp; //1 - a^2/7
  *tmp = *sin_addr;
  *sin_addr = *tmp * (*angle);
  
	//*sin_addr = sinx;
	
	*tmp = 20.0;
	float marioy = *(player_addr + 44);
  
  if(*player_dir_addr == 0x00003000)
    *tmp2 = marioy + (*dist) * (*sin_addr);
  else
    *tmp2 = marioy - (*dist) * (*sin_addr);
  
	*(*goomba_addr + 44) = *tmp2; //store sin etc
	*tmp = 15.0;
  *tmp2 = *(*goomba_addr + 44);
	*(*goomba_addr + 44) = *tmp2 + *tmp;
	float goombay = *(*goomba_addr + 44);
  
	//check direction of mario!
	//float dir = *(player_addr + 64);
	//*tmpint = 0x0000d000;
	//*tmpint = (int)*(player_addr + 64);
	//*tmpint = (int)*(0x8154b904);
	//*tmp = 20.0;
    float mariox = *(player_addr + 43);
	
	if(*(player_dir_addr) == 0x00003000) //stands to the right
  {
	  *tmp2 = mariox + (*dist) * (*cos_addr) + *tmp;
  }
	else
  {
	  *tmp2 = mariox - (*dist) * (*cos_addr) - *tmp;
  }
   
	*(*goomba_addr + 43) = *tmp2;
	float * goombax = (*goomba_addr + 43);
	
  //increase timer
  *tmpint = 1;
  *portal_timer += *tmpint;
  
  //store button presses as a 1 if the button is held down, and its
  //value is already zero, so as to shoot just one portal at a time.
  //0x02000000 on the wii, 0x06000000 in dolphin!
  if(((*button_presses & 0x06000000) == 0x06000000 || (*button_presses & 0x02000000) == 0x02000000)
  && *button_store == 0)
  {
    /*
    *tmp = 6.0;
    *tmp2 = *(player_addr+44);
    
    //move mario 6 units up
    *(player_addr+44) = *tmp + *tmp2;
    
    *tmp = 10.0;
    *tmp2 = *(player_addr+43);
    *(player_addr+43) = *tmp + *tmp2;
    */
    (*CreateActor)(0x85, 0x1000, (player_addr+43), 0, 0);
    
    /*
    *tmp = 10.0;
    //move him back
    *(player_addr+43) = *tmp2 - *tmp;
    
    *tmp = 6.0;
    *tmp2 = *(player_addr+44);
    *(player_addr+44) = *tmp2 - *tmp;
    */
    *button_store = 1;
  }
    
  //clear *button_store if button is released
  if(*button_presses == 0)
    *button_store = 0;
  
  //if(*curr_portal == *tmpint) //place first portal
  //{
    //int ** first_portal = (int**)(base_addr);
	float ** first_portalf = (float**)(base_addr);
	float ** second_portalf = (float**)(base_addr+1);
	*tmpint = 0x00850100;

	*tmp = 7.0;
	*tmp2 = 0.0;
	
	//null pointer check!!
	if(*first_portal_addr == 0)
	  return 0;
  
    if( *(*first_portal+2) == 0x00850100) //it's a bobomb
	  {
      if(*(*first_portal+157) == 0) //and we can move it!
      {
        *(*first_portalf + 58) = (*tmp) * (*static_cos_addr);
        *(*first_portalf + 59) = (*tmp) * (*static_sin_addr);
      }else{ //can't move it, freeze it!
        *(*first_portalf + 62) = *tmp2; //gravity = 0
        *(*first_portalf + 58) = *tmp2; //hastx = 0
        *(*first_portalf + 59) = *tmp2; //hasty = 0
      }
	  }else if( *(*first_portal+4) == 0)
    {
      *first_portal_addr = 0;
      return 0;
    }
  
  
  //null pointer
  if(*second_portal_addr == 0)
	  return 0;
    
	if( *(*second_portal+2) == 0x00850100)  
	  {
      if(*(*second_portal+157) == 0) //can move
      {
        *(*second_portalf + 58) = (*tmp) * (*static_cos_addr);
        *(*second_portalf + 59) = (*tmp) * (*static_sin_addr);
      }
      else{
        *(*second_portalf + 62) = *tmp2; //gravity = 0
        *(*second_portalf + 58) = *tmp2; //hastx = 0
        *(*second_portalf + 59) = *tmp2; //hasty = 0
      }
	  }
    else if( *(*second_portal+4) == 0)
    {
      *second_portal_addr = 0;
      return 0;
    }
  
  //rotate it correctly!
  //up
  *tmpint = 0x04000000;
  if(*(*first_portal + 157) >= *tmpint)
    *(*first_portal + 64) = 0x80008000;
    
  if(*(*second_portal + 157) >= *tmpint)
    *(*second_portal + 64) = 0x80008000;
    
  //side left
  *tmpint = 0x28;
  if(*(*first_portal + 157) == *tmpint)
    *(*first_portal + 64) = 0xC000C000;
  
  if(*(*second_portal + 157) == *tmpint)
    *(*second_portal + 64) = 0xC000C000;
    
  //side right
  *tmpint = 0x14;
  if(*(*first_portal + 157) == *tmpint)
    *(*first_portal + 64) = 0x4000C000;
    
  if(*(*second_portal + 157) == *tmpint)
    *(*second_portal + 64) = 0x4000C000;
  
  return 0;
}

