/*
 / _____)             _              | |
 ( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
 (______/|_____)_|_|_| \__)_____)\____)_| |_|
 (C)2013 Semtech

 Description: Delay functions implementation

 License: Revised BSD License, see LICENSE.TXT file include in the project

 Maintainer: Miguel Luis and Gregory Cristian
 */
#include "board.h"

void Delay( float s )
{
    DelayMs(s * 1000.0f);
}

void DelayMs( uint32_t ms )
{
#if defined(FSL_RTOS_FREE_RTOS)
    OSA_TimeDelay(ms);
#elif defined(USE_FREE_RTOS)
    vTaskDelay((((uint32_t)(ms)+500uL/(uint32_t)configTICK_RATE_HZ) *(uint32_t)configTICK_RATE_HZ/1000uL));
#else
    if ( TimerGetLowPowerEnable() == true ) {
        RtcDelayMs(ms);
    } else {
        TimerHwDelayMs(ms);
    }
#endif
}
