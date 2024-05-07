#ifndef PICO_LITTLEFS_USB_UNICODE_H_
#define PICO_LITTLEFS_USB_UNICODE_H_

#include <string.h>
#include <stdint.h>


size_t strlen_utf8(const char *src);
size_t strlen_utf16le(const uint16_t* str, size_t size);
size_t ascii_to_utf16le(uint16_t *dist, size_t dist_size, const char *src, size_t src_size);
size_t utf8_to_utf16le(uint16_t *dist, size_t dist_size, const char *src, size_t src_size);
size_t utf16le_to_utf8(char *dist, size_t buffer_size, const uint16_t *src, size_t len);

#endif
