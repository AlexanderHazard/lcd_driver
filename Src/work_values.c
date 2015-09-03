#include "work_values.h"

void readFromFlashMemory()
{
  fire_mode = 0;
	temp_boil = 0;
	time_ign = 0;
	tan_work = 0;
	fuel_ign = 0;
	screw_fill = 0;
	clean_per = 0;
	flame_bright = 0;
	
	clean_time = 0.0f;
	
	fire_mode_max = 20;
	temp_boil_max = 80;
	time_ign_max = 300;
	tan_work_max = 30;
	fuel_ign_max = 300;
	screw_fill_max = 20;
	clean_per_max = 15;
	flame_bright_max= 100;
	
	clean_time_max = 10.0f;
}