%-
%- Freescale USB Stack source files for CDC or HID Keyboard/Mouse Devices
%-

%- Device\source\common -------------------------------------------
%FILE %'DirRel_Code'usb_class.c
%include FSL_USB_Stack\Device\source\common\usb_class.c
%FILE %'DirRel_Code'usb_class.h
%include FSL_USB_Stack\Device\source\common\usb_class.h
%FILE %'DirRel_Code'usb_framework.c
%include FSL_USB_Stack\Device\source\common\usb_framework.c
%FILE %'DirRel_Code'usb_framework.h
%include FSL_USB_Stack\Device\source\common\usb_framework.h

%- \Device\source\driver -------------------------------------------
%FILE %'DirRel_Code'usb_devapi.h
%include FSL_USB_Stack\Device\source\driver\usb_devapi.h
%FILE %'DirRel_Code'usb_driver.c
%include FSL_USB_Stack\Device\source\driver\usb_driver.c

%if CPUDevice="MCF52259"
%- \Device\source\driver\cfv2 -------------------------------------------
  %FILE? %'DirRel_Code'usb_bdt_cfv2.h
  %include FSL_USB_Stack\Device\source\driver\cfv2\usb_bdt_cfv2.h
  %FILE? %'DirRel_Code'usb_dci_cfv2.h
  %include FSL_USB_Stack\Device\source\driver\cfv2\usb_dci_cfv2.h
  %FILE? %'DirRel_Code'usb_dci_cfv2.c
  %include FSL_USB_Stack\Device\source\driver\cfv2\usb_dci_cfv2.c
  %FILE? %'DirRel_Code'usb_dciapi_cfv2.h
  %include FSL_USB_Stack\Device\source\driver\cfv2\usb_dciapi_cfv2.h
  %- the next one is shared between V2 and V1
  %FILE? %'DirRel_Code'usb_dciapi.h
  %include FSL_USB_Stack\Device\source\driver\cfv1\usb_dciapi.h
%elif (CPUDevice="MCF51JM128") | (CPUDevice="MCF51JM64") | (CPUDevice="MCF51MM256")
%- \Device\source\driver\cfv1 -------------------------------------------
  %FILE? %'DirRel_Code'usb_bdt.h
  %include FSL_USB_Stack\Device\source\driver\cfv1\usb_bdt.h
  %FILE? %'DirRel_Code'usb_dci.h
  %include FSL_USB_Stack\Device\source\driver\cfv1\usb_dci.h
  %FILE? %'DirRel_Code'usb_dci.c
  %include FSL_USB_Stack\Device\source\driver\cfv1\usb_dci.c
  %FILE? %'DirRel_Code'usb_dciapi.h
  %include FSL_USB_Stack\Device\source\driver\cfv1\usb_dciapi.h
%elif (CPUDevice="MC9S08JM60") | (CPUDevice="MC9S08JM16") | (CPUDevice="MC9S08MM128")
%- \Device\source\driver\s08 -------------------------------------------
  %FILE? %'DirRel_Code'usb_bdt.h
  %include FSL_USB_Stack\Device\source\driver\s08\usb_bdt.h
  %FILE? %'DirRel_Code'usb_dci.h
  %include FSL_USB_Stack\Device\source\driver\s08\usb_dci.h
  %FILE? %'DirRel_Code'usb_dci.c
  %include FSL_USB_Stack\Device\source\driver\s08\usb_dci.c
  %FILE? %'DirRel_Code'usb_dciapi.h
  %include FSL_USB_Stack\Device\source\driver\s08\usb_dciapi.h
%elif (CPUDevice="Kinetis K20D50") | (CPUDevice="Kinetis K21D50") | (CPUDevice="Kinetis K40") | (CPUDevice="Kinetis K53") | (CPUDevice="Kinetis K60") | (CPUDevice="Kinetis L2K") | (CPUDevice="Kinetis KL46Z48")
%- \Device\source\driver\kinetis -------------------------------------------
  %FILE? %'DirRel_Code'usb_bdt_kinetis.h
  %include FSL_USB_Stack\Device\source\driver\kinetis\usb_bdt_kinetis.h
  %FILE? %'DirRel_Code'usb_dci_kinetis.c
  %include FSL_USB_Stack\Device\source\driver\kinetis\usb_dci_kinetis.c
  %FILE? %'DirRel_Code'usb_dci_kinetis.h
  %include FSL_USB_Stack\Device\source\driver\kinetis\usb_dci_kinetis.h
  %FILE? %'DirRel_Code'usb_dciapi.h
  %include FSL_USB_Stack\Device\source\driver\kinetis\usb_dciapi.h
%endif

%if CPUDevice="MCF52259"
%- \Device\app\cdc\cw10\cfv2usbm52259 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\cfv2usbm52259\derivative.h
%elif (CPUDevice="MCF51JM128") | (CPUDevice="MCF51JM64")
%- \Device\app\cdc\cw10\cfv1usbjm128 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\cfv1usbjm128\derivative.h
%elif CPUDevice="MC9S08JM60"
%- \Device\app\cdc\cw10\s08usbjm60 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\s08usbjm60\derivative.h
%elif CPUDevice="MC9S08JM16"
%- \Device\app\cdc\cw10\s08usbjm16 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\s08usbjm16\derivative.h
%elif CPUDevice="MC9S08MM128"
%- \Device\app\cdc\cw10\s08usbmm128 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\s08usbmm128\derivative.h
%elif CPUDevice="MCF51MM256"
%- \Device\app\cdc\cw10\mcf51MM256 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\cfv1usbmm256\derivative.h
%elif CPUDevice="Kinetis K20D50"
%- \Device\app\cdc\cw10\kinetis_k20 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k20\derivative.h
%elif CPUDevice="Kinetis K21D50"
%- \Device\app\cdc\cw10\kinetis_k21 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k21\derivative.h
%elif CPUDevice="Kinetis K40"
%- \Device\app\cdc\cw10\kinetis_k40 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k40\derivative.h
%elif CPUDevice="Kinetis K50"
%- \Device\app\cdc\cw10\kinetis_k53 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k53\derivative.h
%elif CPUDevice="Kinetis K60"
%- \Device\app\cdc\cw10\kinetis_k60 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k60\derivative.h
%- \Device\app\cdc\cw10\kinetis_k70 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_k70\derivative.h
%elif CPUDevice="Kinetis L2K"
%- \Device\app\cdc\cw10\kinetis_l2k -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_l2k\derivative.h
%elif CPUDevice="Kinetis KL46Z48"
%- \Device\app\cdc\cw10\kinetis_kl46z48 -------------------------------------------
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Device\app\cdc\cw10\kinetis_kl46z48\derivative.h
%endif

%- \Device\app\common -------------------------------------------
%FILE %'DirRel_Code'types.h
%include FSL_USB_Stack\Device\app\common\types.h

%if CPUDevice="MCF52259"
  %- \Device\app\common\cfv2 -------------------------------------------
  %FILE? %'DirRel_Code'hidef.h
  %include FSL_USB_Stack\Device\app\common\cfv2\hidef.h
  %FILE? %'DirRel_Code'wdt_cfv2.c
  %include FSL_USB_Stack\Device\app\common\cfv2\wdt_cfv2.c
  %FILE? %'DirRel_Code'wdt_cfv2.h
  %include FSL_USB_Stack\Device\app\common\cfv2\wdt_cfv2.h
  %FILE? %'DirRel_Code'exceptions_cfv2.h
  %include FSL_USB_Stack\Device\app\common\cfv2\exceptions_cfv2.h
%elif (CPUDevice="MCF51JM128") | (CPUDevice="MCF51JM64") | (CPUDevice="MCF51MM256")
  %- \Device\app\common\cfv1 -------------------------------------------
  %- nothing needed from here
%elif (CPUDevice="MC9S08JM60") | (CPUDevice="MC9S08JM16")
  %- \Device\app\common\S08 -------------------------------------------
  %- nothing needed from here
%elif ((CPUDevice="Kinetis K20D50") | (CPUDevice="Kinetis K21D50") | (CPUDevice="Kinetis K40") | (CPUDevice="Kinetis K53") | (CPUDevice="Kinetis K60") | (CPUDevice="Kinetis K70")  | (CPUDevice="Kinetis L2K") | (CPUDevice="Kinetis KL46Z48"))
  %- \Device\app\common\kinetis -------------------------------------------
  %FILE? %'DirRel_Code'hidef.h
  %include FSL_USB_Stack\Device\app\common\kinetis\hidef.h
  %FILE? %'DirRel_Code'wdt_kinetis.h
  %include FSL_USB_Stack\Device\app\common\kinetis\wdt_kinetis.h
  %FILE? %'DirRel_Code'wdt_kinetis.c
  %include FSL_USB_Stack\Device\app\common\kinetis\wdt_kinetis.c
%endif
