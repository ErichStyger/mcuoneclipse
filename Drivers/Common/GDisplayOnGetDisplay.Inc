%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnGetDisplay)
%;**     Description :
%;**         Event called from GetDisplay() method. This callback is
%;**         useful if you want to share the communication to the display
%;**         (e.g. SPI) with other peripherals, as this gives you a
%;**         chance to protect the access to it.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine