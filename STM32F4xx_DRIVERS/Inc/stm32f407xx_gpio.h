/**
 ******************************************************************************
 * @file    stm32f407xx_gpio.h
 * @author  Yuvraj Singh
 * @brief   GPIO Driver Header for STM32F407xx MCU
 *
 * This file contains:
 *   - GPIO register definition structure
 *   - GPIO configuration structure
 *   - GPIO handle structure
 *   - Supported macro definitions for GPIO modes, speed, pull-up/pull-down,
 *     output types, and alternate functions.
 *   - Doxygen-compliant documentation for easy code navigation and API usage.
 *
 * @version 1.0
 * @date    14-Nov-2025
 ******************************************************************************
 */

#ifndef INC_STM32F407XX_GPIO_H_
#define INC_STM32F407XX_GPIO_H_

#include "stm32f407xx.h"

/**
 * @defgroup GPIO_Driver GPIO Driver
 * @brief    STM32F407xx General Purpose I/O Driver
 * @{
 */

/**
 * @defgroup GPIO_Config_Structure GPIO Enumerations
 * @brief    Configuration parameters for a single GPIO pin.
 * @{
 */

/**
 * @defgroup GPIO_MODES GPIO Pin Modes
 * @brief GPIO mode configuration macros.
 * @{
 */

#define GPIO_MODE_INPUT      0  /*!< Input floating / input with pull-up/down */
#define GPIO_MODE_OUTPUT     1  /*!< General-purpose output mode */
#define GPIO_MODE_ALT_FUNC   2  /*!< Alternate function mode */
#define GPIO_MODE_ANALOG     3  /*!< Analog mode */

/** @} */ /* end of GPIO_Modes */

/**
 * @defgroup GPIO_OP_TYPES GPIO Output Types
 * @brief GPIO pin output driver configuration macros.
 * @{
 */

#define GPIO_OP_TYPE_PP 	0	/*!< Output Type Push Pull */
#define GPIO_OP_TYPE_OD 	1	/*!< Output Type Open Drain */


/** @} */ /* end of GPIO_OUTPUT_TYPES */

/**
 * @defgroup GPIO_PULLUP_PULLDOWN GPIO Pull-Up/Pull-Down Options
 * @brief GPIO internal resistor configuration macros.
 * @{
 */

#define GPIO_PU_PD_NONE        0   /*!< No pull-up or pull-down */
#define GPIO_PU_PD_PULL_UP     1   /*!< Enable internal pull-up */
#define GPIO_PU_PD_PULL_DOWN   2   /*!< Enable internal pull-down */

/** @} */ /* end of GPIO_PULLUP_PULLDOWN */

/**
 * @defgroup GPIO_PULLUP_PULLDOWN GPIO Pull-Up/Pull-Down Options
 * @brief GPIO internal resistor configuration macros.
 * @{
 */

#define GPIO_PU_PD_NONE        0   /*!< No pull-up or pull-down */
#define GPIO_PU_PD_PULL_UP     1   /*!< Enable internal pull-up */
#define GPIO_PU_PD_PULL_DOWN   2   /*!< Enable internal pull-down */

/** @} */ /* end of GPIO_PULLUP_PULLDOWN */

/**
 * @defgroup GPIO_SPEEDS GPIO Speed Options
 * @brief GPIO output speed configuration macros.
 * @{
 */

#define GPIO_SPEED_LOW         0   /*!< Low speed (2 MHz) */
#define GPIO_SPEED_MEDIUM      1   /*!< Medium speed (25 MHz) */
#define GPIO_SPEED_HIGH        2   /*!< High speed (50 MHz) */
#define GPIO_SPEED_VERY_HIGH   3   /*!< Very high speed (100 MHz) */

/** @} */ /* end of GPIO_SPEEDS */

/**
 * @defgroup GPIO_ALTERNATE_FUNCTIONS GPIO Alternate Function Options
 * @brief GPIO alternate function selection macros (AF0–AF15).
 * @{
 */

#define GPIO_ALT_FUNC_0     0   /*!< Alternate Function 0 */
#define GPIO_ALT_FUNC_1     1   /*!< Alternate Function 1 */
#define GPIO_ALT_FUNC_2     2   /*!< Alternate Function 2 */
#define GPIO_ALT_FUNC_3     3   /*!< Alternate Function 3 */
#define GPIO_ALT_FUNC_4     4   /*!< Alternate Function 4 */
#define GPIO_ALT_FUNC_5     5   /*!< Alternate Function 5 */
#define GPIO_ALT_FUNC_6     6   /*!< Alternate Function 6 */
#define GPIO_ALT_FUNC_7     7   /*!< Alternate Function 7 */
#define GPIO_ALT_FUNC_8     8   /*!< Alternate Function 8 */
#define GPIO_ALT_FUNC_9     9   /*!< Alternate Function 9 */
#define GPIO_ALT_FUNC_10   10   /*!< Alternate Function 10 */
#define GPIO_ALT_FUNC_11   11   /*!< Alternate Function 11 */
#define GPIO_ALT_FUNC_12   12   /*!< Alternate Function 12 */
#define GPIO_ALT_FUNC_13   13   /*!< Alternate Function 13 */
#define GPIO_ALT_FUNC_14   14   /*!< Alternate Function 14 */
#define GPIO_ALT_FUNC_15   15   /*!< Alternate Function 15 */

/** @} */ /* end of GPIO_ALTERNATE_FUNCTIONS */

/**
 * @brief GPIO Configuration Structure
 *
 * This structure holds the configuration settings for a GPIO pin.
 * It is used to initialize the GPIO peripheral in the desired mode.
 *
 * @note Each member corresponds to a hardware field in the GPIO registers.
 */
typedef struct {
    uint8_t GPIO_PIN_NUMBER;   /*!< Specifies the GPIO pin number (0–15).
                                   @ref GPIO_PIN_NUMBERS */

    uint8_t GPIO_MODE;        /*!< Specifies the mode of the pin.
                                   Value must be from @ref GPIO_MODES. */

    uint8_t GPIO_OP_TYPE;     /*!< Specifies the output type (Push-pull/Open-drain).
                                   Value must be from @ref GPIO_OUTPUT_TYPES. */

    uint8_t GPIO_PU_PD;       /*!< Select Pull-up/Pull-down mode.
                                   Value must be from @ref GPIO_PULLUP_PULLDOWN. */

    uint8_t GPIO_SPEED;       /*!< Specifies GPIO output speed.
                                   Value must be from @ref GPIO_SPEEDS. */

    uint8_t GPIO_ALT_FUNC;    /*!< Alternate function mode (AF0–AF15).
                                   Value must be from @ref GPIO_ALTERNATE_FUNCTIONS. */
} GPIOx_Config_t;

/** @} */ /* End of GPIO_Config_Structure */

/**
 * @defgroup GPIO_Handle_Structure GPIO Handle Structure
 * @brief    Structure for combining configuration and register base address.
 * @{
 */

/**
 * @brief GPIO Handle Structure
 *
 * The GPIO handle structure binds:
 *   - A pointer to the GPIO peripheral register definition (`pGPIOx`)
 *   - A configuration structure (`GPIO_Config`)
 *
 * It is passed to all GPIO driver APIs to operate on a pin/port.
 */
typedef struct {
    GPIOx_RegDef_t *pGPIOx;   /*!< Pointer to GPIO peripheral base address.
                                   Refer to @ref GPIO_Base_Address. */

    GPIOx_Config_t  GPIO_CONFIG; /*!< GPIO pin configuration settings. */
} GPIOx_Handle_t;

/** @} */ /* End of GPIO_Handle_Structure */


/*================================================================================
 *===============================GPIO_Driver_APIs=================================
 ================================================================================*/
/**
 * @defgroup GPIO_Driver_APIs GPIO Driver Function Prototypes
 * @brief Public API functions for GPIO configuration and control.
 * @{
 */


/**
 * @brief Initialize a GPIO pin.
 * @param handle Pointer to GPIO handle structure
 * @retval void
 */
void gpio_pin_init(GPIOx_Handle_t *handle);

/**
 * @brief De-initialize a GPIO port.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @retval void
 * @note RCC Reset Register can be used to reset a periph eral
 */
void gpio_port_deinit(GPIOx_RegDef_t *pGPIOx);

/**
 * @brief Read a GPIO pin.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @param Pin number from which you want to read
 * @retval uint8_t Single bit read for the specified pin
 */
uint8_t gpio_read_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);

/**
 * @brief Read the entire GPIO input port.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @retval uint16_t Current 16-bit value of the input data register.
 */
uint16_t gpio_read_port(GPIOx_RegDef_t *pGPIOx);

/**
 * @brief Write HIGH/LOW to a pin.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @param Pin number to which you want to write.
 * @param State you want to set, Set/Reset @ref MISCELLANEOUS_MACROS
 * @retval void
 */
void gpio_write_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t state);

/**
 * @brief Write a 16-bit value to the entire GPIO output port.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @param write_data 16-bit data to write to the GPIO port.
 * @retval void
 */
void gpio_write_port(GPIOx_RegDef_t *pGPIOx, uint16_t write_data);

/**
 * @brief Toggle the logic level of a GPIO output pin.
 * @param pGPIOx Pointer to the GPIO port base address. @ref GPIO_BASE_ADDRESSES
 * @param pin Pin number to toggle (0–15).
 */
void gpio_toggle_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);

/**
 * @brief Configure a GPIO pin as an external interrupt (EXTI).
 *
 * This API configures the selected GPIO pin for external interrupt usage by:
 * - Mapping the GPIO port to the correct EXTI line using SYSCFG
 * - Configuring the trigger type (rising/falling/both)
 * - Enabling the interrupt line in EXTI
 * - Setting the NVIC priority for the corresponding EXTI IRQ
 *
 * @param pGPIOx       Pointer to the GPIO port (GPIOA, GPIOB, ...) @ref GPIO_BASE_ADDRESSES
 * @param pin          GPIO pin number (0–15) @ref GPIO_PIN_NUMBER_MACROS
 * @param trigger      Interrupt trigger selection @ref INTERRUPT_TRIGGER_TYPE_MACROS
 * @param irq_priority NVIC priority for the EXTI interrupt (0 = highest)
 */
void gpio_irq_config(GPIOx_RegDef_t *pGPIOx,
                     uint8_t pin,
                     uint8_t trigger,
                     uint8_t irq_priority);

/**
 * @brief Enable or disable NVIC interrupt for a GPIO EXTI line.
 *
 * @param pin    GPIO pin number (0–15), used to determine EXTI line.
 * @param en_di  ENABLE or DISABLE.
 *
 * @note This function only updates NVIC enable registers.
 *       It does NOT configure EXTI, SYSCFG, or trigger polarity.
 */
void gpio_irq_control(uint8_t pin, uint8_t en_di);

/**
 * @brief Clears the interrupt pending flag for the specified EXTI line.
 *
 * @param pin  GPIO pin number (0–15) associated with the EXTI line.
 *
 * @note  This function writes a '1' to the EXTI_PR register bit.
 *        Clearing the EXTI pending bit also clears the corresponding
 *        NVIC pending state automatically — no NVIC action is needed.
 */
void gpio_irq_clear(uint8_t pin);

/** @} */ /* end of GPIO_Driver_APIs */

/** @} */ /* End of GPIO_Driver */
#endif /* INC_STM32F407XX_GPIO_H_ */ //@yuvraj
