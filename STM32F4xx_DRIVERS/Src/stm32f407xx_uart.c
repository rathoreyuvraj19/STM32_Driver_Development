/*
 * stm32f407xx_uart.c
 *
 *  Created on: Dec 13, 2025
 *      Author: ratho
 */


#include "stm32f407xx_uart.h"
#include "stm32f407xx_rcc.h"

void uart_set_baud_rate(UART_Handle_t* pUART_Handle){
	uint32_t fclk = RCC_GetUSARTClock(pUART_Handle->pUARTx);
	if(fclk == 0){
		return;
	}
	uint32_t temp = fclk*125/(1*(2-pUART_Handle->UART_Config.UART_CONFIG_OVER_SAMPLING)*pUART_Handle->UART_Config.UART_CONFIG_BAUD_RATE);
	uint32_t matissa = temp/1000;
	uint32_t fraction= (temp-(matissa*1000))*8*(2-pUART_Handle->UART_Config.UART_CONFIG_OVER_SAMPLING)+500;
	fraction = fraction / 1000;
	pUART_Handle->pUARTx->USART_BRR &= ~(0xFFFF);
	pUART_Handle->pUARTx->USART_BRR |= (matissa<<4);
	pUART_Handle->pUARTx->USART_BRR |= (fraction);
}

void uart_init(UART_Handle_t* pUART_Handle)
{
	//0. Basic Check first
	if((pUART_Handle == NULL) || (pUART_Handle->pUARTx == NULL)){
		return;
	}
    //1.Enable the Peripheral Clock before writing to any of the Configuration Register
	if(pUART_Handle->pUARTx == UART1){
		USART1_PCLK_EN();
	}else if(pUART_Handle->pUARTx == UART2){
		USART2_PCLK_EN();
	}else if(pUART_Handle->pUARTx == UART3){
		USART3_PCLK_EN();
	}else if(pUART_Handle->pUARTx == UART4){
		UART4_PCLK_EN();
	}else if(pUART_Handle->pUARTx == UART5){
		UART5_PCLK_EN();
	}else if(pUART_Handle->pUARTx == UART6){
		USART6_PCLK_EN();
	}

	//2. Set Over Sampling (@note This step must come before setting the baud rate)
	pUART_Handle->pUARTx->USART_CR1 &= ~(1<<USART_CR1_OVER8);
	pUART_Handle->pUARTx->USART_CR1 |= (pUART_Handle->UART_Config.UART_CONFIG_OVER_SAMPLING<<USART_CR1_OVER8);

	//3. Set the mode
	if(pUART_Handle->UART_Config.UART_CONFIG_MODE == UART_CONFIG_MODE_RX){
		pUART_Handle->pUARTx->USART_CR1 &= ~(1U << USART_CR1_TE);
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_RE);
	}else if (pUART_Handle->UART_Config.UART_CONFIG_MODE == UART_CONFIG_MODE_TX){
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_TE);
		pUART_Handle->pUARTx->USART_CR1 &= ~(1U << USART_CR1_RE);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_MODE == UART_CONFIG_MODE_TX_RX){
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_TE);
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_RE);
	}

	//4. Set Baud Rate
	uart_set_baud_rate(pUART_Handle);

	//5. Set the parity
	if(pUART_Handle->UART_Config.UART_CONFIG_PARITY == UART_CONFIG_PARITY_NONE){
		pUART_Handle->pUARTx->USART_CR1 &= ~(1U << USART_CR1_PCE);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_PARITY == UART_CONFIG_PARITY_EVEN ){
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_PCE);
		pUART_Handle->pUARTx->USART_CR1 &= ~(1 << USART_CR1_PS);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_PARITY == UART_CONFIG_PARITY_ODD){
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_PCE);
		pUART_Handle->pUARTx->USART_CR1 |= (1U << USART_CR1_PS);
	}

	//6. Set No of stop Bits
	pUART_Handle->pUARTx->USART_CR2 &= ~(0x3 << USART_CR2_STOP);
	pUART_Handle->pUARTx->USART_CR2 |= (pUART_Handle->UART_Config.UART_CONFIG_NO_OF_STOP_BITS << USART_CR2_STOP);

	//7. Set Word Length
	pUART_Handle->pUARTx->USART_CR1 &= ~(0x1<< USART_CR1_M);
	pUART_Handle->pUARTx->USART_CR1 |= ((pUART_Handle->UART_Config.UART_CONFIG_WORD_LENGTH)<< USART_CR1_M);

	//8. Set Hardware Flow
	if(pUART_Handle->UART_Config.UART_CONFIG_HW_FLOW_CONTROL == UART_CONFIG_HW_FLOW_CONTROL_NONE){
		pUART_Handle->pUARTx->USART_CR3 &= ~(1U<< USART_CR3_CTSE);
		pUART_Handle->pUARTx->USART_CR3 &= ~(1U<< USART_CR3_RTSE);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_HW_FLOW_CONTROL == UART_CONFIG_HW_FLOW_CONTROL_CTS){
		pUART_Handle->pUARTx->USART_CR3 |= (1U<< USART_CR3_CTSE);
		pUART_Handle->pUARTx->USART_CR3 &= ~(1U<< USART_CR3_RTSE);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_HW_FLOW_CONTROL == UART_CONFIG_HW_FLOW_CONTROL_RTS){
		pUART_Handle->pUARTx->USART_CR3 &= ~(1U<< USART_CR3_CTSE);
		pUART_Handle->pUARTx->USART_CR3 |= (1U<< USART_CR3_RTSE);
	}else if(pUART_Handle->UART_Config.UART_CONFIG_HW_FLOW_CONTROL == UART_CONFIG_HW_FLOW_CONTROL_CTS_RTS){
		pUART_Handle->pUARTx->USART_CR3 |= (1U<< USART_CR3_CTSE);
		pUART_Handle->pUARTx->USART_CR3 |= (1U<< USART_CR3_RTSE);
	}
}

void UART_Peri_Control(UART_Reg_Def_t* pUARTx, uint8_t EI_DI){
	if(pUARTx == NULL){
		return ;
	}
	if(EI_DI == ENABLE){
		pUARTx->USART_CR1 |= (1U << USART_CR1_UE);
	}else{
		pUARTx->USART_CR1 &= ~(1U << USART_CR1_UE);
        while (pUARTx->USART_CR1 & (1U << USART_CR1_UE)) {
            /* wait until UART is disabled */
        }
	}
}

void UART_DeInit(UART_Reg_Def_t* pUARTx){
	//1. User RCC reg to reset the peripheral
		while(!UART_Get_Status_Flag(pUARTx,UART_STATUS_FLAG_TC)){

		}
	//2. Disable the UART
		UART_Peri_Control(pUARTx,DISABLE);
	if(pUARTx == UART1){
		USART1_PCLK_DI();
	}else if(pUARTx == UART2){
		USART2_PCLK_DI();
	}else if(pUARTx == UART3){
		USART3_PCLK_DI();
	}else if(pUARTx == UART4){
		UART4_PCLK_DI();
	}else if(pUARTx == UART5){
		UART5_PCLK_DI();
	}else if(pUARTx == UART6){
		USART6_PCLK_DI();
	}
}

uint8_t UART_Get_Status_Flag(UART_Reg_Def_t *pUARTx, uint32_t FlagPos) {
	if(pUARTx == NULL){
		return 0;
	}
	return ((uint8_t) (pUARTx->USART_SR >> FlagPos) & 0x1);
}

void UART_SendData_Blocking(UART_Handle_t *pUARTHandle, uint8_t *TXBuffer, uint32_t Len) {
	if(pUARTHandle == NULL || pUARTHandle->pUARTx == NULL || TXBuffer == NULL || Len == 0){
		return;
	}
	uint32_t idx = 0;
	while (Len > 0) {
		if (UART_Get_Status_Flag(pUARTHandle->pUARTx, UART_STATUS_FLAG_TXE)) {
			pUARTHandle->pUARTx->USART_SR &= ~(1U << USART_SR_TC);
			uint8_t temp = TXBuffer[idx++];
			pUARTHandle->pUARTx->USART_DR = temp;
			Len--;
		}
	}
	while (!UART_Get_Status_Flag(pUARTHandle->pUARTx, UART_STATUS_FLAG_TC)) {

	}
}

void UART_Send_String(UART_Handle_t *pUARTHandle,char* str, uint32_t size){
	for(int i = 0; i<= size; i++){
		UART_SendData_Blocking(pUARTHandle, (uint8_t*)&str[i], 1);
	}
}















