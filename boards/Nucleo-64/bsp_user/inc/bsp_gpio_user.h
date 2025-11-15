#ifndef BSP_GPIO_USER_H
#define BSP_GPIO_USER_H

#include "bsp.h"

typedef enum
{
    BSP_GPIO_USER_PIN_LED,
    BSP_GPIO_USER_PIN_BUTTON,
    BSP_GPIO_USER_PIN_STEPPER_MOTOR_DIRECTION,
    BSP_GPIO_USER_PIN_STEPPER_MOTOR_STEP,
    BSP_GPIO_USER_PIN_MAX
} BspGpioUser_Pin_t;

extern Bsp_Gpio_t BspGpioUser_HandleTable[BSP_GPIO_USER_PIN_MAX];

Bsp_Gpio_t *BspGpioUser_GetGpioHandle(const Bsp_GpioPin_t exti_pin);

#endif /* BSP_GPIO_USER_H */