%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateBarGraph)
%;**     Description :
%;**         Creates a bar graph
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to 
%;**       * barGraph%ParbarGraph %>27 - Pointer to bargraph element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**         bgColor%ParbgColor %>27 - Graph background color
%;**       * data%Pardata %>27 - Pointer to the data (values 0..100)
%;**         nofData%ParnofData %>27 - number of data
%;**         barColor%ParbarColor %>27 - Color to be used for the bars
%;**         borderWidth%ParborderWidth %>27 - Width of the border around
%;** %>29 the graph. Pass zero for no border.
%;**         borderColor%ParborderColor %>27 - Color for the graph border
%;**         borderSpace%ParborderSpace %>27 - Space to be used in pixels
%;** %>29 between border and bars.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine