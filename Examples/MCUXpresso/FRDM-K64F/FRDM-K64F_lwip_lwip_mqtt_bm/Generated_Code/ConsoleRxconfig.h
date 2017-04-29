#ifndef __ConsoleRx_CONFIG_H
#define __ConsoleRx_CONFIG_H

#ifndef ConsoleRx_CONFIG_REENTRANT
  #define ConsoleRx_CONFIG_REENTRANT    1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef ConsoleRx_CONFIG_BUF_SIZE
  #define ConsoleRx_CONFIG_BUF_SIZE     64   /* number of elements in the buffer */
#endif

#ifndef ConsoleRx_CONFIG_ELEM_SIZE
  #define ConsoleRx_CONFIG_ELEM_SIZE    1   /* size of a single element in bytes */
#endif

#endif /* __ConsoleRx_CONFIG_H */
