/**
 ******************************************************************************
 * @file    stm32f407xx_gpio.c
 * @author  Yuvraj Singh Rathore
 * @version 1.0
 * @date    13-Nov-2025
 * @brief   GPIO peripheral driver source file for STM32F407xx MCU.
 *
 * @details
 * This file implements low-level GPIO driver functions using direct register
 * access for deterministic timing and optimal performance. It provides APIs for:
 *
 *  - Initializing and de-initializing GPIO ports and pins
 *  - Configuring pin modes, speeds, output types, pull-up/pull-down settings
 *  - Reading from and writing to pins or entire ports
 *  - Managing alternate functions and EXTI interrupt configuration
 *
 * @note Ensure the GPIO peripheral clock is enabled before calling any API.
 * @attention Bare-metal driver without HAL/StdPeriph dependencies.
 *
 * @section GPIO_API_Summary GPIO Driver API Summary
 *
 * - gpio_pin_init()    : Configure a GPIO pin (mode, type, speed, pull, AF)
 * - gpio_port_deinit() : Reset an entire GPIO port
 * - gpio_read_pin()    : Read the logic level of a pin
 * - gpio_read_port()   : Read the 16-bit input state of a port
 * - gpio_write_pin()   : Write HIGH/LOW to a pin
 * - gpio_write_port()  : Write 16-bit value to a port
 * - gpio_toggle_pin()  : Toggle pin output level
 * - gpio_irq_config()  : Configure EXTI trigger type
 * - gpio_irq_control() : Enable/disable NVIC interrupt for GPIO EXTI line
 * - gpio_irq_clear()   : Clear EXTI pending flag
 *
 * @see stm32f407xx_gpio.h
 ******************************************************************************
 */

#include "stm32f407xx_gpio.h"

void gpio_pin_init(GPIOx_Handle_t *GPIOx_Handle) {
	uint8_t gpio_pin_number = GPIOx_Handle->GPIO_CONFIG.GPIO_PIN_NUMBER;
	uint8_t gpio_mode = GPIOx_Handle->GPIO_CONFIG.GPIO_MODE;
	uint8_t gpio_speed = GPIOx_Handle->GPIO_CONFIG.GPIO_SPEED;
	uint8_t gpio_output_type = GPIOx_Handle->GPIO_CONFIG.GPIO_OP_TYPE;
	uint8_t gpio_pu_pd = GPIOx_Handle->GPIO_CONFIG.GPIO_PU_PD;
	uint8_t gpio_alt_func = GPIOx_Handle->GPIO_CONFIG.GPIO_ALT_FUNC;
	/*1. Enable the respective GPIO peripheral through RCC */
	if (GPIOx_Handle->pGPIOx == GPIOA) {
		GPIOA_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOB) {
		GPIOB_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOC) {
		GPIOC_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOD) {
		GPIOD_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOE) {
		GPIOE_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOF) {
		GPIOF_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOG) {
		GPIOG_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOH) {
		GPIOH_PCLK_EN();
	} else if (GPIOx_Handle->pGPIOx == GPIOI) {
		GPIOI_PCLK_EN();
	}
	/*2.Set the pin mode */
	GPIOx_Handle->pGPIOx->MODER &= ~(0x03 << (2 * gpio_pin_number)); /* Clear the bits */
	GPIOx_Handle->pGPIOx->MODER |= (gpio_mode << (2 * gpio_pin_number)); /* Set the desire bits */

	/* 3. Set the GPIO Speed. @note: speed is applicable only for output and alt-function mode */
	if (gpio_mode == GPIO_MODE_OUTPUT || gpio_mode == GPIO_MODE_ALT_FUNC) {
		GPIOx_Handle->pGPIOx->OSPEEDR &= ~(0x03 << (2 * gpio_pin_number)); /* Clear the bits */
		GPIOx_Handle->pGPIOx->OSPEEDR |= (gpio_speed << (2 * gpio_pin_number)); /* Set the desire bit */
	}
	/* 4. Set the output type (Push_pull/Open_Drain). @note This part is only applicable when mode is output or alternate Function */
	if (gpio_mode == GPIO_MODE_OUTPUT || gpio_mode == GPIO_MODE_ALT_FUNC) {
		GPIOx_Handle->pGPIOx->OTYPER &= ~(0x1 << gpio_pin_number); /* Clear the bits */
		GPIOx_Handle->pGPIOx->OTYPER |= (gpio_output_type << gpio_pin_number); /* Set the desire bit */
	}

	/* 5. Set the pullup or pulldown config. @note this config is only applicable when mode is output or alternate function or input */
	if (gpio_mode != GPIO_MODE_ANALOG) {
		GPIOx_Handle->pGPIOx->PUPDR &= ~(0x03 << (2 * gpio_pin_number)); /* Clear the bits */
		GPIOx_Handle->pGPIOx->PUPDR |= (gpio_pu_pd << (2 * gpio_pin_number)); /* Set the desire bit */
	}

	/*  6. Setting ALT FUNCTION config. @note this config is only applicable when mode is ALT FUNC MODE */
	if (gpio_mode == GPIO_MODE_ALT_FUNC) {
		if (gpio_pin_number <= 7) { /*We have to configure AFRL */
			GPIOx_Handle->pGPIOx->AFRL &= ~(0xF << (4 * (gpio_pin_number % 8)));
			GPIOx_Handle->pGPIOx->AFRL |= (gpio_alt_func << (4 * (gpio_pin_number % 8)));
		} else { /*We have to configure AFRH */
			GPIOx_Handle->pGPIOx->AFRH &= ~(0xF << (4 * (gpio_pin_number % 8)));
			GPIOx_Handle->pGPIOx->AFRH |= (gpio_alt_func << (4 * (gpio_pin_number % 8)));
		}
	}

}

void gpio_port_deinit(GPIOx_RegDef_t *pGPIOx) {
	if (pGPIOx == GPIOA) {
//		RCC->AHB1RSTR |= (1 << 0); 	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 0);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOA_RESET();
	} else if (pGPIOx == GPIOB) {
//		RCC->AHB1RSTR |= (1 << 1); 	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 1);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOB_RESET();
	} else if (pGPIOx == GPIOC) {
//		RCC->AHB1RSTR |= (1 << 2); 	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 2);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOC_RESET();
	} else if (pGPIOx == GPIOD) {
//		RCC->AHB1RSTR |= (1 << 3);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 3);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOD_RESET();
	} else if (pGPIOx == GPIOE) {
//		RCC->AHB1RSTR |= (1 << 4);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 4);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOE_RESET();
	} else if (pGPIOx == GPIOF) {
//		RCC->AHB1RSTR |= (1 << 5);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 5);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOF_RESET();
	} else if (pGPIOx == GPIOG) {
//		RCC->AHB1RSTR |= (1 << 6);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 6);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOG_RESET();
	} else if (pGPIOx == GPIOH) {
//		RCC->AHB1RSTR |= (1 << 7);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 7);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOH_RESET();
	} else if (pGPIOx == GPIOI) {
//		RCC->AHB1RSTR |= (1 << 8);	/* Assert the reset bit */
//		RCC->AHB1RSTR &= ~(1 << 8);	/* De-assert the reset bit */
		// Instead of this we will use macros.
		GPIOI_RESET();
	}
}

uint8_t gpio_read_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin) {
	if (pin > 15)
		return 0; /** @note Safety: Pin number cannot be more than 15 */
	return (uint8_t) ((pGPIOx->IDR >> pin) & 0x1);
}

uint16_t gpio_read_port(GPIOx_RegDef_t *pGPIOx) {
	return (uint16_t) (pGPIOx->IDR);
}

void gpio_write_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t state) {
	pGPIOx->ODR |= ((state << pin));
}

void gpio_write_port(GPIOx_RegDef_t *pGPIOx, uint16_t write_data) {
	pGPIOx->ODR = write_data;
}

void gpio_toggle_pin(GPIOx_RegDef_t* pGPIOx, uint8_t pin){
	if (pin > 15) return;
	pGPIOx->ODR ^= (0x01<<pin);
}























