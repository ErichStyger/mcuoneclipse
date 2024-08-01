readme.txt
----------

Program to decode and convert a freestanding gcov stream into a gcfn format which then can be merged with gcov-tool.

Usage:
A) Decode the data strean file:
decode -f stream.txt -o stream.gcfn

B) Merge and create .gcda files:
arm-none-eabi-gcov-tool merge-stream < stream.gcfn
