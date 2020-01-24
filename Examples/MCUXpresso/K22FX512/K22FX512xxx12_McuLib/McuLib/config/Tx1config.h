#ifndef __Tx1_CONFIG_H
#define __Tx1_CONFIG_H

#ifndef Tx1_CONFIG_REENTRANT
  #define Tx1_CONFIG_REENTRANT          1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef Tx1_CONFIG_BUF_SIZE
  #define Tx1_CONFIG_BUF_SIZE           64   /* number of elements in the buffer */
#endif

#ifndef Tx1_CONFIG_ELEM_SIZE
  #define Tx1_CONFIG_ELEM_SIZE          1   /* size of a single element in bytes */
#endif

#endif /* __Tx1_CONFIG_H */
