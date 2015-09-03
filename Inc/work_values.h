/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WORK_VALUES_H
#define __WORK_VALUES_H

#include "stm32f1xx_hal.h"

 volatile static uint16_t fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;
 volatile static uint16_t fire_mode_max, temp_boil_max, time_ign_max, tan_work_max, fuel_ign_max, screw_fill_max, clean_per_max, flame_bright_max;
 volatile static float clean_time,clean_time_max;

  void readFromFlashMemory();
#endif