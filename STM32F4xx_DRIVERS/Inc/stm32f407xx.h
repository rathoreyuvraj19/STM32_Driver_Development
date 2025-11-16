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
#include<stdint.h>

/**
 * @defgroup MISCELLANEOUS_MACROS General-purpose macros
 * @brief General macros that can be used across the codebase.
 * @{
 */

#define ENABLE   1
#define DISABLE  0
#define SET      1
#define RESET    0

/** @} */  // end of MISCELLANEOUS_MACROS

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
 * @defgroup AHB1_PERIPEHRALS_BASE_ADDRESSES Base address of AHB1 peripherals
 * @brief Base addresses of peripherals connected on AHB1 Bus
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
//#define GPIOJ_BASEADDR              0x40022400UL    /**< GPIOJ Peripheral base address */
//#define GPIOK_BASEADDR 	          0x40022800UL    /**< GPIOK Peripheral base address */
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


/**
 * @defgroup AHB2_PERIPEHRALS_BASE_ADDRESSES Base address of AHB2 peripherals
 * @brief Base addresses of peripherals connected on AHB2 Bus
 * @{
 */


#define USB_OTG_FS_BASEADDR	        0x50000000UL	/**< USB On-The-Go Full Speed (USB OTG FS) Peripheral base address */
#define DCMI_BASEADDR               0x50050000UL    /**< Digital Camera Interface (DCMI) Peripheral base address */
#define CRYP_BASEADDR               0x50060000UL    /**< Cryptographic Processor (CRYP) Peripheral base address */
#define HASH_BASEADDR               0x50060400UL    /**< Hash Processor (HASH) Peripheral base address */
#define RNG_BASEADDR                0x50060800UL    /**< Random Number Generator (RNG) Peripheral base address */
#define FSMC_CR_BASEADDR            0xA0000000UL    /**< Flexible Memory Controller (FMC) Peripheral base address */
/** @} */


/**
 * @defgroup APB1_PERIPEHRALS_BASE_ADDRESSES Base address of APB1 peripherals
 * @brief Base addresses of peripherals connected on APB1 Bus
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

/**
 * @defgroup APB2_PERIPEHRALS_BASE_ADDRESSES Base address of APB2 peripherals
 * @brief Base addresses of peripherals connected on APB1 Bus
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

/**
 * @defgroup INTERRUPT_TRIGGER_TYPE_MACROS Interrupt Trigger Type Macros
 * @brief Macros representing the EXTI trigger configuration types.
 * @{
 */

#define INTERRUPT_TRIGGER_TYPE_RISING   0   /*!< Trigger interrupt on rising edge  */
#define INTERRUPT_TRIGGER_TYPE_FALLING  1   /*!< Trigger interrupt on falling edge */
#define INTERRUPT_TRIGGER_TYPE_BOTH     2   /*!< Trigger interrupt on both edges   */

/** @} */  /* End of INTERRUPT_TRIGGER_TYPE_MACROS */

/**
 * @defgroup GPIO_PIN_NUMBER_MACROS GPIO Pin Number Macros
 * @brief Macros to represent GPIO pin numbers (0–15).
 * @note These macros are used to specify the pin index inside a GPIO port.
 * @{
 */

#define GPIO_PIN_0     0  /*!< GPIO Pin 0  */
#define GPIO_PIN_1     1  /*!< GPIO Pin 1  */
#define GPIO_PIN_2     2  /*!< GPIO Pin 2  */
#define GPIO_PIN_3     3  /*!< GPIO Pin 3  */
#define GPIO_PIN_4     4  /*!< GPIO Pin 4  */
#define GPIO_PIN_5     5  /*!< GPIO Pin 5  */
#define GPIO_PIN_6     6  /*!< GPIO Pin 6  */
#define GPIO_PIN_7     7  /*!< GPIO Pin 7  */
#define GPIO_PIN_8     8  /*!< GPIO Pin 8  */
#define GPIO_PIN_9     9  /*!< GPIO Pin 9  */
#define GPIO_PIN_10   10 /*!< GPIO Pin 10 */
#define GPIO_PIN_11   11 /*!< GPIO Pin 11 */
#define GPIO_PIN_12   12 /*!< GPIO Pin 12 */
#define GPIO_PIN_13   13 /*!< GPIO Pin 13 */
#define GPIO_PIN_14   14 /*!< GPIO Pin 14 */
#define GPIO_PIN_15   15 /*!< GPIO Pin 15 */

/** @} */ /* End of GPIO_PIN_NUMBER_MACROS */

/**
 * @defgroup NVIC_IRQ_PRIORITY_LEVELS NVIC Interrupt Priority Levels (0–15)
 * @brief Priority encoding for STM32F4 NVIC (lower = higher priority).
 *
 * @note Cortex-M4 uses only upper 4 bits of priority byte.
 * @note Priority 0 is highest urgency, 15 is lowest.
 * @{
 */

#define NVIC_IRQ_PRIORITY_0     0   /**< Highest priority - real-time critical */
#define NVIC_IRQ_PRIORITY_1     1   /**< Very high priority */
#define NVIC_IRQ_PRIORITY_2     2   /**< Time-critical */
#define NVIC_IRQ_PRIORITY_3     3   /**< High priority */
#define NVIC_IRQ_PRIORITY_4     4   /**< Above normal */
#define NVIC_IRQ_PRIORITY_5     5   /**< Normal priority */
#define NVIC_IRQ_PRIORITY_6     6   /**< Medium priority */
#define NVIC_IRQ_PRIORITY_7     7   /**< Mid-Low priority */
#define NVIC_IRQ_PRIORITY_8     8   /**< Low priority */
#define NVIC_IRQ_PRIORITY_9     9   /**< Lower priority */
#define NVIC_IRQ_PRIORITY_10   10   /**< Background servicing */
#define NVIC_IRQ_PRIORITY_11   11   /**< Low background */
#define NVIC_IRQ_PRIORITY_12   12   /**< Very low */
#define NVIC_IRQ_PRIORITY_13   13   /**< Idle-level tasks */
#define NVIC_IRQ_PRIORITY_14   14   /**< Near lowest */
#define NVIC_IRQ_PRIORITY_15   15   /**< Lowest possible priority */

/** @} */ // end of NVIC_IRQ_PRIORITY_LEVELS


//*********************Peripheral Register Definition structure**********************//

/**@defgroup GPIOx_REG_DEF GPIOx Peripheral Register Definition
 * @brief Register Definition of GPIOx Peripheral Register
 * @{
 */
typedef struct {
	volatile uint32_t MODER;	 /*!< @todo Add Explanation, Also explain why its volatile*/
	volatile uint32_t OTYPER;    /*!< @todo Add Explanation*/
	volatile uint32_t OSPEEDR;   /*!< @todo Add Explanation*/
	volatile uint32_t PUPDR;     /*!< @todo Add Explanation*/
	volatile uint32_t IDR;       /*!< @todo Add Explanation*/
	volatile uint32_t ODR;       /*!< @todo Add Explanation*/
	volatile uint32_t BSRR;      /*!< @todo Add Explanation*/
	volatile uint32_t LCKR;      /*!< @todo Add Explanation*/
	volatile uint32_t AFRL;      /*!< @todo Add Explanation*/
	volatile uint32_t AFRH;      /*!< @todo Add Explanation*/
}GPIOx_RegDef_t;
/** @} */

/**
 * @defgroup GPIO_BASE_ADDRESSES GPIO Port Base Address Macros
 * @brief Macros that provide typed base address pointers for all GPIO ports.
 * @{
 */

#define GPIOA   ((GPIOx_RegDef_t*)GPIOA_BASEADDR)   /*!< Base address pointer for GPIO Port A */
#define GPIOB   ((GPIOx_RegDef_t*)GPIOB_BASEADDR)   /*!< Base address pointer for GPIO Port B */
#define GPIOC   ((GPIOx_RegDef_t*)GPIOC_BASEADDR)   /*!< Base address pointer for GPIO Port C */
#define GPIOD   ((GPIOx_RegDef_t*)GPIOD_BASEADDR)   /*!< Base address pointer for GPIO Port D */
#define GPIOE   ((GPIOx_RegDef_t*)GPIOE_BASEADDR)   /*!< Base address pointer for GPIO Port E */
#define GPIOF   ((GPIOx_RegDef_t*)GPIOF_BASEADDR)   /*!< Base address pointer for GPIO Port F */
#define GPIOG   ((GPIOx_RegDef_t*)GPIOG_BASEADDR)   /*!< Base address pointer for GPIO Port G */
#define GPIOH   ((GPIOx_RegDef_t*)GPIOH_BASEADDR)   /*!< Base address pointer for GPIO Port H */
#define GPIOI   ((GPIOx_RegDef_t*)GPIOI_BASEADDR)   /*!< Base address pointer for GPIO Port I */
//#define GPIOJ ((GPIOx_RegDef_t*)GPIOJ_BASEADDR)   /*!< Base address pointer for GPIO Port J */
//#define GPIOK ((GPIOx_RegDef_t*)GPIOK_BASEADDR)   /*!< Base address pointer for GPIO Port K */

/** @} */   /* End of GPIO_BASE_ADDRESSES */




/**@defgroup RCC_REG RCC Peripheral Register Definition
 * @brief Register Definition of Reset and Clock Control (RCC) Peripheral Register
 * @{
 */
typedef struct {
	volatile uint32_t CR;	 		  	/*!< @todo Add Explanation OFFSET: 0x00 */
	volatile uint32_t PLLCFGR;    	  	/*!< @todo Add Explanation OFFSET: 0x04*/
	volatile uint32_t CFGR;   		  	/*!< @todo Add Explanation OFFSET: 0x08*/
	volatile uint32_t CIR;     	  	/*!< @todo Add Explanation OFFSET: 0x0C*/
	volatile uint32_t AHB1RSTR;       	/*!< @todo Add Explanation OFFSET: 0x10*/
	volatile uint32_t AHB2RSTR;       	/*!< @todo Add Explanation OFFSET: 0x14*/
	volatile uint32_t AHB3RSTR;      	/*!< @todo Add Explanation OFFSET: 0x18*/
	volatile uint32_t reserved1;      	/*!< @todo Add Explanation OFFSET: 0x1C*/
	volatile uint32_t APB1RSTR;      	/*!< @todo Add Explanation OFFSET: 0x20*/
	volatile uint32_t APB2RSTR;      	/*!< @todo Add Explanation OFFSET: 0x24*/
	volatile uint32_t reserved2;      	/*!< @todo Add Explanation OFFSET: 0x28*/
	volatile uint32_t reserved3;      	/*!< @todo Add Explanation OFFSET: 0x2C*/
	volatile uint32_t AHB1ENR;      	/*!< @todo Add Explanation OFFSET: 0x30*/
	volatile uint32_t AHB2ENR;      	/*!< @todo Add Explanation OFFSET: 0x34*/
	volatile uint32_t AHB3ENR;      	/*!< @todo Add Explanation OFFSET: 0x38*/
	volatile uint32_t reserved4;      	/*!< @todo Add Explanation OFFSET: 0x3C*/
	volatile uint32_t APB1ENR;      	/*!< @todo Add Explanation OFFSET: 0x40*/
	volatile uint32_t APB2ENR;      	/*!< @todo Add Explanation OFFSET: 0x44*/
	volatile uint32_t reserve5;      	/*!< @todo Add Explanation OFFSET: 0x48*/
	volatile uint32_t reserve6;      	/*!< @todo Add Explanation OFFSET: 0x4C*/
	volatile uint32_t AHB1LPENR;      	/*!< @todo Add Explanation OFFSET: 0x50*/
	volatile uint32_t AHB2LPENR;      	/*!< @todo Add Explanation OFFSET: 0x54*/
	volatile uint32_t AHB3LPENR;      	/*!< @todo Add Explanation OFFSET: 0x58*/
	volatile uint32_t reserve7;      	/*!< @todo Add Explanation OFFSET: 0x5C*/
	volatile uint32_t APB1LPENR;      	/*!< @todo Add Explanation OFFSET: 0x60*/
	volatile uint32_t APB2LPENR;      	/*!< @todo Add Explanation OFFSET: 0x64*/
	volatile uint32_t reserve8;      	/*!< @todo Add Explanation OFFSET: 0x68*/
	volatile uint32_t reserve9;      	/*!< @todo Add Explanation OFFSET: 0x6C*/
	volatile uint32_t BDCR;      		/*!< @todo Add Explanation OFFSET: 0x70*/
	volatile uint32_t CSR;      		/*!< @todo Add Explanation OFFSET: 0x74*/
	volatile uint32_t reserve10;      	/*!< @todo Add Explanation OFFSET: 0x78*/
	volatile uint32_t reserve11;      	/*!< @todo Add Explanation OFFSET: 0x7C*/
	volatile uint32_t SSCGR;      		/*!< @todo Add Explanation OFFSET: 0x80*/
	volatile uint32_t PLLI2SCFGR;     	/*!< @todo Add Explanation OFFSET: 0x84*/
}RCC_RegDef_t;

#define RCC	((RCC_RegDef_t*)RCC_BASEADDR) /*!< @todo Add Explanation*/

/** @} */

/**@defgroup SYSCFG_REG SYSCFG Peripheral Register Definition
 * @brief Register Definition of System Configuration and Controller (SYSCFG) Peripheral Register
 * @{
 */
typedef struct  {
	volatile uint32_t MEMRMP;	 		  	/*!< @todo Add Explanation OFFSET: 0x00 */
	volatile uint32_t PMC;	 		  		/*!< @todo Add Explanation OFFSET: 0x04 */
	volatile uint32_t EXTICR1;	 		  	/*!< @todo Add Explanation OFFSET: 0x08 */
	volatile uint32_t EXTICR2;	 		  	/*!< @todo Add Explanation OFFSET: 0x0C */
	volatile uint32_t EXTICR3;	 		  	/*!< @todo Add Explanation OFFSET: 0x10 */
	volatile uint32_t EXTICR4;	 		  	/*!< @todo Add Explanation OFFSET: 0x14 */
	volatile uint32_t reserved1;	 		  	/*!< @todo Add Explanation OFFSET: 0x18 */
	volatile uint32_t reserved2;	 		  	/*!< @todo Add Explanation OFFSET: 0x1C */
	volatile uint32_t CMPCR;	 		  	/*!< @todo Add Explanation OFFSET: 0x20 */
}SYSCFG_RegDef_t;

#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASEADDR) /*!< @todo Add Explanation*/

/** @} */

/**
 * @defgroup EXTI_REG EXTI Peripheral Register Definition
 * @brief Register definitions for the External Interrupt/Event Controller (EXTI).
 * @{
 */
typedef struct
{
    volatile uint32_t IMR;     /*!< Interrupt Mask Register,          OFFSET: 0x00
                                    0 = interrupt masked
                                    1 = interrupt not masked (enabled) */

    volatile uint32_t EMR;     /*!< Event Mask Register,              OFFSET: 0x04
                                    Controls event generation (not interrupts) */

    volatile uint32_t RTSR;    /*!< Rising Trigger Selection Register, OFFSET: 0x08
                                    1 = interrupt/event on rising edge */

    volatile uint32_t FTSR;    /*!< Falling Trigger Selection Register, OFFSET: 0x0C
                                    1 = interrupt/event on falling edge */

    volatile uint32_t SWIER;   /*!< Software Interrupt Event Register, OFFSET: 0x10
                                    Write 1 to trigger software interrupt */

    volatile uint32_t PR;      /*!< Pending Register,                  OFFSET: 0x14
                                    Write 1 to clear the pending interrupt flag */
} EXTI_RegDef_t;

#define EXTI    ((EXTI_RegDef_t*)EXTI_BASEADDR) /*!< Pointer to EXTI peripheral registers */

/** @} */ /* End of EXTI_REG */



//==================================================================================//
//=================== Clock Enable Disable Macros===================================//
//==================================================================================//

/**
 * @defgroup CLOCK_ENABLE_MACROS Macros to Enable/Disable clocks for various peripherals
 * @brief Contains macros to enable or disable peripheral clocks through RCC.
 * @{
 */

	/**
	 * @defgroup AHB1_PCLK_EN_DI_MACROS
	 * @ingroup CLOCK_ENABLE_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to AHB1 bus.
	 * @{
	 */

	#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))  /*!< Enable GPIOA clock (AHB1ENR bit 0) */
	#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0)) /*!< Disable GPIOA clock (AHB1ENR bit 0) */

	#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))  /*!< Enable GPIOB clock (AHB1ENR bit 1) */
	#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1)) /*!< Disable GPIOB clock (AHB1ENR bit 1) */

	#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))  /*!< Enable GPIOC clock (AHB1ENR bit 2) */
	#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2)) /*!< Disable GPIOC clock (AHB1ENR bit 2) */

	#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))  /*!< Enable GPIOD clock (AHB1ENR bit 3) */
	#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3)) /*!< Disable GPIOD clock (AHB1ENR bit 3) */

	#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))  /*!< Enable GPIOE clock (AHB1ENR bit 4) */
	#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4)) /*!< Disable GPIOE clock (AHB1ENR bit 4) */

	#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1<<5))  /*!< Enable GPIOF clock (AHB1ENR bit 5) */
	#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1<<5)) /*!< Disable GPIOF clock (AHB1ENR bit 5) */

	#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1<<6))  /*!< Enable GPIOG clock (AHB1ENR bit 6) */
	#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1<<6)) /*!< Disable GPIOG clock (AHB1ENR bit 6) */

	#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7))  /*!< Enable GPIOH clock (AHB1ENR bit 7) */
	#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7)) /*!< Disable GPIOH clock (AHB1ENR bit 7) */

	#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1<<8))  /*!< Enable GPIOI clock (AHB1ENR bit 8) */
	#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1<<8)) /*!< Disable GPIOI clock (AHB1ENR bit 8) */

		/** @todo Complete for other peripherals */

	/** @} */ // End of AHB1 Bus Peripheral Enable Disable

	/**
	 * @defgroup AHB2_PCLK_EN_DI_MACROS
	 * @ingroup CLOCK_ENABLE_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to AHB2 bus.
	 * @{
	 */
		/** @todo Complete for other peripherals */

	/** @} */ // End of AHB2 Bus Peripheral Enable Disable

	/**
	 * @defgroup AHB3_PCLK_EN_DI_MACROS
	 * @ingroup CLOCK_ENABLE_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to AHB3 bus.
	 * @{
	 */
		/** @todo Complete for other peripherals */

	/** @} */ // End of AHB3 Bus Peripheral Enable Disable

	/**
	 * @defgroup APB1_PCLK_EN_DI_MACROS
	 * @ingroup CLOCK_ENABLE_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to APB1 bus.
	 * @{
	 */
	/** @todo Complete for other peripherals */

	/** @} */ // End of APB1 Bus Peripheral Enable Disable

	/**
	 * @defgroup APB2_PCLK_EN_DI_MACROS
	 * @ingroup CLOCK_ENABLE_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to APB2 bus.
	 * @{
	 */
	#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1<<14))
	#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1<<14))
	/** @todo Complete for other peripherals */

	/** @} */ // End of APB2 Bus Peripheral Enable Disable



/** @} */// End of CLOCK_ENABLE_MACROS

//==================================================================================//
//=================== Peripheral Reset Macros ======================================//
//==================================================================================//
/**
 * @defgroup PERIPHERAL_RESET_MACROS Macros to reset various peripherals
 * @brief Contains macros to reset various peripheral through RCC Reset Reg
 * @{
 */

	/**
	 * @defgroup AHB1_RESET_MACROS AHB1 Peripheral Reset Macros
	 * @ingroup  PERIPHERAL_RESET_MACROS
	 * @brief Macros to reset AHB1 peripherals.
	 * @{
	 */

		#define GPIOA_RESET()  do{ RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0); }while(0) /**< Reset GPIOA */
		#define GPIOB_RESET()  do{ RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1); }while(0) /**< Reset GPIOB */
		#define GPIOC_RESET()  do{ RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2); }while(0) /**< Reset GPIOC */
		#define GPIOD_RESET()  do{ RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3); }while(0) /**< Reset GPIOD */
		#define GPIOE_RESET()  do{ RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4); }while(0) /**< Reset GPIOE */
		#define GPIOF_RESET()  do{ RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5); }while(0) /**< Reset GPIOF */
		#define GPIOG_RESET()  do{ RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6); }while(0) /**< Reset GPIOG */
		#define GPIOH_RESET()  do{ RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7); }while(0) /**< Reset GPIOH */
		#define GPIOI_RESET()  do{ RCC->AHB1RSTR |= (1 << 8); RCC->AHB1RSTR &= ~(1 << 8); }while(0) /**< Reset GPIOI */
	/** @todo Finish for rest of the peripheral */

	/** @} */ // end of AHB1_RESET_MACROS


	/**
	 * @defgroup AHB2_RESET_MACROS AHB2 Peripheral Reset Macros
	 * @ingroup PERIPHERAL_RESET_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to AHB2 bus.
	 * @{
	 */

	/** @todo Complete for other peripherals */

	/** @} */// End of AHB2 Bus Peripheral Reset Macros

	/**
	 * @defgroup AHB3_RESET_MACROS AHB3 Peripheral Reset Macros
	 * @ingroup PERIPHERAL_RESET_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to AHB3 bus.
	 * @{
	 */

	/** @todo Complete for other peripherals */

	/** @} */// End of AHB3 Bus Peripheral Reset Macros

	/**
	 * @defgroup APB1_RESET_MACROS APB1 Peripheral Reset Macros
	 * @ingroup PERIPHERAL_RESET_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to APB1 bus.
	 * @{
	 */

	/** @todo Complete for other peripherals */

	/** @} */// End of APB1 Bus Peripheral Reset Macros

	/**
	 * @defgroup APB2_RESET_MACROS APB2 Peripheral Reset Macros
	 * @ingroup PERIPHERAL_RESET_MACROS
	 * @brief Macros to enable or disable for peripherals belonging to APB2 bus.
	 * @{
	 */
	#define SYSCFG_EN() 	(RCC.)
	/** @todo Complete for other peripherals */

	/** @} */// End of APB2 Bus Peripheral Reset Macros

/** @} */



/**
 * @defgroup NVIC_REG NVIC Register Definition
 * @brief Register definitions for Nested Vectored Interrupt Controller (NVIC).
 * @{
 */

/* NVIC base address for Cortex-M4 */
#define NVIC_BASEADDR     (0xE000E100UL)

/* NVIC register layout */
typedef struct
{
    volatile uint32_t ISER[8];     /*!< Interrupt Set-Enable Registers    */
    uint32_t RESERVED0[24];

    volatile uint32_t ICER[8];     /*!< Interrupt Clear-Enable Registers  */
    uint32_t RESERVED1[24];

    volatile uint32_t ISPR[8];     /*!< Interrupt Set-Pending Registers   */
    uint32_t RESERVED2[24];

    volatile uint32_t ICPR[8];     /*!< Interrupt Clear-Pending Registers */
    uint32_t RESERVED3[24];

    volatile uint32_t IABR[8];     /*!< Interrupt Active Bit Registers    */
    uint32_t RESERVED4[56];

    volatile uint32_t IPR[60];     /*!< Interrupt Priority Registers (240 bytes / 4) */
    uint32_t RESERVED5[644];

    volatile uint32_t STIR;        /*!< Software Trigger Interrupt Reg    */
} NVIC_RegDef_t;

/* NVIC pointer */
#define NVIC   ((NVIC_RegDef_t*)NVIC_BASEADDR)

/** @} */

/**
 * @defgroup IRQ_NUMBER_MACROS IRQ Numbers for STM32F407
 * @brief Defines the interrupt numbers used by the NVIC for all STM32F407 peripherals.
 * @details These values map directly to the exception numbers in the vector table.
 * @{
 */

#define IRQ_NUM_WWDG               0   /*!< Window Watchdog Interrupt */
#define IRQ_NUM_PVD                1   /*!< PVD through EXTI Line interrupt */
#define IRQ_NUM_TAMP_STAMP         2   /*!< Tamper and TimeStamp interrupts */
#define IRQ_NUM_RTC_WKUP           3   /*!< RTC Wakeup interrupt */
#define IRQ_NUM_FLASH              4   /*!< Flash global interrupt */
#define IRQ_NUM_RCC                5   /*!< RCC global interrupt */
#define IRQ_NUM_EXTI0              6   /*!< EXTI Line0 interrupt */
#define IRQ_NUM_EXTI1              7   /*!< EXTI Line1 interrupt */
#define IRQ_NUM_EXTI2              8   /*!< EXTI Line2 interrupt */
#define IRQ_NUM_EXTI3              9   /*!< EXTI Line3 interrupt */
#define IRQ_NUM_EXTI4              10  /*!< EXTI Line4 interrupt */

#define IRQ_NUM_DMA1_STREAM0       11  /*!< DMA1 Stream0 global interrupt */
#define IRQ_NUM_DMA1_STREAM1       12  /*!< DMA1 Stream1 global interrupt */
#define IRQ_NUM_DMA1_STREAM2       13  /*!< DMA1 Stream2 global interrupt */
#define IRQ_NUM_DMA1_STREAM3       14  /*!< DMA1 Stream3 global interrupt */
#define IRQ_NUM_DMA1_STREAM4       15  /*!< DMA1 Stream4 global interrupt */
#define IRQ_NUM_DMA1_STREAM5       16  /*!< DMA1 Stream5 global interrupt */
#define IRQ_NUM_DMA1_STREAM6       17  /*!< DMA1 Stream6 global interrupt */

#define IRQ_NUM_ADC                18  /*!< ADC1, ADC2 and ADC3 global interrupt */

#define IRQ_NUM_CAN1_TX            19  /*!< CAN1 TX interrupts */
#define IRQ_NUM_CAN1_RX0           20  /*!< CAN1 RX0 interrupts */
#define IRQ_NUM_CAN1_RX1           21  /*!< CAN1 RX1 interrupts */
#define IRQ_NUM_CAN1_SCE           22  /*!< CAN1 SCE (status change error) interrupts */

#define IRQ_NUM_EXTI9_5            23  /*!< EXTI Line[9:5] interrupts */

#define IRQ_NUM_TIM1_BRK_TIM9      24  /*!< TIM1 Break and TIM9 interrupt */
#define IRQ_NUM_TIM1_UP_TIM10      25  /*!< TIM1 Update and TIM10 interrupt */
#define IRQ_NUM_TIM1_TRG_COM_TIM11 26  /*!< TIM1 Trigger/Commutation and TIM11 interrupt */
#define IRQ_NUM_TIM1_CC            27  /*!< TIM1 Capture Compare interrupt */

#define IRQ_NUM_TIM2               28  /*!< TIM2 global interrupt */
#define IRQ_NUM_TIM3               29  /*!< TIM3 global interrupt */
#define IRQ_NUM_TIM4               30  /*!< TIM4 global interrupt */

#define IRQ_NUM_I2C1_EV            31  /*!< I2C1 event interrupt */
#define IRQ_NUM_I2C1_ER            32  /*!< I2C1 error interrupt */
#define IRQ_NUM_I2C2_EV            33  /*!< I2C2 event interrupt */
#define IRQ_NUM_I2C2_ER            34  /*!< I2C2 error interrupt */

#define IRQ_NUM_SPI1               35  /*!< SPI1 global interrupt */
#define IRQ_NUM_SPI2               36  /*!< SPI2 global interrupt */

#define IRQ_NUM_USART1             37  /*!< USART1 global interrupt */
#define IRQ_NUM_USART2             38  /*!< USART2 global interrupt */
#define IRQ_NUM_USART3             39  /*!< USART3 global interrupt */

#define IRQ_NUM_EXTI15_10          40  /*!< EXTI Line[15:10] interrupts */

#define IRQ_NUM_RTC_ALARM          41  /*!< RTC Alarms via EXTI line interrupt */
#define IRQ_NUM_OTG_FS_WKUP        42  /*!< USB OTG FS Wakeup through EXTI */

#define IRQ_NUM_TIM8_BRK_TIM12     43  /*!< TIM8 Break and TIM12 interrupt */
#define IRQ_NUM_TIM8_UP_TIM13      44  /*!< TIM8 Update and TIM13 interrupt */
#define IRQ_NUM_TIM8_TRG_COM_TIM14 45  /*!< TIM8 Trigger/Commutation and TIM14 interrupt */
#define IRQ_NUM_TIM8_CC            46  /*!< TIM8 Capture Compare interrupt */

#define IRQ_NUM_DMA1_STREAM7       47  /*!< DMA1 Stream7 global interrupt */

#define IRQ_NUM_FSMC               48  /*!< FSMC global interrupt */
#define IRQ_NUM_SDIO               49  /*!< SDIO global interrupt */

#define IRQ_NUM_TIM5               50  /*!< TIM5 global interrupt */

#define IRQ_NUM_SPI3               51  /*!< SPI3 global interrupt */

#define IRQ_NUM_UART4              52  /*!< UART4 global interrupt */
#define IRQ_NUM_UART5              53  /*!< UART5 global interrupt */

#define IRQ_NUM_TIM6_DAC           54  /*!< TIM6 global and DAC underrun interrupt */
#define IRQ_NUM_TIM7               55  /*!< TIM7 global interrupt */

#define IRQ_NUM_DMA2_STREAM0       56  /*!< DMA2 Stream0 global interrupt */
#define IRQ_NUM_DMA2_STREAM1       57  /*!< DMA2 Stream1 global interrupt */
#define IRQ_NUM_DMA2_STREAM2       58  /*!< DMA2 Stream2 global interrupt */
#define IRQ_NUM_DMA2_STREAM3       59  /*!< DMA2 Stream3 global interrupt */
#define IRQ_NUM_DMA2_STREAM4       60  /*!< DMA2 Stream4 global interrupt */

#define IRQ_NUM_ETH                61  /*!< Ethernet global interrupt */
#define IRQ_NUM_ETH_WKUP           62  /*!< Ethernet Wakeup through EXTI */

#define IRQ_NUM_CAN2_TX            63  /*!< CAN2 TX interrupts */
#define IRQ_NUM_CAN2_RX0           64  /*!< CAN2 RX0 interrupts */
#define IRQ_NUM_CAN2_RX1           65  /*!< CAN2 RX1 interrupts */
#define IRQ_NUM_CAN2_SCE           66  /*!< CAN2 SCE interrupts */

#define IRQ_NUM_OTG_FS             67  /*!< USB OTG FS global interrupt */

#define IRQ_NUM_DMA2_STREAM5       68  /*!< DMA2 Stream5 global interrupt */
#define IRQ_NUM_DMA2_STREAM6       69  /*!< DMA2 Stream6 global interrupt */
#define IRQ_NUM_DMA2_STREAM7       70  /*!< DMA2 Stream7 global interrupt */

#define IRQ_NUM_USART6             71  /*!< USART6 global interrupt */

#define IRQ_NUM_I2C3_EV            72  /*!< I2C3 event interrupt */
#define IRQ_NUM_I2C3_ER            73  /*!< I2C3 error interrupt */

#define IRQ_NUM_OTG_HS_EP1_OUT     74  /*!< USB OTG HS EP1 OUT interrupt */
#define IRQ_NUM_OTG_HS_EP1_IN      75  /*!< USB OTG HS EP1 IN interrupt */
#define IRQ_NUM_OTG_HS_WKUP        76  /*!< USB OTG HS Wakeup interrupt */
#define IRQ_NUM_OTG_HS             77  /*!< USB OTG HS global interrupt */

#define IRQ_NUM_DCMI               78  /*!< DCMI global interrupt */
#define IRQ_NUM_CRYP               79  /*!< Crypto global interrupt */
#define IRQ_NUM_HASH_RNG           80  /*!< Hash and RNG global interrupt */

#define IRQ_NUM_FPU                81  /*!< Floating Point Unit global interrupt */

/** @} */





#endif /* INC_STM32F407XX_H_ */
