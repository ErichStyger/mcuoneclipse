%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DrawBarChart)
%;**     Description :
%;**         Draws a series of bars for a chart
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - upper left corner x coordinate
%;**         y%Pary %>27 - upper left corner y coordinate
%;**         width%Parwidth %>27 - Chart box width
%;**         height%Parheight %>27 - Chart box height
%;**       * data%Pardata %>27 - Pointer to data (series of %% values
%;** %>29 from 0...100%%)
%;**         nofData%ParnofData %>27 - number of data bytes
%;**         barColor%ParbarColor %>27 - Color to be used for the bars.
%;**         borderWidth%ParborderWidth %>27 - width of a border to be
%;** %>29 draw. Pass zero if there shall be no border.
%;**         borderColor%ParborderColor %>27 - Color to be used for the
%;** %>29 border (if borderWidth is not zero)
%;**         borderSpace%ParborderSpace %>27 - Space to be used in pixels
%;** %>29 between border and bars.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine