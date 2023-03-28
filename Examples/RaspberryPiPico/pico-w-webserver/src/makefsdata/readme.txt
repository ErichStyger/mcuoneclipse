From
C:\Raspy\pico\pico-sdk\lib\lwip\src\apps\http\makefsdata


https://lists.gnu.org/archive/html/lwip-users/2012-07/msg00130.html


You shouldn't need to compile the whole lwip code to compile makefsdata.c;
makefsdata.c is my only source file being compiled in that project.

But you do need some of the lwip source handy so that makefsdata.c can
include the necessary c files in its compile. If your lwip source is in a
folder called "lwip" and the lwip and contrib folders are in the same
location, the #include ../../../../lwip/ should work itself out. You will
likely need to add some additional include paths to make everything happy.
For me it looks like:
./lwip/src/include/ipv4
./lwip/src/include
./contrib/ports/win32/include (for an example lwipopts.h)


https://github.com/krzmaz/pico-w-webserver-example/tree/main/src
https://krzmaz.com/2022-08-15-creating-a-web-server-on-raspberry-pi-pico-w-using-pico-sdk-and-lwip/#HTML