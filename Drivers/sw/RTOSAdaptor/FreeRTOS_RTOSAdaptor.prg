%-
%- Implementation of RTOS ADAPTOR for FreeRTOS
%-
%- (C) 2011 Freescale, all rights reserved
%-
%------------------------------------------------------------------------------
%- Including common RTOS adapter library.
%------------------------------------------------------------------------------
%- It is included indirectly through symbol as a workaround of limitation
%- of the tool used for creating installation.
%-
%define RTOSAdap_priv_CommonAdapterInterface sw\RTOSAdaptor\Common_RTOSAdaptor.prg
%include %'RTOSAdap_priv_CommonAdapterInterface'
%undef RTOSAdap_priv_CommonAdapterInterface
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRTOSTypeDefinitions
%------------------------------------------------------------------------------
  %- PUBLIC TYPES
%{ {%'OperatingSystemId' RTOS Adapter} RTOS specific definition of type of Ioctl() command constants %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genDriverInstallationsFunctionDefinition
%------------------------------------------------------------------------------
%- For bare-board RTOS no driver installations are generated.
%-
%{ {%'OperatingSystemId' RTOS Adapter} Function PE_LDD_driver_installations() definition: It is not generated %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genDriverInstallationsFunctionDeclaration
%------------------------------------------------------------------------------
%- For bare-board RTOS no driver installations are generated.
%-
%{ {%'OperatingSystemId' RTOS Adapter} Function PE_LDD_driver_installations() declaration: It is not generated %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genDriverMemoryAlloc(arg_destPtrBuffer,arg_objType,opt_arg_errCode,arg_globDefsThread,opt_arg_MemoryAllocParams)
%------------------------------------------------------------------------------
  %-
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(componentInstanceName,,loc_componentInstanceName)
  %-
  %- Check if RTOSAdap_driverMemoryAlloc() was called only once for this object
  %if defined(RTOSAdap_alloc_object_%'arg_destPtrBuffer')
    %error! There was called allocation for object "%'arg_destPtrBuffer'" for object type "%'arg_objType'" twice (which does not work for bareboard RTOS what only simulates the dynamic allocation)
  %else
    %- o.k., it is first call, mark that such object was allocated
    %define RTOSAdap_alloc_object_%'arg_destPtrBuffer'
  %endif
 %-
  %THREAD %'arg_globDefsThread' SELECT
%>1%{ {%'OperatingSystemId' RTOS Adapter} Static object used for simulation of dynamic driver memory allocation %}
  %THREAD %'arg_globDefsThread' UNSELECT
  %-
  %-
  %define! loc_ObjDefPrefix
  %define! loc_ObjDefSuffix
  %-
  %------------------------------------------------------------------------------
  %- Processing of optional parameters
  %------------------------------------------------------------------------------
  %inclSUB RTOSAdap_lib_getStructMember(%'opt_arg_MemoryAllocParams',ALIGN,loc_Param_Align,optional)
  %inclSUB RTOSAdap_lib_getStructMember(%'opt_arg_MemoryAllocParams',ZERO,loc_Param_Zero,optional)
  %------------------------------------------------------------------------------
  %- Processing of ALIGN optional parameter
  %------------------------------------------------------------------------------
  %if loc_Param_Align != 'undef'
    %if loc_Param_Align != ''
      %- Add new data section to linker file
      %if (Compiler = 'CodeWarriorARM') | (Compiler = 'CodeWarriorMCF')
        %add PE_G_LCF_DATA_SECTION .%'loc_componentInstanceName'_memory_section
        %add PE_G_LCF_DATA_ALIGN %loc_Param_Align
        %define! loc_ObjDefPrefix __declspec(%'loc_componentInstanceName'_memory_section)%_space_
      %elif (Compiler = 'IARARM')
        %add PE_G_LCF_DATA_SECTION %'loc_componentInstanceName'_memory_section
        %add PE_G_LCF_DATA_ALIGN %loc_Param_Align
      %elif (Compiler = 'IARMCF')
        %- No linker file modifications needed.
      %elif (Compiler = 'GNUC')
        %- No linker file modifications needed.
      %elif (Compiler = 'ARM_CC')
        %- No linker file modifications needed.
      %else
        %error! RTOS adapter: Unsupported compiler to allign allocated memory!
      %endif
      %THREAD %'arg_globDefsThread' SELECT
      %if (Compiler = 'CodeWarriorARM') | (Compiler = 'CodeWarriorMCF')
%>1%{ This pragma aligns an object to %loc_Param_Align bytes boundary. %}
%>1#pragma define_section %'loc_componentInstanceName'_memory_section ".%'loc_componentInstanceName'_memory_section" far_abs RW
      %elif (Compiler = 'IARARM')
%>1%{ This pragma aligns an object to %loc_Param_Align bytes boundary. %}
%>1#pragma location=".%'loc_componentInstanceName'_memory_section"
      %elif (Compiler = 'IARMCF')
%>1%{ This pragma aligns an object to %loc_Param_Align bytes boundary. %}
%>1#pragma data_alignment=%loc_Param_Align
      %elif (Compiler = 'GNUC')
        %define! loc_ObjDefSuffix %'_space_'__attribute__ ((aligned (%'loc_Param_Align')))
      %elif (Compiler = 'ARM_CC')
        %define! loc_ObjDefSuffix %'_space_'__attribute__ ((aligned (%'loc_Param_Align')))
      %endif
      %THREAD %'arg_globDefsThread' UNSELECT
    %else
      %error! Parameter ALIGN has no value
    %endif
    %undef loc_Param_Align
  %endif
  %-
  %- Generate definition of static object
  %define loc_staticObjName %'arg_destPtrBuffer'__DEFAULT_RTOS_ALLOC
  %THREAD %'arg_globDefsThread' SELECT
%>1%'loc_ObjDefPrefix'static %'arg_objType' %'loc_staticObjName'%'loc_ObjDefSuffix';
  %THREAD %'arg_globDefsThread' UNSELECT
  %-
%{ {%'OperatingSystemId' RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object %}
%'arg_destPtrBuffer' = &%'loc_staticObjName';
  %------------------------------------------------------------------------------
  %- Processing of ZERO optional parameter
  %------------------------------------------------------------------------------
  %if loc_Param_Zero != 'undef'
%{ {%'OperatingSystemId' RTOS Adapter} Driver memory allocation: Fill the allocated memory by zero value %}
PE_FillMemory(%'arg_destPtrBuffer', 0U, sizeof(%'arg_objType'));
    %undef loc_Param_Zero
  %endif
  %-
  %undef loc_staticObjName
  %undef loc_ObjDefPrefix
%SUBROUTINE_END
%- 
%- <<< EST old code for dynamic memory allocation:
%-  %- Dynamic allocation is supported (generate it)
%-   %inclSUB RTOSAdap_getRTOSFunction(Malloc,loc_MallocFunction)
%- %{ {%'OperatingSystemId' RTOS Adapter} Driver memory allocation: RTOS function call is defined by %'OperatingSystemId' RTOS Adapter property %}
%- %-MEM_ALLOC_FUNCTION_START
%- %'arg_destPtrBuffer' = (%'arg_objType' *)%'loc_MallocFunction'(sizeof(%'arg_objType'));
%- %-MEM_ALLOC_FUNCTION_END
%- %if opt_arg_errCode <> ''
%- #if FreeRTOS_CHECK_MEMORY_ALLOCATION_ERRORS
%- if (%'arg_destPtrBuffer' == NULL) {
%-   %'opt_arg_errCode'
%- }
%- #endif
%- %endif
%-   %-
%-   %- Set memory block type (not supported now)
%- %-_mem_set_type(%'arg_destPtrBuffer', MEM_TYPE_...);
%-   %-
%-   %undef loc_MallocFunction
%- %SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genDriverMemoryDealloc(arg_ptrBuffer,arg_objType)
%------------------------------------------------------------------------------
  %- Bare-board RTOS is simulating dynamic allocation by static allocation.
  %- Allocation is only simulated, so deallocation has no effect.
%{ {%'OperatingSystemId' RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated %}
%SUBROUTINE_END
%- 
%- << EST code with dynamic memory allocation
%-  %- Dynamic allocation is supported, generate it
%-  %inclSUB RTOSAdap_getRTOSFunction(Dealloc,loc_DeallocFunction)
%- %{ {%'OperatingSystemId' RTOS Adapter} Driver memory deallocation: RTOS function call is defined by %'OperatingSystemId' RTOS Adapter property %}
%- %-MEM_DEALLOC_FUNCTION_START
%- #if FRTOS_MEMORY_SCHEME != 1 /* scheme 1 has no deallocate */
%- %'loc_DeallocFunction'(%'arg_ptrBuffer');
%- #endif
%- %-MEM_DEALLOC_FUNCTION_END
%-   %-
%-   %undef loc_DeallocFunction
%- %SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_getInterruptVectorSymbol(arg_vectorName,out_vectorIndexConstantName)
%------------------------------------------------------------------------------
  %- In bareboard RTOS interrupt vector table is generated by PE and linked statically.
  %-
  %- Such symbol is not used in bare-board, but for syntax compatibility the
  %- sub-routine must return "something" valid.
  %-
  %define! %out_vectorIndexConstantName LDD_ivIndex_%'arg_vectorName'
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genSetInterruptVector(arg_intVectorProperty,arg_isrFunctionName,arg_isrParameterType,arg_isrParameterValue,opt_arg_oldISRSettings,arg_globDefsThread)
%------------------------------------------------------------------------------
%- Bareboard arg_isrParameterType limitation: No. Parameter can be of any type.
%-
  %- In bareboard RTOS interrupt vector table is generated by PE and linked statically.
  %-
  %- Check if RTOSAdap_genSetInterruptVector() was called only once for this interrupt vector
  %if defined(RTOSAdap_alloc_interrupt_%"%'arg_intVectorProperty'_Name")
    %error! There was called allocation for interrupt vector %"%'arg_intVectorProperty'_Name" twice (which does not work for bareboard RTOS what only simulates the run-time vector allocation)
  %else
    %- o.k., it is first call, mark that interrupt vector was allocated
    %define RTOSAdap_alloc_interrupt_%"%'arg_intVectorProperty'_Name"
  %endif
  %-
  %- No ISR run-time allocation is used.
  %- Register ISR function to be statically generated into the vector table
  %if (%"%'arg_intVectorProperty'Shared" = 'no')
    %-Not shared interrupt vector
    %define_prj iv%"%'arg_intVectorProperty'_Name" %'arg_isrFunctionName'
  %else
    %- Shared interrupt vector
  %endif
  %-
  %if (arg_isrParameterType != '')
%{ {%'OperatingSystemId' RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable %}
%"%'arg_intVectorProperty'_Name"__BAREBOARD_RTOS_ISRPARAM = %'arg_isrParameterValue';
  %-
  %- Generate the definition of the global variable holding ISR parameter value
  %THREAD %'arg_globDefsThread' SELECT
%>1%{ {%'OperatingSystemId' RTOS Adapter} Global variable used for passing a parameter into ISR %}
%>1static %'arg_isrParameterType' %"%'arg_intVectorProperty'_Name"__BAREBOARD_RTOS_ISRPARAM;
  %THREAD %'arg_globDefsThread' UNSELECT
  %endif
  %-
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRestoreInterruptVector(arg_intVectorProperty,arg_oldISRSettings)
%------------------------------------------------------------------------------
  %- In bareboard RTOS interrupt vector table is generated by PE and linked statically.
  %- No ISR run-time allocation is used, so deallocation has no effect.
%{ {%'OperatingSystemId' RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genISRSettingsVarDeclaration(arg_varName,opt_arg_comment)
%------------------------------------------------------------------------------
  %- In bareboard RTOS interrupt vector table is generated by PE and linked statically.
  %- No object for saving/restoring ISR vector is used, so no delcaration is generated
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genISRFunctionDefinitionOpen(arg_intVectorProperty,arg_isrFunctionName,arg_isrParameterType,arg_isrParameterName)
%------------------------------------------------------------------------------
%- Bareboard arg_isrParameterType limitation: No. Parameter can be of any type.
%-
%if ((%'arg_intVectorProperty' = '$SHARED') | (%"%'arg_intVectorProperty'Shared" = 'no'))
  %- Not shared interrupt vector
%include Common\DefineISR.prg(%'arg_isrFunctionName')
%else
void %'arg_isrFunctionName'(void)
%endif
{
  %if arg_isrParameterName != ''
  %{ {%'OperatingSystemId' RTOS Adapter} ISR parameter is passed through the global variable %}
  %'arg_isrParameterType' %'arg_isrParameterName' = %"%'arg_intVectorProperty'_Name"__BAREBOARD_RTOS_ISRPARAM;
  %endif
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genISRFunctionDefinitionClose(arg_intVectorProperty,arg_isrFunctionName,arg_isrParameterType,arg_isrParameterName)
%------------------------------------------------------------------------------
}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genISRFunctionDeclaration(arg_intVectorProperty,arg_isrFunctionName,arg_isrParameterType,arg_isrParameterName)
%------------------------------------------------------------------------------
%- Bareboard arg_isrParameterType limitation: No. Parameter can be of any type.
%-
%{ {%'OperatingSystemId' RTOS Adapter} ISR function prototype %}
%if ((%'arg_intVectorProperty' = '$SHARED') | (%"%'arg_intVectorProperty'Shared" = 'no'))
  %- Not shared interrupt vector
  %if (%'arg_intVectorProperty' != '$SHARED')
    %define! RTOSAdap_intVectorPropertySymbol_%"%'arg_intVectorProperty'_Name" %arg_intVectorProperty
    %define! RTOSAdap_intVectorName_%'arg_isrFunctionName' %"%'arg_intVectorProperty'_Name"
    %define! RTOSAdap_isrFunctionName_%"%'arg_intVectorProperty'_Name" %arg_isrFunctionName
  %endif
%include Common\CreateIntSection.prg
%include Common\DeclareISR.prg(%'arg_isrFunctionName')
%include Common\CreateCodeSection.prg
%else
  %- Shared interrupt vector
void %'arg_isrFunctionName'(void);
%endif
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genReentrantMethodBegin(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
  %- Handle optional parameter
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(genReentrantMethods,%'opt_arg_genReentrantMethods',arg_genReentrantMethods)
  %- In bareboard use standard Processor Expert function generated into PE_Types.h.
  %if arg_genReentrantMethods == 'yes'
    %- Reentrant methods are required, generate enter critical section
%{ {%'OperatingSystemId' RTOS Adapter} Method is required to be reentrant, critical section begins, general PE function is used %}
EnterCritical();
  %elif arg_genReentrantMethods == 'no'
    %- Reentrant methods are not required, no code is generated
  %else
    %error! Invalid value of parameter 'opt_arg_genReentrantMethods' ("%'arg_genReentrantMethods'")
  %endif
  %-
  %undef arg_genReentrantMethods
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genReentrantMethodEnd(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
  %- Handle optional parameter
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(genReentrantMethods,%'opt_arg_genReentrantMethods',arg_genReentrantMethods)
  %- In bareboard use standard Processor Expert function generated into PE_Types.h.
  %if arg_genReentrantMethods == 'yes'
    %- Reentrant methods are required, generate exit critical section
%{ {%'OperatingSystemId' RTOS Adapter} Critical section end, general PE function is used %}
ExitCritical();
  %elif arg_genReentrantMethods == 'no'
    %- Reentrant methods are not required, no code is generated
  %else
    %error! Invalid value of parameter 'opt_arg_genReentrantMethods' ("%'arg_genReentrantMethods'")
  %endif
  %-
  %undef arg_genReentrantMethods
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genCriticalSectionBegin(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
  %- Handle optional parameter
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(genReentrantMethods,%'opt_arg_genReentrantMethods',arg_genReentrantMethods)
  %- In bareboard use standard Processor Expert function generated into PE_Types.h.
  %if arg_genReentrantMethods == 'yes'
    %- The method itself is generated as reentrant, additional critical sections are not needed
  %elif arg_genReentrantMethods == 'no'
    %- Reentrant methods are not required, but critical sections must remain
    %inclSUB RTOSAdap_getRTOSFunction(EnterCritical,loc_enterCriticalFunctionName)
%{ {%'OperatingSystemId' RTOS Adapter} Critical section begin (RTOS function call is defined by %'OperatingSystemId' RTOS Adapter property) %}
%'loc_enterCriticalFunctionName'();
    %undef loc_enterCriticalFunctionName
  %else
    %error! Invalid value of parameter 'opt_arg_genReentrantMethods' ("%'arg_genReentrantMethods'")
  %endif
  %-
  %undef arg_genReentrantMethods
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genCriticalSectionEnd(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
  %- Handle optional parameter
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(genReentrantMethods,%'opt_arg_genReentrantMethods',arg_genReentrantMethods)
  %- In bareboard use standard Processor Expert function generated into PE_Types.h.
  %if arg_genReentrantMethods == 'yes'
    %- The method itself is generated as reentrant, additional critical sections are not needed
  %elif arg_genReentrantMethods == 'no'
    %- Reentrant methods are not required, but critical sections must remain
    %inclSUB RTOSAdap_getRTOSFunction(ExitCritical,loc_exitCriticalFunctionName)
%{ {%'OperatingSystemId' RTOS Adapter} Critical section ends (RTOS function call is defined by %'OperatingSystemId' RTOS Adapter property) %}
%'loc_exitCriticalFunctionName'();
    %undef loc_exitCriticalFunctionName
  %else
    %error! Invalid value of parameter 'opt_arg_genReentrantMethods' ("%'arg_genReentrantMethods'")
  %endif
  %-
  %undef arg_genReentrantMethods
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genIoctlCommandConstantDefinition(arg_commandName,arg_commandLogicalIndex,opt_arg_simpleComponentType)
%------------------------------------------------------------------------------
  %- Get constant name
  %inclSUB RTOSAdap_getIoctlCommandConstantName(%'arg_commandName',%'opt_arg_simpleComponentType',loc_constantName)
  %-
#define %'loc_constantName'                                      %>57((LDD_RTOS_TIoctlCommand)%'arg_commandLogicalIndex')
  %-
  %undef loc_constantName
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_getIoctlCommandConstantName(arg_commandName,opt_arg_simpleComponentType,out_constantName)
%------------------------------------------------------------------------------
  %- Handle optional parameters
  %inclSUB RTOSAdap_priv_getOptionalParameterEffectiveValue(simpleComponentType,%'opt_arg_simpleComponentType',arg_simpleComponentType)
  %-
  %- Check if arg_componentType is a valid enumerated value
  %:loc_simpleCompTypeIndex = %get_index1(%'arg_simpleComponentType',RTOSAdap_enum_simpleComponentTypes)
  %if loc_simpleCompTypeIndex = '-1'
    %error! Invalid HAL simple component type "%'arg_simpleComponentType'"
  %endif
  %-
  %define! %'out_constantName' %'arg_simpleComponentType'_IOCTL_%'arg_commandName'
  %-
  %undef arg_simpleComponentType
  %undef loc_simpleCompTypeIndex
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRTOSIncludes()
%------------------------------------------------------------------------------
#include "FreeRTOS.h" /* FreeRTOS interface */
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRTOSDriverIncludes()
%------------------------------------------------------------------------------
%{ {%'OperatingSystemId' RTOS Adapter} No RTOS driver includes %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genPublishedRTOSSettings
%------------------------------------------------------------------------------
%{ {%'OperatingSystemId' RTOS Adapter} No published RTOS settings %}
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genMemoryBarrierBegin(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genMemoryBarrierEnd(opt_arg_genReentrantMethods)
%------------------------------------------------------------------------------
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genReentrantMethodDeclare(opt_arg_genReentrantMethods, spinlock_name)
%------------------------------------------------------------------------------
 %- Do nothing for FreeRTOS 
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRTOSReturnIRQ_Attended()
%------------------------------------------------------------------------------
return;
%SUBROUTINE_END
%-
%-
%------------------------------------------------------------------------------
%SUBROUTINE RTOSAdap_genRTOSReturnIRQ_NOTAttended()
%------------------------------------------------------------------------------
return;
%SUBROUTINE_END
%-