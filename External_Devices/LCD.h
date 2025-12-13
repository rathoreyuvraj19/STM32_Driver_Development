/*
 * LCD.h
 *
 *  Created on: Dec 12, 2025
 *      Author: ratho
 */

#ifndef LCD_H_
#define LCD_H_
#include <stdint.h>
#include <string.h>
#include "stm32f407xx_gpio.h"
#include "stm32f407xx_spi.h"

// Place these definitions near the top with your other #defines (e.g., after the pin definitions)
#define LCD_SHIFT_LEFT  0x18U
#define LCD_SHIFT_RIGHT 0x1CU

#define RS_COMMAND_SELECT 	0U
#define RS_DATA_SELECT 		1U
/*
 * 1. Initialize the GPIOs as per the comment
 * RS -> PB0 Output
 * E  -> PB1 Output
 * D4 -> PB4 Output
 * D5 -> PB5 Output
 * D6 -> PB6 Output
 * D7 -> PB7 Output
 */
#define RS_PIN_NO  0U
#define E_PIN_NO  1U
#define D4_PIN_NO  4U
#define D5_PIN_NO  5U
#define D6_PIN_NO  6U
#define D7_PIN_NO  7U

typedef struct {
	GPIOx_RegDef_t *GPIOx;
	uint8_t LCD_Pin_RS;
	uint8_t LCD_Pin_E;
	uint8_t LCD_Pin_D4;
	uint8_t LCD_Pin_D5;
	uint8_t LCD_Pin_D6;
	uint8_t LCD_Pin_D7;
} LCD_Def_t;


void delay_1us(void);
void delayUS(uint32_t delay);
void pulse_enable(LCD_Def_t* LCD_Def);
void load_data_pins(LCD_Def_t* LCD_Def, uint8_t data);
void LCD_Data_Send(LCD_Def_t* LCD_Def, uint8_t data);
void LCD_Command_Send(LCD_Def_t* LCD_Def, uint8_t command);
void LCD_Init(LCD_Def_t* LCD_Def);
void display_lcd(LCD_Def_t* LCD_Def, char *data, uint8_t size);
void LCD_Shift_Display(LCD_Def_t* LCD_Def, uint8_t direction, uint8_t steps);

#endif /* LCD_H_ */
