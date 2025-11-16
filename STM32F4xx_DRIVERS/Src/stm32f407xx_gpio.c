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
			GPIOx_Handle->pGPIOx->AFRL |= (gpio_alt_func
					<< (4 * (gpio_pin_number % 8)));
		} else { /*We have to configure AFRH */
			GPIOx_Handle->pGPIOx->AFRH &= ~(0xF << (4 * (gpio_pin_number % 8)));
			GPIOx_Handle->pGPIOx->AFRH |= (gpio_alt_func
					<< (4 * (gpio_pin_number % 8)));
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
	uint8_t temp = (uint8_t) ((pGPIOx->IDR >> pin) & 0x1);
	return temp;
}

uint16_t gpio_read_port(GPIOx_RegDef_t *pGPIOx) {
	return (uint16_t) (pGPIOx->IDR);
}

void gpio_write_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t state) {
	if (state) {
		pGPIOx->ODR |= ((1 << pin));
	} else {
		pGPIOx->ODR &= ~((1 << pin));
	}
}

void gpio_write_port(GPIOx_RegDef_t *pGPIOx, uint16_t write_data) {
	pGPIOx->ODR = write_data;
}

void gpio_toggle_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin) {
	if (pin > 15)
		return;
	pGPIOx->ODR ^= (0x01 << pin);
}

void gpio_irq_config(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t trigger,
		uint8_t irq_priority) {
	/**
	 * Sequence of steps in gpio_irq_config() API:
	 * 1. Program SYSCFG
	 * 2. Program EXTI
	 * 3. Program Trigger mode
	 * 4. Clear pending interrupt
	 * 5. Unmask EXTI line
	 * 6. Sets NVIC priority
	 */
	/** --------------------------------------------------------------------
	 * 1. Enable SYSCFG Peripheral Clock
	 *
	 * The EXTI configuration registers (EXTICR1–4) reside inside SYSCFG.
	 * We must enable its clock before accessing them.
	 * -------------------------------------------------------------------- */
	SYSCFG_PCLK_EN();

	/** Pointer to access SYSCFG register block */
	SYSCFG_RegDef_t *pSYSCFG = SYSCFG;

	/** --------------------------------------------------------------------
	 * 2. Determine which EXTICR register to use
	 *
	 * Each EXTICR register configures 4 pins:
	 *   EXTICR1 → EXTI0..3
	 *   EXTICR2 → EXTI4..7
	 *   EXTICR3 → EXTI8..11
	 *   EXTICR4 → EXTI12..15
	 *
	 * Index is pin / 4:
	 *   pin 0–3   → 0
	 *   pin 4–7   → 1
	 *   pin 8–11  → 2
	 *   pin 12–15 → 3
	 * -------------------------------------------------------------------- */
	uint8_t sys_cfg_reg_number = pin / 4;

	/** --------------------------------------------------------------------
	 * 3. Determine GPIO port code for mapping
	 *
	 * SYSCFG_EXTICR expects:
	 *   0x0 = Port A
	 *   0x1 = Port B
	 *   0x2 = Port C
	 *   ...
	 *   0x8 = Port I
	 * -------------------------------------------------------------------- */
	uint8_t gpio_port_map;

	if (pGPIOx == GPIOA)
		gpio_port_map = 0x00;
	else if (pGPIOx == GPIOB)
		gpio_port_map = 0x01;
	else if (pGPIOx == GPIOC)
		gpio_port_map = 0x02;
	else if (pGPIOx == GPIOD)
		gpio_port_map = 0x03;
	else if (pGPIOx == GPIOE)
		gpio_port_map = 0x04;
	else if (pGPIOx == GPIOF)
		gpio_port_map = 0x05;
	else if (pGPIOx == GPIOG)
		gpio_port_map = 0x06;
	else if (pGPIOx == GPIOH)
		gpio_port_map = 0x07;
	else if (pGPIOx == GPIOI)
		gpio_port_map = 0x08;
	else
		return; /** Invalid GPIO pointer */

	/** --------------------------------------------------------------------
	 * 4. Configure the correct SYSCFG_EXTICR register
	 *
	 * Each pin gets 4 bits inside its EXTICR register:
	 *   Bits = 4 × (pin % 4)
	 *
	 * Steps:
	 *  - Clear the 4-bit field for the selected EXTI line
	 *  - Write GPIO port code to select the source input
	 * -------------------------------------------------------------------- */
	uint8_t shift_amount = 4 * (pin % 4);

	if (sys_cfg_reg_number == 0) {
		/** Configure EXTI0–3 */
		pSYSCFG->EXTICR1 &= ~(0xF << shift_amount);
		pSYSCFG->EXTICR1 |= (gpio_port_map << shift_amount);
	} else if (sys_cfg_reg_number == 1) {
		/** Configure EXTI4–7 */
		pSYSCFG->EXTICR2 &= ~(0xF << shift_amount);
		pSYSCFG->EXTICR2 |= (gpio_port_map << shift_amount);
	} else if (sys_cfg_reg_number == 2) {
		/** Configure EXTI8–11 */
		pSYSCFG->EXTICR3 &= ~(0xF << shift_amount);
		pSYSCFG->EXTICR3 |= (gpio_port_map << shift_amount);
	} else if (sys_cfg_reg_number == 3) {
		/** Configure EXTI12–15 */
		pSYSCFG->EXTICR4 &= ~(0xF << shift_amount);
		pSYSCFG->EXTICR4 |= (gpio_port_map << shift_amount);
	}

	/** 3. Setting rising/falling trigger or both */
	EXTI_RegDef_t *pEXTI = EXTI;
	pEXTI->RTSR &= ~(1 << pin);
	pEXTI->FTSR &= ~(1 << pin);
	if (trigger == INTERRUPT_TRIGGER_TYPE_RISING) {
		pEXTI->RTSR |= (1 << pin);
	} else if (trigger == INTERRUPT_TRIGGER_TYPE_FALLING) {
		pEXTI->FTSR |= (1 << pin);
	} else if (trigger == INTERRUPT_TRIGGER_TYPE_BOTH) {
		pEXTI->RTSR |= (1 << pin);
		pEXTI->FTSR |= (1 << pin);
	}

	/** 4 Clearing the pending interrupt. A interrupt is clearing by writing 1 to EXTI_PR Register */
	pEXTI->PR |= (1 << pin);

	/** 5. After Clearing the pending bit. Now unmask the interrupt.*/
	pEXTI->IMR |= (1 << pin);

	/** 6. Finally, configure the NVIC interrupt priority */

	uint8_t irq;

	/* Step 1: Identify which IRQ vector corresponds to the EXTI line */
	if (pin <= 4) {
		/* EXTI0 → IRQ6, EXTI1 → IRQ7, ... EXTI4 → IRQ10 */
		irq = IRQ_NUM_EXTI0 + pin;
	} else if (pin <= 9) {
		/* EXTI5–9 all map to EXTI9_5 shared IRQ */
		irq = IRQ_NUM_EXTI9_5;
	} else {
		/* EXTI10–15 all map to EXTI15_10 shared IRQ */
		irq = IRQ_NUM_EXTI15_10;
	}

	/* Step 2: Compute the NVIC IPR register and byte offset */
	NVIC_RegDef_t *pNVIC = NVIC;
	uint8_t ipr_index = irq / 4;          // Each IPR holds 4 priority fields
	uint8_t ipr_offset = (irq % 4) * 8;   // Select correct byte
	ipr_offset += 4;                    // Priority uses only upper 4 bits [7:4]

	/*
	 * Step 3: Clear the old priority
	 * We clear a full byte (even though only 4 bits are used),
	 * because NVIC ignores the lower 4 bits anyway.
	 */
	pNVIC->IPR[ipr_index] &= ~(0xFF << ipr_offset);

	/*
	 * Step 4: Write new priority
	 * irq_priority is masked to 4 bits (0–15),
	 * then shifted into bits [7:4] of the correct byte.
	 */
	pNVIC->IPR[ipr_index] |= ((irq_priority & 0x0F) << ipr_offset);
}

void gpio_irq_clear(uint8_t pin) {
	EXTI_RegDef_t *pEXTI = EXTI;
	pEXTI->PR |= (1 << pin);
}

void gpio_irq_control(uint8_t pin, uint8_t en_di) {
	/** @note This API only controls EXTI GPIO interrupts (EXTI0–EXTI15).
	 *
	 * Steps to ENABLE a GPIO EXTI interrupt:
	 * 1. Unmask the EXTI line in EXTI_IMR
	 * 2. Enable the corresponding NVIC interrupt via NVIC_ISER
	 * 3. (Optional but recommended) Clear any pending EXTI flag using @ref gpio_irq_clear()
	 * Try to follow the sequence, to avoid race condition
	 *
	 * Steps to DISABLE a GPIO EXTI interrupt:
	 * 1. Disable the corresponding NVIC interrupt via NVIC_ICER
	 * 2. Mask the EXTI line in EXTI_IMR
	 * 3. Clear any pending EXTI flag using @ref gpio_irq_clear()
	 * Try to follow the sequence, to avoid race around condition
	 *
	 * @note Only EXTI->PR must be written to clear pending interrupts.
	 *       Writing 1 to EXTI_PR clears both the EXTI and NVIC pending state.
	 *       No need to write to NVIC->ICPR for EXTI lines.
	 */

	NVIC_RegDef_t *pNVIC = NVIC;
	EXTI_RegDef_t *pEXTI = EXTI;

	if (en_di == ENABLE) {
		// 1. Unmask the EXTI line in EXTI_IMR
		pEXTI->IMR |= (1 << pin);
		// 2. Enable the corresponding NVIC interrupt via NVIC_ISER
		uint8_t irq;
		if (pin <= 4) {
			/* EXTI0 → IRQ6, EXTI1 → IRQ7, ... EXTI4 → IRQ10 */
			irq = IRQ_NUM_EXTI0 + pin;
			pNVIC->ISER[0] |= (1 << irq);
		} else if (pin <= 9) {
			/* EXTI5–9 all map to EXTI9_5 shared IRQ */
			irq = IRQ_NUM_EXTI9_5;
			pNVIC->ISER[0] |= (1 << irq);
		} else {
			/* EXTI10–15 all map to EXTI15_10 shared IRQ */
			irq = IRQ_NUM_EXTI15_10;
			pNVIC->ISER[1] |= (1 << (irq % 32));
		}
		// 3. Clear the Pending interrupt.
		gpio_irq_clear(pin);
	} else {                      //Disable interrupt
		// 1. Mask the EXTI line in EXTI_IMR
		pEXTI->IMR &= ~(1 << pin);
		// 2. Disable the corresponding NVIC interrupt via NVIC_ISER
		uint8_t irq;
		if (pin <= 4) {
			/* EXTI0 → IRQ6, EXTI1 → IRQ7, ... EXTI4 → IRQ10 */
			irq = IRQ_NUM_EXTI0 + pin;
			pNVIC->ICER[0] |= (1 << irq);
		} else if (pin <= 9) {
			/* EXTI5–9 all map to EXTI9_5 shared IRQ */
			irq = IRQ_NUM_EXTI9_5;
			pNVIC->ICER[0] |= (1 << irq);
		} else {
			/* EXTI10–15 all map to EXTI15_10 shared IRQ */
			irq = IRQ_NUM_EXTI15_10;
			pNVIC->ICER[1] |= (1 << (irq % 32));
		}
		// 3. Clear the Pending interrupt.
		gpio_irq_clear(pin);
	}
}

