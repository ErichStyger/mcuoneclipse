//#include "MKL25Z128LK4.h"
#include "MKL25Z4.h"
#include "FreeRTOS/FreeRTOS.h"

//! @brief Init hardware for FRDM-KL25Z4 board.
#define RED         (18) /* Red LED is on BTB18 */
#define GREEN       (19) /* Red LED is on BTB19 */
#define RED_SHIFT   (1<<RED)
#define GREEN_SHIFT (1<<GREEN)
#define BLUE	    (1)
#define BLUE_SHIFT  (1<<BLUE)

#define RED_OFF()       (GPIOB_PSOR = RED_SHIFT)
#define RED_ON()        (GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE()    (GPIOB_PTOR = RED_SHIFT)

#define GREEN_OFF()     (GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON()      (GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE()  (GPIOB_PTOR = GREEN_SHIFT)

#define BLUE_OFF()      (GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON		(GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE	(GPIOD_PTOR = BLUE_SHIFT)

static void InitLED(void) {
  /*
   * Initialize the Red LED (PTB18)
   */
  {
          /* Turn on clock to PortB module */
          SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

          /* Set the PTB18 pin multiplexer to GPIO mode */
          PORTB_PCR18 = PORT_PCR_MUX(1);

          /* Set the initial output state to high */
          GPIOB_PSOR |= RED_SHIFT;

          /* Set the pins direction to output */
          GPIOB_PDDR |= RED_SHIFT;
  }

  /*
   * Initialize the Green LED (PTB19)
   */
  {
          /* Turn on clock to PortB module */
          SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

          /* Set the PTB19 pin multiplexer to GPIO mode */
          PORTB_PCR19 = PORT_PCR_MUX(1);

          /* Set the initial output state to high */
          GPIOB_PSOR |= GREEN_SHIFT;

          /* Set the pins direction to output */
          GPIOB_PDDR |= GREEN_SHIFT;
  }

  /*
   * Initialize the Blue LED (PTD1)
   */
  {
          /* Turn on clock to PortB module */
          SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

          /* Set the PTD1 pin multiplexer to GPIO mode */
          PORTD_PCR1 = PORT_PCR_MUX(1);

          /* Set the initial output state to high */
          GPIOD_PSOR = BLUE_SHIFT;

          /* Set the pins direction to output */
          GPIOD_PDDR |= BLUE_SHIFT;
  }
}

static void init_hardware(void)
{
  InitLED();
}
/* Service constants */
#define COP_PDD_KEY_1 0x55U                      /**< First key */
#define COP_PDD_KEY_2 0xAAU                      /**< Second key */

static portTASK_FUNCTION(redTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    RED_TOGGLE();
    //SIM_SRVCOP = COP_PDD_KEY_1;
    //SIM_SRVCOP = COP_PDD_KEY_2;
    vTaskDelay(10/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(greenTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    GREEN_TOGGLE();
    vTaskDelay(1200/portTICK_RATE_MS); /* wait time, so the other task can give token */
  }
}

static xTaskHandle redTaskHandle, greenTaskHandle;

static void start(void) {
  if (xTaskCreate(
        redTask,  /* pointer to the task */
        (signed char *)"Red", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)&redTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (xTaskCreate(
        greenTask,  /* pointer to the task */
        (signed char *)"Green", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)&greenTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler(); /* does not return */
}

void SystemInit(void) {
   SCB_VTOR = (uint32_t)(&__vector_table); /* Set the interrupt vector table position */
  /* Disable the WDOG module */
  /* SIM_COPC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COPT=0,COPCLKS=0,COPW=0 */
  SIM_COPC = SIM_COPC_COPT(0x00);                                   

  /* Disable the WDOG module */
  /* SIM_COPC: COPT=0,COPCLKS=0,COPW=0 */
  SIM_COPC = (uint32_t)0x00u;
  
       SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK );

}

int main(void)
{
  init_hardware();
  start();
  return 0;
}
