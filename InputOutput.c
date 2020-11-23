// InputOutput.c
// Runs on LM4F120/TM4C123
// Test the switch initialization functions by setting the LED
// color according to the status of the switches.
// Daniel and Jonathan Valvano
// May 3, 2015

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016
   Section 4.2    Program 4.1

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// negative logic switches connected to PF0 and PF4 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad
// NOTE: The NMI (non-maskable interrupt) is on PF0.  That means that
// the Alternate Function Select, Pull-Up Resistor, Pull-Down Resistor,
// and Digital Enable are all locked for PF0 until a value of 0x4C4F434B
// is written to the Port F GPIO Lock Register.  After Port F is
// unlocked, bit 0 of the Port F GPIO Commit Register must be set to
// allow access to PF0's control registers.  On the LM4F120, the other
// bits of the Port F GPIO Commit Register are hard-wired to 1, meaning
// that the rest of Port F can always be freely re-configured at any
// time.  Requiring this procedure makes it unlikely to accidentally
// re-configure the JTAG pins as GPIO, which can lock the debugger out
// of the processor and make it permanently unable to be debugged or
// re-programmed.
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "nums on 3 displays.h"
#include "C:\Keil\TExaSware\tm4c123gh6pm.h"
//#include "display 1.h"
//#include "display 2.h"
//#include "display 3.h"

#define MAX_TIME 750000
#define  PA2 (*((volatile uint32_t*)0x40004010))
#define  PA3 (*((volatile uint32_t*)0x40004020))
#define  PA4 (*((volatile uint32_t*)0x40004040))
#define  PA5 (*((volatile uint32_t*)0x40004080))
#define  PA6 (*((volatile uint32_t*)0x40004100))
#define  PA7 (*((volatile uint32_t*)0x40004200))
	
#define  PB0 (*((volatile uint32_t*)0x40005004))
#define  PB1 (*((volatile uint32_t*)0x40005008))
#define  PB2 (*((volatile uint32_t*)0x40005010))
#define  PB3 (*((volatile uint32_t*)0x40005020))
#define  PB4 (*((volatile uint32_t*)0x40005040))
#define  PB5 (*((volatile uint32_t*)0x40005080))
#define  PB6 (*((volatile uint32_t*)0x40005100))
#define  PB7 (*((volatile uint32_t*)0x40005200))
	
#define  PC4 (*((volatile uint32_t*)0x40006040))
#define  PC5 (*((volatile uint32_t*)0x40006080))
#define  PC6 (*((volatile uint32_t*)0x40006100))
#define  PC7 (*((volatile uint32_t*)0x40006200))
	
#define  PD0 (*((volatile uint32_t*)0x40007004))
#define  PD1 (*((volatile uint32_t*)0x40007008))
#define  PD2 (*((volatile uint32_t*)0x40007010))
#define  PD3 (*((volatile uint32_t*)0x40007020))
#define  PD6 (*((volatile uint32_t*)0x40007100))
#define  PD7 (*((volatile uint32_t*)0x40007200))

#define  PE0 (*((volatile uint32_t*)0x40024004))
#define  PE1 (*((volatile uint32_t*)0x40024008))
#define  PE2 (*((volatile uint32_t*)0x40024010))
#define  PE3 (*((volatile uint32_t*)0x40024020))
#define  PE4 (*((volatile uint32_t*)0x40024040))
#define  PE5 (*((volatile uint32_t*)0x40024080))

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0       (*((volatile uint32_t *)0x40025004))
#define PF4       (*((volatile uint32_t *)0x40025040))
#define SWITCHES  (*((volatile uint32_t *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
#define ECHO (1U<<2) //PA2(INput)
#define TRIGGER (1U<<3) //PA3(OUTPUT)
float measureD(void);
uint32_t counter =0;
float distance=0;

void PortF_Init(void){ volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
uint32_t PortF_Input(void){
  return (GPIO_PORTF_DATA_R&0x11);  // read PF4,PF0 inputs
}

void PortF_Output(uint32_t data){ // write PF3-PF1 outputs
  GPIO_PORTF_DATA_R = data;
}

void delay_Microsecond(uint32_t time)
{
    int i;
    SYSCTL_RCGCTIMER_R |=(1U<<1); 
        TIMER1_CTL_R=0;
    TIMER1_CFG_R=0x04;
    TIMER1_TAMR_R=0x02;
    TIMER1_TAILR_R= 16-1;
    TIMER1_ICR_R =0x1;
    TIMER1_CTL_R |=0x01;
 
    for(i=0;i<time;i++){ 
        while((TIMER1_RIS_R & 0x1)==0);
     TIMER1_ICR_R = 0x1;
    }
 
}
float measureD(void){ 
    GPIO_PORTA_DATA_R &=~TRIGGER;
    delay_Microsecond(10);
    GPIO_PORTA_DATA_R |= TRIGGER;
    delay_Microsecond(10);
		GPIO_PORTA_DATA_R &=~TRIGGER;
    counter =0;
    while((GPIO_PORTA_DATA_R&ECHO)==0)    {}
    while(((GPIO_PORTA_DATA_R&ECHO )!=0) &(counter < MAX_TIME))  { 
			counter++; 
			delay_Microsecond(20);
		}	 
		distance = (float)counter*(float)0.171500*1.5;
		return distance; 
}

void initall(void){
	  SYSCTL_RCGCGPIO_R  |=(1U<<0); //Enable clock for PORTA 
			delay_Microsecond(100);
GPIO_PORTA_DIR_R |=TRIGGER;
GPIO_PORTA_DEN_R |=(ECHO)|(TRIGGER);
  	
}

void display_third_digit (int n)
{
	if (n==0)
		num1_0();
	else if (n==1)
		num1_1();
	else if (n==2)
		num1_2();
	else if (n==3)
		num1_3();
	else if (n==4)
		num1_4();
}
void display_second_digit (int n)
{
	if (n==0)
		num2_0();
	else if (n==1)
		num2_1();
	else if (n==2)
		num2_2();
	else if (n==3)
		num2_3();
	else if (n==4)
		num2_4();
	else if (n==5)
		num2_5();
  	else if (n==6)
		num2_6();
	else if (n==7)
		num2_7();
	else if (n==8)
		num2_8();
	else if (n==9)
		num2_9();
}

void display_first_digit (int n)
{
	if (n==0)
		num3_0();
	else if (n==1)
		num3_1();
	else if (n==2)
		num3_2();
	else if (n==3)
		num3_3();
	else if (n==4)
		num3_4();
	else if (n==5)
		num3_5();
	else if (n==6)
		num3_6();
	else if (n==7)
		num3_7();
	else if (n==8)
		num3_8();
	else if (n==9)
		num3_9();
}


int main(void){ uint32_t status;
  PortF_Init();              // initialize PF0 and PF4 and make them inputs
    initall();
	PortF_Output(BLUE);
	delay_Microsecond(1000000);
	
	SYSCTL_RCGCGPIO_R |= (0x01); //PORT A
	 SYSCTL_RCGCGPIO_R |= (0x02); //PORT B
	 SYSCTL_RCGCGPIO_R |= (0x08); //PORT D
   SYSCTL_RCGCGPIO_R |= (0x10); //PORT E
										
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
  GPIO_PORTD_CR_R = 0xff;
												 
	GPIO_PORTA_AMSEL_R =0x00;
  GPIO_PORTB_AMSEL_R =0x00;
	GPIO_PORTD_AMSEL_R =0x00;
	GPIO_PORTE_AMSEL_R =0x00;
	GPIO_PORTA_PCTL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00;
  GPIO_PORTD_PCTL_R = 0x00;
  GPIO_PORTE_PCTL_R = 0x00;
  GPIO_PORTA_AFSEL_R = 0x00 ;
	GPIO_PORTB_AFSEL_R = 0x00 ;
	GPIO_PORTD_AFSEL_R = 0x00 ;
  GPIO_PORTE_AFSEL_R = 0x00 ;
  GPIO_PORTA_DIR_R  |= 0xFB ;
  GPIO_PORTB_DIR_R  |= 0xFE ;
  GPIO_PORTD_DIR_R  |= 0xFF ;	
  GPIO_PORTE_DIR_R  |= 0xFF ;
  GPIO_PORTA_DEN_R |= 0xFF ;
  GPIO_PORTB_DEN_R |= 0xFF ;
	GPIO_PORTD_DEN_R |= 0xFF ;
	GPIO_PORTE_DEN_R |= 0xFF ;			
	
	// make PF3-1 out (PF3-1 built-in LEDs)
  while(1){
    status = measureD();
		
    if(status<10) PortF_Output(BLUE); 
     else if(status < 50) PortF_Output(RED);  // SW2 pressed
      else if(status<100) PortF_Output(GREEN);// both switches pressed
      else PortF_Output(0);     // neither switch pressed
    
	}
		/*delay_Microsecond(1000000);
		int count=0;
 // int  n = measureD();
int numberArray[3];
		
  // while ()
		 {
      // numberArray[count] = n % 10;
	  // cout<<numberArray[count]<<endl;
      // n /= 10;
       //count++;
			 numberArray[2]=status/100;
			 status= status-numberArray[2];
			 numberArray[1]=status/10;
			 status=status-numberArray[1];
			 numberArray[0]=status;
			 
  
    //  }
		 display_first_digit(numberArray[0]);
			display_second_digit(numberArray[1]);
			display_third_digit(numberArray[2]);
			*/
			
 }

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
