#ifndef __OUT_DEV_H
#define __OUT_DEV_H

#include "stm32f1xx_hal.h"

typedef enum {ENABLE_STATE, DISABLE_STATE} devstate;
typedef struct{ devstate CurrentState; uint16_t IO_port;} deviceInfo;
devstate screwTake, screwIgn, outTan, outFireBar, outPumpBoil, outPompCatl;

void initOutDevices();
void changeDevState(deviceInfo cDevice);

#endif