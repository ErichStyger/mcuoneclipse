%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (forward)
%;**     Description :
%;**         The f_forward function reads the data from the file and
%;**         forward it to the outgoing stream without data buffer. This
%;**         is suitable for small memory system because it does not
%;**         require any data buffer at application module. The file
%;**         pointer of the file object increases in number of bytes
%;**         forwarded. In case of *ByteFwd < ByteToFwd without error, it
%;**         means the requested bytes could not be transferred due to
%;**         end of file or stream goes busy during data transfer.
%include Common\GeneralParameters.inc(27)
%;**         FileObject%ParFileObject %>27 - Pointer to the open file
%;** %>29 object.
%;**         Func%ParFunc %>27 - Pointer to the user-defined data
%;** %>29 streaming function. For details, refer to
%;** %>29 the sample code.
%;**         ByteToFwd%ParByteToFwd %>27 - Number of bytes to forward in
%;** %>29 range of UINT.
%;**         ByteFwd%ParByteFwd %>27 - Pointer to the UINT variable to
%;** %>29 return number of bytes forwarded.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine