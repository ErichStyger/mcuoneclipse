#ifndef __MEMORY_H__
#define __MEMORY_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

   
int memory_init(void);
int memory_erase(uint32_t addr, uint32_t len);
int memory_write(uint32_t addr, uint8_t *buf, uint32_t len);
int memory_read(uint32_t addr, uint8_t *buf, uint32_t len);
int memory_copy(uint32_t to, uint32_t from, uint32_t len);
int memory_flash_read(uint32_t addr, uint8_t *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif


