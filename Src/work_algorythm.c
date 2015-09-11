#include "work_algorythm.h"
#include "work_timer.h"
#include "out_dev.h"
#include "hd4480.h"

void alCleaning();
void alGasTaking();

void alCleaning()
 {
	 LCD_Clear();
	 LCD_Goto(1, 0);
   LCD_Puts("Cleaning...");
	 
	 //enable screw ignition
	  enableDev(&screwIgn);
	  startTimerDevice(&ScrewIgnTimer, 15);
	  while(ScrewIgnTimer.CurrentState == ENABLE_TIM);//wait while Screw ign timer working
	 
	  enableDev(&outFireBar);
	  startTimerDevice(&FireBarTimer,15);
	  while(FireBarTimer.CurrentState == ENABLE_TIM);//wait while FireBar timer working
	 
	// workState = END_WORK;
	 
	 //here will be fan
	 /*enableDev(&outFireBar);
	 startTimerDevice(&FireBarTimer,15);
	 while(FireBarTimer.CurrentState == ENABLE_TIM);//wait while FireBar timer working	 
	 */
	 
 }
 
 void alGasTaking()
 {
	 LCD_Clear();
	 LCD_Goto(1, 0);
   LCD_Puts("Gas Taking...");
	 
	 //enable screw ignition
	  enableDev(&screwTake);
	  startTimerDevice(&ScrewTakerTimer, 30);
	  while(ScrewTakerTimer.CurrentState == ENABLE_TIM);//wait while Screw ign timer working
	 
	  enableDev(&screwIgn);
	  startTimerDevice(&ScrewIgnTimer,30);
	  while(ScrewIgnTimer.CurrentState == ENABLE_TIM);//wait while FireBar timer working
	 
	// workState = END_WORK;
	 
	 //here will be fan
	 /*enableDev(&outFireBar);
	 startTimerDevice(&FireBarTimer,15);
	 while(FireBarTimer.CurrentState == ENABLE_TIM);//wait while FireBar timer working	 
	 */
	 
 }
 
 void alWorkSystem()
  {
		alCleaning();
		alGasTaking();
    workState = END_WORK;
  }