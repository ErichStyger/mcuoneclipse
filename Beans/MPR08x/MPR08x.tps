<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>SounderClickPeriodType</Name>
      <Items lines_count="2">
        <Line>10 ms</Line>
        <Line>20 ms</Line>
      </Items>
      <Hints lines_count="2">
        <Line>10 ms Sounder Click Period</Line>
        <Line>20 ms Sounder Click Period</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>0</Line>
        <Line>1</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>SounderFrequencyType</Name>
      <Items lines_count="2">
        <Line>1 kHz</Line>
        <Line>2 KHz</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Sounder Frequency is 1 kHz</Line>
        <Line>Sounder Frequency is 2 kHz</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>0</Line>
        <Line>1</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>RunModeType</Name>
      <Items lines_count="4">
        <Line>Run1</Line>
        <Line>Run2</Line>
        <Line>Stop1</Line>
        <Line>Stop2</Line>
      </Items>
      <Hints lines_count="4">
        <Line>When in Run1 mode the sensor controller will run continuously.</Line>
        <Line>When in Run2 mode the sensor controller will continue to scan the electrodes but a low power state will be enabled between each cycle. Because of this, any I2C communication that occurs, may or may not respond while the sensor is in this mode.</Line>
        <Line>When in Stop1 mode the sensor controller will not scan the electrodes. While capacitance sensing is disabled I2C communications will still be accepted and the sensor controller will maintain instantaneous response to all register requests. This is the only mode in which register values can be set.</Line>
        <Line>When in Stop2 mode the sensor controller will not scan the electrodes or accept I2C communication. The MPR083 is off during this mode.</Line>
      </Hints>
      <Defines lines_count="4">
        <Line>5</Line>
        <Line>1</Line>
        <Line>4</Line>
        <Line>0</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>MPRDeviceType</Name>
      <Items lines_count="2">
        <Line>MPR083</Line>
        <Line>MPR084</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Device is the 8 pad rotary sensor MPR083</Line>
        <Line>Device is the 8 pad single key sensor MPR084.</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>MPR083</Line>
        <Line>MPR084</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
