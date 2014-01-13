/**
 * \file
 * \brief Mealy Sequential Machine.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Here all the Mealy interfaces are implemented.
 *
  Following Mealy Sequential State Machine is implemented:
  \dot
  digraph mealy_graph {
      node [shape=ellipse];
      rankdir=LR;
      I    [fillcolor=lightblue,style=filled,label="init" ];
      A    [fillcolor=lightblue,style=filled,label="A:0000" ];
      B    [fillcolor=lightblue,style=filled,label="B:1000" ];
      C    [fillcolor=lightblue,style=filled,label="C:0100"];
      D    [fillcolor=lightblue,style=filled,label="D:0010"];
      E    [fillcolor=lightblue,style=filled,label="E:0001"];
      I -> A;
      A -> A [label="a/all LED off"];
      A -> B [label="b/LED1 on"];
      B -> B [label="b/LED1 on"];
      B -> C [label="a/LED2 on"];
      C -> C [label="a/LED2 on"];
      C -> D [label="b/LED3 on"];
      D -> D [label="b/LED3 on"];
      D -> E [label="a/LED4 on"];
      E -> E [label="a/LED4 on"];
      E -> B [label="b/LED1 on"];
  }
  \enddot
  This state machine will change one LED for each level change:
  \image html MealyLed.jpg
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_MEALY
#include "Mealy.h"    /* our own interface */
#include "LED.h"      /* interface to LED driver */
#include "Keys.h"     /* interface to switch 1 */
#include "CLS1.h"
#include "UTIL1.h"

static bool MEALY_isOn = TRUE;

/*! 
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr("Mealy Status", MEALY_isOn?"on \r\n":"off\r\n", io->stdOut);
}

/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  /* list your local help here */
  CLS1_SendHelpStr("mealy", "Group of Mealy commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  on|off", "Turns the machine on or off\r\n", io->stdOut);
}

uint8_t MEALY_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "mealy status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "mealy help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp(cmd, "mealy on", sizeof("mealy on")-1)==0) {
    MEALY_isOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strncmp(cmd, "mealy off", sizeof("mealy off")-1)==0) {
    MEALY_isOn = FALSE;
    *handled = TRUE;
  }
  return ERR_OK;
}

/*!
 \brief Enumeration for the LEDs we want to emit. Note that they are encoded in bits
*/
typedef enum LED_Enum {
  LED1=(1<<0), /*!< LED1 is on */
  LED2=(1<<1), /*!< LED2 is on */
  LED3=(1<<2), /*!< LED3 is on */
  LED4=(1<<3)  /*!< LED4 is on */
} LED_Enum; /*!< state machine states */

/*!
 \brief Enumeration of all our states in the state machine
*/
typedef enum MealyState {
  A=0, /*!< Original/Entry state: all LEDs are off */
  B=1, /*!< LED1 is on */
  C=2, /*!< LED2 is on */
  D=3, /*!< LED3 is on */
  E=4  /*!< LED4 is on */
} MealyState; /*!< state machine states */

/*!
 \brief Input states for the Mealy Sequential Machine.
*/
typedef enum InputState {
  INPUT_a=0, /*!< Must be zero, used as index into ::tbl */
  INPUT_b=1  /*!< Must be one, used as index into ::tbl */
} InputState;

static MealyState state; /*!< The current state of our machine */

/*!
  \brief Array of 5 states (::A,::B,::C,::D,::E), 2 input states (::INPUT_a, ::INPUT_b) and 4 LEDs as output states.
*/
const uint8_t tbl[5][2][2] = /* format: {next,output} */
   /*     input a          input b */
 { /*A*/ {{A,0},    {B,LED1}},       /*!< State A: with input_a, remain in A; with input_b: go to B and turn on LED1 */
   /*B*/ {{C,LED2}, {B,LED1}},
   /*C*/ {{C,LED2}, {D,LED3}},
   /*D*/ {{E,LED4}, {D,LED3}},
   /*E*/ {{E,LED4}, {B,LED1}},
 };

/*!
  \brief Method to return which input key has been pressed for the Mealy Sequential Machine.
  \return Returns ::INPUT_a or ::INPUT_b
 */
static InputState GetInput(void) {
  if (KEY1_Get()==0) { /* b */
    return INPUT_b;
  } else { /* a */
    return INPUT_a;
  }
}

/*!
 * \brief Turn the LEDs on or off depending on the led set.
 * \param [in] set Bit set of LEDs. A one indicates to turn the LED on, a zero will turn it off.
 */
static void LEDPut(const uint8_t set) {
  LED1_Put(set&LED1);
  LED2_Put(set&LED2);
  LED3_Put(set&LED3);
  LED4_Put(set&LED4);
}

/*!
\brief Mealy Sequential Machine to test the LEDs.
       The machine has the internal states A, B C, D and E,
       input states a and b and output states O = {set of LED};
*/
void MEALY_Run(void) {
  InputState i;

  if (MEALY_isOn) {
    i = GetInput(); /* get input state */
    LEDPut(tbl[state][i][1]); /* output the next state */
    state = (MealyState)(tbl[state][(uint8_t)i][0]);  /* read out next internal state */
  }
}

/*! \brief Initializes the Mealy state machine */
void MEALY_Init(void) {
  state = A;
  MEALY_isOn = FALSE;
}
#endif
