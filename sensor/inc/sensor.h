#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>
#include <stdint.h>

#include "bsp.h"

typedef uint32_t Sensor_Sample_t;

void Sensor_Initialize(void);
void Sensor_Sample(Sensor_Sample_t *const buffer, const uint32_t count, const Bsp_Callback_t *const callback);
bool Sensor_IsSampling(void);

#endif /* SENSOR_H */