%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetSecurityEncryptionModesStr)
%;**     Description :
%;**         Set Security & Encryption Modes
%include Common\GeneralParameters.inc(27)
%;**       * modes%Parmodes %>27 - Pointer to string with the security
%;** %>29 and encryption modes, in 'mode', 'encrypt'
%;** %>29 format.
%;** %>29 'mode' = Security Mode
%;** %>29 0 - sec_mode_off (default)
%;** %>29 1 - sec_mode1_non-secure
%;** %>29 2 - sec_mode2-service
%;** %>29 3 - sec_mode3_link
%;** %>29 4 - sec_mode_unknown
%;** %>29 'encrypt' = encryption mode
%;** %>29 0 - hci_enc_mode_off (default)
%;** %>29 1 - hci_enc_mode_pt_to_pt
%;** %>29 2 - hci_enc_mode_pt_to_pt_and_bcast
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine