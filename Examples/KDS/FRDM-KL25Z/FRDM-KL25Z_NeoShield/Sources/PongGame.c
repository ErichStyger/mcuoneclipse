/*
 * PongGame.c
 *
 *  Created on: 28.12.2014
 *      Author: tastyger
 */
#include "Platform.h"
#if PL_HAS_PONG
#include "PongGame.h"
#include "FRTOS1.h"
#include "NeoPixel.h"

#define PONG_NOF_PIXELS 144
#define PONG_NOF_BALLS   4
#define PONG_DEFAULT_BACKGROUND_RGB 0x010101

typedef struct {
  NEO_PixelIdxT pos; /* current pos */
  uint32_t color; /* current color at pos */
  bool forward; /* forward or backward moving */
  TickType_t drawTickCounter; /* time the ball was drawn */
  uint16_t speedMs; /* time to move from one position to another */
} PONG_BallT;

typedef enum {
  PONG_GAME_STATE_INIT,
  PONG_GAME_STATE_WAIT_FOR_START,
  PONG_GAME_STATE_RUNNING,
  PONG_GAME_STATE_PAUSE,
} PONG_GameState;

static PONG_GameState PONG_gameState;
static PONG_BallT PONG_Balls[PONG_NOF_BALLS];

static bool ButtonRightPressed(void) {
  return TRUE;
}

static bool ButtonLeftPressed(void) {
  return TRUE;
}

static void PONG_InitBall(PONG_BallT *ball) {
  ball->pos = 0;
  ball->forward = TRUE;
  ball->color = 0;
  ball->speedMs = 0;
  ball->drawTickCounter = 0;
}

static void PONG_DrawBall(PONG_BallT *ball) {
  (void)NEO_SetPixelColor(ball->pos, ball->color);
  ball->drawTickCounter = FRTOS1_xTaskGetTickCount();
}

static void PONG_RemoveBall(PONG_BallT *ball) {
  uint32_t color;
  int i;

  color = PONG_DEFAULT_BACKGROUND_RGB; /* default */
  for(i=0;i<PONG_NOF_BALLS;i++) {
    if (&PONG_Balls[i]!=ball && PONG_Balls[i].pos==ball->pos) { /* other ball on our position */
      color = PONG_Balls[i].color; /* use other balls color */
    }
  }
  (void)NEO_SetPixelColor(ball->pos, color);
}

static void PONG_PlayerLooses(bool isLeft) {
}

static void PONG_InitGame(void) {
  int i;

  NEO_ClearAllPixel();
#if 1
  /* background */
  for(i=0;i<PONG_NOF_PIXELS;i++) {
    NEO_SetPixelColor(i, PONG_DEFAULT_BACKGROUND_RGB);
  }
#endif
  NEO_TransferPixels();
  for(i=0;i<PONG_NOF_BALLS;i++) {
    PONG_InitBall(&PONG_Balls[i]);
  }
}

static void PONG_StartGame(void) {
  int i;

#if PONG_NOF_BALLS>=1
  PONG_Balls[0].pos = 0; /* leftmost */
  PONG_Balls[0].color = 0x00ff00; /* green */
  PONG_Balls[0].forward = TRUE; /* left to right */
  PONG_Balls[0].speedMs = 250; /* initial speed */
#endif
#if PONG_NOF_BALLS>=2
  PONG_Balls[1].pos = PONG_NOF_PIXELS-1; /* rightmost */
  PONG_Balls[1].color = 0x0000ff; /* blue */
  PONG_Balls[1].forward = FALSE; /* right to left */
  PONG_Balls[1].speedMs = 150; /* initial speed */
#endif
#if PONG_NOF_BALLS>=3
  PONG_Balls[2].pos = PONG_NOF_PIXELS-1; /* rightmost */
  PONG_Balls[2].color = 0x500050;
  PONG_Balls[2].forward = FALSE; /* right to left */
  PONG_Balls[2].speedMs = 50; /* initial speed */
#endif
#if PONG_NOF_BALLS>=4
  PONG_Balls[3].pos = 0; /* rightmost */
  PONG_Balls[3].color = 0x302050;
  PONG_Balls[3].forward = TRUE; /* right to left */
  PONG_Balls[3].speedMs = 5; /* initial speed */
#endif
  for(i=0;i<PONG_NOF_BALLS;i++) {
    PONG_DrawBall(&PONG_Balls[i]);
  }
  NEO_TransferPixels();
}

static void PONG_UpdateBall(PONG_BallT *ball) {
  PONG_RemoveBall(ball); /* clear current ball */
  for(;;) { /* breaks */
    if (ball->forward) {
      if (ball->pos<PONG_NOF_PIXELS-1) {
        ball->pos++;
        PONG_DrawBall(ball);
        break;
      } else if (ButtonRightPressed()) { /* play back */
        //ball->color = 0x0000ff; /* blue */
        ball->forward = FALSE;
        continue;
      } else {
        PONG_PlayerLooses(FALSE); /* right player looses */
        break;
      }
    } else { /* backward */
      if (ball->pos>0) {
        ball->pos--;
        PONG_DrawBall(ball);
        break;
      } else if (ButtonLeftPressed()) { /* play back */
        //ball->color = 0x00ff00; /* green */
        ball->forward = TRUE;
        continue;
      } else {
        PONG_PlayerLooses(TRUE); /* left player looses */
        break;
      }
    }
  } /* for */
}

static void PONG_UpdateBalls(void) {
  TickType_t currTickCount;
  bool transferPixels = FALSE;
  int i;

  currTickCount = FRTOS1_xTaskGetTickCount();
  for(i=0;i<PONG_NOF_BALLS;i++) {
    if (currTickCount>=PONG_Balls[i].drawTickCounter+PONG_Balls[i].speedMs/portTICK_RATE_MS) {
      PONG_UpdateBall(&PONG_Balls[i]);
      transferPixels = TRUE;
    }
  }
  if (transferPixels) {
    NEO_TransferPixels();
  }
}

static void PONG_RunMachine(void) {
  switch(PONG_gameState) {
    case PONG_GAME_STATE_INIT:
      PONG_InitGame();
      PONG_gameState = PONG_GAME_STATE_WAIT_FOR_START;
      break;
    case PONG_GAME_STATE_WAIT_FOR_START:
      PONG_StartGame();
      PONG_gameState = PONG_GAME_STATE_RUNNING;
      break;
    case PONG_GAME_STATE_RUNNING:
      PONG_UpdateBalls();
      break;

    case PONG_GAME_STATE_PAUSE:
      /* stay in current state */
      break;

    default:
      break;
  }
}

static portTASK_FUNCTION(PongTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  PONG_gameState = PONG_GAME_STATE_INIT;
  for(;;) {
    PONG_RunMachine();
    FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
  }
}

void PONG_Init(void) {
  if (FRTOS1_xTaskCreate(
        PongTask,  /* pointer to the task */
        "Pong", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_HAS_PONG */
