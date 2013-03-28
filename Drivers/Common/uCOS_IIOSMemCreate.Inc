%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSMemCreate)
%;**     Description :
%;**         Create a fixed-sized memory partition that will be managed
%;**         by uC/OS-II.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - is the starting address of the memory
%;** %>29 partition
%;**         nblks%Parnblks %>27 - is the number of memory blocks to
%;** %>29 create from the partition.
%;**         blksize%Parblksize %>27 - is the size (in bytes) of each
%;** %>29 block in the memory partition.
%;**       * perr%Parperr %>27 - Pointer to to a variable containing an
%;** %>29 error message which will be set by this
%;** %>29 function to either:
%;** %>29 OS_ERR_NONE              if the memory
%;** %>29 partition has been created correctly.
%;** %>29 OS_ERR_MEM_INVALID_ADDR  if you are
%;** %>29 specifying an invalid address for the
%;** %>29 memory storage of the partition or, the
%;** %>29 block does not align on a pointer boundary
%;** %>29 OS_ERR_MEM_INVALID_PART  no free partitions
%;** %>29 available
%;** %>29 OS_ERR_MEM_INVALID_BLKS  user specified an
%;** %>29 invalid number of blocks (must be >= 2)
%;** %>29 OS_ERR_MEM_INVALID_SIZE  user specified an
%;** %>29 invalid block size
%;** %>29 - must be greater than the size of a
%;** %>29 pointer
%;** %>29 - must be able to hold an integral number
%;** %>29 of pointers
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns:
%;** %>29 != (OS_MEM *)0  is the partition was
%;** %>29 created
%;** %>29 == (OS_MEM *)0  if the partition was not
%;** %>29 created because of invalid arguments or, no
%;** %>29 free partition is available.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine