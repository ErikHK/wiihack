//int main(int argc, char *argv[])
//#include<stdio.h>


int main(void)
{
  float *base_addr;// = (float*)0x802f6940;
  base_addr = (float*)0x802f6900;
  float ** goomba_addr = (float**)0x802f6930;
  int * tmpint = (int*)(base_addr+6);
  float * tmp = (float*)(base_addr+5);
  float * tmp2 = (float*)(base_addr+7);
  float * tmp3 = (float*)(base_addr+9);
  int * portal_timer = (int*)(base_addr+8);
  int ** first_portal = (int**)(base_addr);
  int ** second_portal = (int**)(base_addr+1);
  int * curr_portal = (int*)(base_addr+2);
  float * player_addr = (float*)0x8154b804;
  int * player_dir_addr = (int*)0x8154b904;
  float * dist = (float*)(base_addr+10);
  
  float * sin_addr = (float*)(base_addr+28);
  float * cos_addr = (float*)(base_addr+29);
  
  float * static_sin_addr = (float*)(base_addr+32);
  float * static_cos_addr = (float*)(base_addr+33);
  
  //int * goomba = *goomba_addr;
  
  
  float * tilt_addr = (float*)0x807612c8;
  *(base_addr+5) = 1.57;	//pi/2
  float * angle = (base_addr+24);
  *angle = *(base_addr+5)*(*tilt_addr);	//pi/2
  //float * goomba = &goomba_addr;
  //float *tmp = base_addr+5;
  
  //*tmp = 0;
  
  if( **goomba_addr != *tmp)
  {
	//COSINE!
	float cosx = fabs((*angle)*(*angle)*(*angle));
	*tmp = 12.0;
	cosx = cosx/(*tmp);
	*tmp = 1.0;
	cosx = *tmp + cosx; //cosx = 1+a^3/12;
	*tmp = 2.0;
	cosx = cosx - (*angle)*(*angle)/(*tmp); //finito
	
	*cos_addr = cosx;
	
	//move it outwards!
	*tmp = 0.0;
	*tmp2 = 2.0;
	*tmp3 = 100.0;
	if(*(*goomba_addr + 157) == *tmp
	 && *dist < (*tmp3)) //is free to move
	{
	  *dist += *tmp2;
	}
	else
	  *dist -= *tmp2;
    
	//SINE
	*tmp = 7.0;
	*tmp2 = 1.0;
	float sinx = (*angle)* (*tmp2 - (*angle)*(*angle)/(*tmp));
	*sin_addr = sinx;
	
	*tmp = 20.0;
	float marioy = *(player_addr + 44);
	*tmp2 = marioy + (*dist) * sinx;
	*(*goomba_addr + 44) = *tmp2;
	*tmp = 15.0;
	*(*goomba_addr + 44) = *(*goomba_addr + 44) + *tmp;
	float goombay = *(*goomba_addr + 44);

	//check direction of mario!
	//float dir = *(player_addr + 64);
	//*tmpint = 0x0000d000;
	//*tmpint = (int)*(player_addr + 64);
	//*tmpint = (int)*(0x8154b904);
	*tmpint = *(player_dir_addr);
	*tmp = 20.0;
    float mariox = *(player_addr + 43);
	
	if(*tmpint == 0x00003000) //stands to the right
	  *tmp2 = mariox + (*dist) * cosx;
	else
	  *tmp2 = mariox - (*dist) * cosx;
	
	  
	*(*goomba_addr + 43) = *tmp2;
	float * goombax = (*goomba_addr + 43);
	
  }
  
  //increase timer
  *tmpint = 1;
  *portal_timer += *tmpint;
  
  *tmpint = 2;
  
  
  //if(*curr_portal == *tmpint) //place first portal
  //{
    //int ** first_portal = (int**)(base_addr);
	float ** first_portalf = (float**)(base_addr);
	float ** second_portalf = (float**)(base_addr+1);
	*tmpint = 0x00850100;

	*tmp = 7.0;
	*tmp2 = 0.0;
	
	//null pointer check here!!
	//if(first_portal == NULL)
	//  return 0;
	
    if( *(*first_portal+2) == *tmpint) //it's a bobomb
	  {
	  if(*(*first_portalf+157) == *tmp2) //and we can move it!
	  {
		*(*first_portalf + 58) = (*tmp) * (*static_cos_addr);
	    *(*first_portalf + 59) = (*tmp) * (*static_sin_addr);
	  }else{ //can't move it, freeze it!
	    *(*first_portalf + 62) = *tmp2; //gravity = 0
		*(*first_portalf + 58) = *tmp2; //hastx = 0
		*(*first_portalf + 59) = *tmp2; //hasty = 0
	  }
	  
	  
	  }
	
	if( *(*second_portal+2) == *tmpint)  
	  {
	  if(*(*second_portalf+157) == *tmp2) //can move
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
	  
  //}
  
  
}

