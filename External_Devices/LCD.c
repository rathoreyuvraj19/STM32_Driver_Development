/*
 * LCD.c
 *
 *  Created on: Dec 12, 2025
 *      Author: ratho
 */


#include "LCD.h"


void delay_1us(void) {
	for (volatile int i = 0; i < 30; i++)
		; // approx 1 µs @ 168 MHz with O2
}

void delayUS(uint32_t delay) {
	for (volatile uint32_t i = 0; i < delay; i++) {
		delay_1us();
	}
}

void pulse_enable(LCD_Def_t* LCD_Def) {
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_E, 1);
	delayUS(1);
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_E, 0);
	delayUS(1);
}

void load_data_pins(LCD_Def_t* LCD_Def,uint8_t data) {
	uint8_t D7 = (data >> 3) & 0x01;
	uint8_t D6 = (data >> 2) & 0x01;
	uint8_t D5 = (data >> 1) & 0x01;
	uint8_t D4 = (data >> 0) & 0x01;

	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_D7, D7);
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_D6, D6);
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_D5, D5);
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_D4, D4);
}

void LCD_Data_Send(LCD_Def_t* LCD_Def,uint8_t data) {
	//1. First set RS
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_RS, RS_DATA_SELECT);
	delayUS(50);
	//2. Load all the data to each pin
	uint8_t upper_nibble = ((data >> 4) & 0x0F);
	uint8_t lower_nibble = data & 0x0F;
	load_data_pins(LCD_Def,upper_nibble);
	pulse_enable(LCD_Def);
	load_data_pins(LCD_Def,lower_nibble);
	pulse_enable(LCD_Def);
	delayUS(50);
}

void LCD_Command_Send(LCD_Def_t* LCD_Def,uint8_t command) {
	//1. First set RS
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_RS, RS_COMMAND_SELECT);
	delayUS(50);
	//2. Load all the data to each pin
	uint8_t upper_nibble = ((command >> 4) & 0x0F);
	uint8_t lower_nibble = command & 0x0F;
	load_data_pins(LCD_Def,upper_nibble);
	pulse_enable(LCD_Def);
	load_data_pins(LCD_Def,lower_nibble);
	pulse_enable(LCD_Def);
	delayUS(50);
}

void LCD_Init(LCD_Def_t* LCD_Def) {
	// 0. Set the LCD Structure !!
	LCD_Def->GPIOx = GPIOB;
	LCD_Def->LCD_Pin_RS = RS_PIN_NO;
	LCD_Def->LCD_Pin_E 	= E_PIN_NO;
	LCD_Def->LCD_Pin_D4 = D4_PIN_NO;
	LCD_Def->LCD_Pin_D5 = D5_PIN_NO;
	LCD_Def->LCD_Pin_D6 = D6_PIN_NO;
	LCD_Def->LCD_Pin_D7 = D7_PIN_NO;

	/*
	 * 1. Initialize the GPIOs as per the comment
	 * RS -> PB0 Output
	 * E  -> PB1 Output
	 * D4 -> PB4 Output
	 * D5 -> PB5 Output
	 * D6 -> PB6 Output
	 * D7 -> PB7 Output
	 */
	GPIOx_Handle_t GPIOx;
	GPIOx.pGPIOx = LCD_Def->GPIOx;
	GPIOx.GPIO_CONFIG.GPIO_MODE = GPIO_MODE_OUTPUT;
	GPIOx.GPIO_CONFIG.GPIO_OP_TYPE = GPIO_OP_TYPE_PP;
	GPIOx.GPIO_CONFIG.GPIO_SPEED = GPIO_SPEED_MEDIUM;

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_RS;

	gpio_pin_init(&GPIOx);

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_E;
	gpio_pin_init(&GPIOx);
	gpio_write_pin(LCD_Def->GPIOx, LCD_Def->LCD_Pin_E, 0); // Pull E low

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_D4;
	gpio_pin_init(&GPIOx);

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_D5;
	gpio_pin_init(&GPIOx);

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_D6;
	gpio_pin_init(&GPIOx);

	GPIOx.GPIO_CONFIG.GPIO_PIN_NUMBER = LCD_Def->LCD_Pin_D7;
	gpio_pin_init(&GPIOx);

	//2. Initialize the LCD

	//	Step	Command (HEX)	Meaning
	//	1	0x33	Initialize LCD in 8-bit mode (reset sequence)
	//	2	0x32	Switch to 4-bit mode
	//	3	0x28	Function set: 4-bit, 2 lines, 5×8 font
	//	4	0x0C	Display ON, cursor OFF
	//	5	0x06	Entry mode: auto‑increment cursor
	//	6	0x01	Clear display

	//uint8_t Command_Seq[] = {0x33,0x32,0x28,0x0C,0x06,0x01};

	LCD_Command_Send(LCD_Def,0x33);
	delayUS(5000);  // 5 ms

	LCD_Command_Send(LCD_Def,0x32);
	delayUS(200);   // 200 us

	//LCD_Command_Send(0x28);
	LCD_Command_Send(LCD_Def,0x20);
	delayUS(50);

	LCD_Command_Send(LCD_Def,0x0C);
	delayUS(50);

	LCD_Command_Send(LCD_Def,0x06);
	delayUS(50);

	LCD_Command_Send(LCD_Def,0x01);
	delayUS(2000);  // Clear display
}

void LCD_Display_String(LCD_Def_t* LCD_Def,char *data, uint8_t size) {
	LCD_Command_Send(LCD_Def,0x01);
	delayUS(2000);  // Clear display
	LCD_Command_Send(LCD_Def,0x80);
	delayUS(2000);

	for (int i = 0; i < size; i++) {
		LCD_Data_Send(LCD_Def,data[i]);
	}
	if(size > 16){
		LCD_Shift_Display(LCD_Def, LCD_SHIFT_LEFT , size-15);
	}
}

void LCD_Shift_Display(LCD_Def_t* LCD_Def, uint8_t direction, uint8_t steps) {
	// The delay between shifts controls the speed of the scroll.
	// 200ms is a good starting point for a visible, smooth scroll.
	uint32_t scroll_delay_ms = 10;

	for (uint8_t i = 0; i < steps; i++) {
		// Send the Display Shift command (0x18 or 0x1C)
		LCD_Command_Send(LCD_Def,direction);

		// Wait for the shift to be visible before sending the next one
		delayUS(scroll_delay_ms * 1000); // Convert ms to us
	}
}
