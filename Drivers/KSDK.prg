%-
%- Helper to migrate files to the Kinetis SDK
%-
%if (%CPUDB_prph_has_feature(CPU,SDK_SUPPORT) = 'yes') %- TRUE/FALSE not defined for SDK projects
%FILE? %'DirRel_Code'PE_KSDK_Types.h
%include KSDK\PE_KSDK_Types.h
%endif
