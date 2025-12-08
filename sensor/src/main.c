#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "bsp.h"
#include "bsp_gpio.h"
#include "bsp_gpio_user.h"
#include "bsp_uart.h"
#include "bsp_uart_user.h"

#include "cobs.h"
#include "sensor.h"

#define SAMPLE_SIZE            3000
#define SERIAL_DELIMITER_0     0xAAU
#define SERIAL_DELIMITER_1     0x55U
#define SERIAL_SAMPLE_START    0x01U
#define SERIAL_SAMPLE_COMPLETE 0x02U

typedef enum
{
    SERIAL_BYTE_DELIMITER_0,
    SERIAL_BYTE_DELIMITER_1,
    SERIAL_BYTE_COMMAND,
    SERIAL_BYTE_MAX
} Serial_Byte_t;

static uint32_t samples[SAMPLE_SIZE];
static uint8_t  serial_buffer[4096U];
static uint8_t  serial_encoding_buffer[sizeof(serial_buffer)];

static void Task(void);

int main(void)
{
    Bsp_Initialize();
    (void)BspUart_Start(BSP_UART_USER_1);
    (void)BspGpio_Write(BSP_GPIO_USER_PIN_LED, BSP_GPIO_STATE_RESET);

    Sensor_Initialize();

    while (true)
    {
        Task();
    }

    return 0;
}

static void Task(void)
{
    Bsp_Error_t error;
    size_t      received = 0U;

    while (received < sizeof(serial_buffer))
    {
        size_t size = 0U;
        error     = BspUart_Receive(BSP_UART_USER_1, serial_buffer + received, 1U, &size);
        received += size;

        if ((BSP_ERROR_NONE != error) || ((size > 0U) && (0x00U == *(serial_buffer + received - 1U))))
        {
            break;
        }
    }

    if (sizeof(serial_buffer) == received)
    {
        /* TODO */
    }
    else if (BSP_ERROR_NONE == error)
    {
        size_t size = Cobs_Decode(serial_encoding_buffer, sizeof(serial_encoding_buffer), serial_buffer, received);

        if ((SIZE_MAX != size) &&
            (SERIAL_DELIMITER_0 == serial_encoding_buffer[SERIAL_BYTE_DELIMITER_0]) &&
            (SERIAL_DELIMITER_1 == serial_encoding_buffer[SERIAL_BYTE_DELIMITER_1]) &&
            (SERIAL_SAMPLE_START == serial_encoding_buffer[SERIAL_BYTE_COMMAND]))
        {
            (void)BspGpio_Write(BSP_GPIO_USER_PIN_LED, BSP_GPIO_STATE_RESET);
            Sensor_Sample(samples, SAMPLE_SIZE, NULL);
            while (Sensor_IsSampling())
            {
            }
            Sensor_ConvertRawSamples(samples, SAMPLE_SIZE);

            serial_encoding_buffer[SERIAL_BYTE_COMMAND] = SERIAL_SAMPLE_COMPLETE;
            for (size_t i = SERIAL_BYTE_MAX; i < SAMPLE_SIZE + SERIAL_BYTE_MAX; i++)
            {
                serial_encoding_buffer[i] = (uint8_t)samples[i - SERIAL_BYTE_MAX];
            }
            size = Cobs_Encode(serial_encoding_buffer, SAMPLE_SIZE + SERIAL_BYTE_MAX, serial_buffer, sizeof(serial_buffer));
            if (SIZE_MAX != size)
            {
                error = BspUart_Transmit(BSP_UART_USER_1, serial_buffer, size);
            }

            if (BSP_ERROR_NONE == error)
            {
                BspGpio_Write(BSP_GPIO_USER_PIN_LED, BSP_GPIO_STATE_SET);
            }
            else
            {
                (void)BspUart_Stop(BSP_UART_USER_1);
                (void)BspUart_Start(BSP_UART_USER_1);
            }
        }
    }
    else
    {
        (void)BspUart_Stop(BSP_UART_USER_1);
        (void)BspUart_Start(BSP_UART_USER_1);
    }
}