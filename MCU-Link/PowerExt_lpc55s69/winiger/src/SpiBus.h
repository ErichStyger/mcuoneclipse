/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 #ifndef __SPI_BUS_H_
 #define __SPI_BUS_H_

 
 #ifdef __cplusplus
 extern "C" {
 #endif

#define SpiBus_CONFIG_USE_MUTEX (0) /* use mutex to protect SPI bus access */
#if !SpiBus_CONFIG_USE_MUTEX
  #warning "SPI bus access is not protected!"
#endif

void SpiBus_Assert(void);
void SpiBus_Deassert(void);

#if SpiBus_CONFIG_USE_MUTEX
  void SpiBus_Lock(void);
  void SpiBus_Unlock(void);
#endif

void SpiBus_Deinit(void);

void SpiBus_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif
  #endif /* __SPI_BUS_H_ */