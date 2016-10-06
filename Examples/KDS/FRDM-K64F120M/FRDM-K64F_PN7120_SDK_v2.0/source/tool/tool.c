#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h" /* << EST */

void Sleep(unsigned int ms)
{
#if 0
	SemaphoreHandle_t xSemaphore = NULL;

	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreTake( xSemaphore, portTICK_PERIOD_MS * ms);
#else /* << EST */
	vTaskDelay(pdMS_TO_TICKS(ms));
#endif
}
