readme.txt
----------
EVKB: MIMXRT1050-EVK_S26KS512S.cfx
Embedded Artists: MIMXRT1050-EcoXiP_ATXP032.cfx

Example project for the i.MX RT1050 (1052) EVK using the LCD.

NOTE: The LED only blinks on the EVKB, not on the original EVK(A)!

See
https://mcuoneclipse.com/2018/07/21/adding-a-rocktech-capacitive-touch-lcd-to-the-nxp-i-mx-rt1052-evk/
https://mcuoneclipse.com/2018/08/04/i-mx-rt1050-evk-vs-evkb/



-------------------------------
ISSUES
-------------------------------

FreeRTOS thread awareness does not work with LinkServer (workaround: use non-stop mode):
Error in final launch sequence
Failed to execute MI command:
-target-select extended-remote | crt_emu_cm_redlink -msg-port=54548 -g -mi -2 -pMIMXRT1052xxxxB -vendor=NXP --no-packed -reset= -ProbeHandle=1 -CoreIndex=0 -cache=disable -x "C:/Users/Erich Styger/Data/GitRepos/McuOnEclipse/Examples/MCUXpresso/i.MX RT1050_EVK/MIMXRT1052_LCD/Debug" --flash-dir "C:/Users/Erich Styger/mcuxpresso/01/.mcuxpressoide_packages_support/MIMXRT1052xxxxB_support/Flash" --telnet 3333
Error message from debugger back end:
Remote communication error.  Target disconnected.: Success.


FreeRTOS thread awareness does *not* work with P&E. Workaround: use -kernel=none in the Server parameters