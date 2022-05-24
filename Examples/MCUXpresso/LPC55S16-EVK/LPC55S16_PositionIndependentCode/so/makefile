CC_SO_OPTIONS=-msingle-pic-base -mpic-register=r9 -mno-pic-data-is-text-relative -fPIC 

all:
	cd ../so
	arm-none-eabi-gcc $(CC_SO_OPTIONS) -mcpu=cortex-m4 -mthumb -Wall -g -O1 -c ../so/myLib.c -o myLib.o
	arm-none-eabi-gcc -shared -Wl,-soname,libmylib.so -nostdlib -o libmylib.so myLib.o
	arm-none-eabi-objcopy -v -O binary "libmylib.so" "libmylib.bin"
	
	@echo "generating listing files"
	arm-none-eabi-objdump -h -S "myLib.o" >"myLib.objdump.dis"
	arm-none-eabi-objdump -h -S "libmylib.so" >"libmylib.so.objdump.dis"
	arm-none-eabi-readelf -l "libmylib.so" > "libmylib.so.readelf.dis"
	cp libmylib.so ../Debug
	@echo "finished building shared library"
	
clean:
	-@rm *.so
	-@rm *.dis
	-@rm *.o
  
	