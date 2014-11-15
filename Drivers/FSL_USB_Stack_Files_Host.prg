%-
%- Freescale USB Stack source files for MSD Host
%-
%- 
%- Host\source\classes\common -------------------------------------------
%FILE %'DirRel_Code'usb_classes.c
%include FSL_USB_Stack\Host\source\classes\common\usb_classes.c

%- Host\source\classes\hub -------------------------------------------
%FILE %'DirRel_Code'usb_host_hub.h
%include FSL_USB_Stack\Host\source\classes\hub\usb_host_hub.h
%FILE %'DirRel_Code'usb_host_hub.c
%include FSL_USB_Stack\Host\source\classes\hub\usb_host_hub.c
%FILE %'DirRel_Code'usb_host_hub_sm.h
%include FSL_USB_Stack\Host\source\classes\hub\usb_host_hub_sm.h
%FILE %'DirRel_Code'usb_host_hub_sm.c
%include FSL_USB_Stack\Host\source\classes\hub\usb_host_hub_sm.c
%FILE %'DirRel_Code'usb_host_hub_prv.h
%include FSL_USB_Stack\Host\source\classes\hub\usb_host_hub_prv.h

%- Host\source\host_common -------------------------------------------
%FILE %'DirRel_Code'host_ch9.c
%include FSL_USB_Stack\Host\source\host_common\host_ch9.c
%FILE %'DirRel_Code'host_ch9.h
%include FSL_USB_Stack\Host\source\host_common\host_ch9.h
%FILE %'DirRel_Code'host_close.c
%include FSL_USB_Stack\Host\source\host_common\host_close.c
%FILE %'DirRel_Code'host_close.h
%include FSL_USB_Stack\Host\source\host_common\host_close.h
%FILE %'DirRel_Code'host_cnfg.h
%include FSL_USB_Stack\Host\source\host_common\host_cnfg.h
%FILE %'DirRel_Code'host_cnl.c
%include FSL_USB_Stack\Host\source\host_common\host_cnl.c
%FILE %'DirRel_Code'host_cnl.h
%include FSL_USB_Stack\Host\source\host_common\host_cnl.h
%FILE %'DirRel_Code'host_common.c
%include FSL_USB_Stack\Host\source\host_common\host_common.c
%FILE %'DirRel_Code'host_common.h
%include FSL_USB_Stack\Host\source\host_common\host_common.h
%FILE %'DirRel_Code'host_debug.h
%include FSL_USB_Stack\Host\source\host_common\host_debug.h
%FILE %'DirRel_Code'host_dev_list.c
%include FSL_USB_Stack\Host\source\host_common\host_dev_list.c
%FILE %'DirRel_Code'host_dev_list.h
%include FSL_USB_Stack\Host\source\host_common\host_dev_list.h
%FILE %'DirRel_Code'host_driver.c
%include FSL_USB_Stack\Host\source\host_common\host_driver.c
%FILE %'DirRel_Code'host_driver.h
%include FSL_USB_Stack\Host\source\host_common\host_driver.h
%FILE %'DirRel_Code'host_main.c
%include FSL_USB_Stack\Host\source\host_common\host_main.c
%FILE %'DirRel_Code'host_main.h
%include FSL_USB_Stack\Host\source\host_common\host_main.h
%FILE %'DirRel_Code'host_rcv.c
%include FSL_USB_Stack\Host\source\host_common\host_rcv.c
%FILE %'DirRel_Code'host_rcv.h
%include FSL_USB_Stack\Host\source\host_common\host_rcv.h
%FILE %'DirRel_Code'host_shut.c
%include FSL_USB_Stack\Host\source\host_common\host_shut.c
%FILE %'DirRel_Code'host_shut.h
%include FSL_USB_Stack\Host\source\host_common\host_shut.h
%FILE %'DirRel_Code'host_snd.c
%include FSL_USB_Stack\Host\source\host_common\host_snd.c
%FILE %'DirRel_Code'host_snd.h
%include FSL_USB_Stack\Host\source\host_common\host_snd.h
%FILE %'DirRel_Code'hostapi.h
%include FSL_USB_Stack\Host\source\host_common\hostapi.h

%- Host\source\driver -------------------------------------------
%FILE %'DirRel_Code'khci.h
%include FSL_USB_Stack\Host\source\driver\khci.h
%- %FILE %'DirRel_Code'khci.c
%- %include FSL_USB_Stack\Host\source\driver\khci.c
%FILE %'DirRel_Code'mem_util.h
%include FSL_USB_Stack\Host\source\driver\mem_util.h
%FILE %'DirRel_Code'mem_util.c
%include FSL_USB_Stack\Host\source\driver\mem_util.c
%FILE %'DirRel_Code'usbevent.h
%include FSL_USB_Stack\Host\source\driver\usbevent.h
%FILE %'DirRel_Code'usbevent.c
%include FSL_USB_Stack\Host\source\driver\usbevent.c
%FILE %'DirRel_Code'usbmsgq.c
%include FSL_USB_Stack\Host\source\driver\usbmsgq.c
%FILE %'DirRel_Code'usbmsgq.h
%include FSL_USB_Stack\Host\source\driver\usbmsgq.h
%FILE %'DirRel_Code'usbsem.c
%include FSL_USB_Stack\Host\source\driver\usbsem.c
%FILE %'DirRel_Code'usbsem.h
%include FSL_USB_Stack\Host\source\driver\usbsem.h
%FILE %'DirRel_Code'types.h
%include FSL_USB_Stack\Host\source\driver\types.h
%FILE %'DirRel_Code'usb.h
%include FSL_USB_Stack\Host\source\driver\usb.h
%FILE %'DirRel_Code'usb_bsp.h
%include FSL_USB_Stack\Host\source\driver\usb_bsp.h
%FILE %'DirRel_Code'usb_desc.h
%include FSL_USB_Stack\Host\source\driver\usb_desc.h
%FILE %'DirRel_Code'psptypes.h
%include FSL_USB_Stack\Host\source\driver\psptypes.h
%FILE %'DirRel_Code'usbprv.h
%include FSL_USB_Stack\Host\source\driver\usbprv.h
%FILE %'DirRel_Code'usbprv_host.h
%include FSL_USB_Stack\Host\source\driver\usbprv_host.h

%- Host\examples\common -------------------------------------------
%FILE %'DirRel_Code'hidef.h
%include FSL_USB_Stack\Host\examples\common\hidef.h
%FILE %'DirRel_Code'poll.h
%include FSL_USB_Stack\Host\examples\common\poll.h
%FILE %'DirRel_Code'poll.c
%include FSL_USB_Stack\Host\examples\common\poll.c
%FILE %'DirRel_Code'rtc.h
%include FSL_USB_Stack\Host\examples\common\rtc.h

%if CPUDevice="Kinetis L2K"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_l2k\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis KL24Z48"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_kl24z48\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis KL26Z48"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_kl26z48\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis KL46Z48"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_kl46z48\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K20D50"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k20\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif (CPUDevice="Kinetis K21D50") | (CPUDevice="Kinetis K21F120M")
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k21\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K60"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k60\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K64F"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k64f\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%else
  %error No or unknow (%CPUDevice) device selected in component?
%endif
