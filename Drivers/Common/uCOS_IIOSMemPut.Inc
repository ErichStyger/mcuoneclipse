%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSMemPut)
%;**     Description :
%;**         Returns a memory block to a partition
%include Common\GeneralParameters.inc(27)
%;**       * pmem%Parpmem %>27 - Pointer to to the memory partition
%;** %>29 control block
%;**       * pblk%Parpblk %>27 - Pointer to the memory block being
%;** %>29 released.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE: if the memory block was
%;** %>29 inserted into the partition
%;** %>29 OS_ERR_MEM_FULL: if you are returning a
%;** %>29 memory block to an already FULL memory
%;** %>29 partition (You freed more blocks than you
%;** %>29 allocated!)
%;** %>29 OS_ERR_MEM_INVALID_PMEM: if you passed a
%;** %>29 NULL pointer for 'pmem'
%;** %>29 OS_ERR_MEM_INVALID_PBLK: if you passed a
%;** %>29 NULL pointer for the block to release.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine