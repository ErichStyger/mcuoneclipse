/**
 * \file
 * \brief Snake game
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a classic Nokia phone game: the Snake game.
 *    Based on: https://bitbucket.org/hewerthomn/snake-duino-iii/src/303e1c2a016eb0746b2a7ad1176b16ee78f0177b/SnakeDuinoIII.ino?at=master
 */
/*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <phk@FreeBSD.ORG> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return Poul-Henning Kamp
* ----------------------------------------------------------------------------
*/
#include "platform.h"

#if PL_CONFIG_HAS_SNAKE_GAME
#include "McuWait.h"
#include "McuGDisplaySSD1306.h"
#include "Snake.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuSSD1306.h"
#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontHelv08Normal.h"

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

/* frame size */
#define MAX_WIDTH  McuGDisplaySSD1306_GetWidth()
#define MAX_HEIGHT McuGDisplaySSD1306_GetHeight()

/* defaults */
#define SNAKE_LEN   10 /* initial snake length */
#define SNAKE_SPEED 100 /* initial delay in ms */

static int snakeLen = SNAKE_LEN; /* actual snake length */
static int point    = 0, points = 10;
static int level    = 0, time   = SNAKE_SPEED;
static McuGDisplaySSD1306_PixelDim xFood = 0, yFood  = 0; /* location of food */

typedef enum {
  SNAKE_DIRECTION_LEFT,
  SNAKE_DIRECTION_RIGHT,
  SNAKE_DIRECTION_UP,
  SNAKE_DIRECTION_DOWN,
} SNAKE_Direction_e;
static SNAKE_Direction_e SnakeCurrentDirection;

#define SNAKE_MAX_LEN   32 /* maximum length of snake */

/* vector containing the coordinates of the individual parts */
/* of the snake {cols[0], row[0]}, corresponding to the head */
static McuGDisplaySSD1306_PixelDim snakeCols[SNAKE_MAX_LEN];

/* Vector containing the coordinates of the individual parts */
/* of the snake {cols [snake_lenght], row [snake_lenght]} correspond to the tail */
static McuGDisplaySSD1306_PixelDim snakeRow[SNAKE_MAX_LEN];

static TaskHandle_t gameTaskHandle;
static QueueHandle_t SNAKE_Queue;
#define SNAKE_QUEUE_LENGTH     5
#define SNAKE_QUEUE_ITEM_SIZE  sizeof(SNAKE_Event)

bool SNAKE_GameIsRunning(void) {
  eTaskState taskState;

  if (gameTaskHandle==NULL) {
    return FALSE;
  }
  taskState = eTaskGetState(gameTaskHandle);
  return (taskState!=eSuspended); /* only if task is not suspended */
}

BaseType_t SNAKE_SendButtonEventFromISR(SNAKE_Event event, BaseType_t *pxHigherPriorityTaskWoken) {
  if (event==SNAKE_ENTER_EVENT) { /* center button is used to pause/continue game */
    event = SNAKE_START_STOP_EVENT;
  }
  return xQueueSendFromISR(SNAKE_Queue, &event, pxHigherPriorityTaskWoken);
}

/* below can be used from non-interrupts */
void SNAKE_SendEvent(SNAKE_Event event) {
  if (event==SNAKE_ENTER_EVENT) { /* center button is used to pause/continue game */
    event = SNAKE_START_STOP_EVENT;
  } else if (event==SNAKE_RESUME_GAME) {
    vTaskResume(gameTaskHandle);
    return;
  } else if (event==SNAKE_SUSPEND_GAME) {
    vTaskSuspend(gameTaskHandle);
    return;
  }
  if (SNAKE_GameIsRunning()) { /* only if task is not suspended */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
    uint8_t buf[32];

    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"SNAKE_SendEvent: ");
    McuUtility_strcatNum32u(buf, sizeof(buf), event);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuSystemView_Print((char*)buf);
#endif
    if (xQueueSendToBack(SNAKE_Queue, &event, portMAX_DELAY)!=pdPASS) {
      for(;;){} /* ups? */
    }
  }
}

SNAKE_Event SNAKE_ReceiveEvent(bool blocking) {
  portBASE_TYPE res;
  SNAKE_Event event;

  if (blocking) {
    res = xQueueReceive(SNAKE_Queue, &event, portMAX_DELAY);
  } else {
    res = xQueueReceive(SNAKE_Queue, &event, 0);
  }
  if (res==errQUEUE_EMPTY) {
    return SNAKE_NO_EVENT;
  }
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  {
    uint8_t buf[32];

    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"SNAKE_ReceiveEvent: ");
    McuUtility_strcatNum32u(buf, sizeof(buf), event);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuSystemView_Print((char*)buf);
  }
#endif
  return event;
}

static void waitAnyButton(void) {
  (void)SNAKE_ReceiveEvent(TRUE); /* blocking wait */
}

static void showPause(void) {
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;
  McuFontDisplay_Font *font = McuFontHelv08Normal_GetFont();
  uint8_t buf[16];

  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);
  McuGDisplaySSD1306_Clear();
  
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"Pause", font, NULL))/2; /* center text */
  y = 0;
  McuFontDisplay_WriteString((unsigned char*)"Pause", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  x = 0;
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Level: ", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuUtility_Num16sToStr(buf, sizeof(buf), level);
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  x = 0;
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Points: ", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuUtility_Num16sToStr(buf, sizeof(buf), point-1);
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"(Press Button)", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  McuGDisplaySSD1306_UpdateFull();
  
  waitAnyButton();
  McuGDisplaySSD1306_Clear();
  McuGDisplaySSD1306_UpdateFull();
}

static void resetGame(void) {
  int i;
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;
  McuFontDisplay_Font *font = McuFontHelv08Normal_GetFont();
  
  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);
  
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"Ready?", font, NULL))/2; /* center text */
  y = totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Ready?", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"(Press Button)", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuGDisplaySSD1306_UpdateFull();
  waitAnyButton();
  
  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"Go!", font, NULL))/2; /* center text */
  y = McuGDisplaySSD1306_GetHeight()/2 - totalHeight/2;
  McuFontDisplay_WriteString((unsigned char*)"Go!", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuGDisplaySSD1306_UpdateFull();
  McuWait_WaitOSms(1000);
  McuGDisplaySSD1306_Clear();
  McuGDisplaySSD1306_UpdateFull();
  
  snakeLen = SNAKE_LEN;
  for(i=0; i<snakeLen && i<SNAKE_MAX_LEN; i++) {
    snakeCols[i] = snakeLen+2-i; /* start off two pixels from the boarder */
    snakeRow[i]  = (MAX_HEIGHT/2);
  }
  /* initial food position */
  xFood = (McuGDisplaySSD1306_GetWidth()/2);
  yFood = (McuGDisplaySSD1306_GetHeight()/2);
 
  level  = 0;  
  point  = 0;
  points = SNAKE_LEN;
  time   = SNAKE_SPEED;
 
  SnakeCurrentDirection = SNAKE_DIRECTION_RIGHT;
}

static void moveSnake(void) {
  int i, dr, dc;

  /* move snake */
  for(i=snakeLen; i>1; i--) { /* extend snake by one position */
    snakeRow[i]  = snakeRow[i-1];
    snakeCols[i] = snakeCols[i-1];
  }
  /* change snake head based on direction */
  switch(SnakeCurrentDirection) {
    case SNAKE_DIRECTION_UP:    { dr = -1; dc =  0;} break;
    case SNAKE_DIRECTION_RIGHT: { dr =  0; dc =  1;} break;
    case SNAKE_DIRECTION_DOWN:  { dr =  1; dc =  0;} break;
    case SNAKE_DIRECTION_LEFT:  { dr =  0; dc = -1;} break;
  }
  snakeRow[0]  += dr;
  snakeCols[0] += dc;
  snakeRow[1]  += dr;
  snakeCols[1] += dc;
}

static void drawSnake(void) {
  int i;

  /* draw snake */
  McuGDisplaySSD1306_Clear();
  McuGDisplaySSD1306_DrawBox(0, 0, MAX_WIDTH, MAX_HEIGHT, 1, McuGDisplaySSD1306_COLOR_WHITE); /* draw border around display */
  McuGDisplaySSD1306_DrawCircle(snakeCols[1], snakeRow[1], 1, McuGDisplaySSD1306_COLOR_WHITE); /* draw head */
  for(i=0; i<snakeLen; i++) { /* draw from head to tail */
    McuGDisplaySSD1306_PutPixel(snakeCols[i], snakeRow[i], McuGDisplaySSD1306_COLOR_WHITE);
  }
  McuGDisplaySSD1306_DrawFilledBox(xFood, yFood, 3, 3, McuGDisplaySSD1306_COLOR_WHITE); /* draw food */
  McuGDisplaySSD1306_UpdateFull();
}

static void eatFood(void) {
  /* increase the point and snake length */
  point++;
  snakeLen += 2;
  if (snakeLen>SNAKE_MAX_LEN-1) {
    snakeLen = SNAKE_MAX_LEN-1;
  }
  /* new random coordinates for food */
  xFood = McuUtility_random(1, MAX_WIDTH-3);
  yFood = McuUtility_random(1, MAX_HEIGHT-3);
  drawSnake();  
}

static void upLevel(void) {
  level++;
  point   = 1;
  points += 10;
  if(level > 1) {
    time -= 10;
    if (time<10) {
      time = 10;
    }
  }
}

static void checkButtons(void) {
  /*! \todo Check implementation of handling push button inputs */
  SNAKE_Event event;
  McuGDisplaySSD1306_PixelDim xSnake, ySnake; /* snake face */

  event = SNAKE_ReceiveEvent(FALSE);
  /* get head position */
  xSnake = snakeCols[0];
  ySnake = snakeRow[0];
  /* LEFT */
  if(event==SNAKE_LEFT_EVENT && SnakeCurrentDirection!=SNAKE_DIRECTION_RIGHT) {
    if((xSnake > 0 || xSnake <= McuGDisplaySSD1306_GetWidth() - xSnake)) {
      SnakeCurrentDirection = SNAKE_DIRECTION_LEFT;
    }
    return;
  }
  /* RIGHT */
  if(event==SNAKE_RIGHT_EVENT && SnakeCurrentDirection!=SNAKE_DIRECTION_LEFT) {
    if((xSnake > 0 || xSnake <= McuGDisplaySSD1306_GetWidth() - xSnake)) {
      SnakeCurrentDirection = SNAKE_DIRECTION_RIGHT;
    }
    return;
  }
  /* UP */
  if(event==SNAKE_UP_EVENT && SnakeCurrentDirection!=SNAKE_DIRECTION_DOWN) {
    if((ySnake > 0 || ySnake <= McuGDisplaySSD1306_GetHeight() - ySnake)) {
      SnakeCurrentDirection = SNAKE_DIRECTION_UP;
    }
    return;
  }
  /* DOWN */
  if(event==SNAKE_DOWN_EVENT && SnakeCurrentDirection!=SNAKE_DIRECTION_UP) {
    if((ySnake > 0 || ySnake <= McuGDisplaySSD1306_GetHeight() - ySnake)) {
      SnakeCurrentDirection = SNAKE_DIRECTION_DOWN;
    }
    return;
  }
  /* START/PAUSE */
  if(event==SNAKE_START_STOP_EVENT) {
    showPause();
  }
}

static void gameover(void) {
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;
  McuFontDisplay_Font *font = McuFontHelv08Normal_GetFont();
  uint8_t buf[16];

  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"End of Game", font, NULL))/2; /* center text */
  y = 0;
  McuFontDisplay_WriteString((unsigned char*)"End of Game", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  x = 0;
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Level: ", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuUtility_Num16sToStr(buf, sizeof(buf), level);
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  x = 0;
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Points: ", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuUtility_Num16sToStr(buf, sizeof(buf), point-1);
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"(Press Button)", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuGDisplaySSD1306_UpdateFull();
  McuWait_WaitOSms(4000);
  waitAnyButton();
//  vTaskSuspend(NULL); /* pause task until resumed again */
  resetGame();  
}

static void snake(void) {
  int i;
  McuGDisplaySSD1306_PixelDim xSnake, ySnake; /* snake face */
  
  xSnake = snakeCols[0];
  ySnake = snakeRow[0];
  if(point == 0 || point >= points) {
    upLevel();
  }  
  checkButtons();
  /* the snake has eaten the food (right or left) */
  for(i=0; i < 3; i++) { /* check 3 pixels around */
    /* control the snake's head (x) with x-coordinates of the food */
    if((xSnake+1 == xFood) || (xSnake == xFood+1))  {
      /* control the snake's head (y) with y-coordinates of the food */
      if((ySnake == yFood) || (ySnake+1 == yFood) || (ySnake == yFood+1)) {
        eatFood();
      }
    }
    /* the snake has eaten the food (from above or from below) */
    if((ySnake == yFood) || (ySnake == yFood+i)) {
      if((xSnake == xFood) || (xSnake+i == xFood) || (xSnake == xFood+i)) {
        eatFood();
      }
    }    
  }
  if(SnakeCurrentDirection==SNAKE_DIRECTION_LEFT) {
    /* snake touches the left wall */
    if(xSnake == 1) {
      gameover();
    }
    if(xSnake > 1) {
      moveSnake();
      drawSnake();
    }
  }
  if(SnakeCurrentDirection==SNAKE_DIRECTION_RIGHT) {
    /* snake touches the top wall */
    if(xSnake == MAX_WIDTH-1) {
      gameover();
    }
    if(xSnake < MAX_WIDTH-1) {
      moveSnake();
      drawSnake();
    }
  }
  if(SnakeCurrentDirection==SNAKE_DIRECTION_UP) {
    /* snake touches the above wall */
    if(ySnake == 1) {
      gameover();
    }
    if(ySnake > 1) {
      moveSnake();
      drawSnake();
    }
  }
  if(SnakeCurrentDirection==SNAKE_DIRECTION_DOWN) {
    /* snake touches the ground */
    if(ySnake == MAX_HEIGHT-1) {
      gameover();
    }
    if(ySnake  < MAX_HEIGHT-1) {
      moveSnake();
      drawSnake();
    }
  }
}

static void intro(void) {
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;
  McuFontDisplay_Font *font = McuFontHelv08Normal_GetFont();
  
  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"Snake Game", font, NULL))/2; /* center text */
  y = totalHeight;
  McuFontDisplay_WriteString((unsigned char*)"Snake Game", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  y += totalHeight;
  x = (McuGDisplaySSD1306_GetWidth()-McuFontDisplay_GetStringWidth((unsigned char*)"by Erich Styger", font, NULL))/2; /* center text */
  McuFontDisplay_WriteString((unsigned char*)"by Erich Styger", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
  McuGDisplaySSD1306_UpdateFull();
  McuWait_WaitOSms(2000);
}

static void SnakeTask(void *pvParameters) {
  McuSSD1306_Init();
  McuSSD1306_Clear(); /* clear the display */
  McuSSD1306_PrintString(0, 0, (unsigned char*)"Welcome to SNAKE!");
  intro();
  McuUtility_randomSetSeed(xTaskGetTickCount());
  resetGame();
  drawSnake();
  for(;;) {
    snake();
    vTaskDelay(pdMS_TO_TICKS(time));
  }
}

void SNAKE_Deinit(void) {
  /* nothing to do? */
}

void SNAKE_Init(void) {
  SNAKE_Queue = xQueueCreate(SNAKE_QUEUE_LENGTH, SNAKE_QUEUE_ITEM_SIZE);
  if (SNAKE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(SNAKE_Queue, "SnakeQueue");
  if (xTaskCreate(
      SnakeTask,  /* pointer to the task */
        "Snake", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        &gameTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  //vTaskSuspend(gameTaskHandle);
}
#endif /* PL_HAS_SNAKE_GAME */
