#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
  
#include "TM4C123GH6PM.h"
#include "nums on 3 displays.h"
#include "port's pins initialization tm4c123.h"

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
/*	else if (n==5)
		num1_5();
	else if (n==6)
		num1_6();
	else if (n==7)
		num1_7();
	else if (n==8)
		num1_8();
	else if (n==9)
		num1_9();*/
}
