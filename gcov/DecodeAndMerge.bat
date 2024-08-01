decode -f stream.txt -o stream.gcfn
arm-none-eabi-gcov-tool merge-stream < stream.gcfn