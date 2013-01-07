%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateIcon)
%;**     Description :
%;**         Creates a new calendar day element
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to 
%;**       * icon%Paricon %>27 - Pointer to icon element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**         type%Partype %>27 - type of icon to be created
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine