/*
 * stm32f407xx_uart.h
 *
 *  Created on: Dec 13, 2025
 *      Author: ratho
 */

#ifndef INC_STM32F407XX_UART_H_
#define INC_STM32F407XX_UART_H_

#include "stm32f407xx.h"


/**
 * @defgroup UART_DRIVER_DEVELOPEMNT UART Driver
 * @brief UART Driver Development
 * @{
 */
	/**
	 * @brief UART_CONFIG_TYPE_DEF
	 */
	typedef struct {
		uint8_t USART_CONFIG_Mode;
		uint32_t USART_CONFIG_Buad_Rate;
		uint8_t USART_CONFIG_Parity;
		uint8_t USART_CONFIG_No_Of_Stop_Bits;
		uint8_t USART_CONFIG_Word_Length;
		uint8_t USART_CONFIG_HW_Flow_Control;
	}UART_Config_t;

	/**
	 * @brief UART_HANDLE_TYPE_DEF
	*/
	typedef struct{
		UART_Reg_Def_t* pUARTx;
		UART_Config_t   UART_Config;
	}UART_Handle_t;

/** @} */ // End of UART_DRIVER_DEVELOPEMNT
#endif /* INC_STM32F407XX_UART_H_ */
