/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "HAL_Display.h"

/*Function Definitions*/
void HAL_Display_Init(void)
{

	/* Init in GPIO module before calling this
	 * PA6 - LCD reset signal, enabled in low level
	 * PB6 - Chip select, which set functions are included in SPI1
	 * PA8 - A0 which defines if it is command or data */
	MX_SPI1_Init();

	/* Make sure to set reset line to low for tRW time (1us at least 3.3V)
	 * and let time pass after tR (1us at least 3.3V, there is no resolution for
	 * such a small change, so 1ms will suffice */
	HAL_Display_Reset_Enable();
	LL_mDelay(DELAY_SECURE_TRANS);
	HAL_Display_Reset_Disable();
	LL_mDelay(DELAY_SECURE_TRANS);


	/* Start with display init recommended in spec for
	 * NHD-C1283A12-FSW-FBW */

	/* Configure A0 for command, Initialize LCD */
	MX_SPI1_CS_Enable();
	HAL_Display_A0_Cmd();
	LL_mDelay(DELAY_SECURE_TRANS);

	/* ADC select - sets the display RAM address SEG output to normal */
	MX_SPI1_Send(ADC_SELECT_RAM_SEG_NORMAL);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* LCD display off */
	MX_SPI1_Send(CMD_DISPLAY_OFF);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Common output mode select, select COM output scan direction: normal direction */
	MX_SPI1_Send(CMD_COM_OUTPUT_NORMAL_DIR);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* LCD Bias set: 1/9 bias */
	MX_SPI1_Send(CMD_LCD_BIAS_1_9);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Select internal power supply 111: only the internal power supply is set */
	MX_SPI1_Send(CMD_PWR_CTL_SET_OPERATING_MODE);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* V0 voltage internal resistor ratio: 001 = 3.5 */
	MX_SPI1_Send(CMD_V0_INTERNAL_RESISTOR_RATIO);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Electronic volume set to 3F*/
	MX_SPI1_Send(CMD_ELEC_VOLUME_MODE_SET);
	LL_mDelay(DELAY_SECURE_TRANS);
	MX_SPI1_Send(0x3F);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Display start line */
	MX_SPI1_Send(CMD_DISPLAY_START_ADDRESS);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Set segments: all segments on */
	MX_SPI1_Send(CMD_DISPLAY_ALL_POINTS_ON);
	LL_mDelay(DELAY_SECURE_TRANS);

	/* Set Display ON */
	MX_SPI1_Send(CMD_DISPLAY_ON);
	LL_mDelay(DELAY_SECURE_TRANS);
	MX_SPI1_CS_Disable();

	/* Configure A0 for data and disable CS */
	MX_SPI1_CS_Disable();
	HAL_Display_A0_Data();
	LL_mDelay(1);

	HAL_Display_Clear();

	return;
}


void HAL_Display_Clear(void)
{
	/*Display OFF*/
	MX_SPI1_CS_Enable();
	HAL_Display_A0_Cmd();
	MX_SPI1_Send(CMD_DISPLAY_OFF);
	LL_mDelay(DELAY_SECURE_TRANS);
    MX_SPI1_CS_Disable();

	/*Start clearing page by page*/
	for(uint8_t page = 0; page < NUM_OF_PAGES; page++)
	{
		MX_SPI1_CS_Enable();

		HAL_Display_A0_Cmd();

		MX_SPI1_Send(PAGE_ADDRESS_0 | page);
		LL_mDelay(DELAY_SECURE_TRANS);

		for(uint8_t column = 0; column < LCD_WIDTH; column++)
		{
			/* Column lower, then upper */
			HAL_Display_A0_Cmd();
			MX_SPI1_Send(0x00 | (column & 0x0F));
			LL_mDelay(DELAY_SECURE_TRANS);
			MX_SPI1_Send(0x10 | ((column >> 4) & 0x0F));
			LL_mDelay(DELAY_SECURE_TRANS);

			/* Clear data */
			HAL_Display_A0_Data();
			MX_SPI1_Send(CMD_DUMMY);
			LL_mDelay(DELAY_SECURE_TRANS);
		}

		MX_SPI1_CS_Disable();
	}
	/*Set display ON*/
	MX_SPI1_CS_Enable();
	HAL_Display_A0_Cmd();
	MX_SPI1_Send(CMD_DISPLAY_ON);
	LL_mDelay(DELAY_SECURE_TRANS);
	MX_SPI1_CS_Disable();

	return;
}

void HAL_Display_A0_Cmd(void)
{
	/* A0 is assumed to be configured in GPIO module and it is used to send
	 * commands when low*/
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);

	return;
}

void HAL_Display_A0_Data(void)
{
	/* A0 is assumed to be configured in GPIO module and it is used to send
	 * data when high*/
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);

	return;
}

void HAL_Display_Reset_Enable(void)
{
	/* Reset line is assumed to be configured in GPIO module and it is used to
	 * reset the display when low */
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);

	return;
}

void HAL_Display_Reset_Disable(void)
{
	/* Reset line is assumed to be configured in GPIO module and it is used to
	 * release the display when high */
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6);

	return;
}

void HAL_Display_Commands(uint8_t cmd)
{
	MX_SPI1_Send(cmd);

	return;
}
