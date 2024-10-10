//conditional execution code example
#include "LPC17xx.h"
#include "GLCD.h"
#include "LED.h"

#define __FI    	1                  	/* Font index 16x24           	*/

// Bit Band - used to calculate the alias address
#define ADDRESS(x)	(*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

//Alias addresses - found Ssing bitband formulas for specific LEDs
#define GPIO1_LED31 (*((volatile unsigned long*)0x233806FC))       	//FIO1PIN - 0x2009C034, pin 31
#define GPIO2_LED2 (*((volatile unsigned long *)0x23380A88))        	//FIO2PIN - 0x2009C054, pin 2

//delay function
int wait_loop0 = 10000;
int wait_loop1 = 1500;

// nested loops for delay
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
	int r1 = 1, r2 = 2;
	volatile unsigned long * GPIO1_LED28 ;  // function mode
	volatile unsigned long * GPIO2_LED4 ;
    
	LED_Init();
    
	GLCD_Init();                           	/* Initialize graphical LCD*/

	//Title
  GLCD_Clear(White);                     	/* Clears graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, " 	COE718 Demo	");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, __FI, "   Bitband Program  ");
  GLCD_SetBackColor(White);
	GLCD_SetTextColor(Red);

	GPIO1_LED28 = &BitBand(&LPC_GPIO1->FIOPIN1, 28); // bitband function to set LEDs
	GPIO2_LED4 = &BitBand(&LPC_GPIO2->FIOPIN0, 4);
    
	while(1){   	 
        	if(r1 < r2){
      	//mask mode
        	GLCD_DisplayString(5, 0, __FI, "  	Mask Mode	");
        	LPC_GPIO1->FIOPIN |=  ( 1 << 29);  //setting LEDs using masking bits
        	LPC_GPIO2->FIOPIN |=  ( 1 << 3);
        	delay(1);
        	LPC_GPIO2->FIOPIN &=  ~( 1 << 3);  //turning off the mask mode LEDs
        	LPC_GPIO1->FIOPIN &=  ~( 1 << 29);
        	r1++;
	}
    	else if(r1 == r2){
        	//function mode
        	GLCD_DisplayString(5, 0, __FI, "   Function Mode   ");
        	*GPIO2_LED4 = 1;                                     	//setting LEDS using bitband function
        	*GPIO1_LED28 = 1;
        	delay(1);
        	*GPIO2_LED4 = 0;                                  	//turning off the function mode LEDs
        	*GPIO1_LED28 = 0;
        	r1++;
    	}else {
        	//bitband mode
        	GLCD_DisplayString(5, 0, __FI, "	Bitband Mode   ");
        	GPIO2_LED2 = 1;                                 	//setting LEDs using bitbanding
        	GPIO1_LED31 = 1;
        	delay(1);
        	GPIO2_LED2 = 0;                                  	//turning off the bitband mode LEDs
        	GPIO1_LED31 = 0;
        	r1 = 1;
    	}
	}
}
