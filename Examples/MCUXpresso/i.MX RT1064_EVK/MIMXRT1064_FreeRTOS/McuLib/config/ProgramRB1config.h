#ifndef __ProgramRB1_CONFIG_H
#define __ProgramRB1_CONFIG_H

#ifndef ProgramRB1_CONFIG_REENTRANT
  #define ProgramRB1_CONFIG_REENTRANT   1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef ProgramRB1_CONFIG_BUF_SIZE
  #define ProgramRB1_CONFIG_BUF_SIZE    8   /* number of elements in the buffer */
#endif

#ifndef ProgramRB1_CONFIG_ELEM_SIZE
  #define ProgramRB1_CONFIG_ELEM_SIZE   1   /* size of a single element in bytes */
#endif

#endif /* __ProgramRB1_CONFIG_H */
