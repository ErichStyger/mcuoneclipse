/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "flipdot.h"
#include "rs485.h"

static uint8_t calcCheckSum(uint8_t *buf, size_t bufSize) {
  int32_t sum = 0;
  for(int i=1; i<bufSize-2; i++) { /* sum up everything up including EOT at the end, but without SOT at the start */
    sum += buf[i];
  }
  sum &= 0xff; /* chop to a byte */
  sum ^= 255; /* EXOR it */
  sum += 1; /* add one */
  return sum;
}

static const char NumToHexChar[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

static void StoreASCIIHex8(uint8_t *buf, uint8_t val) {
  /* store checksum as ASCII, e.b. 0x4A  => '4' 'A' */
  buf[0] = NumToHexChar[val/16];
  buf[1] = NumToHexChar[val%16];
}

static void StoreASCIIHex16(uint8_t *buf, uint16_t val) {
  /* store checksum as ASCII, e.b. 0x4A  => '4' 'A' */
  StoreASCIIHex8(buf, (val>>8)&0xff);
  StoreASCIIHex8(buf+2, val&0xff);
}

#define FLIP_DOT_DEVICE_ADDRESS  (1) /* position of rotary switch */
#define FLIP_DOT_NOF_COL         (20)
#define FLIP_DOT_NOF_ROW         (14)
#define FLIP_DOT_NOF_DATA        (FLIP_DOT_NOF_COL*(((FLIP_DOT_NOF_ROW-1)/8)+1))
#define FLIP_DOT_NOF_BUF_BYTES   (1/*SOT*/ +1/*cmd*/ +1/*addr*/ +2/*nof*/ +2*FLIP_DOT_NOF_DATA +1/*EOT*/ +2/*checksum*/)

#define FLIP_DOT_BUF_POS_SOT     (0)
#define FLIP_DOT_BUF_POS_CMD     (1)
#define FLIP_DOT_BUF_POS_ADDR    (2)
#define FLIP_DOT_BUF_POS_NOF     (3)
#define FLIP_DOT_BUF_POS_DATA    (5)
#define FLIP_DOT_BUF_POS_EOT     (FLIP_DOT_BUF_POS_DATA+2*FLIP_DOT_NOF_DATA)
#define FLIP_DOT_BUF_POS_CHECK   (FLIP_DOT_BUF_POS_EOT+1)

static uint8_t dotMap[((FLIP_DOT_NOF_COL-1)/8)+1][FLIP_DOT_NOF_ROW];
/* see https://freefontsdownload.net/free-small-5x3-regular-font-125210.htm, should add subline (g, y, ...) plus extra column for w and m */
static const char char3x5_colon[5][3] = {
    "   ",
    " * ",
    "   ",
    " * ",
    "   "
};

static const char char3x5_space[5][3] = {
    "   ",
    "   ",
    "   ",
    "   ",
    "   "
};

static const char char3x5_dot[5][3] = {
    "   ",
    "   ",
    "   ",
    "   ",
    " * "
};

static const char char3x5_0[5][3] = {
    "***",
    "* *",
    "* *",
    "* *",
    "***"
};

static const char char3x5_1[5][3] = {
    " * ",
    " * ",
    " * ",
    " * ",
    " * "
};

static const char char3x5_2[5][3] = {
    "***",
    "  *",
    "***",
    "*  ",
    "***"
};

static const char char3x5_3[5][3] = {
    "***",
    "  *",
    "***",
    "  *",
    "***"
};

static const char char3x5_4[5][3] = {
    "* *",
    "* *",
    "***",
    "  *",
    "  *"
};
static const char char3x5_5[5][3] = {
    "***",
    "*  ",
    "***",
    "  *",
    "***"
};
static const char char3x5_6[5][3] = {
    "***",
    "*  ",
    "***",
    "* *",
    "***"
};
static const char char3x5_7[5][3] = {
    "***",
    "  *",
    "  *",
    "  *",
    "  *"
};
static const char char3x5_8[5][3] = {
    "***",
    "* *",
    "***",
    "* *",
    "***"
};
static const char char3x5_9[5][3] = {
    "***",
    "* *",
    "***",
    "  *",
    "***"
};

static const char char3x5_A[5][3] = {
    " * ",
    "* *",
    "***",
    "* *",
    "* *"
};
static const char char3x5_B[5][3] = {
    "** ",
    "* *",
    "***",
    "* *",
    "** "
};
static const char char3x5_C[5][3] = {
    " **",
    "*  ",
    "*  ",
    "*  ",
    " **"
};
static const char char3x5_D[5][3] = {
    "***",
    "*  ",
    "*  ",
    "*  ",
    "***"
};
static const char char3x5_E[5][3] = {
    "***",
    "*  ",
    "***",
    "*  ",
    "***"
};
static const char char3x5_F[5][3] = {
    "***",
    "*  ",
    "***",
    "*  ",
    "*  "
};
static const char char3x5_G[5][3] = {
    "***",
    "*  ",
    "***",
    "* *",
    "***"
};
static const char char3x5_H[5][3] = {
    "* *",
    "* *",
    "***",
    "* *",
    "* *"
};
static const char char3x5_I[5][3] = {
    "***",
    " * ",
    " * ",
    " * ",
    "***"
};
static const char char3x5_J[5][3] = {
    "***",
    "  *",
    "  *",
    "  *",
    "** "
};
static const char char3x5_K[5][3] = {
    "* *",
    "** ",
    "*  ",
    "** ",
    "* *"
};
static const char char3x5_L[5][3] = {
    "*  ",
    "*  ",
    "*  ",
    "*  ",
    "***"
};
static const char char3x5_M[5][3] = {
    "* *",
    "***",
    "* *",
    "* *",
    "* *"
};
static const char char3x5_N[5][3] = {
    "* *",
    "***",
    "***",
    "***",
    "* *"
};
static const char char3x5_P[5][3] = {
    "***",
    "* *",
    "***",
    "*  ",
    "*  "
};
static const char char3x5_Q[5][3] = {
    "***",
    "* *",
    "* *",
    "** ",
    "* *"
};
static const char char3x5_R[5][3] = {
    "***",
    "* *",
    "***",
    "** ",
    "* *"
};
static const char char3x5_S[5][3] = {
    "***",
    "*  ",
    "***",
    "  *",
    "***"
};
static const char char3x5_T[5][3] = {
    "***",
    " * ",
    " * ",
    " * ",
    " * "
};
static const char char3x5_U[5][3] = {
    "* *",
    "* *",
    "* *",
    "* *",
    "***"
};
static const char char3x5_V[5][3] = {
    "* *",
    "* *",
    "* *",
    " * ",
    " *"
};
static const char char3x5_W[5][3] = {
    "* *",
    "* *",
    "* *",
    "***",
    "* *"
};
static const char char3x5_X[5][3] = {
    "* *",
    "* *",
    "***",
    "* *",
    "* *"
};
static const char char3x5_Y[5][3] = {
    "* *",
    "***",
    "***",
    "* *",
    "* *"
};
static const char char3x5_Z[5][3] = {
    "***",
    "  *",
    " * ",
    "*  ",
    "***"
};

static const char char3x5_a[5][3] = {
    "   ",
    " **",
    "* *",
    "* *",
    " **"
};
static const char char3x5_b[5][3] = {
    "*  ",
    "** ",
    "* *",
    "* *",
    "** "
};
static const char char3x5_c[5][3] = {
    "   ",
    "***",
    "*  ",
    "*  ",
    "***"
};
static const char char3x5_d[5][3] = {
    "  *",
    " **",
    "* *",
    "* *",
    " **"
};
static const char char3x5_e[5][3] = {
    "   ",
    " * ",
    "* *",
    "** ",
    " **"
};
static const char char3x5_f[5][3] = {
    " **",
    " * ",
    "***",
    " * ",
    " * "
};
static const char char3x5_g[5][3] = {
    "***",
    "* *",
    "***",
    "  *",
    "**"
};
static const char char3x5_h[5][3] = {
    "*  ",
    "** ",
    "* *",
    "* *",
    "* *"
};
static const char char3x5_i[5][3] = {
    " * ",
    "   ",
    " * ",
    " * ",
    " * "
};
static const char char3x5_j[5][3] = {
    " * ",
    "   ",
    " * ",
    " * ",
    "*  "
};
static const char char3x5_k[5][3] = {
    "*  ",
    "* *",
    "** ",
    "* *",
    "* *"
};
static const char char3x5_l[5][3] = {
    "*  ",
    " * ",
    " * ",
    " * ",
    " *"
};
static const char char3x5_m[5][3] = {
    "   ",
    "   ",
    "***",
    "***",
    "* *"
};
static const char char3x5_n[5][3] = {
    "   ",
    "   ",
    "***",
    "* *",
    "* *"
};
static const char char3x5_o[5][3] = {
    "   ",
    "   ",
    "***",
    "* *",
    "***"
};
static const char char3x5_p[5][3] = {
    "   ",
    "***",
    "* *",
    "***",
    "*  "
};
static const char char3x5_q[5][3] = {
    "   ",
    "***",
    "* *",
    "***",
    "  *"
};
static const char char3x5_r[5][3] = {
    "   ",
    "***",
    "* *",
    "* ",
    "*  "
};
static const char char3x5_s[5][3] = {
    "   ",
    " **",
    "*  ",
    "  *",
    "** "
};
static const char char3x5_t[5][3] = {
    " * ",
    "***",
    " * ",
    " * ",
    " **"
};
static const char char3x5_u[5][3] = {
    "   ",
    "   ",
    "* *",
    "* *",
    "***"
};
static const char char3x5_v[5][3] = {
    "   ",
    "* *",
    "* *",
    "* *",
    " * "
};
static const char char3x5_w[5][3] = {
    "   ",
    "* *",
    "***",
    "***",
    "* *"
};
static const char char3x5_x[5][3] = {
    "   ",
    "* *",
    " * ",
    "* *",
    "* *"
};
static const char char3x5_y[5][3] = {
    "   ",
    "* *",
    "* *",
    "***",
    "  *"
};
static const char char3x5_z[5][3] = {
    "   ",
    "***",
    "  *",
    "*  ",
    "***"
};

static const char SmileyCharMap[FLIP_DOT_NOF_ROW][FLIP_DOT_NOF_COL] = {
    "       *****        ",
    "      *     *       ",
    "     *       *      ",
    "    *         *     ",
    "   *           *    ",
    "  *   **   **   *   ",
    "  *   **   **   *   ",
    "  *             *   ",
    "  *   *     *   *   ",
    "   *  *     *  *    ",
    "    *  *   *  *     ",
    "     *  ***  *      ",
    "      *     *       ",
    "       *****        "
};

static const char Smiley2CharMap[FLIP_DOT_NOF_ROW][FLIP_DOT_NOF_COL] = {
    "       *****        ",
    "      *******       ",
    "     *********      ",
    "    ***********     ",
    "   *************    ",
    "  ****  ***  ****   ",
    "  ****  ***  ****   ",
    "  ***************   ",
    "  ***************   ",
    "   *** ***** ***    ",
    "    *** *** ***     ",
    "     ***   ***      ",
    "      *******       ",
    "       *****        "
};


static void SetDot(unsigned int x, unsigned int y) {
  if (x<FLIP_DOT_NOF_COL && y<FLIP_DOT_NOF_ROW) {
    dotMap[x/8][y] |= 1<<(7-x%8);
  }
}

static void ClrDot(unsigned int x, unsigned int y) {
  if (x<FLIP_DOT_NOF_COL && y<FLIP_DOT_NOF_ROW) {
    dotMap[x/8][y] &= ~(1<<(7-x%8));
  }
}

static void PutDot(unsigned int x, unsigned int y, bool on) {
  if (on) {
    SetDot(x, y);
  } else {
    ClrDot(x, y);
  }
}

static bool IsDotSet(unsigned int x, unsigned int y) {
  return dotMap[x/8][y]&(1<<(7-x%8));
}

static void DrawBitMap(const char map[FLIP_DOT_NOF_ROW][FLIP_DOT_NOF_COL]) {
  for(int x=0;x<FLIP_DOT_NOF_COL;x++) {
    for(int y=0;y<FLIP_DOT_NOF_COL;y++) {
      PutDot(x, y, map[y][x]!=' ');
    }
  }
}

static void DrawFontCharMap3x5(int x0, int y0, const char charMap[5][3]) {
  for(int x=0; x<3; x++) {
    for(int y=0; y<5; y++) {
      PutDot(x0+x, y0+y, charMap[y][x]!=' ');
    }
  }
}

static void DrawFontChar3x5(int x0, int y0, char ch) {
  switch(ch) {
    case '0': DrawFontCharMap3x5(x0, y0, char3x5_0);  break;
    case '1': DrawFontCharMap3x5(x0, y0, char3x5_1);  break;
    case '2': DrawFontCharMap3x5(x0, y0, char3x5_2);  break;
    case '3': DrawFontCharMap3x5(x0, y0, char3x5_3);  break;
    case '4': DrawFontCharMap3x5(x0, y0, char3x5_4);  break;
    case '5': DrawFontCharMap3x5(x0, y0, char3x5_5);  break;
    case '6': DrawFontCharMap3x5(x0, y0, char3x5_6);  break;
    case '7': DrawFontCharMap3x5(x0, y0, char3x5_7);  break;
    case '8': DrawFontCharMap3x5(x0, y0, char3x5_8);  break;
    case '9': DrawFontCharMap3x5(x0, y0, char3x5_9);  break;
    case ':': DrawFontCharMap3x5(x0, y0, char3x5_colon);  break;
    case ' ': DrawFontCharMap3x5(x0, y0, char3x5_space);  break;
    case '.': DrawFontCharMap3x5(x0, y0, char3x5_dot);  break;
    case 'A': DrawFontCharMap3x5(x0, y0, char3x5_A);  break;
    case 'B': DrawFontCharMap3x5(x0, y0, char3x5_B);  break;
    case 'C': DrawFontCharMap3x5(x0, y0, char3x5_C);  break;
    case 'D': DrawFontCharMap3x5(x0, y0, char3x5_D);  break;
    case 'E': DrawFontCharMap3x5(x0, y0, char3x5_E);  break;
    case 'F': DrawFontCharMap3x5(x0, y0, char3x5_F);  break;
    case 'G': DrawFontCharMap3x5(x0, y0, char3x5_G);  break;
    case 'H': DrawFontCharMap3x5(x0, y0, char3x5_H);  break;
    case 'I': DrawFontCharMap3x5(x0, y0, char3x5_I);  break;
    case 'J': DrawFontCharMap3x5(x0, y0, char3x5_J);  break;
    case 'K': DrawFontCharMap3x5(x0, y0, char3x5_K);  break;
    case 'L': DrawFontCharMap3x5(x0, y0, char3x5_L);  break;
    case 'M': DrawFontCharMap3x5(x0, y0, char3x5_M);  break;
    case 'N': DrawFontCharMap3x5(x0, y0, char3x5_N);  break;
    case 'O': DrawFontCharMap3x5(x0, y0, char3x5_0);  break;
    case 'P': DrawFontCharMap3x5(x0, y0, char3x5_P);  break;
    case 'Q': DrawFontCharMap3x5(x0, y0, char3x5_Q);  break;
    case 'R': DrawFontCharMap3x5(x0, y0, char3x5_R);  break;
    case 'S': DrawFontCharMap3x5(x0, y0, char3x5_S);  break;
    case 'T': DrawFontCharMap3x5(x0, y0, char3x5_T);  break;
    case 'U': DrawFontCharMap3x5(x0, y0, char3x5_U);  break;
    case 'V': DrawFontCharMap3x5(x0, y0, char3x5_V);  break;
    case 'W': DrawFontCharMap3x5(x0, y0, char3x5_W);  break;
    case 'X': DrawFontCharMap3x5(x0, y0, char3x5_X);  break;
    case 'Y': DrawFontCharMap3x5(x0, y0, char3x5_Y);  break;
    case 'Z': DrawFontCharMap3x5(x0, y0, char3x5_Z);  break;

    case 'a': DrawFontCharMap3x5(x0, y0, char3x5_a);  break;
    case 'b': DrawFontCharMap3x5(x0, y0, char3x5_b);  break;
    case 'c': DrawFontCharMap3x5(x0, y0, char3x5_c);  break;
    case 'd': DrawFontCharMap3x5(x0, y0, char3x5_d);  break;
    case 'e': DrawFontCharMap3x5(x0, y0, char3x5_e);  break;
    case 'f': DrawFontCharMap3x5(x0, y0, char3x5_f);  break;
    case 'g': DrawFontCharMap3x5(x0, y0, char3x5_g);  break;
    case 'h': DrawFontCharMap3x5(x0, y0, char3x5_h);  break;
    case 'i': DrawFontCharMap3x5(x0, y0, char3x5_i);  break;
    case 'j': DrawFontCharMap3x5(x0, y0, char3x5_j);  break;
    case 'k': DrawFontCharMap3x5(x0, y0, char3x5_k);  break;
    case 'l': DrawFontCharMap3x5(x0, y0, char3x5_l);  break;
    case 'm': DrawFontCharMap3x5(x0, y0, char3x5_m);  break;
    case 'n': DrawFontCharMap3x5(x0, y0, char3x5_n);  break;
    case 'o': DrawFontCharMap3x5(x0, y0, char3x5_o);  break;
    case 'p': DrawFontCharMap3x5(x0, y0, char3x5_p);  break;
    case 'q': DrawFontCharMap3x5(x0, y0, char3x5_q);  break;
    case 'r': DrawFontCharMap3x5(x0, y0, char3x5_r);  break;
    case 's': DrawFontCharMap3x5(x0, y0, char3x5_s);  break;
    case 't': DrawFontCharMap3x5(x0, y0, char3x5_t);  break;
    case 'u': DrawFontCharMap3x5(x0, y0, char3x5_u);  break;
    case 'v': DrawFontCharMap3x5(x0, y0, char3x5_v);  break;
    case 'w': DrawFontCharMap3x5(x0, y0, char3x5_w);  break;
    case 'x': DrawFontCharMap3x5(x0, y0, char3x5_x);  break;
    case 'y': DrawFontCharMap3x5(x0, y0, char3x5_y);  break;
    case 'z': DrawFontCharMap3x5(x0, y0, char3x5_z);  break;
    default:
      break;
  } /* switch */
}

static void DrawText3x5(int x0, int y0, const char *text) {
  const char *p = text;
  while(*p != '\0') {
    DrawFontChar3x5(x0, y0, *p);
    p++;
    x0 += 4;
  }
}

void FlipDot_DrawTime3x5(int x0, int y0, uint8_t hour, uint8 minute) {
  DrawFontChar3x5(x0, y0, '0'+hour/10);
  x0 += 4;
  DrawFontChar3x5(x0, y0, '0'+hour%10);
  x0 += 3;
  DrawFontChar3x5(x0, y0, ':');
  x0 += 3;
  DrawFontChar3x5(x0, y0, '0'+minute/10);
  x0 += 4;
  DrawFontChar3x5(x0, y0, '0'+minute%10);
}

void FlipDot_DrawDate3x5(int x0, int y0, uint8_t day, uint8 month, uint16_t year) {
  DrawFontChar3x5(x0, y0, '0'+day/10);
  x0 += 4;
  DrawFontChar3x5(x0, y0, '0'+day%10);
#if 0
  x0 += 3;
  DrawFontChar3x5(x0, y0, '.');
  x0 += 3;
  DrawFontChar3x5(x0, y0, '0'+month/10);
  x0 += 4;
  DrawFontChar3x5(x0, y0, '0'+month%10);
#else
  x0 += 4;
  switch(month) {
    case 1: DrawText3x5(x0, y0, "Jan"); break;
    case 2: DrawText3x5(x0, y0, "Feb"); break;
    case 3: DrawText3x5(x0, y0, "Mar"); break;
    case 4: DrawText3x5(x0, y0, "Apr"); break;
    case 5: DrawText3x5(x0, y0, "May"); break;
    case 6: DrawText3x5(x0, y0, "Jun"); break;
    case 7: DrawText3x5(x0, y0, "Jul"); break;
    case 8: DrawText3x5(x0, y0, "Aug"); break;
    case 9: DrawText3x5(x0, y0, "Sep"); break;
    case 10: DrawText3x5(x0, y0, "Okt"); break;
    case 11: DrawText3x5(x0, y0, "Nov"); break;
    case 12: DrawText3x5(x0, y0, "Dez"); break;
    default: break;
  }
#endif
}

void FlipDot_ClearAllDots(void) {
  for (int x=0; x<FLIP_DOT_NOF_COL; x++) {
    for (int y=0; y<FLIP_DOT_NOF_ROW; y++) {
      ClrDot(x, y);
    }
  }
}

void FlipDot_SetAllDots(void) {
  for (int x=0; x<FLIP_DOT_NOF_COL; x++) {
    for (int y=0; y<FLIP_DOT_NOF_ROW; y++) {
      SetDot(x, y);
    }
  }
}

static void DataDots(uint8_t *buf) {
  /* transform bitmap data into flip dot data */
  static uint16_t rowConst[16] = { /* constant values for rows */
      /* 0 */ 1<<9,
      /* 1 */ 1<<10,
      /* 2 */ 1<<11,
      /* 3 */ 1<<12,
      /* 4 */ 1<<13,
      /* 5 */ 1<<14,
      /* 6 */ 1<<15,
      /* 7 */ 1<<0,
      /* 8 */ 1<<1,
      /* 9 */ 1<<2,
      /* 10 */ 1<<3,
      /* 11 */ 1<<4,
      /* 12 */ 1<<5,
      /* 13 */ 1<<6,
      /* 14 */ 0, /* dummy */
      /* 15 */ 0  /* dummy */
  };
  uint16_t val;

  for(int x=0;x<FLIP_DOT_NOF_COL;x++) {
    val = 0;
    for(int y=0;y<FLIP_DOT_NOF_ROW;y++) {
      if (IsDotSet(x,y)) {
        val |= rowConst[y];
      }
    } /* for y */
    StoreASCIIHex16(&buf[x*4], val);
  } /* for x */
}

void FlipDot_SendDots(void) {
  /* see https://github.com/hawkz/Hanover_Flipdot */
  /* https://cute766.info/adventures-with-flippy-the-flip-dot-display-software-and-teardown/ */
  uint8_t buf[FLIP_DOT_NOF_BUF_BYTES] = {
      0x00, /* SOT */
      0x00, /* command: '0': text message, '1': graphics message, followed by the address of the device */
      0x00, /* address: '1', 'val'+1 ('0' is broadcast) */
      0x00, 0x00, /* how man bytes (20*14+2 /8) 0x32 0x41 => '2' 'A' => 0x2A => 42 bytes => 84 characters */  /* Example: '5' '4' => 0x54 => 84 bytes */
      /* Data: treated column by column, from upper left to lower right */
      0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x30, 0x36, 0x46, 0x43,
      0x37, 0x46, 0x43, 0x30, 0x37, 0x30, 0x30, 0x30, 0x36, 0x30,
      0x30, 0x30, 0x46, 0x38, 0x30, 0x33, 0x46, 0x43, 0x30, 0x37,
      0x43, 0x30, 0x36, 0x30, 0x43, 0x30, 0x36, 0x46, 0x43, 0x30,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x30, 0x36, 0x46, 0x43,
      0x37, 0x46, 0x43, 0x30, 0x37, 0x30, 0x30, 0x30, 0x36, 0x30,
      0x30, 0x30, 0x46, 0x38, 0x30, 0x33, 0x46, 0x43, 0x30, 0x37,
      0x43, 0x30, 0x36, 0x30, 0x43, 0x30, 0x36, 0x46, 0x43, 0x30,
      /* End of data */
      0x00, /* EOT, footer */
      0x00, 0x00   /* checksum */
  };
  buf[FLIP_DOT_BUF_POS_SOT] = 0x02; /* SOT */
  buf[FLIP_DOT_BUF_POS_CMD] = '1'; /* 1: graphics */
  buf[FLIP_DOT_BUF_POS_ADDR] = '0'+FLIP_DOT_DEVICE_ADDRESS+1; /* addr */
  StoreASCIIHex8(&buf[FLIP_DOT_BUF_POS_NOF], FLIP_DOT_NOF_DATA);
  DataDots(&buf[FLIP_DOT_BUF_POS_DATA]); /* data */
  buf[FLIP_DOT_BUF_POS_EOT] = 0x03; /* EOT */
  uint8_t checkSum = calcCheckSum(buf, sizeof(buf));
  StoreASCIIHex8(&buf[FLIP_DOT_BUF_POS_CHECK], checkSum);
  RS485_SendData(buf, sizeof(buf));
  RS485_SendData((unsigned char*)"\n", 1);
}

void FlipDot_Test(void) {
  FlipDot_SetAllDots();
  FlipDot_SendDots();
  vTaskDelay(pdMS_TO_TICKS(500));
  FlipDot_ClearAllDots();
  FlipDot_SendDots();
  vTaskDelay(pdMS_TO_TICKS(500));

  for(int x=0;x<FLIP_DOT_NOF_COL;x++) {
    for(int y=0;y<FLIP_DOT_NOF_ROW;y++) {
      SetDot(x, y);
    } /* for y */
    FlipDot_SendDots();
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for x */

  FlipDot_ClearAllDots();
  for(int y=0;y<FLIP_DOT_NOF_ROW;y++) {
    for(int x=0;x<FLIP_DOT_NOF_COL;x++) {
      SetDot(x, y);
    } /* for y */
    FlipDot_SendDots();
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for x */

#if 0
  for(int x=0;x<FLIP_DOT_NOF_COL;x++) {
    for(int y=0;y<FLIP_DOT_NOF_ROW;y++) {
      SetDot(x, y);
      SendDots();
      //vTaskDelay(pdMS_TO_TICKS(10));
//      ClrDot(x, y);
    } /* for y */
  } /* for x */
  SendDots();
#endif
  DrawBitMap(SmileyCharMap);
  FlipDot_SendDots();
  vTaskDelay(pdMS_TO_TICKS(1000));
  DrawBitMap(Smiley2CharMap);
  FlipDot_SendDots();
}


static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"flipdot", (unsigned char*)"FlipDot settings\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"flipdot", (unsigned char*)"Group of FlipDot commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test", (unsigned char*)"Test\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  clear", (unsigned char*)"Clear display\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  fill", (unsigned char*)"Fill display\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  clock", (unsigned char*)"Show clock\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t FlipDot_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "flipdot help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "flipdot status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "flipdot test")==0) {
    *handled = true;
    FlipDot_Test();
  } else if (McuUtility_strcmp((char*)cmd, "flipdot clear")==0) {
    *handled = true;
    FlipDot_ClearAllDots();
    FlipDot_SendDots();
  } else if (McuUtility_strcmp((char*)cmd, "flipdot fill")==0) {
    *handled = true;
    FlipDot_SetAllDots();
    FlipDot_SendDots();
  } else if (McuUtility_strcmp((char*)cmd, "flipdot clock")==0) {
    *handled = true;
    FlipDot_ClearAllDots();
    FlipDot_DrawTime3x5(1, 1, 12, 34);
    FlipDot_SendDots();

    FlipDot_DrawTime3x5(1, 1, 6, 58);
    FlipDot_SendDots();

    FlipDot_DrawTime3x5(1, 1, 19, 59);
    FlipDot_SendDots();

    FlipDot_DrawDate3x5(0, 8, 1, 6, 2021);
    FlipDot_SendDots();
  }
  return ERR_OK;
}

void FlipDot_Init(void) {
  FlipDot_ClearAllDots();
}
