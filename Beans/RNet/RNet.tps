<?xml version="1.0" encoding="UTF-8"?>
<TypesAndGlobals>
  <Types>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeTransceiver</Name>
      <Items lines_count="2">
        <Line>nRF24L01+</Line>
        <Line>MC13201</Line>
      </Items>
      <Hints lines_count="2">
        <Line>Nordic Semiconductor nRF24L01+</Line>
        <Line>Freescale Semiconductor MC13201/MC13213</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>RNET_CONFIG_TRANSCEIVER_NRF24</Line>
        <Line>RNET_CONFIG_TRANSCEIVER_MC13201</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeShortAddressSize</Name>
      <Items lines_count="2">
        <Line>8 Bits</Line>
        <Line>16 Bits</Line>
      </Items>
      <Hints lines_count="2">
        <Line>8bit network node address</Line>
        <Line>16bit network node address</Line>
      </Hints>
      <Defines lines_count="2">
        <Line>1</Line>
        <Line>2</Line>
      </Defines>
    </Type>
    <Type>
      <Type>TEnumSpec</Type>
      <Name>typeNRF24_DataRate</Name>
      <Items lines_count="3">
        <Line>250 kBit</Line>
        <Line>1000 kBit</Line>
        <Line>2000 kBit</Line>
      </Items>
      <Hints lines_count="3">
        <Line>255 kBit</Line>
        <Line>1000 kBit</Line>
        <Line>2000 kBit</Line>
      </Hints>
      <Defines lines_count="3">
        <Line>RF_SETUP_RF_DR_250</Line>
        <Line>RF_SETUP_RF_DR_1000</Line>
        <Line>RF_SETUP_RF_DR_2000</Line>
      </Defines>
    </Type>
  </Types>
</TypesAndGlobals>
