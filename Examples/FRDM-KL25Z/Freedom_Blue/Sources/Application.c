/*
 * Application.c
 *
 *  Created on: Oct 14, 2012
 *      Author: Erich Styger
 */

#include "Application.h"
#include "BT1.h"
#include "UTIL1.h"
#include "FSSH1.h"
#include "Shell.h"

static uint8_t ExecuteQueryString(uint8_t(*f)(unsigned char*,size_t), unsigned char *text, const FSSH1_StdIOType *io) {
  uint8_t buf[32];

  FSSH1_SendStr(text, io->stdOut);
  if (f(buf, sizeof(buf))!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
    return ERR_FAILED;
  } else {
    FSSH1_SendStr(buf, io->stdOut);
    FSSH1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }
  return ERR_OK;
}

static void Test(const FSSH1_StdIOType *io) {
  uint8_t buf[32];
  uint8_t num8;
  uint16_t mask;

  FSSH1_SendStr((unsigned char*)"\r\nBluetooth Module Test:\r\n----------------------\r\n", io->stdOut);

  FSSH1_SendStr((unsigned char*)"Test UART: ", io->stdOut);
  if (BT1_btTestUART()!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
    return;
  } else {
    FSSH1_SendStr((unsigned char*)"OK\r\n", io->stdOut);
  }

#if 0
  FSSH1_SendStr((unsigned char*)"Reset Device: ", io->stdOut);
  if (BT1_btResetDevice()!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    FSSH1_SendStr((unsigned char*)"OK\r\n", io->stdOut);
  }
  FSSH1_SendStr((unsigned char*)"Wait some time to reset device...\r\n", io->stdOut);
  WAIT1_Waitms(BT1_TIMEOUT_MS_AFTER_RESET);
#endif
  
  ExecuteQueryString(BT1_btQueryFirmwareVersionStr, (unsigned char*)"Firmware Version: ", io);
  
#if 0
  FSSH1_SendStr((unsigned char*)"Reset to factory defaults: ", io->stdOut);
  if (BT1_btRestorFactoryDefault()!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    FSSH1_SendStr((unsigned char*)"OK\r\n", io->stdOut);
  }
  WAIT1_Waitms(BT1_TIMEOUT_MS_AFTER_FACTORY_DEFAULT); /* give device time to boot up again. Did not find a value in the data sheet */
#endif
  
  ExecuteQueryString(BT1_btQueryDeviceName, (unsigned char*)"Device Name: ", io);
  ExecuteQueryString(BT1_btQueryBluetoothAddressStr, (unsigned char*)"Bluetooth Address: ", io);

#if 0
  FSSH1_SendStr((unsigned char*)"Setting device name: ", io->stdOut);
  if (BT1_btSetDeviceName((unsigned char*)"INTRO")!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    FSSH1_SendStr((unsigned char*)"OK\r\n", io->stdOut);
  } 
#endif
  
  FSSH1_SendStr((unsigned char*)"Role: ", io->stdOut);
  if (BT1_btQueryRole(&buf[0])!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    buf[1] = '\0';
    FSSH1_SendStr(buf, io->stdOut);
    if (buf[0]=='0') {
      FSSH1_SendStr((unsigned char*)(" (slave)"), io->stdOut);
    } else if (buf[1]=='1') {
      FSSH1_SendStr((unsigned char*)(" (master)"), io->stdOut);
    } else if (buf[1]=='2') {
      FSSH1_SendStr((unsigned char*)(" (slave-loop)"), io->stdOut);
    } else {
      FSSH1_SendStr((unsigned char*)(" (UNKNOWN)"), io->stdOut);
    }
    FSSH1_SendStr((unsigned char*)"\r\n", io->stdOut);
  } 

  ExecuteQueryString(BT1_btQueryIACStr, (unsigned char*)"IAC: ", io);
  ExecuteQueryString(BT1_btQueryIAMStr, (unsigned char*)"IAM: ", io);
  ExecuteQueryString(BT1_btQueryPairingPasskey, (unsigned char*)"Pairing Passkey: ", io);
  ExecuteQueryString(BT1_btQueryUARTParametersStr, (unsigned char*)"UART Parameter: ", io);
  
  FSSH1_SendStr((unsigned char*)"Connection method: ", io->stdOut);
  if (BT1_btQueryConnectionMethod(&buf[0])!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    buf[1] = '\0';
    FSSH1_SendStr(buf, io->stdOut);
    if (buf[0]=='0') {
      FSSH1_SendStr((unsigned char*)" (specific address only)", io->stdOut);
    } else if (buf[0]=='1') {
      FSSH1_SendStr((unsigned char*)" (any address)", io->stdOut);
    } else if (buf[0]=='2') {
      FSSH1_SendStr((unsigned char*)" (test mode)", io->stdOut);
    }
    FSSH1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }
  
  ExecuteQueryString(BT1_btQueryBindingBluetoothAddress, (unsigned char*)"Binding Bluetooth Address: ", io);
  ExecuteQueryString(BT1_btQueryLEDOutputPolarityStr, (unsigned char*)"Output LED polarity: ", io);

  FSSH1_SendStr((unsigned char*)"Multiple User I/O pins: ", io->stdOut);
  if (BT1_btQueryMultipleUserIOPins(&mask)!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), mask);
    FSSH1_SendStr(buf, io->stdOut);
    FSSH1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }

  ExecuteQueryString(BT1_btQueryScanningParametersStr, (unsigned char*)"Scanning Parameters: ", io);
  ExecuteQueryString(BT1_btQuerySNIFFParametersStr, (unsigned char*)"SNIFF Parameters: ", io);
  ExecuteQueryString(BT1_btQuerySecurityEncryptionModesStr, (unsigned char*)"Security and Encryption Modes: ", io);

  FSSH1_SendStr((unsigned char*)"Total number of authenticated devices: ", io->stdOut);
  if (BT1_btQueryTotalNumberOfDeviceFromAuthenticationList(&num8)!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"failed\r\n", io->stdOut);
  } else {
    buf[0] = '\0';
    UTIL1_Num8uToStr(buf, sizeof(buf), num8);
    FSSH1_SendStr(buf, io->stdOut);
    FSSH1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }
  
  ExecuteQueryString(BT1_btQueryMostRecentlyUsedAuthenticatedDevice, (unsigned char*)"Most recently authenticated Device: ", io);
  ExecuteQueryString(BT1_btQueryCurrentStateOfDeviceStr, (unsigned char*)"Current State of Device: ", io);
}

static void PrintHelp(const FSSH1_StdIOType *io) {
  /* list your local help here */
  FSSH1_SendHelpStr((unsigned char*)"bt", (unsigned char*)"Group of bt commands\r\n", io->stdOut);
  FSSH1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows trace help or status\r\n", io->stdOut);
  FSSH1_SendHelpStr((unsigned char*)"  cmd <AT command>", (unsigned char*)"Send AT command to Bluetooth modem\r\n", io->stdOut);
}

/*!
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const FSSH1_StdIOType *io) {
  /* list your local status here */
  FSSH1_SendStatusStr((unsigned char*)"bt", (unsigned char*)"\r\n", io->stdOut);
  FSSH1_SendStatusStr((unsigned char*)"  dummy", (unsigned char*)"yes\r\n", io->stdOut);
  Test(io);
}

static void SendATCommand(const unsigned char *cmd, const FSSH1_StdIOType *io) {
  unsigned char buf[32];
  unsigned char cmdBuf[32];
  
  UTIL1_strcpy(cmdBuf, sizeof(cmdBuf), cmd);
  UTIL1_strcat(cmdBuf, sizeof(cmdBuf), (unsigned char*)"\r\n");
  buf[0] = '\0';
  if (BT1_SendATCommand(cmdBuf, buf, sizeof(buf), (unsigned char*)"OK\r\n")!=ERR_OK) {
    FSSH1_SendStr((unsigned char*)"***AT does not match tail\r\n", io->stdOut);
  }
  FSSH1_SendStr(buf, io->stdOut);
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  /* handling our own commands */
  if (UTIL1_strcmp((char*)cmd, FSSH1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "bt help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, FSSH1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "bt status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "bt cmd ", sizeof("bt cmd ")-1)==0) {
    SendATCommand(cmd+sizeof("bt cmd ")-1, io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "bt test")==0) {
    Test(io);
    *handled = TRUE;
  }
  return ERR_OK;
}

void APP_Run(void) {
  unsigned char buf[32];
  Serial1_TComData rx;
  
  SHELL_Init();
  buf[0]='\0';
  SHELL_ParseLine((unsigned char*)"help");
  for(;;) {
    SHELL_ReadAndParseLine(buf, sizeof(buf));
    if (Serial1_GetCharsInRxBuf()>0) {
      if (Serial1_RecvChar(&rx)==ERR_OK) {
        FSSH1_GetStdio()->stdOut(rx);
      }
    }
  }
}
