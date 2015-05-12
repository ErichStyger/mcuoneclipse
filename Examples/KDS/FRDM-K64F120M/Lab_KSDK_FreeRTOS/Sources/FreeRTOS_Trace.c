/*
 * FreeRTOS_Trace.c
 *
 *  Created on: 03.05.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "Utility.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#if configUSE_TRACE_HOOKS
  #include "trcUser.h"
#endif

#if configUSE_TRACE_HOOKS
static void vGetGDBDumpCommand(uint8_t *buf, uint16_t bufSize, uint8_t *fileName) {
  /* construct gdb command string: dump binary memory <file> <hexStartAddr> <hexEndAddr> */
  uint8_t *ptr; /* pointer to data */
  size_t len; /* size/length of data */

  ptr = (uint8_t*)vTraceGetTraceBuffer();
  len = uiTraceGetTraceBufferSize();
  Utility_strcpy(buf, bufSize, (unsigned char*)"dump binary memory ");
  Utility_strcat(buf, bufSize, fileName);
  Utility_strcat(buf, bufSize, (unsigned char*)" 0x");
  Utility_strcatNum32Hex(buf, bufSize, (uint32_t)ptr);
  Utility_strcat(buf, bufSize, (unsigned char*)" 0x");
  Utility_strcatNum32Hex(buf, bufSize, (uint32_t)(ptr+len));
}

void RTOSTRC_OnTraceWrap(void) {
  uint8_t buf[64];

  /* GDB: dump binary memory <file> <hexStartAddr> <hexEndAddr> */
  vGetGDBDumpCommand(buf, sizeof(buf), (uint8_t*)"c:\\tmp\\trc.dump");
}

void RTOSTRC_Init(void) {
	vTraceInitTraceData();
	if (uiTraceStart()==0) {
		for(;;); /* error */
	}
}
#endif

