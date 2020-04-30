/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "demos.h"
#include "McuRTOS.h"
#include "stepper.h"
#include "matrix.h"
#include "McuUtility.h"
#if PL_CONFIG_USE_STEPPER_EMUL
  #include "NeoPixel.h"
#endif

#if PL_CONFIG_USE_STEPPER_EMUL
static void MATRIX_LedDemo0(void) {
  NEO_ClearAllPixel();

  NEO_SetAllPixelColor(0x020000); /* red */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x000200); /* green */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x000002); /* blue */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x020202); /* white */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

#if PL_CONFIG_USE_STEPPER_EMUL
static NEO_PixelColor Rainbow(int32_t numOfSteps, int32_t step) {
  float r = 0.0;
  float g = 0.0;
  float b = 0.0;
  float h = (double)step / numOfSteps;
  int i = (int32_t)(h * 6);
  float f = h * 6.0 - i;
  float q = 1 - f;

  switch (i % 6)  {
      case 0:
          r = 1;
          g = f;
          b = 0;
          break;
      case 1:
          r = q;
          g = 1;
          b = 0;
          break;
      case 2:
          r = 0;
          g = 1;
          b = f;
          break;
      case 3:
          r = 0;
          g = q;
          b = 1;
          break;
      case 4:
          r = f;
          g = 0;
          b = 1;
          break;
      case 5:
          r = 1;
          g = 0;
          b = q;
          break;
  }
  r *= 255;
  g *= 255;
  b *= 255;
  return ((((int)r)<<16)|(((int)g)<<8))+(int)b;
}
static void MATRIX_LedDemo1(void) {
  uint8_t rowStartStep[NEO_NOF_LANES]; /* rainbow color starting values */
  NEO_PixelColor color;
  NEO_PixelIdxT lane, pos;
  uint8_t brightness = 2;
  int val = 0;

  for(int i=0; i<NEO_NOF_LANES;i++) {
    rowStartStep[i] = val;
    val+=20;
    if(val>=0xff) {
      val = 0;
    }
  }

  NEO_ClearAllPixel();
  for (int i=0; i<200; i++) {
    for(lane=0; lane<NEO_NOF_LANES; lane++) {
      color = Rainbow(256, rowStartStep[lane]);
      color = NEO_BrightnessPercentColor(color, brightness);
      rowStartStep[lane]++;
      for(pos=0; pos<NEO_NOF_LEDS_IN_LANE; pos++) {
        NEO_SetPixelColor(lane, pos, color);
      }
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

/* ------------------------------------------------- */
typedef struct {
  uint8_t r, g, b;
  int posX, posY;
  int dirX, dirY;
} PongBall_t;

typedef struct {
  uint8_t r, g, b;
  int posX, posY;
  int points;
} PongPlayer_t;

static void DrawBall(PongBall_t *b) {
  MATRIX_SetRingColor(b->posX, b->posY, b->r, b->g, b->b);
}

static void ClearBall(PongBall_t *b) {
  MATRIX_SetRingColor(b->posX, b->posY, 0, 0, 0);
}

static void DrawPlayer(PongPlayer_t *player) {
  MATRIX_SetRingColor(player->posX, player->posY, player->r, player->g, player->b);
}

static void ClearPlayer(PongPlayer_t *player) {
  MATRIX_SetRingColor(player->posX, player->posY, 0, 0, 0);
}

static void MovePlayer(PongPlayer_t *player, int deltaY) {
  ClearPlayer(player);
  player->posY += deltaY;
  if (player->posY<0) {
    player->posY = 0;
  } else if (player->posY>MATRIX_NOF_CLOCKS_Y-1) {
    player->posY =MATRIX_NOF_CLOCKS_Y-1;
  }
  DrawPlayer(player);
}

static void PongGameLost(PongPlayer_t *player, PongBall_t *ball) {
  /* mark player in red */
  player->r = 0x50;
  player->g = 0;
  player->b = 0;
  DrawBall(ball);
  DrawPlayer(player);
  NEO_TransferPixels();
  vTaskDelay(pdMS_TO_TICKS(100));
  for(int i=0; i<10; i++) {
    ClearBall(ball);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(100));
    DrawBall(ball);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void ScorePoint(PongPlayer_t *player) {
  player->points++;
  /* blink it */
  player->r <<= 5;
  player->g <<= 5;
  player->b <<= 5;
  DrawPlayer(player);
  NEO_TransferPixels();
  vTaskDelay(pdMS_TO_TICKS(100));
  player->r >>= 5;
  player->g >>= 5;
  player->b >>= 5;
  DrawPlayer(player);
  NEO_TransferPixels();
  vTaskDelay(pdMS_TO_TICKS(100));
}

static bool MoveBall(PongBall_t *b, PongPlayer_t *left, PongPlayer_t *right) {
  bool gameOver = false;

  ClearBall(b);
  b->posX += b->dirX;
  b->posY += b->dirY;
  if (b->posY < 0) {
    b->posY = 1;
    b->dirY = -b->dirY;
  } else if (b->posY >= MATRIX_NOF_CLOCKS_Y) {
    b->posY = MATRIX_NOF_CLOCKS_Y-2;
    b->dirY = -b->dirY;
  }
  /* check collision with player */
  if (b->posX == left->posX) {
    if (b->posY != left->posY) {
      /* player left lost */
      PongGameLost(left, b);
      gameOver = true;
    } else {
      b->dirX = -b->dirX;
      b->dirY = -b->dirY;
      b->posX += b->dirX;
      b->posY += b->dirY;
      ScorePoint(left);
    }
  }
  if (b->posX == right->posX) {
    if (b->posY != right->posY) {
      /* player right lost */
      PongGameLost(right, b);
      gameOver = true;
    } else {
      b->dirX = -b->dirX;
      b->dirY = -b->dirY;
      b->posX += b->dirX;
      b->posY += b->dirY;
      ScorePoint(right);
    }
  }
  DrawBall(b);
  return gameOver;
}

static void MATRIX_LedPong(void) {
  PongBall_t ball;
  PongPlayer_t playerL, playerR;
  bool gameOver;

  /* ball: */
  ball.r = 0x4;
  ball.g = 0x4;
  ball.b = 0x4;
  ball.posX = 1;
  ball.posY = 1;
  ball.dirX = 1;
  ball.dirY = 1;
  /* player left: */
  playerL.r = 0;
  playerL.g = 0x4;
  playerL.b = 0;
  playerL.points = 0;
  playerL.posX = 0;
  playerL.posY = 0;
  /* player right: */
  playerR.r = 0;
  playerR.g = 0;
  playerR.b = 0x4;
  playerR.points = 0;
  playerR.posX = MATRIX_NOF_CLOCKS_X-1;
  playerR.posY = MATRIX_NOF_CLOCKS_Y/2;

  NEO_ClearAllPixel();
  DrawPlayer(&playerL);
  DrawPlayer(&playerR);
  DrawBall(&ball);
  NEO_TransferPixels();
  vTaskDelay(pdMS_TO_TICKS(1000));

  for(int i=0; i<60; i++) {
    gameOver = MoveBall(&ball, &playerL, &playerR);
    DrawPlayer(&playerL);
    DrawPlayer(&playerR);
    NEO_TransferPixels();
    if (gameOver) {
      break;
    }
#if PL_MATRIX_CONFIG_IS_12x5
    if (i==1) {
      MovePlayer(&playerL, 1);
    } else if (i==3) {
      MovePlayer(&playerL, 1);
    } else if (i==7) {
      MovePlayer(&playerR, 1);
    } else if (i==9) {
      MovePlayer(&playerL, -1);
    } else if (i==15) {
      MovePlayer(&playerL, 1);
      MovePlayer(&playerR, -1);
    } else if (i==16) {
      MovePlayer(&playerL, -1);
    } else if (i==17) {
      MovePlayer(&playerL, -1);
    } else if (i==26) {
      MovePlayer(&playerR, -1);
    } else if (i==27) {
      MovePlayer(&playerR, 1);
    }
#elif PL_MATRIX_CONFIG_IS_8x3
    if (i==1) {
      MovePlayer(&playerL, 1);
    } else if (i==3) {
      MovePlayer(&playerR, 1);
    } else if (i==9) {
      MovePlayer(&playerL, -1);
    } else if (i==15) {
      MovePlayer(&playerL, -1);
      MovePlayer(&playerR, 1);
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"demo", (unsigned char*)"Group of demo commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
#if PL_CONFIG_USE_STEPPER_EMUL
  McuShell_SendHelpStr((unsigned char*)"  led 0", (unsigned char*)"LED color demo\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led 1", (unsigned char*)"LED rainbow demo\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  pong", (unsigned char*)"pong demo\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t DEMO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "demo help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "demo status")==0)) {
    *handled = true;
    return PrintStatus(io);
#if PL_CONFIG_USE_STEPPER_EMUL
  } else if (McuUtility_strcmp((char*)cmd, "demo led 0")==0) {
    *handled = TRUE;
    if (MATRIX_GetUpdateRotorLed()) {
      McuShell_SendStr((unsigned char*)"matrix led rotor is enabled, disable it first.\n", io->stdErr);
      return ERR_FAILED;
    }
    MATRIX_LedDemo0();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "demo led 1")==0) {
    *handled = TRUE;
    if (MATRIX_GetUpdateRotorLed()) {
      McuShell_SendStr((unsigned char*)"matrix led rotor is enabled, disable it first.\n", io->stdErr);
      return ERR_FAILED;
    }
    MATRIX_LedDemo1();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "demo pong")==0) {
    *handled = TRUE;
    if (MATRIX_GetUpdateRotorLed()) {
      McuShell_SendStr((unsigned char*)"matrix led rotor is enabled, disable it first.\n", io->stdErr);
      return ERR_FAILED;
    }
    MATRIX_LedPong();
    return ERR_OK;
#endif
  }
  return ERR_OK;
}
#endif
