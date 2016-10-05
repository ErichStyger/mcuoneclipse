#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

void Sleep(unsigned int ms)
{
	SemaphoreHandle_t xSemaphore = NULL;

	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreTake( xSemaphore, portTICK_PERIOD_MS * ms);
}
