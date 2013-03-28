%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnDetach)
%;**     Description :
%;**         Event generated when a device is detached.
%include Common\GeneralParameters.inc(27)
%;**         hid_type%Parhid_type %>27 - type of device, one of
%;** %>29 HIDTYPE_MOUSE, HIDTYPE_KBD, HIDTYPE_JOY or
%;** %>29 HIDTYPE_UNKNOWN
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine