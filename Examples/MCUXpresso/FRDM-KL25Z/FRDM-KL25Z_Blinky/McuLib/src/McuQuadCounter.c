/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuQuadCounter.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : QuadCounter
**     Version     : Component 01.034, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-08-14, 06:24, # CodeGen: 679
**     Abstract    :
**
This driver implements a quadrature encoder using two signals (C1 and C2) to generate position information.
**     Settings    :
**          Component name                                 : McuQuadCounter
**          C1 and C2 swapped                              : no
**          Counter Type                                   : 32bit
**          Method                                         : 
**            Sampling                                     : Enabled
**              Error Correction                           : no
**              C1                                         : SDK_BitIO
**              C2                                         : SDK_BitIO
**            Input Capture                                : Disabled
**          Shell                                          : Enabled
**            Shell                                        : McuShell
**            Utility                                      : McuUtility
**     Contents    :
**         GetPos       - McuQuadCounter_QuadCntrType McuQuadCounter_GetPos(void);
**         SetPos       - void McuQuadCounter_SetPos(McuQuadCounter_QuadCntrType pos);
**         GetVal       - uint8_t McuQuadCounter_GetVal(void);
**         Sample       - void McuQuadCounter_Sample(void);
**         Deinit       - void McuQuadCounter_Deinit(void);
**         Init         - void McuQuadCounter_Init(void);
**         ParseCommand - uint8_t McuQuadCounter_ParseCommand(const unsigned char *cmd, bool *handled,...
**
** * Copyright (c) 2014-2020, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuQuadCounter.h
** @version 01.00
** @brief
**
This driver implements a quadrature encoder using two signals (C1 and C2) to generate position information.
*/         
/*!
**  @addtogroup McuQuadCounter_module McuQuadCounter module documentation
**  @{
*/         

/* MODULE McuQuadCounter. */

#include "McuQuadCounter.h"

#if McuQuadCounter_SWAP_PINS_AT_RUNTIME
  static bool McuQuadCounter_swappedPins = FALSE;
#endif

/* The decoder has 4 different states, together with the previous state the table has 16 entries.
   The value in the table (0,1,-1) indicates the steps taken since previous sample. */
#define QUAD_ERROR  3 /*!< Value to indicate an error in impulse detection. Has to be different from 0,1,-1 */

static const signed char McuQuadCounter_Quad_Table[4][4] =
  {               /* prev   new    */
    {             /* c1 c2  c1 c2  */
     0,           /* 0  0   0  0  no change or missed a step? */
     1,           /* 0  0   0  1   */
     -1,          /* 0  0   1  0   */
     QUAD_ERROR   /* 0  0   1  1  error, lost impulse */
     },
    {             /* c1 c2  c1 c2  */
     -1,          /* 0  1   0  0   */
     0,           /* 0  1   0  1   no change or missed a step? */
     QUAD_ERROR,  /* 0  1   1  0   error, lost impulse */
     1            /* 0  1   1  1   */
     },
    {             /* c1 c2  c1 c2  */
     1,           /* 1  0   0  0   */
     QUAD_ERROR,  /* 1  0   0  1   error, lost impulse */
     0,           /* 1  0   1  0   no change or missed a step? */
     -1           /* 1  0   1  1   */
     },
    {             /* c1 c2  c1 c2  */
     QUAD_ERROR,  /* 1  1   0  0   error, lost impulse */
     -1,          /* 1  1   0  1   */
     1,           /* 1  1   1  0   */
     0            /* 1  1   1  1   no change or missed a step? */
     }
  };
static uint8_t McuQuadCounter_last_quadrature_value; /*! Value of C1&C2 during last round. */

static McuQuadCounter_QuadCntrType McuQuadCounter_currPos = 0; /*!< Current position */

/*
** ===================================================================
**     Method      :  SetPos (component QuadCounter)
**
**     Description :
**         Sets the position information. Can be used as well to reset
**         the position information.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pos             - Position value to be set.
**     Returns     : Nothing
** ===================================================================
*/
void McuQuadCounter_SetPos(McuQuadCounter_QuadCntrType pos)
{
  McuQuadCounter_currPos = pos;
}

/*
** ===================================================================
**     Method      :  GetPos (component QuadCounter)
**
**     Description :
**         Returns the current position based on the encoder tracking.
**     Parameters  : None
**     Returns     :
**         ---             - position
** ===================================================================
*/
McuQuadCounter_QuadCntrType McuQuadCounter_GetPos(void)
{
  return McuQuadCounter_currPos;
}

/*
** ===================================================================
**     Method      :  GetVal (component QuadCounter)
**
**     Description :
**         Returns the quadrature value (0, 1, 2 or 3)
**     Parameters  : None
**     Returns     :
**         ---             - Quadrature value (0-3)
** ===================================================================
*/
uint8_t McuQuadCounter_GetVal(void)
{
#if McuQuadCounter_SWAP_PINS_AT_RUNTIME
  if (McuQuadCounter_swappedPins) {
    return McuQuadCounter_GET_C1_C2_PINS_SWAPPED();
  } else {
    return McuQuadCounter_GET_C1_C2_PINS();
  }
#else
  return McuQuadCounter_GET_C1_C2_PINS();
#endif
}

/*
** ===================================================================
**     Method      :  Sample (component QuadCounter)
**
**     Description :
**         Call this method to periodically sample the signals.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuQuadCounter_Sample(void)
{
  signed char new_step;
  uint8_t c12; /* value of the two sensor input */

  c12 = McuQuadCounter_GetVal();
  new_step = McuQuadCounter_Quad_Table[McuQuadCounter_last_quadrature_value][c12];
  McuQuadCounter_last_quadrature_value = c12;
  if (new_step == QUAD_ERROR) {
  } else if (new_step != 0) {
    McuQuadCounter_currPos += new_step;
  }
}

/*
** ===================================================================
**     Method      :  Deinit (component QuadCounter)
**
**     Description :
**         Module de-initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuQuadCounter_Deinit(void)
{
  /* nothing needed */
}

/*
** ===================================================================
**     Method      :  Init (component QuadCounter)
**
**     Description :
**         Module initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuQuadCounter_Init(void)
{
  McuQuadCounter_currPos = 0;
  McuQuadCounter_last_quadrature_value = McuQuadCounter_GET_C1_C2_PINS();
#if McuQuadCounter_SWAP_PINS_AT_RUNTIME
  McuQuadCounter_swappedPins = FALSE;
#endif
}

/*
** ===================================================================
**     Method      :  ParseCommand (component QuadCounter)
**
**     Description :
**         Handler to process shell commands
**     Parameters  :
**         NAME            - DESCRIPTION
**         cmd             - Command string to be parsed
**       * handled         - Pointer to boolean. The handler
**                           sets this variable to TRUE if command was
**                           handled, otherwise let it untouched.
**         io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t McuQuadCounter_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io)
{
  uint8_t res=ERR_OK;

  if (McuUtility_strcmp((const char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((const char *)cmd, "McuQuadCounter help")==0) {
    McuShell_SendHelpStr((const unsigned char*)"McuQuadCounter", (const unsigned char*)"McuQuadCounter command group\r\n", io->stdOut);
    McuShell_SendHelpStr((const unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((const unsigned char*)"  reset", (const unsigned char*)"Reset the current position counter\r\n", io->stdOut);
    *handled = TRUE;
  } else if (McuUtility_strcmp((const char*)cmd, McuShell_CMD_STATUS)==0 || McuUtility_strcmp((const char*)cmd, "McuQuadCounter status")==0) {
    McuShell_SendStr((const unsigned char*)"McuQuadCounter:\r\n", io->stdOut);
    McuShell_SendStatusStr((const unsigned char*)"  pos", (const unsigned char*)"", io->stdOut);
  #if McuQuadCounter_CNTR_BITS==16
    McuShell_SendNum16u(McuQuadCounter_currPos, io->stdOut);
  #elif McuQuadCounter_CNTR_BITS==32
    McuShell_SendNum32u(McuQuadCounter_currPos, io->stdOut);
  #else
    #error "unknown counter size!"
  #endif
    McuShell_SendStr((const unsigned char*)", ", io->stdOut);
  #if McuQuadCounter_CNTR_BITS==16
    McuShell_SendNum16s((int16_t)McuQuadCounter_currPos, io->stdOut);
  #elif McuQuadCounter_CNTR_BITS==32
    McuShell_SendNum32s((int32_t)McuQuadCounter_currPos, io->stdOut);
  #else
    #error "unknown counter size!"
  #endif
    McuShell_SendStr((const unsigned char*)"\r\n", io->stdOut);
    McuShell_SendStatusStr((const unsigned char*)"  C1 C2", (const unsigned char*)"", io->stdOut);
    if (McuQuadCounter_GET_C1_PIN()!=0) {
      McuShell_SendStr((const unsigned char*)"1 ", io->stdOut);
    } else {
      McuShell_SendStr((const unsigned char*)"0 ", io->stdOut);
    }
    if (McuQuadCounter_GET_C2_PIN()!=0) {
      McuShell_SendStr((const unsigned char*)"1\r\n", io->stdOut);
    } else {
      McuShell_SendStr((const unsigned char*)"0\r\n", io->stdOut);
    }
    *handled = TRUE;
  } else if (McuUtility_strcmp((const char*)cmd, "McuQuadCounter reset")==0) {
    McuQuadCounter_SetPos(0);
    *handled = TRUE;
  }
  return res;
}

/* END McuQuadCounter. */

/*!
** @}
*/