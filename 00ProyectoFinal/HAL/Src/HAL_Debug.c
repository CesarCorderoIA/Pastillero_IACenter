/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "HAL_Debug.h"
#include <stdio.h>

void HAL_Debug(char ch[])
{
	printf("%s\n\r", ch);
	fflush(stdout);
	LL_mDelay(1000);
}
