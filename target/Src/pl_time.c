#include "pl_time.h"



// -------------------- Constants --------------------
#define INC_MS 10 //< i.e. time precision


// -------------------- Global variables --------------------
static uint32_t guiCurrentTime;

static TIM_HandleTypeDef grTIM_Handle = {0};


// -------------------- HAL Functions --------------------
void pl_time_init(void)
{
	guiCurrentTime = 0;
	
	// Enable TIM1 clock
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	// Enable TIM1 peripheral
	__HAL_TIM_ENABLE(&grTIM_Handle);
	
	// Enable TIM1 Update IRQ
	__HAL_TIM_ENABLE_IT(&grTIM_Handle, TIM_IT_UPDATE);
	
	// Enable TIM1 Update IRQ in NVIC
	HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
	
	// Configure TIM1
	grTIM_Handle.Instance = TIM1;
	
	grTIM_Handle.Init.Prescaler = 8000; //< 8 MHz -> 1 kHz (i.e. 1 ms)
	grTIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	grTIM_Handle.Init.Period = INC_MS;
	grTIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	grTIM_Handle.Init.RepetitionCounter = 0;
	grTIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
	HAL_TIM_Base_Init(&grTIM_Handle);
	
	// Start TIM1
	HAL_TIM_Base_Start_IT(&grTIM_Handle);
}


uint32_t pl_time_getMs(void)
{
	return guiCurrentTime;
}


void pl_time_waitMs(uint32_t uiDuration)
{
	uint32_t uiTime0 = guiCurrentTime;
	
	while ( guiCurrentTime - uiTime0 < uiDuration );
}


void pl_time_deinit(void)
{
	HAL_TIM_Base_Stop_IT(&grTIM_Handle);
	
	HAL_TIM_Base_DeInit(&grTIM_Handle);
	
	HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
	
	__HAL_TIM_DISABLE_IT(&grTIM_Handle, TIM_IT_UPDATE);
	
	__HAL_TIM_DISABLE(&grTIM_Handle);
	
	__HAL_RCC_TIM1_CLK_DISABLE();
	
	guiCurrentTime = 0;
}


// -------------------- Internal Functions --------------------

void TIM1_UP_IRQHandler(void)
{
	guiCurrentTime += INC_MS;
	
	// Acknowledge IRQ
	HAL_TIM_IRQHandler(&grTIM_Handle);
}

