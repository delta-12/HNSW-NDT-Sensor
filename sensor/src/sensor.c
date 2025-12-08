#include "sensor.h"

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_tim.h"

#include "bsp.h"
#include "bsp_gpio.h"
#include "bsp_gpio_user.h"
#include "bsp_pwm.h"
#include "bsp_pwm_user.h"
#include "bsp_timer.h"
#include "bsp_timer_user.h"

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
    BspTimerUser_Timer_t timer;
    DMA_HandleTypeDef *dma_handle;
    BspGpioUser_Pin_t solenoid;
    BspPwmUser_Timer_t adc_clock_timer;
    Bsp_TimerChannel_t adc_clock_channel;
    BspGpioUser_Pin_t adc_bits[SENSOR_ADC_BIT_MAX];
    volatile bool sampling;
    Bsp_Callback_t callback;
} Sensor_t;

extern DMA_HandleTypeDef hdma_tim1_up;

static Sensor_t sensor = {
    .timer             = BSP_TIMER_USER_TIMER_SENSOR,
    .dma_handle        = &hdma_tim1_up,
    .solenoid          = BSP_GPIO_USER_SENSOR_SOLENOID,
    .adc_clock_timer   = BSP_PWM_USER_TIMER_0,
    .adc_clock_channel = BSP_TIMER_CHANNEL_1,
    .adc_bits          = {
        BSP_GPIO_USER_SENSOR_ADC_BIT_0,
        BSP_GPIO_USER_SENSOR_ADC_BIT_1,
        BSP_GPIO_USER_SENSOR_ADC_BIT_2,
        BSP_GPIO_USER_SENSOR_ADC_BIT_3,
        BSP_GPIO_USER_SENSOR_ADC_BIT_4,
        BSP_GPIO_USER_SENSOR_ADC_BIT_5,
        BSP_GPIO_USER_SENSOR_ADC_BIT_6,
        BSP_GPIO_USER_SENSOR_ADC_BIT_7,
    },
    .sampling = false,
    .callback = {
        .function = NULL,
        .arg      = NULL,
    },
};

static void Sensor_Callback(const DMA_HandleTypeDef *const hdma);

void Sensor_Initialize(void)
{
    sensor.sampling = false;

    (void)BspGpio_Write(sensor.solenoid, BSP_GPIO_STATE_RESET);

    // __HAL_TIM_ENABLE_DMA(BspTimerUser_HandleTable[sensor.timer].timer_handle, TIM_DMA_UPDATE);
    HAL_DMA_RegisterCallback(sensor.dma_handle, HAL_DMA_XFER_CPLT_CB_ID, (void (*)(DMA_HandleTypeDef *)) Sensor_Callback);
}

void Sensor_Sample(Sensor_Sample_t *const buffer, const uint32_t count, const Bsp_Callback_t *const callback)
{
    if (!sensor.sampling && (NULL != buffer))
    {
        sensor.sampling = true;

        if (NULL != callback)
        {
            sensor.callback = *callback;
        }
        else
        {
            sensor.callback.function = NULL;
        }

        (void)BspPwm_Start(sensor.adc_clock_timer, sensor.adc_clock_channel);
        (void)BspPwm_SetDutyCycle(sensor.adc_clock_timer, sensor.adc_clock_channel, 0.50);

        (void)BspGpio_Write(sensor.solenoid, BSP_GPIO_STATE_SET);
        Bsp_Delay(80U);
        (void)BspGpio_Write(sensor.solenoid, BSP_GPIO_STATE_RESET);
        Bsp_Delay(15U);

        /* TODO theshold condition */

        //  __HAL_TIM_DISABLE_DMA(BspTimerUser_HandleTable[sensor.timer].timer_handle, TIM_DMA_UPDATE);
        // HAL_DMA_Abort(sensor.dma_handle);   // Fully reset DMA stream
        __HAL_TIM_ENABLE_DMA(BspTimerUser_HandleTable[sensor.timer].timer_handle, TIM_DMA_UPDATE);

        (void)HAL_DMA_Start_IT(sensor.dma_handle,
                               (uint32_t)&BspGpioUser_HandleTable[sensor.adc_bits[BSP_GPIO_USER_SENSOR_ADC_BIT_0]].gpio_port->IDR,
                               (uint32_t)buffer,
                               count);
        (void)BspTimer_Start(sensor.timer);
    }
}

bool Sensor_IsSampling(void)
{
    return sensor.sampling;
}

void Sensor_ConvertRawSamples(Sensor_Sample_t *const buffer, const uint32_t count)
{
    if (NULL != buffer)
    {
        for (uint32_t i = 0U; i < count; i++)
        {
            uint8_t sample = 0U;

            for (Sensor_AdcBit_t bit = SENSOR_ADC_BIT_0; bit < SENSOR_ADC_BIT_MAX; bit++)
            {
                sample |= (uint8_t)((Bsp_GpioPin_t)*(buffer + i) & (BspGpioUser_HandleTable[sensor.adc_bits[bit]].gpio_pin));
            }

            *(buffer + i) = (uint32_t)sample;
        }
    }
}

static void Sensor_Callback(const DMA_HandleTypeDef *const hdma)
{
    if (hdma == sensor.dma_handle)
    {
        sensor.sampling = false;
        (void)BspTimer_Stop(sensor.timer);
        (void)BspPwm_Stop(sensor.adc_clock_timer, sensor.adc_clock_channel);

        __HAL_TIM_DISABLE_DMA(BspTimerUser_HandleTable[sensor.timer].timer_handle, TIM_DMA_UPDATE);

        /* Fully reset DMA */
        HAL_DMA_Abort(sensor.dma_handle);               // stop
        HAL_DMA_DeInit(sensor.dma_handle);              // deinit registers

        __HAL_DMA_CLEAR_FLAG(sensor.dma_handle, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4 | DMA_FLAG_TEIF0_4);
        sensor.dma_handle->State = HAL_DMA_STATE_READY;

        HAL_DMA_Init(sensor.dma_handle);                // reinit registers

        HAL_DMA_RegisterCallback(sensor.dma_handle, HAL_DMA_XFER_CPLT_CB_ID, (void (*)(DMA_HandleTypeDef *)) Sensor_Callback);

        __HAL_TIM_SET_COUNTER(BspTimerUser_HandleTable[sensor.timer].timer_handle, 0);

        if (NULL != sensor.callback.function)
        {
            sensor.callback.function(sensor.callback.arg);
        }
    }
}