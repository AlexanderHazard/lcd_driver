#include "out_dev.h"

void gpioDevInit();

/*
*init IO for using out devices
*/
void initOutDevices()
{

}

/*
*
*/
void changeDevState(deviceInfo cDeviceaver)
{
  
}

/*init gpios to output*/
void gpioDevInit()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	
	
		//speed and mode are common for all pins
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
}