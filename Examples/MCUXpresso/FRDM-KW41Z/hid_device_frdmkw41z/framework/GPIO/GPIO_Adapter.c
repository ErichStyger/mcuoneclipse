/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file GPIO_IrqAdapter.c
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_os_abstraction.h"

#include "GPIO_Adapter.h"
#include "gpio_pins.h"
#include "FunctionLib.h"

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#define gGpio_FoundPortIsr_c  0x01
#define gGpio_FoundSimilar_c  0x02


/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */


/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
static void Gpio_CommonIsr(void);
static gpioStatus_t Gpio_InstallPortISR(IRQn_Type irqId, uint32_t nvicPrio);


/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
static gpioIsr_t mGpioIsr[gGpioMaxIsrEntries_c];
static uint16_t  mGpioIsrCount=0;
static PORT_Type *const maPortBases[] = PORT_BASE_PTRS;
static GPIO_Type *const maGpioBases[] = GPIO_BASE_PTRS;
static IRQn_Type maPortIrqId[] = PORT_IRQS;

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */
uint32_t GpioGetPinPCR(gpioPort_t gpioPort, uint8_t gpioPin)
{
    PORT_Type *base = maPortBases[gpioPort];
    return (uint32_t)base->PCR[gpioPin];   
}
/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */
void GpioSetPinPCR(gpioPort_t gpioPort, uint8_t gpioPin, uint32_t pcr)
{
    PORT_Type *base = maPortBases[gpioPort];
    base->PCR[gpioPin] = pcr;   
}
/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */
void GpioSetPinPCR_ISF_Preserved(gpioPort_t gpioPort, uint8_t gpioPin, uint32_t pcr)
{
    PORT_Type *base = maPortBases[gpioPort];
    base->PCR[gpioPin] = pcr & (~PORT_PCR_ISF_MASK) ;   
}

pinInterrupt_t GpioGetPinInterrupt(gpioPort_t gpioPort, uint8_t gpioPin)
{
    PORT_Type *base = maPortBases[gpioPort];
    uint32_t temp = (base->PCR[gpioPin] & PORT_PCR_IRQC_MASK) >> PORT_PCR_IRQC_SHIFT;
    return (pinInterrupt_t)temp;
}

void GpioSetPinInterrupt(gpioPort_t gpioPort, uint8_t gpioPin, pinInterrupt_t mode)
{
    PORT_SetPinInterruptConfig(maPortBases[gpioPort], gpioPin, (port_interrupt_t)(mode));
}

void GpioSetSlewRate(gpioPort_t gpioPort, uint8_t gpioPin, pinSlewRate_t slewRate)
{
    PORT_Type *base = maPortBases[gpioPort];
    
    if( slewRate < pinSlewRate_Invalid_c )
    {
        base->PCR[gpioPin] &= ~PORT_PCR_SRE_MASK;
        base->PCR[gpioPin] |= PORT_PCR_SRE(slewRate);
    }
}

void GpioSetOpenDrain(gpioPort_t gpioPort, uint8_t gpioPin, bool_t enable)
{
#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    PORT_Type *base = maPortBases[gpioPort];

    if(enable)
    {
        base->PCR[gpioPin] |= PORT_PCR_ODE_MASK;
    }
    else
    {
        base->PCR[gpioPin] &= ~PORT_PCR_ODE_MASK;
    }
#endif /* FSL_FEATURE_PORT_HAS_OPEN_DRAIN */
}

/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioSetPassiveFilter(gpioPort_t gpioPort, uint8_t gpioPin, bool_t enable)
{
    PORT_Type *base = maPortBases[gpioPort];
    
    if(enable)
    {
        base->PCR[gpioPin] |= PORT_PCR_PFE_MASK;
    }
    else
    {
        base->PCR[gpioPin] &= ~PORT_PCR_PFE_MASK;
    }
}

/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioSetPinPullMode(gpioPort_t gpioPort, uint8_t gpioPin, pinPullSelect_t pullSelect)
{
  uint32_t pcr;
  PORT_Type *base = maPortBases[gpioPort];
  pcr = base->PCR[gpioPin];
  pcr &= ~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
  if(pullSelect < pinPull_Disabled_c)
  {
    pcr |= pullSelect | PORT_PCR_PE_MASK;
  }
  base->PCR[gpioPin] = pcr;
}
/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioSetPinMux(gpioPort_t gpioPort, uint8_t gpioPin, pinMux_t pinMux)
{
  PORT_SetPinMux(maPortBases[gpioPort], (uint32_t) gpioPin, (port_mux_t)pinMux);
}

/*! *********************************************************************************
* \brief  
*
* \param[in]  
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioSetPinMux_ISF_Preserved(gpioPort_t gpioPort, uint8_t gpioPin, pinMux_t pinMux)
{
    PORT_Type *base = maPortBases[gpioPort];
    base->PCR[gpioPin] = (base->PCR[gpioPin] & ~(PORT_PCR_MUX_MASK | PORT_PCR_ISF_MASK)) | PORT_PCR_MUX(pinMux);
}
/*! *********************************************************************************
* \brief  
*
* \param[in]  pInputConfig             pointer to a gpioInputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioClearPinIntFlag(const gpioInputPinConfig_t* pInputConfig)
{
  PORT_ClearPinsInterruptFlags(maPortBases[pInputConfig->gpioPort], 1<<pInputConfig->gpioPin);
}
/*! *********************************************************************************
* \brief  
*
* \param[in]  pInputConfig             pointer to a gpioInputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

uint32_t GpioIsPinIntPending(const gpioInputPinConfig_t* pInputConfig)
{
  uint32_t isfr = PORT_GetPinsInterruptFlags(maPortBases[pInputConfig->gpioPort]);
  return ((isfr >> pInputConfig->gpioPin) & 0x01U);
}

/*! *********************************************************************************
* \brief  Set the logical level of the output pin
*
* \param[in]  pOutputConfig             pointer to a gpioOutputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioSetPinOutput(const gpioOutputPinConfig_t* pOutputConfig)
{
  GPIO_SetPinsOutput(maGpioBases[pOutputConfig->gpioPort], 1<< pOutputConfig->gpioPin);
  
}
/*! *********************************************************************************
* \brief  Clear the logical level of the output pin
*
* \param[in]  pOutputConfig             pointer to a gpioOutputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioClearPinOutput(const gpioOutputPinConfig_t* pOutputConfig)
{
  GPIO_ClearPinsOutput(maGpioBases[pOutputConfig->gpioPort], 1<< pOutputConfig->gpioPin);
  
}
/*! *********************************************************************************
* \brief  Toggle the logical level of the output pin
*
* \param[in]  pOutputConfig             pointer to a gpioOutputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

void GpioTogglePinOutput(const gpioOutputPinConfig_t* pOutputConfig)
{
  GPIO_TogglePinsOutput(maGpioBases[pOutputConfig->gpioPort], 1<< pOutputConfig->gpioPin);
  
}

/*! *********************************************************************************
* \brief  Reads the logical level of the output pin
*
* \param[in]  pOutputConfig             pointer to a gpioOutputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */
uint32_t GpioReadOutputPin(const gpioOutputPinConfig_t* pOutputConfig)
{
    return GPIO_ReadPinInput(maGpioBases[pOutputConfig->gpioPort], pOutputConfig->gpioPin);
}

/*! *********************************************************************************
* \brief  Reads the logical level of the input pin
*
* \param[in]  pInputConfig             pointer to a gpioInputPinConfig_t structure 
*
* \return  logical level of the input pin
*
********************************************************************************** */

uint32_t GpioReadPinInput(const gpioInputPinConfig_t* pInputConfig)
{
  return GPIO_ReadPinInput(maGpioBases[pInputConfig->gpioPort], pInputConfig->gpioPin);
}
/*! *********************************************************************************
* \brief  Initializes input pins
*
* \param[in]  pInputConfig             table of input pins configuration structures
* \param[in]  noOfElements             number of elements of the table
*
* \return  install status
*
********************************************************************************** */

bool_t GpioInputPinInit(const gpioInputPinConfig_t* pInputConfig, uint32_t noOfElements )
{
  port_pin_config_t pinConfig;
  gpio_pin_config_t gpioConfig;
  if(pInputConfig == NULL)
  {
    return FALSE;
  }
  while(noOfElements)
  {
    if((pInputConfig->gpioPin > 31) 
       || (pInputConfig->gpioPort >= FSL_FEATURE_SOC_GPIO_COUNT)   
         || (pInputConfig->pullSelect >= pinPull_Invalid_c)    
           || (pInputConfig->interruptSelect >= pinInt_Invalid_c))
    {
      return FALSE;
    }  
    uint16_t* ptr = (uint16_t*)&pinConfig;
    *ptr = 0;
    pinConfig.pullSelect = (pInputConfig->pullSelect == pinPull_Disabled_c)?(kPORT_PullDisable):((pInputConfig->pullSelect == pinPull_Down_c) ? kPORT_PullDown : kPORT_PullUp);
    pinConfig.mux = kPORT_MuxAsGpio;
    PORT_SetPinConfig(maPortBases[pInputConfig->gpioPort], pInputConfig->gpioPin, &pinConfig);
    PORT_SetPinInterruptConfig(maPortBases[pInputConfig->gpioPort], pInputConfig->gpioPin, (port_interrupt_t)(pInputConfig->interruptSelect));
    gpioConfig.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(maGpioBases[pInputConfig->gpioPort], pInputConfig->gpioPin, &gpioConfig);
    noOfElements--;
    pInputConfig++;
  }
  return TRUE;
}

/*! *********************************************************************************
* \brief  Initializes output pins
*
* \param[in]  pOutputConfig   table of output pins configuration structures
* \param[in]  noOfElements    number of elements of the table
* \return  install status
*
********************************************************************************** */

bool_t GpioOutputPinInit(const gpioOutputPinConfig_t* pOutputConfig, uint32_t noOfElements )
{
  port_pin_config_t pinConfig;
  gpio_pin_config_t gpioConfig;
  if(pOutputConfig == NULL)
  {
    return FALSE;
  }
  while(noOfElements)
  {
    if((pOutputConfig->gpioPin > 31) 
       || (pOutputConfig->gpioPort >= FSL_FEATURE_SOC_GPIO_COUNT)   
         || (pOutputConfig->slewRate >= pinSlewRate_Invalid_c)    
           || (pOutputConfig->driveStrength >= pinDriveStrength_Invalid_c))
    {
      return FALSE;
    }  
    gpioConfig.pinDirection = kGPIO_DigitalOutput;
    gpioConfig.outputLogic = pOutputConfig->outputLogic;
    GPIO_PinInit(maGpioBases[pOutputConfig->gpioPort], pOutputConfig->gpioPin, &gpioConfig);
    uint16_t* ptr = (uint16_t*)&pinConfig;
    *ptr = 0;
    pinConfig.slewRate = pOutputConfig->slewRate;
    pinConfig.driveStrength = pOutputConfig->driveStrength;
    pinConfig.mux = kPORT_MuxAsGpio;
    PORT_SetPinConfig(maPortBases[pOutputConfig->gpioPort], pOutputConfig->gpioPin, &pinConfig);
    noOfElements--;
    pOutputConfig++;
  }
  return TRUE;
}
/*! *********************************************************************************
* \brief  Uninstall the callback for the specified Pin Definition
*
* \param[in]  cb              The callback function to be installed
* \param[in]  priority        The priority used by the GPIO_IrqAdapter
* \param[in]  nvicPriority    The priority to be set in NVIC. Only most significant bits are used!
* \param[in]  pinDef          The KSDK pin definition
*
* \return  install status
*
********************************************************************************** */

gpioStatus_t GpioInstallIsr( pfGpioIsrCb_t cb, uint8_t priority, uint8_t nvicPriority, const gpioInputPinConfig_t* pInputConfig )
{
    uint32_t i;
    uint8_t  found   = 0;
    uint8_t  pos     = mGpioIsrCount;
    gpioPort_t portId = pInputConfig->gpioPort;
    uint32_t pinMask = 1 << pInputConfig->gpioPin;
    IRQn_Type irqNo  = maPortIrqId[portId];

    for( i=0; i<mGpioIsrCount; i++ )
    {
        /* search for port ISR already installed */
        if( mGpioIsr[i].port == portId )
        {
            found |= gGpio_FoundPortIsr_c;
        }
        /* search for insert position */
        if( (pos == mGpioIsrCount) && (mGpioIsr[i].prio >= priority) ) 
        {
            pos = i;
        }
        /* search for an entry with the same callback installed for the same port with the same priority */
        if( (mGpioIsr[i].callback == cb) && (mGpioIsr[i].port == portId) && (mGpioIsr[i].prio == priority) )
        {
            pos = i;
            found |= gGpio_FoundSimilar_c;
            break;
        }
    }

    if( found & gGpio_FoundSimilar_c )
    {
        /* found the same ISR installed for the same port, but other pins */
        mGpioIsr[pos].pinMask |= pinMask;
    }
    else
    {
      if( mGpioIsrCount >= gGpioMaxIsrEntries_c )
      {
        return gpio_outOfMemory;
      }
      OSA_InterruptDisable();
      if( pos != mGpioIsrCount )
      {
        
        /* Shift all entries to the left, to obtain a sorted list */
        for( i=mGpioIsrCount; i>pos; i-- )
        {
          mGpioIsr[i] = mGpioIsr[i-1];
        }
        
      }
      /* install new callback */
      mGpioIsr[pos].callback = cb;
      mGpioIsr[pos].prio     = priority;
      mGpioIsr[pos].port     = portId;
      mGpioIsr[pos].pinMask  = pinMask;
      mGpioIsr[pos].irqId    = irqNo;
      mGpioIsrCount++;
      OSA_InterruptEnable();
    }

    if( found )
    {
        /* The PORT ISR was already installed. Update NVIC priority if higher than the old one! */
        nvicPriority = nvicPriority >> (8 - __NVIC_PRIO_BITS);
        i = NVIC_GetPriority(irqNo);
        if( i > nvicPriority )
        {
            NVIC_SetPriority(irqNo, nvicPriority);
        }
        return gpio_success;
    }
    else
    {
        /* Install common PORT ISR */
        return Gpio_InstallPortISR(irqNo, nvicPriority);
    }
}

/*! *********************************************************************************
* \brief  Uninstall the callback for the specified Pin Definition
*
* \param[in]  pinDef    The KSDK pin definition
*
* \return  uninstall status
*
********************************************************************************** */

gpioStatus_t GpioUninstallIsr( const gpioInputPinConfig_t* pInputConfig )
{
    IRQn_Type irqNo;
    uint32_t  i, j;
    gpioPort_t portId = pInputConfig->gpioPort;
    uint32_t pinMask  = 1 <<pInputConfig->gpioPin;        
    for( i=0; i<mGpioIsrCount; i++ )
    {
        if( (mGpioIsr[i].port == portId) && (mGpioIsr[i].pinMask & pinMask) )
        {
            OSA_InterruptDisable();
            /* uninstall ISR only for specified pins */
            mGpioIsr[i].pinMask &= ~pinMask;
            /* if no more pins are active, uninstall handler function */
            if( !mGpioIsr[i].pinMask )
            {
                irqNo = mGpioIsr[i].irqId;
                mGpioIsr[i].callback = NULL;

                /* Shift next entries to the left */
                for( j=i; j<mGpioIsrCount-1; j++ )
                {
                    mGpioIsr[j] = mGpioIsr[j+1];
                }
                mGpioIsrCount--;

                /* Search for other ISR installed for the same IRQ */
                for( j=0; j<mGpioIsrCount; j++ )
                {
                    if( irqNo == mGpioIsr[j].irqId )
                    {
                        irqNo = NotAvail_IRQn;
                        break;
                    }
                }

                /* If no other ISR was installed for this IRQ, disable IRQ in NVIC */
                if( irqNo != NotAvail_IRQn )
                {
                    NVIC_DisableIRQ(irqNo);
                }
            }
            OSA_InterruptEnable();
            return gpio_success;
        }
    }

    return gpio_notFound;
}

/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************* */

/*! *********************************************************************************
* \brief  Common GPIO ISR.
*
********************************************************************************** */
static void Gpio_CommonIsr(void)
{
    uint32_t i;
    IRQn_Type irqId = (IRQn_Type)(__get_IPSR() - 16);

    /* Search for the highest priority ISR installed for the current PORT */
    for( i=0; i<mGpioIsrCount; i++ )
    {
        if( (mGpioIsr[i].pinMask & PORT_GetPinsInterruptFlags(maPortBases[mGpioIsr[i].port])) && 
            (mGpioIsr[i].irqId == irqId) )        
        {
            mGpioIsr[i].callback();
            /* If other lower priority IRSs need to run, this common ISR will run again! */
            return;
        }
    }
}

/*! *********************************************************************************
* \brief  Install the Gpio_CommonIsr() ISR for the specified IRQ
*
* \param[in]  irqId    The CMSIS irq Id
* \param[in]  nvicPrio The priority to be set in NVIC
*
* \return  install status
*
********************************************************************************** */
static gpioStatus_t Gpio_InstallPortISR(IRQn_Type irqId, uint32_t nvicPrio)
{
    if( irqId != NotAvail_IRQn )
    {
        OSA_InstallIntHandler(irqId, Gpio_CommonIsr);

        /* Enable IRQ in NVIC and set priority */
        NVIC_ClearPendingIRQ(irqId);
        NVIC_EnableIRQ(irqId);
        NVIC_SetPriority(irqId, nvicPrio >> (8 - __NVIC_PRIO_BITS));
    }
    return gpio_success;
}