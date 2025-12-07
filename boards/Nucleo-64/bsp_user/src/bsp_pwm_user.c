#include "bsp_pwm_user.h"

#include "tim.h"

#include "bsp.h"

const Bsp_PwmConfig_t BspPwmUser_TimerConfigTable[BSP_PWM_USER_TIMER_MAX] = {
    [BSP_PWM_USER_TIMER_0] = {
        .timer_handle = &htim2, .max_channel = BSP_TIMER_CHANNEL_1
    },
};