<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeMemAllocScheme</Name>
      <Items lines_count="4">
        <Line>Scheme 1</Line>
        <Line>Scheme 2</Line>
        <Line>Scheme 3</Line>
        <Line>Scheme 4</Line>
      </Items>
      <Hints lines_count="4">
        <Line>This is the simplest scheme of all. It does not permit memory to be freed once it has been allocated, but despite this is suitable for a surprisingly large number of applications.</Line>
        <Line>This scheme uses a best fit algorithm and, unlike scheme 1, allows previously allocated blocks to be freed. It does not however combine adjacent free blocks into a single large block.</Line>
        <Line>This is just a wrapper for the standard malloc() and free() functions. It makes them thread safe.</Line>
        <Line>This scheme includes memory block coalescence.</Line>
      </Hints>
      <Defines lines_count="4">
        <Line>Scheme1</Line>
        <Line>Scheme2</Line>
        <Line>Scheme3</Line>
        <Line>Scheme4</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeCFswi</Name>
      <Items lines_count="7">
        <Line>VL1swi</Line>
        <Line>VL2swi</Line>
        <Line>VL3swi</Line>
        <Line>VL4swi</Line>
        <Line>VL5swi</Line>
        <Line>VL6swi</Line>
        <Line>VL7swi</Line>
      </Items>
      <Hints lines_count="7">
        <Line>using VL1swi</Line>
        <Line>using VL2swi</Line>
        <Line>using VL3swi</Line>
        <Line>using VL4swi</Line>
        <Line>using VL5swi</Line>
        <Line>using VL6swi</Line>
        <Line>using VL7swi</Line>
      </Hints>
      <Defines lines_count="7">
        <Line>VL1swi</Line>
        <Line>VL2swi</Line>
        <Line>VL3swi</Line>
        <Line>VL4swi</Line>
        <Line>VL5swi</Line>
        <Line>VL6swi</Line>
        <Line>VL7swi</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeCFcpu</Name>
      <Items lines_count="5">
        <Line>MCF51CN</Line>
        <Line>MCF51JM</Line>
        <Line>MCF51QE</Line>
        <Line>MCF51JE</Line>
        <Line>MCF51MM</Line>
      </Items>
      <Hints lines_count="5">
        <Line>ColdFire V1 MCF51CN family</Line>
        <Line>ColdFire V1 MCF51JM family</Line>
        <Line>ColdFire V1 MCF51QE family</Line>
        <Line>ColdFire V1 MCF51JE family</Line>
        <Line>ColdFire V1 MCF51MM family</Line>
      </Hints>
      <Defines lines_count="5">
        <Line>MCF51CN</Line>
        <Line>MCF51JM</Line>
        <Line>MCF51QE</Line>
        <Line>MCF51JE</Line>
        <Line>MCF51MM</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeStackOverflowMethod</Name>
      <Items lines_count="3">
        <Line>Method 1</Line>
        <Line>Method 2</Line>
        <Line>none</Line>
      </Items>
      <Hints lines_count="3">
        <Line>It is likely that the stack will reach its greatest (deepest) value after the kernel has swapped the task out of the Running state because this is when the stack will contain the task context. At this point the kernel can check that the processor stack pointer remains within the valid stack space. The stack overflow hook function is called if the stack pointer contain a value that is outside of the valid stack range.  This method is quick but not guaranteed to catch all stack overflows.</Line>
        <Line>When a task is first created its stack is filled with a known value. When swapping a task out of the Running state the kernel can check the last 16 bytes within the valid stack range to ensure that these known values have not been overwritten by the task or interrupt activity. The stack overflow hook function is called should any of these 16 bytes not remain at their initial value.  This method is less efficient than method one, but still fairly fast. It is very likely to catch stack overflows but is still not guaranteed to catch all overflows.</Line>
        <Line>No Stack Overflow checking</Line>
      </Hints>
      <Defines lines_count="3">
        <Line>1</Line>
        <Line>2</Line>
        <Line>0</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeCF2cpu</Name>
      <Items lines_count="1">
        <Line>MCF5225x</Line>
      </Items>
      <Hints lines_count="1">
        <Line>ColdFire V2 MCF5225x family</Line>
      </Hints>
      <Defines lines_count="1">
        <Line>MCF5225x</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeOptimizationLevel</Name>
      <Items lines_count="5">
        <Line>0</Line>
        <Line>1</Line>
        <Line>2</Line>
        <Line>3</Line>
        <Line>4</Line>
      </Items>
      <Hints lines_count="5">
        <Line>Optimization level 0</Line>
        <Line>Optimization level 1</Line>
        <Line>Optimization level 2</Line>
        <Line>Optimization level 3</Line>
        <Line>Optimization level 4</Line>
      </Hints>
      <Defines lines_count="5">
        <Line>0</Line>
        <Line>1</Line>
        <Line>2</Line>
        <Line>3</Line>
        <Line>4</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeARMFamily</Name>
      <Items lines_count="3">
        <Line>Cortex M0+</Line>
        <Line>Cortex M4</Line>
        <Line>Cortex M4F</Line>
      </Items>
      <Hints lines_count="3">
        <Line>ARM Cortex M0+ (Kinetis L family)</Line>
        <Line>ARM Cortex M4 (Kinetis K family)</Line>
        <Line>ARM Cortex M4 (Kinetis K family with floating point unit)</Line>
      </Hints>
      <Defines lines_count="3">
        <Line>M0+</Line>
        <Line>M4</Line>
        <Line>M4F</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
