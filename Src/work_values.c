#include "work_values.h"

volatile float clean_time,clean_time_max, clean_time_min;
volatile workvalue fire_mode, temp_boil, time_ign, tan_work, fuel_ign, screw_fill, clean_per, flame_bright;

void readFromFlashMemory()
{
  fire_mode.curVal = 0;
	temp_boil.curVal = 0;
	time_ign.curVal = 0;
	tan_work.curVal = 0;
	fuel_ign.curVal = 0;
	screw_fill.curVal = 0;
	clean_per.curVal = 0;
	flame_bright.curVal = 0;
	
	clean_time = 0.0f;
	
	fire_mode.maxVal = 20;
	temp_boil.maxVal = 80;
	time_ign.maxVal = 300;
	tan_work.maxVal = 30;
	fuel_ign.maxVal = 300;
	screw_fill.maxVal = 20;
	clean_per.maxVal = 15;
	flame_bright.maxVal= 100;
	
	clean_time_max = 10.0f;
	clean_time_min = 0.01f;
}