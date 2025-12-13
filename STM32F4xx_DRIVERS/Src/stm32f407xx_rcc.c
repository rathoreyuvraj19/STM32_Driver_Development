/*
 * stm32f407xx_rcc.c
 *
 *  Created on: Dec 13, 2025
 *      Author: ratho
 */

#include "stm32f407xx_rcc.h"
#include "stm32f407xx_uart.h"



static const uint32_t AHB_PRESCALER_TABLE[16] = {1,1,1,1,1,1,1,1,
											2,4,8,16,64,128,256,512};
static const uint8_t APB_PRESCALER_TABLE[8] = {1,1,1,1,
											2,4,8,16};

static uint32_t RCC_Get_PLL_CLK(void){
	//1.Identify the PLL Source using PPLSRC bit of PLLCFGR register
	uint8_t PLL_SRC = (RCC->PLLCFGR >> 22) & 0x1 ;
	uint32_t PLL_CLK_Freq = 0;
	if(PLL_SRC == 0){ // PLL Src is HSI
		PLL_CLK_Freq = HSI_Freq;
	}else if(PLL_SRC == 1){// PLL Src is HSE
		PLL_CLK_Freq = HSE_Freq;
	}
	//2. Extract PLLM, PLLN, PLLP factors
	uint8_t PLLM = RCC->PLLCFGR & 0x3f;
	if(PLLM < 2){
		return 0;
	}
	uint16_t PLLN = (RCC->PLLCFGR >> 6) & 0x1FF;
	if(!(PLLN>=50 && PLLN <=432)){
		return 0;
	}
	uint8_t PLLP = (RCC->PLLCFGR>>16) & 0x3;
	if(PLLP==0){
		PLLP = 2;
	}else if(PLLP==1){
		PLLP = 4;
	}else if(PLLP==2){
		PLLP = 6;
	}else if(PLLP==3){
		PLLP = 8;
	}

	return (PLL_CLK_Freq / PLLM) * PLLN / PLLP;
}

static uint32_t RCC_Get_SYSCLK_Freq(void){
	//1. First Identify the SYS CLOCK Source
	uint8_t clk_src = (RCC->CFGR>>2) & 0x3;

	//2. Get the AHB Prescaler
	uint32_t AHB_Prescaler = AHB_PRESCALER_TABLE[(RCC->CFGR>>4) & 0xF];
	if(clk_src == CLK_SRC_HSI){//SRC is HSI
		return HSI_Freq/AHB_Prescaler;
	}else if(clk_src == CLK_SRC_HSE){// SRC is HSE
		return HSE_Freq/AHB_Prescaler;
	}else if(clk_src == CLK_SRC_PLL){//SRC is PLL
		uint32_t PLL_CLK = RCC_Get_PLL_CLK();
		if(PLL_CLK == 0){
			return 0;
		}
		return (PLL_CLK/AHB_Prescaler);
	}
	return 0;
}

uint32_t RCC_GetPCLK1Freq(void){
	uint8_t RCC_CFGR_PPRE1 = (RCC->CFGR >> 10) & 0x7;
	uint32_t SYS_CLK_FREQ = RCC_Get_SYSCLK_Freq();
	if(SYS_CLK_FREQ==0){
		return 0;
	}
	return SYS_CLK_FREQ/APB_PRESCALER_TABLE[RCC_CFGR_PPRE1];
}

uint32_t RCC_GetPCLK2Freq(void){
	uint8_t RCC_CFGR_PPRE2 = (RCC->CFGR >> 13) & 0x7;
	uint32_t SYS_CLK_FREQ = RCC_Get_SYSCLK_Freq();
	if(SYS_CLK_FREQ==0){
		return 0;
	}
	return SYS_CLK_FREQ/APB_PRESCALER_TABLE[RCC_CFGR_PPRE2];
}

uint32_t RCC_GetUSARTClock(UART_Reg_Def_t* USARTx){
	if(USARTx == UART1 || USARTx == UART6){
		return RCC_GetPCLK2Freq();
	}else if(USARTx == UART2|| USARTx == UART3 || USARTx == UART4 || USARTx == UART5){
		return RCC_GetPCLK1Freq();
	}
	return 0;
}
