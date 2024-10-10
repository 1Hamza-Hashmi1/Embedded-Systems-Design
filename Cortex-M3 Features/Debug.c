#include "LPC17xx.h"
#include "LED.h"

#define __FI    	1                  	/* Font index 16x24           	*/

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)	(*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

//Alias addresses for specific LEDs found using bitband formulas
#define GPIO1_LED31 (*((volatile unsigned long*)0x233806FC))       	//FIO1PIN - 0x2009C034, pin 31
#define GPIO2_LED2 (*((volatile unsigned long *)0x23380A88))        	//FIO2PIN - 0x2009C054, pin 2

//delay function
int wait_loop0 = 10000;
int wait_loop1 = 1500;
// using nested loops to add a delay in the program
void delay(int seconds)
{
	int i, j, k;
	for(i = 0; i < seconds; i++)
	{
    	for(j = 0; j < wait_loop0; j++)
    	{
        	for(k = 0; k < wait_loop1; k++)
        	{
            	int volatile t = 120 * j * i + k;
            	t = t + 5;
        	}
    	}
	}
}

int main(void){
	int r1 = 1, r2 = 1, r3 = 2;
	volatile unsigned long * GPIO1_LED28 ; //used for the function mode
	volatile unsigned long * GPIO2_LED4 ;
    
	LED_Init();
	//delay(1);
	while(1){
        	if(r1-r2 < r3){  	//s suffix is used here for conditional execution
      	//mask mode
        	LPC_GPIO1->FIOPIN |=  ( 1 << 29);  //setting LEDs by masking bits
        	LPC_GPIO2->FIOPIN |=  ( 1 << 3);
        	LPC_GPIO2->FIOPIN &=  ~( 1 << 3);  //turning off the mask mode LEDs
        	LPC_GPIO1->FIOPIN &=  ~( 1 << 29);
        	r1+=2;
	}
    	else if(r1 == 3){
        	//function mode
        	*GPIO2_LED4 = 1;                                     	//setting LEDS using bitband function
        	*GPIO1_LED28 = 1;
        	*GPIO2_LED4 = 0;                                  	//turning off the function mode LEDs
        	*GPIO1_LED28 = 0;
        	r1 = r2 + (r3*4); 		//barrel shifter is used here
    	}else {
        	//bitband mode
        	GPIO2_LED2 = 1;                                 	//setting LEDs using bitbanding
        	GPIO1_LED31 = 1;
        	GPIO2_LED2 = 0;                                  	//turning off the bitband mode LEDs
        	GPIO1_LED31 = 0;
        	r1 = 1;
    	}
	}
}
