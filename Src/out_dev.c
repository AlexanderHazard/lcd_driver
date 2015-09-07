#include "out_dev.h"

volatile deviceInfo screwTake, screwIgn, outTan, outFireBar, outPumpBoil, outPumpCatl;

void gpioDevInit();

/*
*init IO for using out devices
*/
void initOutDevices()
{
	/*init device structures*/
	 screwTake.cPort = GPIOA;
   screwTake.IO_port = ScrTkOut;
	 screwTake.CurrentState = DISABLE_STATE;
	
	 screwIgn.cPort = GPIOA;
	 screwIgn.IO_port = ScrIgnOut;
	 screwIgn.CurrentState = DISABLE_STATE;
	
	 outTan.cPort = GPIOA;
	 outTan.IO_port = TanOut;
	 outTan.CurrentState = DISABLE_STATE;
	
	 outFireBar.cPort = GPIOB;
	 outFireBar.IO_port = FireBarOut;
	 outFireBar.CurrentState = DISABLE_STATE;
	
	 outPumpBoil.cPort = GPIOB;
	 outPumpBoil.IO_port = PumpBoilOut;
	 outPumpBoil.CurrentState = DISABLE_STATE;
	
	 outPumpCatl.cPort = GPIOB;
	 outPumpCatl.IO_port = PumpCatleOut;
	 outPumpCatl.CurrentState = DISABLE_STATE;
	
	/*init device ports*/
	 gpioDevInit();
	
}

/*
*
*/
void changeDevState(deviceInfo *cDevice)
 {
  if(cDevice->CurrentState == DISABLE_STATE) 
	  {
			cDevice->CurrentState = ENABLE_STATE;
	    HAL_GPIO_WritePin(cDevice->cPort, cDevice->IO_port, GPIO_PIN_SET);
 		}
		
	else if(cDevice->CurrentState == ENABLE_STATE)
	  {
			cDevice->CurrentState = DISABLE_STATE;
		  HAL_GPIO_WritePin(cDevice->cPort, cDevice->IO_port, GPIO_PIN_RESET);
		}		
 }

void enableDev(deviceInfo *cDevice)
 {
	cDevice->CurrentState = ENABLE_STATE;
	HAL_GPIO_WritePin(cDevice->cPort, cDevice->IO_port, GPIO_PIN_SET);
 }

void disableDev(deviceInfo *cDevice)
 {
	cDevice->CurrentState = DISABLE_STATE;
	HAL_GPIO_WritePin(cDevice->cPort, cDevice->IO_port, GPIO_PIN_RESET);
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
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Pin = ScrTkOut | ScrIgnOut | TanOut;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
			//speed and mode are common for all pins
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Pin = FireBarOut | PumpBoilOut | PumpCatleOut;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOA, ScrTkOut | ScrIgnOut | TanOut, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, FireBarOut | PumpBoilOut | PumpCatleOut, GPIO_PIN_RESET);
}