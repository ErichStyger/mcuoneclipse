arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -g -fPIC -O1 -c myLib.c -o myLib.o
arm-none-eabi-gcc -shared -Wl,-soname,libmystuff.so --entry=MyLib_Init -nostdlib -o libmystuff.so myLib.o -lc
arm-none-eabi-objdump -h -S "libmystuff.so" >"libmystuff.so.lss"
arm-none-eabi-readelf -l "libmystuff.so" > "libmystuff.so.diss"