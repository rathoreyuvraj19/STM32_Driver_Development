

#include "stm32f407xx_rcc.h"
#include "stm32f407xx_uart.h"
#include "stm32f407xx_gpio.h"
#include "LCD.h"


UART_Handle_t UART_Handle;
LCD_Def_t LCD_Def;
//static uint8_t rx_done = 0;
static uint8_t rx_string_done = 0;

uint8_t RxByte;
static char RxString[500];
static uint32_t RX_idx = 0;

static uint8_t TX_done = 0;

typedef enum {
    TX_IDLE,
    TX_SEND_CRLF_1,
    TX_SEND_STRING,
    TX_SEND_CRLF_2
} tx_state_t;

static tx_state_t tx_state = TX_IDLE;

void LCD_Inititalize(){
	delayUS(2 * 10000); // After power on wait for 1.5 ms minimum
	LCD_Init(&LCD_Def);

	LCD_Command_Send(&LCD_Def,0x80);
	LCD_Command_Send(&LCD_Def,0x0F);
}

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

	LCD_Inititalize();


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

	//3. GPIO init
	USART3_GPIO_Init();

	//4. Enable the interrupt
	UART_IRQInterruptConfig(&UART_Handle, ENABLE);

	char str[] = "Device is Ready \r\n";
	//UART_SendData_Blocking(&UART_Handle, data, 11);
	UART_Send_String(&UART_Handle, "\x1B[2J\x1B[H", strlen("\x1B[2J\x1B[H"));
	UART_Send_String(&UART_Handle, "\x1B[2J\x1B[H", strlen("\x1B[2J\x1B[H"));
	UART_Send_String(&UART_Handle, str, strlen(str));

	//ROUGH
//	uint8_t TXBuff[5] = {65,66,67,68,69};
	char TXBuff[] ="Yuvrajjjjj\r\n";
	UART_SendData_IT(&UART_Handle, (uint8_t*)TXBuff, strlen(TXBuff));

	//5. Start RX
	//while(UART_RecieveData_IT(&UART_Handle, rx_buff, 5));
	while(UART_ReceiveData_IT(&UART_Handle, &RxByte, 1));
	while (1) {
		if(rx_string_done == 1){
			rx_string_done = 0;
			LCD_Display_String(&LCD_Def, RxString, strlen(RxString));
		}
		if(TX_done == 1){
			TX_done = 0;
		}
	}
	return 0;
}

void USART3_IRQHandler(){
	UART_IRQHandling(&UART_Handle);
}

void UART_ApplicationEventCallback(UART_Handle_t *pUARTHandle, uint8_t Event) {
	/* ---------- RX COMPLETE ---------- */
	if (Event == UART_EVENT_RX_CMPLT) {
		if (RxByte == '\r') {
			/* Terminate string */
			RxString[RX_idx] = '\0';
			RX_idx = 0;

			tx_state = TX_SEND_CRLF_1;

			/* Start TX ONCE */
			UART_SendData_IT(pUARTHandle, (uint8_t*) "\r\n", 2);
		} else if (RxByte == '\b') {
			if (RX_idx > 0) {
				RX_idx--;
				UART_Echo(pUARTHandle, RxByte);
			}
		} else {
			if (RX_idx < sizeof(RxString) - 1) {
				RxString[RX_idx++] = (char) RxByte;
				UART_Echo(pUARTHandle, RxByte);
			}
		}

		/* Re-arm RX ONCE */
		UART_ReceiveData_IT(pUARTHandle, &RxByte, 1);
	}

	/* ---------- TX COMPLETE ---------- */
	else if (Event == UART_EVENT_TX_CMPLT) {
		switch (tx_state) {
		case TX_SEND_CRLF_1:
			tx_state = TX_SEND_STRING;
			UART_SendData_IT(pUARTHandle, (uint8_t*) RxString,
					strlen(RxString));
			break;

		case TX_SEND_STRING:
			tx_state = TX_SEND_CRLF_2;
			UART_SendData_IT(pUARTHandle, (uint8_t*) "\r\n", 2);
			break;

		case TX_SEND_CRLF_2:
			tx_state = TX_IDLE;
			rx_string_done = 1;
			break;

		default:
			break;
		}
	}
}

