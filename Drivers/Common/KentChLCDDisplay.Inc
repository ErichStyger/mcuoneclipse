%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Display)
%;**     Description :
%;**         Function to send parameter for up-dating the display screen
%;**         with the data. The data are in the driver.
%include Common\GeneralParameters.inc(27)
%;**         firstDataRow%ParfirstDataRow %>27 - Location of data for
%;** %>29 first update row. This is the row of the
%;** %>29 display RAM.
%;**         firstImageRow%ParfirstImageRow %>27 - First physical display
%;** %>29 row to update. This is physical display row
%;** %>29 where the data from displayRAM[firstDataRow]
%;** %>29 shall show up.
%;**         numRows%ParnumRows %>27 - Number of rows to update.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine