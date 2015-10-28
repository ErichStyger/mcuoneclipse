/*
 * Snake.c
 *
 *  Created on: Jul 2, 2014
 *      Author: Erich Styger
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

#include "PDC1.h"
#include "WAIT1.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "GFONT1.h"
#include "Snake.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "EVNT1.h"

/* constants */
#define UP    1
#define RIGHT 2
#define DOWN  3
#define LEFT  4

/* frame size */
#define MAX_WIDTH  GDisp1_GetWidth()
#define MAX_HEIGHT GDisp1_GetHeight()

/* defaults */
#define SNAKE_LEN   10
#define SNAKE_SPEED 20 /* initial delay in ms */

/* snake length */
static int snakeLen = SNAKE_LEN;
static int point    = 0, points = 10;
static int level    = 0, time   = SNAKE_SPEED;

static int xSnake,    ySnake; /* snake face */
static int xFood = 0, yFood  = 0; /* location of food */

/* directions */
static int dr = 0, dc = 1;
static bool left = FALSE, right = TRUE, up = FALSE, down = FALSE;

/* vector containing the coordinates of the individual parts */
/* of the snake {cols[0], row[0]}, corresponding to the head */
static int snakeCols[260];

/* Vector containing the coordinates of the individual parts */
/* of the snake {cols [snake_lenght], row [snake_lenght]} correspond to the tail */
static int snakeRow[260];

static void waitAnyButton(void) {
  for(;;) {
    if (EVNT1_GetClearEvent(EVNT1_SNAKE_START_PAUSE)) {
      break;
    }
    if (EVNT1_GetClearEvent(EVNT1_SNAKE_UP)) {
      break;
    }
    if (EVNT1_GetClearEvent(EVNT1_SNAKE_DOWN)) {
      break;
    }
    if (EVNT1_GetClearEvent(EVNT1_SNAKE_LEFT)) {
      break;
    }
    if (EVNT1_GetClearEvent(EVNT1_SNAKE_RIGHT)) {
      break;
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static void delay(int ms) {
  WAIT1_Waitms(ms);
}

static int random(int min, int max) {
  TickType_t cnt;
  
  cnt = FRTOS1_xTaskGetTickCount();
  cnt &= 0xff; /* reduce to 8 bits */
  if (max>64) {
    cnt >>= 1;
  } else {
    cnt >>= 2;
  }
  if (cnt<min) {
    cnt = min;
  }
  if (cnt>max) {
    cnt = max/2;
  }
  return cnt;
}

static void showPause(void) {
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, totalHeight;
  GFONT_Callbacks *font = GFONT1_GetFont();
  uint8_t buf[16];

  FDisp1_GetFontHeight(font, &charHeight, &totalHeight);
  GDisp1_Clear();
  
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"Pause", font, NULL))/2; /* center text */
  y = 0;
  FDisp1_WriteString((unsigned char*)"Pause", GDisp1_COLOR_BLACK, &x, &y, font);

  x = 0;
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"Level: ", GDisp1_COLOR_BLACK, &x, &y, font);
  UTIL1_Num16sToStr(buf, sizeof(buf), level);
  FDisp1_WriteString(buf, GDisp1_COLOR_BLACK, &x, &y, font);

  x = 0;
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"Points: ", GDisp1_COLOR_BLACK, &x, &y, font);
  UTIL1_Num16sToStr(buf, sizeof(buf), point-1);
  FDisp1_WriteString(buf, GDisp1_COLOR_BLACK, &x, &y, font);
  
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"(Press Button)", GDisp1_COLOR_BLACK, &x, &y, font);

  GDisp1_UpdateFull();
  
  waitAnyButton();
  GDisp1_Clear();
  GDisp1_UpdateFull();
}

static void resetGame(void) {
  int i;
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, totalHeight;
  GFONT_Callbacks *font = GFONT1_GetFont();
  
  GDisp1_Clear();
  FDisp1_GetFontHeight(font, &charHeight, &totalHeight);
  
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"Ready?", font, NULL))/2; /* center text */
  y = totalHeight;
  FDisp1_WriteString((unsigned char*)"Ready?", GDisp1_COLOR_BLACK, &x, &y, font);
  
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"(Press Button)", GDisp1_COLOR_BLACK, &x, &y, font);
  GDisp1_UpdateFull();
  waitAnyButton();
  
  GDisp1_Clear();
  FDisp1_GetFontHeight(font, &charHeight, &totalHeight);
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"Go!", font, NULL))/2; /* center text */
  y = GDisp1_GetHeight()/2 - totalHeight/2;
  FDisp1_WriteString((unsigned char*)"Go!", GDisp1_COLOR_BLACK, &x, &y, font);
  GDisp1_UpdateFull();
  delay(1000);
  GDisp1_Clear();
  GDisp1_UpdateFull();
  
  snakeLen = SNAKE_LEN;
  for(i=0; i < (snakeLen-1); i++) {
    snakeCols[i] = i;
    snakeRow[i]  = (MAX_HEIGHT / 2);
  }
 
  xSnake = 0;
  ySnake = (MAX_WIDTH/2);
 
  xFood = (GDisp1_GetWidth()/2);
  yFood = (GDisp1_GetHeight()/2);
 
  level  = 0;  
  point  = 0;
  points = SNAKE_LEN;
  time   = SNAKE_SPEED;
 
  up    = FALSE; 
  right = TRUE;
  down  = FALSE;
  left  = FALSE;
  dr    = 0;
  dc    = 1;
}

static void drawSnake(void) {
  int i;
  
  GDisp1_DrawBox(0, 0, MAX_WIDTH, MAX_HEIGHT, 1, GDisp1_COLOR_BLACK);
  for(i = snakeLen; i > 0; i--) {
    GDisp1_DrawCircle(snakeCols[i], snakeRow[i], 1, GDisp1_COLOR_BLACK);
  }
  GDisp1_DrawFilledBox(xFood, yFood, 3, 3, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  for(i = snakeLen; i > 0; i--) {
    snakeRow[i]  = snakeRow[i - 1];
    snakeCols[i] = snakeCols[i - 1];
  }
  snakeRow[0]  += dr;
  snakeCols[0] += dc;
}

static void eatFood(void) {
  /* increase the point and snake length */
  point++;
  snakeLen += 2;
  /* new coordinates food randomly */
  xFood = random(1, MAX_WIDTH-3);
  yFood = random(1, MAX_HEIGHT-3);
  drawSnake();  
}

static void upLevel(void) {
  level++;
  point   = 1;
  points += 10;
  if(level > 1) {
    time -= 4;
  }
}

static void direc(int d) {
  switch(d) {
    case UP:    { left=FALSE; right=FALSE; up=TRUE ; down=FALSE; dr = -1; dc =  0;} break;
    case RIGHT: { left=FALSE; right=TRUE ; up=FALSE; down=FALSE; dr =  0; dc =  1;} break;
    case DOWN:  { left=FALSE; right=FALSE; up=FALSE; down=TRUE ; dr =  1; dc =  0;} break;
    case LEFT:  { left=TRUE ; right=FALSE; up=FALSE; down=FALSE; dr =  0; dc = -1;} break;
  }
}

static void moveSnake(void) {
  /* LEFT */
  if(EVNT1_GetClearEvent(EVNT1_SNAKE_LEFT) && !right) {
    if((xSnake > 0 || xSnake <= GDisp1_GetWidth() - xSnake)) {
      direc(LEFT);
    }
    return;
  }
  /* RIGHT */
  if(EVNT1_GetClearEvent(EVNT1_SNAKE_RIGHT) && !left) {
    if((xSnake > 0 || xSnake <= GDisp1_GetWidth() - xSnake)) {
      direc(RIGHT);
    }
    return;
  }
  /* UP */
  if(EVNT1_GetClearEvent(EVNT1_SNAKE_UP) && !down) {
    if((ySnake > 0 || ySnake <= GDisp1_GetHeight() - ySnake)) {
      direc(UP);
    }
    return;
  }
  /* DOWN */
  if(EVNT1_GetClearEvent(EVNT1_SNAKE_DOWN) && !up) {
    if((ySnake > 0 || ySnake <= GDisp1_GetHeight() - ySnake)) {
      direc(DOWN);
    }
    return;
  }
  /* START/PAUSE */
  if(EVNT1_GetClearEvent(EVNT1_SNAKE_START_PAUSE)) {
    showPause();
  }
}

static void gameover(void) {
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, totalHeight;
  GFONT_Callbacks *font = GFONT1_GetFont();
  uint8_t buf[16];

  GDisp1_Clear();
  FDisp1_GetFontHeight(font, &charHeight, &totalHeight);

  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"End of Game", font, NULL))/2; /* center text */
  y = 0;
  FDisp1_WriteString((unsigned char*)"End of Game", GDisp1_COLOR_BLACK, &x, &y, font);

  x = 0;
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"Level: ", GDisp1_COLOR_BLACK, &x, &y, font);
  UTIL1_Num16sToStr(buf, sizeof(buf), level);
  FDisp1_WriteString(buf, GDisp1_COLOR_BLACK, &x, &y, font);

  x = 0;
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"Points: ", GDisp1_COLOR_BLACK, &x, &y, font);
  UTIL1_Num16sToStr(buf, sizeof(buf), point-1);
  FDisp1_WriteString(buf, GDisp1_COLOR_BLACK, &x, &y, font);

  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"(Press Button)", font, NULL))/2; /* center text */
  y += totalHeight;
  FDisp1_WriteString((unsigned char*)"(Press Button)", GDisp1_COLOR_BLACK, &x, &y, font);
  GDisp1_UpdateFull();
  delay(4000);
  waitAnyButton();
 
  resetGame();  
}

static void snake(void) {
  int i;
  
  xSnake = snakeCols[0];
  ySnake = snakeRow[0];
  if(point == 0 || point >= points) {
    upLevel();
  }  
  GDisp1_Clear();
  /* GDisp1_UpdateFull(); */
  moveSnake();
  /* the snake has eaten the food (right or left) */
  for(i=0; i < 3; i++) {
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
  /* LEFT */
  if(left) {
    /* snake touches the left wall */
    if(xSnake == 1) {
      gameover();
    }
    if(xSnake  > 1) {
      drawSnake();
    }
  }
  /* RIGHT */
  if(right) {
    /* snake touches the top wall */
    if(xSnake == MAX_WIDTH-1) {
      gameover();
    }
    if(xSnake  < MAX_WIDTH-1) {
      drawSnake();
    }
  }
  /* UP */
  if(up) {
    /* snake touches the above wall */
    if(ySnake == 1) {
      gameover();
    }
    if(ySnake > 1) {
      drawSnake();
    }
  }
  /* DOWN */
  if(down) {
    /* snake touches the ground */
    if(ySnake == MAX_HEIGHT-1) {
      gameover();
    }
    if(ySnake  < MAX_HEIGHT-1) {
      drawSnake();
    }
  }
}

static void intro(void) {
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, totalHeight;
  GFONT_Callbacks *font = GFONT1_GetFont();
  
  GDisp1_Clear();
  FDisp1_GetFontHeight(font, &charHeight, &totalHeight);
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"Snake Game", font, NULL))/2; /* center text */
  y = totalHeight;
  FDisp1_WriteString((unsigned char*)"Snake Game", GDisp1_COLOR_BLACK, &x, &y, font);
  y += totalHeight;
  x = (GDisp1_GetWidth()-FDisp1_GetStringWidth((unsigned char*)"McuOnEclipse", font, NULL))/2; /* center text */
  FDisp1_WriteString((unsigned char*)"McuOnEclipse", GDisp1_COLOR_BLACK, &x, &y, font);
  GDisp1_UpdateFull();
  WAIT1_WaitOSms(3000);
}

static void SnakeTask(void *pvParameters) {
  intro();
  resetGame();
  for(;;) {
    snake();
    FRTOS1_vTaskDelay(time/portTICK_RATE_MS);
  }
}

void SNAKE_Init(void) {
  if (FRTOS1_xTaskCreate(
      SnakeTask,  /* pointer to the task */
        "Snake", /* task name for kernel awareness debugging */
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
