#include "pl_usart.h"



// -------------------- Constants --------------------
#define USART_PORT   GPIOA
#define USART_TX_PIN GPIO_PIN_2
#define USART_RX_PIN GPIO_PIN_3

#define USART_TIMEOUT 80000 //< 10 ms @ 8 MHz


// -------------------- Global variables --------------------
static UART_HandleTypeDef grUART_Handle; //< [NOTA : USART used as UART]

static uint8_t bByteReceived; //< [NOTA : only 1 byte, no buffer used]



// -------------------- HAL Functions --------------------
void pl_usart_init(void)
{
	GPIO_InitTypeDef rGPIO_Tx_Init = {0};
	GPIO_InitTypeDef rGPIO_Rx_Init = {0};
	
	bByteReceived = 0;

	// Configure USART2
	grUART_Handle.Instance = USART2;
	
	grUART_Handle.Init.BaudRate = 115200;
	grUART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
	grUART_Handle.Init.StopBits = UART_STOPBITS_1;
	grUART_Handle.Init.Parity = UART_PARITY_NONE;
	grUART_Handle.Init.Mode = UART_MODE_TX_RX;
	grUART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		
	// Enable USART2 clock
	__USART2_CLK_ENABLE();
	
	// Enable USART2 peripheral
	__HAL_UART_ENABLE(&grUART_Handle);
	
	// Enable GPIOA clock
	__GPIOA_CLK_ENABLE();
	
	// Configure USART2 pins as alternate function
	rGPIO_Tx_Init.Pin = USART_TX_PIN;
	rGPIO_Tx_Init.Mode = GPIO_MODE_AF_PP;
	rGPIO_Tx_Init.Pull = GPIO_NOPULL;
	rGPIO_Tx_Init.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(USART_PORT, &rGPIO_Tx_Init);
	
	rGPIO_Rx_Init.Pin = USART_RX_PIN;
	rGPIO_Rx_Init.Mode = GPIO_MODE_AF_OD;
	rGPIO_Rx_Init.Pull = GPIO_NOPULL;
	rGPIO_Rx_Init.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(USART_PORT, &rGPIO_Rx_Init);		
	
	// Enable USART2 Rx IRQ
	__HAL_UART_ENABLE_IT(&grUART_Handle, UART_IT_RXNE);
	
	// Enable USART2 IRQ in NVIC
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	
	// Initialize USART2
	HAL_UART_Init(&grUART_Handle);
}


void pl_usart_send(uint8_t uiByte)
{
	HAL_UART_Transmit(&grUART_Handle, &uiByte, 1, USART_TIMEOUT);
}


void pl_usart_recv(uint8_t *puiByte)
{
	// Disable USART_IT_RXNE
	__HAL_UART_DISABLE_IT(&grUART_Handle, UART_IT_RXNE);
	
	// Receive byte [NOTA : critical section starting here...]
	if ( HAL_UART_Receive(&grUART_Handle, puiByte, 1, USART_TIMEOUT) == HAL_OK )
	{
		// Reset bByteReceived flag [NOTA : no lock needed here since this flag can only be set in IRQ context]
		bByteReceived = 0;
	}
	
	// Re-enable USART_IT_RXNE
	__HAL_UART_ENABLE_IT(&grUART_Handle, UART_IT_RXNE);
}


uint8_t pl_usart_data_avail(void)
{
	return bByteReceived;
}


void pl_usart_deinit(void)
{
	HAL_UART_DeInit(&grUART_Handle);
	
	HAL_NVIC_DisableIRQ(USART2_IRQn);
	
	__HAL_UART_DISABLE_IT(&grUART_Handle, UART_IT_RXNE);
	
	__HAL_UART_DISABLE(&grUART_Handle);
	
	HAL_GPIO_DeInit(USART_PORT, USART_RX_PIN);
	HAL_GPIO_DeInit(USART_PORT, USART_TX_PIN);
	
	__USART2_CLK_DISABLE();
}


// -------------------- Internal Functions --------------------
void USART2_IRQHandler(void)
{
	// Set bByteReceived flag
	bByteReceived = 1;
	
	// Acknowledge IRQ
	HAL_UART_IRQHandler(&grUART_Handle);
}

