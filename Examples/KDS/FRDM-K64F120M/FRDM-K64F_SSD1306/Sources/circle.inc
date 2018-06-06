/*
Graphics data created with GLCD_Convert developed by Konstantinos Halakatevakis.
Looking for cool displays? Visit "http://www.Display3000.com"
*/
#define PROGMEM /* nothing */

const unsigned char Table_Circle[4] PROGMEM = {
0x00, 0x00, 0xFF, 0xFF
};


/* Color mode byte:

Bit     0:    0    --> Compression on
              1    --> Compression off

Bit 1 - 4:    0000 --> 65536 colors
              0001 --> 4096 colors
              0010 --> 256 colors
              0011 --> Palette mode 256 - 32 colors (1 byte = 1 pixel)
              0100 --> Palette mode 16 - 8   colors (1 byte = 2 pixel)
              0101 --> Palette mode 4        colors (1 byte = 4 pixel)
              0110 --> Palette mode 2        colors (1 byte = 8 pixel)
              0111 --> Monochrome mode - Vertical orientation
              1000 --> Monochrome mode - Horizontal orientation
              1001 --> Reserved
              1010 --> Reserved
              1011 --> Reserved
              1100 --> Reserved
              1101 --> Reserved
              1110 --> Reserved
              1111 --> Reserved

Bit 5 - 7:    Reserved

Bit 8 - 10:   000  --> 256 colors or no palette
              001  --> 128 colors
              010  --> 64 colors
              011  --> 32 colors
              100  --> 16 colors
              101  --> 8 colors
              110  --> 4 colors
              111  --> 2 colors

Bit 11 - 15:  Reserved

*/


const unsigned char Circle[86] PROGMEM = {
/* Image dimensions: (W x H) */
0x00, 0x1D, 0x00, 0x16,

/* Color mode */
0x07, 0x0C,

/* Data */
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xF8, 0x00, 0x03, 0xFF, 0x80,
0x00, 0x0F, 0xF8, 0x00, 0x00, 0x3F, 0x80, 0x7F, 0x00, 0xFC, 0x0F, 0xFE, 0x07, 0xC0, 0xFF, 0xF8,
0x1E, 0x0F, 0xFF, 0xE0, 0xF0, 0x7F, 0xFF, 0x07, 0x83, 0xFF, 0xF8, 0x3C, 0x0F, 0xFF, 0x81, 0xF0,
0x3F, 0xF8, 0x1F, 0x80, 0x7F, 0x00, 0xFE, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0xFF, 0xE0, 0x00,
0x0F, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xC0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC
};
