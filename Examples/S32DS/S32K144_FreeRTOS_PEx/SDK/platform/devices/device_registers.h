/*
** ###################################################################
**     Abstract:
**         Common include file for CMSIS register access layer headers.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All rights reserved.
**
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
** ###################################################################
*/

#ifndef DEVICE_REGISTERS_H
#define DEVICE_REGISTERS_H

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, global macro not referenced.
* The macro defines the device currently in use and may be used by components for specific checks.
*
*/


/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */

#if (defined(CPU_S32K148) || defined(CPU_S32K146) || defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT) || defined(CPU_S32K142))

    #define S32K14x_SERIES

    /* Specific core definitions */
    #include "common/s32_core_cm4.h"

    #if defined(CPU_S32K148)

        #define S32K148_SERIES

        /* Register definitions */
        #include "S32K148/include/S32K148.h"
        /* CPU specific feature definitions */
        #include "S32K148/include/S32K148_features.h"

    #elif defined(CPU_S32K146)

        #define S32K146_SERIES

        /* Register definitions */
        #include "S32K146/include/S32K146.h"
        /* CPU specific feature definitions */
        #include "S32K146/include/S32K146_features.h"

    #elif (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT))

        #define S32K144_SERIES

        /* Register definitions */
        #include "S32K144/include/S32K144.h"
        /* CPU specific feature definitions */
        #include "S32K144/include/S32K144_features.h"

    #elif defined(CPU_S32K142)

        #define S32K142_SERIES

        /* Register definitions */
        #include "S32K142/include/S32K142.h"
        /* CPU specific feature definitions */
        #include "S32K142/include/S32K142_features.h"

    #endif

#elif defined(CPU_S32V234)

    #define S32V234_SERIES

    /* Specific core definitions */
    #include "common/s32_core_cm4.h"
    /* Register definitions */
    #include "S32V234/include/S32V234.h"
    /* CPU specific feature definitions */
    #include "S32V234/include/S32V234_features.h"

#elif (defined(CPU_MPC5748G) || defined(CPU_MPC5746C) || defined(CPU_MPC5744P))

    #define MPC574x_SERIES

    /* Specific core definitions */
    #include "common/s32_core_e200.h"

    #if (defined(CPU_MPC5748G))

        #define MPC5748G_SERIES

        /* Register definitions */
        #include "MPC5748G/include/MPC5748G.h"
        /* CPU specific feature definitions */
        #include "MPC5748G/include/MPC5748G_features.h"

    #elif defined(CPU_MPC5746C)

        #define MPC5746C_SERIES

        /* Register definitions */
        #include "MPC5746C/include/MPC5746C.h"
        /* CPU specific feature definitions */
        #include "MPC5746C/include/MPC5746C_features.h"

    #elif defined(CPU_MPC5744P)

        #define MPC5744P_SERIES

        /* Register definitions */
        #include "MPC5744P/include/MPC5744P.h"
        /* CPU specific feature definitions */
        #include "MPC5744P/include/MPC5744P_features.h"

    #endif

#elif (defined(CPU_S32MTV))

    #define S32MTV_SERIES

    /* Specific core definitions */
    #include "common/s32_core_cm4.h"

    /* Register definitions */
    #include "S32MTV/include/S32MTV.h"
    /* CPU specific feature definitions */
    #include "S32MTV/include/S32MTV_features.h"

#elif defined(CPU_SJA1110)

    #define SJA1110_SERIES

    /* Specific core definitions */
    #include "common/s32_core_cm7.h"

    /* Register definitions */
    #include "SJA1110/include/SJA1110.h"
    /* CPU specific feature definitions */
    #include "SJA1110/include/SJA1110_features.h"

#elif defined(CPU_S32S247)

    #define S32S247_SERIES

    /* Specific core definitions */
    #include "common/s32_core_cm7.h"

    /* Register definitions */
    #include "S32S247/include/S32S247.h"
    /* CPU specific feature definitions */
    #include "S32S247/include/S32S247_features.h"

#else
    #error "No valid CPU defined!"
#endif

#include "devassert.h"

#endif /* DEVICE_REGISTERS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
