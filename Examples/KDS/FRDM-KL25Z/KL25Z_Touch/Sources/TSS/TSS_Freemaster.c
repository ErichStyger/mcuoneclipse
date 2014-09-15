/**HEADER********************************************************************
* 
* Copyright (c) 2008-2011 Freescale Semiconductor;
* All Rights Reserved                       
*
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: TSS_Freemaster.c$
* $Version : 3.6.21.0$
* $Date    : Sep-18-2012$
*
* Comments:
*
*   This file contains FreeMASTER interface for TSS variables.
*
*END************************************************************************/

#include "TSS_API.h"

#if TSS_USE_FREEMASTER_GUI  
  #include "freemaster.h"

  typedef struct {
    UINT32 indexdata;
    UINT32 flagreg;
  } FMSTR_WRITE_STRUCT;
  
  FMSTR_WRITE_STRUCT fmstr_write = {0xffffffff, 0xff};  
  
  typedef struct {
      UINT8 low_bit            :1;
      UINT8 low_bit1           :1;
      UINT8 low_bit2           :1;
      UINT8 low_bit3           :1;
      UINT8 low_bit4           :1;
      UINT8 low_bit5           :1;
      UINT8 low_bit6           :1;
      UINT8 low_bit7           :1;
  } FMSTR_BIT_STRUCT;

  typedef struct{
   UINT8             ptr_size;
   FMSTR_BIT_STRUCT  low_bit_mask;
  } FMSTR_CONFIG_STRUCT;

  volatile FMSTR_CONFIG_STRUCT fmstr_config = {sizeof(const UINT8 *), {1,0,0,0,0,0,0,0}};

  /////////////////////////////////////////////////////////////////////////
  
  extern UINT16 tss_au16ElecBaseline[TSS_N_ELECTRODES];
  extern UINT8 tss_cu8NumElecs;
  extern const UINT8 tss_cu8NumCtrls;
  extern const UINT16 tss_cu16Version;
#if TSS_N_CONTROLS > 0
  extern const UINT8 * const tss_acpsCSStructs[TSS_N_CONTROLS];
  extern const UINT8 * const tss_acpsDecContext[TSS_N_CONTROLS];
#endif
  void TSS_FmstrCall(void);
  void TSS_FmstrIsrCallback(void);
 
 #if FMSTR_USE_TSA 
  /* FreeMASTER TSA table for TSS variables */
  FMSTR_TSA_TABLE_BEGIN(TSS_Table)
      //FreeMASTER interface to write
      FMSTR_TSA_RW_VAR(fmstr_write,                         FMSTR_TSA_USERTYPE(FMSTR_WRITE_STRUCT))
      FMSTR_TSA_STRUCT(FMSTR_WRITE_STRUCT)
      FMSTR_TSA_MEMBER(FMSTR_WRITE_STRUCT, indexdata,       FMSTR_TSA_UINT32)
      FMSTR_TSA_MEMBER(FMSTR_WRITE_STRUCT, flagreg,         FMSTR_TSA_UINT32)

      FMSTR_TSA_RW_VAR(fmstr_config,                        FMSTR_TSA_USERTYPE(FMSTR_CONFIG_STRUCT))
      FMSTR_TSA_STRUCT(FMSTR_CONFIG_STRUCT)
  	  FMSTR_TSA_MEMBER(FMSTR_CONFIG_STRUCT, ptr_size,       FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(FMSTR_CONFIG_STRUCT, low_bit_mask,   FMSTR_TSA_UINT8)
      
      //TSS system config menu
      FMSTR_TSA_RW_VAR(tss_CSSys,                                  FMSTR_TSA_USERTYPE(TSS_CSSystem))
      FMSTR_TSA_STRUCT(TSS_CSSystem)
      FMSTR_TSA_MEMBER(TSS_CSSystem, Faults,                       FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, SystemConfig,                 FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, NSamples,                     FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, DCTrackerRate,                FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, ResponseTime,                 FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, StuckKeyTimeout,              FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, LowPowerScanPeriod,           FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, LowPowerElectrode,            FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, LowPowerElectrodeSensitivity, FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, SystemTrigger,                FMSTR_TSA_UINT8)
      FMSTR_TSA_MEMBER(TSS_CSSystem, AutoTriggerModuloValue,       FMSTR_TSA_UINT8)
  
      //electrodes config menu
  #if TSS_USE_DELTA_LOG
      FMSTR_TSA_RO_VAR(tss_ai8InstantDelta,     FMSTR_TSA_UINT8)
  #endif
  #if TSS_USE_SIGNAL_LOG
      FMSTR_TSA_RO_VAR(tss_au16InstantSignal,   FMSTR_TSA_UINT16)
  #endif
      FMSTR_TSA_RO_VAR(tss_au16ElecBaseline,    FMSTR_TSA_UINT16)
      FMSTR_TSA_RO_VAR(tss_au8ElectrodeStatus,  FMSTR_TSA_UINT8)
      FMSTR_TSA_RW_VAR(tss_au8Sensitivity,      FMSTR_TSA_UINT8)
      FMSTR_TSA_RW_VAR(tss_au8ElectrodeEnablers,FMSTR_TSA_UINT8) 
      FMSTR_TSA_RO_VAR(tss_cu8NumElecs,         FMSTR_TSA_UINT8)
        
      //controls menu
      FMSTR_TSA_RO_VAR(tss_cu8NumCtrls,         FMSTR_TSA_UINT8)
#if TSS_N_CONTROLS > 0
      FMSTR_TSA_RO_VAR(tss_acpsCSStructs,       FMSTR_TSA_UINT32)
      FMSTR_TSA_RO_VAR(tss_acpsDecContext,      FMSTR_TSA_UINT32)
#endif
      // TSS version information
      FMSTR_TSA_RO_VAR(tss_cu16Version,         FMSTR_TSA_UINT16)
  FMSTR_TSA_TABLE_END()
#endif

  /* 
   * FreeMASTER interface to write configure TSS feature over FreeMASTER
   */
  void TSS_FmstrCall(void)
  {
    UINT16 u16DummyVersion;
    FMSTR_CONFIG_STRUCT temp = fmstr_config;
    TSS_CONTROL_ID controlID;
    
    if (fmstr_write.flagreg != 0xff)
    {
      UINT8 type = (UINT8) (fmstr_write.indexdata>>24);
      UINT8 index = (UINT8) ((fmstr_write.indexdata>>16)&0xff);
      UINT16 data = (UINT16) ((fmstr_write.indexdata)&0xffff);
        
      *((UINT8*)&controlID)  = (UINT8) ((fmstr_write.indexdata>>8)&0xff);
        switch (type)
        {
        case 0:
          TSS_SetSystemConfig(index, data);
          break;
        case 1:
          TSS_SetKeypadConfig(controlID, index, (UINT8)(data&0xff));
          break;
        case 2:
          TSS_SetSliderConfig(controlID, index, (UINT8)(data&0xff));
          break;
        case 3:
          TSS_SetRotaryConfig(controlID, index, (UINT8)(data&0xff));
          break;
        }
        fmstr_write.flagreg = 0xff;
    }
    /* Dummy usage of tss_cu16Version to avoid remove from the memory */
    u16DummyVersion = tss_cu16Version;
    u16DummyVersion++;
    
  }
  
  /* 
   * User callback called from FMSTR_Isr() handler
   */
  void TSS_FmstrIsrCallback(void)
  {
    /* Set Sample Interrupted flag, because SCI measures at background and it can interrupt sampling of GPIO based methods */
    TSS_SET_SAMPLE_INTERRUPTED();
  }
#else
  void TSS_FmstrIsrCallback(void);

  void TSS_FmstrIsrCallback(void)
  {

  }
#endif /* End of TSS_USE_FREEMASTER_GUI */
