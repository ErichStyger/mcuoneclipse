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

%if CPUDevice="Kinetis L2K"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_l2k\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis KL26Z48"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_kl26z18\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis KL46Z48"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_kl46z18\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K20D50"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k20\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K21D50"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k21\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%elif CPUDevice="Kinetis K60"
  %FILE? %'DirRel_Code'derivative.h
  %include FSL_USB_Stack\Host\examples\msd\cw10\kinetis_k60\derivative.h
  %FILE? %'DirRel_Code'khci_kinetis.c
  %include FSL_USB_Stack\Host\source\driver\kinetis\khci_kinetis.c
%endif

