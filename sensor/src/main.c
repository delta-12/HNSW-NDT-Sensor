#include "bsp_gpio_user.h"
#include "bsp_timer_user.h"

#include "sensor.h"

static Sensor_t sensor = {
    .timer     = BSP_TIMER_USER_TIMER_SENSOR,
    .solenoid  = BSP_GPIO_USER_SENSOR_SOLENOID,
    .adc_clock = BSP_GPIO_USER_SENSOR_CLK,
    .adc_bits  = {
        BSP_GPIO_USER_SENSOR_ADC_BIT_0,
        BSP_GPIO_USER_SENSOR_ADC_BIT_1,
        BSP_GPIO_USER_SENSOR_ADC_BIT_2,
        BSP_GPIO_USER_SENSOR_ADC_BIT_3,
        BSP_GPIO_USER_SENSOR_ADC_BIT_4,
        BSP_GPIO_USER_SENSOR_ADC_BIT_5,
        BSP_GPIO_USER_SENSOR_ADC_BIT_6,
        BSP_GPIO_USER_SENSOR_ADC_BIT_7,
    }
};

int main(void)
{
    (void)(sensor);

    return 0;
}