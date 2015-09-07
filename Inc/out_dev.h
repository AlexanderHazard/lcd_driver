#ifndef __OUT_DEV_H
#define __OUT_DEV_H

#include "stm32f1xx_hal.h"

#define ScrTkOut GPIO_PIN_2
#define ScrIgnOut GPIO_PIN_3
#define TanOut GPIO_PIN_10
#define FireBarOut GPIO_PIN_3
#define PumpBoilOut GPIO_PIN_4
#define PumpCatleOut GPIO_PIN_5

typedef enum {ENABLE_STATE, DISABLE_STATE} devstate;
typedef struct{ GPIO_TypeDef* cPort; devstate CurrentState; uint16_t IO_port;} deviceInfo;
volatile extern deviceInfo screwTake, screwIgn, outTan, outFireBar, outPumpBoil, outPumpCatl;

void initOutDevices();
void changeDevState(deviceInfo *cDevice);//change state of device
void enableDev(deviceInfo *cDevice);//enable device
void disableDev(deviceInfo *cDevice);//disable device

#endif