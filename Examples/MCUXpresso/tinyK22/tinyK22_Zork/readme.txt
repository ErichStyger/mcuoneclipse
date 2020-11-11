readme.txt
----------

This application implements the 'Zork' game on the tinyK22.
See https://mcuoneclipse.com/2018/12/02/playing-zork-with-freertos-on-arm-in-three-different-ways/

By default, it is using the internal flash for storage. Using the SD card is not tested yet, so no save functionality yet.

The latest version of this game is on GitHub:
https://github.com/ErichStyger/mcuoneclipse/tree/master/Examples/MCUXpresso/tinyK22/tinyK22_Zork

How to play:
- Open a terminal and connect to the OpenSDA/Debug port virtual UART (115200 baud).
- The application runs a Shell/Console interface. Use the 
  help
  command to get a list of commands.
- Use
  Zork play
  to start the game
- In the game, use following command to get some help
  help
- to leave the game, use the following command to return to the shell:
  quit


Have fun!
Erich