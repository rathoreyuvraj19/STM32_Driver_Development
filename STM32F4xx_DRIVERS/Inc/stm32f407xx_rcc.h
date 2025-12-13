/*
 * stm32f407xx_rcc.h
 *
 *  Created on: Dec 13, 2025
 *      Author: ratho
 */

#ifndef INC_STM32F407XX_RCC_H_
#define INC_STM32F407XX_RCC_H_

#include "stm32f407xx.h"

#define MHZ			(1000000U)
#define HSI_Freq 	(16U * MHZ)
#define HSE_Freq 	(8U * MHZ )

#define CLK_SRC_HSI 0U
#define CLK_SRC_HSE 1U
#define CLK_SRC_PLL 2U

uint32_t RCC_GetPCLK1Freq(void);

uint32_t RCC_GetPCLK2Freq(void);

uint32_t RCC_GetUSARTClock(UART_Reg_Def_t *USARTx);


#endif /* INC_STM32F407XX_RCC_H_ */
