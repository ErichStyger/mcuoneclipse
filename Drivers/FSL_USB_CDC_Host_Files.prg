%-
%- Freescale USB Stack CDC Host source files
%-
%-
%- Host\examples\cdc_serial -------------------------------------------
%FILE? %'DirRel_Code'cdc_serial.c
%include FSL_USB_Stack\Host\examples\cdc_serial\cdc_serial.c
%FILE? %'DirRel_Code'cdc_serial.h
%include FSL_USB_Stack\Host\examples\cdc_serial\cdc_serial.h
%FILE? %'DirRel_Code'usb_classes.h
%include FSL_USB_Stack\Host\examples\cdc_serial\usb_classes.h
%FILE? %'DirRel_Code'usb_user_config.h
%include FSL_USB_Stack\Host\examples\cdc_serial\user_config.h

%- \Host\source\classes\cdc -------------------------------------------
%FILE %'DirRel_Code'fio.h
%include FSL_USB_Stack\Host\source\classes\cdc\fio.h
%FILE %'DirRel_Code'io.h
%include FSL_USB_Stack\Host\source\classes\cdc\io.h
%FILE %'DirRel_Code'ioctl.h
%include FSL_USB_Stack\Host\source\classes\cdc\ioctl.h
%FILE %'DirRel_Code'serial.h
%include FSL_USB_Stack\Host\source\classes\cdc\serial.h
%FILE %'DirRel_Code'usb_host_cdc.c
%include FSL_USB_Stack\Host\source\classes\cdc\usb_host_cdc.c
%FILE %'DirRel_Code'usb_host_cdc.h
%include FSL_USB_Stack\Host\source\classes\cdc\usb_host_cdc.h
%FILE %'DirRel_Code'usb_host_cdc_intf.c
%include FSL_USB_Stack\Host\source\classes\cdc\usb_host_cdc_intf.c

