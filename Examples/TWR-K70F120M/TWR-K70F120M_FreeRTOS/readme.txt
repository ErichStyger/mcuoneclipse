readme.txt
----------

This application demontrates FreeRTOS as Processor Expert component on the TWR-K60 board.
It creates 4 LED tasks, each blinking an LED on the board, plus a main task which is using
a shell to communicate with the TWR-SER RS-232 (38400 baud).

This demo has been used with MCU10.2beta (www.freescale.com/cwmuc10).

Steps if you want to add FreeRTOS to your own Processor Expert project:
- Add the FreeRTOS component to the project.
  This will automatically add the Utility component too (used for kernel statistics) if not alrady present.
- Make sure you specify the same optimization level and floating point option settings in the Scheduler > Kinetis settings as specified in 
  the Kinetis compiler settings. Otherwise the stack frame will not match with the interrupt service 
  routine code produced by Processor Expert.
- Inside the FreeRTOS component, configure a timer (e.g. to 10 ms tick period)
- The port requires the assembler to include a FreeRTOS header file.
  In the assembler build tools settings, make sure that the assembler finds header file in the Generated_Code folder.
  (project 'Properties > C/C++ Build > Settings > ARM Assembler > Input' and add "${ProjDirPath}\Generated_Code" to the user path.
- Enable the 'Supervisor Call' and 'Pendable Service' interrupts in the CPU component:
  You find them in the CPU component > Properties tab > CPU interrupts/resets group.
- In Events.c, make sure both the supervisor call interrupt and pendable service interrupt call the corresponding RTOS methods: 
    void Cpu_OnSupervisorCall(void)
    {
      vPortSVCHandler();
    }
    
    void Cpu_OnPendableService(void)
    {
      xPortPendSVHandler();
    }
- Make sure you have enough heap set up in the FreeRTOS component
- Generate code, build and download   