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
	 * @defgroup UART_CONFIG_MACROS UART Configuration Macros
	 * @brief UART Configuration Macros
	 * @{
	 */

		#define UART_CONFIG_MODE_TX		0U
		#define UART_CONFIG_MODE_RX		1U
		#define UART_CONFIG_MODE_TX_RX	2U

		#define UART_CONFIG_BAUD_RATE_9600		9600U
		#define UART_CONFIG_BAUD_RATE_19200 	19200U
		#define UART_CONFIG_BAUD_RATE_38400 	38400U
		#define UART_CONFIG_BAUD_RATE_57600 	57600U
		#define UART_CONFIG_BAUD_RATE_115200 	115200U
		#define UART_CONFIG_BAUD_RATE_230400 	230400U
		#define UART_CONFIG_BAUD_RATE_460800 	460800U
		#define UART_CONFIG_BAUD_RATE_576000 	576000U
		#define UART_CONFIG_BAUD_RATE_921600 	921600U

		#define UART_CONFIG_PARITY_NONE	0U
		#define UART_CONFIG_PARITY_EVEN	1U
		#define UART_CONFIG_PARITY_ODD 	2U

		#define UART_CONFIG_STOP_BITS_1     0U
		#define UART_CONFIG_STOP_BITS_0_5   1U
		#define UART_CONFIG_STOP_BITS_2     2U
		#define UART_CONFIG_STOP_BITS_1_5   3U


		#define UART_CONFIG_WORD_LENGTH_8	0U
		#define UART_CONFIG_WORD_LENGTH_9	1U

		#define UART_CONFIG_HW_FLOW_CONTROL_NONE		0U
		#define UART_CONFIG_HW_FLOW_CONTROL_CTS			1U
		#define UART_CONFIG_HW_FLOW_CONTROL_RTS			2U
		#define UART_CONFIG_HW_FLOW_CONTROL_CTS_RTS		3U

		#define UART_CONFIG_OVER_SAMPLING_8		1U
		#define UART_CONFIG_OVER_SAMPLING_16	0U

	/** @} */

	/**
	 * @defgroup UART_STATUS_FLAG_MACROS UART Status Flag Macros
	 * @brief UART status register flag bit position definitions
	 * @{
	 */

		#define UART_STATUS_FLAG_PE     0U  /*!< Parity Error flag bit position */
		#define UART_STATUS_FLAG_FE     1U  /*!< Framing Error flag bit position */
		#define UART_STATUS_FLAG_NF     2U  /*!< Noise Error flag bit position */
		#define UART_STATUS_FLAG_ORE    3U  /*!< Overrun Error flag bit position */
		#define UART_STATUS_FLAG_IDLE   4U  /*!< IDLE line detected flag bit position */
		#define UART_STATUS_FLAG_RXNE   5U  /*!< Receive data register not empty */
		#define UART_STATUS_FLAG_TC     6U  /*!< Transmission complete */
		#define UART_STATUS_FLAG_TXE    7U  /*!< Transmit data register empty */
		#define UART_STATUS_FLAG_LBD    8U  /*!< LIN break detection flag */
		#define UART_STATUS_FLAG_CTS    9U  /*!< CTS flag */

	/** @} */


	/**
	 * @brief UART_CONFIG_MACROS
	 */
	typedef struct {
		uint8_t 	UART_CONFIG_MODE;
		uint32_t 	UART_CONFIG_BAUD_RATE;
		uint8_t 	UART_CONFIG_PARITY;
		uint8_t 	UART_CONFIG_NO_OF_STOP_BITS;
		uint8_t 	UART_CONFIG_WORD_LENGTH;
		uint8_t 	UART_CONFIG_HW_FLOW_CONTROL;
		uint8_t   	UART_CONFIG_OVER_SAMPLING;
	}UART_Config_t;

	/**
	 * @brief UART_HANDLE_TYPE_DEF
	*/
	typedef struct{
		UART_Reg_Def_t* pUARTx;
		UART_Config_t   UART_Config;

		uint8_t* pTXBuffer;
		uint32_t TXLen;
		uint32_t TXState;

		uint8_t* pRXBuffer;
		uint32_t RXLen;
		uint32_t RXState;
	}UART_Handle_t;

	/** @} */ // End of UART_DRIVER_DEVELOPEMNT

	/**
	 * @brief   Initializes the UART peripheral with user-defined configuration.
	 *
	 * @details This function configures the UART peripheral registers based on
	 *          the parameters stored in the @ref UART_Handle_t structure.
	 *          It sets up:
	 *          - UART operating mode (TX, RX, or TX/RX)
	 *          - Baud rate
	 *          - Word length
	 *          - Parity control
	 *          - Number of stop bits
	 *          - Hardware flow control
	 *
	 *          The function programs the corresponding USART registers
	 *          (CR1, CR2, CR3, and BRR) and enables the UART peripheral.
	 *
	 *          This function does not enable interrupts or DMA. Those features
	 *          must be configured separately using dedicated APIs.
	 *
	 * @param   pUART_Handle[in] Pointer to a UART handle structure containing
	 *                           the UART peripheral base address and configuration.
	 *
	 * @note    The UART peripheral clock must be enabled before calling this function.
	 * @note    Invalid configuration combinations (e.g., word length vs parity)
	 *          should be validated by the caller or internally by this function.
	 *
	 * @warning This function assumes the UART peripheral is in the disabled state
	 *          before initialization. Re-initializing an enabled UART may lead
	 *          to undefined behavior.
	 *
	 * @return  void
	 */
	void uart_init(UART_Handle_t* pUART_Handle);

	/**
	 * @brief   Enable or disable the UART peripheral.
	 *
	 * @details This function controls the main UART peripheral enable bit.
	 *          When enabled, the UART peripheral becomes operational and can
	 *          transmit and receive data. When disabled, the UART is stopped
	 *          and its registers are not active.
	 *
	 * @param[in] pUARTx  Pointer to the UART peripheral base address
	 *                    (e.g., USART1, USART2, USART3, UART4, UART5).
	 *
	 * @param[in] EI_DI   Enable or disable control:
	 *                    - ENABLE  : Enable the UART peripheral
	 *                    - DISABLE : Disable the UART peripheral
	 *
	 * @note    The UART must be disabled before changing certain configuration
	 *          parameters such as word length, parity, and stop bits.
	 *
	 * @warning Disabling the UART while a transmission is in progress may
	 *          result in data loss.
	 */
	void UART_Peri_Control(UART_Reg_Def_t* pUARTx, uint8_t EI_DI);

	/**
	 * @brief   Get the status of a UART status flag.
	 *
	 * @details This function checks the specified status flag in the UART
	 *          status register and reports whether the flag is set or cleared.
	 *          It does not modify the flag state.
	 *
	 * @param[in] pUARTx    Pointer to the UART peripheral base address
	 *                      (e.g., USART1, USART2, USART3, UART4, UART5).
	 *
	 * @param[in] FlagName  Name of the UART status flag to be checked.
	 *                      This parameter must be one of the predefined
	 *                      UART status flag macros:
	 *                      - UART_FLAG_TXE
	 *                      - UART_FLAG_RXNE
	 *                      - UART_FLAG_TC
	 *                      - UART_FLAG_PE
	 *                      - UART_FLAG_FE
	 *                      - UART_FLAG_NE
	 *                      - UART_FLAG_ORE
	 *
	 * @return  uint8_t     FLAG_SET   (1) if the flag is set
	 *                      FLAG_RESET (0) if the flag is cleared
	 *
	 * @note    Some status flags are cleared by specific read or write
	 *          sequences as defined in the reference manual.
	 *          This function only reads the flag state.
	 */
	uint8_t UART_Get_Status_Flag(UART_Reg_Def_t* pUARTx, uint32_t FlagPos);

	/**
	 * @brief   De-initialize the UART peripheral.
	 *
	 * @details This function de-initializes the specified UART peripheral by
	 *          disabling the UART, clearing all configuration and status registers,
	 *          and returning the peripheral to its reset state using the RCC
	 *          peripheral reset mechanism.
	 *
	 * @param[in] pUARTx  Pointer to the UART peripheral base address
	 *                    (e.g., USART1, USART2, USART3, UART4, UART5).
	 *
	 * @note    This function waits for any ongoing transmission to complete
	 *          before disabling the UART to avoid data corruption.
	 *
	 * @note    GPIO de-initialization is not handled by this function and must
	 *          be performed separately if required.
	 *
	 * @warning Disabling or resetting the UART while a transmission or reception
	 *          is in progress may result in data loss.
	 */
	void UART_DeInit(UART_Reg_Def_t* pUARTx);

	void UART_SendData_Blocking(UART_Handle_t *pUARTHandle, uint8_t *TXBuffer, uint32_t Len);

	void UART_Send_String(UART_Handle_t *pUARTHandle,char* str, uint32_t size);

	void UART_RecieveData_Blocking(UART_Handle_t* pUARTHandle, uint8_t* RXBuff, uint32_t Len);

	uint32_t UART_Recieve_String(UART_Handle_t *pUARTHandle,char* str);

	void UART_IRQInterruptConfig(UART_Handle_t *pUARTHandle, uint8_t EnOrDi);// This function is used to configure the NVIC for the interrupt

	void UART_IRQPriorityConfig(UART_Handle_t *pUARTHandle, uint32_t Priority);

	void UART_IRQHandling(UART_Handle_t *pUARTHandle);

	void UART_ITControl(UART_Reg_Def_t *pUARTx, uint8_t InterruptType, uint8_t EnOrDi);

	uint8_t UART_RecieveData_IT(UART_Handle_t* pUARTHandle, uint8_t* RXBuff, uint32_t Len);

	//*********UART INTERRUPT EVENT************//
	#define UART_STATE_READY    0
	#define UART_STATE_BUSY_TX  1
	#define UART_STATE_BUSY_RX  2

	#define UART_EVENT_TX_CMPLT   			1
	#define UART_EVENT_RX_CMPLT   			2
	#define UART_EVENT_IDLE      			3
	#define UART_EVENT_ERROR     			4
	#define UART_EVENT_RX_STR_CMPLT     	5

	#define UART_IT_TYPE_TXE 	0
	#define UART_IT_TYPE_TC 	1
	#define UART_IT_TYPE_RXNE 	2



#endif /* INC_STM32F407XX_UART_H_ */
