#ifndef __RNG1_CONFIG_H
#define __RNG1_CONFIG_H

#ifndef RNG1_CONFIG_REENTRANT
  #define RNG1_CONFIG_REENTRANT         1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef RNG1_CONFIG_BUF_SIZE
  #define RNG1_CONFIG_BUF_SIZE          64   /* number of elements in the buffer */
#endif

#ifndef RNG1_CONFIG_ELEM_SIZE
  #define RNG1_CONFIG_ELEM_SIZE         2   /* size of a single element in bytes */
#endif

#endif /* __RNG1_CONFIG_H */
