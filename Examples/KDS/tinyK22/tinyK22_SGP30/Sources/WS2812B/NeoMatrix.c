/*-------------------------------------------------------------------------
  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  -------------------------------------------------------------------------
  This file is part of the Adafruit NeoMatrix library.

  NeoMatrix is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoMatrix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with NeoMatrix.  If not, see
  <http://www.gnu.org/licenses/>.
  -------------------------------------------------------------------------*/

#include "Platform.h"
#include "NeoMatrix.h"
#include "NeoPixel.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"

typedef struct {
  uint8_t type;
  uint8_t matrixWidth, matrixHeight, tilesX, tilesY;
  uint16_t (*remapFn)(uint16_t x, uint16_t y);
  uint32_t passThruColor;
  bool  passThruFlag;
} MATRIX_Matrix;

static MATRIX_Matrix matrix;

#if 0
// Downgrade 24-bit color to 16-bit (add reverse gamma lookup here?)
uint16_t Adafruit_NeoMatrix_Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)(r & 0xF8) << 8) |
         ((uint16_t)(g & 0xFC) << 3) |
                    (b         >> 3);
}

// Pass-through is a kludge that lets you override the current drawing
// color with a 'raw' RGB (or RGBW) value that's issued directly to
// pixel(s), side-stepping the 16-bit color limitation of Adafruit_GFX.
// This is not without some limitations of its own -- for example, it
// won't work in conjunction with the background color feature when
// drawing text or bitmaps (you'll just get a solid rect of color),
// only 'transparent' text/bitmaps.  Also, no gamma correction.
// Remember to UNSET the passthrough color immediately when done with
// it (call with no value)!

// Pass raw color value to set/enable passthrough
void Adafruit_NeoMatrix_setPassThruColor(uint32_t c) {
  matrix.passThruColor = c;
  matrix.passThruFlag  = TRUE;
}
#endif

void Adafruit_NeoMatrix_drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  #define swap(a, b) {uint16_t swapTmp; swapTmp=a; a=b; b=swapTmp;}

  if((x < 0) || (y < 0) || (x >= GDisp1_GetWidth()) || (y >= GDisp1_GetHeight())) return;
  int tileOffset = 0, pixelOffset, val;

  if(matrix.remapFn) { // Custom X/Y remapping function
    pixelOffset = (*matrix.remapFn)(x, y);
  } else {      // Standard single matrix or tiled matrices

    uint8_t  corner = matrix.type & NEO_MATRIX_CORNER;
    uint16_t minor, major, majorScale;

    if(matrix.tilesX) { // Tiled display, multiple matrices
      uint16_t tile;

      minor = x / matrix.matrixWidth;            // Tile # X/Y; presume row major to
      major = y / matrix.matrixHeight,           // start (will swap later if needed)
      x     = x - (minor * matrix.matrixWidth);  // Pixel X/Y within tile
      y     = y - (major * matrix.matrixHeight); // (-* is less math than modulo)

      // Determine corner of entry, flip axes if needed
      if(matrix.type & NEO_TILE_RIGHT)  minor = matrix.tilesX - 1 - minor;
      if(matrix.type & NEO_TILE_BOTTOM) major = matrix.tilesY - 1 - major;

      // Determine actual major axis of tiling
      if((matrix.type & NEO_TILE_AXIS) == NEO_TILE_ROWS) {
        majorScale = matrix.tilesX;
      } else {
        swap(major, minor);
        majorScale = matrix.tilesY;
      }

      // Determine tile number
      if((matrix.type & NEO_TILE_SEQUENCE) == NEO_TILE_PROGRESSIVE) {
        // All tiles in same order
        tile = major * majorScale + minor;
      } else {
        // Zigzag; alternate rows change direction.  On these rows,
        // this also flips the starting corner of the matrix for the
        // pixel math later.
        if(major & 1) {
          corner ^= NEO_MATRIX_CORNER;
          tile = (major + 1) * majorScale - 1 - minor;
        } else {
          tile =  major      * majorScale     + minor;
        }
      }

      // Index of first pixel in tile
      tileOffset = tile * matrix.matrixWidth * matrix.matrixHeight;

    } // else no tiling (handle as single tile)

    // Find pixel number within tile
    minor = x; // Presume row major to start (will swap later if needed)
    major = y;

    // Determine corner of entry, flip axes if needed
    if(corner & NEO_MATRIX_RIGHT)  minor = matrix.matrixWidth  - 1 - minor;
    if(corner & NEO_MATRIX_BOTTOM) major = matrix.matrixHeight - 1 - major;

    // Determine actual major axis of matrix
    if((matrix.type & NEO_MATRIX_AXIS) == NEO_MATRIX_ROWS) {
      majorScale = matrix.matrixWidth;
    } else {
      swap(major, minor);
      majorScale = matrix.matrixHeight;
    }

    // Determine pixel number within tile/matrix
    if((matrix.type & NEO_MATRIX_SEQUENCE) == NEO_MATRIX_PROGRESSIVE) {
      // All lines in same order
      pixelOffset = major * majorScale + minor;
    } else {
      // Zigzag; alternate rows change direction.
      if(major & 1) pixelOffset = (major + 1) * majorScale - 1 - minor;
      else          pixelOffset =  major      * majorScale     + minor;
    }
  }
  val = tileOffset+pixelOffset; /* overall index in matrix */
  NEO_SetPixelRGB(val/NEO_NOF_LEDS_IN_LANE, val%NEO_NOF_LEDS_IN_LANE, red, green, blue);
  //NEO_SetPixelRGB(0, tileOffset + pixelOffset, red, green, blue); /* single lane version */
}

void MATRIX_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
  GDisp1_PixelDim x, y;
  uint8_t buf[16];

  (void)hour;
  NEO_ClearAllPixel();

  buf[0] = '\0';
  UTIL1_strcatNum16uFormatted(buf, sizeof(buf), min, '0', 2);
  UTIL1_chcat(buf, sizeof(buf), ':');
  x = 0; y = 0;
  FDisp1_WriteString(buf, 0x001100, &x, &y, GFONT1_GetFont());

  buf[0] = '\0';
  UTIL1_strcatNum16uFormatted(buf, sizeof(buf), sec, '0', 2);
  x = 3; y = 8;
  FDisp1_WriteString(buf, 0x001100, &x, &y, GFONT1_GetFont());

  NEO_TransferPixels();
}

#if 0
static void FontTest(void) {
  GDisp1_PixelDim x, y;
  uint16_t i;
  uint8_t buf1[8], buf2[8];

  for(i=0;i<15;i++) {
    x = y = 0;
    UTIL1_Num16uToStr(buf1, sizeof(buf1), 150+i*10);
    FDisp1_WriteString(buf1, 0x002200, &x, &y, GFONT1_GetFont());
    x = 0; y = 8;
    UTIL1_Num16uToStr(buf2, sizeof(buf2), 20+i*5);
    FDisp1_WriteString(buf2, 0x112211, &x, &y, GFONT1_GetFont());
    NEO_TransferPixels();
    WAIT1_Waitms(1000);
    /* clear */
    x = y = 0;
    FDisp1_WriteString(buf1, 0x000000, &x, &y, GFONT1_GetFont());
    x = 0; y = 8;
    FDisp1_WriteString(buf2, 0x000000, &x, &y, GFONT1_GetFont());
  }
}

void MATRIX_Test(void) {
  int x, y;

  //GDisp1_PutPixel(0,0,0xFF0000);
  //GDisp1_PutPixel(8,0,0xFFFF00);
  //GDisp1_PutPixel(0,8,0xFF00FF);
  //GDisp1_PutPixel(8,8,0x00FF00);
  FontTest();
#if 0
  for (x=0; x<GDisp1_GetWidth(); x++) {
    for(y=0; y<GDisp1_GetHeight(); y++) {
      //Adafruit_NeoMatrix_drawPixel(x, y, 0xff/4, 0x0, 0x0);
      GDisp1_PutPixel(x, y, 0xff0000);
      NEO_TransferPixels();
      WAIT1_Waitms(10);
      //Adafruit_NeoMatrix_drawPixel(x, y, 0x0, 0x0, 0x0);
      GDisp1_PutPixel(x, y, 0);
    }
  }
#endif
}
#endif

void MATRIX_Init(void) {
  /* note: the x/y first pixel (0,0) is always on top left, with x to the right and y to the bottom */
#if 0
  /* single Adafruit 8x8 matrix. Orientation is DIN first pixel is top-left */
  matrix.type =
        NEO_MATRIX_TOP  // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_LEFT // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_ROWS // axis, pixels are organized in  NEO_MATRIX_ROWS or NEO_MATRIX_COLUMNS
      + NEO_MATRIX_PROGRESSIVE // sequence, pixels either change side NEO_MATRIX_PROGRESSIVE or NEO_MATRIX_ZIGZAG
      ;
#elif 0
  /* single Adafruit 8x8 matrix. Orientation is DIN first pixel is bottom-left */
  matrix.type =
        NEO_MATRIX_BOTTOM  // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_LEFT // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_COLUMNS // axis, pixels are organized in  NEO_MATRIX_ROWS or NEO_MATRIX_COLUMNS
      + NEO_MATRIX_PROGRESSIVE // sequence, pixels either change side NEO_MATRIX_PROGRESSIVE or NEO_MATRIX_ZIGZAG
      ;
#elif 1
  /* three Adafruit 8x8 matrix. Orientation is DIN first pixel is top-left, with x going to the right and y going to the bottom */
  matrix.type =
        NEO_MATRIX_TOP  // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_LEFT // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_ROWS // axis, pixels are organized in  NEO_MATRIX_ROWS or NEO_MATRIX_COLUMNS
      + NEO_MATRIX_PROGRESSIVE // sequence, pixels either change side NEO_MATRIX_PROGRESSIVE or NEO_MATRIX_ZIGZAG
      /* tile configuration */
      + NEO_TILE_TOP    // corner, position of first tile: NEO_TILE_TOP or NEO_TILE_BOTTOM
      + NEO_TILE_LEFT   // corner, position of first tile: NEO_TILE_LEFT or NEO_TILE_RIGHT
      + NEO_TILE_ROWS   // axis, organization of tiles: NEO_TILE_ROWS or NEO_TILE_COLUMNS
      + NEO_TILE_PROGRESSIVE // sequence, organization of tiles: NEO_TILE_PROGRESSIVE or NEO_TILE_ZIGZAG
      ;
#elif 0
  /* two Adafruit 8x8 matrix. Orientation is DIN first pixel is bottom-left */
  matrix.type =
        NEO_MATRIX_BOTTOM  // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_LEFT // corner, first pixel: either NEO_MATRIX_TOP or NEO_MATRIX_BOTTOM
      + NEO_MATRIX_COLUMNS // axis, pixels are organized in  NEO_MATRIX_ROWS or NEO_MATRIX_COLUMNS
      + NEO_MATRIX_PROGRESSIVE // sequence, pixels either change side NEO_MATRIX_PROGRESSIVE or NEO_MATRIX_ZIGZAG
      /* tile configuration */
      + NEO_TILE_TOP    // corner, position of first tile: NEO_TILE_TOP or NEO_TILE_BOTTOM
      + NEO_TILE_LEFT   // corner, position of first tile: NEO_TILE_LEFT or NEO_TILE_RIGHT
      + NEO_TILE_ROWS   // axis, organization of tiles: NEO_TILE_ROWS or NEO_TILE_COLUMNS
      + NEO_TILE_PROGRESSIVE // sequence, organization of tiles: NEO_TILE_PROGRESSIVE or NEO_TILE_ZIGZAG
      ;
#else
  matrix.type = NEO_MATRIX_TOP+NEO_MATRIX_LEFT+NEO_MATRIX_ROWS+NEO_MATRIX_PROGRESSIVE
                +NEO_TILE_TOP+NEO_TILE_LEFT+NEO_TILE_COLUMNS+NEO_TILE_ZIGZAG;
#endif
  matrix.matrixWidth = 8; /* size of *each* matrix */
  matrix.matrixHeight = 8; /* size of *each* matrix */
  matrix.tilesX = GDisp1_GetWidth()/8; /* number of tiles in X direction */
  matrix.tilesY = GDisp1_GetHeight()/8; /* number of tiles in Y direction */
  matrix.remapFn = NULL; /* remapping function */
  matrix.passThruColor = 0;
  matrix.passThruFlag = FALSE;
}
