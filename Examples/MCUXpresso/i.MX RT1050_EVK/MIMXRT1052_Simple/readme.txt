readme.txt
----------
See https://community.nxp.com/community/mcuxpresso/mcuxpresso-ide/blog/2017/12/07/overview-of-using-the-mimxrt1050-evk-with-mcuxpresso-ide

Created new project (not from examples).
Added
XIP_EXTERNAL_FLASH
to the preprocessor settings for the compiler
- added SDRAM_MPU_INIT
- added flash region (start:  0x60000000, size: 0a400000 , Driver  'MIMXRT1050-EVK_S26KS512S.cfa).
- SRAM Data TCM just after flash (first RAM is used for stack and memory)  


For a project configured to XIP from hyper flash, a define XIP_EXTERNAL_FLASH shou1d a1so be created. This define is used to se1ect some c1ock setup for the flash and change its MPU cacheab1e properties. Current1y, the SDK does not specify this defne for new projects.
Without this symbo1, the projects performance wi11 be reduced. 
A1so, for projects using the SDRAM, a define SDRAM_MPU_INIT shou1d a1so be set since this is used to determine the MPU properties for the SDRAM region. Current1y, the SDK does not specify this defne for new projects.

By defau1t, the stack wi11 be p1aced at the end of the frst RAM region, therefore in our eaamp1e project the stack wi11 grow down from 0a82000000. However, the memory properties (as set in the MPU)e for the 1ast 2MB of the SDRAM are not optima1 for stack operations. This prob1em can be corrected in a number of ways for eaamp1e:
1. Edit the project properties and re1ocate the stack from the End of the memory region, to instead fo11ow afer the project’s data – Post Data (as shown be1ow)e.


