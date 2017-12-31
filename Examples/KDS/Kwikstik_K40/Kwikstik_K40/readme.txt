readme.txt
----------

a)
The following line needs to be disabled in CPU.c:
//  MCG_C7 &= (uint8_t)~(uint8_t)(MCG_C7_OSCSEL_MASK);
otherwise it will cause a hard fault due a silicon bug.

b) Disable the RCM Initialization in PE_low_level_init():
  /* RCM_RPFW: RSTFLTSEL=0 */
  RCM_RPFW &= (uint8_t)~(uint8_t)(RCM_RPFW_RSTFLTSEL(0x1F));
  /* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
  RCM_RPFC &= (uint8_t)~(uint8_t)(
               RCM_RPFC_RSTFLTSS_MASK |
               RCM_RPFC_RSTFLTSRW(0x03)
              );



In case of problem using the J-Link debug interface:
- unplug cables
- SW1 OFF
- plug in USB cable for debug (J18)
- SW1 ON
