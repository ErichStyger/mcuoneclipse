/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DMAMUX_MACROS_H_
#define DMAMUX_MACROS_H_

/* DMAMUX - Register accessors */
#define DMAMUX_CHCFG_REG(base,index)             ((base)->CHCFG[index])

/* DMAMUX - Register instance definitions */
/* DMAMUX */
#define DMAMUX_CHCFG0                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,0)
#define DMAMUX_CHCFG1                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,1)
#define DMAMUX_CHCFG2                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,2)
#define DMAMUX_CHCFG3                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,3)
#define DMAMUX_CHCFG4                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,4)
#define DMAMUX_CHCFG5                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,5)
#define DMAMUX_CHCFG6                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,6)
#define DMAMUX_CHCFG7                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,7)
#define DMAMUX_CHCFG8                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,8)
#define DMAMUX_CHCFG9                            DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,9)
#define DMAMUX_CHCFG10                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,10)
#define DMAMUX_CHCFG11                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,11)
#define DMAMUX_CHCFG12                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,12)
#define DMAMUX_CHCFG13                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,13)
#define DMAMUX_CHCFG14                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,14)
#define DMAMUX_CHCFG15                           DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,15)


#define DMAMUX_PDD_EnableChannel(PeripheralBase, Channel, State) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_ENBL_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << DMAMUX_CHCFG_ENBL_SHIFT))) \
  )
#define DMAMUX_PDD_EnableTrigger(PeripheralBase, Channel, State) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_TRIG_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << DMAMUX_CHCFG_TRIG_SHIFT))) \
  )
#define DMAMUX_PDD_SetChannelSource(PeripheralBase, Channel, ChannelSource) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_SOURCE_MASK)))) | ( \
      (uint8_t)(ChannelSource))) \
  )
#define DMA_PDD_EnablePeripheralRequest(PeripheralBase, Channel, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      DMA_CERQ_REG(PeripheralBase) = \
       (uint8_t)(Channel)) : ( \
      DMA_SERQ_REG(PeripheralBase) = \
       (uint8_t)(Channel)) \
  )


#endif /* DMAMUX_MACROS_H_ */
