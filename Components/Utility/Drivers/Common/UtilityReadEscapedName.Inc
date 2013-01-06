%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadEscapedName)
%;**     Description :
%;**         Scans an escaped name from a string. This is useful e.g. for
%;**         double quoted file names.
%include Common\GeneralParameters.inc(27)
%;**       * filename%Parfilename %>27 - the name to be copied. Names may
%;** %>29 be in quoted format
%;**       * destname%Pardestname %>27 - the destination of the copy.
%;** %>29 Names are not in quoted format. destname
%;** %>29 may be NULL to get the other return values
%;** %>29 only
%;**         maxlen%Parmaxlen %>27 - length allocated for destname
%;**       * lenRead%ParlenRead %>27 - length read in filename to copy
%;** %>29 the whole name. Note that filenames maybe
%;** %>29 space terminated, so *lenRead <
%;** %>29 strlen(filename)
%;**         lenWritten%ParlenWritten %>27 - the size written in destname.
%;** %>29 In case of overflows in destname,
%;** %>29 lenWritten is still increased but destname
%;** %>29 no longer written. The have the string
%;** %>29 length in these cases use strlen(destname)
%;**         terminators%Parterminators %>27 - additional characters
%;** %>29 where a name should terminate. May be NULL
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine