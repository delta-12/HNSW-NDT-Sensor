#include "bsp_gpio_user.h"

#include "main.h"

#include "bsp.h"

Bsp_Gpio_t BspGpioUser_HandleTable[BSP_GPIO_USER_PIN_MAX] = {
    [BSP_GPIO_USER_PIN_LED] = {
        .gpio_port = LD2_GPIO_Port,
        .gpio_pin  = LD2_Pin,
        .mode      = BSP_GPIO_MODE_OUTPUT,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_PIN_STEPPER_MOTOR_DIRECTION] = {
        .gpio_port = STEPPER_DIRECTION_GPIO_Port,
        .gpio_pin  = STEPPER_DIRECTION_Pin,
        .mode      = BSP_GPIO_MODE_OUTPUT,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_PIN_STEPPER_MOTOR_STEP] = {
        .gpio_port = STEPPER_STEP_GPIO_Port,
        .gpio_pin  = STEPPER_STEP_Pin,
        .mode      = BSP_GPIO_MODE_OUTPUT,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
};

Bsp_Gpio_t *BspGpioUser_GetGpioHandle(const Bsp_GpioPin_t exti_pin)
{
    Bsp_Gpio_t *gpio = NULL;

    switch (exti_pin)
    {
    default:
        break;
    }

    return gpio;
}