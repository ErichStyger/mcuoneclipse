/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if (__ARM_FEATURE_CMSE & 1) == 0
#error "Need ARMv8-M security extensions"
#elif (__ARM_FEATURE_CMSE & 2) == 0
#error "Compile with --cmse"
#endif

#include "stdint.h"
#include "arm_cmse.h"
#include "veneer_table.h"
#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_STRING_LENGTH         0x400
typedef int (*callbackptr_NS)(char const * s1, char const * s2) __attribute__((cmse_nonsecure_call));

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* strnlen function implementation for arm compiler */
#if defined(__arm__)
size_t strnlen(const char* s, size_t maxLength)
{
    size_t length = 0;
    while ((length <= maxLength) && (*s))
    {
      s++;
      length++;
    }
    return length;
}
#endif

__attribute__ ((cmse_nonsecure_entry)) void DbgConsole_Printf_NSE(char const *s) 
{
    size_t  string_length;
    /* Access to non-secure memory from secure world has to be properly validated */
    /* Check whether string is properly terminated */
    string_length = strnlen(s, MAX_STRING_LENGTH);
    if ((string_length == MAX_STRING_LENGTH) && (s[string_length] != '\0'))
    {
        PRINTF("String too long or invalid string termination!\r\n");
         abort();
    }

    /* Check whether string is located in non-secure memory */
    if (cmse_check_address_range((void *)s, string_length, CMSE_NONSECURE | CMSE_MPU_READ) == NULL)
    {
        PRINTF("String is not located in normal world!\r\n");
        abort();
    }
    PRINTF(s);
}

/* Non-secure callable (entry) function, calling a non-secure callback function */
__attribute__((cmse_nonsecure_entry)) uint32_t StringCompare_NSE(volatile callbackptr callback, char const *s1, char const *s2)
{
    callbackptr_NS callback_NS;
    size_t  string_length;
    int result;
 
    /* Input parameters check */
    /* Check whether function pointer is located in non-secure memory */
    callback_NS = (callbackptr_NS)cmse_nsfptr_create(callback);
    if (cmse_check_pointed_object((int *)callback_NS, CMSE_NONSECURE) == NULL)
    {
        PRINTF("The callback is not located in normal world!\r\n");
        abort();
    }
    /* Check whether string is properly terminated */
    string_length = strnlen(s1, MAX_STRING_LENGTH);
    if ((string_length == MAX_STRING_LENGTH) && (s1[string_length] != '\0'))
    {
        PRINTF("First string too long or invalid string termination!\r\n");
         abort();
    }
    /* Check whether string is properly terminated */
    string_length = strnlen(s2, MAX_STRING_LENGTH);
    if ((string_length == MAX_STRING_LENGTH) && (s2[string_length] != '\0'))
    {
        PRINTF("Second string too long or invalid string termination!\r\n");
         abort();
    }
    PRINTF("Comparing two string as a callback to normal world\r\n");
    PRINTF("String 1: ");
    PRINTF(s1);
    PRINTF("String 2: ");
    PRINTF(s2);
    result = callback_NS(s1, s2);
    return result;
}

