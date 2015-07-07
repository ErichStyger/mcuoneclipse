readme.txt
----------
Demonstration project for Segger RTT (Real Time Terminal)
https://www.segger.com/jlink-real-time-terminal.html

Install terminal
http://mcuoneclipse.com/2015/04/20/serial-terminal-view-in-eclipse-luna/
- create project
- add RTT files
- add utility files
- add code to main (add #includes)

Listen to localhost:19021 with telnet

Window > Show View > Target Explorer Views
- open telnet to localhost port 19021

Use the J-Link RTT client (JLinkRTTClient.exe) which automatically reconnects.
Or use the J-Link RTT Viewer. Both tools are located in the segger subfolder of the KDS installation.