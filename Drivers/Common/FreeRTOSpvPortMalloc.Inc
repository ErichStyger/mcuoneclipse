%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (pvPortMalloc)
%;**     Description :
%;**         Allocates a memory block using the port pvPortMalloc()
%;**         function
%include Common\GeneralParameters.inc(27)
%;**         xWantedSize%ParxWantedSize %>27 - size of memory block
%;** %>29 requested
%;**     Returns     :
%;**         ---%RetVal %>27 - memory block or NULL if failed
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine