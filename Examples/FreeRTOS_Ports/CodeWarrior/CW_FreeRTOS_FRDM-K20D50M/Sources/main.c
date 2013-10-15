/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "FreeRTOS.h"

/* Red RGB LED is on PTC3 */
#define RED             (3)
#define RED_SHIFT       (1<<RED)

#define RED_OFF()       (GPIOC_PSOR = RED_SHIFT)
#define RED_ON()        (GPIOC_PCOR = RED_SHIFT)
#define RED_TOGGLE()    (GPIOC_PTOR = RED_SHIFT)

/* Green RGB LED is on PTD4 */
#define GREEN           (4)
#define GREEN_SHIFT     (1<<GREEN)

#define GREEN_OFF()     (GPIOD_PSOR = GREEN_SHIFT)
#define GREEN_ON()      (GPIOD_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE()  (GPIOD_PTOR = GREEN_SHIFT)

/* Blue RGB LED is on PTA2 */
#define BLUE            (2)
#define BLUE_SHIFT      (1<<BLUE)

#define BLUE_OFF()      (GPIOA_PSOR = BLUE_SHIFT)
#define BLUE_ON()       (GPIOA_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE()   (GPIOA_PTOR = BLUE_SHIFT)

static void InitLED(void) {
  /* Turn on clock to PortC (red led), PortD (green led) and PortA (blue led) module */
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK|SIM_SCGC5_PORTD_MASK|SIM_SCGC5_PORTA_MASK;

  /* Set the PTC3 (red led), PTD4 (green led) and PTA2 (blue led) pin multiplexer to GPIO mode */
  PORTC_PCR3 = PORT_PCR_MUX(1);
  PORTD_PCR4 = PORT_PCR_MUX(1);
  PORTA_PCR2 = PORT_PCR_MUX(1);

  /* Set the initial output state to high */
  GPIOC_PSOR |= RED_SHIFT;
  GPIOD_PSOR |= GREEN_SHIFT;
  GPIOA_PSOR |= BLUE_SHIFT;

  /* Set the pins direction to output */
  GPIOC_PDDR |= RED_SHIFT;
  GPIOD_PDDR |= GREEN_SHIFT;
  GPIOA_PDDR |= BLUE_SHIFT;
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    RED_TOGGLE();
    vTaskDelay(1000/portTICK_RATE_MS);
  }
}

int main(void)
{
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
