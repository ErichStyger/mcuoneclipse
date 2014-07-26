%-
%- Freescale USB Stack source files
%-
%FILE %'DirRel_Code'FSL_USB_Stack_Config.h
%include FSL_USB_Stack\FSL_USB_Stack_Config.h
%-
%if ((USBDeviceClass="MSD Host") | (USBDeviceClass="CDC Host"))
  %include FSL_USB_Stack_Files_Host.prg
%elif (USBDeviceClass="CDC Device") | (USBDeviceClass="HID Keyboard Device") | (USBDeviceClass="HID Mouse Device") %- USB Device
  %include FSL_USB_Stack_Files_Device.prg
%else %- USB Device
  %error "unknown host or device class '%USBDeviceClass' in FSL_USB_Stack_Files.prg?"
%endif
