/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K64F_lwIP_FreeRTOS
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-18, 16:12, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "eNet1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "KSDK1.h"
#include "SYS1.h"
#include "RTT1.h"
#include "CS1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */
#define DHCP_TIMEOUT  10

#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/udp.h"
#include "lwip/dhcp.h"
#include "netif/etharp.h"
#include "ethernetif.h"

#include <string.h>
#include <stdio.h>

/* providing a debug_printf() to make the linker happy */
int debug_printf(const char  *fmt_s, ...)
{
#if 0
   va_list  ap;
   int  result;
   /* Do nothing if the debug uart is not initialized.*/
   if (s_debugConsole.type == kDebugConsoleNone)
   {
       return -1;
   }
   va_start(ap, fmt_s);
   result = _doprint(NULL, debug_putc, -1, (char *)fmt_s, ap);
   va_end(ap);

   return result;
#else
   return -1;
#endif
}

#if 1 /* depending on the GNU tools and libraries, a custom _sbrk() is needed */
void *_sbrk ( uint32_t delta ) {
extern char end; /* Defined by the linker */
static char *heap_end;
char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &end;
  }

  prev_heap_end = heap_end;
  heap_end += delta;
  return (void *) prev_heap_end;
}
#endif

static void LwipInitTask(void* pvArguments) {
  err_t err;
  struct netif fsl_netif0;
  ip_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;
  char msg[] = "This is my message";

  (void)pvArguments;
  // Init lwip stack
  tcpip_init(NULL,NULL);
  printf("%s: lwip init called ..\n", __FUNCTION__);

  // Setup IP Config for DHCP ...
  IP4_ADDR(&fsl_netif0_ipaddr, 0,0,0,0);
  IP4_ADDR(&fsl_netif0_netmask, 0,0,0,0);
  IP4_ADDR(&fsl_netif0_gw, 0,0,0,0);

  /* Add a network interface to the list of lwIP netifs. */
  netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init, ethernet_input);
  /* Set the network interface as the default network interface. */
  netif_set_default(&fsl_netif0);

  for(;;) {
    /* obtain the IP address, default gateway and subnet mask by using DHCP*/
    err = dhcp_start(&fsl_netif0);

    printf("%s : Started DCHP request (%s)\n", __FUNCTION__, lwip_strerr(err));
    for(int i=0; i < DHCP_TIMEOUT && fsl_netif0.dhcp->state != DHCP_BOUND; i++) {
      printf("%s : Current DHCP State : %d\n", __FUNCTION__, fsl_netif0.dhcp->state);
      // Wait a second
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }

    // Make it active ...
    netif_set_up(&fsl_netif0);

    printf("%s : Interface is up : %d\n", __FUNCTION__, fsl_netif0.dhcp->state);
    printf("%s : IP %s\n", __FUNCTION__, ipaddr_ntoa(&fsl_netif0.ip_addr));
    printf("%s : NM %s\n", __FUNCTION__, ipaddr_ntoa(&fsl_netif0.netmask));
    printf("%s : GW %s\n", __FUNCTION__, ipaddr_ntoa(&fsl_netif0.gw));

    if (fsl_netif0.dhcp->state == DHCP_BOUND) {
      // Send out some UDP data
      struct netconn* pConnection;

      // Create UDP connection
      pConnection = netconn_new(NETCONN_UDP);
      // Connect to local port
      err = netconn_bind(pConnection, IP_ADDR_ANY, 12345);
      printf("%s : Bound to IP_ADDR_ANY port 12345 (%s)\n", __FUNCTION__, lwip_strerr(err));

      err = netconn_connect(pConnection, IP_ADDR_BROADCAST, 12346 );
      printf("%s : Connected to IP_ADDR_BROADCAST port 12346 (%s)\n", __FUNCTION__, lwip_strerr(err));

      for(int i = 0; i < 10; i++ ){
        struct netbuf* buf = netbuf_new();
          void* data = netbuf_alloc(buf, sizeof(msg));

          memcpy (data, msg, sizeof (msg));
          err = netconn_send(pConnection, buf);
        printf("%s : Sending to IP_ADDR_BROADCAST port 12346 (%s)\n", __FUNCTION__, lwip_strerr(err));

          netbuf_delete(buf); // De-allocate packet buffer

          // Wait a second
        vTaskDelay(1000/portTICK_PERIOD_MS);
      }

      err = netconn_disconnect(pConnection);
      printf("%s : Disconnected from IP_ADDR_BROADCAST port 12346 (%s)\n", __FUNCTION__, lwip_strerr(err));

      err = netconn_delete(pConnection);
      printf("%s : Deleted connection (%s)\n", __FUNCTION__, lwip_strerr(err));
    }
    // Wait a second
    vTaskDelay(1000/portTICK_PERIOD_MS);

    /* finish the lease of the IP address */
    err = dhcp_release(&fsl_netif0);
    printf("%s : DHCP Release (%s)\n", __FUNCTION__, lwip_strerr(err));

    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  printf("Welcome to the world of lwip!\r\n");

  /* Disable the mpu */
  MPU_BWR_CESR_VLD(MPU, 0);

  /* create lwIP initialization task */
  xTaskCreate(LwipInitTask,
      "LwipInitTask",
      configMINIMAL_STACK_SIZE * 4,
      (void*)NULL,
      tskIDLE_PRIORITY,
      (xTaskHandle*)NULL);

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
