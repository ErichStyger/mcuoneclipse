%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (open)
%;**     Description :
%;**         Open/Create a file
%include Common\GeneralParameters.inc(27)
%;**         fp%Parfp %>27 - Pointer to the blank file object structure
%;**         path%Parpath %>27 - Pointer to a null-terminated string that
%;** %>29 specifies the file name to create or open.
%;**         mode%Parmode %>27 - Specifies the type of access and open
%;** %>29 method for the file. It is specified by a
%;** %>29 combination of following flags.
%;** %>29 FA_READ: Specifies read access to the
%;** %>29 object. Data can be read from the file.
%;** %>29 Combine with FA_WRITE for read-write access.
%;** %>29 FA_WRITE: Specifies write access to the
%;** %>29 object. Data can be written to the file.
%;** %>29 Combine with FA_READ for read-write access.
%;** %>29 FA_OPEN_EXISTING: Opens the file. The
%;** %>29 function fails if the file is not existing.
%;** %>29 (Default)
%;** %>29 FA_OPEN_ALWAYS: Opens the file if it is
%;** %>29 existing. If not, a new file is created. To
%;** %>29 append data to the file, use f_lseek
%;** %>29 function after file open in this method.
%;** %>29 FA_CREATE_NEW: Creates a new file. The
%;** %>29 function fails if the file is already
%;** %>29 existing.
%;** %>29 FA_CREATE_ALWAYS: Creates a new file. If
%;** %>29 the file is existing, it is truncated and
%;** %>29 overwritten.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine