/**
 ******************************************************************************
 * @file           : stm32f407xx.h
 * @brief          : Header file for STM32F407xx MCUS
 * @author         : Yuvraj Singh Rathore
 * @date           : Nov 2025
 * @version        : 1.0
 * @details        : Provides APIs for all the peripheral connected to the processor
 ******************************************************************************
 */
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_


/**
 * @defgroup MEMORY_SEGMENTATION Memory Segmentation
 * @brief Base Addresses various memory and buses
 * @{
 */
#define FLASH_BASEADDR	0x08000000UL //This is also called as Main Memory
/**< @note In STM32, Flash memory is called “Main Memory” because
 * it’s the primary executable memory region containing your user application.
 */
#define SRAM1_BASEADDR	0x20000000UL    /**< SRAM1 base address */
#define SRAM			SRAM1_BASEADDR	/**< SRAM base address (It is nothing but SRAM1)*/
#define SRAM2_BASEADDR	0x2001C000UL	/**< SRAM2 base address */
#define SRAM3_BASEADDR	0x20020000UL    /**< SRAM3 base address */
#define ROM_BASEADDR	0x1FFF0000UL 	/**< @note The ROM is called "System Memory" because it holds
                                   	   	   * the ST factory bootloader, used only for system-level
                                   	   	   * functions like firmware programming or DFU — not for
                                   	   	   * normal application execution.
                                   	   	   */
#define PERIPHERAL_BASEADDR 		0x40000000UL /**< Peripheral base address */
#define APB1_PERIPHERAL_BASEADDR 	0x40000000UL /**< APB1 Peripheral base address */
#define APB2_PERIPHERAL_BASEADDR 	0x40010000UL /**< APB2 Peripheral base address */
#define AHB1_PERIPHERAL_BASEADDR 	0x40020000UL /**< AHB1 Peripheral base address */
#define AHB2_PERIPHERAL_BASEADDR 	0x50000000UL /**< AHB2 Peripheral base address */
/** @} */


/**
 * @defgroup AHB1_BASE_ADDRESSES AHB1 Bus Peripheral Base Addresses
 * @brief Base addresses of peripherals connected to AHB1 Bus
 * @{
 */

#define GPIOA_BASEADDR              0x40020000UL    /**< GPIOA Peripheral base address */
#define GPIOB_BASEADDR              0x40020400UL    /**< GPIOB Peripheral base address */
#define GPIOC_BASEADDR              0x40020800UL    /**< GPIOC Peripheral base address */
#define GPIOD_BASEADDR              0x40020C00UL    /**< GPIOD Peripheral base address */
#define GPIOE_BASEADDR              0x40021000UL    /**< GPIOE Peripheral base address */
#define GPIOF_BASEADDR              0x40021400UL    /**< GPIOF Peripheral base address */
#define GPIOG_BASEADDR              0x40021800UL    /**< GPIOG Peripheral base address */
#define GPIOH_BASEADDR              0x40021C00UL    /**< GPIOH Peripheral base address */
#define GPIOI_BASEADDR              0x40022000UL    /**< GPIOI Peripheral base address */
#define GPIOJ_BASEADDR              0x40022400UL    /**< GPIOJ Peripheral base address */
#define GPIOK_BASEADDR 	            0x40022800UL    /**< GPIOK Peripheral base address */
#define CRC_BASEADDR                0x40023000UL    /**< Cyclic Redundancy Check (CRC) Peripheral base address */
#define RCC_BASEADDR    			0x40023800UL    /**< Reset and Clock Control (RCC) Peripheral base address */
#define FLASH_IF_REG_BASEADDR		0x40023C00UL    /**< Flash interface register Peripheral base address */
#define BKPSRAM_BASEADDR			0x40024000UL    /**< BKPSRAM Peripheral base address */
#define DMA1_BASEADDR				0x40026000UL    /**< Direct Memory Access 1 (DMA1) Peripheral base address */
#define DMA2_BASEADDR				0x40026400UL    /**< Direct Memory Access 2 (DMA2) Peripheral base address */
#define ETHERNET_MAC_BASEADDR		0x40028000UL    /**< ETHERNET MAC Peripheral base address */
#define DMA2D_BASEADDR				0x4002B000UL    /**< Chrom-Art Accelerator Controller (DMA2D) Peripheral base address */
#define USB_OTG_HS_BASEADDR			0x40040000UL    /**< USB On-The-Go High Speed (USB OTG HS) Peripheral base address */
/** @} */


/**@defgroup AHB2_BASE_ADDRESSES AHB2 Bus Peripheral Base Addresses
 * @brief Base Addresses of peripheral hanging on AHB2 Bus
 * @{
 */

#define USB_OTG_FS_BASEADDR	        0x50000000UL	/**< USB On-The-Go Full Speed (USB OTG FS) Peripheral base address */
#define DCMI_BASEADDR               0x50050000UL    /**< Digital Camera Interface (DCMI) Peripheral base address */
#define CRYP_BASEADDR               0x50060000UL    /**< Cryptographic Processor (CRYP) Peripheral base address */
#define HASH_BASEADDR               0x50060400UL    /**< Hash Processor (HASH) Peripheral base address */
#define RNG_BASEADDR                0x50060800UL    /**< Random Number Generator (RNG) Peripheral base address */
#define FSMC_CR_BASEADDR            0xA0000000UL    /**< Flexible Memory Controller (FMC) Peripheral base address */
/** @} */


/**@defgroup APB1_BASE_ADDRESSES APB1 Bus Peripheral Base Addresses
 * @brief Base Addresses of peripheral hanging on APB1 Bus
 * @{
 */

#define TIM2_BASEADDR            0x40000000UL		/**< Basic Timer 2 (TIM2) Peripheral base address */
#define TIM3_BASEADDR            0x40000400UL		/**< Basic Timer 3 (TIM3) Peripheral base address */
#define TIM4_BASEADDR            0x40000800UL       /**< Basic Timer 4 (TIM4) Peripheral base address */
#define TIM5_BASEADDR            0x40000C00UL       /**< Basic Timer 5 (TIM5) Peripheral base address */
#define TIM6_BASEADDR            0x40001000UL       /**< Basic Timer 6 (TIM6) Peripheral base address */
#define TIM7_BASEADDR            0x40001400UL       /**< Basic Timer 7 (TIM7) Peripheral base address */
#define TIM12_BASEADDR           0x40001800UL       /**< Basic Timer 12 (TIM12) Peripheral base address */
#define TIM13_BASEADDR           0x40001C00UL       /**< Basic Timer 13 (TIM13) Peripheral base address */
#define TIM14_BASEADDR           0x40002000UL       /**< Basic Timer 14 (TIM14) Peripheral base address */
#define RTC_BKP_REG_BASEADDR     0x40002800UL       /**< Real Time Counter Backup Register Peripheral base address */
#define WWDG_BASEADDR            0x40002C00UL       /**< Window Watch Dog (WWDG) Peripheral base address */
#define IWDG_BASEADDR            0x40003000UL       /**< Independent Watch Dog (IWDG) Peripheral base address */
#define I2S2ext_BASEADDR         0x40003400UL       /**< I2S2ext Peripheral base address */
#define SPI2_I2S2_BASEADDR       0x40003800UL       /**< Serial Peripheral Interface 2 (SPI2/I2S2) Peripheral base address */
#define SPI3_I2S3_BASEADDR       0x40003C00UL       /**< Serial Peripheral Interface 3 (SPI3/I2S3) Peripheral base address */
#define I2S3ext_BASEADDR         0x40004000UL       /**< I2S3ext Peripheral base address */
#define USART2_BASEADDR          0x40004400UL       /**< Universal Synchronous Asynchronous Receiver Transmitter 2 (USART2) Peripheral base address */
#define USART3_BASEADDR          0x40004800UL       /**< Universal Synchronous Asynchronous Receiver Transmitter 3 (USART3) Peripheral base address */
#define UART4_BASEADDR           0x40004C00UL       /**< Universal Synchronous Asynchronous Receiver Transmitter 4 (USART4)  Peripheral base address */
#define UART5_BASEADDR           0x40005000UL       /**< Universal Synchronous Asynchronous Receiver Transmitter 5 (USART5) Peripheral base address */
#define I2C1_BASEADDR            0x40005400UL       /**< Inter-integrated circuit 1 (I2C1) Peripheral base address */
#define I2C2_BASEADDR            0x40005800UL       /**< Inter-integrated circuit 2 (I2C2) Peripheral base address */
#define I2C3_BASEADDR            0x40005C00UL       /**< Inter-integrated circuit 3 (I2C3) Peripheral base address */
#define CAN1_BASEADDR            0x40006400UL       /**< Controlled Area Network 1 (CAN1) Peripheral base address */
#define CAN2_BASEADDR            0x40006800UL       /**< Controlled Area Network 2 (CAN2) Peripheral base address */
#define PWR_BASEADDR             0x40007000UL       /**< Power Controller (PWR) Peripheral base address */
#define DAC_BASEADDR             0x40007400UL       /**< Digital to Analog Converter (DAC) Peripheral base address */
#define UART7_BASEADDR           0x40007800UL       /**< Universal Asynchronous Receiver Transmitter 7 (UART7) Peripheral base address */
#define UART8_BASEADDR			 0x40007C00UL       /**< Universal Asynchronous Receiver Transmitter 8 (UART8) Peripheral base address */
/** @} */

/**@defgroup APB2_BASE_ADDRESSES APB2 Bus Peripheral Base Addresses
 * @brief Base Addresses of peripheral hanging on APB2 Bus
 * @{
 */

#define TIM1_BASEADDR            0x40010000UL      /**< Basic Timer 1 (TIM1) Peripheral base address */
#define TIM8_BASEADDR            0x40010400UL      /**< Basic Timer 8 (TIM8) Peripheral base address */
#define USART1_BASEADDR          0x40011000UL      /**< Universal Synchronous Asynchronous Receiver Transmitter 1 (USART1) Peripheral base address */
#define USART6_BASEADDR          0x40011400UL      /**< Universal Synchronous Asynchronous Receiver Transmitter 6 (USART6) Peripheral base address */
#define ADC123_BASEADDR          0x40012000UL      /**< Analog to Digital Converter 1,2,3 (ADC) Peripheral base address */
#define SDIO_BASEADDR            0x40012C00UL      /**< Secure digital input/output interface (SDIO) Peripheral base address */
#define SPI1_BASEADDR            0x40013000UL      /**< Serial Peripheral Interface 1 (SPI1) Peripheral base address */
#define SPI4_BASEADDR            0x40013400UL      /**< Serial Peripheral Interface 4 (SPI4) Peripheral base address */
#define SYSCFG_BASEADDR          0x40013800UL      /**< System configuration controller (SYSCFG) Peripheral base address */
#define EXTI_BASEADDR            0x40013C00UL      /**< External interrupt/event controller Peripheral base address */
#define TIM9_BASEADDR            0x40014000UL      /**< Basic Timer 9 (TIM9) Peripheral base address */
#define TIM10_BASEADDR           0x40014400UL      /**< Basic Timer 10 (TIM10) Peripheral base address */
#define TIM11_BASEADDR           0x40014800UL      /**< Basic Timer 11 (TIM11) Peripheral base address */
#define SPI5_BASEADDR            0x40015000UL      /**< Serial Peripheral Interface 5 (SPI5) Peripheral base address */
#define SPI6_BASEADDR            0x40015400UL      /**< Serial Peripheral Interface 6 (SPI6) Peripheral base address */
#define SAI1_BASEADDR            0x40015800UL      /**< Serial audio interface (SAI) Peripheral base address */
#define LCD_TFT_BASEADDR         0x40016800UL      /**< LCD TFT Controller (LCD_TFT) Peripheral base address */
/** @} */





















#endif /* INC_STM32F407XX_H_ */
