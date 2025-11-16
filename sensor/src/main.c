#include <stdbool.h>
#include <stdint.h>

#include "bsp.h"
#include "bsp_gpio.h"
#include "bsp_gpio_user.h"

#include "sensor.h"

#define SAMPLE_SIZE 3000

static uint32_t samples[SAMPLE_SIZE];

int main(void)
{
    Bsp_Initialize();
    BspGpio_Write(BSP_GPIO_USER_PIN_LED, BSP_GPIO_STATE_RESET);

    Sensor_Initialize();
    Sensor_Sample(samples, SAMPLE_SIZE, NULL);
    while (Sensor_IsSampling())
    {
    }
    Sensor_ConvertRawSamples(samples, SAMPLE_SIZE);

    BspGpio_Write(BSP_GPIO_USER_PIN_LED, BSP_GPIO_STATE_SET);

    return 0;
}
