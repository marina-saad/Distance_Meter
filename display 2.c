#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
  
#include "TM4C123GH6PM.h"
#include "nums on 3 displays.h"
#include "port's pins initialization tm4c123.h"

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
