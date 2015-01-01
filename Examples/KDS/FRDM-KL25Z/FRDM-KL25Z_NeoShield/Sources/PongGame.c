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
#if PL_HAS_MUSIC
  #include "Music.h"
  #include "VS1.h"
#endif
#if PL_HAS_MIDI
  #include "MidiMusic.h"
#endif
#if PL_HAS_KEYS
  #include "EVNT1.h"
  #include "Keys.h"
  #include "KEY1.h"
#endif

#define PONG_NOF_PIXELS  20
#define PONG_NOF_BALLS   1
#define PONG_DEFAULT_BACKGROUND_RGB 0x010101

typedef struct {
  NEO_PixelIdxT pos; /* current pos */
  uint32_t color; /* current color at pos */
  bool forward; /* forward or backward moving */
  TickType_t drawTickCounter; /* time the ball was drawn */
  uint16_t speedMs; /* time to move from one position to another */
} PONG_BallT;

typedef struct {
  NEO_PixelIdxT pos; /* current pos */
  uint32_t color; /* current color at pos */
  bool isOn; /* limiter is on */
  TickType_t pressedTickCounter; /* time the button was pressed */
  uint16_t buttonTimeoutMs; /* button press timeout in milliseconds */
} PONG_LimiterT;

typedef enum {
  PONG_GAME_STATE_INIT,
  PONG_GAME_STATE_WAIT_FOR_START,
  PONG_GAME_STATE_RUNNING,
  PONG_GAME_STATE_PAUSE,
  PONG_GAME_STATE_OVER,
} PONG_GameState;

static PONG_GameState PONG_gameState;
static PONG_BallT PONG_Balls[PONG_NOF_BALLS];
static PONG_LimiterT PONG_LeftLimiter, PONG_RightLimiter;

static bool ButtonRightPressed(void) {
#if PL_HAS_MP3
  MUSIC_PlayTheme(MUSIC_THEME_WHOSH1);
  FRTOS1_taskYIELD();
#endif
  return EVNT1_GetClearEvent(EVNT1_BTN_LEFT_PRESSED);
}

static bool ButtonLeftPressed(void) {
#if PL_HAS_MP3
  MUSIC_PlayTheme(MUSIC_THEME_WHOSH1);
  FRTOS1_taskYIELD();
#endif
#if PL_HAS_LEFT_BTN
  return EVNT1_GetClearEvent(EVNT1_BTN_LEFT_PRESSED);
#else
  return TRUE;
#endif
}

static void PONG_InitBall(PONG_BallT *ball) {
  ball->pos = 0;
  ball->forward = TRUE;
  ball->color = 0;
  ball->speedMs = 0;
  ball->drawTickCounter = 0;
}

static void POING_InitLimiter(PONG_LimiterT *limiter) {
  limiter->pos = 0;
  limiter->color = 0;
  limiter->isOn = FALSE;
  limiter->pressedTickCounter = 0;
  limiter->buttonTimeoutMs = 0;
}

static void PONG_DrawBall(PONG_BallT *ball) {
  (void)NEO_SetPixelColor(ball->pos, ball->color);
  ball->drawTickCounter = FRTOS1_xTaskGetTickCount();
}

static void PONG_SetLimiter(PONG_LimiterT *limiter) {
  (void)NEO_SetPixelColor(limiter->pos, limiter->color);
  limiter->isOn = TRUE;
}

static void PONG_ClearLimiter(PONG_LimiterT *limiter) {
  (void)NEO_SetPixelColor(limiter->pos, PONG_DEFAULT_BACKGROUND_RGB);
  limiter->isOn = FALSE;
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

static void PONG_GameOver(void) {
  int i;

#if PL_HAS_MP3
  MUSIC_PlayTheme(MUSIC_THEME_BUZZER);
#endif
  for(i=0;i<PONG_NOF_PIXELS;i++) {
    NEO_SetPixelColor(i, 0x300000);
  }
  NEO_TransferPixels();
}

static void PONG_PlayerLooses(bool isLeft) {
}

static void PONG_InitGame(void) {
  int i;

  NEO_ClearAllPixel();
  /* background */
  for(i=0;i<PONG_NOF_PIXELS;i++) {
    NEO_SetPixelColor(i, PONG_DEFAULT_BACKGROUND_RGB);
  }
  NEO_TransferPixels();
  for(i=0;i<PONG_NOF_BALLS;i++) {
    PONG_InitBall(&PONG_Balls[i]);
  }
  POING_InitLimiter(&PONG_LeftLimiter);
  POING_InitLimiter(&PONG_RightLimiter);
}

static void PONG_StartGame(void) {
  int i;

  PONG_LeftLimiter.color = 0x442255;
  PONG_LeftLimiter.pos = 0;
  PONG_LeftLimiter.isOn = TRUE;
  PONG_LeftLimiter.buttonTimeoutMs = 250;

  PONG_RightLimiter.color = 0x222255;
  PONG_RightLimiter.pos = PONG_NOF_PIXELS-1;
  PONG_RightLimiter.isOn = TRUE;
  PONG_RightLimiter.buttonTimeoutMs = 250;

#if PONG_NOF_BALLS>=1
  PONG_Balls[0].pos = PONG_LeftLimiter.pos+1; /* leftmost */
  PONG_Balls[0].color = 0x001100; /* green */
  PONG_Balls[0].forward = TRUE; /* left to right */
  PONG_Balls[0].speedMs = 200; /* initial speed */
#endif
#if PONG_NOF_BALLS>=2
  PONG_Balls[1].pos = PONG_NOF_PIXELS-1-1; /* rightmost */
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
  PONG_SetLimiter(&PONG_LeftLimiter);
  PONG_SetLimiter(&PONG_RightLimiter);
  NEO_TransferPixels();
}

static void PONG_CheckLimiterButtons(void) {
  bool gameOver = FALSE;
  TickType_t currTickCount;

  currTickCount = FRTOS1_xTaskGetTickCount();
  if (EVNT1_GetClearEvent(EVNT1_BTN_LEFT_PRESSED)) {
    PONG_LeftLimiter.pressedTickCounter = currTickCount;
    PONG_SetLimiter(&PONG_LeftLimiter);
  } else if (PONG_LeftLimiter.isOn && currTickCount>PONG_LeftLimiter.pressedTickCounter+(PONG_LeftLimiter.buttonTimeoutMs/portTICK_RATE_MS)) {
    PONG_ClearLimiter(&PONG_LeftLimiter);
  }
  if (EVNT1_GetClearEvent(EVNT1_BTN_RIGHT_PRESSED)) {
    PONG_RightLimiter.pressedTickCounter = currTickCount;
    PONG_SetLimiter(&PONG_RightLimiter);
  } else if (PONG_RightLimiter.isOn && currTickCount>PONG_RightLimiter.pressedTickCounter+(PONG_RightLimiter.buttonTimeoutMs/portTICK_RATE_MS)) {
    PONG_ClearLimiter(&PONG_RightLimiter);
  }
}

static bool PONG_UpdateBall(PONG_BallT *ball) {
  bool gameOver = FALSE;

  PONG_RemoveBall(ball); /* clear current ball */
  if (ball->forward) {
    if (ball->pos<PONG_RightLimiter.pos-1) {
      ball->pos++;
      PONG_DrawBall(ball);
    } else if (/*ball->pos==PONG_RightLimiter.pos-1*/ PONG_RightLimiter.isOn) {
      ball->forward = FALSE;
      ball->pos--;
      PONG_DrawBall(ball);
    } else {
      PONG_PlayerLooses(FALSE); /* right player looses */
      gameOver = TRUE;
    }
  } else { /* backward */
    if (ball->pos>PONG_LeftLimiter.pos+1) {
      ball->pos--;
      PONG_DrawBall(ball);
    } else if (/*ball->pos==PONG_LeftLimiter.pos+1*/ PONG_LeftLimiter.isOn) {
      ball->forward = TRUE;
      ball->pos++;
      PONG_DrawBall(ball);
    } else {
      PONG_PlayerLooses(TRUE); /* left player looses */
      gameOver = TRUE;
    }
  }
  return gameOver;
}

static bool PONG_UpdateBalls(void) {
  TickType_t currTickCount;
  bool transferPixels = FALSE;
  int i;
  bool gameOver = FALSE;

  currTickCount = FRTOS1_xTaskGetTickCount();
  PONG_CheckLimiterButtons();
  for(i=0;i<PONG_NOF_BALLS;i++) {
    if (currTickCount>=PONG_Balls[i].drawTickCounter+PONG_Balls[i].speedMs/portTICK_RATE_MS) {
      if (PONG_UpdateBall(&PONG_Balls[i])) {
        gameOver = TRUE;
      }
      transferPixels = TRUE;
    }
  }
  if (transferPixels) {
    NEO_TransferPixels();
  }
  return gameOver;
}

static void PONG_RunMachine(void) {
  switch(PONG_gameState) {
    case PONG_GAME_STATE_INIT:
      PONG_InitGame();
      PONG_gameState = PONG_GAME_STATE_WAIT_FOR_START;
      break;

    case PONG_GAME_STATE_WAIT_FOR_START:
    #if PL_HAS_MP3
      if (!MUSIC_IsPlaying()) {
        MUSIC_PlayTheme(MUSIC_THEME_JACK1);
        FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
      }
    #endif
      if (EVNT1_GetClearEvent(EVNT1_BTN_LEFT_PRESSED)) {
#if PL_HAS_MP3
        MUSIC_Stop();
#endif
        PONG_StartGame();
        PONG_gameState = PONG_GAME_STATE_RUNNING;
      }
      break;

    case PONG_GAME_STATE_RUNNING:
      if (PONG_UpdateBalls()) {
        PONG_GameOver();
        FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
        PONG_gameState = PONG_GAME_STATE_OVER;
      }
      break;

    case PONG_GAME_STATE_PAUSE:
      /* stay in current state */
      break;

    case PONG_GAME_STATE_OVER:
      if (EVNT1_GetClearEvent(EVNT1_BTN_LEFT_PRESSED)) {
        PONG_gameState = PONG_GAME_STATE_INIT;
      }
      break;

    default:
      break;
  }
}

#if PL_HAS_MIDI
static void PlayMIDI(void) {
  int instrument, note;

  VS1_MIDI_SetBank(0, 0);
  for(instrument=0; instrument<127; instrument++) {
    VS1_MIDI_SetInstrument(0, instrument);
    for(note=30; note<40; note++) {
      VS1_MIDI_NoteOn(0, note, 127);
      FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
      VS1_MIDI_NoteOff(0, note, 127);
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
    }
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}
#endif

static portTASK_FUNCTION(PongTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  FRTOS1_vTaskDelay(1000/portTICK_RATE_MS); /* wait some time to mount sd card */
  PONG_gameState = PONG_GAME_STATE_INIT;
#if PL_HAS_MIDI
  VS1_LoadRealtimeMidiPlugin();
  MM_Play();
#endif
  for(;;) {
#if PL_HAS_KEYS
    KEY1_ScanKeys();
#endif
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
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_HAS_PONG */
