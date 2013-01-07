%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (FillMemory)
%;**     Description :
%;**         Fills the display memory with a pattern
%include Common\GeneralParameters.inc(27)
%;**         startAddr%ParstartAddr %>27 - start address
%;**         endAddr%ParendAddr %>27 - end address
%;**         pattern%Parpattern %>27 - fill pattern
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine