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
  float * player_addr = (float*)0x8154b804;

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
	float cosx = (*angle)*(*angle)*(*angle);
	*tmp = 12.0;
	cosx = cosx/(*tmp);
	*tmp = 1.0;
	cosx = *tmp + cosx; //cosx = 1+a^3/12;
	*tmp = 2.0;
	cosx = cosx - (*angle)*(*angle)/(*tmp); //finito
    
	//SINE
	*tmp = 7.0;
	*tmp2 = 1.0;
	float sinx = (*angle)* (*tmp2 - (*angle)*(*angle)/(*tmp));
	
	*tmp = 20.0;
    float mariox = *(player_addr + 43);
	*tmp2 = mariox + (*tmp) * cosx;
	
	*(*goomba_addr + 43) = *tmp2;
	float marioy = *(player_addr + 44);
	*tmp2 = marioy + (*tmp) * sinx;
	*(*goomba_addr + 44) = *tmp2;
  }
}

