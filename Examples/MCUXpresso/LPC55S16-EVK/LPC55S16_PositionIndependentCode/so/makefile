CC_SO_OPTIONS=-msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative -fPIC 

all:
	cd ../so
	arm-none-eabi-gcc $(CC_SO_OPTIONS) -mcpu=cortex-m4 -mthumb -Wall -g -O1 -c ../so/myLib.c -o myLib.o
	arm-none-eabi-gcc -shared -Wl,-soname,libmystuff.so -nostdlib -o libmystuff.so myLib.o
	@echo "generating listing files"
	arm-none-eabi-objdump -h -S "myLib.o" >"myLib.objdump.dis"
	arm-none-eabi-objdump -h -S "libmystuff.so" >"libmystuff.so.objdump.dis"
	arm-none-eabi-readelf -l "libmystuff.so" > "libmystuff.so.readelf.dis"
	@echo "finished building shared library"
	