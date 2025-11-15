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
    [BSP_GPIO_USER_PIN_BUTTON] = {
        .gpio_port = B1_GPIO_Port,
        .gpio_pin  = B1_Pin,
        .mode      = BSP_GPIO_MODE_INPUT,
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
    [BSP_GPIO_USER_SENSOR_ADC_BIT_0] = {
        .gpio_port = SENSOR_BIT_0_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_0_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_1] = {
        .gpio_port = SENSOR_BIT_1_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_1_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_2] = {
        .gpio_port = SENSOR_BIT_2_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_2_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_3] = {
        .gpio_port = SENSOR_BIT_3_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_3_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_4] = {
        .gpio_port = SENSOR_BIT_4_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_4_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_5] = {
        .gpio_port = SENSOR_BIT_5_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_5_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_6] = {
        .gpio_port = SENSOR_BIT_6_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_6_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_ADC_BIT_7] = {
        .gpio_port = SENSOR_BIT_7_GPIO_Port,
        .gpio_pin  = SENSOR_BIT_7_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_CLK] = {
        .gpio_port = SENSOR_CLK_GPIO_Port,
        .gpio_pin  = SENSOR_CLK_Pin,
        .callback  = {
            .function = NULL,
            .arg      = NULL,
        },
        .debounce = 0U,
        .previous = 0U,
    },
    [BSP_GPIO_USER_SENSOR_SOLENOID] = {
        .gpio_port = SENSOR_SOLENOID_GPIO_Port,
        .gpio_pin  = SENSOR_SOLENOID_Pin,
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
    case B1_Pin:
        gpio = &BspGpioUser_HandleTable[BSP_GPIO_USER_PIN_BUTTON];
        break;
    default:
        break;
    }

    return gpio;
}