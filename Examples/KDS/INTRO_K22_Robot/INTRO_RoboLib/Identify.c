/**
 * \file
 * \brief Module to identify different devices based on their unique ID.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * With this module individual devices are identified based on their unique ID.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_IDENTIFY
#include "Identify.h"
#include "KIN1.h"
#include "UTIL1.h"

static ID_Devices currDevice = ID_DEVICE_NONE;

typedef struct {
  ID_Devices id;
  const unsigned char *name;
  KIN1_UID uuid;
} ID_Device;

static const ID_Device idTable[] =
{
  {.id=ID_DEVICE_ROBO_V1_L1,  .name=(const unsigned char*)"L1",  .uuid={{0x00,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}}},
  {.id=ID_DEVICE_ROBO_V1_L2,  .name=(const unsigned char*)"L2",  .uuid={{0x00,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}}},
  {.id=ID_DEVICE_ROBO_V1_L3,  .name=(const unsigned char*)"L3",  .uuid={{0x00,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x0A}}},
  {.id=ID_DEVICE_ROBO_V1_L4,  .name=(const unsigned char*)"L4",  .uuid={{0x00,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x24}}},
  {.id=ID_DEVICE_ROBO_V2_L5,  .name=(const unsigned char*)"L5",  .uuid={{0x00,0x38,0x00,0x00,0x67,0xCD,0xB5,0x41,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
  {.id=ID_DEVICE_ROBO_V1_L7,  .name=(const unsigned char*)"L7",  .uuid={{0x00,0x20,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x07}}},
  {.id=ID_DEVICE_ROBO_V1_L8,  .name=(const unsigned char*)"L8",  .uuid={{0x00,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}}},
  {.id=ID_DEVICE_ROBO_V2_L12, .name=(const unsigned char*)"L12", .uuid={{0x00,0x34,0x00,0x00,0x67,0xCD,0xB7,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x14}}},
  {.id=ID_DEVICE_ROBO_V2_L13, .name=(const unsigned char*)"L13", .uuid={{0x00,0x36,0x00,0x00,0x67,0xCD,0xB6,0x31,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
  {.id=ID_DEVICE_ROBO_V2_L14, .name=(const unsigned char*)"L14", .uuid={{0x00,0x30,0x00,0x00,0x4E,0x45,0xB6,0x31,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
  {.id=ID_DEVICE_ROBO_V2_L20, .name=(const unsigned char*)"L20", .uuid={{0x00,0x03,0x00,0x00,0x67,0xCD,0xB7,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
  {.id=ID_DEVICE_ROBO_V2_L21, .name=(const unsigned char*)"L21", .uuid={{0x00,0x05,0x00,0x00,0x4E,0x45,0xB7,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
  {.id=ID_DEVICE_ROBO_V2_L22, .name=(const unsigned char*)"L22", .uuid={{0x00,0x1F,0x00,0x00,0x67,0xD2,0x6A,0x41,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x37}}},
  {.id=ID_DEVICE_ROBO_V2_L23, .name=(const unsigned char*)"L23", .uuid={{0x00,0x0A,0x00,0x00,0x67,0xCD,0xB8,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}}},
};

static ID_Devices IdentifyDevice(void) {
  uint8_t res;
  KIN1_UID id;
  unsigned int i;

  res = KIN1_UIDGet(&id);
  if (res==ERR_OK) {
    for(i=0; i<sizeof(idTable)/sizeof(idTable[0]); i++) {
      if (KIN1_UIDSame(&id, &idTable[i].uuid)) {
        return idTable[i].id; /* found it */
      }
    }
  }
  return ID_DEVICE_UNKNOWN;
}

static const ID_Device *GetDeviceDesc(ID_Devices id) {
  unsigned int i;

  for(i=0; i<sizeof(idTable)/sizeof(idTable[0]); i++) {
    if (idTable[i].id == id) {
      return &idTable[i]; /* found it */
    }
  }
  return NULL;
}


ID_Devices ID_WhichDevice(void) {
  if (currDevice==ID_DEVICE_NONE) {
    /* not checked ID, try to find matching robot */
    currDevice = IdentifyDevice();
  }
  return currDevice;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  const ID_Device *device;

  CLS1_SendStatusStr((unsigned char*)"id", (unsigned char*)"\r\n", io->stdOut);
  device = GetDeviceDesc(ID_WhichDevice());
  if (device!=NULL) {
    UTIL1_strcpy(buf, sizeof(buf), device->name);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  device", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  device", (uint8_t*)"UNKNOWN\r\n", io->stdOut);
  }

  return ERR_OK;
}

uint8_t ID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "id help")==0) {
    CLS1_SendHelpStr((unsigned char*)"id", (const unsigned char*)"Group of id commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "id status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void ID_Deinit(void) {
  currDevice = ID_DEVICE_NONE;
}

void ID_Init(void) {
  currDevice = ID_DEVICE_NONE;
}
#endif /* PL_CONFIG_HAS_IDENTIFY */
