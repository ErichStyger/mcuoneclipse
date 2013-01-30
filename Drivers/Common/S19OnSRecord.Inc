%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnSRecord)
%;**     Description :
%;**         Event called for every S-Record
%include Common\GeneralParameters.inc(27)
%;**       * returnCode%ParreturnCode %>27 - Pointer to error code
%;**         type%Partype %>27 - type of S-Record (as character), e.g. '3'
%;**         addr%Paraddr %>27 - Address of data
%;**       * dataBuf%PardataBuf %>27 - Pointer to buffer of S-Record data
%;** %>29 (in binary form)
%;**         dataBufSize%PardataBufSize %>27 - Size in bytes of the data
%;** %>29 buffer
%;**       * data%Pardata %>27 - Pointer to private data
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine