/*
 * stm32f407xx_spi.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ratho
 */

#include "stm32f407xx_spi.h"

/***********************
 * Internal Helper Definitions
 * @note keep them in .c file only, it will prevent them from exposing to the user
 * also use keyword static with it
 ***********************/

static void SPI_Tx_IRQ_Helper(SPIx_Handle_t *pHandle){
	// Check and Load the data into DR
	if (pHandle->TXLen > 0) {
		pHandle->pSPIx->DR = *(pHandle->pTXBuffer);
		pHandle->TXLen--;
		pHandle->pTXBuffer++;
	}

	// Check for transmission complete
	if (pHandle->TXLen == 0) {
		SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_TXE, DISABLE);
		pHandle->TxState = SPI_STATE_READY;
		pHandle->TXLen = 0;
		pHandle->pTXBuffer = NULL;
		SPI_ApplicationEventCallback(pHandle, SPI_EVENT_TX_CMPLT);
	}
}

static void SPI_Rx_IRQ_Helper(SPIx_Handle_t *pHandle) {
	// Check and Load the data into DR
	if (pHandle->RXLen > 0) {
		*(pHandle->pRXBuffer) = (pHandle->pSPIx->DR);
		pHandle->RXLen--;
		pHandle->pRXBuffer++;
	}

	// Check for reception complete
	if (pHandle->RXLen == 0) {
		SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_RXNE, DISABLE);
		pHandle->RxState = SPI_STATE_READY;
		pHandle->RXLen = 0;
		pHandle->pRXBuffer = NULL;
		SPI_ApplicationEventCallback(pHandle, SPI_EVENT_RX_CMPLT);
	}
}
static void SPI_OVR_Err_IRQ_Helper(SPIx_Handle_t *pHandle){
	//1. Clear the OVER_RUN flag
	// @note Clearing the OVR bit is done by a read from the SPI_DR register followed by a read access
	// to the SPI_SR register.
	volatile uint32_t temp;
	temp = pHandle->pSPIx->DR; // First Read from SPI_DR reg.
	temp = pHandle->pSPIx->SR; // Second Read from SPI_SR reg to clear the flag.
	(void)temp;
	//2. Inform the application about the over run error
	SPI_ApplicationEventCallback(pHandle, SPI_EVENT_OVR_ERR);
}

static void SPI_CRC_Err_IRQ_Helper(SPIx_Handle_t *pHandle){
	/** @todo Complete the SPI_CRC_Err_IRQ_Helper() **/
}

static void SPI_MODF_Err_IRQ_Helper(SPIx_Handle_t *pHandle){
	/** @todo Complete the SPI_MODF_Err_IRQ_Helper() **/
}


void SPIx_Init(SPIx_Handle_t *pSPI_Handle){
	SPIx_RegDef_t* pSPIx = pSPI_Handle->pSPIx;
	uint8_t SPI_DEVICE_MODE = pSPI_Handle->SPI_CONFIG.SPI_DEVICE_MODE;
	uint8_t SPI_BUS_MODE = pSPI_Handle->SPI_CONFIG.SPI_BUS_MODE;
	uint8_t SPI_CLOCK_SPEED = pSPI_Handle->SPI_CONFIG.SPI_CLOCK_SPEED;
	uint8_t SPI_CPOL = pSPI_Handle->SPI_CONFIG.SPI_CPOL;
	uint8_t SPI_CPHA = pSPI_Handle->SPI_CONFIG.SPI_CPHA;
	uint8_t SPI_FRAME_SIZE = pSPI_Handle->SPI_CONFIG.SPI_FRAME_SIZE;
	uint8_t SPI_SSM_SETTING = pSPI_Handle->SPI_CONFIG.SPI_SSM_SETTING;
	uint8_t SPI_BIT_ORDER = pSPI_Handle->SPI_CONFIG.SPI_BIT_ORDER;
	uint8_t SPI_SSOE = pSPI_Handle->SPI_CONFIG.SPI_SSOE;
	uint8_t SPI_CRC_EN = pSPI_Handle->SPI_CONFIG.SPI_CRC_EN;
	//@todo use SPI_CRC_EN later
	(void)SPI_CRC_EN;
	/** 1. Enable the SPIx peripheral clock Through RCC */
	RCC_RegDef_t* pRCC = RCC;
	if(pSPIx == SPI1){ /** Enable the SPI1 RCC APB2ENR reg */
		pRCC->APB2ENR |= (1 << 12);
	}else if(pSPIx == SPI2){/** Enable the SPI2 RCC APB1ENR reg */
		pRCC->APB1ENR |= (1 << 14);
	}else if(pSPIx == SPI3){/** Enable the SPI3 RCC APB1ENR reg */
		pRCC->APB1ENR |= (1 << 15);
	}

	/** 2. Set Device Mode Master/Slave (MSTR)	 */
	pSPIx->CR1 &= ~(1 << SPI_CR1_MSTR_Pos);
	pSPIx->CR1 |= (SPI_DEVICE_MODE << SPI_CR1_MSTR_Pos);

	/** 3. Set Bus Mode (Full Duplex/Half Duplex/Simplex)	 */
	if (SPI_BUS_MODE == SPI_BUS_MODE_FULL_DUPLEX) { // Normal Mode
		//Clear BIDIMODE Bit in CR1 Reg
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE_Pos);
		// Also Clear the RXONLY Bit just for safety
		pSPIx->CR1 &= ~(1 << SPI_CR1_RXONLY_Pos);
	}else if(SPI_BUS_MODE == SPI_BUS_MODE_HALF_DUPLEX){
		//Set BIDIMODE Bit in CR1 Reg
		/** @todo Implement later you should make seperate API for BIDIOE Bit */
		pSPIx->CR1 |= (1 << SPI_CR1_BIDIMODE_Pos);
	}else if(SPI_BUS_MODE == SPI_BUS_MODE_SIMPLEX_RX){// Simplex Means either Tx only or Rx Only
		/** Clear this bit and use RX only for setting
		 * 	@note Master can be in RX only mode as well, its not necessary that master has to be in TX only in Simplex mode
		 * 	@note For simplex mode BIDIMODE Bit has to be Cleared
		 */
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE_Pos);
		pSPIx->CR1 |= (1 << SPI_CR1_RXONLY_Pos);
	}

	/** 4. Select the BR[2:0] bits to define the serial clock baud rate (see SPI_CR1 register). */
	pSPIx->CR1 &= ~(0x07 << 3); /*!< Clear the bits BR[2:0] first */
	pSPIx->CR1 |= (SPI_CLOCK_SPEED << 3); /*!< Set the bits @ref SPI_CLOCK_SPEED_MACROS*/

	/** 5. Select the CPOL and CPHA bits to define one of the four relationships between the
	* data transfer and the serial clock (see Figure 248). This step is not required when the
	* TI mode is selected.
    */
	pSPIx->CR1 &= ~(1 << SPI_CR1_CPHA_Pos); 	/*!< Clear CPHA */
	pSPIx->CR1 &= ~(1 << SPI_CR1_CPOL_Pos);		/*!< Clear CPOL */
	pSPIx->CR1 |= (SPI_CPHA << SPI_CR1_CPHA_Pos); 		/*!< Set CPHA */
	pSPIx->CR1 |= (SPI_CPOL << SPI_CR1_CPOL_Pos);		/*!< Set CPOL */

	/** 6. Set the DFF bit to define 8- or 16-bit data frame format */
	pSPIx->CR1 &= ~(1 << SPI_CR1_DFF_Pos); /*!< Clear DFF */
	pSPIx->CR1 |= (SPI_FRAME_SIZE << SPI_CR1_DFF_Pos); /*!< Set DFF */

	/** 7. Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format. */
	pSPIx->CR1 &= ~(1 << SPI_CR1_LSBFIRST_Pos);
	pSPIx->CR1 |= (SPI_BIT_ORDER << SPI_CR1_LSBFIRST_Pos);

	/** 8. If the NSS pin is required in input mode, in hardware mode, connect the NSS pin to a
	* high-level signal during the complete byte transmit sequence. In NSS software mode,
	* set the SSM and SSI bits in the SPI_CR1 register. If the NSS pin is required in output
	* mode, the SSOE bit only should be set. This step is not required when the TI mode is
	* selected.
	*/
	pSPIx->CR1 &= ~(1 << SPI_CR1_SSM_Pos); // Clear the SSM Bit in CR1 Reg
	pSPIx->CR1 |= (SPI_SSM_SETTING << SPI_CR1_SSM_Pos);// Set the bit

	pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE_Pos);	// Clear the SSOE Bit in CR2 Reg
	pSPIx->CR2 |= (SPI_SSOE << SPI_CR2_SSOE_Pos);// Set the bit

	/** 9. Set the FRF bit in SPI_CR2 to select the TI protocol for serial communications */
	/**@TODO implement CRC_EN and FRF */
}

void SPIx_DeInit(SPIx_RegDef_t *pSPIx)
{
    RCC_RegDef_t *pRCC = RCC;

    if (pSPIx == SPI1)
    {
        pRCC->APB2RSTR |=  (1 << 12);   // Force reset
        pRCC->APB2RSTR &= ~(1 << 12);   // Release reset
    }
    else if (pSPIx == SPI2)
    {
        pRCC->APB1RSTR |=  (1 << 14);   // Force reset
        pRCC->APB1RSTR &= ~(1 << 14);   // Release reset
    }
    else if (pSPIx == SPI3)
    {
        pRCC->APB1RSTR |=  (1 << 15);   // Force reset
        pRCC->APB1RSTR &= ~(1 << 15);   // Release reset
    }

    /** 2. Disable peripheral clock to save power */
       if (pSPIx == SPI1)
       {
           pRCC->APB2ENR &= ~(1 << 12);
       }
       else if (pSPIx == SPI2)
       {
           pRCC->APB1ENR &= ~(1 << 14);
       }
       else if (pSPIx == SPI3)
       {
           pRCC->APB1ENR &= ~(1 << 15);
       }
}

void SPIx_Peri_Control(SPIx_RegDef_t *pSPIx, uint8_t EN_DI){
	if(EN_DI == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE_Pos);
	}else{
		//	1. Wait until TXE=1
		while(!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));
		// 	2. Then wait until BSY=0
		while(SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_BSY));
		// 	3. The Disable the SPI
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE_Pos);
	}
}

uint8_t SPIx_GetFlagStatus(SPIx_RegDef_t *pSPIx, uint32_t FlagName) {
	return (uint8_t) (((pSPIx->SR) >> FlagName) & (0x01U));
}

void SPIx_SendData_Blocking(SPIx_RegDef_t *pSPIx, uint8_t* pTX_Data_Buffer, uint32_t Len_Byte){
	/**@TODO Edge case in 16 Bit mode what if user sends odd bytes */
	while (Len_Byte > 0) {
		// Wait until TXE = 1
		while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));
		//Check the data format
		if (pSPIx->CR1 & (1U << SPI_CR1_DFF_Pos)) {   // Frame Size = 16
			pSPIx->DR = *((uint16_t*) pTX_Data_Buffer);
			pTX_Data_Buffer += 2;
			Len_Byte -= 2;
		} else {   // Frame Size = 8
			pSPIx->DR = *pTX_Data_Buffer;
			pTX_Data_Buffer++;
			Len_Byte--;
		}
	}


    /**
     * After writing ALL data, wait for:
     * TXE = 1 → DR empty
     * BSY = 0 → last bit fully shifted out
     */
    while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));
    while  ( SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_BSY));
}

void SPIx_ReceiveData_Blocking(SPIx_RegDef_t *pSPIx, uint8_t *pRX_Data_Buffer, uint32_t Len_Byte)
{
	/**@todo Edge case in 16 Bit mode what if user sends odd bytes */
    while (Len_Byte > 0)
    {
        if(pSPIx->CR1 & (1U << SPI_CR1_DFF_Pos)){/** 16 Bit SPI */
        	/** 2. Wait for TXE = 1 */
        	while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));

        	/** 3. Dummy write */
        	pSPIx->DR = (uint16_t)0xFFFF;

        	/** 4. Wait for RXNE = 1 */
        	while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_RXNE));

        	/** 5. Read received byte */
        	*(uint16_t*)pRX_Data_Buffer = (uint16_t)pSPIx->DR;
        	pRX_Data_Buffer+=2;
        	Len_Byte-=2;
        }else{/** 8 Bit SPI */
        	/** 2. Wait for TXE = 1 */
        	while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));

        	/** 3. Dummy write */
        	pSPIx->DR = (uint8_t)0xFF;

        	/** 4. Wait for RXNE = 1 */
        	while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_RXNE));

        	/** 5. Read received byte */
        	*pRX_Data_Buffer = (uint8_t)pSPIx->DR;
        	pRX_Data_Buffer++;
        	Len_Byte--;
        }
    }

    /** 6. Wait for BSY to clear */
    while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));
    while (SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_BSY));
}

void SPIx_IRQConfig(uint8_t IRQNumber, uint8_t irq_priority){
	uint8_t IPR_Reg_Number = IRQNumber / 4;
	uint8_t IRQ_Pos = (IRQNumber % 4) * 8;
	NVIC_RegDef_t *pNVIC = (NVIC_RegDef_t *)NVIC_BASEADDR;
	irq_priority &= 0x0F; // Masking the priority
	if(IRQNumber == IRQ_NUM_SPI1 || IRQNumber == IRQ_NUM_SPI2 || IRQNumber == IRQ_NUM_SPI3 ){
		pNVIC->IPR[IPR_Reg_Number] &= ~(0xFF << IRQ_Pos);
		pNVIC->IPR[IPR_Reg_Number] |= (((uint32_t)irq_priority) << (IRQ_Pos + 4)); // We Just have to write upper 4 bits
	}else {
		return ;
	}
}

void SPIx_IRQControl(uint8_t IRQNumber, uint8_t EN_DI){
	//1. Check if IRQ is not spi related, if not return
	if (IRQNumber != IRQ_NUM_SPI1 &&
		IRQNumber != IRQ_NUM_SPI2 &&
		IRQNumber != IRQ_NUM_SPI3) {
		return;
	}

	uint32_t reg_Idx = IRQNumber / 32;
	uint32_t bit_position = IRQNumber % 32;
	if(EN_DI == ENABLE){
		// Enable interrupt in NVIC using ISER
		NVIC->ISER[reg_Idx] |= (1U << bit_position);
	}else{
		// To disable the interrupt write 1 to ICER register
		NVIC->ICER[reg_Idx] |= (1U << bit_position);
		// Also clear the pending interrupt using ICPR
		NVIC->ICPR[reg_Idx] |= (1U << bit_position);
	}
}

void SPIx_PeripheralInterruptControl(SPIx_RegDef_t *pSPIx, uint8_t ITType, uint8_t EN_DI){
	if (EN_DI) {
		if (ITType == SPI_IT_TYPE_TXE) {
			pSPIx->CR2 |= (1U << SPI_CR2_TXEIE_Pos);
		} else if (ITType == SPI_IT_TYPE_RXNE) {
			pSPIx->CR2 |= (1U << SPI_CR2_RXNEIE_Pos);
		} else if (ITType == SPI_IT_TYPE_ERR) {
			pSPIx->CR2 |= (1U << SPI_CR2_ERRIE_Pos);
		}
	} else {
		if (ITType == SPI_IT_TYPE_TXE) {
			pSPIx->CR2 &= ~(1U << SPI_CR2_TXEIE_Pos);
		} else if (ITType == SPI_IT_TYPE_RXNE) {
			pSPIx->CR2 &= ~(1U << SPI_CR2_RXNEIE_Pos);
		} else if (ITType == SPI_IT_TYPE_ERR) {
			pSPIx->CR2 &= ~(1U << SPI_CR2_ERRIE_Pos);
		}
	}
}

uint8_t SPIx_SendDataIT(SPIx_Handle_t *pHandle, uint8_t *pTxBuf, uint32_t Len){
	/** @todo right now assuming 8 bit transfer, modify for 16 bit also. **/
	//0. Basic Checks first
	if(pHandle == NULL || pTxBuf == NULL || Len == 0 ){
		return SPI_INVALID_PARAM;
	}
	if(pHandle->TxState == SPI_STATE_BUSY_IN_TX || pHandle->RxState == SPI_STATE_BUSY_IN_RX){
		return SPI_BUSY;
	}
	//1. Save TXBuffer and Length Info in some global variable
	pHandle->pTXBuffer = pTxBuf;
	pHandle->TXLen = Len;

	//2. Mark the SPI as Busy in transmission so that no other code can
	// take over the SPI peripheral until transmission is over
	pHandle->TxState = SPI_STATE_BUSY_IN_TX;
	//3. Enable the TXEIE control bit in the CR2 reg to generate interrupt whenever the TX buffer of the corresponding
	// SPI is empty (i.e. Whenever the TXE flag is set in the status register)
	SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_TXE, ENABLE);
	return SPI_TXRX_SUCCESS;
	//4. @todo Data Transmission will be handled by the ISR code
}

uint8_t SPIx_ReceiveDataIT(SPIx_Handle_t *pHandle, uint8_t *pRxBuf, uint32_t Len){
	/** @todo right now assuming 8 bit receive, modify for 16 bit also. **/
	//0. Basic Check first
	if(pHandle->TxState == SPI_STATE_BUSY_IN_TX || pHandle->RxState == SPI_STATE_BUSY_IN_RX){
		return SPI_BUSY;
	}
	if(pHandle == NULL || pRxBuf == NULL || Len ==0){
		return SPI_INVALID_PARAM;
	}
	//1. Save the RxBuffer and Length info in some global variable
	pHandle->RXLen = Len;
	pHandle->pRXBuffer = pRxBuf;

	//2. Mark the SPI as Busy in Rx so that no other code can
	// take over the SPI peripheral until the rx is over
	pHandle->RxState = SPI_STATE_BUSY_IN_RX;
	//3. Enable the RXNEIE control bit in the CR2 reg to generate interrupt whenever the RX buffer of the
	//corresponding SPI is not empty (i.e. Whenever the RXNE flag is set in the status register)
	SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_RXNE, ENABLE);
	return SPI_TXRX_SUCCESS;
	//4. @todo Data Reception will be handled by the ISR code
}

void SPIx_IRQHandling(SPIx_Handle_t *pHandle){

    /* basic sanity check */
    if (pHandle == NULL || pHandle->pSPIx == NULL) {
        return;
    }


	//0. Extract the status status flags
	//uint8_t txe_flag = (pHandle->pSPIx->SR & (1 << SPI_SR_TXE_Pos));
	uint8_t txe_flag = SPIx_GetFlagStatus(pHandle->pSPIx, SPI_STATUS_FLAG_TXE);
	//uint8_t rxne_flag = (pHandle->pSPIx->SR & (1 << SPI_SR_RXNE_Pos));
	uint8_t rxne_flag = SPIx_GetFlagStatus(pHandle->pSPIx, SPI_STATUS_FLAG_RXNE);
	//uint8_t ovr_flag = (pHandle->pSPIx->SR & (1 << SPI_SR_OVR_Pos));
	uint8_t ovr_flag = SPIx_GetFlagStatus(pHandle->pSPIx, SPI_STATUS_FLAG_OVR);
	uint8_t crc_err_flag = SPIx_GetFlagStatus(pHandle->pSPIx, SPI_STATUS_FLAG_CRCERR);
	uint8_t modf_flag = SPIx_GetFlagStatus(pHandle->pSPIx, SPI_STATUS_FLAG_MODF);

	uint8_t txeie_bit = (pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE_Pos));
	uint8_t rxneie_bit = (pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE_Pos));
	uint8_t errie_bit = (pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE_Pos));


	// Check TXE flag
	if(txe_flag && txeie_bit){
		SPI_Tx_IRQ_Helper(pHandle);
	}

	// Check RXNE flag
	if(rxne_flag && rxneie_bit){
		SPI_Rx_IRQ_Helper(pHandle);
	}

	// Check Overrun Error
	if (ovr_flag && errie_bit)
	{
		SPI_OVR_Err_IRQ_Helper(pHandle);
	}

	// Check CRC Error
	if (crc_err_flag && errie_bit)
	{
		SPI_CRC_Err_IRQ_Helper(pHandle);
	}

	// Check Master mode fault Error
	if (modf_flag && errie_bit)
	{
		SPI_MODF_Err_IRQ_Helper(pHandle);
	}
}

void SPI_CloseTransmission(SPIx_Handle_t *pHandle){
	if (pHandle == NULL) {
		return;
	}
	SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_TXE, DISABLE);
	pHandle->TxState = SPI_STATE_READY;
	pHandle->TXLen = 0;
	pHandle->pTXBuffer = NULL;
	SPI_ApplicationEventCallback(pHandle, SPI_EVENT_TX_CMPLT);
}

void SPI_CloseReception(SPIx_Handle_t *pHandle){
	if (pHandle == NULL) {
		return;
	}
	SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_RXNE, DISABLE);
	pHandle->RxState = SPI_STATE_READY;
	pHandle->RXLen = 0;
	pHandle->pRXBuffer = NULL;
	SPI_ApplicationEventCallback(pHandle, SPI_EVENT_RX_CMPLT);
}

/** Weak default implementation; application should provide its own version.
 *
 * Place this in stm32f407xx_spi.c (or another driver C file). The `weak`
 * attribute allows the linker to replace this with the application's
 * implementation if provided.
 */
__attribute__((weak)) void SPI_ApplicationEventCallback(SPIx_Handle_t *pHandle, uint8_t AppEv)
{
    /* Default: do nothing. Application may override to handle events. */
    (void)pHandle;
    (void)AppEv;
}
