c:\nxp\SRecord\srec_cat\srec_cat ./BL_0xA000/tinyK22_Blinky.s19 -fill 0xff 0xa000 0xd000 -crop 0xc400 0xD000 -Bit_Reverse -CRC32LE 0x1000 -Bit_Reverse -XOR 0xff -crop 0x1000 0x1004 -Output - -hex_dump


@REM Show BCA:
echo show BCA:
c:\nxp\SRecord\srec_cat.exe ./BL_0xA000/tinyK22_Blinky.bin -binary -crop 0x3c0 0x3d0 -output - -hex_dump

@REM calculate CRC
echo calculate CRC:
c:\nxp\SRecord\srec_cat ./BL_0xA000/tinyK22_Blinky.bin -binary -fill 0xff 0x0000 0x1000 -crop 0x0400 0x1000 -Bit_Reverse -CRC32LE 0x1000 -Bit_Reverse -XOR 0xff -crop 0x1000 0x1004 -Output - -hex_dump

REM 6B636667
REM 00A00000  0000a000
REM C0250000  000025c0
REM 00D6CCBB  bbccd600

@REM add CRC
c:\nxp\SRecord\srec_cat -generate 0xc3cc 0xc3d0 -constant-l-e 0xD688C6B4 4 ./BL_0xA000/tinyK22_Blinky.s19 -exclude 0xc3cc 0xc3d0 -Output_Block_Size 16 -output newWithCRC32.s19