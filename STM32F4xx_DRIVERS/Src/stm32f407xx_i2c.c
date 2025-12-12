/*
 * stm32f407xx_i2c.c
 *
 *  Created on: Dec 8, 2025
 *      Author: ratho
 */

#include "stm32f407xx_i2c.h"

void I2C_Peri_Control(I2C_RegDef_t *pI2C, uint8_t EN_DI){
	if (EN_DI == ENABLE) {

	} else {

	}
}

void I2C_Init(I2C_Handle_t *pI2C_Handle){
	if(pI2C_Handle == NULL){
		return;
	}
}
