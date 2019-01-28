#ifndef __TimeRB1_CONFIG_H
#define __TimeRB1_CONFIG_H

#ifndef TimeRB1_CONFIG_REENTRANT
  #define TimeRB1_CONFIG_REENTRANT      1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef TimeRB1_CONFIG_BUF_SIZE
  #define TimeRB1_CONFIG_BUF_SIZE       4   /* number of elements in the buffer */
#endif

#ifndef TimeRB1_CONFIG_ELEM_SIZE
  #define TimeRB1_CONFIG_ELEM_SIZE      2   /* size of a single element in bytes */
#endif

#endif /* __TimeRB1_CONFIG_H */
