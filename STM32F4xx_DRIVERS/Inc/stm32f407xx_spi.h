/*
 * stm32f407xx_spi.h
 *
 *  Created on: Nov 17, 2025
 *      Author: ratho
 */

#ifndef INC_STM32F407XX_SPI_H_
#define INC_STM32F407XX_SPI_H_
#include "stm32f407xx.h"

/**
 * @defgroup SPI_DRIVER_DEVELOPEMNT SPI Driver
 * @brief SPI Driver Development
 * @{
 */

/**
 * @defgroup SPI_CONFIG_MACROS SPI Configuration Macros
 * @brief SPI configuration Macros
 * @{
 */

	/**
	 * @defgroup SPI_DEVICE_MODE_MACROS SPI Device Mode Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI_DEVICE_MODE configuration Macros
	 * @{
	 */
		#define SPI_DEVICE_MODE_MASTER  1  /*!< SPI in Master mode */
		#define SPI_DEVICE_MODE_SLAVE   0  /*!< SPI in Slave mode  */
	/** @} */   // end of SPI_DEVICE_MODE_MACROS

	/**
	 * @defgroup SPI_BUS_MODE_MACROS SPI Device Bus Mode Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI_DEVICE_BUS_MODE configuration Macros
	 * @{
	 */
		#define SPI_BUS_MODE_FULL_DUPLEX  	0  /*!< 2-line full duplex */
		#define SPI_BUS_MODE_HALF_DUPLEX  	1  /*!< 1-line half duplex */
		#define SPI_BUS_MODE_SIMPLEX_RX  	2  /*!< 1-line simplex (RX/TX only) */
	/** @} */   // end of SPI_BUS_MODE_MACROS

	/**
	 * @defgroup SPI_CLOCK_SPEED_MACROS SPI Clock Speed Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI_CLOCK_SPEED configuration Macros
	 * @{
	 */
		#define	SPI_CLOCK_SPEED_BY_2	 0 /*!< Peripheral clk / 2   */
		#define	SPI_CLOCK_SPEED_BY_4	 1 /*!< Peripheral clk / 4   */
		#define	SPI_CLOCK_SPEED_BY_8	 2 /*!< Peripheral clk / 8   */
		#define	SPI_CLOCK_SPEED_BY_16	 3 /*!< Peripheral clk / 16  */
		#define	SPI_CLOCK_SPEED_BY_32	 4 /*!< Peripheral clk / 32  */
		#define	SPI_CLOCK_SPEED_BY_64	 5 /*!< Peripheral clk / 64  */
		#define	SPI_CLOCK_SPEED_BY_128	 6 /*!< Peripheral clk / 128 */
		#define	SPI_CLOCK_SPEED_BY_256	 7 /*!< Peripheral clk / 256 */
	/** @} */   // end of SPI_CLOCK_SPEED_MACROS

	/**
	 * @defgroup SPI_CPOL_MACROS SPI CPOL Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI_CPOL configuration Macros
	 * @{
	 */
		#define SPI_CPOL_HIGH 	1 /*!< Clock idle state is HIGH */
		#define SPI_CPOL_LOW 	0 /*!< Clock idle state is LOW  */
	/** @} */   // end of SPI_CPOL_MACROS

	/**
	 * @defgroup SPI_CPHA_MACROS SPI CPHA Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI_CPHA configuration Macros
	 * @{
	 */
		#define SPI_CPHA_FIRST_EDGE     0 /*!< Data sampled on first (leading) clock edge  */
		#define SPI_CPHA_SECOND_EDGE    1 /*!< Data sampled on second (trailing) clock edge */
	/** @} */   // end of SPI_CPHA_MACROS

	/**
	 * @defgroup SPI_FRAME_SIZE_MACROS SPI Frame Size Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI data frame size configuration Macros
	 * @{
	 */
		#define SPI_FRAME_SIZE_8_BITS     0 /*!< 8-bit data frame size  */
		#define SPI_FRAME_SIZE_16_BITS    1 /*!< 16-bit data frame size */
	/** @} */   // end of SPI_FRAME_SIZE_MACROS

	/**
	 * @defgroup SPI_SSM_MACROS	SPI SSM Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI Software Slave Management configuration Macros
	 * @{
	 */
		#define SPI_SSM_SETTING_DI    0 /*!< Software slave management disabled */
		#define SPI_SSM_SETTING_EN    1 /*!< Software slave management enabled  */
	/** @} */   // end of SPI_SSM_MACROS

	/**
	 * @defgroup SPI_BIT_ORDER_MACROS SPI Bit Order Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI Bit Order configuration Macros
	 * @{
	 */
		#define SPI_BIT_ORDER_LSB_FIRST    1 /*!< Data transmitted LSB first */
		#define SPI_BIT_ORDER_MSB_FIRST    0 /*!< Data transmitted MSB first */
	/** @} */   // end of SPI_BIT_ORDER_MACROS

	/**
	 * @defgroup SPI_SSOE_MACROS SPI SSOE Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI Slave Select Output Enable (SSOE) configuration Macros
	 * @{
	 */
		#define SPI_SSOE_EN   1 /*!< NSS output is driven by hardware (Master mode) */
		#define SPI_SSOE_DI   0 /*!< NSS output is disabled, software/GPIO controls NSS */
	/** @} */   // end of SPI_SSOE_MACROS

	/**
	 * @defgroup SPI_CRC_MACROS SPI CRC Configuration Macros
	 * @ingroup SPI_CONFIG_MACROS
	 * @brief SPI CRC calculation enable/disable configuration Macros
	 * @{
	 */
		#define SPI_CRC_ENABLE    1 /*!< CRC calculation enabled  */
		#define SPI_CRC_DISABLE   0 /*!< CRC calculation disabled */
	/** @} */   // end of SPI_CRC_MACROS

/** @} */   // end of SPI_CONFIG_MACROS



/**
 * @defgroup SPI_Config_Struct SPI Configuration Structure definition
 * @brief SPI configuration structure
 * @note  Used to configure SPI peripheral before enabling it
 * @{
 */
typedef struct
{
    uint8_t SPI_DEVICE_MODE;  /*!< Master or Slave mode selection.             Refer @ref SPI_DEVICE_MODE_MACROS        */
    uint8_t SPI_BUS_MODE;     /*!< Full-duplex / Half-duplex / Rx-only mode.   Refer @ref SPI_BUS_MODE_MACROS    */
    uint8_t SPI_CLOCK_SPEED;  /*!< Baud rate configuration (BR[2:0] bits).     Refer @ref SPI_CLOCK_SPEED_MACROS        */
    uint8_t SPI_CPOL;         /*!< Clock polarity selection.                   Refer @ref SPI_CPOL_MACROS               */
    uint8_t SPI_CPHA;         /*!< Clock phase selection.                      Refer @ref SPI_CPHA_MACROS               */
    uint8_t SPI_FRAME_SIZE;   /*!< 8-bit or 16-bit data frame format.          Refer @ref SPI_FRAME_SIZE_MACROS         */
    uint8_t SPI_SSM_SETTING;  /*!< Software slave management enable/disable.   Refer @ref SPI_SSM_MACROS                */
    uint8_t SPI_BIT_ORDER;    /*!< MSB-first or LSB-first transmission.        Refer @ref SPI_BIT_ORDER_MACROS          */
    uint8_t SPI_SSOE;         /*!< SSO output enable (Master mode only).       Refer @ref SPI_SSOE_MACROS               */
    uint8_t SPI_CRC_EN;       /*!< CRC calculation enable/disable.             Refer @ref SPI_CRC_MACROS                */
} SPIx_Config_t;
/** @} */ // End of SPIx_Config_t Structure Definition


/**
 * @defgroup SPI_Handle_Struct SPI Handle Structure definition
 * @brief SPI handle structure
 * @note  Contains SPI instance and its configuration
 * @{
 */
typedef struct
{
    SPIx_RegDef_t 	*pSPIx;   	/*!< Pointer to SPI peripheral base address */
    SPIx_Config_t  	SPI_CONFIG; 	/*!< SPI configuration settings */

    volatile uint8_t		*pTXBuffer;
    volatile uint32_t 		TXLen;
    volatile uint8_t 		TxState;

    volatile uint8_t		*pRXBuffer;
    volatile uint32_t 		RXLen;
    volatile uint8_t 		RxState;


} SPIx_Handle_t;
/** @} */ // End of SPIx_Handle_t Structure Definition

/**
 * @defgroup SPI_STATUS_FLAG_MACROS SPI Status Flag Macros
 * @brief SPI Status Flag macros
 * @{
 */

	/**
	 * @brief Receive buffer not empty (bit 0)
	 * @details Status: Data available to read in receive buffer.
	 *          Set when receive buffer contains valid data ready to be read.
	 *          Cleared automatically when data register is read.
	 */
	#define SPI_STATUS_FLAG_RXNE       0

	/**
	 * @brief Transmit buffer empty (bit 1)
	 * @details Status: Ready to transmit new data.
	 *          Set when transmit buffer is empty and ready to accept new data.
	 *          Cleared automatically when data is written to data register.
	 */
	#define SPI_STATUS_FLAG_TXE        1

	/**
	 * @brief Channel side (bit 2)
	 * @details Status: Indicates which audio channel is active (I2S mode only).
	 *          Used in I2S mode only. Indicates current audio channel:
	 *          0 = Left channel, 1 = Right channel. Not used in SPI mode.
	 */
	#define SPI_STATUS_FLAG_CHSIDE     2

	/**
	 * @brief Underrun error (bit 3)
	 * @details Status: Slave couldn't provide data in time (error condition).
	 *          Set in slave mode when master requests data but transmit buffer is empty.
	 *          Cleared by reading status register then writing to data register.
	 */
	#define SPI_STATUS_FLAG_UDR        3

	/**
	 * @brief CRC error (bit 4)
	 * @details Status: Data corruption detected (error condition).
	 *          Set when received CRC doesn't match calculated CRC.
	 *          Only applicable when hardware CRC is enabled. Cleared by software.
	 */
	#define SPI_STATUS_FLAG_CRCERR     4

	/**
	 * @brief Mode fault (bit 5)
	 * @details Status: Multi-master conflict detected (error condition).
	 *          Set when NSS pin is pulled low while in master mode, causing automatic
	 *          switch to slave mode. Cleared by reading status then writing config register.
	 */
	#define SPI_STATUS_FLAG_MODF       5

	/**
	 * @brief Overrun error (bit 6)
	 * @details Status: Received data was lost due to unread previous data (error condition).
	 *          Set when new data is received while previous data is unread (data loss).
	 *          Cleared by reading data register then reading status register.
	 */
	#define SPI_STATUS_FLAG_OVR        6

	/**
	 * @brief Busy (bit 7)
	 * @details Status: SPI communication in progress.
	 *          Set when SPI communication is ongoing or transmit buffer is not empty.
	 *          Cleared automatically when communication completes.
	 */
	#define SPI_STATUS_FLAG_BSY        7

	/**
	 * @brief Frame format error (bit 8)
	 * @details Status: Frame synchronization error occurred (error condition).
	 *          Set when frame format/synchronization error occurs (TI mode).
	 *          Cleared by reading status register.
	 */
	#define SPI_STATUS_FLAG_FRE        8

/**@}*/ // End of SPI_STATUS_FLAG_MACROS

/**
 * @defgroup SPI_API_PROTOTYPES SPI API Prototypes
 * @brief SPI API Prototypes
 * @note  Contains SPI API Prototypes
 * @{
 */

/**
 * @brief   Initializes the SPI peripheral based on the configuration provided
 *          in the SPI handle structure.
 *
 * @param   pSPI_Handle : Pointer to SPI handle structure which contains
 *                        SPI register base address and SPI configuration settings.
 *
 * @note    This function does NOT enable the SPI peripheral. It only configures
 *          the control registers. User must call SPIx_PeripheralControl()
 *          to enable the peripheral after initialization.
 *
 * @return  None
 */
void SPIx_Init(SPIx_Handle_t *pSPI_Handle);

/**
 * @brief   Resets the SPI peripheral registers to their default reset values.
 *
 * @param   pSPIx : Pointer to the SPI peripheral base address
 *                  (e.g., SPI1, SPI2, SPI3).
 *
 * @note    This function uses the RCC reset mechanism to reset the peripheral.
 *          After reset, the SPI clock is automatically disabled.
 *
 * @return  None
 */
void SPIx_DeInit(SPIx_RegDef_t *pSPIx);

/**
 * @brief   Enables or disables the SPI peripheral.
 *
 * @param   pSPIx : Pointer to the SPI peripheral base address
 *                  (e.g., SPI1, SPI2, SPI3).
 *
 * @param   EN_DI : Enable/Disable macro.
 *                  Pass ENABLE to enable SPI peripheral.
 *                  Pass DISABLE to disable SPI peripheral.
 *
 * @note    This function sets or clears the SPE bit in SPI_CR1 register.
 *
 * @return  None
 */
void SPIx_Peri_Control(SPIx_RegDef_t *pSPIx, uint8_t EN_DI);

/**
 * @brief   Reads the status of a specific SPI status flag.
 *
 * @param   pSPIx[in]     : Pointer to the SPI peripheral base address
 *                      (e.g., SPI1, SPI2, SPI3).
 *
 * @param   FlagName[in]  	: Name of the flag to check. This must be one of the
 *                      	predefined SPI flag macros, such as:
 *                      	- SPI_TXE_FLAG
 *                      	- SPI_RXNE_FLAG
 *                      	- SPI_BUSY_FLAG
 *                      	@ref SPI_STATUS_FLAG_MACROS
 *
 * @note    This function reads the SPI_SR register and checks the bit
 *          corresponding to the selected flag.
 *
 * @return  uint8_t   : FLAG_SET   (1) if the flag is set
 *                      FLAG_RESET (0) if the flag is cleared
 */
uint8_t SPIx_GetFlagStatus(SPIx_RegDef_t *pSPIx, uint32_t FlagName);

/**
 * @brief  Send data over the specified SPI peripheral.
 *
 * This function transmits a block of data through the given SPI instance.
 * It writes the provided buffer into the SPI data register until the
 * specified length is sent.
 *
 * @param[in]  pSPIx   Pointer to the SPI peripheral register definition structure.
 * @param[in]  pData   Pointer to the data buffer containing bytes to be transmitted.
 * @param[in]  Len     Length of the data buffer in bytes.
 *
 * @note  This is a blocking call. The function waits until all data
 *        has been transmitted before returning.
 *
 * @retval None
 */
void SPIx_SendData_Blocking(SPIx_RegDef_t *pSPIx, uint8_t* pTX_Data_Buffer, uint32_t Len_Byte);
/**
 * @brief  Receive data from the specified SPI peripheral in blocking mode.
 *
 * This function receives a block of data from the given SPI instance
 * using a polling-based (blocking) mechanism. In master mode, dummy writes
 * are performed to generate the required SPI clock for data sampling. The
 * function waits until each byte is available in the receive buffer before
 * reading it from the data register.
 *
 * The function returns only after all requested bytes have been received.
 * It does not handle interrupt- or DMA-based transfers.
 *
 * @param[in]  pSPIx     Pointer to the SPI peripheral register definition structure.
 * @param[out] pData     Pointer to the receive buffer where incoming data will be stored.
 * @param[in]  Len       Number of bytes to be received.
 *
 * @note Ensure the SPI peripheral is properly configured and enabled before
 *       calling this function. In master mode, NSS should be driven low before
 *       invoking this API and released high after the transfer completes.
 *
 * @note This API internally clears Overrun (OVR) errors for safe operation.
 *
 * @retval None
 */
void SPIx_ReceiveData_Blocking(SPIx_RegDef_t *pSPIx, uint8_t* pRX_Data_Buffer, uint32_t Len_Byte);

/**
 * @brief  Configure the priority of a given SPI interrupt in the NVIC.
 *
 * This function sets the interrupt priority for the specified SPI IRQ number
 * in the Nested Vectored Interrupt Controller (NVIC). It does not enable or
 * disable the interrupt; it only assigns the priority value to the corresponding
 * NVIC IPR (Interrupt Priority Register) field.
 *
 * @param[in] IRQNumber      The IRQ number associated with the SPI peripheral
 *                           (e.g., IRQ_NUM_SPI1, IRQ_NUM_SPI2, IRQ_NUM_SPI3).
 *
 * @param[in] irq_priority   Priority value (0–15). Only the upper 4 bits of each
 *                           NVIC priority byte are implemented on Cortex-M MCUs,
 *                           so only the lower 4 bits of @p irq_priority are used.
 *
 * @note  This API does NOT enable the interrupt. Use @ref SPIx_IRQEnable()
 *        to enable or disable the interrupt in NVIC ISER/ICER registers.
 *
 * @note  This API DOES NOT configure SPI peripheral interrupt bits (CR2).
 *        For enabling TXEIE/RXNEIE/ERRIE, use the SPI peripheral configuration APIs.
 */
void SPIx_IRQConfig(uint8_t IRQNumber, uint8_t irq_priority);

/**
 * @brief  Enable or disable the given SPI IRQ in the NVIC.
 *
 * This function controls the interrupt routing at the processor (NVIC) level.
 * It does NOT configure SPI peripheral CR2 (TXEIE/RXNEIE/ERRIE); it only
 * enables or disables the interrupt line in NVIC ISER/ICER registers.
 *
 * @param[in] IRQNumber   IRQ number corresponding to the SPI peripheral
 *                        (e.g., IRQ_NUM_SPI1, IRQ_NUM_SPI2, IRQ_NUM_SPI3).
 *
 * @param[in] EN_DI       Enable/Disable interrupt line:
 *                        - ENABLE  : Enable NVIC interrupt
 *                        - DISABLE : Disable NVIC interrupt
 */
void SPIx_IRQControl(uint8_t IRQNumber, uint8_t EN_DI);

/**
 * @brief  Enable or disable specified SPI peripheral interrupts (CR2).
 *
 * @param[in] pSPIx   Pointer to SPI registers (SPI1, SPI2, ...).
 * @param[in] ITType  Combination (OR) of SPI_IT_TXE, SPI_IT_RXNE, SPI_IT_ERR Refer @ref SPI_IT_TYPE.
 * @param[in] EN_DI   ENABLE (non-zero) to set bits, DISABLE (0) to clear bits.
 *
 * @note This controls only the SPI peripheral (CR2). NVIC must be enabled/disabled
 *       separately using SPIx_IRQControl()/SPIx_IRQEnable().
 * @note Typical usage: configure priority, enable the correct CR2 bits, then enable NVIC.
 */

void SPIx_PeripheralInterruptControl(SPIx_RegDef_t *pSPIx, uint8_t ITType, uint8_t EN_DI);

/**
 * @brief  Start a non-blocking (interrupt-driven) transmit on the SPI peripheral.
 *
 * This function begins an interrupt-driven transmit using the SPI handle state.
 * It programs the handle with the transmit buffer and length, sets the handle
 * state to BUSY, and enables the SPI peripheral TXE interrupt (CR2: TXEIE).
 *
 * After this function returns the transfer is performed in IRQ context. The
 * application is notified when the transfer completes via
 * SPI_ApplicationEventCallback(..., SPI_EVENT_TX_CMPLT).
 *
 * Typical safe call sequence:
 *   1. SPIx_IRQConfig(IRQ, priority);
 *   2. SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_TXEIE, ENABLE);
 *   3. SPIx_IRQControl(IRQ, ENABLE);
 *   4. SPIx_SendDataIT(pHandle, pTxBuf, Len);
 *
 * @param[in,out]  pHandle    Pointer to the SPI handle which holds peripheral and state.
 * @param[in]      pTxBuf     Pointer to the transmit buffer. MUST remain valid until
 *                            the SPI_EVENT_TX_CMPLT callback is invoked.
 * @param[in]      Len        Number of bytes to transmit (for DFF=16 handle as number of bytes).
 *
 * @retval 0  Success — transfer started.
 * @retval 1  Busy — transmit already in progress.
 * @retval 2  Invalid parameter (NULL handle or NULL buffer or Len == 0).
 *
 * @note  This function only enables the SPI peripheral interrupt (CR2 TXEIE). The
 *        caller is responsible for enabling the corresponding NVIC line via
 *        SPIx_IRQConfig() + SPIx_IRQControl() (or do that earlier in init).
 * @note  The transmit completion callback is invoked from IRQ context — keep it short
 *        (set a flag or schedule work for the main loop).
 */
uint8_t SPIx_SendDataIT(SPIx_Handle_t *pHandle, uint8_t *pTxBuf, uint32_t Len);

/**
 * @brief  Start a non-blocking (interrupt-driven) receive on the SPI peripheral.
 *
 * This function begins an interrupt-driven receive using the SPI handle state.
 * It programs the handle with the receive buffer and length, sets the handle
 * state to BUSY, and enables the SPI peripheral RXNE interrupt (CR2: RXNEIE).
 *
 * In master mode the driver (or application) must provide clocking for the slave:
 * the driver may perform dummy TX writes in the ISR to generate SCK (implementation detail).
 *
 * When the requested number of bytes has been received the application will be
 * notified using SPI_ApplicationEventCallback(..., SPI_EVENT_RX_CMPLT).
 *
 * Typical safe call sequence:
 *   1. SPIx_IRQConfig(IRQ, priority);
 *   2. SPIx_PeripheralInterruptControl(pHandle->pSPIx, SPI_IT_TYPE_RXNEIE, ENABLE);
 *   3. SPIx_IRQControl(IRQ, ENABLE);
 *   4. SPIx_ReceiveDataIT(pHandle, pRxBuf, Len);
 *
 * @param[in,out]  pHandle    Pointer to the SPI handle which holds peripheral and state.
 * @param[out]     pRxBuf     Pointer to the receive buffer. Must remain valid until
 *                            the SPI_EVENT_RX_CMPLT callback.
 * @param[in]      Len        Number of bytes to receive (for DFF=16 handle as number of bytes).
 *
 * @retval 0  Success — receive started.
 * @retval 1  Busy — receive already in progress.
 * @retval 2  Invalid parameter (NULL handle or NULL buffer or Len == 0).
 *
 * @note  The driver may perform dummy writes (0xFF) to generate clocks in master mode.
 * @note  This function only enables the SPI peripheral RXNEIE bit; NVIC enabling must
 *        be handled by the caller (SPIx_IRQConfig + SPIx_IRQControl).
 * @note  The completion callback is invoked from IRQ context.
 */
uint8_t SPIx_ReceiveDataIT(SPIx_Handle_t *pHandle, uint8_t *pRxBuf, uint32_t Len);

/**
 * @brief  Handle all interrupt events for the given SPI peripheral.
 *
 * This function must be called from the actual SPI IRQ handler
 * (e.g., SPI1_IRQHandler). It services TXE, RXNE, and OVR interrupt
 * sources based on the state stored in the SPI handle.
 *
 * @param[in,out] pHandle   Pointer to the SPI handle structure associated
 *                          with the SPI peripheral generating the interrupt.
 *
 * @note This function runs in IRQ context. Keep callback handlers short
 *       and defer heavy processing to the main loop or a task.
 *
 * @retval None
 */
void SPIx_IRQHandling(SPIx_Handle_t *pHandle);

/**
  * @brief  Finalizes an ongoing SPI communication transaction by disabling interrupts
  * and resetting the handle state variables.
  * @param  pHandle: Pointer to a SPIx_Handle_t structure that contains
  * the configuration and communication state for the specified SPI.
  * @retval None
  */
void SPI_Close_Transfer(SPIx_Handle_t *pHandle);

/**
 * @brief  Application callback invoked by the SPI driver on asynchronous events.
 *
 * This callback is called from interrupt context by the SPI driver to notify
 * the application about important asynchronous events (transfer complete,
 * errors, etc.). The application SHOULD implement this function in its code
 * to handle events; otherwise the weak default implementation will be used.
 *
 * IMPORTANT:
 *  - This function is invoked from IRQ context. Keep the implementation short:
 *    set flags, toggle an LED, or post to an RTOS queue — do not perform long
 *    blocking operations or heavy processing inside this callback.
 *  - Any data buffers passed via the SPI handle remain valid only until the
 *    callback returns (unless otherwise documented).
 *
 * Typical AppEv values (define these in your header):
 *  - SPI_EVENT_TX_CMPLT  : Transmit completed successfully
 *  - SPI_EVENT_RX_CMPLT  : Receive completed successfully
 *  - SPI_EVENT_OVR_ERR   : Overrun error occurred
 *  - SPI_EVENT_CRC_ERR   : CRC error (if used)
 *
 * @param[in] pHandle  Pointer to the SPI handle that generated the event.
 *                     The handle contains peripheral instance and transfer state.
 * @param[in] AppEv    Event identifier (one of the SPI_EVENT_* constants).
 */
void SPI_ApplicationEventCallback(SPIx_Handle_t *pHandle, uint8_t AppEv);
/**
 * @brief  Gracefully terminate an ongoing SPI transmit interrupt operation.
 *
 * This function is called by the SPI driver when a TX interrupt-driven
 * transmission has completed, or may be called by the application to abort
 * an ongoing TX transfer.
 *
 * It performs the following actions:
 *   - Disables the TXE interrupt (TXEIE bit in CR2).
 *   - Resets the handle's TX state to @ref SPI_STATE_READY.
 *   - Clears internal TX buffer pointers and counters.
 *
 * @note  This function does NOT disable the SPI peripheral (SPE bit).
 *        It only stops the interrupt-driven transmission mechanism.
 *
 * @param[in,out] pHandle   Pointer to the SPI handle structure.
 *
 * @retval None
 */
void SPI_CloseTransmission(SPIx_Handle_t *pHandle);

/**
 * @brief  Gracefully terminate an ongoing SPI receive interrupt operation.
 *
 * This function is used by the SPI driver when an interrupt-driven RX transfer
 * completes, or can be invoked by the application to abort a receive sequence.
 *
 * It performs the following actions:
 *   - Disables the RXNE interrupt (RXNEIE bit in CR2).
 *   - Resets the RX state to @ref SPI_STATE_READY.
 *   - Clears internal RX buffer pointers and counters.
 *
 * @note  This function does NOT clear overrun (OVR) errors.
 *        OVR must be handled separately by the error ISR helper.
 *
 * @param[in,out] pHandle   Pointer to the SPI handle structure.
 *
 * @retval None
 */
void SPI_CloseReception(SPIx_Handle_t *pHandle);


/** @} */ // End of SPI_API_PROTOTYPES

/**
 * @defgroup SPI_BIT_POSITION_MACROS SPI Register Bit Position
 * @brief Bit position definitions for SPI peripheral registers.
 *
 * These macros provide the bit positions of all relevant control and status
 * fields within the SPI registers. They allow clean and readable register
 * access using shift operations.
 *
 * Example usage:
 * @code
 *   // Set the MSTR bit
 *   pSPIx->CR1 |= (1U << SPI_CR1_MSTR_Pos);
 *
 *   // Clear the SPE bit
 *   pSPIx->CR1 &= ~(1U << SPI_CR1_SPE_Pos);
 * @endcode
 *
 * @note These macros only define bit positions, not masks. Masks can be
 *       generated by shifting (1U << <bit>).
 *
 * @retval None
 * @{
 */

	/**
	 * @defgroup SPI_CR1_BIT_POSITIONS
	 * @brief Bit positions for SPI Control Register 1 (CR1).
	 *
	 * Used to configure clock, mode, and frame settings.
	 *
	 * @{
	 */

	#define SPI_CR1_CPHA_Pos        0U
	#define SPI_CR1_CPOL_Pos        1U
	#define SPI_CR1_MSTR_Pos        2U
	#define SPI_CR1_BR_Pos          3U   /*!< Baud rate (3 bits) */
	#define SPI_CR1_SPE_Pos         6U
	#define SPI_CR1_LSBFIRST_Pos    7U
	#define SPI_CR1_SSI_Pos         8U
	#define SPI_CR1_SSM_Pos         9U
	#define SPI_CR1_RXONLY_Pos      10U
	#define SPI_CR1_DFF_Pos         11U
	#define SPI_CR1_CRCNEXT_Pos     12U
	#define SPI_CR1_CRCEN_Pos       13U
	#define SPI_CR1_BIDIOE_Pos      14U
	#define SPI_CR1_BIDIMODE_Pos    15U

	/** @} */ // End of SPI_CR1_BIT_POSITIONS


	/**
	 * @defgroup SPI_CR2_BIT_POSITIONS
	 * @brief Bit positions for SPI Control Register 2 (CR2).
	 *
	 * Used to enable interrupts, DMA, and SS output.
	 *
	 * @note Use (1U << <macro>) to form masks.
	 *
	 * @{
	 */

	#define SPI_CR2_RXDMAEN_Pos     0U  /*!< RX DMA enable */
	#define SPI_CR2_TXDMAEN_Pos     1U  /*!< TX DMA enable */
	#define SPI_CR2_SSOE_Pos        2U  /*!< SS output enable */
	#define SPI_CR2_FRF_Pos         4U  /*!< Frame format */
	#define SPI_CR2_ERRIE_Pos       5U  /*!< Error interrupt enable */
	#define SPI_CR2_RXNEIE_Pos      6U  /*!< RX interrupt enable */
	#define SPI_CR2_TXEIE_Pos       7U  /*!< TX interrupt enable */

	/** @} */ // End of SPI_CR2_BIT_POSITIONS

	/**
	 * @defgroup SPI_SR_BIT_POSITIONS
	 * @brief Bit positions for SPI Status Register (SR).
	 *
	 * Used to check TX, RX, CRC, and error status.
	 *
	 * @{
	 */

	#define SPI_SR_RXNE_Pos         0U
	#define SPI_SR_TXE_Pos          1U
	#define SPI_SR_CHSIDE_Pos       2U
	#define SPI_SR_UDR_Pos          3U
	#define SPI_SR_CRCERR_Pos       4U
	#define SPI_SR_MODF_Pos         5U
	#define SPI_SR_OVR_Pos          6U
	#define SPI_SR_BSY_Pos          7U
	#define SPI_SR_FRE_Pos          8U

	/** @} */ // End of SPI_SR_BIT_POSITIONS

	/**
	 * @defgroup SPI_DR_BIT_POSITIONS
	 * @brief Bit positions for SPI Data Register (DR).
	 *
	 * Holds TX/RX data (16 bits).
	 *
	 * @{
	 */

	#define SPI_DR_DR_Pos           0U

	/** @} */ // End of SPI_DR_BIT_POSITIONS

	/**
	 * @defgroup SPI_CRCPR_BIT_POSITIONS
	 * @brief Bit position for CRC Polynomial Register.
	 *
	 * Defines CRC polynomial value.
	 *
	 * @{
	 */

	#define SPI_CRCPR_CRCPOLY_Pos   0U

	/** @} */ // End of SPI_CRCPR_BIT_POSITIONS

	/**
	 * @defgroup SPI_RXCRCR_BIT_POSITIONS
	 * @brief Bit position for RX CRC Register.
	 *
	 * Holds received CRC value.
	 *
	 * @{
	 */

	#define SPI_RXCRCR_RXCRC_Pos    0U

	/** @} */ // End of SPI_RXCRCR_BIT_POSITIONS

	/**
	 * @defgroup SPI_TXCRCR_BIT_POSITIONS
	 * @brief Bit position for TX CRC Register.
	 *
	 * Holds transmitted CRC value.
	 *
	 * @{
	 */

	#define SPI_TXCRCR_TXCRC_Pos    0U

	/** @} */ // End of SPI_TXCRCR_BIT_POSITIONS


/** @} */ // End of SPI_BIT_POSITION_MACROS

/**
 * @defgroup SPI_IT_TYPE SPI Peripheral Interrupt Types
 * @brief Bit positions used to select which SPI interrupt to enable/disable.
 *
 * These definitions correspond to logical interrupt types in the SPI driver.
 * They are NOT the CR2 register bit positions themselves, but identifiers used
 * by software APIs (e.g., SPIx_PeripheralInterruptControl()) to specify which
 * SPI interrupt to manipulate.
 *
 * @{
 */

	#define SPI_IT_TYPE_TXE    0U   /**< Transmit buffer empty interrupt type  */
	#define SPI_IT_TYPE_RXNE   1U   /**< Receive buffer not empty interrupt type */
	#define SPI_IT_TYPE_ERR    2U   /**< Error interrupt type (OVR, MODF, CRCERR) */

/** @} */ /* End of SPI_IT_TYPE */

/**
 * @defgroup SPI_STATE SPI Driver States
 * @brief Internal driver state values used to track ongoing SPI operations.
 *
 * These constants represent the current state of the SPI driver, and are used
 * internally by APIs such as SPIx_SendDataIT() and SPIx_ReceiveDataIT() to
 * prevent re-entrant transfers.
 *
 * @{
 */

#define SPI_STATE_READY        0U   /**< SPI is idle and ready for a new transfer */
#define SPI_STATE_BUSY_IN_TX   1U   /**< SPI is currently transmitting data (IT mode) */
#define SPI_STATE_BUSY_IN_RX   2U   /**< SPI is currently receiving data (IT mode) */

/** @} */ /* End of SPI_STATE */

/**
 * @defgroup SPI_RETURN_CODES SPI Return Codes
 * @brief Return status values used by SPI interrupt-driven APIs.
 *
 * These codes indicate whether an SPI IT-based transfer request was accepted,
 * rejected due to an ongoing transfer, or invalid due to bad arguments.
 *
 * @{
 */

#define SPI_TXRX_SUCCESS     0U   /**< Operation successful — IT transfer started */
#define SPI_BUSY             1U   /**< SPI is busy (TX or RX already in progress) */
#define SPI_INVALID_PARAM    2U   /**< Invalid argument (NULL buffer, length 0, etc.) */

/** @} */ /* End of SPI_RETURN_CODES */

/** @defgroup SPI_Events
 * @brief SPI driver event codes for application callbacks.
 * @{
 */
#define SPI_EVENT_TX_CMPLT   1  /**< Transmission finished */
#define SPI_EVENT_RX_CMPLT   2  /**< Reception finished */
#define SPI_EVENT_OVR_ERR    3  /**< Overrun error occurred */
#define SPI_EVENT_CRC_ERR    4  /**< CRC mismatch detected */
#define SPI_EVENT_MODF_ERR   5  /**< Mode fault error */
#define SPI_EVENT_FRE_ERR    6  /**< Frame format error */
/** @} */ // end of SPI_Events


/** @} */ // End of SPI Driver
#endif /* INC_STM32F407XX_SPI_H_ */
