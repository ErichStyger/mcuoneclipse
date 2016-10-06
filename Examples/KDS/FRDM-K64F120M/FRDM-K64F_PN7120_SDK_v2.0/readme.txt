readme.txt
----------

Kinetis Design Studio V3.2.0 project using the Kinetis SDK V2.0 on a FRDM-K64F board, talking to a PN7120 NFC Controller SBC Kit.


Open:
- Sleep() implementation ==> using vtaskDelay() instead
- check interrupt priorities: do they match with FreeRTOS? PortC interrupt is sending semaphore!
- tml_Init() already does pin initialization?

