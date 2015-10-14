/*
 * host.c
 *      Author: Erich Styger
 */

#include "host.h"
#include "msd_commands.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "FsMSD1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"

#define ONLY_HOST 0 /* if set to 1, no RTOS runs */

static void print(unsigned char *str) {
#if !ONLY_HOST
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}

static void CheckStatus(void) {
  switch (FsMSD1_GetDeviceStatus()) {
     case USB_DEVICE_IDLE:
       break;
     case USB_DEVICE_ATTACHED:
       LEDR_Off();
       LEDG_On();
       print((unsigned char*)"Mass Storage Device Attached\n" );
       break;
     case USB_DEVICE_SET_INTERFACE_STARTED:
       break;
     case USB_DEVICE_INTERFACED:
       break;
     case USB_DEVICE_DETACHED:
       LEDR_On();
       LEDG_Off();
       print((unsigned char*)"\nMass Storage Device Detached\n" );
       break;
     case USB_DEVICE_OTHER:
       break;
     default:
       print((unsigned char*)"Unknown Mass Storage Device State\n");
       break;
  } /* switch */
}

#if 1
#define BSP_CLOCK_SRC           (50000000ul)        // crystal, oscillator freq.
#define BSP_REF_CLOCK_SRC           (2000000ul)       // must be 2-4MHz

#define BSP_CORE_DIV                (1)
#define BSP_BUS_DIV                 (1)
#define BSP_FLEXBUS_DIV             (1)
#define BSP_FLASH_DIV               (2)
// BSP_CLOCK_MUL from interval 24 - 55
#define BSP_CLOCK_MUL               (24)    // 48MHz

#define BSP_REF_CLOCK_DIV           (BSP_CLOCK_SRC / BSP_REF_CLOCK_SRC)

#define BSP_CLOCK                   (BSP_REF_CLOCK_SRC * BSP_CLOCK_MUL)
#define BSP_CORE_CLOCK              (BSP_CLOCK / BSP_CORE_DIV)          // CORE CLK, max 100MHz
#define BSP_SYSTEM_CLOCK            (BSP_CORE_CLOCK)                    // SYSTEM CLK, max 100MHz
#define BSP_BUS_CLOCK               (BSP_CLOCK / BSP_BUS_DIV)       // max 50MHz
#define BSP_FLEXBUS_CLOCK           (BSP_CLOCK / BSP_FLEXBUS_DIV)
#define BSP_FLASH_CLOCK             (BSP_CLOCK / BSP_FLASH_DIV)     // max 25MHz



static unsigned char pll_init()
{
    uint_32 temp_reg, i;
    
    /* First move to FBE mode */
#ifdef MCU_MK60N512VMD100
  /* Enable external oscillator, RANGE=0, HGO=, EREFS=, LP=, IRCS= */
  MCG_C2 = 0;
#else
  /* Enable external oscillator, RANGE=2, HGO=1, EREFS=1, LP=0, IRCS=0 */
  MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK|MCG_C2_IRCS_MASK;
#endif
  
  // after initialization of oscillator release latched state of oscillator and GPIO
  SIM_SCGC4 |= SIM_SCGC4_LLWU_MASK;
  LLWU_CS |= LLWU_CS_ACKISO_MASK;

    /* Select external oscillator and Reference Divider and clear IREFS to start ext osc
     CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0 */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);

#if defined (MCU_MK40N512VMD100)
  /* Wait for oscillator to initialize */
    while (!(MCG_S & MCG_S_OSCINIT_MASK)){};
#endif

   /* Wait for Reference clock Status bit to clear */
    while (MCG_S & MCG_S_IREFST_MASK){};

    /* Wait for clock status bits to show clock source is ext ref clk */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2){};

#ifdef MCU_MK60N512VMD100
  MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1); /* 24 */
#else
    MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1) | MCG_C5_PLLCLKEN_MASK;
#endif
    /* Ensure MCG_C6 is at the reset default of 0. LOLIE disabled,
     PLL enabled, clk monitor disabled, PLL VCO divider is clear */
    MCG_C6 = 0;

    
        temp_reg = FMC_PFAPR; // store present value of FMC_PFAPR
        
        // set M0PFD through M7PFD to 1 to disable prefetch
        FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK
            | FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
            | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
    
        /* Set system options dividers */
        SIM_CLKDIV1 =   SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV - 1) |   /* core/system clock */
                        SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV - 1)  |   /* peripheral clock; */
                        SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |  /* FlexBus clock driven to the external pin (FB_CLK)*/
                        SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV - 1);     /* flash clock */
    
        // wait for dividers to change
        for (i = 0; i < BSP_FLASH_DIV - 1; i++);
        
        FMC_PFAPR = temp_reg; // re-store original value of FMC_PFAPR
    
    
      
    /* Set the VCO divider and enable the PLL, LOLIE = 0, PLLS = 1, CME = 0, VDIV = */
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24); /* 2MHz * BSP_CLOCK_MUL */
    
    while (!(MCG_S & MCG_S_PLLST_MASK)){}; /* wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_LOCK_MASK)){}; /* Wait for LOCK bit to set */

    /* Transition into PEE by setting CLKS to 0
    CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0 */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;

    /* Wait for clock status bits to update */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){};

    return 0;
} //pll_init


static void _bsp_platform_init(void) {
  NVICICPR2 = (1 << 9);                     //Clear any pending interrupts on USB
  NVICISER2 = (1 << 9);                     //Enable interrupts from USB module
  
  /* Init PLL */
  pll_init();
  
    /* Disable MPU. All accesses from all bus masters are allowed */
  MPU_CESR = 0;
   
  /* 1. Configure USB to be clocked from PLL */
    SIM_SOPT2 |= SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK;
    
#if PLL_96
    /* 2. USB freq divider */
    SIM_CLKDIV2 = 0x02;
#endif /* PLL_96 */

    /* 3. Enable USB-OTG IP clocking */
  SIM_SCGC4 |= (SIM_SCGC4_USBOTG_MASK);      
  
  /* old documentation writes setting this bit is mandatory */
    USB0_USBTRC0 = 0x40;
     
    /* Weak pulldowns */
    USB0_USBCTRL = 0x40;
  
}
#endif

#if ONLY_HOST
static void HOST_Run(void) {
  LEDB_On();
  for(;;) {
    FsMSD1_AppTask();
    CheckStatus();
  }
}
#endif

#if !ONLY_HOST
static portTASK_FUNCTION(HostTask, pvParameters) {
  (void)pvParameters; /* not used */
  FsMSD1_HostInit();
  for(;;) {
    FsMSD1_AppTask();
    CheckStatus();
    FRTOS1_taskYIELD();
    //FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}
#endif

void Cpu_SetBASEPRI(uint32_t Level);
byte USB1_Init(void);
#include "Cpu.h"

void HOST_Init(void) {
  _bsp_platform_init();
#if ONLY_HOST
  USB1_Init();
  _bsp_platform_init();
  FsMSD1_HostInit();
  /* Enable interrupts of the given priority level */
  Cpu_SetBASEPRI(0U);
  HOST_Run();
#else
  if (FRTOS1_xTaskCreate(HostTask, "Host", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

