%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReceiveDataBlock)
%;**     Description :
%;**         Retrieve a data block from the device
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to data buffer
%;**         nofBytes%ParnofBytes %>27 - number of bytes to retrieve,
%;** %>29 must be a multiple of 4
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if reading was going fine, FALSE
%;** %>29 otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine