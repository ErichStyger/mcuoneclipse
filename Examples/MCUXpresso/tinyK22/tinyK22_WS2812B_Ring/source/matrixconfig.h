/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MATRIXCONFIG_H_
#define MATRIXCONFIG_H_

#include "platform.h"
#include <stdbool.h>
#include <stdint.h>

#if PL_CONFIG_IS_MASTER

/* clock organisation: only one can be enabled! */
#define MATRIX_CONFIG_IS_8x3    (1) /* original 8x3 matrix configuration with 24 clocks */
#define MATRIX_CONFIG_IS_12x5   (0) /* new 8x3 matrix configuration with 60 clocks */

/* configuration for master: */
#if MATRIX_CONFIG_IS_8x3
  #define MATRIX_NOF_BOARDS         (6)   /* total number of boards in matrix */
  #define MATRIX_NOF_CLOCKS_X       (8)   /* number of clocks in x (horizontal) direction */
  #define MATRIX_NOF_CLOCKS_Y       (3)   /* number of clocks in y (vertical) direction */
  #define MATRIX_NOF_CLOCKS_Z       (2)   /* number of clocks in z direction */
#elif MATRIX_CONFIG_IS_12x5
  #define MATRIX_NOF_BOARDS         (15)  /* total number of boards in matrix */
  #define MATRIX_NOF_CLOCKS_X       (12)  /* number of clocks in x (horizontal) direction */
  #define MATRIX_NOF_CLOCKS_Y       (5)   /* number of clocks in y (vertical) direction */
  #define MATRIX_NOF_CLOCKS_Z       (2)   /* number of clocks in z direction */
#endif

typedef enum {
#if MATRIX_CONFIG_IS_8x3
  BOARD_ADDR_00=0x20, /* first board top board */
  BOARD_ADDR_01=0x21,
  BOARD_ADDR_02=0x22,

  BOARD_ADDR_05=0x25, /* second row, first board */
  BOARD_ADDR_06=0x26,
  BOARD_ADDR_07=0x27,
#elif MATRIX_CONFIG_IS_12x5
  BOARD_ADDR_00=0x20, /* first board top board */
  BOARD_ADDR_01=0x21,
  BOARD_ADDR_02=0x22,
  BOARD_ADDR_03=0x23,
  BOARD_ADDR_04=0x24,

  BOARD_ADDR_05=0x25, /* second row, first board */
  BOARD_ADDR_06=0x26,
  BOARD_ADDR_07=0x27,
  BOARD_ADDR_08=0x28,
  BOARD_ADDR_09=0x15,

  BOARD_ADDR_10=0x10, /* third row, first row */
  BOARD_ADDR_11=0x11,
  BOARD_ADDR_12=0x12,
  BOARD_ADDR_13=0x13,
  BOARD_ADDR_14=0x14,
#endif
} MATRIX_BOARD_ADDR_e;

typedef struct {
  uint8_t addr; /* RS-485 address */
  uint8_t nr;   /* clock number, 0..3 */
  struct {
    uint8_t x, y; /* coordinates on the board */
  } board;
  bool enabled; /* if enabled or not */
} MatrixClock_t;

extern const MatrixClock_t clockMatrix[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y];

typedef struct {
  bool enabled;
  uint8_t addr;
} MATRIX_BoardList_t;

extern const MATRIX_BoardList_t MATRIX_BoardList[MATRIX_NOF_BOARDS];

#endif /* PL_CONFIG_IS_MASTER */

#endif /* MATRIXCONFIG_H_ */
