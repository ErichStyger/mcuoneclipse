/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "McuSWO.h"
#include "leds.h"
#include "buttons.h"
#include "fsl_hashcrypt.h"
#include "Shell.h"
#include "disk.h"
#include "sha-256.h"
#include "w25_interface.h"

#include "cr_section_macros.h"
#if PL_CONFIG_HAS_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
  #include "janpatch.h"
  #include "littleFS/lfs.h"
  #include "patch.h"
  #include "littleFS/McuLittleFSBlockDevice.h"
#endif
#include "memory.h"

#define STARTADDRESS_IMAGE 0x1E800

static lfs_t* JANPATCH_LFS_lfs;

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

TIMEREC timeSync;
DATEREC dateSync;

#define FILESYSTEM_READ_BUFFER_SIZE 256//256
#define FILESYSTEM_PROG_BUFFER_SIZE 256//256
#define FILESYSTEM_LOOKAHEAD_SIZE 256 //128
#define FILESYSTEM_CACHE_SIZE 256

#if 0
/* configuration of the file system is provided by this struct */
static const struct lfs_config JANPATCH_cfg = {
  /* block device operations */
  .read = McuLittleFS_block_device_read,
  .prog = McuLittleFS_block_device_prog,
  .erase = McuLittleFS_block_device_erase,
  .sync = McuLittleFS_block_device_sync,
  /* block device configuration */
  .read_size = FILESYSTEM_READ_BUFFER_SIZE,
  .prog_size = FILESYSTEM_PROG_BUFFER_SIZE,
  .block_size = 4096,
  .block_count = 16384, /* 16384 * 4K = 64 MByte */
  .cache_size = FILESYSTEM_CACHE_SIZE,
  .lookahead_size = FILESYSTEM_LOOKAHEAD_SIZE,
  .block_cycles = 500,
#if LITTLEFS_CONFIG_THREAD_SAFE
  .lock = NULL,
  .unlock = NULL,
#endif
};
#endif

static SemaphoreHandle_t mutex;



static void TestSha256(void)
{
	struct Sha_256 sha_256;
	uint8_t result;
	uint8_t hash[32];
	sha_256_init(&sha_256, hash);
	static lfs_t* fileSystem;
	fileSystem = McuLFS_GetFileSystem();
	JANPATCH_STREAM patchFile;


	result = lfs_file_open(fileSystem, &patchFile, "patch.bin", LFS_O_RDWR | LFS_O_CREAT| LFS_O_APPEND);
	if (result < 0) {
		McuLog_info("Error open patch.bin \n\n\n\n");
		//return ERR_FAILED;
	}



	W25_read_block_for_SHA(fileSystem, &patchFile, 512, hash);

	McuLog_info("\r\n\r\n\r\n########## ========== SHA256 of file  ========== ##########\r\n");
	for(int i=0; i<sizeof(hash);i++){
		McuLog_info("0x%02X, ", hash[i]);
	}




//    status_t status;
//    size_t outLength;
//    unsigned int length;
//    unsigned char output[32];
//
//    static const uint8_t message[] =
//        "Be that word our sign of parting, bird or fiend! I shrieked upstarting"
//        "Get thee back into the tempest and the Nights Plutonian shore!"
//        "Leave no black plume as a token of that lie thy soul hath spoken!"
//        "Leave my loneliness unbroken! quit the bust above my door!"
//        "Take thy beak from out my heart, and take thy form from off my door!"
//        "Quoth the raven, Nevermore.  ";
//
//    /* Expected SHA-256 for the message. */
//    static const unsigned char sha256[] = {0x63, 0x76, 0xea, 0xcc, 0xc9, 0xa2, 0xc0, 0x43, 0xf4, 0xfb, 0x01,
//                                           0x34, 0x69, 0xb3, 0x0c, 0xf5, 0x28, 0x63, 0x5c, 0xfa, 0xa5, 0x65,
//                                           0x60, 0xef, 0x59, 0x7b, 0xd9, 0x1c, 0xac, 0xaa, 0x31, 0xf7};
//
//
//
//    length    = sizeof(message) - 1;
//    outLength = sizeof(output);
//    memset(&output, 0, outLength);
//
//    sha_256_write(&sha_256, message, length);
//    sha_256_close(&sha_256);
    /************************ SHA-256 **************************/
    //status = HASHCRYPT_SHA(HASHCRYPT, kHASHCRYPT_Sha256, message, length, output, &outLength);
    //TEST_ASSERT(kStatus_Success == status);
    //TEST_ASSERT(outLength == 32u);
   // TEST_ASSERT(memcmp(output, sha256, outLength) == 0);

    McuLog_info("SHA-256 Test pass\r\n");
}


void JumpToBootloaderFUOTA(uint32_t addr)
{


#if McuLib_CONFIG_SDK_USE_FREERTOS
	portDISABLE_ALL_INTERRUPTS(); /* disable all interrupts, they get enabled in vStartScheduler() */
	vPortStopTickTimer(); /* tick timer shall not run until the RTOS scheduler is started */
	vTaskSuspendAll();
#endif



    uint32_t *vectorTable = (uint32_t*)addr;
     uint32_t sp = vectorTable[0];
     uint32_t pc = vectorTable[1];
     //uint32_t pc = addr + 171;


    typedef void(*app_entry_t)(void);

    uint32_t ss_stackPointer = 0;
    uint32_t ss_applicationEntry = 0;
    app_entry_t ss_application = 0;

    ss_stackPointer = sp;
    ss_applicationEntry = pc;
    ss_application = (app_entry_t)ss_applicationEntry;

    // Change MSP and PSP
    __set_MSP(ss_stackPointer);
    __set_PSP(ss_stackPointer);
    SCB->VTOR = addr;

    // Jump to application
    ss_application();

    // Should never reach here.
    __NOP();
}



static uint8_t W25_read_and_flash(lfs_file_t* file, bool readFromBeginning, size_t nofBytes) {
	  static int32_t filePos;
	  size_t fileSize;
	  uint8_t buf[512];

	  if( nofBytes > 512) {
	    nofBytes = 512;
	  }
	  if(readFromBeginning) {
	    lfs_file_rewind(JANPATCH_LFS_lfs,file);
	    filePos = 0;
	  } else {
	    lfs_file_seek(JANPATCH_LFS_lfs,file, filePos,LFS_SEEK_SET);
	  }

	  fileSize = lfs_file_size(JANPATCH_LFS_lfs, file);
	  filePos = lfs_file_tell(JANPATCH_LFS_lfs, file);
	  fileSize = fileSize - filePos;

	  while(fileSize>0){

		  if(fileSize > nofBytes)  {
		    if (lfs_file_read(JANPATCH_LFS_lfs, file, buf, nofBytes) < 0) {
		      return ERR_FAILED;
		    }


		  } else {
		    if (lfs_file_read(JANPATCH_LFS_lfs, file, buf, fileSize) < 0) {
		    }
			if(!(memory_erase((STARTADDRESS_IMAGE+filePos), 512))){
				memory_write((STARTADDRESS_IMAGE+filePos), buf, 512);
				McuLog_info("\r\n\r\n\r\n########## ========== FLASHING DATA TO MEMORY ========== ##########\r\n");
				McuLog_info("Flashed Block to address 0x%08X\r\n", STARTADDRESS_IMAGE+filePos);
				McuLog_info("File size remaning 0x%08X\r\n\r\n\r\n", fileSize- nofBytes);
				McuLog_info("\r\n\r\n\r\n");
			}
			else{
				return ERR_FAILED;
			}
		    return ERR_PARAM_SIZE; //EOF
		  }



		if(!(memory_erase((STARTADDRESS_IMAGE+filePos), 512))){
			memory_write((STARTADDRESS_IMAGE+filePos), buf, 512);
			McuLog_info("\r\n\r\n\r\n########## ========== FLASHING DATA TO MEMORY ========== ##########\r\n");
			McuLog_info("Flashed Block to address 0x%08X\r\n", STARTADDRESS_IMAGE+filePos);
			McuLog_info("File size remaning 0x%08X\r\n\r\n\r\n", fileSize- nofBytes);
			McuLog_info("\r\n\r\n\r\n");
		}
		else{
			return ERR_FAILED;
		}

	  filePos = filePos + nofBytes;
	  bzero(buf, nofBytes);
	  filePos = lfs_file_tell(JANPATCH_LFS_lfs, file);
	  fileSize = fileSize - nofBytes;

	  }
  return ERR_OK;
}


static void AppOnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      McuLog_info("Dbnc pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      McuLog_info("Dbnc repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      McuLog_info("Dbnc long pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      McuLog_info("Dbnc pressed repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      McuLog_info("Dbnc released: %d", buttons);
      break;

    default:
    case MCUDBNC_EVENT_END:
      McuLog_info("Dbnc end: %d", buttons);
      break;
  }
}


// function signatures
//size_t (*fread)(void*, size_t, size_t, JANPATCH_STREAM*);
//size_t (*fwrite)(const void*, size_t, size_t, JANPATCH_STREAM*);
//int    (*fseek)(JANPATCH_STREAM*, long int, int);
//long   (*ftell)(JANPATCH_STREAM*);

void progress(uint8_t percentage) {
    printf("Patch progress: %d%%\n", percentage);
}

// Functions similar to the POSIX functions
int bd_fseek(lfs_file_t *file, long int pos, int origin) {
    return (int)lfs_file_seek(JANPATCH_LFS_lfs, file, (lfs_soff_t)pos, origin);;
}

long int bd_ftell(lfs_file_t *file) {
    return (long int)lfs_file_tell(JANPATCH_LFS_lfs, file);
}

size_t bd_fread(void *buffer, size_t elements, size_t size, lfs_file_t *file) {
    return (size_t)lfs_file_read(JANPATCH_LFS_lfs, file, buffer, (lfs_size_t)size);
}

size_t bd_fwrite(const void *buffer, size_t elements, size_t size, lfs_file_t *file) {
    return lfs_file_write(JANPATCH_LFS_lfs, file, buffer, (lfs_size_t)size);
}


static void AppTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif

  McuLog_info("App Task started.");
  memory_init();
#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  McuTimeDate_Init(); /* if using external RTC it uses I2C, need to do this from clock task */
#endif
  BTN_RegisterAppCallback(AppOnDebounceEvent);
#if PL_CONFIG_HAS_LITTLE_FS
  McuLog_info("Mounting litteFS volume.");
  if(McuLFS_Mount(McuShell_GetStdio())==ERR_FAILED){
	  McuLog_info("Mounting failed please format device first");
  }
  else{

  }
#endif

#if PL_CONFIG_HAS_HW_RTC
  McuLog_info("Sync HW & Intern RTC.");
  if(McuTimeDate_Init()==ERR_FAILED){
	  McuLog_info("Mounting failed please format device first");
  }
  else{

  }

#endif
  for(;;) {
#if PL_CONFIG_USE_SD_CARD
    present = DISK_IsInserted((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
#endif
    if (BTN_IsPressed(BTN_WAKEUP)) {

//    	uint8_t result;
//    	LEDS_On(LEDS_GREEN);
//    	//JumpToBootloaderFUOTA(STARTADDRESS_IMAGE);
//    	JANPATCH_LFS_lfs = McuLFS_GetFileSystem();
//    	JANPATCH_STREAM patchFile;
//
//    	if (result < 0) {
//    		return ERR_FAILED;
//    	}
//
//    	result = lfs_file_open(JANPATCH_LFS_lfs, &patchFile, "patch.bin", LFS_O_RDWR | LFS_O_CREAT| LFS_O_APPEND);
//    	if (result < 0) {
//    		McuLog_info("Error open patch.bin \n\n\n\n");
//    		//return ERR_FAILED;
//    	}
//    	result = lfs_file_seek(JANPATCH_LFS_lfs, &patchFile, 0, LFS_SEEK_END);
//    	if (result < 0) {
//    		(void)lfs_file_close(JANPATCH_LFS_lfs, &patchFile);
//    		McuLog_info("Error seek patch.bin \n\n\n\n");
//    		//return ERR_FAILED;
//    	}
//
//    	uint32_t filesize;
//    	filesize = lfs_file_size(JANPATCH_LFS_lfs, &patchFile);

    	TestSha256();




    }
    if (BTN_IsPressed(BTN_UP)) {
    	//int result;
      McuLog_info("User Up pressed.");
      LEDS_Neg(LEDS_BLUE);

      //int res;
      JANPATCH_LFS_lfs = McuLFS_GetFileSystem();
//
//
//      JANPATCH_STREAM originalFile;
//
//      res = lfs_remove(JANPATCH_LFS_lfs, "original.bin");
//      if (res < 0) {
//    	  McuLog_info("Error remove original.bin.\n\n\n\n");
//        //return ERR_FAILED;
//      }
//      res = lfs_remove(JANPATCH_LFS_lfs, "patch.bin");
//      if (res < 0) {
//    	  McuLog_info("Error remove patch.bin.\n\n\n\n");
//        //return ERR_FAILED;
//      }
//
//      res = lfs_remove(JANPATCH_LFS_lfs, "newFile.bin");
//      if (res < 0) {
//    	  McuLog_info("Error remove newFile.bin.\n\n\n\n");
//        //return ERR_FAILED;
//      }
//
//
//      result = lfs_file_open(JANPATCH_LFS_lfs, &originalFile, "hello_wolrd_old.bin", LFS_O_RDWR | LFS_O_CREAT| LFS_O_APPEND);
//      if (result < 0) {
//    	  McuLog_info("Error open blinkyBinary_2.bin \n\n\n\n");
//        return ERR_FAILED;
//      }
//      result = lfs_file_seek(JANPATCH_LFS_lfs, &originalFile, 0, LFS_SEEK_END);
//      if (result < 0) {
//        (void)lfs_file_close(JANPATCH_LFS_lfs, &originalFile);
//        McuLog_info("Error seek blinkyBinary_2.bin \n\n\n\n");
//        return ERR_FAILED;
//      }
//
//      //lfs_file_write(JANPATCH_LFS_lfs, &originalFile, &ORIGINAL, sizeof(ORIGINAL));
//      //(void)lfs_file_close(JANPATCH_LFS_lfs, &originalFile);
//
//
//
//	  JANPATCH_STREAM patchFile;
//
//      if (result < 0) {
//        return ERR_FAILED;
//      }
//
//      result = lfs_file_open(JANPATCH_LFS_lfs, &patchFile, "patch.bin", LFS_O_RDWR | LFS_O_CREAT| LFS_O_APPEND);
//      if (result < 0) {
//    	  McuLog_info("Error open patch.bin \n\n\n\n");
//        //return ERR_FAILED;
//      }
//      result = lfs_file_seek(JANPATCH_LFS_lfs, &patchFile, 0, LFS_SEEK_END);
//      if (result < 0) {
//        (void)lfs_file_close(JANPATCH_LFS_lfs, &patchFile);
//        McuLog_info("Error seek patch.bin \n\n\n\n");
//        //return ERR_FAILED;
//      }
//
//      lfs_file_write(JANPATCH_LFS_lfs, &patchFile, &PATCH_blinky, sizeof(PATCH_blinky));
//      //(void)lfs_file_close(JANPATCH_LFS_lfs, &patchFile);
//
//
	  JANPATCH_STREAM newFile;
	  lfs_file_open(JANPATCH_LFS_lfs, &newFile, "newFile.bin",LFS_O_RDWR | LFS_O_CREAT| LFS_O_APPEND);

	  W25_read_and_flash(&newFile, true, 512);
	  (void)lfs_file_close(JANPATCH_LFS_lfs, &newFile);
//	  //(void)lfs_file_close(JANPATCH_LFS_lfs, &newFile);
//	    janpatch_ctx ctx = {
//	        { (unsigned char*)malloc(256), 256 }, // source buffer
//	        { (unsigned char*)malloc(256), 256 }, // diff buffer
//	        { (unsigned char*)malloc(256), 256 }, // target buffer
//
//	        &bd_fread,
//	        &bd_fwrite,
//	        &bd_fseek,
//	        &bd_ftell,
//
//			&progress
//	    };
//
//
////	    /* Go... */
//		int jpr = janpatch(ctx, &originalFile, &patchFile, &newFile);
//		if (jpr != 0) {
//			McuLog_info("Patching failed... %d\n", jpr);
//			return 1;
//		}
//		result = lfs_file_close(JANPATCH_LFS_lfs, &originalFile);
//	    if (result < 0) {
//	       McuLog_info("Error close originalFile.bin \n\n\n\n");
//	     }
//	    result = lfs_file_close(JANPATCH_LFS_lfs, &patchFile);
//	    if (result < 0) {
//	       McuLog_info("Error close patchFile.bin \n\n\n\n");
//	     }
//	    result = lfs_file_close(JANPATCH_LFS_lfs, &newFile);
//	    if (result < 0) {
//	       McuLog_info("Error close newFile.bin \n\n\n\n");
//	     }

		//McuLog_info("Patching OK: New size is %ld\n", newFile.ctz);

		McuLog_info("Calculating SHA256 hash...\n");
    }

#if 1
    BTN_PollDebounce(); /* check and debounce */
#else /* simply button polling */
    if (BTN_IsPressed(BTN_USER)) {
      McuLog_info("User Button pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
    if (BTN_IsPressed(BTN_WAKEUP)) {
      McuLog_info("Wakeup Button pressed.");
      LEDS_Neg(LEDS_GREEN);
    }
#endif
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS    McuTimeDate_CONFIG_TICK_TIME_MS

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  McuTimeDate_AddTick();
}

void APP_Run(void) {
  PL_Init(); /* init modules */
  //TestSha256();
  for(int i=0;i<2;i++) {
//  for(;;) {
#if PL_CONFIG_USE_SWO
    McuSWO_SendStr((unsigned char*)"Hello World using ITM console.\n");
#endif
    LEDS_On(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(100);
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_GREEN);
    McuWait_Waitms(100);
    LEDS_On(LEDS_BLUE);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_BLUE);
    McuWait_Waitms(100);
#if PL_CONFIG_HAS_USER_BUTTON
    if (BTN_IsPressed(BTN_USER)) {
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
    }
#endif
  } /* for */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      3000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  mutex = xSemaphoreCreateMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "Mutex");
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
