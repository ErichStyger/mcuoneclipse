readme.txt
----------
Project for MCUXpresso IDE and lwip and MQTT on FRDM-K64F board.


The LwIP stack is highly configurable via the lwipopts.h header which you have to create to overwrite the default settings from include/lwip/opts.h.



https://github.com/fboris/STM32Cube_FW_F4/blob/master/Middlewares/Third_Party/PolarSSL/library/net.c

using sockets: ???
#define LWIP_SOCKET             1

Example code:
https://github.com/SuperHouse/esp-open-rtos/blob/master/examples/aws_iot/ssl_connection.c
