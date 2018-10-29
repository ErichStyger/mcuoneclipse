/*
 * Application.c
 *
 *  Created on: 29.10.2018
 *      Author: Erich Styger Local
 */

#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "rc522/MFRC522.h"

// Number of known default keys (hard-coded)
// NOTE: Synchronize the NR_KNOWN_KEYS define with the defaultKeys[] array
#define NR_KNOWN_KEYS   8
// Known keys, see: https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys
static const uint8_t knownKeys[NR_KNOWN_KEYS][MF_KEY_SIZE] =  {
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // FF FF FF FF FF FF = factory default
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5}, // A0 A1 A2 A3 A4 A5
    {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5}, // B0 B1 B2 B3 B4 B5
    {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd}, // 4D 3A 99 C3 51 DD
    {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a}, // 1A 98 2C 7E 45 9A
    {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7}, // D3 F7 D3 F7 D3 F7
    {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}, // AA BB CC DD EE FF
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // 00 00 00 00 00 00
};

static void dump_byte_array(uint8_t *buffer, uint8_t bufferSize) {
  uint8_t buf[8];

  for (uint8_t i = 0; i < bufferSize; i++) {
      UTIL1_strcpy(buf, sizeof(buf), " ");
      UTIL1_strcatNum8Hex(buf, sizeof(buf), buffer[i]);
      CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
  }
}

/*
 * Try using the PICC (the tag/card) with the given key to access block 0.
 * On success, it will show the key details, and dump the block data on Serial.
 *
 * @return true when the given key worked, false otherwise.
 */
bool try_key(MIFARE_Key *key) {
    bool result = false;
    uint8_t buffer[18];
    uint8_t block = 0;
    MFRC522_StatusCode status;

    // http://arduino.stackexchange.com/a/14316
    if (!PICC_IsNewCardPresent()) {
        return FALSE;
    }
    if (!PICC_ReadCardSerial()) {
        return FALSE;
    }
    CLS1_SendStr("Authenticating using key A...\r\n", CLS1_GetStdio()->stdOut);
    status = MFRC522_PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, block, key, MFRC522_GetUid());
    if (status != STATUS_OK) {
      CLS1_SendStr("PCD_Authenticate() failed: ", CLS1_GetStdio()->stdErr);
      CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdErr);
      CLS1_SendStr("\r\n", CLS1_GetStdio()->stdErr);
      return false;
    }
    // Read block
    uint8_t byteCount = sizeof(buffer);
    status = MFRC522_MIFARE_Read(block, buffer, &byteCount);
    if (status != STATUS_OK) {
      CLS1_SendStr("MIFARE_Read() failed: ", CLS1_GetStdio()->stdErr);
      CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdErr);
    } else {
        // Successful read
        result = true;
        CLS1_SendStr("Success with key:", CLS1_GetStdio()->stdOut);
        dump_byte_array((*key).keyByte, MF_KEY_SIZE);
        CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
        // Dump block data
        CLS1_SendStr("Block ", CLS1_GetStdio()->stdOut);
        CLS1_SendNum8u(block, CLS1_GetStdio()->stdOut);
        CLS1_SendStr(":", CLS1_GetStdio()->stdOut);
        dump_byte_array(buffer, 16);
        CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
    }
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
    MFRC522_PICC_HaltA();       // Halt PICC
    MFRC522_PCD_StopCrypto1();  // Stop encryption on PCD
    return result;
}

static void CheckForCard(void) {
  uint8_t block = 0;
  MFRC522_StatusCode status;
  Uid *uid;

  if (!PICC_IsNewCardPresent()) {
    return;
  }
  if (!PICC_ReadCardSerial()) {
    return;
  }

  uid = MFRC522_GetUid();
#if 0
  CLS1_SendStr("Card UID:", CLS1_GetStdio()->stdOut);
  dump_byte_array(uid->uidByte, uid->size);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  CLS1_SendStr("PICC type:", CLS1_GetStdio()->stdOut);
  PICC_Type piccType = PICC_GetType(uid->sak);
  CLS1_SendStr(PICC_GetTypeName(piccType), CLS1_GetStdio()->stdOut);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Try the known default keys
  MIFARE_Key key;
  for (uint8_t k = 0; k < NR_KNOWN_KEYS; k++) {
      // Copy the known key into the MIFARE_Key structure
      for (uint8_t i = 0; i < MF_KEY_SIZE; i++) {
          key.keyByte[i] = knownKeys[k][i];
      }
      // Try the key
      if (try_key(&key)) {
          // Found and reported on the key and block,
          // no need to try other keys for this PICC
          break;
      }
  }
#else
  // Dump debug info about the card; PICC_HaltA() is automatically called
  MFRC522_PICC_DumpToSerial(uid);
#endif
}

void APP_Run(void) {
  CLS1_SendStr("RFID-RC522\r\n", CLS1_GetStdio()->stdOut);
  PCD_Init();
  for(;;) {
    CheckForCard();
    WAIT1_Waitms(100);
    LED1_Neg();
  } /* for */
}

