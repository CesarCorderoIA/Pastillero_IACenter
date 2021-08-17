/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "HAL_Speaker.h"

/*Function Definitions*/
void HAL_Speaker_Init(void)
{
	MX_TIM2_Init();

	return;
}


void HAL_Speaker_Activate(void)
{
	/* Enable TIM2 - Channel3 */
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH3);
	LL_TIM_EnableCounter(TIM2);

	return;
}

void HAL_Speaker_Deactivate(void)
{
	/* Disable TIM2 - Channel3 */
	LL_TIM_CC_DisableChannel(TIM2, LL_TIM_CHANNEL_CH3);
	LL_TIM_DisableCounter(TIM2);

	return;
}


