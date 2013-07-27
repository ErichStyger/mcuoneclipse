<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeRecorderStoreMode</Name>
      <Items lines_count="2">
        <Line>Ring Buffer</Line>
        <Line>Stop when full</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Using ring buffer</Line>
        <Line>Stops recording when buffer is ful</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>TRACE_STORE_MODE_RING_BUFFER</Line>
        <Line>TRACE_STORE_MODE_STOP_WHEN_FULL</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeTimerPort</Name>
      <Items lines_count="2">
        <Line>OS Tick</Line>
        <Line>HW Timer</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Using the OS Tick as low resolution timestamps</Line>
        <Line>Using hardware timer (RTOS performance timer)</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>TIMER_PORT_TYPE_OSTICK</Line>
        <Line>TIMER_PORT_TYPE_HWTC</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeTraceDataAllocation</Name>
      <Items lines_count="2">
        <Line>static</Line>
        <Line>dynamic</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Static trace data allocation</Line>
        <Line>Dynamic trace data allocation</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>TRACE_DATA_ALLOCATION_STATIC</Line>
        <Line>TRACE_DATA_ALLOCATION_DYNAMIC</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
