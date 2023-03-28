#ifndef __CGI_H__
#define __CGI_H__

// GPIOs for Leds
#define LED1	18
#define LED2	19
#define LED3	20
#define LED4	21

/* initialize the CGI handler */
void  cgi_init(void);

/* CGI handler for LED control */
const char * cgi_handler_basic(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
/* CGI handler for LED control with feedback*/
const char * cgi_handler_extended(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);


/* led control and debugging info */
void Led_On(int led);
void Led_Off(int led);

#endif // __CGI_H__
