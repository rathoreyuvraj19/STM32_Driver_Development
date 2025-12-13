

#include "stm32f407xx_rcc.h"
#include "stm32f407xx_uart.h"
#include "stm32f407xx_gpio.h"
#include "LCD.h"

LCD_Def_t LCD_Def;
void LCD_Inititalize(){
	delayUS(2 * 10000); // After power on wait for 1.5 ms minimum
	LCD_Init(&LCD_Def);

	LCD_Command_Send(&LCD_Def,0x80);
	LCD_Command_Send(&LCD_Def,0x0F);
}
//void USART1_GPIO_Init(){
//	GPIOx_Handle_t GPIOB_Handle;
//	GPIOB_Handle.pGPIOx = GPIOB;
//	GPIOB_Handle.GPIO_CONFIG.GPIO_MODE = GPIO_MODE_ALT_FUNC;
//	GPIOB_Handle.GPIO_CONFIG.GPIO_ALT_FUNC = GPIO_ALT_FUNC_7;
//	GPIOB_Handle.GPIO_CONFIG.GPIO_SPEED = GPIO_SPEED_MEDIUM;
//	GPIOB_Handle.GPIO_CONFIG.GPIO_OP_TYPE = GPIO_OP_TYPE_PP;
//	GPIOB_Handle.GPIO_CONFIG.GPIO_PIN_NUMBER = GPIO_PIN_6;
//	gpio_pin_init(&GPIOB_Handle);
//
//	GPIOB_Handle.GPIO_CONFIG.GPIO_PIN_NUMBER = GPIO_PIN_7;
//	gpio_pin_init(&GPIOB_Handle);
//}
void USART3_GPIO_Init(){
	GPIOx_Handle_t GPIOC_Handle;
	GPIOC_Handle.pGPIOx = GPIOC;
	GPIOC_Handle.GPIO_CONFIG.GPIO_MODE = GPIO_MODE_ALT_FUNC;
	GPIOC_Handle.GPIO_CONFIG.GPIO_ALT_FUNC = GPIO_ALT_FUNC_7;
	GPIOC_Handle.GPIO_CONFIG.GPIO_SPEED = GPIO_SPEED_MEDIUM;
	GPIOC_Handle.GPIO_CONFIG.GPIO_OP_TYPE = GPIO_OP_TYPE_PP;
	GPIOC_Handle.GPIO_CONFIG.GPIO_PIN_NUMBER = GPIO_PIN_10;
	gpio_pin_init(&GPIOC_Handle);

	GPIOC_Handle.GPIO_CONFIG.GPIO_PIN_NUMBER = GPIO_PIN_11;
	gpio_pin_init(&GPIOC_Handle);
}

int main(){

	UART_Handle_t UART_Handle;

	UART_Handle.pUARTx = UART3;
	UART_Handle.UART_Config.UART_CONFIG_MODE = UART_CONFIG_MODE_TX_RX;
	UART_Handle.UART_Config.UART_CONFIG_NO_OF_STOP_BITS= UART_CONFIG_STOP_BITS_1;
	UART_Handle.UART_Config.UART_CONFIG_PARITY = UART_CONFIG_PARITY_NONE;
	UART_Handle.UART_Config.UART_CONFIG_WORD_LENGTH = UART_CONFIG_WORD_LENGTH_8;
	UART_Handle.UART_Config.UART_CONFIG_BAUD_RATE = UART_CONFIG_BAUD_RATE_9600;
	UART_Handle.UART_Config.UART_CONFIG_OVER_SAMPLING = UART_CONFIG_OVER_SAMPLING_16;

	//2. Call the UART init function
	uart_init(&UART_Handle);
	UART_Peri_Control(UART_Handle.pUARTx, ENABLE);

	uint8_t data[11] = {'N',98,99,100,101,102,103,104,105,0x0D,0xA};
	char str[] =
			"\x1B[31m  ***     ***  \r\n *****   ***** \r\n***************\r\n*** I LOVE YOU **\r\n***   NEHU   ***\r\n ************* \r\n   *********   \r\n     *****     \r\n       *       \r\n\x1B[0m"
;
	LCD_Inititalize();
	//3. GPIO init
	USART3_GPIO_Init();
	for(int j =0;j <1 ;j++){
//		UART_SendData_Blocking(&UART_Handle, data, 11);
		UART_Send_String(&UART_Handle, str, strlen(str));
		for(volatile int i = 0 ;i <30000;i++){

		}
	}
	char buf[32];
	memset(buf,0,sizeof(buf));
	int i = 0;
	while (1) {
		if (UART_Get_Status_Flag(UART_Handle.pUARTx, UART_STATUS_FLAG_RXNE))
		{
		    uint8_t ch = UART_Handle.pUARTx->USART_DR;
		    buf[i++] = (char)ch;
		    /* ENTER key handling (CR received) */
		    if (ch == '\r')
		    {

		        uint8_t newline[2] = {'\r', '\n'};
		        UART_SendData_Blocking(&UART_Handle, newline, 2);
		        LCD_Command_Send(&LCD_Def,0x01);
		        delayUS(2*1000);
		        LCD_Command_Send(&LCD_Def,0x02);
		        delayUS(2*1000);
		        display_lcd(&LCD_Def,buf, i);
//		        if(i>16){ @todo here we have to use interrupt recieve so that in the rest of the time lcd can shift
//		        	LCD_Shift_Display(&LCD_Def, LCD_SHIFT_LEFT, i-16);
//		        }
		        i = 0;
		        memset(buf,0,sizeof(buf));
		    }
		    /* BACKSPACE handling */
		    else if (ch == 0x08 || ch == 0x7F)
		    {
		        uint8_t bs_seq[3] = {0x08, ' ', 0x08};
		        UART_SendData_Blocking(&UART_Handle, bs_seq, 3);
		        i-=2;
		    }
		    /* Normal character echo */
		    else
		    {
		        UART_SendData_Blocking(&UART_Handle, &ch, 1);
		    }
		}

	}
	return 0;
}
