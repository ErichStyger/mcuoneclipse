%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateSlider)
%;**     Description :
%;**         Creates a new slider element
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * slider%Parslider %>27 - Pointer to element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**         Color%ParColor %>27 - background color of button
%;**         min%Parmin %>27 - Minumum value of slider
%;**         max%Parmax %>27 - Maximum value of slider
%;**         steps%Parsteps %>27 - Number of desired steps
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine