#ifndef SENSOR_H
#define SENSOR_H

#include "bsp_gpio_user.h"

typedef enum
{
    SENSOR_ADC_BIT_0,
    SENSOR_ADC_BIT_1,
    SENSOR_ADC_BIT_2,
    SENSOR_ADC_BIT_3,
    SENSOR_ADC_BIT_4,
    SENSOR_ADC_BIT_5,
    SENSOR_ADC_BIT_6,
    SENSOR_ADC_BIT_7,
    SENSOR_ADC_BIT_MAX
} Sensor_AdcBit_t;

typedef struct
{
    BspGpioUser_Pin_t solenoid;
    BspGpioUser_Pin_t adc_clock;
    BspGpioUser_Pin_t adc_bits[SENSOR_ADC_BIT_MAX];
} Sensor_t;

void Sensor_Initialize(const Sensor_t *const sensor);
void Sensor_StartSample(const Sensor_t *const sensor);

#endif /* SENSOR_H */