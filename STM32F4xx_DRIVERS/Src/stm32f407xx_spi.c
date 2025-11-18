/*
 * stm32f407xx_spi.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ratho
 */

#include "stm32f407xx_spi.h"

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
	if (SPI_BUS_MODE == SPI_DEVICE_BUS_MODE_FULL_DUPLEX) { // Normal Mode
		//Clear BIDIMODE Bit in CR1 Reg
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE_Pos);
		// Also Clear the RXONLY Bit just for safety
		pSPIx->CR1 &= ~(1 << SPI_CR1_RXONLY_Pos);
	}else if(SPI_BUS_MODE == SPI_DEVICE_BUS_MODE_HALF_DUPLEX){
		//Set BIDIMODE Bit in CR1 Reg
		/** @todo Implement later you should make seperate API for BIDIOE Bit */
		pSPIx->CR1 |= (1 << SPI_CR1_BIDIMODE_Pos);
	}else if(SPI_BUS_MODE == SPI_DEVICE_BUS_MODE_SIMPLEX){// Simplex Means either Tx only or Rx Only
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
	/**@todo implement CRC_EN and FRF */
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

void SPIx_SendData_Blocking(SPIx_RegDef_t *pSPIx, uint8_t* pData, uint32_t Len){
	while(Len>0){
		// Wait until TXE = 1
		while (!SPIx_GetFlagStatus(pSPIx, SPI_STATUS_FLAG_TXE));
		//Check the data format
		if(pSPIx->CR1 & (1U << SPI_CR1_DFF_Pos)){// Frame Size = 16
			pSPIx->DR = *((uint16_t*) pData);
			pData += 2;
			Len -= 2;
		}else{// Frame Size = 8
			pSPIx->DR = *pData;
			pData++;
			Len--;
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
