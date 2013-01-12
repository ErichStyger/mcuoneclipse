%-
%- Freescale USB Stack source files
%-
%if USBDeviceClass="MSD Host"

  %include FSL_USB_Stack_Files_Host.prg

%elif (USBDeviceClass="CDC Device") | (USBDeviceClass="HID Keyboard Device") %- USB Device

  %include FSL_USB_Stack_Files_Device.prg

%else %- USB Device
  %error "unknown host or device class '%USBDeviceClass' in FSL_USB_Stack_Files.prg?"
%endif
