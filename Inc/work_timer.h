#ifndef __WORK_TIMER_H
#define __WORK_TIMER_H
#include "stm32f1xx_hal.h"

typedef enum {ENABLE_TIM, DISABLE_TIM} timerstate;

typedef struct{timerstate CurrentState; uint16_t secondBuff;} timerInfo;

extern timerInfo ScrewTakerTimer, ScrewIgnTimer, FireBarTimer, TanTimer, PumpBoilTimer, PumpCatlTimer;

void secTimCallback();
void initTimers();/*init timer*/
void pauseTimerDevice(timerInfo *cTimer);
void restartTimerDevice(timerInfo *cTimer);
void startTimerDevice(timerInfo *cTimer, uint16_t sSeconds);/*init structure for current out device*/

#endif