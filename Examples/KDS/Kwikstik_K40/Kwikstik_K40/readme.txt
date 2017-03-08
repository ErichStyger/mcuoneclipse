readme.txt
----------

The following line needs to be disabled in CPU.c:
//  MCG_C7 &= (uint8_t)~(uint8_t)(MCG_C7_OSCSEL_MASK);
otherwise it will cause a hard fault due a silicon bug.