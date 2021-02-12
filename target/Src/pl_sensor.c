#include "pl_sensor.h"



// -------------------- Constants --------------------
#define SENSOR_I2C_ADDRESS (0x5d << 1)

#define SENSOR_PORT     GPIOB
#define SENSOR_SCL_PIN  GPIO_PIN_8
#define SENSOR_SDA_PIN  GPIO_PIN_9
#define SENSOR_INT1_PIN GPIO_PIN_4

#define I2C_TIMEOUT 1000 //< 10 ms @ 100 kHz

/* Registers */
#define REG_WHO_AM_I     0x0f

#define REG_CTRL_REG1    0x20 //< Power Down + Output Data Rate
#define REG_CTRL_REG2    0x21 //< FIFO mode + WaTerMark
#define REG_CTRL_REG3    0x22 //< INT1 active Low
#define REG_CTRL_REG4    0x23 //< WaTerMark signal on INT1 pin

#define REG_INT_SOURCE   0x25 //< INT1 acknowledgment

#define REG_PRESS_OUT_XL 0x28 //< Pressure Low
#define REG_PRESS_OUT_L  0x29 //< Pressure Medium
#define REG_PRESS_OUT_H  0x2a //< Pressure High

#define REG_FIFO_CTRL    0x2e //< Stream mode


// -------------------- Global variables --------------------
static I2C_HandleTypeDef grI2C_Handle;

static uint8_t guiNbSamp;

static uint8_t gbDataAvail;


// -------------------- HAL Functions --------------------
void pl_sensor_init(void)
{
	GPIO_InitTypeDef rGPIO_Scl_Sda_Init = {0};
	GPIO_InitTypeDef rGPIO_Int1_Init = {0};
	uint8_t uiSensorId = 0;
	
	// Enable I2C1 clock
	__I2C1_CLK_ENABLE();
	
	// Enable AFIO clock
	__AFIO_CLK_ENABLE();
	
	// Remap I2C1 to GPIOB pins (SCL = B8 ; SDA = B9)
	__HAL_AFIO_REMAP_I2C1_ENABLE();
	
	// Enable GPIOB clock
	__GPIOB_CLK_ENABLE();
	
	// Configure I2C1 pins as alternate function
	rGPIO_Scl_Sda_Init.Pin = SENSOR_SCL_PIN;
	rGPIO_Scl_Sda_Init.Mode = GPIO_MODE_AF_OD;
	rGPIO_Scl_Sda_Init.Pull = GPIO_PULLUP;
	rGPIO_Scl_Sda_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SENSOR_PORT, &rGPIO_Scl_Sda_Init);
	
	rGPIO_Scl_Sda_Init.Pin = SENSOR_SDA_PIN;
	HAL_GPIO_Init(SENSOR_PORT, &rGPIO_Scl_Sda_Init);
	
	// Configure INT1 GPIO
	rGPIO_Int1_Init.Pin = SENSOR_INT1_PIN;
	rGPIO_Int1_Init.Mode = GPIO_MODE_IT_FALLING;
	rGPIO_Int1_Init.Pull = GPIO_PULLUP;
	rGPIO_Int1_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SENSOR_PORT, &rGPIO_Int1_Init);
	
	// Enable INT1 GPIO IRQ in NVIC
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	
	// Configure I2C1
	grI2C_Handle.Instance = I2C1;
	
	grI2C_Handle.Init.ClockSpeed = 100000;
	grI2C_Handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	grI2C_Handle.Init.OwnAddress1 = 0x01;
	grI2C_Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	grI2C_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	grI2C_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	grI2C_Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	
	// Enable I2C1 peripheral
	__HAL_I2C_ENABLE(&grI2C_Handle);
	
	// Initialize I2C1
	HAL_I2C_Init(&grI2C_Handle);
	
	// Get sensor ID
	HAL_I2C_Mem_Read(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_WHO_AM_I, 1, &uiSensorId, 1, I2C_TIMEOUT); //< [NOTA : for debug -> Id = 0xbd]
}


void pl_sensor_configure(pl_sensor_freq_t eFreq, uint8_t uiNbSamp)
{
	uint8_t uiByte = 0;
	
	guiNbSamp = uiNbSamp;
	
	uiByte = ( (eFreq & 0x07) << 4 );
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG1, 1, &uiByte, 1, I2C_TIMEOUT);
	
	uiByte = (1 << 6) | (1 << 5);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG2, 1, &uiByte, 1, I2C_TIMEOUT);
	
	uiByte = (1 << 7);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG3, 1, &uiByte, 1, I2C_TIMEOUT);
	
	uiByte = (1 << 2);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG4, 1, &uiByte, 1, I2C_TIMEOUT);
	
	uiByte = (1 << 6) | ((uiNbSamp-1) & 0x1f);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_FIFO_CTRL, 1, &uiByte, 1, I2C_TIMEOUT);
}


void pl_sensor_start(void)
{
	uint8_t uiByte = 0;
	
	gbDataAvail = 0;
	
	HAL_I2C_Mem_Read(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG1, 1, &uiByte, 1, I2C_TIMEOUT);
	uiByte |= (1 << 7);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG1, 1, &uiByte, 1, I2C_TIMEOUT);	
}


uint8_t pl_sensor_get_data(uint8_t *tuiBuffer)
{
	uint8_t uiByte = 0;
	int i = 0;
	
	// Get data
	for (i = 0 ; i < guiNbSamp ; i++)
	{
		HAL_I2C_Mem_Read(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_PRESS_OUT_XL, 1, tuiBuffer+3*i, 3, I2C_TIMEOUT);
	}
	
	// Reset gbDataAvail flag [NOTA : no lock needed here since this flag can only be set in IRQ context ...
					// ... and IRQ can't be triggered while REG_INT_SOURCE is not read, which is not done yet]
	gbDataAvail = 0;
	
	// Acknlowledge sensor IRQ by reading INT_SOURCE register [NOTA : now REG_INT_SOURCE is read !]
	HAL_I2C_Mem_Read(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_INT_SOURCE, 1, &uiByte, 1, I2C_TIMEOUT);
	
	return 0;
}


uint8_t pl_sensor_data_avail(void)
{
	return gbDataAvail;
}


void pl_sensor_stop(void)
{
	uint8_t uiByte = 0;
	
	HAL_I2C_Mem_Read(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG1, 1, &uiByte, 1, I2C_TIMEOUT);
	uiByte &= ~(1 << 7);
	HAL_I2C_Mem_Write(&grI2C_Handle, SENSOR_I2C_ADDRESS, REG_CTRL_REG1, 1, &uiByte, 1, I2C_TIMEOUT);	
}


// -------------------- Internal Functions --------------------
void EXTI4_IRQHandler(void)
{
	// Set gbDataAvail flag
	gbDataAvail = 1;
	
	// Acknowledge GPIO IRQ
	HAL_GPIO_EXTI_IRQHandler(SENSOR_INT1_PIN);
}

