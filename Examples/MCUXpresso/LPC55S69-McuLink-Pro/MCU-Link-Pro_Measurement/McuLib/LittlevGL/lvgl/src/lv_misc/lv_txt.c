/**
 * @file lv_text.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_txt.h"
#include "lv_math.h"

/*********************
 *      DEFINES
 *********************/
#define NO_BREAK_FOUND UINT32_MAX

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static inline bool is_break_char(uint32_t letter);

#if LV_TXT_ENC == LV_TXT_ENC_UTF8
static uint8_t lv_txt_utf8_size(const char * str);
static uint32_t lv_txt_unicode_to_utf8(uint32_t letter_uni);
static uint32_t lv_txt_utf8_conv_wc(uint32_t c);
static uint32_t lv_txt_utf8_next(const char * txt, uint32_t * i);
static uint32_t lv_txt_utf8_prev(const char * txt, uint32_t * i_start);
static uint32_t lv_txt_utf8_get_byte_id(const char * txt, uint32_t utf8_id);
static uint32_t lv_txt_utf8_get_char_id(const char * txt, uint32_t byte_id);
static uint32_t lv_txt_utf8_get_length(const char * txt);
#elif LV_TXT_ENC == LV_TXT_ENC_ASCII
static uint8_t lv_txt_iso8859_1_size(const char * str);
static uint32_t lv_txt_unicode_to_iso8859_1(uint32_t letter_uni);
static uint32_t lv_txt_iso8859_1_conv_wc(uint32_t c);
static uint32_t lv_txt_iso8859_1_next(const char * txt, uint32_t * i);
static uint32_t lv_txt_iso8859_1_prev(const char * txt, uint32_t * i_start);
static uint32_t lv_txt_iso8859_1_get_byte_id(const char * txt, uint32_t utf8_id);
static uint32_t lv_txt_iso8859_1_get_char_id(const char * txt, uint32_t byte_id);
static uint32_t lv_txt_iso8859_1_get_length(const char * txt);
#endif
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
uint8_t (*lv_txt_encoded_size)(const char *)                   = lv_txt_utf8_size;
uint32_t (*lv_txt_unicode_to_encoded)(uint32_t)                = lv_txt_unicode_to_utf8;
uint32_t (*lv_txt_encoded_conv_wc)(uint32_t)                   = lv_txt_utf8_conv_wc;
uint32_t (*lv_txt_encoded_next)(const char *, uint32_t *)      = lv_txt_utf8_next;
uint32_t (*lv_txt_encoded_prev)(const char *, uint32_t *)      = lv_txt_utf8_prev;
uint32_t (*lv_txt_encoded_get_byte_id)(const char *, uint32_t) = lv_txt_utf8_get_byte_id;
uint32_t (*lv_encoded_get_char_id)(const char *, uint32_t)     = lv_txt_utf8_get_char_id;
uint32_t (*lv_txt_get_encoded_length)(const char *)            = lv_txt_utf8_get_length;
#elif LV_TXT_ENC == LV_TXT_ENC_ASCII
uint8_t (*lv_txt_encoded_size)(const char *)                   = lv_txt_iso8859_1_size;
uint32_t (*lv_txt_unicode_to_encoded)(uint32_t)                = lv_txt_unicode_to_iso8859_1;
uint32_t (*lv_txt_encoded_conv_wc)(uint32_t)                   = lv_txt_iso8859_1_conv_wc;
uint32_t (*lv_txt_encoded_next)(const char *, uint32_t *)      = lv_txt_iso8859_1_next;
uint32_t (*lv_txt_encoded_prev)(const char *, uint32_t *)      = lv_txt_iso8859_1_prev;
uint32_t (*lv_txt_encoded_get_byte_id)(const char *, uint32_t) = lv_txt_iso8859_1_get_byte_id;
uint32_t (*lv_encoded_get_char_id)(const char *, uint32_t)     = lv_txt_iso8859_1_get_char_id;
uint32_t (*lv_txt_get_encoded_length)(const char *)            = lv_txt_iso8859_1_get_length;

#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Get size of a text
 * @param size_res pointer to a 'point_t' variable to store the result
 * @param text pointer to a text
 * @param font pinter to font of the text
 * @param letter_space letter space of the text
 * @param txt.line_space line space of the text
 * @param flags settings for the text from 'txt_flag_t' enum
 * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid
 * line breaks
 */
void lv_txt_get_size(lv_point_t * size_res, const char * text, const lv_font_t * font, lv_coord_t letter_space,
                     lv_coord_t line_space, lv_coord_t max_width, lv_txt_flag_t flag)
{
    size_res->x = 0;
    size_res->y = 0;

    if(text == NULL) return;
    if(font == NULL) return;

    if(flag & LV_TXT_FLAG_EXPAND) max_width = LV_COORD_MAX;

    uint32_t line_start     = 0;
    uint32_t new_line_start = 0;
    lv_coord_t act_line_length;
    uint8_t letter_height = lv_font_get_line_height(font);

    /*Calc. the height and longest line*/
    while(text[line_start] != '\0') {
        new_line_start += lv_txt_get_next_line(&text[line_start], font, letter_space, max_width, flag);
        size_res->y += letter_height;
        size_res->y += line_space;

        /*Calculate the the longest line*/
        act_line_length = lv_txt_get_width(&text[line_start], new_line_start - line_start, font, letter_space, flag);

        size_res->x = LV_MATH_MAX(act_line_length, size_res->x);
        line_start  = new_line_start;
    }

    /*Ma ke the text one line taller if the last character is '\n' or '\r'*/
    if((line_start != 0) && (text[line_start - 1] == '\n' || text[line_start - 1] == '\r')) {
        size_res->y += letter_height + line_space;
    }

    /*Correction with the last line space or set the height manually if the text is empty*/
    if(size_res->y == 0)
        size_res->y = letter_height;
    else
        size_res->y -= line_space;
}

/**
 * Get the next line of text. Check line length and break chars too.
 * @param txt a '\0' terminated string
 * @param font pointer to a font
 * @param letter_space letter space
 * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid line breaks
 * @param flags settings for the text from 'txt_flag_type' enum
 * @return the index of the first char of the new line (in byte index not letter index. With UTF-8 they are different)
 */
uint16_t lv_txt_get_next_line(const char * txt, const lv_font_t * font, lv_coord_t letter_space, lv_coord_t max_width,
                              lv_txt_flag_t flag)
{
    if(txt == NULL) return 0;
    if(font == NULL) return 0;

    if(flag & LV_TXT_FLAG_EXPAND) max_width = LV_COORD_MAX;

    uint32_t i                   = 0;
    uint32_t i_next              = 0;
    lv_coord_t cur_w             = 0;
    uint32_t last_break          = NO_BREAK_FOUND;
    lv_txt_cmd_state_t cmd_state = LV_TXT_CMD_STATE_WAIT;
    uint32_t letter_w;
    uint32_t letter      = 0;
    uint32_t letter_next = 0;

    letter_next = lv_txt_encoded_next(txt, &i_next);

    while(txt[i] != '\0') {
        letter      = letter_next;
        i           = i_next;
        letter_next = lv_txt_encoded_next(txt, &i_next);

        /*Handle the recolor command*/
        if((flag & LV_TXT_FLAG_RECOLOR) != 0) {
            if(lv_txt_is_cmd(&cmd_state, letter) != false) {
                continue; /*Skip the letter is it is part of a command*/
            }
        }

        /*Check for new line chars*/
        if(letter == '\n' || letter == '\r') {
            /*Return with the first letter of the next line*/
            if(letter == '\r' && letter_next == '\n')
                return i_next;
            else
                return i;
        } else { /*Check the actual length*/
            letter_w = lv_font_get_glyph_width(font, letter, letter_next);
            cur_w += letter_w;

            /*If the txt is too long then finish, this is the line end*/
            if(cur_w > max_width) {
                /*If a break character was already found break there*/
                if(last_break != NO_BREAK_FOUND) {
                    i = last_break;
                } else {
                    /* Now this character is out of the area so it will be first character of the next line*/
                    /* But 'i' already points to the next character (because of lv_txt_utf8_next) step beck one*/
                    lv_txt_encoded_prev(txt, &i);
                }

                /* Do not let to return without doing nothing.
                 * Find at least one character (Avoid infinite loop )*/
                if(i == 0) lv_txt_encoded_next(txt, &i);

                return i;
            }
            /*If this char still can fit to this line then check if
             * txt can be broken here later */
            else if(is_break_char(letter)) {
                last_break = i; /*Save the first char index after break*/
            }
        }

        if(letter_w > 0) {
            cur_w += letter_space;
        }
    }

    return i;
}

/**
 * Give the length of a text with a given font
 * @param txt a '\0' terminate string
 * @param length length of 'txt' in byte count and not characters (Á is 1 character but 2 bytes in
 * UTF-8)
 * @param font pointer to a font
 * @param letter_space letter space
 * @param flags settings for the text from 'txt_flag_t' enum
 * @return length of a char_num long text
 */
lv_coord_t lv_txt_get_width(const char * txt, uint16_t length, const lv_font_t * font, lv_coord_t letter_space,
                            lv_txt_flag_t flag)
{
    if(txt == NULL) return 0;
    if(font == NULL) return 0;

    uint32_t i                   = 0;
    lv_coord_t width             = 0;
    lv_txt_cmd_state_t cmd_state = LV_TXT_CMD_STATE_WAIT;
    uint32_t letter;
    uint32_t letter_next;

    if(length != 0) {
        while(i < length) {
            letter      = lv_txt_encoded_next(txt, &i);
            letter_next = lv_txt_encoded_next(&txt[i], NULL);
            if((flag & LV_TXT_FLAG_RECOLOR) != 0) {
                if(lv_txt_is_cmd(&cmd_state, letter) != false) {
                    continue;
                }
            }

            lv_coord_t char_width = lv_font_get_glyph_width(font, letter, letter_next);
            if(char_width > 0) {
                width += char_width;
                width += letter_space;
            }
        }

        if(width > 0) {
            width -= letter_space; /*Trim the last letter space. Important if the text is center
                                      aligned */
        }
    }

    return width;
}

/**
 * Check next character in a string and decide if the character is part of the command or not
 * @param state pointer to a txt_cmd_state_t variable which stores the current state of command
 * processing (Initied. to TXT_CMD_STATE_WAIT )
 * @param c the current character
 * @return true: the character is part of a command and should not be written,
 *         false: the character should be written
 */
bool lv_txt_is_cmd(lv_txt_cmd_state_t * state, uint32_t c)
{
    bool ret = false;

    if(c == (uint32_t)LV_TXT_COLOR_CMD[0]) {
        if(*state == LV_TXT_CMD_STATE_WAIT) { /*Start char*/
            *state = LV_TXT_CMD_STATE_PAR;
            ret    = true;
        }
        /*Other start char in parameter is escaped cmd. char */
        else if(*state == LV_TXT_CMD_STATE_PAR) {
            *state = LV_TXT_CMD_STATE_WAIT;
        }
        /*Command end */
        else if(*state == LV_TXT_CMD_STATE_IN) {
            *state = LV_TXT_CMD_STATE_WAIT;
            ret    = true;
        }
    }

    /*Skip the color parameter and wait the space after it*/
    if(*state == LV_TXT_CMD_STATE_PAR) {
        if(c == ' ') {
            *state = LV_TXT_CMD_STATE_IN; /*After the parameter the text is in the command*/
        }
        ret = true;
    }

    return ret;
}

/**
 * Insert a string into an other
 * @param txt_buf the original text (must be big enough for the result text)
 * @param pos position to insert. Expressed in character index and not byte index (Different in
 * UTF-8) 0: before the original text, 1: after the first char etc.
 * @param ins_txt text to insert
 */
void lv_txt_ins(char * txt_buf, uint32_t pos, const char * ins_txt)
{
    uint32_t old_len = strlen(txt_buf);
    uint32_t ins_len = strlen(ins_txt);
    uint32_t new_len = ins_len + old_len;
    pos              = lv_txt_encoded_get_byte_id(txt_buf, pos); /*Convert to byte index instead of letter index*/

    /*Copy the second part into the end to make place to text to insert*/
    uint32_t i;
    for(i = new_len; i >= pos + ins_len; i--) {
        txt_buf[i] = txt_buf[i - ins_len];
    }

    /* Copy the text into the new space*/
    memcpy(txt_buf + pos, ins_txt, ins_len);
}

/**
 * Delete a part of a string
 * @param txt string to modify
 * @param pos position where to start the deleting (0: before the first char, 1: after the first
 * char etc.)
 * @param len number of characters to delete
 */
void lv_txt_cut(char * txt, uint32_t pos, uint32_t len)
{

    uint32_t old_len = strlen(txt);

    pos = lv_txt_encoded_get_byte_id(txt, pos); /*Convert to byte index instead of letter index*/
    len = lv_txt_encoded_get_byte_id(&txt[pos], len);

    /*Copy the second part into the end to make place to text to insert*/
    uint32_t i;
    for(i = pos; i <= old_len - len; i++) {
        txt[i] = txt[i + len];
    }
}

#if LV_TXT_ENC == LV_TXT_ENC_UTF8
/*******************************
 *   UTF-8 ENCODER/DECOER
 ******************************/

/**
 * Give the size of an UTF-8 coded character
 * @param str pointer to a character in a string
 * @return length of the UTF-8 character (1,2,3 or 4). O on invalid code
 */
static uint8_t lv_txt_utf8_size(const char * str)
{
    if((str[0] & 0x80) == 0)
        return 1;
    else if((str[0] & 0xE0) == 0xC0)
        return 2;
    else if((str[0] & 0xF0) == 0xE0)
        return 3;
    else if((str[0] & 0xF8) == 0xF0)
        return 4;
    return 1; /*If the char was invalid step tell it's 1 byte long*/
}

/**
 * Convert an Unicode letter to UTF-8.
 * @param letter_uni an Unicode letter
 * @return UTF-8 coded character in Little Endian to be compatible with C chars (e.g. 'Á', 'Ű')
 */
static uint32_t lv_txt_unicode_to_utf8(uint32_t letter_uni)
{
    if(letter_uni < 128) return letter_uni;
    uint8_t bytes[4];

    if(letter_uni < 0x0800) {
        bytes[0] = ((letter_uni >> 6) & 0x1F) | 0xC0;
        bytes[1] = ((letter_uni >> 0) & 0x3F) | 0x80;
        bytes[2] = 0;
        bytes[3] = 0;
    } else if(letter_uni < 0x010000) {
        bytes[0] = ((letter_uni >> 12) & 0x0F) | 0xE0;
        bytes[1] = ((letter_uni >> 6) & 0x3F) | 0x80;
        bytes[2] = ((letter_uni >> 0) & 0x3F) | 0x80;
        bytes[3] = 0;
    } else if(letter_uni < 0x110000) {
        bytes[0] = ((letter_uni >> 18) & 0x07) | 0xF0;
        bytes[1] = ((letter_uni >> 12) & 0x3F) | 0x80;
        bytes[2] = ((letter_uni >> 6) & 0x3F) | 0x80;
        bytes[3] = ((letter_uni >> 0) & 0x3F) | 0x80;
    }

    uint32_t * res_p = (uint32_t *)bytes;
    return *res_p;
}

/**
 * Convert a wide character, e.g. 'Á' little endian to be UTF-8 compatible
 * @param c a wide character or a  Little endian number
 * @return `c` in big endian
 */
static uint32_t lv_txt_utf8_conv_wc(uint32_t c)
{
    /*Swap the bytes (UTF-8 is big endian, but the MCUs are little endian)*/
    if((c & 0x80) != 0) {
        uint32_t swapped;
        uint8_t c8[4];
        memcpy(c8, &c, 4);
        swapped = (c8[0] << 24) + (c8[1] << 16) + (c8[2] << 8) + (c8[3]);
        uint8_t i;
        for(i = 0; i < 4; i++) {
            if((swapped & 0xFF) == 0)
                swapped = (swapped >> 8); /*Ignore leading zeros (they were in the end originally)*/
        }
        c = swapped;
    }

    return c;
}

/**
 * Decode an UTF-8 character from a string.
 * @param txt pointer to '\0' terminated string
 * @param i start byte index in 'txt' where to start.
 *          After call it will point to the next UTF-8 char in 'txt'.
 *          NULL to use txt[0] as index
 * @return the decoded Unicode character or 0 on invalid UTF-8 code
 */
static uint32_t lv_txt_utf8_next(const char * txt, uint32_t * i)
{
    /* Unicode to UTF-8
     * 00000000 00000000 00000000 0xxxxxxx -> 0xxxxxxx
     * 00000000 00000000 00000yyy yyxxxxxx -> 110yyyyy 10xxxxxx
     * 00000000 00000000 zzzzyyyy yyxxxxxx -> 1110zzzz 10yyyyyy 10xxxxxx
     * 00000000 000wwwzz zzzzyyyy yyxxxxxx -> 11110www 10zzzzzz 10yyyyyy 10xxxxxx
     * */

    uint32_t result = 0;

    /*Dummy 'i' pointer is required*/
    uint32_t i_tmp = 0;
    if(i == NULL) i = &i_tmp;

    /*Normal ASCII*/
    if((txt[*i] & 0x80) == 0) {
        result = txt[*i];
        (*i)++;
    }
    /*Real UTF-8 decode*/
    else {
        /*2 bytes UTF-8 code*/
        if((txt[*i] & 0xE0) == 0xC0) {
            result = (uint32_t)(txt[*i] & 0x1F) << 6;
            (*i)++;
            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += (txt[*i] & 0x3F);
            (*i)++;
        }
        /*3 bytes UTF-8 code*/
        else if((txt[*i] & 0xF0) == 0xE0) {
            result = (uint32_t)(txt[*i] & 0x0F) << 12;
            (*i)++;

            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += (uint32_t)(txt[*i] & 0x3F) << 6;
            (*i)++;

            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += (txt[*i] & 0x3F);
            (*i)++;
        }
        /*4 bytes UTF-8 code*/
        else if((txt[*i] & 0xF8) == 0xF0) {
            result = (uint32_t)(txt[*i] & 0x07) << 18;
            (*i)++;

            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += (uint32_t)(txt[*i] & 0x3F) << 12;
            (*i)++;

            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += (uint32_t)(txt[*i] & 0x3F) << 6;
            (*i)++;

            if((txt[*i] & 0xC0) != 0x80) return 0; /*Invalid UTF-8 code*/
            result += txt[*i] & 0x3F;
            (*i)++;
        } else {
            (*i)++; /*Not UTF-8 char. Go the next.*/
        }
    }
    return result;
}

/**
 * Get previous UTF-8 character form a string.
 * @param txt pointer to '\0' terminated string
 * @param i start byte index in 'txt' where to start. After the call it will point to the previous
 * UTF-8 char in 'txt'.
 * @return the decoded Unicode character or 0 on invalid UTF-8 code
 */
static uint32_t lv_txt_utf8_prev(const char * txt, uint32_t * i)
{
    uint8_t c_size;
    uint8_t cnt = 0;

    /*Try to find a !0 long UTF-8 char by stepping one character back*/
    (*i)--;
    do {
        if(cnt >= 4) return 0; /*No UTF-8 char found before the initial*/

        c_size = lv_txt_encoded_size(&txt[*i]);
        if(c_size == 0) {
            if(*i != 0)
                (*i)--;
            else
                return 0;
        }
        cnt++;
    } while(c_size == 0);

    uint32_t i_tmp  = *i;
    uint32_t letter = lv_txt_encoded_next(txt, &i_tmp); /*Character found, get it*/

    return letter;
}

/**
 * Convert a character index (in an UTF-8 text) to byte index.
 * E.g. in "AÁRT" index of 'R' is 2th char but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param utf8_id character index
 * @return byte index of the 'utf8_id'th letter
 */
static uint32_t lv_txt_utf8_get_byte_id(const char * txt, uint32_t utf8_id)
{
    uint32_t i;
    uint32_t byte_cnt = 0;
    for(i = 0; i < utf8_id; i++) {
        byte_cnt += lv_txt_encoded_size(&txt[byte_cnt]);
    }

    return byte_cnt;
}

/**
 * Convert a byte index (in an UTF-8 text) to character index.
 * E.g. in "AÁRT" index of 'R' is 2th char but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param byte_id byte index
 * @return character index of the letter at 'byte_id'th position
 */
static uint32_t lv_txt_utf8_get_char_id(const char * txt, uint32_t byte_id)
{
    uint32_t i        = 0;
    uint32_t char_cnt = 0;

    while(i < byte_id) {
        lv_txt_encoded_next(txt, &i); /*'i' points to the next letter so use the prev. value*/
        char_cnt++;
    }

    return char_cnt;
}

/**
 * Get the number of characters (and NOT bytes) in a string. Decode it with UTF-8 if enabled.
 * E.g.: "ÁBC" is 3 characters (but 4 bytes)
 * @param txt a '\0' terminated char string
 * @return number of characters
 */
static uint32_t lv_txt_utf8_get_length(const char * txt)
{
    uint32_t len = 0;
    uint32_t i   = 0;

    while(txt[i] != '\0') {
        lv_txt_encoded_next(txt, &i);
        len++;
    }

    return len;
}

#elif LV_TXT_ENC == LV_TXT_ENC_ASCII
/*******************************
 *  ASCII ENCODER/DECOER
 ******************************/

/**
 * Give the size of an ISO8859-1 coded character
 * @param str pointer to a character in a string
 * @return length of the UTF-8 character (1,2,3 or 4). O on invalid code
 */
static uint8_t lv_txt_iso8859_1_size(const char * str)
{
    (void)str; /*Unused*/
    return 1;
}

/**
 * Convert an Unicode letter to ISO8859-1.
 * @param letter_uni an Unicode letter
 * @return ISO8859-1 coded character in Little Endian to be compatible with C chars (e.g. 'Á', 'Ű')
 */
static uint32_t lv_txt_unicode_to_iso8859_1(uint32_t letter_uni)
{
    if(letter_uni < 128)
        return letter_uni;
    else
        return ' ';
}

/**
 * Convert wide characters to ASCII, however wide characters in ASCII range (e.g. 'A') are ASCII compatible by default.
 * So this function does nothing just returns with `c`.
 * @param c a character, e.g. 'A'
 * @return same as `c`
 */
static uint32_t lv_txt_iso8859_1_conv_wc(uint32_t c)
{
    return c;
}

/**
 * Decode an ISO8859-1 character from a string.
 * @param txt pointer to '\0' terminated string
 * @param i start byte index in 'txt' where to start.
 *          After call it will point to the next UTF-8 char in 'txt'.
 *          NULL to use txt[0] as index
 * @return the decoded Unicode character or 0 on invalid UTF-8 code
 */
static uint32_t lv_txt_iso8859_1_next(const char * txt, uint32_t * i)
{
    if(i == NULL) return txt[1]; /*Get the next char */

    uint8_t letter = txt[*i];
    (*i)++;
    return letter;
}

/**
 * Get previous ISO8859-1 character form a string.
 * @param txt pointer to '\0' terminated string
 * @param i start byte index in 'txt' where to start. After the call it will point to the previous UTF-8 char in 'txt'.
 * @return the decoded Unicode character or 0 on invalid UTF-8 code
 */
static uint32_t lv_txt_iso8859_1_prev(const char * txt, uint32_t * i)
{
    if(i == NULL) return *(txt - 1); /*Get the prev. char */

    (*i)--;
    uint8_t letter = txt[*i];

    return letter;
}

/**
 * Convert a character index (in an ISO8859-1 text) to byte index.
 * E.g. in "AÁRT" index of 'R' is 2th char but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param utf8_id character index
 * @return byte index of the 'utf8_id'th letter
 */
static uint32_t lv_txt_iso8859_1_get_byte_id(const char * txt, uint32_t utf8_id)
{
    (void)txt;      /*Unused*/
    return utf8_id; /*In Non encoded no difference*/
}

/**
 * Convert a byte index (in an ISO8859-1 text) to character index.
 * E.g. in "AÁRT" index of 'R' is 2th char but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param byte_id byte index
 * @return character index of the letter at 'byte_id'th position
 */
static uint32_t lv_txt_iso8859_1_get_char_id(const char * txt, uint32_t byte_id)
{
    (void)txt;      /*Unused*/
    return byte_id; /*In Non encoded no difference*/
}

/**
 * Get the number of characters (and NOT bytes) in a string. Decode it with UTF-8 if enabled.
 * E.g.: "ÁBC" is 3 characters (but 4 bytes)
 * @param txt a '\0' terminated char string
 * @return number of characters
 */
static uint32_t lv_txt_iso8859_1_get_length(const char * txt)
{
    return strlen(txt);
}
#else

#error "Invalid character encoding. See `LV_TXT_ENC` in `lv_conf.h`"

#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Test if char is break char or not (a text can broken here or not)
 * @param letter a letter
 * @return false: 'letter' is not break char
 */
static inline bool is_break_char(uint32_t letter)
{
    uint8_t i;
    bool ret = false;

    /*Compare the letter to TXT_BREAK_CHARS*/
    for(i = 0; LV_TXT_BREAK_CHARS[i] != '\0'; i++) {
        if(letter == (uint32_t)LV_TXT_BREAK_CHARS[i]) {
            ret = true; /*If match then it is break char*/
            break;
        }
    }

    return ret;
}
