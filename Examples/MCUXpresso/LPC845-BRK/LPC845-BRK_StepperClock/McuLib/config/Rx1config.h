#ifndef __Rx1_CONFIG_H
#define __Rx1_CONFIG_H

#ifndef Rx1_CONFIG_REENTRANT
  #define Rx1_CONFIG_REENTRANT          1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef Rx1_CONFIG_BUF_SIZE
  #define Rx1_CONFIG_BUF_SIZE           64   /* number of elements in the buffer */
#endif

#ifndef Rx1_CONFIG_ELEM_SIZE
  #define Rx1_CONFIG_ELEM_SIZE          1   /* size of a single element in bytes */
#endif

#endif /* __Rx1_CONFIG_H */
