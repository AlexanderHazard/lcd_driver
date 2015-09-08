#include "work_values.h"

volatile float clean_time,clean_time_max, clean_time_min;
volatile workvalue fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_100   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_PAGE_101 + FLASH_PAGE_SIZE   /* End @ of user Flash area */

/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;

uint32_t Address = 0, PAGEError = 0;

void readFromFlashMemory()
{
	Address = FLASH_USER_START_ADDR;
	
	fire_mode.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	fire_mode.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	fire_mode.maxVal = *(__IO uint32_t *)Address;
	Address +=4;

	temp_boil.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	temp_boil.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	temp_boil.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
	time_ign.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	time_ign.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	time_ign.maxVal = *(__IO uint32_t *)Address;;
	Address +=4;
	
	tan_work.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	tan_work.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	tan_work.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
	fuel_ign.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	fuel_ign.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	fuel_ign.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
	screw_fill.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	screw_fill.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	screw_fill.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
	clean_per.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	clean_per.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	clean_per.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
	flame_bright.minVal = *(__IO uint32_t *)Address;
	Address +=4;
	flame_bright.curVal = *(__IO uint32_t *)Address;
	Address +=4;
	flame_bright.maxVal = *(__IO uint32_t *)Address;
	Address +=4;
	
		
/*
	temp_boil.maxVal = 80;
	time_ign.maxVal = 300;
	tan_work.maxVal = 30;
	fuel_ign.maxVal = 300;
	screw_fill.maxVal = 20;
	clean_per.maxVal = 15;
	flame_bright.maxVal= 100;
*/	

	clean_time_min = (*(__IO uint32_t *)Address)/100.0f;
	Address += 4;
	
	clean_time = (*(__IO uint32_t *)Address)/100.0f;
	Address += 4;
	
	clean_time_max = (*(__IO uint32_t *)Address)/100.0f;
	
	/*	clean_time = 0.0f;
	clean_time_max = 10.0f;
	clean_time_min = 0.01f;
	*/
	//writeToFlashMemory();
}

void writeToFlashMemory()
{
	HAL_FLASH_Unlock();
  
	/* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
  EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;
	
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) return;//return if  memory hasn't clear
	Address = FLASH_USER_START_ADDR;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fire_mode.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fire_mode.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fire_mode.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)temp_boil.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)temp_boil.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)temp_boil.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)time_ign.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)time_ign.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)time_ign.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)tan_work.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)tan_work.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)tan_work.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fuel_ign.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fuel_ign.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)fuel_ign.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)screw_fill.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)screw_fill.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)screw_fill.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)clean_per.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)clean_per.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)clean_per.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)flame_bright.minVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)flame_bright.curVal);
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)flame_bright.maxVal);
	Address += 4;
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)(clean_time_min*100));
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)(clean_time*100));
	Address += 4;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, (uint32_t)(clean_time_max*100));
	Address += 4;

	
	HAL_FLASH_Lock();
}