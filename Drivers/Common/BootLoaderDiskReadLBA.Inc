%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadLBA)
%;**     Description :
%;**         Read a Logical Block Address
%include Common\GeneralParameters.inc(27)
%;**         FAT_LBA%ParFAT_LBA %>27 - Logical Block Address to Read
%;**       * pu8DataPointer%Parpu8DataPointer %>27 - Pointer to array to
%;** %>29 store data read
%;**       * fileStatus%ParfileStatus %>27 - Pointer to file status
%;** %>29 information
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
