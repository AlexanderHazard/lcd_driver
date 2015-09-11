#include "work_timer.h"
#include "out_dev.h"

timerInfo ScrewTakerTimer, ScrewIgnTimer, FireBarTimer, TanTimer, PumpBoilTimer, PumpCatlTimer;
TIM_HandleTypeDef htim3;

void resetTimersStructs();

void initTimers()
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 65535;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);
	
	HAL_TIM_Base_Start_IT(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

	
	HAL_TIM_Base_Init(&htim3);

  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  HAL_TIM_Base_Start_IT(&htim3);
	
	resetTimersStructs();
}

//reset settings to default
void resetTimersStructs()
{
  ScrewTakerTimer.CurrentState = DISABLE_TIM;
	ScrewTakerTimer.secondBuff = 0;
	
	
	ScrewIgnTimer.CurrentState = DISABLE_TIM;
	ScrewIgnTimer.secondBuff = 0;
	
	TanTimer.CurrentState = DISABLE_TIM;
	TanTimer.secondBuff = 0;
	
	FireBarTimer.CurrentState = DISABLE_TIM;
	FireBarTimer.secondBuff = 0;
	
	
	PumpBoilTimer.CurrentState = DISABLE_TIM;
  PumpBoilTimer.secondBuff = 0;

	PumpCatlTimer.CurrentState = DISABLE_TIM;
	PumpCatlTimer.secondBuff = 0;
	
}


//work timers
/*
Enable timer for current device
*/
void startTimerDevice(timerInfo *cTimer, uint16_t sSeconds)
 {
   cTimer->secondBuff = sSeconds;
	 cTimer->CurrentState = ENABLE_TIM;  
 }
 
/*
 Pause device timer
*/ 
void pauseTimerDevice(timerInfo *cTimer)
 {
   cTimer->CurrentState = DISABLE_TIM;
 }

/*
 Restart device after pause.
 It means that we dont refresh devices timer
*/
void restartTimerDevice(timerInfo *cTimer)
 {
   cTimer->CurrentState = ENABLE_TIM;
 }
 
/*
check all counts, and disable device when timer full to zero
*/
void secTimCallback()
{
  if(ScrewTakerTimer.CurrentState == ENABLE_TIM)
	 {
	   if(--ScrewTakerTimer.secondBuff <= 0 ) 
		  {   
		   ScrewTakerTimer.CurrentState = DISABLE_TIM;
			 disableDev(&screwTake);
		  }
	 }
		
  if(ScrewIgnTimer.CurrentState == ENABLE_TIM)
	  {
	    if(--ScrewIgnTimer.secondBuff <= 0 ) 
				{
				 ScrewIgnTimer.CurrentState = DISABLE_TIM;
				 disableDev(&screwIgn);
			  }
	  }
		
  if(TanTimer.CurrentState == ENABLE_TIM)
	  {
	    if(--TanTimer.secondBuff <= 0 ) 
				{
					TanTimer.CurrentState = DISABLE_TIM;
					disableDev(&outTan);
				}
	  }
		
  if(FireBarTimer.CurrentState == ENABLE_TIM)
	  {
	    if(--FireBarTimer.secondBuff <= 0 ) 
			 {
				FireBarTimer.CurrentState = DISABLE_TIM;
				disableDev(&outFireBar);
			 }
	  }		
		
  if(PumpBoilTimer.CurrentState == ENABLE_TIM)
	  {
	    if(--PumpBoilTimer.secondBuff <= 0 ) 
			 {
				 PumpBoilTimer.CurrentState = DISABLE_TIM;
				 disableDev(&outPumpBoil);
			 }
	  }			

  if(PumpCatlTimer.CurrentState == ENABLE_TIM)
	  {
	    if(--PumpCatlTimer.secondBuff <= 0 ) 
			  {
					PumpCatlTimer.CurrentState = DISABLE_TIM;
					disableDev(&outPumpCatl);
				}
	  }				
}