%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ElementInitCommon)
%;**     Description :
%;**         Initialize an element with the standard parameters.
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to element
%;**         type%Partype %>27 - The element type we want to create
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**         bgColor%ParbgColor %>27 - background color
%;**         handler%Parhandler %>27 - message handler to be used
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine