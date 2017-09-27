readme.txt
----------
http://www2.warwick.ac.uk/fac/sci/systemsbiology/staff/dyer/software/pchineclipse/


${COMMAND} ${cross_toolchain_flags} ${FLAGS} ${INPUTS} -c

-x c++-header -o ../Sources/pch.h.gch


Normal:
${COMMAND} ${cross_toolchain_flags} ${FLAGS} -c ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}





${COMMAND} ${cross_toolchain_flags} ${FLAGS} ${INPUTS}
-c -x c++-header -o ../PCH/pch.h.gch

-Winvalid-pch