/*
 * stm32f407xx_uart.c
 *
 *  Created on: Dec 13, 2025
 *      Author: ratho
 */


#include "stm32f407xx_uart.h"
#include "stm32f407xx_rcc.h"

void UART_Echo(UART_Handle_t *pUARTHandle, char ch){
	if (ch == '\b' || ch == 0x7F) {
	    UART_Send_String(pUARTHandle, "\b \b", 3);
	}
	else if (ch == '\r') {
	    UART_Send_String(pUARTHandle, "\r\n", 2);
	}
	else {
	    UART_SendData_Blocking(pUARTHandle, (uint8_t*)&ch, 1);
	}
}

__attribute__((weak)) void UART_ApplicationEventCallback(UART_Handle_t *pUARTHandle, uint8_t Event) {
/* This function can be overridden by the application.
 Default implementation does nothing. */
}

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

void UART_RecieveData_Blocking(UART_Handle_t* pUARTHandle, uint8_t* RXBuff, uint32_t Len){
	//Wait for RXNE Flag
	while(Len > 0){
		if(UART_Get_Status_Flag(pUARTHandle->pUARTx, UART_STATUS_FLAG_RXNE)){
			*RXBuff = pUARTHandle->pUARTx->USART_DR;
			Len--;
			RXBuff++;
		}
	}
}

uint32_t UART_Recieve_String(UART_Handle_t *pUARTHandle,char* str){
	uint32_t count = 0;
	uint8_t temp = 0;
	while(temp != '\r'){
		UART_RecieveData_Blocking(pUARTHandle, &temp, 1);
		UART_Echo(pUARTHandle, (char)temp);
		if(temp == '\b'){
			count--;
			continue;
		}
		str[count] = (char)temp;
		count++;
	}
	return count-1;// Reduce the "\n"
}

void UART_IRQPriorityConfig(UART_Handle_t *pUARTHandle, uint32_t Priority){
	//First Identify the interrupt priority Number
	uint32_t IRQNumber;
	if(pUARTHandle->pUARTx == UART1){
		IRQNumber = IRQ_NUM_USART1;
	}else if(pUARTHandle->pUARTx == UART2){
		IRQNumber = IRQ_NUM_USART2;
	}else if(pUARTHandle->pUARTx == UART3){
		IRQNumber = IRQ_NUM_USART3;
	}else if(pUARTHandle->pUARTx == UART4){
		IRQNumber = IRQ_NUM_UART4;
	}else if(pUARTHandle->pUARTx == UART5){
		IRQNumber = IRQ_NUM_UART5;
	}else if(pUARTHandle->pUARTx == UART6){
		IRQNumber = IRQ_NUM_USART6;
	}else {
		return;
	}
	uint32_t IPR_Number = IRQNumber / 4;
	uint32_t IPR_Index = (IRQNumber % 4)*8;

	//Sanity Check of the priority number
	Priority &= 0x0F;

	// Clear the previous value
	NVIC->IPR[IPR_Number] &= ~(0xF << (IPR_Index+4));
	NVIC->IPR[IPR_Number] |= (Priority << (IPR_Index+4));
}

void UART_IRQInterruptConfig(UART_Handle_t *pUARTHandle, uint8_t EnOrDi){
	if(pUARTHandle == NULL || pUARTHandle->pUARTx == NULL){
		return;
	}
	//First Identify the interrupt priority Number
	uint32_t IRQNumber;
	if(pUARTHandle->pUARTx == UART1){
		IRQNumber = IRQ_NUM_USART1;
	}else if(pUARTHandle->pUARTx == UART2){
		IRQNumber = IRQ_NUM_USART2;
	}else if(pUARTHandle->pUARTx == UART3){
		IRQNumber = IRQ_NUM_USART3;
	}else if(pUARTHandle->pUARTx == UART4){
		IRQNumber = IRQ_NUM_UART4;
	}else if(pUARTHandle->pUARTx == UART5){
		IRQNumber = IRQ_NUM_UART5;
	}else if(pUARTHandle->pUARTx == UART6){
		IRQNumber = IRQ_NUM_USART6;
	}else {
		return;
	}

	uint32_t ISER_Reg_Number = IRQNumber / 32;
	uint32_t ISER_Index = IRQNumber % 32;

	if(EnOrDi == ENABLE){
		NVIC->ISER[ISER_Reg_Number] |= (1U << ISER_Index);
	}else{
		NVIC->ICER[ISER_Reg_Number] |= (1U << ISER_Index);
	}
}


void UART_IRQHandling(UART_Handle_t *pUARTHandle){
	// Extract out all the status bits and check which type of interrupt occurred using Status Reg and Control Reg
	uint8_t CR1_TCIE_Bit 	= ((pUARTHandle->pUARTx->USART_CR1>>USART_CR1_TCIE) & (1 ));
	uint8_t CR1_TXEIE_Bit 	= ((pUARTHandle->pUARTx->USART_CR1>>USART_CR1_TXEIE) & (1));
	uint8_t CR1_PEIE_Bit 	= ((pUARTHandle->pUARTx->USART_CR1>>USART_CR1_PEIE) & (1));
	uint8_t CR1_RXNEIE_Bit 	= ((pUARTHandle->pUARTx->USART_CR1>>USART_CR1_RXNEIE) & (1));
	uint8_t CR1_IDLEIE_Bit 	= ((pUARTHandle->pUARTx->USART_CR1>>USART_CR1_IDLEIE) & (1));

	uint8_t SR_TC_Bit = UART_Get_Status_Flag(pUARTHandle->pUARTx, USART_SR_TC);
	uint8_t SR_TXE_Bit = UART_Get_Status_Flag(pUARTHandle->pUARTx, USART_SR_TXE);
	uint8_t SR_PE_Bit = UART_Get_Status_Flag(pUARTHandle->pUARTx, USART_SR_TC);
	uint8_t SR_RXNE_Bit = UART_Get_Status_Flag(pUARTHandle->pUARTx, USART_SR_RXNE);
	uint8_t SR_IDLE_Bit = UART_Get_Status_Flag(pUARTHandle->pUARTx, USART_SR_IDLE);

	// Based on SR and CR decide which interrupt occurred
	if(CR1_TCIE_Bit & SR_TC_Bit){// TC interrupt Triggered
		//@todo
	}
	if(CR1_TXEIE_Bit & SR_TXE_Bit){// TXE interrupt Triggered
		// Load the TX data
		if(pUARTHandle->TXLen > 0){
			pUARTHandle->pUARTx->USART_DR = *(pUARTHandle->pTXBuffer);
			pUARTHandle->pTXBuffer++;
			pUARTHandle->TXLen--;
		}
		// If the length become zero close the communication
		if(pUARTHandle->TXLen == 0){
			//Disable TXNIE interrupt
			UART_ITControl(pUARTHandle->pUARTx, UART_IT_TYPE_TXE, DISABLE);

			//Clear the global Handle
			pUARTHandle->TXState = UART_STATE_READY;
			pUARTHandle->pTXBuffer = NULL;

			//Notify the user app
		    UART_ApplicationEventCallback(pUARTHandle, UART_EVENT_TX_CMPLT);
		}
	}
	if(CR1_PEIE_Bit & SR_PE_Bit){// PE interrupt Triggered
		//@todo
	}
	if(CR1_RXNEIE_Bit & SR_RXNE_Bit){// RXNEIE interrupt Triggered
		// Take out the data from the RX Reg, this will automatically clear the RXNEIE flag
		uint8_t RxByte = pUARTHandle->pUARTx->USART_DR;
		if(pUARTHandle->RXLen > 0){
			*(pUARTHandle->pRXBuffer) = RxByte;
			pUARTHandle->pRXBuffer++;
			pUARTHandle->RXLen--;
		}
		// If RX length becomes zero it means it have received all the bytes and now we have to disable the interrupt i.e. we require no more interrupts
		if(pUARTHandle->RXLen == 0){
			// Disable the RXNE interrupt
			UART_ITControl(pUARTHandle->pUARTx, UART_IT_TYPE_RXNE, DISABLE);

			//Reset States
			pUARTHandle->RXState = UART_STATE_READY;
			pUARTHandle->pRXBuffer = NULL;

			//Notify the user app
			UART_ApplicationEventCallback(pUARTHandle, UART_EVENT_RX_CMPLT);
		}
	}
	if(CR1_IDLEIE_Bit & SR_IDLE_Bit){// IDLE interrupt Triggered
		//@todo
	}
}

uint8_t UART_SendData_IT(UART_Handle_t* pUARTHandle, uint8_t* TXBuff, uint32_t Len){
	/* Parameter validation */
	if (pUARTHandle == NULL || TXBuff == NULL || Len == 0) {
	    return 1;   /* Error */
	}

	/* Check if UART is already busy in TX */
    if (pUARTHandle->TXState == UART_STATE_BUSY_TX) {
        return 2;   /* Busy */
    }

    // Save the data in Global Handle
    pUARTHandle->TXLen = Len;
    pUARTHandle->pTXBuffer = TXBuff;
    pUARTHandle->TXState = UART_STATE_BUSY_TX;

    //Enable TXE interrupt
    UART_ITControl(pUARTHandle->pUARTx, UART_IT_TYPE_TXE, ENABLE);

    // On success return 0;
    return 0;
}

uint8_t UART_ReceiveData_IT(UART_Handle_t* pUARTHandle, uint8_t* RXBuff, uint32_t Len){
    /* Parameter validation */
    if (pUARTHandle == NULL || RXBuff == NULL || Len == 0) {
        return 1;   /* Error */
    }

    /* Check if UART is already busy in RX */
    if (pUARTHandle->RXState == UART_STATE_BUSY_RX) {
        return 2;   /* Busy */
    }

	// Save the data in Global Handle
	pUARTHandle->RXLen = Len;
	pUARTHandle->RXState = UART_STATE_BUSY_RX;
	pUARTHandle->pRXBuffer = RXBuff;

	/* Enable RXNE interrupt at UART level */
	UART_ITControl(pUARTHandle->pUARTx, UART_IT_TYPE_RXNE, ENABLE);

	// On success Return 0
	return 0;
}

void UART_ITControl(UART_Reg_Def_t *pUARTx, uint8_t InterruptType, uint8_t EnOrDi) {
	if (pUARTx == NULL) {
		return;
	}

	if (EnOrDi == ENABLE) {
		switch (InterruptType) {
		case UART_IT_TYPE_TXE:
			pUARTx->USART_CR1 |= (1 << USART_CR1_TXEIE);
			break;

		case UART_IT_TYPE_TC:
			pUARTx->USART_CR1 |= (1 << USART_CR1_TCIE);
			break;

		case UART_IT_TYPE_RXNE:
			pUARTx->USART_CR1 |= (1 << USART_CR1_RXNEIE);
			break;

		default:
			break;
		}
	} else {
		switch (InterruptType) {
		case UART_IT_TYPE_TXE:
			pUARTx->USART_CR1 &= ~(1 << USART_CR1_TXEIE);
			break;

		case UART_IT_TYPE_TC:
			pUARTx->USART_CR1 &= ~(1 << USART_CR1_TCIE);
			break;

		case UART_IT_TYPE_RXNE:
			pUARTx->USART_CR1 &= ~(1 << USART_CR1_RXNEIE);
			break;

		default:
			break;
		}
	}
}







