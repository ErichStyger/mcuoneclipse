%-
%- Freescale USB Stack CDC source files
%-
%-
%- \Device\source\class -------------------------------------------
%FILE %'DirRel_Code'usb_cdc.c
%include FSL_USB_Stack\Device\source\class\usb_cdc.c
%FILE %'DirRel_Code'usb_cdc.h
%include FSL_USB_Stack\Device\source\class\usb_cdc.h
%FILE %'DirRel_Code'usb_cdc_pstn.c
%include FSL_USB_Stack\Device\source\class\usb_cdc_pstn.c
%FILE %'DirRel_Code'usb_cdc_pstn.h
%include FSL_USB_Stack\Device\source\class\usb_cdc_pstn.h

%- \Device\app\cdc -------------------------------------------
%FILE %'DirRel_Code'usb_user_config.h
%include FSL_USB_Stack\Device\app\cdc\user_config.h
%FILE %'DirRel_Code'USB_Config.h
%include FSL_USB_Stack\Device\app\cdc\USB_Config.h
%FILE %'DirRel_Code'usb_descriptor.c
%include FSL_USB_Stack\Device\app\cdc\usb_descriptor.c
%FILE %'DirRel_Code'usb_descriptor.h
%include FSL_USB_Stack\Device\app\cdc\usb_descriptor.h

%- .inf driver files -------------------------------------------
%FILE %'DirRel_Docs'cdc.inf
%include FSL_USB_Stack\Device\app\cdc\inf\cdc.inf
%FILE %'DirRel_Docs'cdc.inf_readme.txt
%include FSL_USB_Stack\Device\app\cdc\inf\cdc.inf_readme.txt
