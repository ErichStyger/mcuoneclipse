/*
 * Card.c
 *
 *  Created on: May 1, 2013
 *      Author: Erich Styger
 */


#include "Card.h"
#include "CLS1.h"
#include "UTIL1.h"

/* 4 bit code with 1 bit ODD parity. The bits are LSB first!
 * See: http://stripesnoop.sourceforge.net/devel/phrack37.txt */
typedef struct BCD {
  uint8_t code; /* 4bits LSB first with ODD parity bit */
  unsigned char ch; /* character code */
} BCD;

static const BCD charMap5bit[] =
  { /* index into table: 4 first bits of bit5! */
      {0b00001, '0'},
      {0b10000, '1'},
      {0b01000, '2'},
      {0b11001, '3'},
      {0b00100, '4'},
      {0b10101, '5'},
      {0b01101, '6'},
      {0b11100, '7'},
      {0b00010, '8'},
      {0b10011, '9'},
      {0b01011, ':'}, /* control */
      {0b11010, ';'}, /* start sentinel */
      {0b00111, '<'}, /* control */
      {0b10110, '='}, /* field separator */
      {0b01110, '>'}, /* control */
      {0b11111, '?'}  /* end sentinel */
  };

uint8_t CARD_5bitCodeForChar(unsigned char ch, uint8_t *code) {
  if (ch<'0'||ch>'?') {
    return ERR_FAILED;
  }
  *code = charMap5bit[ch-'0'].code;
  return ERR_OK;
}

uint8_t CARD_5bitcharForCode(uint8_t code, unsigned char *ch) {
  int i;
  
  for(i=0; i<sizeof(charMap5bit)/sizeof(charMap5bit[0]); i++) {
    if (charMap5bit[i].code==code) {
      *ch = charMap5bit[i].ch;
      return ERR_OK;
    }
  }
  *ch = '\0';
  return ERR_FAILED;
}


uint8_t CARD_GetBit(uint8_t *bitArray, uint16_t nofArrayBits, uint16_t bitPos, uint8_t *bit) {
  if (bitPos>nofArrayBits) {
    return ERR_FAILED;
  }
  *bit = bitArray[bitPos/(8*sizeof(uint8_t))] & (0x80>>(bitPos%(sizeof(uint8_t)*8)));
  return ERR_OK;
}

uint8_t CARD_SetBit(uint8_t *bitArray, uint16_t nofArrayBits, uint16_t bitPos) {
  if (bitPos>nofArrayBits) {
    return ERR_FAILED;
  }
  bitArray[bitPos/(8*sizeof(uint8_t))] |= 0x80>>(bitPos%(sizeof(uint8_t)*8));
  return ERR_OK;
}

uint8_t CARD_ClrBit(uint8_t *bitArray, uint16_t nofArrayBits, uint16_t bitPos) {
  if (bitPos>nofArrayBits) {
    return ERR_FAILED;
  }
  bitArray[bitPos/(8*sizeof(uint8_t))] &= ~(0x80>>(bitPos%(sizeof(uint8_t)*8)));
  return ERR_OK;
}

/*!
 * \brief Reads a number of bits from a bit array
 * \param bitArray pointer to array of bytes which represent the bit array
 * \param nofArrayBits size of bit array in bits
 * \param bitStart bit start position where to start extracting, 0 is MSB in byte
 * \param nofBits how many bits to extract
 * \param data here the extracted bits are stored
 * @return ERR_OK if everything is ok, ERR_OVERFLOW for access out of array, ERR_FAILED otherwise
 */
uint8_t CARD_ReadBits(uint8_t *bitArray, uint16_t nofArrayBits, uint16_t bitArrayPos, uint8_t nofBits, uint8_t *data) {
  uint8_t tmp, bit;
  
  if (   bitArrayPos>nofArrayBits /* start out of array */
      || bitArrayPos+nofBits>nofArrayBits /* end out of array */
      || nofBits==0 /* need at least one bit */
      || nofBits>8 /* we only support extracting 8bits */
     ) 
  {
    return ERR_OVERFLOW;
  }
  tmp = 0;
  for(;;) { /* breaks */
    if (CARD_GetBit(bitArray, nofArrayBits, bitArrayPos, &bit)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (bit!=0) {
      tmp |= 1;
    }
    nofBits--;
    bitArrayPos++;
    if (nofBits==0) {
      break;
    }
    tmp <<= 1;
  }
  *data = tmp;
  return ERR_OK;
}

uint8_t CARD_InsertBits(uint8_t *bitArray, uint16_t nofArrayBits, uint16_t bitArrayPos, uint8_t data, uint8_t dataStartBitPos, uint8_t nofDataBits) {
  uint8_t mask, res;
  
  if (bitArrayPos>nofArrayBits) {
    return ERR_FAILED;
  }
  mask = 0x80>>dataStartBitPos;
  while(nofDataBits>0) {
    if (data&mask) {
      res = CARD_SetBit(bitArray, nofArrayBits, bitArrayPos);
    } else {
      res = CARD_ClrBit(bitArray, nofArrayBits, bitArrayPos);
    }
    if (res!=ERR_OK) {
      return res;
    }
    nofDataBits--;
    mask >>= 1;
    bitArrayPos++;
  }
  return ERR_OK;
}

uint8_t CARD_Encode(uint8_t *bitArray, uint16_t nofArrayBits, const unsigned char *src, uint16_t *encodedDataBits) {
  uint8_t code;
  uint16_t bitPos;
  int i;
  
  for(i=0;i<nofArrayBits/8;i++) { /* initialize buffer */
    bitArray[i] = 0;
  }
  bitPos = 0;
  while(*src!='\0') {
    if (CARD_5bitCodeForChar(*src, &code)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (CARD_InsertBits(bitArray, nofArrayBits, bitPos, code, 3, 5)!=ERR_OK) {
      return ERR_FAILED;
    }
    bitPos += 5;
    src++;
  }
  *encodedDataBits = bitPos;
  return ERR_OK;
}

uint8_t CARD_Decode(uint8_t *bitArray, uint16_t nofArrayBits, unsigned char *buf, size_t bufSize) {
  int bitPos;
  uint8_t code, res=ERR_OK;
  
  *buf = '\0';
  for(bitPos=0;bitPos<nofArrayBits && bufSize>1;bitPos+=5) {
    if (CARD_ReadBits(bitArray, nofArrayBits, bitPos, 5, &code)!=ERR_OK) {
      res = ERR_FAILED;
      break;
    }
    if (CARD_5bitcharForCode(code, buf)!=ERR_OK) {
      res = ERR_FAILED;
      break;
    }
    bufSize--;
    buf++;
  }
  *buf = '\0'; /* terminate buffer in any case */
  if(bufSize==1) { /* enough buffer? */
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t EncodeString(uint8_t *bitArray, uint16_t nofArrayBits, const unsigned char *str, uint16_t *encodedDataBits, const CLS1_StdIOType *io) {
  static uint8_t buf[36];
  int i;

  CLS1_SendStr((unsigned char*)"Encoding this string: ", io->stdOut);
  CLS1_SendStr(str, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  if (CARD_Encode(bitArray, nofArrayBits, str, encodedDataBits)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Encoding failed!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((unsigned char*)"Encoded data in hex: ", io->stdErr);
  for(i=0;i<*encodedDataBits/8;i++) {
    buf[0] = '\0';
    UTIL1_strcatNum8Hex(buf, sizeof(buf), bitArray[i]);
    UTIL1_chcat(buf, sizeof(buf), ' ');
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
  return ERR_OK;
}

static uint8_t DecodeData(uint8_t *bitArray, uint16_t nofArrayBits, const CLS1_StdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStr((unsigned char*)"Decoded:\r\n", io->stdOut);
  if (CARD_Decode(bitArray, nofArrayBits, buf, sizeof(buf))!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Decoding failed!\r\n", io->stdErr);
  }
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"card", (unsigned char*)"Group of card commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help", (unsigned char*)"Print help information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  encode <str>", (unsigned char*)"Encode a string\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  decode <data>", (unsigned char*)"Decode list of hex data values, e.g. AB C7\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t CARD_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  static uint8_t bitArray[48];
  static uint8_t dataValues[48];
  uint16_t encodedDataBits;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "card help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (UTIL1_strncmp((char*)cmd, "card encode ", sizeof("card encode ")-1)==0) {
    uint8_t res;
    
    *handled = TRUE;
    res = EncodeString(bitArray, sizeof(bitArray)*8, cmd+sizeof("card encode"), &encodedDataBits, io);
    if (res!=ERR_OK) {
      return res;
    }
    return DecodeData(bitArray, encodedDataBits, io);
  } else if (UTIL1_strncmp((char*)cmd, "card decode ", sizeof("card decode ")-1)==0) {
    const unsigned char *p;
    int i;

    *handled = TRUE;
    p = cmd+sizeof("card decode");
    i = 0;
    while(*p!='\0') {
      if (UTIL1_ScanHex8uNumberNoPrefix(&p, &dataValues[i])!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"Failed reading number!\r\n", io->stdErr);
        return ERR_FAILED;
      }
      i++;
    }
    return DecodeData(dataValues, i*8, io);
  }
  return ERR_OK;
}
