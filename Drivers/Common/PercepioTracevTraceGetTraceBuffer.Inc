%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceGetTraceBuffer)
%;**     Description :
%;**         Return a pointer to the recorder data structure. Use this
%;**         together with uiTraceGetTraceBufferSize if you wish to
%;**         implement an own store/upload solution, e.g., in case a
%;**         debugger connection is not available for uploading the data.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Pointer to the trace buffer
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine