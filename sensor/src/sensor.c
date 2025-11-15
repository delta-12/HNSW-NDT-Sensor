#include "sensor.h"

#include "bsp.h"
#include "bsp_gpio.h"

void Sensor_Initialize(const Sensor_t *const sensor)
{
    if (NULL != sensor)
    {
        (void)BspGpio_Write(sensor->solenoid, BSP_GPIO_STATE_RESET);
        (void)BspGpio_Write(sensor->adc_clock, BSP_GPIO_STATE_RESET);
    }
}

void Sensor_StartSample(const Sensor_t *const sensor)
{
    /* TODO */
    (void)(sensor);
}