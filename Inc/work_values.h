/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WORK_VALUES_H
#define __WORK_VALUES_H

#include "stm32f1xx_hal.h"

 volatile static uint16_t fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;
 volatile static float clean_time;

  void readFromFlashMemory();
#endif