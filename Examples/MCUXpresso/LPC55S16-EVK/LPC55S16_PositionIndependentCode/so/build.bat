arm-none-eabi-gcc -msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative -mcpu=cortex-m4 -mthumb -Wall -g -fPIC -O1 -c myLib.c -o myLib.o
arm-none-eabi-objdump -h -S "myLib.o" >"myLib.lst"
arm-none-eabi-gcc -shared -Wl,-soname,libmystuff.so -nostdlib -o libmystuff.so myLib.o
arm-none-eabi-objdump -h -S "libmystuff.so" >"libmystuff.so.lst"
arm-none-eabi-readelf -l "libmystuff.so" > "libmystuff.so.dis"