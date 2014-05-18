/* GNUC Startup library
 *    Copyright © 2005 Freescale semiConductor Inc. All Rights Reserved.
 *
 * $Date: 2011/09/21 06:41:34 $
 * $Revision: 1.4 $
 */

/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         
  typedef unsigned int uint32_t;

  /* ISR prototype */
  extern uint32_t __SP_INIT;
  extern
  #ifdef __cplusplus
  "C"
  #endif
  void __thumb_startup( void );
  typedef void (*const tIsrFunc)(void);
  typedef struct {
    void * __ptr;
    tIsrFunc __fun[0x77];
  } tVectorTable;

  void Cpu_Interrupt(void) {
    for(;;) {}
  }
  
  /*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
  /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */
  
  __attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */
  
    /* ISR name                             No. Address      Pri Name                           Description */
    &__SP_INIT,                        /* 0x00  0x00000000   -   ivINT_Initial_Stack_Pointer    */
    {
    (tIsrFunc)&__thumb_startup,        /* 0x01  0x00000004   -   ivINT_Initial_Program_Counter  */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x02  0x00000008   -2   ivINT_NMI                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x03  0x0000000C   -1   ivINT_Hard_Fault               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x04  0x00000010   -   ivINT_Mem_Manage_Fault         */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x05  0x00000014   -   ivINT_Bus_Fault                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x06  0x00000018   -   ivINT_Usage_Fault              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x07  0x0000001C   -   ivINT_Reserved7                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x08  0x00000020   -   ivINT_Reserved8                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x09  0x00000024   -   ivINT_Reserved9                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0A  0x00000028   -   ivINT_Reserved10               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0B  0x0000002C   -   ivINT_SVCall                   */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0C  0x00000030   -   ivINT_DebugMonitor             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0D  0x00000034   -   ivINT_Reserved13               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0E  0x00000038   -   ivINT_PendableSrvReq           */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0F  0x0000003C   -   ivINT_SysTick                  */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x10  0x00000040   -   ivINT_DMA0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x11  0x00000044   -   ivINT_DMA1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x12  0x00000048   -   ivINT_DMA2                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x13  0x0000004C   -   ivINT_DMA3                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x14  0x00000050   -   ivINT_DMA4                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x15  0x00000054   -   ivINT_DMA5                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x16  0x00000058   -   ivINT_DMA6                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x17  0x0000005C   -   ivINT_DMA7                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x18  0x00000060   -   ivINT_DMA8                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x19  0x00000064   -   ivINT_DMA9                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1A  0x00000068   -   ivINT_DMA10                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1B  0x0000006C   -   ivINT_DMA11                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1C  0x00000070   -   ivINT_DMA12                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1D  0x00000074   -   ivINT_DMA13                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1E  0x00000078   -   ivINT_DMA14                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1F  0x0000007C   -   ivINT_DMA15                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x20  0x00000080   -   ivINT_DMA_Error                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x21  0x00000084   -   ivINT_MCM                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x22  0x00000088   -   ivINT_FTFL                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x23  0x0000008C   -   ivINT_Read_Collision           */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x24  0x00000090   -   ivINT_LVD_LVW                  */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x25  0x00000094   -   ivINT_LLW                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x26  0x00000098   -   ivINT_Watchdog                 */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x27  0x0000009C   -   ivINT_RNG                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x28  0x000000A0   -   ivINT_I2C0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x29  0x000000A4   -   ivINT_I2C1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2A  0x000000A8   -   ivINT_SPI0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2B  0x000000AC   -   ivINT_SPI1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2C  0x000000B0   -   ivINT_SPI2                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2D  0x000000B4   -   ivINT_CAN0_ORed_Message_buffer */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2E  0x000000B8   -   ivINT_CAN0_Bus_Off             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2F  0x000000BC   -   ivINT_CAN0_Error               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x30  0x000000C0   -   ivINT_CAN0_Tx_Warning          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x31  0x000000C4   -   ivINT_CAN0_Rx_Warning          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x32  0x000000C8   -   ivINT_CAN0_Wake_Up             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x33  0x000000CC   -   ivINT_Reserved51               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x34  0x000000D0   -   ivINT_Reserved52               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x35  0x000000D4   -   ivINT_CAN1_ORed_Message_buffer */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x36  0x000000D8   -   ivINT_CAN1_Bus_Off             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x37  0x000000DC   -   ivINT_CAN1_Error               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x38  0x000000E0   -   ivINT_CAN1_Tx_Warning          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x39  0x000000E4   -   ivINT_CAN1_Rx_Warning          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3A  0x000000E8   -   ivINT_CAN1_Wake_Up             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3B  0x000000EC   -   ivINT_Reserved59               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3C  0x000000F0   -   ivINT_Reserved60               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3D  0x000000F4   -   ivINT_UART0_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3E  0x000000F8   -   ivINT_UART0_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x3F  0x000000FC   -   ivINT_UART1_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x40  0x00000100   -   ivINT_UART1_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x41  0x00000104   -   ivINT_UART2_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x42  0x00000108   -   ivINT_UART2_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x43  0x0000010C   -   ivINT_UART3_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x44  0x00000110   -   ivINT_UART3_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x45  0x00000114   -   ivINT_UART4_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x46  0x00000118   -   ivINT_UART4_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x47  0x0000011C   8   ivINT_UART5_RX_TX              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x48  0x00000120   8   ivINT_UART5_ERR                */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x49  0x00000124   -   ivINT_ADC0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4A  0x00000128   -   ivINT_ADC1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4B  0x0000012C   -   ivINT_CMP0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4C  0x00000130   -   ivINT_CMP1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4D  0x00000134   -   ivINT_CMP2                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4E  0x00000138   -   ivINT_FTM0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x4F  0x0000013C   -   ivINT_FTM1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x50  0x00000140   -   ivINT_FTM2                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x51  0x00000144   -   ivINT_CMT                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x52  0x00000148   -   ivINT_RTC                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x53  0x0000014C   -   ivINT_Reserved83               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x54  0x00000150   -   ivINT_PIT0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x55  0x00000154   -   ivINT_PIT1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x56  0x00000158   -   ivINT_PIT2                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x57  0x0000015C   -   ivINT_PIT3                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x58  0x00000160   -   ivINT_PDB0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x59  0x00000164   -   ivINT_USB0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5A  0x00000168   -   ivINT_USBDCD                   */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5B  0x0000016C   -   ivINT_ENET_1588_Timer          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5C  0x00000170   -   ivINT_ENET_Transmit            */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5D  0x00000174   -   ivINT_ENET_Receive             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5E  0x00000178   -   ivINT_ENET_Error               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x5F  0x0000017C   -   ivINT_I2S0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x60  0x00000180   8   ivINT_SDHC                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x61  0x00000184   -   ivINT_DAC0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x62  0x00000188   -   ivINT_DAC1                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x63  0x0000018C   -   ivINT_TSI0                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x64  0x00000190   -   ivINT_MCG                      */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x65  0x00000194   -   ivINT_LPTimer                  */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x66  0x00000198   -   ivINT_Reserved102              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x67  0x0000019C   -   ivINT_PORTA                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x68  0x000001A0   -   ivINT_PORTB                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x69  0x000001A4   -   ivINT_PORTC                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6A  0x000001A8   -   ivINT_PORTD                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6B  0x000001AC   -   ivINT_PORTE                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6C  0x000001B0   -   ivINT_Reserved108              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6D  0x000001B4   -   ivINT_Reserved109              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6E  0x000001B8   -   ivINT_Reserved110              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x6F  0x000001BC   -   ivINT_Reserved111              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x70  0x000001C0   -   ivINT_Reserved112              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x71  0x000001C4   -   ivINT_Reserved113              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x72  0x000001C8   -   ivINT_Reserved114              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x73  0x000001CC   -   ivINT_Reserved115              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x74  0x000001D0   -   ivINT_Reserved116              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x75  0x000001D4   -   ivINT_Reserved117              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x76  0x000001D8   -   ivINT_Reserved118              */
    (tIsrFunc)&Cpu_Interrupt           /* 0x77  0x000001DC   -   ivINT_Reserved119              */
    }
  };
  /*lint -restore Enable MISRA rule (11.4) checking. */
  


/*!
** @}
*/
