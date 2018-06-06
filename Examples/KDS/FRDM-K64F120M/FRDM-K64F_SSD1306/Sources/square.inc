
/*******************************************************************************
* image
* filename: P:/KDS/FRDM-K64F120M/FRDM-K64F_SSD1306/Sources/square.xml
* name: square
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Threshold Dither 0
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_square[48] = {
    0x00, 0x00, 0x00, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x7f, 0xff, 0xfe, 
    0x00, 0x00, 0x00
};
const tImage square = { image_data_square, 24, 16,
    8 };

