readme.txt
----------
Project for a tinyK22 board (NXP K22FN512VLH12) using FreeRTOS.

This project includes ASAN (Address Sanitizer).

Notes:
- asan.c contains the ASAN hooks and wrappers
- to enable ASAN for a source file, add the following to the compiler options:
  -fsanitize=kernel-address -fasan-shadow-offset=32
