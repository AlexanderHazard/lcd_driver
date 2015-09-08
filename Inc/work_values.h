/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WORK_VALUES_H
#define __WORK_VALUES_H

#include "stm32f1xx_hal.h"
#define ADDR_FLASH_PAGE_100   ((uint32_t)0x08019000) /* Base @ of Page 100, 1 Kbytes */
#define ADDR_FLASH_PAGE_101   ((uint32_t)0x08019400) /* Base @ of Page 101, 1 Kbytes */
#define ADDR_FLASH_PAGE_124   ((uint32_t)0x0801F000) /* Base @ of Page 124, 1 Kbytes */
#define ADDR_FLASH_PAGE_125   ((uint32_t)0x0801F400) /* Base @ of Page 125, 1 Kbytes */
#define ADDR_FLASH_PAGE_126   ((uint32_t)0x0801F800) /* Base @ of Page 126, 1 Kbytes */
#define ADDR_FLASH_PAGE_127   ((uint32_t)0x0801FC00) /* Base @ of Page 127, 1 Kbytes */

typedef struct{
   volatile int16_t minVal;
	 volatile int16_t curVal;
   volatile int16_t maxVal;
} workvalue;

 volatile extern workvalue fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;
 volatile extern float clean_time,clean_time_max, clean_time_min;

  void readFromFlashMemory();
  void writeToFlashMemory();
#endif