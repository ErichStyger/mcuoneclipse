%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnButton)
%;**     Description :
%;**         Called a button change happens (indicating no button is
%;**         pressed or that a button is pressed).
%include Common\GeneralParameters.inc(27)
%;**         button%Parbutton %>27 - a value of 0 means no button pressed,
%;** %>29 1 means button one pressed, 2 button 2
%;** %>29 pressed, 3 for button 3 etc and 8 means
%;** %>29 button 8 pressed.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine