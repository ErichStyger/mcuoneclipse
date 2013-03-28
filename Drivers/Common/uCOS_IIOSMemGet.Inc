%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSMemGet)
%;**     Description :
%;**         Get a memory block from a partition
%include Common\GeneralParameters.inc(27)
%;**       * pmem%Parpmem %>27 - Pointer to the memory partition control
%;** %>29 block
%;**       * perr%Parperr %>27 - Pointer to to a variable containing an
%;** %>29 error message which will be set by this
%;** %>29 function to either:
%;** %>29 OS_ERR_NONE             if the memory
%;** %>29 partition has been created correctly.
%;** %>29 OS_ERR_MEM_NO_FREE_BLKS if there are no
%;** %>29 more free memory blocks to allocate to
%;** %>29 caller
%;** %>29 OS_ERR_MEM_INVALID_PMEM if you passed a
%;** %>29 NULL pointer for 'pmem'
%;**     Returns     :
%;**         ---%RetVal %>27 - A pointer to a memory block if no error is
%;** %>29 detected, a pointer to NULL if an error is
%;** %>29 detected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine