<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeRegisterDeclaration</Name>
      <Items lines_count="5">
        <Line>By Bit Name</Line>
        <Line>By Port Name</Line>
        <Line>By Address</Line>
        <Line>By LDD</Line>
        <Line>Set Clear Port Name</Line>
      </Items>
      <Hints lines_count="5">
        <Line>Resource is defined with a symbol/name identifying the register bit.</Line>
        <Line>Resource is defined with a symbol/name identifying the register plus a bit number.</Line>
        <Line>Resource is defined with an address identifying the register plus a bit number.</Line>
        <Line>Ressource is using Logical Device Driver (LDD).</Line>
        <Line>Ressource is using special set and clear registers.</Line>
      </Hints>
      <Defines lines_count="5">
        <Line>bitname</Line>
        <Line>portname</Line>
        <Line>address</Line>
        <Line>ldd</Line>
        <Line>setClearPortName</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeDirection</Name>
      <Items lines_count="2">
        <Line>input</Line>
        <Line>output</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Port is configured as input.</Line>
        <Line>Port is configured as output.</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>input</Line>
        <Line>output</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
