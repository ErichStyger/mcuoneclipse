%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (LoadSoftChar)
%;**     Description :
%;**         Loads a user defined (softchar) into the display CGRAM.
%include Common\GeneralParameters.inc(27)
%;**         charCode%ParcharCode %>27 - The character code to be defined
%;** %>29 (0..7)
%;**       * softChar%ParsoftChar %>27 - Pointer to an array of 8 bytes
%;** %>29 defining the soft character
%;** %>29 Example of the soft character 'ü':
%;** %>29 const byte SoftCharUE[8] = { // ü
%;** %>29 0x11, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d, 0
%;** %>29 //  X...X
%;** %>29 //  .....
%;** %>29 //  X...X
%;** %>29 //  X...X
%;** %>29 //  X...X
%;** %>29 //  X..XX
%;** %>29 //  .XX.X
%;** %>29 };
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine