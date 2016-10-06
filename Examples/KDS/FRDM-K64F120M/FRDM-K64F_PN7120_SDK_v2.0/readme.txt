readme.txt
----------

Kinetis Design Studio V3.2.0 project using the Kinetis SDK V2.0 on a FRDM-K64F board, talking to a PN7120 NFC Controller SBC Kit.

Hardware connections:
- GND and 3.3V
- I2C SCL: PTE24
- I2C SDA: PTE23
- IRQ: PTC4
- VEN: PTC3

Open:
- check interrupt priorities: do they match with FreeRTOS? PortC interrupt is sending semaphore!

Changes:
- Sleep() implementation ==> using vtaskDelay() instead
