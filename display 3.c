#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
  
#include "TM4C123GH6PM.h"
#include "nums on 3 displays.h"
#include "port's pins initialization tm4c123.h"

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
