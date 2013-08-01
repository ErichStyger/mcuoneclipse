%-
%- Freescale USB Stack HID Keyboard source files
%-

%- \Device\source\class -------------------------------------------
%FILE %'DirRel_Code'usb_hid.c
%include FSL_USB_Stack\Device\source\class\usb_hid.c
%FILE %'DirRel_Code'usb_hid.h
%include FSL_USB_Stack\Device\source\class\usb_hid.h

%- \Device\app\hid -------------------------------------------
%FILE %'DirRel_Code'usb_user_config.h
%include FSL_USB_Stack\Device\app\hid\user_config.h
%FILE %'DirRel_Code'usb_descriptor.h
%include FSL_USB_Stack\Device\app\hid\usb_descriptor.h
%FILE %'DirRel_Code'USB_Config.h
%include FSL_USB_Stack\Device\app\hid\USB_Config.h
%FILE %'DirRel_Code'usb_descriptor.c
%include FSL_USB_Stack\Device\app\hid\usb_descriptor.c
