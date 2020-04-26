/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "matrixconfig.h"
#include "matrix.h"

#if PL_CONFIG_IS_MASTER

#if MATRIX_CONFIG_IS_8x3
  const MatrixClock_t clockMatrix[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y] = /* information about how the clocks are organized */
  {
    [0][0]={.addr=BOARD_ADDR_00, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][0]={.addr=BOARD_ADDR_00, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][0]={.addr=BOARD_ADDR_00, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][0]={.addr=BOARD_ADDR_00, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][1]={.addr=BOARD_ADDR_01, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][1]={.addr=BOARD_ADDR_01, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][1]={.addr=BOARD_ADDR_01, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][1]={.addr=BOARD_ADDR_01, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][2]={.addr=BOARD_ADDR_02, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][2]={.addr=BOARD_ADDR_02, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][2]={.addr=BOARD_ADDR_02, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][2]={.addr=BOARD_ADDR_02, .nr=0, .board.x=3, .board.y=0, .enabled=true},

    [4][0]={.addr=BOARD_ADDR_05, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][0]={.addr=BOARD_ADDR_05, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][0]={.addr=BOARD_ADDR_05, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][0]={.addr=BOARD_ADDR_05, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][1]={.addr=BOARD_ADDR_06, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][1]={.addr=BOARD_ADDR_06, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][1]={.addr=BOARD_ADDR_06, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][1]={.addr=BOARD_ADDR_06, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][2]={.addr=BOARD_ADDR_07, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][2]={.addr=BOARD_ADDR_07, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][2]={.addr=BOARD_ADDR_07, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][2]={.addr=BOARD_ADDR_07, .nr=0, .board.x=3, .board.y=0, .enabled=true},
  };

  const MATRIX_BoardList_t MATRIX_BoardList[MATRIX_NOF_BOARDS] = {
      {.enabled = true, .addr=BOARD_ADDR_00},
      {.enabled = true, .addr=BOARD_ADDR_01},
      {.enabled = true, .addr=BOARD_ADDR_02},

      {.enabled = true, .addr=BOARD_ADDR_05},
      {.enabled = true, .addr=BOARD_ADDR_06},
      {.enabled = true, .addr=BOARD_ADDR_07},
  };
#elif MATRIX_CONFIG_IS_12x5
  const MatrixClock_t clockMatrix[MATRIX_NOF_CLOCKS_X][MATRIX_NOF_CLOCKS_Y] = /* information about how the clocks are organized */
  {
    [0][0]={.addr=BOARD_ADDR_00, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][0]={.addr=BOARD_ADDR_00, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][0]={.addr=BOARD_ADDR_00, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][0]={.addr=BOARD_ADDR_00, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][1]={.addr=BOARD_ADDR_01, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][1]={.addr=BOARD_ADDR_01, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][1]={.addr=BOARD_ADDR_01, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][1]={.addr=BOARD_ADDR_01, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][2]={.addr=BOARD_ADDR_02, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][2]={.addr=BOARD_ADDR_02, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][2]={.addr=BOARD_ADDR_02, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][2]={.addr=BOARD_ADDR_02, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][3]={.addr=BOARD_ADDR_03, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][3]={.addr=BOARD_ADDR_03, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][3]={.addr=BOARD_ADDR_03, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][3]={.addr=BOARD_ADDR_03, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [0][4]={.addr=BOARD_ADDR_04, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [1][4]={.addr=BOARD_ADDR_04, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [2][4]={.addr=BOARD_ADDR_04, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [3][4]={.addr=BOARD_ADDR_04, .nr=0, .board.x=3, .board.y=0, .enabled=true},

    [4][0]={.addr=BOARD_ADDR_05, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][0]={.addr=BOARD_ADDR_05, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][0]={.addr=BOARD_ADDR_05, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][0]={.addr=BOARD_ADDR_05, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][1]={.addr=BOARD_ADDR_06, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][1]={.addr=BOARD_ADDR_06, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][1]={.addr=BOARD_ADDR_06, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][1]={.addr=BOARD_ADDR_06, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][2]={.addr=BOARD_ADDR_07, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][2]={.addr=BOARD_ADDR_07, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][2]={.addr=BOARD_ADDR_07, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][2]={.addr=BOARD_ADDR_07, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][3]={.addr=BOARD_ADDR_08, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][3]={.addr=BOARD_ADDR_08, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][3]={.addr=BOARD_ADDR_08, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][3]={.addr=BOARD_ADDR_08, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [4][4]={.addr=BOARD_ADDR_09, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [5][4]={.addr=BOARD_ADDR_09, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [6][4]={.addr=BOARD_ADDR_09, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [7][4]={.addr=BOARD_ADDR_09, .nr=0, .board.x=3, .board.y=0, .enabled=true},

    [8][0]={.addr=BOARD_ADDR_10, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [9][0]={.addr=BOARD_ADDR_10, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [10][0]={.addr=BOARD_ADDR_10, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [11][0]={.addr=BOARD_ADDR_10, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [8][1]={.addr=BOARD_ADDR_11, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [9][1]={.addr=BOARD_ADDR_11, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [10][1]={.addr=BOARD_ADDR_11, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [11][1]={.addr=BOARD_ADDR_11, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [8][2]={.addr=BOARD_ADDR_12, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [9][2]={.addr=BOARD_ADDR_12, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [10][2]={.addr=BOARD_ADDR_12, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [11][2]={.addr=BOARD_ADDR_12, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [8][3]={.addr=BOARD_ADDR_13, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [9][3]={.addr=BOARD_ADDR_13, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [10][3]={.addr=BOARD_ADDR_13, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [11][3]={.addr=BOARD_ADDR_13, .nr=0, .board.x=3, .board.y=0, .enabled=true},
    [8][4]={.addr=BOARD_ADDR_14, .nr=3, .board.x=0, .board.y=0, .enabled=true}, [9][4]={.addr=BOARD_ADDR_14, .nr=2, .board.x=1, .board.y=0, .enabled=true}, [10][4]={.addr=BOARD_ADDR_14, .nr=1, .board.x=2, .board.y=0, .enabled=true}, [11][4]={.addr=BOARD_ADDR_14, .nr=0, .board.x=3, .board.y=0, .enabled=true},
  };

  const MATRIX_BoardList_t MATRIX_BoardList[MATRIX_NOF_BOARDS] = {
      {.enabled = true, .addr=BOARD_ADDR_00},
      {.enabled = true, .addr=BOARD_ADDR_01},
      {.enabled = true, .addr=BOARD_ADDR_02},
      {.enabled = true, .addr=BOARD_ADDR_03},
      {.enabled = true, .addr=BOARD_ADDR_04},

      {.enabled = true, .addr=BOARD_ADDR_05},
      {.enabled = true, .addr=BOARD_ADDR_06},
      {.enabled = true, .addr=BOARD_ADDR_07},
      {.enabled = true, .addr=BOARD_ADDR_08},
      {.enabled = true, .addr=BOARD_ADDR_09},

      {.enabled = true, .addr=BOARD_ADDR_10},
      {.enabled = true, .addr=BOARD_ADDR_11},
      {.enabled = true, .addr=BOARD_ADDR_12},
      {.enabled = true, .addr=BOARD_ADDR_13},
      {.enabled = true, .addr=BOARD_ADDR_14},
  };
#endif

#endif /* PL_CONFIG_IS_MASTER */
