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
    tIsrFunc __fun[0x2F];
  } tVectorTable;

  void Cpu_Interrupt(void) {
    for(;;) {}
  }
  
  /*lint -esym(765,__vect_table) Disable MISRA rule (8.10) checking for symbols (__vect_table). Definition of the interrupt vector table placed by linker on a predefined location. */
  /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. Need to explicitly cast pointers to the general ISR for Interrupt vector table */
  
  __attribute__ ((section (".vectortable"))) const tVectorTable __vect_table = { /* Interrupt vector table */
  
    /* ISR name                             No. Address      Pri Name                         */
    &__SP_INIT,                        /* 0x00  0x00000000   -   ivINT_Initial_Stack_Pointer  */
    {
    (tIsrFunc)&__thumb_startup,        /* 0x01  0x00000004   -   ivINT_Initial_Program_Counter */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x02  0x00000008   -2  ivINT_NMI                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x03  0x0000000C   -1  ivINT_Hard_Fault              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x04  0x00000010   -   ivINT_Reserved4               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x05  0x00000014   -   ivINT_Reserved5               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x06  0x00000018   -   ivINT_Reserved6               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x07  0x0000001C   -   ivINT_Reserved7               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x08  0x00000020   -   ivINT_Reserved8               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x09  0x00000024   -   ivINT_Reserved9               */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0A  0x00000028   -   ivINT_Reserved10              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0B  0x0000002C   -   ivINT_SVCall                  */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0C  0x00000030   -   ivINT_Reserved12              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0D  0x00000034   -   ivINT_Reserved13              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0E  0x00000038   -   ivINT_PendableSrvReq          */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x0F  0x0000003C   -   ivINT_SysTick                 */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x10  0x00000040   -   ivINT_DMA0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x11  0x00000044   -   ivINT_DMA1                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x12  0x00000048   -   ivINT_DMA2                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x13  0x0000004C   -   ivINT_DMA3                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x14  0x00000050   -   ivINT_Reserved20              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x15  0x00000054   -   ivINT_FTFA                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x16  0x00000058   -   ivINT_LVD_LVW                 */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x17  0x0000005C   -   ivINT_LLW                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x18  0x00000060   -   ivINT_I2C0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x19  0x00000064   -   ivINT_I2C1                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1A  0x00000068   -   ivINT_SPI0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1B  0x0000006C   -   ivINT_SPI1                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1C  0x00000070   -   ivINT_UART0                   */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1D  0x00000074   -   ivINT_UART1                   */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1E  0x00000078   -   ivINT_UART2                   */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x1F  0x0000007C   -   ivINT_ADC0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x20  0x00000080   -   ivINT_CMP0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x21  0x00000084   -   ivINT_TPM0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x22  0x00000088   -   ivINT_TPM1                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x23  0x0000008C   -   ivINT_TPM2                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x24  0x00000090   -   ivINT_RTC                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x25  0x00000094   -   ivINT_RTC_Seconds             */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x26  0x00000098   -   ivINT_PIT                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x27  0x0000009C   -   ivINT_Reserved39              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x28  0x000000A0   -   ivINT_USB0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x29  0x000000A4   -   ivINT_DAC0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2A  0x000000A8   -   ivINT_TSI0                    */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2B  0x000000AC   -   ivINT_MCG                     */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2C  0x000000B0   -   ivINT_LPTimer                 */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2D  0x000000B4   -   ivINT_Reserved45              */
    (tIsrFunc)&Cpu_Interrupt,          /* 0x2E  0x000000B8   -   ivINT_PORTA                   */
    (tIsrFunc)&Cpu_Interrupt           /* 0x2F  0x000000BC   -   ivINT_PORTD                   */
    }
  };
  /*lint -restore Enable MISRA rule (11.4) checking. */
  

/*!
** @}
*/
