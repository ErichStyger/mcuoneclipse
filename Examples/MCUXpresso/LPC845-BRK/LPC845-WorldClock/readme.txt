readme.txt
----------

StepperClock project with the NXP LPC845.
This clock is using dual stepper motors to show the time.
Multiple clocks can be combined to show the time for different time zones.

Possible stepper motor noise is reduced by 'firm' hands on the shafts.

Board bringup:
- Resistance 5V-GND: ~100k
- Resistance 3V-BND: ~360k

Power:
- V0.1: power consumption: 5V @ 80 mA
- V1.0: no motors (only LPC): ~20mA (5V), limit at 30mA
- V1.0: with motors: 205mA (4V), limit at 250 mA. Motors initialized and operating: all 6 boards: ~85mA


RS-485 addr for server:0x01, default client is 0x0a, assigned clients are 0x10, 0x11, 0x12, ...

Command format:
@<dst> <src> cmd <command>

Example commands to client 0x20 from node 1:
@0x20 1 cmd help
@0x20 1 cmd app clock off
@0x20 1 cmd stepper zero all
@0x20 1 cmd McuTimeDate time 08:44
@0x20 1 cmd app clock on

Status auf Master:
@0 cmd status

ToDo:
- better mag failure handling: if one fails, still move the other ones
- queue handling: receiving queue items while executing current queue

stepper q 0 0 stepper m 0 0 180 4 cw
stepper q 0 1 stepper m 0 1 180 8 cc
stepper q 0 0 stepper m 0 0 0 4 cw
stepper q 0 1 stepper m 0 1 0 8 cc
stepper exq