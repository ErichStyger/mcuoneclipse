readme.txt
----------
Project for a tinyK22 board (NXP K22FN512VLH12) with a low power demo:

Loop{
-	LED On
-	Delay 1 Sekunden
-	LED Off
-	Change to LowPower modus
-	Delay 10 Sekunden
-	Change to normal modus
-	Start Loop again
}


- The LED is configured in leds.c
- LowPower.h configures the low power mode used
