#include "unicode.h"


size_t strlen_utf8(const char *src) {
    size_t count = 0;
    size_t i = 0;
    size_t src_size = strlen(src);

    while (i < src_size) {
        uint8_t byte = src[i];

        if ((byte & 0x80) == 0) {  // 1-byte UTF-8
            count++;
        } else if ((byte & 0xE0) == 0xC0) {  // 2-byte UTF-8
            count++;
            i++;  // Skip the continuation byte
        } else if ((byte & 0xF0) == 0xE0) {  // 3-byte UTF-8
            count++;
            i += 2;  // Skip the continuation bytes
        } else if ((byte & 0xF8) == 0xF0) {  // 4-byte UTF-8
            count++;
            i += 3;  // Skip the continuation bytes
        } else {
            return -1;  // Invalid UTF-8 byte
        }

        i++;
    }
    return count;
}

size_t ascii_to_utf16le(uint16_t *dist, size_t dist_size, const char *src, size_t src_size) {
    size_t utf16le_pos = 0;

    for (size_t i = 0; i < src_size && src[i] != '\0'; ++i) {
        uint32_t codepoint = (uint32_t)src[i];

        if (utf16le_pos + 1 <= dist_size) {
            dist[utf16le_pos++] = (uint16_t)codepoint;
        } else {
            break;
        }
    }

    if (utf16le_pos < dist_size) {
        dist[utf16le_pos] = '\0';
    }
    return utf16le_pos;
}

// Convert UTF-8 to UTF-16LE and return the length of the converted string
size_t utf8_to_utf16le(uint16_t* dist, size_t dist_size, const char *src, size_t src_size) {
    size_t dist_pos = 0;
    size_t src_pos = 0;

    while (src_pos < src_size && dist_pos < dist_size) {
        uint32_t codepoint = 0;
        size_t extra_bytes = 0;

        uint8_t byte = src[src_pos];

        // Determine the number of bytes for the UTF-8 codepoint
        if ((byte & 0x80) == 0) {  // 1-byte UTF-8
            codepoint = byte;
        } else if ((byte & 0xE0) == 0xC0) {  // 2-byte UTF-8
            codepoint = byte & 0x1F;
            extra_bytes = 1;
        } else if ((byte & 0xF0) == 0xE0) {  // 3-byte UTF-8
            codepoint = byte & 0x0F;
            extra_bytes = 2;
        } else if ((byte & 0xF8) == 0xF0) {  // 4-byte UTF-8
            codepoint = byte & 0x07;
            extra_bytes = 3;
        } else {
            // Invalid UTF-8 byte
            return -1;  // Return -1 to indicate an error
        }

        // Calculate the complete codepoint
        for (size_t j = 0; j < extra_bytes; ++j) {
            src_pos++;
            if (src_pos >= src_size) {
                return -1;  // Incomplete UTF-8 sequence
            }

            byte = src[src_pos];
            if ((byte & 0xC0) != 0x80) {
                return -1;  // Invalid UTF-8 continuation byte
            }

            codepoint = (codepoint << 6) | (byte & 0x3F);
        }

        // Convert to UTF-16LE
        if (codepoint <= 0xFFFF) {  // Basic Multilingual Plane
            if (dist_pos < dist_size) {
                dist[dist_pos++] = (uint16_t)codepoint;
            }
        } else {  // Supplementary Planes (surrogates)
            codepoint -= 0x10000;
            if (dist_pos + 1 < dist_size) {
                dist[dist_pos++] = 0xD800 | ((codepoint >> 10) & 0x3FF);
                dist[dist_pos++] = 0xDC00 | (codepoint & 0x3FF);
                dist_pos += 2;
            } else {
                return -1;  // Not enough space for surrogates
            }
        }

        src_pos++;
    }

    if (dist_pos < dist_size) {
        dist[dist_pos] = 0;  // Null-terminate
    }

    return dist_pos;
}

size_t utf16le_to_utf8(char *dist, size_t buffer_size, const uint16_t *src, size_t len) {
    size_t dist_len = 0;

    for (size_t i = 0; i < len; ++i) {
        uint32_t codepoint = src[i];
        if (codepoint == 0xFFFF) {
            break;
        }

        if (codepoint <= 0x7F) {
            if (dist_len + 1 <= buffer_size) {
                dist[dist_len++] = (uint8_t)codepoint;
            } else {
                break;
            }
        } else if (codepoint <= 0x7FF) {
            if (dist_len + 2 <= buffer_size) {
                dist[dist_len++] = (uint8_t)(0xC0 | (codepoint >> 6));
                dist[dist_len++] = (uint8_t)(0x80 | (codepoint & 0x3F));
            } else {
                break;
            }
        } else if (codepoint <= 0xFFFF) {
            if (dist_len + 3 <= buffer_size) {
                dist[dist_len++] = (uint8_t)(0xE0 | (codepoint >> 12));
                dist[dist_len++] = (uint8_t)(0x80 | ((codepoint >> 6) & 0x3F));
                dist[dist_len++] = (uint8_t)(0x80 | (codepoint & 0x3F));
            } else {
                break;
            }
        } else {
            break;
        }
    }

    if (dist_len < buffer_size) {
        dist[dist_len] = '\0';
    }
    return dist_len;
}
