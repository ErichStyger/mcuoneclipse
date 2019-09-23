/*
 * Copyright (c) 2013-2015 Immo Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its contributors may
 *   be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(_ar_asm_macros_h_)

#if defined(__IASMARM__)
/*
 * IAR assembler
 */

#define _CODE_SECTION(name) section name : CODE(4)
#define _DATA_SECTION(name) section name : DATA(4)
#define _THUMB thumb
#define _IMPORT(name) import name
#define _EXPORT(name) \
public                \
    name
#define _LABEL(name) name
#define _END end
#define _FN_BEGIN(name) CFI Block CFIBlock_##name Using CFICommon0
#define _FN_LABEL(name) _LABEL(name)
#define _FN_DECL(name) CFI Function name
#define _FN_BEGIN_POST
#define _FN_CANT_UNWIND
#define _FN_END(name) CFI EndBlock CFIBlock_##name
#define _FN_SIZE(name)
#define _EQU(name, value) name equ value
#define _ALIGN(n) alignrom n

/* Insert CFI annotation definitions at top of file */
/* clang-format off */
  CFI Names CFINames0
  CFI StackFrame CFA R13 DATA
  CFI Resource R0:32, R1:32, R2:32, R3:32, R4:32, R5:32, R6:32, R7:32
  CFI Resource R8:32, R9:32, R10:32, R11:32, R12:32, R13:32, R14:32
  CFI EndNames CFINames0

  CFI Common CFICommon0 Using CFINames0
  CFI CodeAlign 2
  CFI DataAlign 4
  CFI ReturnAddress R14 CODE
  CFI CFA R13+0
  CFI R0 SameValue
  CFI R1 SameValue
  CFI R2 SameValue
  CFI R3 SameValue
  CFI R4 SameValue
  CFI R5 SameValue
  CFI R6 SameValue
  CFI R7 SameValue
  CFI R8 SameValue
  CFI R9 SameValue
  CFI R10 SameValue
  CFI R11 SameValue
  CFI R12 SameValue
  CFI R14 SameValue
  CFI EndCommon CFICommon0
/* clang-format on */
#elif defined(__CC_ARM)
/*
 * ARM assembler
 */

#define _CODE_SECTION(name) AREA | name |, CODE, READONLY
#define _DATA_SECTION(name) AREA | name |, DATA, READONLY
#define _THUMB THUMB
#define _IMPORT(name) IMPORT name
#define _EXPORT(name) EXPORT name
#define _LABEL(name) name
#define _END END
#define _FN_BEGIN(name) EXPORT name
#define _FN_LABEL(name) name FUNCTION
#define _FN_DECL(name)
#define _FN_BEGIN_POST
#define _FN_CANT_UNWIND FRAME UNWIND OFF
#define _FN_END(name) ENDFUNC
#define _FN_SIZE(name)
#define _EQU(name, value) name EQU value
#define _ALIGN(n) align n

#elif defined(__GNUC__)
/*
 * GNU assembler
 */

#define _CODE_SECTION(name) .section name
#define _DATA_SECTION(name) .section name
#define _THUMB .thumb
#define _IMPORT(name) .extern name
#define _EXPORT(name) .global name
#define _LABEL(name) name:
#define _END .end
#define _FN_BEGIN(name) .thumb_func
#define _FN_LABEL(name) _LABEL(name)
#define _FN_DECL(name) .type name, % function
#define _FN_BEGIN_POST .fnstart
#define _FN_CANT_UNWIND .cantunwind
#define _FN_END(name) .fnend
#define _FN_SIZE(name) .size name, .- name
#define _EQU(name, value) .equ name, value
#define _ALIGN(n) .balign n

.syntax unified

#else
#error "Unsupported assembler"
#endif

#endif // __ar_asm_macros_h__
