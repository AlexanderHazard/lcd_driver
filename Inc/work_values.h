/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WORK_VALUES_H
#define __WORK_VALUES_H

#include "stm32f1xx_hal.h"

typedef struct{
   volatile int16_t minVal;
	 volatile int16_t curVal;
   volatile int16_t maxVal;
} workvalue;

  static workvalue fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;
 volatile static float clean_time,clean_time_max, clean_time_min;

  void readFromFlashMemory();
#endif