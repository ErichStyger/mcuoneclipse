convert -f stream.txt -o stream.gcfn

arm-none-eabi-gcov-tool merge-stream < stream.gcfn
REM note: creates the .gcda in the destination folder!