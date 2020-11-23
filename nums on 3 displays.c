#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
  
//#include "TM4C123GH6PM.h"
#include "tm4c123gh6pm.h"
#include "nums on 3 displays.h"
#include "port's pins initialization tm4c123.h"

//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_0(void)
{
	PB1=0x02;PB2=0x04;PB3=0x08; PB4=0x10; PB5=0x20;PB6=0x40;
}
void num2_0(void)
{
	PD0=0x01;PD1=0x02;PD2=0x04; PD3=0x08; PD6=0x40;PE2=0x04;
}
void num3_0(void)
{
	PA3=0x08;PB0=0x01;PA5=0x20; PA6=0x40; PA7=0x80;PE0=0x01;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_1(void)
{
	PB2=0x04;PB3=0x08;
}
void num2_1(void)
{
  PD1=0x02;PD2=0x04;;
}
void num3_1(void)
{
	PB0=0x01;PA5=0x20;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_2(void)
{
	PB1=0x02;PB2=0x04; PB4=0x10; PB5=0x20;PB7=0X80;
}
void num2_2(void)
{
	PD0=0x01;PD1=0x02; PD3=0x08; PD6=0x40;PE3=0X08;
}
void num3_2(void)
{
	PA3=0x08;PB0=0x01; PA6=0x40; PA7=0x80;PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_3(void)
{
	PB1=0x02;PB2=0x04;PB3=0x08; PB4=0x10; PB7=0X80;
}
void num2_3(void)
{
	PD0=0x01;PD1=0x02;PD2=0x04; PD3=0x08; PE3=0X08;
}
void num3_3(void)
{
	PA3=0x08;PB0=0x01;PA5=0x20; PA6=0x40; PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_4(void)
{
	PB2=0x04;PB3=0x08; PB6=0x40;PB7=0X80;
}
void num2_4(void)
{
	PD1=0x02;PD2=0x04; PE2=0x04;PE3=0X08;
}
void num3_4(void)
{
	PB0=0x01;PA5=0x20; PE0=0x01;PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_5(void)
{
	PB1=0x02;PB3=0x08; PB4=0x10;PB6=0x40; PB7=0X80;
}
void num2_5(void)
{
	PD0=0x01;PD2=0x04; PD3=0x08;PE2=0x04; PE3=0X08;
}
void num3_5(void)
{
	PA3=0x08;PA5=0x20; PA6=0x40;PE0=0x01;PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_6(void)
{
	PB1=0x02;PB3=0x08; PB4=0x10; PB5=0x20;PB6=0x40;PB7=0X80;
}
void num2_6(void)
{
	PD0=0x01;PD2=0x04; PD3=0x08; PD6=0x40;PE2=0x04;PE3=0X08;
}
void num3_6(void)
{
	PA3=0x08;PA5=0x20; PA6=0x40; PA7=0x80;PE0=0x01;PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_7(void)
{
	PB1=0x02;PB2=0x04;PB3=0x08; 
}
void num2_7(void)
{
	PD0=0x01;PD1=0x02;PD2=0x04; 
}
void num3_7(void)
{
	PA3=0x08;PB0=0x01;PA5=0x20; 
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_8(void)
{
	PB1=0x02;PB2=0x04;PB3=0x08; PB4=0x10; PB5=0x20;PB6=0x40;PB7=0X80;
}
void num2_8(void)
{
	PD0=0x01;PD1=0x02;PD2=0x04; PD3=0x08; PD6=0x40;PE2=0x04;PE3=0X08;
}
void num3_8(void)
{
	PA3=0x08;PB0=0x01;PA5=0x20; PA6=0x40; PA7=0x80;PE0=0x01;PE1=0X02;
}
//0=0X01 ,1=0X02 , 2=0X04 , 3=0X08 ,4=0X10 ,5=0X20 , 6=0X40 , 7=0X80
void num1_9(void)
{
	PB1=0x02;PB2=0x04;PB3=0x08; PB4=0x10; PB6=0x40;PB7=0X80;
}
void num2_9(void)
{
	PD0=0x01;PD1=0x02;PD2=0x04; PD3=0x08; PE2=0x04;PE3=0X08;
}
void num3_9(void)
{
	PA3=0x08;PB0=0x01;PA5=0x20; PA6=0x40; PE0=0x01;PE1=0X02;
}
