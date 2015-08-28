#include "keyboard.h"
#include "Menu.h"
/*functions prototypes*/
  static void extiConfiguration();//ports configuration


void initKeyboard()
{
   extiConfiguration();
}

/*Configurations*/
void extiConfiguration()
{
   GPIO_InitTypeDef GPIO_InitStructure;
	
	//Enable GPIO clock
	  __GPIOA_CLK_ENABLE();

	
	//configure PA pins
	//PA5 - left
	//PA6 - right
	//PA7 - down
	//PA11 - up
	//PA12 - center
	
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*Enable and set EXTI lines interrupts to the lowest priority*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 1);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 1);
	
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/*EXTI interraptions callback*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_5)
	  {
			moveLfMenu();
			HAL_Delay(50);
		}
		
	else if(GPIO_Pin == GPIO_PIN_6)
	  {
			moveRgMenu();
			HAL_Delay(50);
		}

  else if(GPIO_Pin == GPIO_PIN_7)
	  {
			moveDnMenu();
			HAL_Delay(50);
		}		
		
  else if(GPIO_Pin == GPIO_PIN_11)
	  {
		  moveRgMenu();
			HAL_Delay(50);
	  }
		
  else if(GPIO_Pin == GPIO_PIN_12)
	  {
			moveUpMenu();
			HAL_Delay(50);
	  }
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}

