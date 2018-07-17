readme.txt
----------
This project can be used to erase the flash in case of connection problems, see 
https://mcuoneclipse.com/2017/12/16/mcuxpresso-ide-v10-1-0-with-i-mx-rt1052-crossover-processor/

a) power off board
b) Set SW7 to 1-ON 2-ON 3-ON 4-OFF
3) power on board
4) select this project
5) in the Quickstart panel, under 'Debug your board', use the LinkServer icon drop down and use 'Erase Flash Action'
6) Hopefully the operation finishes successfully
8) set SW7 back to 1-OFF 2-ON 3-ON 4-OFF
9) Now you should be able to debug the board again with this application

