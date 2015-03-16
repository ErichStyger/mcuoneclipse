/**
 * \file
 * \brief Implements profile function recorder.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * With -finstrument-functions compiler option, each function entry and exit function
 * will call the hooks __cyg_profile_func_enter() and __cyg_profile_func_exit() which
 * can be used to trace function calls.
 * Functions which shall *not* be profiled/recorded need __attribute__((no_instrument_function)).
 */
#include "CygProfile.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "Demo.h"

#define CYG_RNG_BUF_NOF_ELEMS     64
  /*!< Number of elements in the ring buffer which is used to record function calls */
#define CYG_CALL_STACK_NOF_ELEMS  32
  /*!< Number of stack elements (stack depth) for function name tracking/decoding */
#define CYG_THUMB_MASK 0xFFFFFFFE
  /*!< mask out LSB (thumb) bit */

static bool CYG_Enabled = FALSE; /*!< flag which enables/disables tracing */

/*!
 * Element in ring buffer to store the trace information.
 */
typedef struct {
  bool isEnter; /*!< TRUE for __cyg_profile_func_enter(), FALSE for __cyg_profile_func_exit() */
  void *this_fn; /*!< address (with thumb bit) of the (caller) function */
  void *call_site; /*!< return address to the function which called this_fn */
} CYG_RNG_ElementType;

typedef uint8_t CYG_RNG_BufSizeType; /*!< index type for ring buffer */

static CYG_RNG_ElementType CYG_RNG_buffer[CYG_RNG_BUF_NOF_ELEMS]; /*!< ring buffer */
static CYG_RNG_BufSizeType CYG_RNG_inIdx;  /*!< input index */
static CYG_RNG_BufSizeType CYG_RNG_outIdx; /*!< output index */
static CYG_RNG_BufSizeType CYG_RNG_inSize; /*!< size/number of elements in buffer */

#if CYG_FUNC_TRACE_NAMES_ENABLED
static void *callstack[CYG_CALL_STACK_NOF_ELEMS];
static int topOfCallStack = 0; /* points to next free element */

static __attribute__((no_instrument_function))
const char *getFuncName(void *addr) {
  int main(void);
  void PE_low_level_init(void);

  if (addr==main) {
    return "main";
  } else if (addr==PE_low_level_init) {
    return "PE_low_level_init";
  }
  return "";
}

static CYG_GetFuncNameFct GetFuncNames[] = {
  getFuncName,
  DEMO_getFuncName
};

static __attribute__((no_instrument_function))
void CYG_Push(void *context) {
  callstack[topOfCallStack] = context;
  if (topOfCallStack<CYG_CALL_STACK_NOF_ELEMS-1) {
    topOfCallStack++;
  }
}

static __attribute__((no_instrument_function))
void *CYG_Pop(void) {
  if (topOfCallStack>0) {
    topOfCallStack--;
    return callstack[topOfCallStack];
  }
  return NULL; /* error case */
}

static __attribute__((no_instrument_function))
void *CYG_GetTop(void) {
  if (topOfCallStack>0) {
    return callstack[topOfCallStack-1];
  }
  return NULL; /* error case */
}

static __attribute__((no_instrument_function))
const char *CYG_getFuncName(void *addr) {
  CYG_GetFuncNameFct fct;
  const char* name;
  int i;
  int main(void);

  if (addr==main) {
    return "main";
  }
  for(i=0;i<sizeof(GetFuncNames)/sizeof(GetFuncNames[0]);i++) {
    name = GetFuncNames[i](addr);
    if (*name!='\0') {
      return name;
    }
  }
  return "";
}
#endif /* CYG_FUNC_TRACE_NAMES_ENABLED */

__attribute__((no_instrument_function))
uint8_t CYG_RNG_Put(CYG_RNG_ElementType *elem) {
  uint8_t res = ERR_OK;
  CS1_CriticalVariable();

  CS1_EnterCritical();
  if (CYG_RNG_inSize==CYG_RNG_BUF_NOF_ELEMS) {
    res = ERR_TXFULL;
  } else {
    CYG_RNG_buffer[CYG_RNG_inIdx] = *elem;
    CYG_RNG_inIdx++;
    if (CYG_RNG_inIdx==CYG_RNG_BUF_NOF_ELEMS) {
      CYG_RNG_inIdx = 0;
    }
    CYG_RNG_inSize++;
  }
  CS1_ExitCritical();
  return res;
}

__attribute__((no_instrument_function))
uint8_t CYG_RNG_Get(CYG_RNG_ElementType *elemP) {
  uint8_t res = ERR_OK;
  CS1_CriticalVariable();

  CS1_EnterCritical();
  if (CYG_RNG_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    *elemP = CYG_RNG_buffer[CYG_RNG_outIdx];
    CYG_RNG_inSize--;
    CYG_RNG_outIdx++;
    if (CYG_RNG_outIdx==CYG_RNG_BUF_NOF_ELEMS) {
      CYG_RNG_outIdx = 0;
    }
  }
  CS1_ExitCritical();
  return res;
}

static __attribute__((no_instrument_function))
void CYG_Store(bool isEnter, void *this_fn, void *call_site) {
  /* this_fn is the address (with thumb bit) of the (caller) function */
  /* call_site: return address to the function which called this_fn */
  CYG_RNG_ElementType elem;

  elem.isEnter = isEnter;
  elem.call_site = call_site;
  elem.this_fn = this_fn;
  (void)CYG_RNG_Put(&elem);
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
  /* this_fn is the address (with thumb bit) of the (caller) function */
  /* call_site: return address to the function which called this_fn */
  if (CYG_Enabled) {
    CYG_Store(TRUE, call_site, this_fn);
  }
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  if (CYG_Enabled) {
    CYG_Store(FALSE, call_site, this_fn);
  }
}

__attribute__((no_instrument_function))
void CYG_PrintCallTrace(void) {
  CYG_RNG_BufSizeType nof, i;
  CLS1_ConstStdIOTypePtr stdio;
  uint8_t buf[64];
  CYG_RNG_ElementType elem;
  uint8_t res;
  int level, s;
#if CYG_FUNC_TRACE_NAMES_ENABLED
  void *caller;
  int offset;
  const char *name;
#endif

  CYG_Enabled = FALSE;
  stdio = CLS1_GetStdio();
  CLS1_SendStr("Function Trace:\r\n", stdio->stdOut);
  nof = CYG_RNG_inSize;
  level = 0;
  for(i=0;i<nof;i++) {
    buf[0] = '\0';
    res = CYG_RNG_Get(&elem);
    if (res==ERR_OK) {
      if (elem.isEnter) {
        for(s=0;s<level;s++) {
          UTIL1_chcat(buf, sizeof(buf), ' ');
        }
        level++;
        UTIL1_strcat(buf, sizeof(buf), "{ ");
        UTIL1_strcatNum32Hex(buf, sizeof(buf), (uint32_t)(elem.this_fn)&CYG_THUMB_MASK);
        UTIL1_strcat(buf, sizeof(buf), "->");
        UTIL1_strcatNum32Hex(buf, sizeof(buf), (uint32_t)(elem.call_site)&CYG_THUMB_MASK);
#if CYG_FUNC_TRACE_NAMES_ENABLED
        UTIL1_chcat(buf, sizeof(buf), ' ');
        caller = CYG_GetTop();
        if (caller!=NULL && caller<elem.this_fn) {
          offset = elem.this_fn-caller;
          UTIL1_chcat(buf, sizeof(buf), ' ');
          name = CYG_getFuncName(caller);
          UTIL1_strcat(buf, sizeof(buf), name);
          UTIL1_strcat(buf, sizeof(buf), ":0x");
          UTIL1_strcatNum16Hex(buf, sizeof(buf), offset);
        } else {
          name = CYG_getFuncName(elem.this_fn);
          if (*name=='\0') {
            name = "???";
          }
          UTIL1_strcat(buf, sizeof(buf), name);
        }
        UTIL1_strcat(buf, sizeof(buf), "->");
        UTIL1_strcat(buf, sizeof(buf), CYG_getFuncName(elem.call_site));
        CYG_Push(elem.call_site);
#endif
      } else {
        level--;
        if (level<0) { /* just in case: check proper level */
          UTIL1_strcat(buf, sizeof(buf), "ERROR level ");
          level = 0;
        }
        for(s=0;s<level;s++) {
          UTIL1_chcat(buf, sizeof(buf), ' ');
        }
        UTIL1_strcat(buf, sizeof(buf), "} ");
        UTIL1_strcatNum32Hex(buf, sizeof(buf), (uint32_t)(elem.this_fn)&CYG_THUMB_MASK);
        UTIL1_strcat(buf, sizeof(buf), "<-");
        UTIL1_strcatNum32Hex(buf, sizeof(buf), (uint32_t)(elem.call_site)&CYG_THUMB_MASK);
#if CYG_FUNC_TRACE_NAMES_ENABLED
        UTIL1_chcat(buf, sizeof(buf), ' ');
        (void)CYG_Pop();
        caller = CYG_GetTop();
        if (caller!=NULL && caller<elem.this_fn) {
          offset = elem.this_fn-caller;
          UTIL1_chcat(buf, sizeof(buf), ' ');
          name = CYG_getFuncName(caller);
          UTIL1_strcat(buf, sizeof(buf), name);
          UTIL1_strcat(buf, sizeof(buf), ":0x");
          UTIL1_strcatNum16Hex(buf, sizeof(buf), offset);
        } else {
          name = CYG_getFuncName(elem.this_fn);
          if (*name=='\0') {
            name = "???";
          }
          UTIL1_strcat(buf, sizeof(buf), name);
        }
        UTIL1_strcat(buf, sizeof(buf), "<-");
        UTIL1_strcat(buf, sizeof(buf), CYG_getFuncName(elem.call_site));
#endif
      }
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      CLS1_SendStr(buf, stdio->stdOut);
    } else {
      CLS1_SendStr("ERROR getting element!\r\n", stdio->stdErr);
    }
  }
  CLS1_SendStr("Function Trace: done!\r\n", stdio->stdOut);
}

__attribute__((no_instrument_function))
void CYG_Init(void) {
  int i;

  CYG_RNG_inIdx = 0;
  CYG_RNG_outIdx = 0;
  CYG_RNG_inSize = 0;
  CYG_Enabled = TRUE;
#if CYG_FUNC_TRACE_NAMES_ENABLED
  topOfCallStack = 0;
#endif
}

__attribute__((no_instrument_function))
void CYG_Deinit(void) {
  /* nothing needed */
}

