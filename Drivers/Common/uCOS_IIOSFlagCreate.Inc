%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSFlagCreate)
%;**     Description :
%;**         This function is called to create an event flag group.
%include Common\GeneralParameters.inc(27)
%;**         flags%Parflags %>27 - Contains the initial value to store in
%;** %>29 the event flag group.
%;**       * perror%Parperror %>27 - is a pointer to an error code which
%;** %>29 will be returned to your application.
%;**     Returns     :
%;**         ---%RetVal %>27 - A pointer to an event flag group or a NULL
%;** %>29 pointer if no more groups are available.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine