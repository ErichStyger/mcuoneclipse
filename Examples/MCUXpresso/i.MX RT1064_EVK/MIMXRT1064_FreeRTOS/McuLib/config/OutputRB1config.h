#ifndef __OutputRB1_CONFIG_H
#define __OutputRB1_CONFIG_H

#ifndef OutputRB1_CONFIG_REENTRANT
  #define OutputRB1_CONFIG_REENTRANT    1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef OutputRB1_CONFIG_BUF_SIZE
  #define OutputRB1_CONFIG_BUF_SIZE     10   /* number of elements in the buffer */
#endif

#ifndef OutputRB1_CONFIG_ELEM_SIZE
  #define OutputRB1_CONFIG_ELEM_SIZE    1   /* size of a single element in bytes */
#endif

#endif /* __OutputRB1_CONFIG_H */
