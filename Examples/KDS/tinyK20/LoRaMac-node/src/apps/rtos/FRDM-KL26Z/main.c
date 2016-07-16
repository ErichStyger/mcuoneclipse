/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 28.11.2015
 * \brief FreeRTOS test implementation
 *
 */

#include "board.h"

#define LOG_LEVEL_DEBUG
#include "debug.h"

/*------------------------- Local Defines --------------------------------*/
/* task priority */
#define TASK_LED_RTOS_PRIO           7U
#define TASK_FXOS_RTOS_PRIO          8U
/* task stack size */
#define TASK_LED_RTOS_STACK_SIZE     0x200U
#define TASK_FXOS_RTOS_STACK_SIZE    0x200U
/*------------------------ Local Variables -------------------------------*/
static TimerEvent_t Led1Timer;
volatile bool Led1TimerEvent = false;

static TimerEvent_t Led2Timer;
volatile bool Led2TimerEvent = false;

/*------------------------ Local Functions ------------------------------*/
/* task declare */
void task_led_rtos( task_param_t param );
void task_fxos_rtos( task_param_t param );

/*!
 * \brief Function executed on Led 1 Timeout event
 */
void OnLed1TimerEvent( TimerHandle_t xTimer );

/*!
 * \brief Function executed on Led 2 Timeout event
 */
void OnLed2TimerEvent( TimerHandle_t xTimer );

/* task define */
OSA_TASK_DEFINE(task_led_rtos, TASK_LED_RTOS_STACK_SIZE);
OSA_TASK_DEFINE(task_fxos_rtos, TASK_FXOS_RTOS_STACK_SIZE);

static osa_status_t s_result = kStatus_OSA_Error;

int main( void )
{
    // Target board initialisation
    BoardInitMcu();
    LOG_DEBUG("Mcu initialized.");
    OSA_Init();
    LOG_DEBUG("OS initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

    // These tasks will not start in BM.
    s_result = OSA_TaskCreate(task_led_rtos, (uint8_t *) "led_rtos", TASK_LED_RTOS_STACK_SIZE,
            task_led_rtos_stack, TASK_LED_RTOS_PRIO, (task_param_t) 0, false,
            &task_led_rtos_task_handler);
    if ( s_result != kStatus_OSA_Success ) {
        LOG_ERROR("Failed to create led_rtos task");
    }

    s_result = OSA_TaskCreate(task_fxos_rtos, (uint8_t *) "fxos_rtos", TASK_FXOS_RTOS_STACK_SIZE,
            task_fxos_rtos_stack, TASK_FXOS_RTOS_PRIO, (task_param_t) 0, false,
            &task_fxos_rtos_task_handler);
    if ( s_result != kStatus_OSA_Success ) {
        LOG_ERROR("Failed to create fxos_rtos task");
    }

    // Print the initial banner
    LOG_DEBUG("Hello World!\r\n");

    OSA_Start();

    for ( ;; ) {
    }                    // Should not achieve here
}

/*!
 * task to blink led rtos between 1 seconds.
 */
void task_led_rtos( task_param_t param )
{
    TimerInit(&Led1Timer, "Led1Timer", 250, OnLed1TimerEvent, false);
    TimerInit(&Led2Timer, "Led2Timer", 250, OnLed2TimerEvent, false);

    // Switch LED 1 ON
    GpioWrite(&Led1, 0);
    TimerStart(&Led1Timer);

    while (1) {
        if ( Led1TimerEvent == true ) {
            Led1TimerEvent = false;

            // Switch LED 1 OFF
            GpioWrite(&Led1, 1);
            // Switch LED 2 ON
            GpioWrite(&Led2, 0);
            TimerStart(&Led2Timer);
        }

        if ( Led2TimerEvent == true ) {
            Led2TimerEvent = false;

            // Switch LED 2 OFF
            GpioWrite(&Led2, 1);
            // Switch LED 3 ON
            GpioWrite(&Led1, 0);
            TimerStart(&Led1Timer);
        }

        OSA_TimeDelay(50);
    }
}

void task_fxos_rtos( task_param_t param )
{
    /*! I2C channel to be used by digital 3D accelerometer */
    Fxos.instance = FXOS8700CQ_I2C_INSTANCE;
    I2c.I2c = &Fxos;
    I2cInit(&I2c, I2C_SCL, I2C_SDA);

    /* Initialize accelerometer */
    FxosInit (FXOS_I2C_ADDRESS);

    while (1) {
        accel_sensor_data_t sensorData;
        if ( FxosReadSensorData(&sensorData) != FAIL ) {
            LOG_DEBUG_BARE("DATA: Accelerometer (X/Y/Z) \t%d \t%d \t%d\r\n", sensorData.accelX,
                    sensorData.accelY, sensorData.accelZ);
        }
        OSA_TimeDelay(5000);
    }
}

void OnLed1TimerEvent( TimerHandle_t xTimer )
{
    LOG_TRACE("%s expired.", pcTimerGetTimerName(xTimer));
    Led1TimerEvent = true;
}

void OnLed2TimerEvent( TimerHandle_t xTimer )
{
    LOG_TRACE("%s expired.", pcTimerGetTimerName(xTimer));
    Led2TimerEvent = true;
}
