/*
 * stm32f407xx_i2c.h
 *
 *  Created on: Dec 8, 2025
 *      Author: ratho
 */

#ifndef INC_STM32F407XX_I2C_H_
#define INC_STM32F407XX_I2C_H_
#include "stm32f407xx.h"

/**
 * @defgroup I2C_DRIVER_DEVELOPEMNT I2C Driver
 * @brief I2C Driver Development
 * @{
 */

	/**
	 * @defgroup I2C_CONFIG_MACROS I2C Configuration Macros
	 * @brief I2C Driver Development
	 * @{
	 */

		/**
		 * @defgroup I2C_SCL_SPEED_CONFIG_MACROS I2C SCL Speed Configuration Macros
		 * @brief Supported I2C clock speeds. Values are in Hz.
		 * @{
		 */
			#define I2C_SCLSpeed_SM_100K         100000U   /*!< Standard Mode: 100 kHz       */
			#define I2C_SCLSpeed_FM_200K         200000U   /*!< Fast Mode:     200 kHz       */
			#define I2C_SCLSpeed_FM_400K         400000U   /*!< Fast Mode:     400 kHz       */
			#define I2C_SCLSpeed_FMP_1M          1000000U  /*!< Fast Mode Plus: 1 MHz        */
		/** @} */ //End of I2C_SCL_SPEED_CONFIG_MACROS

		/**
		 * @defgroup I2C_ACK_CONTROL_CONFIG_MACROS I2C ACK Control Configuration Macros
		 * @brief ACK enable/disable options for I2C peripheral.
		 * @{
		 */
			#define I2C_ACK_ENABLE        1U   /*!< Enable ACKing after byte reception  */
			#define I2C_ACK_DISABLE       0U   /*!< Disable ACKing; send NACK on RX     */
		/** @} */ //End of I2C_ACK_CONTROL_CONFIG_MACROS

		/**
		 * @defgroup I2C_FM_DUTY_CYCLE_CONFIG_MACROS I2C Fast Mode Duty Cycle Configuration Macros
		 * @brief Fast-mode duty cycle selection used to program CCR.DUTY bit.
		 * @{
		 */

		/**
		 * @brief Fast-mode duty cycle options used in I2C_Config_t.I2C_FMDutyCycle.
		 *
		 * - I2C_FM_DUTY_2:    T_low / T_high = 2   (CCR.DUTY = 0)
		 * - I2C_FM_DUTY_16_9: T_low / T_high = 16/9 (CCR.DUTY = 1)
		 */
			#define I2C_FM_DUTY_2        0U   /*!< Fast-mode duty = 2 (CCR.DUTY = 0)      */
			#define I2C_FM_DUTY_16_9     1U   /*!< Fast-mode duty = 16/9 (CCR.DUTY = 1)   */

		/** @} */ //I2C_FM_DUTY_CYCLE_CONFIG_MACROS


	/** @} */  /* end I2C_CONFIG_MACROS */

	/**
	 * @brief  I2C peripheral configuration structure.
	 * This structure holds all user-configurable parameters required to
	 * initialize the I2C peripheral. These fields are written into CR1, CR2,
	 * OAR1, CCR and TRISE during peripheral initialization.
	 */
	typedef struct
	{
		uint32_t I2C_SCLSpeed;     /*!< I2C bus speed in Hz.
										- Standard Mode: 100000
										- Fast Mode:     400000
										- Fast Mode+:    1000000 (if supported)
									*/

		uint16_t I2C_DeviceAddress; /*!< Own device address (7-bit or 10-bit).
										 For 7-bit addressing, provide the 7-bit value.
										 For 10-bit addressing, provide the full 10-bit value.
									 */

		uint8_t I2C_ACKControl;    /*!< Acknowledge enable/disable configuration.
										Possible values:
										- I2C_ACK_ENABLE
										- I2C_ACK_DISABLE
									*/

		uint8_t I2C_FMDutyCycle;   /*!< Duty cycle configuration in Fast Mode.
										Possible values:
										- I2C_FM_DUTY_2      (duty = 2)
										- I2C_FM_DUTY_16_9   (duty = 16/9)
									*/
	} I2C_Config_t;


	/**
	 * @brief  I2C peripheral handle structure.
	 *
	 * This structure binds together:
	 *  - The base address of the I2C peripheral register map.
	 *  - The configuration parameters selected by the user.
	 *  - (Future) runtime state variables for interrupt/DMA-based communication.
	 */
	typedef struct
	{
		volatile I2C_RegDef_t *pI2C; /*!< Pointer to I2C peripheral registers (I2C1, I2C2, I2C3). */

		I2C_Config_t I2C_Config;      /*!< I2C configuration settings provided by the user. */

		/* @todo: Add interrupt and DMA state variables
		   e.g., Tx/Rx buffer pointers, lengths, ISR state machines, flags, etc.
		*/
} I2C_Handle_t;


	/**
	 * @defgroup I2C_BIT_POSITION_MACROS I2C Bit Position Macros
	 * @{
	 */

	/* ----------------------------- I2C_CR1 (control register 1) ------------------------------ */
	/* Single-bit control flags */
	#define I2C_CR1_PE_POS            (0U)          /*!< Peripheral enable */
	#define I2C_CR1_SMBUS_POS         (1U)          /*!< SMBus mode */
	#define I2C_CR1_SMBTYPE_POS       (3U)          /*!< SMBus type (host/device) */
	#define I2C_CR1_ENARP_POS         (4U)          /*!< ARP enable (SMBus) */
	#define I2C_CR1_ENPEC_POS         (5U)          /*!< PEC enable */
	#define I2C_CR1_ENGC_POS          (6U)          /*!< General call enable */
	#define I2C_CR1_NOSTRETCH_POS     (7U)          /*!< Clock stretching disable (NOSTRETCH) */
	#define I2C_CR1_START_POS         (8U)          /*!< Start generation (master) */
	#define I2C_CR1_STOP_POS          (9U)          /*!< Stop generation (master) */
	#define I2C_CR1_ACK_POS           (10U)         /*!< Acknowledge enable */
	#define I2C_CR1_POS_POS           (11U)         /*!< ACK/PEC position (POS) */
	#define I2C_CR1_PEC_POS           (12U)         /*!< Packet error checking register */
	#define I2C_CR1_ALERT_POS         (13U)         /*!< SMBus alert */
	#define I2C_CR1_SWRST_POS         (15U)         /*!< Software reset */

	#define I2C_CR1_PE                (1U << I2C_CR1_PE_POS)
	#define I2C_CR1_SMBUS             (1U << I2C_CR1_SMBUS_POS)
	#define I2C_CR1_SMBTYPE           (1U << I2C_CR1_SMBTYPE_POS)
	#define I2C_CR1_ENARP             (1U << I2C_CR1_ENARP_POS)
	#define I2C_CR1_ENPEC             (1U << I2C_CR1_ENPEC_POS)
	#define I2C_CR1_ENGC              (1U << I2C_CR1_ENGC_POS)
	#define I2C_CR1_NOSTRETCH         (1U << I2C_CR1_NOSTRETCH_POS)
	#define I2C_CR1_START             (1U << I2C_CR1_START_POS)
	#define I2C_CR1_STOP              (1U << I2C_CR1_STOP_POS)
	#define I2C_CR1_ACK               (1U << I2C_CR1_ACK_POS)
	#define I2C_CR1_POS_BIT           (1U << I2C_CR1_POS_POS)
	#define I2C_CR1_PEC               (1U << I2C_CR1_PEC_POS)
	#define I2C_CR1_ALERT             (1U << I2C_CR1_ALERT_POS)
	#define I2C_CR1_SWRST             (1U << I2C_CR1_SWRST_POS)

	/* ----------------------------- I2C_CR2 (control register 2) ------------------------------ */
	/* FREQ field is 6 bits (bits[5:0]) - peripheral input clock frequency (MHz) */
	#define I2C_CR2_FREQ_POS         (0U)
	#define I2C_CR2_FREQ_MASK        (0x3FU << I2C_CR2_FREQ_POS)   /*!< CR2 FREQ[5:0] mask */

	#define I2C_CR2_ITERREN_POS      (8U)   /*!< Error interrupt enable */
	#define I2C_CR2_ITEVTEN_POS      (9U)   /*!< Event interrupt enable */
	#define I2C_CR2_ITBUFEN_POS      (10U)  /*!< Buffer interrupt enable */
	#define I2C_CR2_DMAEN_POS        (11U)  /*!< DMA requests enable */
	#define I2C_CR2_LAST_POS         (12U)  /*!< DMA last transfer */

	#define I2C_CR2_ITERREN          (1U << I2C_CR2_ITERREN_POS)
	#define I2C_CR2_ITEVTEN          (1U << I2C_CR2_ITEVTEN_POS)
	#define I2C_CR2_ITBUFEN          (1U << I2C_CR2_ITBUFEN_POS)
	#define I2C_CR2_DMAEN            (1U << I2C_CR2_DMAEN_POS)
	#define I2C_CR2_LAST             (1U << I2C_CR2_LAST_POS)

	/* ----------------------------- I2C_OAR1 (own address register 1) ------------------------ */
	/* OAR1 holds the device own address: 7-bit or 10-bit addressing.
	 * ADD[9:0] field typically occupies bits [10:1] (10-bit) or bits [7:1] for 7-bit left-aligned.
	 * Provide a generic position/mask covering 10 bits starting at bit 0 for convenience.
	 */
	#define I2C_OAR1_ADD_POS         (0U)
	#define I2C_OAR1_ADD_MASK        (0x3FFU << I2C_OAR1_ADD_POS)  /*!< Own address (10-bit) */
	#define I2C_OAR1_ADDMODE_POS     (15U)                          /*!< Addressing mode: 0 = 7-bit, 1 = 10-bit */

	#define I2C_OAR1_ADDMODE         (1U << I2C_OAR1_ADDMODE_POS)

	/* ----------------------------- I2C_OAR2 (own address register 2) ------------------------ */
	#define I2C_OAR2_ENDUAL_POS      (0U)        /*!< Dual addressing enable */
	#define I2C_OAR2_ADD2_POS        (1U)        /*!< Second address bits start at bit 1 */
	#define I2C_OAR2_ADD2_MASK       (0x7FU << I2C_OAR2_ADD2_POS) /*!< 7-bit second address */

	#define I2C_OAR2_ENDUAL          (1U << I2C_OAR2_ENDUAL_POS)

	/* ----------------------------- I2C_DR (data register) ---------------------------------- */
	/* DR is 8-bit data register */
	#define I2C_DR_DR_POS            (0U)
	#define I2C_DR_DR_MASK           (0xFFU << I2C_DR_DR_POS)   /*!< Data register (8-bit) */

	/* ----------------------------- I2C_SR1 (status register 1) ----------------------------- */
	/* Single-bit status flags in SR1: positions per reference manual */
	#define I2C_SR1_SB_POS           (0U)   /*!< Start bit (master mode) */
	#define I2C_SR1_ADDR_POS         (1U)   /*!< Address sent/received (master/slave) */
	#define I2C_SR1_BTF_POS          (2U)   /*!< Byte transfer finished */
	#define I2C_SR1_ADD10_POS        (3U)   /*!< 10-bit header sent (master) */
	#define I2C_SR1_STOPF_POS        (4U)   /*!< Stop detection (slave) */
	#define I2C_SR1_RXNE_POS         (6U)   /*!< Data register not empty (receivers) */
	#define I2C_SR1_TXE_POS          (7U)   /*!< Data register empty (transmitters) */
	#define I2C_SR1_BERR_POS         (8U)   /*!< Bus error */
	#define I2C_SR1_ARLO_POS         (9U)   /*!< Arbitration lost */
	#define I2C_SR1_AF_POS           (10U)  /*!< Acknowledge failure (NACK) */
	#define I2C_SR1_OVR_POS          (11U)  /*!< Overrun/underrun */
	#define I2C_SR1_PECERR_POS       (12U)  /*!< PEC error in reception */
	#define I2C_SR1_TIMEOUT_POS      (14U)  /*!< Timeout or Tlow error (SMBus) */
	#define I2C_SR1_SMBALERT_POS     (15U)  /*!< SMBus alert */

	#define I2C_SR1_SB               (1U << I2C_SR1_SB_POS)
	#define I2C_SR1_ADDR             (1U << I2C_SR1_ADDR_POS)
	#define I2C_SR1_BTF              (1U << I2C_SR1_BTF_POS)
	#define I2C_SR1_ADD10            (1U << I2C_SR1_ADD10_POS)
	#define I2C_SR1_STOPF            (1U << I2C_SR1_STOPF_POS)
	#define I2C_SR1_RXNE             (1U << I2C_SR1_RXNE_POS)
	#define I2C_SR1_TXE              (1U << I2C_SR1_TXE_POS)
	#define I2C_SR1_BERR             (1U << I2C_SR1_BERR_POS)
	#define I2C_SR1_ARLO             (1U << I2C_SR1_ARLO_POS)
	#define I2C_SR1_AF               (1U << I2C_SR1_AF_POS)
	#define I2C_SR1_OVR              (1U << I2C_SR1_OVR_POS)
	#define I2C_SR1_PECERR           (1U << I2C_SR1_PECERR_POS)
	#define I2C_SR1_TIMEOUT          (1U << I2C_SR1_TIMEOUT_POS)
	#define I2C_SR1_SMBALERT         (1U << I2C_SR1_SMBALERT_POS)

	/* ----------------------------- I2C_SR2 (status register 2) ----------------------------- */
	/* SR2 contains bus/master flags and PEC[7:0] in bits[15:8] */
	#define I2C_SR2_MSL_POS          (0U)   /*!< Master/slave */
	#define I2C_SR2_BUSY_POS         (1U)   /*!< Bus busy */
	#define I2C_SR2_TRA_POS          (2U)   /*!< Transmitter/receiver */
	#define I2C_SR2_GENCALL_POS      (4U)   /*!< General call address (slave) */
	#define I2C_SR2_SMBDEFAULT_POS   (5U)   /*!< SMBus default address (SMBus) */
	#define I2C_SR2_SMBHOST_POS      (6U)   /*!< SMBus host header (SMBus) */
	#define I2C_SR2_DUALF_POS        (7U)   /*!< Dual flag (two addresses) */
	#define I2C_SR2_PEC_POS          (8U)   /*!< PEC[7:0] position */

	#define I2C_SR2_MSL              (1U << I2C_SR2_MSL_POS)
	#define I2C_SR2_BUSY             (1U << I2C_SR2_BUSY_POS)
	#define I2C_SR2_TRA              (1U << I2C_SR2_TRA_POS)
	#define I2C_SR2_GENCALL          (1U << I2C_SR2_GENCALL_POS)
	#define I2C_SR2_SMBDEFAULT       (1U << I2C_SR2_SMBDEFAULT_POS)
	#define I2C_SR2_SMBHOST          (1U << I2C_SR2_SMBHOST_POS)
	#define I2C_SR2_DUALF            (1U << I2C_SR2_DUALF_POS)
	#define I2C_SR2_PEC_MASK         (0xFFU << I2C_SR2_PEC_POS) /*!< Packet error checking value */

	/* ----------------------------- I2C_CCR (clock control register) ------------------------- */
	/* CCR field (bits 11:0) holds the clock control value.
	 * For Fast mode, DUTY (bit14) and F/S (bit15) are used.
	 */
	#define I2C_CCR_CCR_POS         (0U)
	#define I2C_CCR_CCR_MASK        (0x0FFFU << I2C_CCR_CCR_POS) /*!< CCR[11:0] mask */
	#define I2C_CCR_DUTY_POS        (14U)                         /*!< Fast mode duty cycle */
	#define I2C_CCR_FS_POS          (15U)                         /*!< 0 = Sm / 1 = Fm */

	#define I2C_CCR_DUTY            (1U << I2C_CCR_DUTY_POS)
	#define I2C_CCR_FS              (1U << I2C_CCR_FS_POS)

	/* ----------------------------- I2C_TRISE (TRISE register) ------------------------------ */
	/* TRISE[5:0] (bits 5:0) */
	#define I2C_TRISE_TRISE_POS    (0U)
	#define I2C_TRISE_TRISE_MASK   (0x3FU << I2C_TRISE_TRISE_POS) /*!< TRISE value mask */

	/* ----------------------------- I2C_FLTR (filter register) ------------------------------ */
	/* DNF[3:0] digital noise filter (bits 3:0), ANOFF (bit 4) analog filter OFF */
	#define I2C_FLTR_DNF_POS       (0U)
	#define I2C_FLTR_DNF_MASK      (0x0FU << I2C_FLTR_DNF_POS) /*!< Digital noise filter mask */
	#define I2C_FLTR_ANOFF_POS     (4U)                          /*!< Analog filter off */

	#define I2C_FLTR_ANOFF         (1U << I2C_FLTR_ANOFF_POS)

	/** @} */ /* end I2C_BIT_POSITION_MACROS */

	/**
	 * @defgroup I2C_API_PROTOTYPES I2C API Prototypes
	 * @brief I2C API Prototypes
	 * @note  Contains I2C API Prototypes
	 * @{
	 */

		/**
		 * @brief   Enables or disables the I2C peripheral.
		 *
		 * This function sets or clears the PE (Peripheral Enable) bit in the I2C_CR1 register,
		 * thereby enabling or disabling the selected I2C peripheral.
		 *
		 * @param[in]  pI2C   Pointer to the I2C peripheral base address
		 *                     (e.g., I2C1, I2C2, I2C3).
		 *
		 * @param[in]  EN_DI   Enable/Disable control macro:
		 *                     - ENABLE  : Set the PE bit to enable the peripheral.
		 *                     - DISABLE : Clear the PE bit to disable the peripheral.
		 *
		 * @note   This function does NOT configure any other I2C settings; it only controls
		 *         the PE bit in I2C_CR1. Ensure initialization is completed using I2C_Init()
		 *         before enabling the peripheral.
		 *
		 * @return None
		 */
		void I2C_Peri_Control(I2C_RegDef_t *pI2C, uint8_t EN_DI);

		/**
		 * @brief   Initializes the I2C peripheral using the configuration provided
		 *          in the I2C handle structure.
		 *
		 * This function configures CR1, CR2, OAR1, CCR and TRISE based on the fields
		 * specified inside @ref I2C_Config_t. It does not modify the SPE/PE enable bit.
		 *
		 * @param[in]  pI2C_Handle   Pointer to an I2C_Handle_t structure that contains
		 *                           the peripheral base address and configuration settings.
		 *
		 * @note    This function does NOT enable the I2C peripheral. The user must call
		 *          I2C_PeripheralControl(pI2C_Handle->pI2C, ENABLE) after initialization.
		 *
		 * @return  None
		 */
		void I2C_Init(I2C_Handle_t *pI2C_Handle);

		/**
		 * @brief   Resets the I2C peripheral registers to their default reset values.
		 *
		 * This function triggers a peripheral reset using the corresponding bit in
		 * the RCC->APB1RSTR register. Once the reset pulse is applied, the peripheral
		 * registers return to their hardware-defined reset state and the I2C peripheral
		 * clock is automatically disabled.
		 *
		 * @param[in]  pI2C   Pointer to the I2C peripheral base address
		 *                     (e.g., I2C1, I2C2, I2C3).
		 *
		 * @note  After calling this function, the user must explicitly re-enable the
		 *        peripheral clock (via I2C1_PCLK_EN(), I2C2_PCLK_EN(), etc.) and
		 *        reinitialize the configuration before using the I2C peripheral again.
		 *
		 * @return None
		 */
		void I2C_DeInit(I2C_RegDef_t *pI2C);


		/**
		 * @brief   Reads the status of a specific I2C status flag.
		 *
		 * This function checks the current state of the I2C status registers
		 * (SR1 and SR2) and returns whether the requested flag is set.
		 *
		 * @param[in]  pI2C     Pointer to the I2C peripheral register map
		 *                       (e.g., I2C1, I2C2, I2C3).
		 *
		 * @param[in]  FlagName  Bitmask identifying the flag to check. Supply one of the
		 *                       I2C flag macros (masks), for example:
		 *                       - I2C_SR1_TXE
		 *                       - I2C_SR1_RXNE
		 *                       - I2C_SR2_BUSY
		 *                       See @ref I2C_STATUS_FLAG_MACROS for available flags.
		 *
		 * @note    Some flags reside in SR1 while others reside in SR2. This function
		 *          inspects both registers as needed. It does not clear or modify flags.
		 *
		 * @return  uint8_t  FLAG_SET (1) if the flag is set, or FLAG_RESET (0) if cleared.
		 */
		uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2C, uint32_t FlagName);

	/** @} */

/** @} */


#endif /* INC_STM32F407XX_I2C_H_ */
