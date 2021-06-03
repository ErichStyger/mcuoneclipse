readme.txt

arm-none-eabi-gcc -shared -mcpu=cortex-m4 -mthumb -Wall -g -fPIC -fmessage-length=0 --specs=nosys.specs mylib.c -o libmylib.so

arm-none-eabi-gcc -c -O0 -mcpu=cortex-m4 -mthumb -Wall -fmessage-length=0 -fPIC startup_lpc55s16.c -o startup.o

arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -Wall -g -fmessage-length=0 --specs=nosys.specs -fPIC  main.c -o main.o

arm-none-eabi-ld startup.o main.o -g -nostdlib -T./LPC55S16_PositionIndependentCode_Debug.ld -Map main.map --print-memory-usage -L. -lmylib -o main.elf


Link error:
arm-none-eabi-gcc -nostdlib -Xlinker -Map="LPC55S16_PositionIndependentCode.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T./LPC55S16_PositionIndependentCode_Debug.ld -L. -lmylib startup.o main.o -o main.elf


arm-none-eabi-gcc -x assembler-with-cpp -c -O0 -mcpu=cortex-m4 -mthumb -Wall -fmessage-length=0 -fPIC startup.S -o startup.o
arm-none-eabi-ld startup.o main.o -g -nostdlib -T./linker.ld -Map main.map --print-memory-usage -L. -lmylib -o main.elf