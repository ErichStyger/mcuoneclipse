/*
 * WS2812B LED driver using FlexIO.
 * Based on the work of Zeljko Stefanovic (many thanks!)
 */

#ifndef __WS2812_H__
#define __WS2812_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>
	
typedef struct {
  uint8_t green;
  uint8_t red;
  uint8_t blue;
} ws2812_control;

extern void WS2812_Init(void);
extern void	WS2812_PinSelect(void);
extern void WS2812_OutputDataDMA(uint32_t * p32_strip_data, uint32_t _strip_data_word_cnt);
	
#ifdef __cplusplus
}
#endif

#endif  /* __WS2812_H__ */
