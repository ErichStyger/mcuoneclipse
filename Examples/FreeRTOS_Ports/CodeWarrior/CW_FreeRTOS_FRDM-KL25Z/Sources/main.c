/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "FreeRTOS.h"

/* Red RGB LED is on PTB18 */
#define RED             (18)
#define RED_SHIFT       (1<<RED)

#define RED_OFF()       (GPIOB_PSOR = RED_SHIFT)
#define RED_ON()        (GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE()    (GPIOB_PTOR = RED_SHIFT)

/* Green RGB LED is on PTB19 */
#define GREEN           (19)
#define GREEN_SHIFT     (1<<GREEN)

#define GREEN_OFF()     (GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON()      (GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE()  (GPIOB_PTOR = GREEN_SHIFT)

/* Blue RGB LED is on PTD1 */
#define BLUE            (1)
#define BLUE_SHIFT      (1<<BLUE)

#define BLUE_OFF()      (GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON()       (GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE()   (GPIOD_PTOR = BLUE_SHIFT)

static void InitLED(void) {
  /* Turn on clock to PortB (red and green led) and PortD (blue led) module */
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;

  /* Set the PTB18 pin multiplexer to GPIO mode */
  PORTB_PCR18 = PORT_PCR_MUX(1);

  /* Set the PTB19 pin multiplexer to GPIO mode */
  PORTB_PCR19 = PORT_PCR_MUX(1);

  /* Set the PTD1 pin multiplexer to GPIO mode */
  PORTD_PCR1 = PORT_PCR_MUX(1);

  /* Set the initial output state to high */
  GPIOB_PSOR |= RED_SHIFT;
  GPIOB_PSOR |= GREEN_SHIFT;
  GPIOD_PSOR |= BLUE_SHIFT;

  /* Set the pins direction to output */
  GPIOB_PDDR |= RED_SHIFT;
  GPIOB_PDDR |= GREEN_SHIFT;
  GPIOD_PDDR |= BLUE_SHIFT;
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    RED_TOGGLE();
    vTaskDelay(1000/portTICK_RATE_MS);
  }
}

int main(void) {
  InitLED();
  
  RED_ON();
  RED_OFF();
  RED_TOGGLE();
  RED_OFF();
  
  GREEN_ON();
  GREEN_OFF();
  GREEN_TOGGLE();
  GREEN_OFF();

  BLUE_ON();
  BLUE_OFF();
  BLUE_TOGGLE();
  BLUE_OFF();

  if (xTaskCreate(
        MainTask,  /* pointer to the task */
        (signed char *)"Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler(); /* does not return */
	return 0;
}
