/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DISPLAY_H__
#define __HAL_DISPLAY_H__


#ifdef __cplusplus
extern "C" {
#endif

/*Begin Commands*/
#define CMD_DUMMY		    			0x00
#define CMD_DISPLAY_ON					0xAF
#define CMD_DISPLAY_OFF					0xAE
#define CMD_DISPLAY_ALL_POINTS_ON		0xA5
#define CMD_DISPLAY_ALL_POINTS_NORMAL	0xA4
#define CMD_DISPLAY_START_ADDRESS		0x40
#define CMD_ELEC_VOLUME_MODE_SET    	0x81
#define CMD_V0_INTERNAL_RESISTOR_RATIO	0x21
#define CMD_PWR_CTL_SET_OPERATING_MODE  0x2F
#define CMD_LCD_BIAS_1_9				0xA2
#define CMD_COM_OUTPUT_NORMAL_DIR		0xC0
#define ADC_SELECT_RAM_SEG_NORMAL		0xA0

#define PAGE_ADDRESS_0					0xB0
#define NUM_OF_PAGES					8

#define LCD_WIDTH						128

#define DELAY_SECURE_TRANS				1

/*End Commands*/


/*Begin Prototypes */
void HAL_Display_Init(void);
void HAL_Display_Clear(void);
void HAL_Display_A0_Cmd(void);
void HAL_Display_A0_Data(void);
void HAL_Display_Reset_Enable(void);
void HAL_Display_Reset_Disable(void);
void HAL_Display_Commands(uint8_t cmd);


/*End Prototypes */


#ifdef __cplusplus
}
#endif

#endif /* __HAL_DISPLAY_H__ */
