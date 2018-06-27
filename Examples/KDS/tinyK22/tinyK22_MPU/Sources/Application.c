/*
 * Application.c
 *
 *  Created on: 25.06.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "Cpu.h"
#if configUSE_MPU_SUPPORT
  #include "SysMPU.h"
#endif

#if configUSE_MPU_SUPPORT
BaseType_t xPortRaisePrivilege( void ) {

}

void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION * const xRegions, StackType_t *pxBottomOfStack, uint32_t ulStackDepth ) PRIVILEGED_FUNCTION {
  if (xRegions==NULL) {
    int ul;
    /* no MPU regions are defined, so allow access to everything */
    xMPUSettings->xRegion[0].ulRegionBaseAddress  = 0x00000000;
    xMPUSettings->xRegion[0].ulRegionAttribute = portMPU_REGION_READ_WRITE;
    /* Invalidate all other regions.   */
    for(ul = 1; ul < portNUM_CONFIGURABLE_REGIONS; ul++) {
      xMPUSettings->xRegion[ul].ulRegionBaseAddress = 0x00000000UL;
      xMPUSettings->xRegion[ul].ulRegionAttribute = 0UL;
    }
   } else {

  }
}
#endif

static void AppTask(void *param) {
  (void)param;
  for(;;) {
    LED1_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}

#define CLK_GATE_REG_OFFSET_SHIFT 16U
#define CLK_GATE_REG_OFFSET_MASK 0xFFFF0000U
#define CLK_GATE_BIT_SHIFT_SHIFT 0U
#define CLK_GATE_BIT_SHIFT_MASK 0x0000FFFFU

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((x)&CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((x)&CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

/** Peripheral SIM base address */
#define SIM_BASE                                 (0x40047000u)

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                  \
    ((((reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

static inline void CLOCK_EnableClock(int name) {
    uint32_t regAddr = SIM_BASE + CLK_GATE_ABSTRACT_REG_OFFSET((uint32_t)name);
    (*(volatile uint32_t *)regAddr) |= (1U << CLK_GATE_ABSTRACT_BITS_SHIFT((uint32_t)name));
}

#define kCLOCK_Sysmpu0   CLK_GATE_DEFINE(0x1040U, 2U)

#define SYSMPU_CLOCKS  \
    {                  \
        kCLOCK_Sysmpu0 \
    }

static const int g_sysmpuClock[] = SYSMPU_CLOCKS;

static void TestMPU(void) {
  #define TCML_BASE 0x20000000// Upper SRAM bitband region
  #define TCML_SIZE 0x00010000

  CLOCK_EnableClock(g_sysmpuClock[0]);

  /* MPU Configuration */
  SYSMPU->WORD[0][0] = 0; /* start address */
  SYSMPU->WORD[0][1] = 0xfffffff0; /* end address */
  SYSMPU->WORD[0][2] = 0;
  SYSMPU->WORD[0][3] = 1; /* region is valid */

#if 0
  MPU_RGD0_WORD2 = 0;// Disable RGD0
  // Set RGD1
  MPU_RGD1_WORD0 = 0;// Start address
  MPU_RGD1_WORD1 = (TCML_BASE + TCML_SIZE);// End Address
  MPU_RGD1_WORD2 = 0x0061F7DF; //(No magic #’s)// Bus master 3: SM all access (List what the Bus  masters are in addition to #’s)
  // Bus master 2: SM all access
  // Bus master 2: UM all access
  // Bus master 1: SM all access
  // Bus master 1: UM all access
  // Bus master 0: SM all access
  // Bus master 0: UM all access
  MPU_RGD1_WORD3 = 0x00000001;// region is valid
  // Set RGD2
  MPU_RGD2_WORD0 = (TCML_BASE + TCML_SIZE + 0x40);
  MPU_RGD2_WORD1 = 0xFFFFFFFF;// End Address
  MPU_RGD2_WORD2 = 0x0061F7DF;
  MPU_RGD2_WORD3 = 0x00000001;// region is valid
#endif
  // Enable MPU function
  SYSMPU->CESR = SYSMPU_CESR_VLD_MASK;
  for(;;) {}
}

void APP_Run(void) {
  TestMPU();
#if 0
  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
#endif
  vTaskStartScheduler();
  for(;;){}
}
