%-
%- Freescale USB Stack MSD source files
%-
%- 
%- Host\examples\msd -------------------------------------------
%FILE? %'DirRel_Code'usb_classes.h
%include FSL_USB_Stack\Host\examples\msd\usb_classes.h
%FILE? %'DirRel_Code'usb_user_config.h
%include FSL_USB_Stack\Host\examples\msd\user_config.h
%FILE? %'DirRel_Code'msd_commands.h
%include FSL_USB_Stack\Host\examples\msd\msd_commands.h

%- Host\source\classes\msd -------------------------------------------
%FILE %'DirRel_Code'usb_host_msd_bo.h
%include FSL_USB_Stack\Host\source\classes\msd\usb_host_msd_bo.h
%FILE %'DirRel_Code'usb_host_msd_bo.c
%include FSL_USB_Stack\Host\source\classes\msd\usb_host_msd_bo.c
%FILE %'DirRel_Code'usb_host_msd_ufi.h
%include FSL_USB_Stack\Host\source\classes\msd\usb_host_msd_ufi.h
%FILE %'DirRel_Code'usb_host_msd_ufi.c
%include FSL_USB_Stack\Host\source\classes\msd\usb_host_msd_ufi.c
%FILE %'DirRel_Code'usb_host_msd_queue.c
%include FSL_USB_Stack\Host\source\classes\msd\usb_host_msd_queue.c
