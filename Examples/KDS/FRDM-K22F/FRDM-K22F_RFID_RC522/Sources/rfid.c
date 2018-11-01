/*
 * rfid.c
 *
 */

#include "Platform.h"
#include "rfid.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "rc522/MFRC522.h"

static SemaphoreHandle_t rfidSem;
static Uid *RFID_uid = NULL;
static bool RFID_dumpNewCardInformation = FALSE;
static uint8_t RFID_newUID4[] = {0x99, 0x52, 0x97, 0xC4};
static bool RFID_changeUID = FALSE;
static bool RFID_authUID = FALSE;
static bool RFID_WriteMifare = FALSE;
static bool RFID_DoSelfTest = FALSE;
static bool RFID_WriteUltraLight = FALSE;
static bool RFID_TryKnownKeys = FALSE;

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

static void dump_byte_array(uint8_t *buffer, uint8_t bufferSize, bool inHex) {
  uint8_t buf[8];

  for (uint8_t i = 0; i < bufferSize; i++) {
      UTIL1_strcpy(buf, sizeof(buf), " ");
      if (inHex) {
        UTIL1_strcatNum8Hex(buf, sizeof(buf), buffer[i]);
      } else {
        UTIL1_strcatNum8u(buf, sizeof(buf), buffer[i]);
      }
      CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
  }
}

/*
 * Try using the PICC (the tag/card) with the given key to access block 0.
 * On success, it will show the key details, and dump the block data on Serial.
 *
 * @return true when the given key worked, false otherwise.
 */
bool try_key(MFRC522_MIFARE_Key *key) {
    bool result = false;
    uint8_t buffer[18];
    uint8_t block = 0;
    MFRC522_StatusCode status;

    // http://arduino.stackexchange.com/a/14316
  //  if (!MFRC522_PICC_IsNewCardPresent()) {
  //      return FALSE;
  //  }
  //  if (!MFRC522_PICC_ReadCardSerial()) {
  //      return FALSE;
  //  }
    CLS1_SendStr("Authenticating using key A...\r\n", CLS1_GetStdio()->stdOut);
    status = MFRC522_PCD_Authenticate(MFRC522_PICC_CMD_MF_AUTH_KEY_A, block, key, MFRC522_GetUid());
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
        dump_byte_array((*key).keyByte, MF_KEY_SIZE, TRUE);
        CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
        // Dump block data
        CLS1_SendStr("Block ", CLS1_GetStdio()->stdOut);
        CLS1_SendNum8u(block, CLS1_GetStdio()->stdOut);
        CLS1_SendStr(":", CLS1_GetStdio()->stdOut);
        dump_byte_array(buffer, 16, TRUE);
        CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
    }
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
    MFRC522_PICC_HaltA();       // Halt PICC
    MFRC522_PCD_StopCrypto1();  // Stop encryption on PCD
    return result;
}

static void TryKnownKeys(void) {
  // Try the known default keys
  MFRC522_MIFARE_Key key;

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
}

static void RFID_GetLock(void) {
  (void)xSemaphoreTakeRecursive(rfidSem, portMAX_DELAY);
}

void RFID_ReleaseLock(void) {
  (void)xSemaphoreGiveRecursive(rfidSem);
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];
  int i;

  CLS1_SendStatusStr((unsigned char*)"rfid", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  card", RFID_uid!=NULL?(uint8_t*)"yes\r\n":(uint8_t*)"no\r\n", io->stdOut);
  if (RFID_uid!=NULL) {
    buf[0] = '\0';
    for (i=0; i<RFID_uid->size; i++) {
      UTIL1_strcatNum8Hex(buf, sizeof(buf), RFID_uid->uidByte[i]);
      UTIL1_strcat(buf, sizeof(buf), " ");
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr((unsigned char*)"  UID", buf, io->stdOut);

    UTIL1_strcpy(buf, sizeof(buf), MFRC522_PICC_GetTypeName(MFRC522_PICC_GetType(RFID_uid->sak)));
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr((unsigned char*)"  type", buf, io->stdOut);
  }
  CLS1_SendStatusStr((unsigned char*)"  dump", RFID_dumpNewCardInformation?(uint8_t*)"on\r\n":(uint8_t*)"off\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"rfid", (unsigned char*)"Group of rfid commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  dump (on|off)", (unsigned char*)"Dump new card information to console\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RFID_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "rfid help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "rfid status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "rfid dump on") == 0) {
    *handled = TRUE;
    RFID_dumpNewCardInformation = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "rfid dump off") == 0) {
    *handled = TRUE;
    RFID_dumpNewCardInformation = FALSE;
  }
  return res;
}

static void init_uid_bytes(uint8_t uidBytes[MFRC522_UID_MAX_NOF_BYTES]) {
  int i;

  for(i=0;i<MFRC522_UID_MAX_NOF_BYTES; i++) {
    uidBytes[i] = 0; /* init */
  }
}

static void set_uid_bytes(uint8_t dst[MFRC522_UID_MAX_NOF_BYTES], uint8_t *src, uint8_t nofSrcBytes) {
  int i;

  for(i=0;i<nofSrcBytes; i++) {
    dst[i] = *src; /* copy */
    src++; /* next byte */
  }
  /* fill rest with zeros */
  for(;i<MFRC522_UID_MAX_NOF_BYTES; i++) {
    dst[i] = 0; /* init */
  }
}

static bool same_uid_bytes(uint8_t src[MFRC522_UID_MAX_NOF_BYTES], uint8_t *dst, uint8_t nofdstBytes) {
  int i;

  for(i=0;i<nofdstBytes; i++) {
    if (src[i] != dst[i]) {
      return FALSE; /* not the same */
    }
  }
  return TRUE; /* same */
}

static void AuthNTag216(Uid *id) { /* Ntag216_AUTH */
  //This example show how you can get Authenticated by the NTAG213,215,216 by default the tags are unprotected in order to protect them we need to write 4 different values:
  // Using mfrc522.MIFARE_Ultralight_Write(PageNum, Data, #Databytes))
  //1.- we need to write the 32bit passWord to page 0xE5 !for ntag 213 and 215 page is different refer to nxp documentation!
  //2.- Now Write the 16 bits pACK to the page 0xE6 use the 2 high bytes like this: pACKH + pACKL + 00 + 00 after an authentication the tag will return this secret bytes
  //3.- Now we need to write the first page we want to protect this is a 1 byte data in page 0xE3 we need to write 00 + 00 + 00 + firstPage  all pages after this one are write protected
  // Now WRITE protection is ACTIVATED so we need to get authenticated in order to write the last data
  //4.- Finally we need to write an access record in order to READ protect the card this step is optional only if you want to read protect also write 80 + 00 + 00 + 00 to 0xE4
  //After completeing all these steps you will nee to authentiate first in order to read or write ant page after the first page you selected to protect
  //To disengage proection just write the page (0xE3) to 00 + 00 + 00 + FF that going to remove all protection
  //Made by GARGANTUA from RoboCreators.com & paradoxalabs.com
  uint8_t PSWBuff[] = {0xFF, 0xFF, 0xFF, 0xFF}; //32 bit PassWord default FFFFFFFF
  uint8_t pACK[] = {0, 0}; //16 bit PassWord ACK returned by the NFCtag
  uint8_t buf[16];
  MFRC522_StatusCode status;

  if (id->sak) {
  }
  CLS1_SendStr("Auth: ", CLS1_GetStdio()->stdOut);
  status = MFRC522_PCD_NTAG216_AUTH(&PSWBuff[0], pACK); //Request Authentification if return STATUS_OK we are good
  if (status!=STATUS_OK) {
    CLS1_SendStr("FAILED\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  //Print PassWordACK
  buf[0] = '\0';
  UTIL1_strcatNum8Hex(buf, sizeof(buf), pACK[0]);
  UTIL1_strcat(buf, sizeof(buf), " ");
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);

  uint8_t WBuff[] = {0x00, 0x00, 0x00, 0x04};
  uint8_t RBuff[18];

  //Serial.print("CHG BLK: ");
  //Serial.println(mfrc522.MIFARE_Ultralight_Write(0xE3, WBuff, 4));  //How to write to a page

  MFRC522_PICC_DumpMifareUltralightToSerial(); //This is a modifier dunp just cghange the for cicle to < 232 instead of < 16 in order to see all the pages on NTAG216
}

static void WriteUltraLight(Uid *uid) {
  MFRC522_StatusCode status;
  uint8_t data[4] = {0x1, 0x2, 0x3, 0x4};

  PICC_Type piccType = MFRC522_PICC_GetType(uid->sak);
  if (piccType != PICC_TYPE_MIFARE_UL)  {
    CLS1_SendStr("Only works with MIFARE Ultralight cards!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
  status = MFRC522_MIFARE_Ultralight_Write(2, data, sizeof(data));
  if (status!=STATUS_OK) {
    CLS1_SendStr("Failed writing!\r\n", CLS1_GetStdio()->stdErr);
  }
}

static void WriteMifare(Uid *uid) {
  MFRC522_MIFARE_Key key;

  PICC_Type piccType = MFRC522_PICC_GetType(uid->sak);
  if (   piccType != PICC_TYPE_MIFARE_MINI
      && piccType != PICC_TYPE_MIFARE_1K
      && piccType != PICC_TYPE_MIFARE_UL
      )
  {
    CLS1_SendStr("Only works with MIFARE classic cards!\r\n", CLS1_GetStdio()->stdErr);
    return;
  }
  // init default access key
  for(int i=0;i<sizeof(key.keyByte);i++) {
    key.keyByte[i] = 0xff;
  }

  // In this sample we use the second sector,
  // that is: sector #1, covering block #4 up to and including block #7
  uint8_t sector         = 1;
  uint8_t blockAddr      = 4;
  uint8_t dataBlock[]    = {
      0x01, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
      0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
      0x09, 0x0a, 0xff, 0x0b, //  9, 10, 255, 11,
      0x0c, 0x0d, 0x0e, 0x0f  // 12, 13, 14, 15
  };
  uint8_t trailerBlock   = 7;
  MFRC522_StatusCode status;
  uint8_t buffer[18];
  uint8_t size = sizeof(buffer);

  // Authenticate using key A
  CLS1_SendStr("Authenticating using key A...\r\n", CLS1_GetStdio()->stdOut);
  status = (MFRC522_StatusCode) MFRC522_PCD_Authenticate(MFRC522_PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, uid);
  if (status != STATUS_OK) {
      CLS1_SendStr("PCD_Authenticate() failed: ", CLS1_GetStdio()->stdOut);
      CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdOut);
      return;
  }

  // Show the whole sector as it currently is
  CLS1_SendStr("Current data in sector:\r\n", CLS1_GetStdio()->stdOut);
  MFRC522_PICC_DumpMifareClassicSectorToSerial(uid, &key, sector);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Read data from the block
  CLS1_SendStr("Reading data from block ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(blockAddr, CLS1_GetStdio()->stdOut);
  CLS1_SendStr(" ...\r\n", CLS1_GetStdio()->stdOut);
  status = (MFRC522_StatusCode) MFRC522_MIFARE_Read(blockAddr, buffer, &size);
  if (status != STATUS_OK) {
    CLS1_SendStr("MIFARE_Read() failed: ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdOut);
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("Data in block ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(blockAddr, CLS1_GetStdio()->stdOut);
  CLS1_SendStr(":\r\n", CLS1_GetStdio()->stdOut);
  dump_byte_array(buffer, 16, TRUE);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Authenticate using key B
  CLS1_SendStr("Authenticating again using key B...\r\n", CLS1_GetStdio()->stdOut);
  status = (MFRC522_StatusCode) MFRC522_PCD_Authenticate(MFRC522_PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, uid);
  if (status != STATUS_OK) {
      CLS1_SendStr("PCD_Authenticate() failed: ", CLS1_GetStdio()->stdOut);
      CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdOut);
      CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
      return;
  }

  // Write data to the block
  CLS1_SendStr("Writing data into block ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(blockAddr, CLS1_GetStdio()->stdOut);
  CLS1_SendStr(" ...\r\n", CLS1_GetStdio()->stdOut);
  dump_byte_array(dataBlock, 16, TRUE);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  status = (MFRC522_StatusCode) MFRC522_MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != STATUS_OK) {
    CLS1_SendStr("MIFARE_Write() failed: ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdOut);
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Read data from the block (again, should now be what we have written)
  CLS1_SendStr("Reading data from block ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(blockAddr, CLS1_GetStdio()->stdOut);
  CLS1_SendStr(" ...\r\n", CLS1_GetStdio()->stdOut);
  status = (MFRC522_StatusCode) MFRC522_MIFARE_Read(blockAddr, buffer, &size);
  if (status != STATUS_OK) {
    CLS1_SendStr("MIFARE_Read() failed: ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr(MFRC522_GetStatusCodeName(status), CLS1_GetStdio()->stdOut);
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("Data in block ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(blockAddr, CLS1_GetStdio()->stdOut);
  CLS1_SendStr(":\r\n", CLS1_GetStdio()->stdOut);
  dump_byte_array(buffer, 16, TRUE);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Check that data in block is what we have written
  // by counting the number of bytes that are equal
  CLS1_SendStr("Checking result...", CLS1_GetStdio()->stdOut);
  uint8_t count = 0;
  for (uint8_t i = 0; i < 16; i++) {
      // Compare buffer (= what we've read) with dataBlock (= what we've written)
      if (buffer[i] == dataBlock[i]) {
          count++;
      }
  }
  CLS1_SendStr("Number of bytes that match = ", CLS1_GetStdio()->stdOut);
  CLS1_SendNum8u(count, CLS1_GetStdio()->stdOut);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  if (count == 16) {
    CLS1_SendStr("Success :-)\r\n", CLS1_GetStdio()->stdOut);
  } else {
    CLS1_SendStr("Failure, no match :-(\r\n", CLS1_GetStdio()->stdOut);
    CLS1_SendStr("  perhaps the write didn't work properly...\r\n", CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);

  // Dump the sector data
  CLS1_SendStr("Current data in sector:\r\n", CLS1_GetStdio()->stdOut);
  MFRC522_PICC_DumpMifareClassicSectorToSerial(uid, &key, sector);
  CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
}

static void RfidTask(void *pvParameters) {
  MFRC522_StatusCode status;
  uint8_t last_uidBytes[MFRC522_UID_MAX_NOF_BYTES];
  int i;
  bool newCardDetected = FALSE;

  (void)pvParameters; /* not used */
  init_uid_bytes(last_uidBytes);
  RFID_uid = NULL;

  vTaskDelay(pdMS_TO_TICKS(1000)); /* give hardware some time to power-up */
  MFRC522_PCD_Init();
  //MFRC522_SetAntennaGain(MFRC522_RxGain_max);
  for(;;) {
    newCardDetected = FALSE;
    RFID_GetLock();
    if (RFID_DoSelfTest) {
      if (!MFRC522_PCD_PerformSelfTest()) {
        CLS1_SendStr("Selftest failed()!\r\n", CLS1_GetStdio()->stdErr);
      }
    }
    if (MFRC522_PICC_IsNewCardPresent()) { /* check if a card responds to PICC_CMD_REQA */
      //CLS1_SendStr("Card detected...\r\n", CLS1_GetStdio()->stdOut);
      if (MFRC522_PICC_ReadCardSerial()) {
        //CLS1_SendStr("Read card serial...\r\n", CLS1_GetStdio()->stdOut);
        RFID_uid = MFRC522_GetUid();

        newCardDetected = TRUE;
        if (RFID_dumpNewCardInformation) {
          MFRC522_PICC_DumpToSerial(RFID_uid);
        } else if (RFID_changeUID) { /* only works with Chinese cards which have the UID writeable! */
          if (!MFRC522_MIFARE_SetUid(RFID_newUID4, sizeof(RFID_newUID4), TRUE)) {
            CLS1_SendStr("Setting new uid failed!\r\n", CLS1_GetStdio()->stdOut);
          } else {
            CLS1_SendStr("Set New ID to card!\r\n", CLS1_GetStdio()->stdOut);
          }
        } else if (RFID_authUID) { /* only for NTAG216! */
          AuthNTag216(RFID_uid);
        } else if (RFID_WriteUltraLight) {
          WriteUltraLight(RFID_uid);
        } else if (RFID_WriteMifare) {
          WriteMifare(RFID_uid);
        } else if (RFID_TryKnownKeys) {
          TryKnownKeys();
        } else if (!same_uid_bytes(last_uidBytes, &RFID_uid->uidByte[0], RFID_uid->size)) {
          CLS1_SendStr("\r\nCard UID:", CLS1_GetStdio()->stdOut);
          dump_byte_array(RFID_uid->uidByte, RFID_uid->size, TRUE);
          CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
          init_uid_bytes(last_uidBytes);

          set_uid_bytes(last_uidBytes, &RFID_uid->uidByte[0], RFID_uid->size);

          CLS1_SendStr("PICC type: ", CLS1_GetStdio()->stdOut);
          PICC_Type piccType = MFRC522_PICC_GetType(RFID_uid->sak);
          CLS1_SendStr(MFRC522_PICC_GetTypeName(piccType), CLS1_GetStdio()->stdOut);
          CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
        } else { /* same card again */
          CLS1_SendStr(".", CLS1_GetStdio()->stdOut);
        }
      }
      MFRC522_PICC_HaltA(); /* Halt PICC */
      MFRC522_PCD_StopCrypto1(); /* Stop encryption on PCD */
    } /* new card present */
    RFID_ReleaseLock();
    if (!newCardDetected) {
      vTaskDelay(pdMS_TO_TICKS(500));
    } else {
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}

void RFID_Init(void) {
  rfidSem = xSemaphoreCreateRecursiveMutex();
  if (rfidSem==NULL) { /* creation failed? */
    for(;;);
  }
  vQueueAddToRegistry(rfidSem, "rfidSem");
  if (xTaskCreate(RfidTask, "RFID", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

