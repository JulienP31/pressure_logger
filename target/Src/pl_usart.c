#include "pl_usart.h"



// -------------------- Constants --------------------
#define USART3_PORT   GPIOC
#define USART3_TX_PIN GPIO_PIN_10
#define USART3_RX_PIN GPIO_PIN_11

#define USART_TIMEOUT 80000 //< 10 ms @ 8 MHz


// -------------------- Global variables --------------------
static UART_HandleTypeDef grUART_Handle; //< [NOTA : USART used as UART]

static uint8_t gbDataAvail;

static uint8_t guiData; //< [NOTA : only 1 byte, no buffer used]


// -------------------- HAL Functions --------------------
void pl_usart_init(void)
{
	GPIO_InitTypeDef rGPIO_Tx_Init = {0};
	GPIO_InitTypeDef rGPIO_Rx_Init = {0};
	
	gbDataAvail = 0;
	guiData = 0;
	
	// Configure USART3
	grUART_Handle.Instance = USART3;
	
	grUART_Handle.Init.BaudRate = 115200;
	grUART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
	grUART_Handle.Init.StopBits = UART_STOPBITS_1;
	grUART_Handle.Init.Parity = UART_PARITY_NONE;
	grUART_Handle.Init.Mode = UART_MODE_TX_RX;
	grUART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	
	// Enable USART3 clock
	__USART3_CLK_ENABLE();
	
	// Enable USART3 peripheral
	__HAL_UART_ENABLE(&grUART_Handle);
	
	// Enable AFIO clock
	__AFIO_CLK_ENABLE();
	
	// Remap USART3 to GPIOC pins (TX = C10 ; RX = C11)
	__HAL_AFIO_REMAP_USART3_PARTIAL();
	
	// Enable GPIOC clock
	__GPIOC_CLK_ENABLE();
	
	// Configure USART3 pins as alternate function
	rGPIO_Tx_Init.Pin = USART3_TX_PIN;
	rGPIO_Tx_Init.Mode = GPIO_MODE_AF_PP;
	rGPIO_Tx_Init.Pull = GPIO_NOPULL;
	rGPIO_Tx_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(USART3_PORT, &rGPIO_Tx_Init);
	
	rGPIO_Rx_Init.Pin = USART3_RX_PIN;
	rGPIO_Rx_Init.Mode = GPIO_MODE_AF_INPUT;
	rGPIO_Rx_Init.Pull = GPIO_PULLUP;
	rGPIO_Rx_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(USART3_PORT, &rGPIO_Rx_Init);
	
	// Enable USART3 Rx IRQ
	__HAL_UART_ENABLE_IT(&grUART_Handle, UART_IT_RXNE);
	
	// Enable USART3 IRQ in NVIC
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	
	// Initialize USART3
	HAL_UART_Init(&grUART_Handle);
}


void pl_usart_send(uint8_t uiByte)
{
	uint8_t uiData = uiByte;
	
	HAL_UART_Transmit(&grUART_Handle, &uiData, 1, USART_TIMEOUT);
}


void pl_usart_recv(uint8_t *puiByte)
{
	// Disable USART3 Rx IRQ
	__HAL_UART_DISABLE_IT(&grUART_Handle, UART_IT_RXNE);
	
	// Get byte
	*puiByte = guiData;
	
	// Reset gbDataAvail flag [NOTA : no lock needed here since this flag can only be set in IRQ context]
	gbDataAvail = 0;
	
	// Re-enable USART3 Rx IRQ
	__HAL_UART_ENABLE_IT(&grUART_Handle, UART_IT_RXNE);
}


uint8_t pl_usart_data_avail(void)
{
	return gbDataAvail;
}


// -------------------- Internal Functions --------------------
void USART3_IRQHandler(void)
{
	// Set gbDataAvail flag
	gbDataAvail = 1;
	
	// Acknowledge IRQ by reading DR
	guiData = USART3->DR;
}

