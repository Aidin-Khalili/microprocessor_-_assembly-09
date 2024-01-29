#include "LPC17xx.h"
//For Pclk_Timer0we have : 100M / 4 = 25 MHz
void TIMER2_IRQHandler() 
{  
  LPC_TIM2->IR=1;			//To clear flag
	LPC_GPIO0->FIOPIN++;
	if (LPC_TIM2->CTCR==1) //To change counter input
		LPC_TIM2->CTCR=5;
	else 
		LPC_TIM2->CTCR=1;
}

void  init_timer2( )		 
{
	LPC_SC->PCONP|=(1<<22);
	LPC_PINCON->PINSEL0|=(0x3<<10)|(0x3<<8);
	LPC_TIM2->PR=0;							//To set prescaler to zero 
	LPC_TIM2->MR0=9;						//Timer interval
	LPC_TIM2->MCR=3;				    //to have interrupt & reset on MR0
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->CTCR=1;						//To Counte as rising edge on cap2.0
}

int main()
{	    		
  LPC_GPIO0->FIODIR=0xFFFFFFFF;		
  init_timer2( ); 
	LPC_TIM2->TCR=1;
  while(1){}
}