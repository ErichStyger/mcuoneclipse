readme.txt
----------

Serial bootloader project for the FRDM-K64F board. See 
https://mcuoneclipse.com/2013/04/28/serial-bootloader-for-the-freedom-board-with-processor-expert/


Notes:
- temporary removed flash protection
  CPU > common settings > Flash configuration field > P-Flash protection settings > protection regions > region 0
- checking for user app moved to __init_user()

