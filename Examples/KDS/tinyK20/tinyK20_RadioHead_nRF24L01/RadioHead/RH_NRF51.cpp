// NRF51.cpp
//
// Per: nRF51_Series_Reference_manual v3.0.pdf
// Copyright (C) 2012 Mike McCauley
// $Id: RH_NRF51.cpp,v 1.1 2015/07/01 00:46:05 mikem Exp $

// Set by Arduino IDE when compiling for nRF51 chips:
#ifdef NRF51

#include <RH_NRF51.h>

RH_NRF51::RH_NRF51()
    : _rxBufValid(false)
{
}

bool RH_NRF51::init()
{
    // Enable the High Frequency clock to the system as a whole
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    /* Wait for the external oscillator to start up */
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) { }
    
    // Enables the DC/DC converter when the radio is enabled. Need this!
    NRF_POWER->DCDCEN = 0x00000001; 

    // Disable and reset the radio
    NRF_RADIO->POWER = RADIO_POWER_POWER_Disabled;
    NRF_RADIO->POWER = RADIO_POWER_POWER_Enabled;
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_DISABLE   = 1;
    // Wait until we are in DISABLE state
    while (NRF_RADIO->EVENTS_DISABLED == 0) {}

    // Physical on-air address is set in PREFIX0 + BASE0 by setNetworkAddress
    NRF_RADIO->TXADDRESS    = 0x00;	// Use logical address 0 (PREFIX0 + BASE0)
    NRF_RADIO->RXADDRESSES  = 0x01;	// Enable reception on logical address 0 (PREFIX0 + BASE0)

    // Configure the CRC
    NRF_RADIO->CRCCNF = (RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos); // Number of checksum bits
    NRF_RADIO->CRCINIT = 0xFFFFUL;      // Initial value      
    NRF_RADIO->CRCPOLY = 0x11021UL;     // CRC poly: x^16+x^12^x^5+1

    // These shorts will make the radio transition from Ready to Start to Disable automatically
    // for both TX and RX, which makes for much shorter on-air times
    NRF_RADIO->SHORTS = (RADIO_SHORTS_READY_START_Enabled << RADIO_SHORTS_READY_START_Pos)
	              | (RADIO_SHORTS_END_DISABLE_Enabled << RADIO_SHORTS_END_DISABLE_Pos);

    NRF_RADIO->PCNF0 = ((8 << RADIO_PCNF0_LFLEN_Pos) & RADIO_PCNF0_LFLEN_Msk); // Payload length in bits

    // Make sure we are powered down
    setModeIdle();

    // Set a default network address
    uint8_t default_network_address[] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
    setNetworkAddress(default_network_address, sizeof(default_network_address));

    setChannel(2); // The default, in case it was set by another app without powering down
    setRF(RH_NRF51::DataRate2Mbps, RH_NRF51::TransmitPower0dBm);

    return true;
}

bool RH_NRF51::setChannel(uint8_t channel)
{
    NRF_RADIO->FREQUENCY = ((channel << RADIO_FREQUENCY_FREQUENCY_Pos) & RADIO_FREQUENCY_FREQUENCY_Msk);
    return true;
}

bool RH_NRF51::setNetworkAddress(uint8_t* address, uint8_t len)
{
    if (len < 3 || len > 5)
	return false;

    // First byte is the prefix, remainder are base
    NRF_RADIO->PREFIX0	  = ((address[0] << RADIO_PREFIX0_AP0_Pos) & RADIO_PREFIX0_AP0_Msk);
    uint32_t base;
    memcpy(&base, address+1, len-1);
    NRF_RADIO->BASE0 = base;

    NRF_RADIO->PCNF1 =  (
	(((sizeof(_buf)) << RADIO_PCNF1_MAXLEN_Pos)  & RADIO_PCNF1_MAXLEN_Msk)  // maximum length of payload
	| (((0UL)        << RADIO_PCNF1_STATLEN_Pos) & RADIO_PCNF1_STATLEN_Msk)	// expand the payload with 0 bytes
	| (((len-1)      << RADIO_PCNF1_BALEN_Pos)   & RADIO_PCNF1_BALEN_Msk)); // base address length in number of bytes.

    return true;
}

bool RH_NRF51::setRF(DataRate data_rate, TransmitPower power)
{
    uint8_t mode;
    uint8_t p;

    if (data_rate == DataRate2Mbps)
	mode = RADIO_MODE_MODE_Nrf_2Mbit;
    else if (data_rate == DataRate1Mbps)
	mode = RADIO_MODE_MODE_Nrf_1Mbit;
    else if (data_rate == DataRate250kbps)
	mode = RADIO_MODE_MODE_Nrf_250Kbit;
    else
	return false;// Invalid

    if      (power == TransmitPower4dBm)
	p = RADIO_TXPOWER_TXPOWER_Pos4dBm;
    else if (power == TransmitPower0dBm)
	p = RADIO_TXPOWER_TXPOWER_0dBm;
    else if (power == TransmitPowerm4dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg4dBm;
    else if (power == TransmitPowerm8dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg8dBm;
    else if (power == TransmitPowerm12dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg12dBm;
    else if (power == TransmitPowerm16dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg16dBm;
    else if (power == TransmitPowerm20dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg20dBm;
    else if (power == TransmitPowerm30dBm)
	p = RADIO_TXPOWER_TXPOWER_Neg30dBm;
    else
	return false; // Invalid


    NRF_RADIO->TXPOWER = ((p << RADIO_TXPOWER_TXPOWER_Pos) & RADIO_TXPOWER_TXPOWER_Msk);
    NRF_RADIO->MODE    = ((mode << RADIO_MODE_MODE_Pos) & RADIO_MODE_MODE_Msk);

    return true;
}

void RH_NRF51::setModeIdle()
{
    if (_mode != RHModeIdle)
    {
	NRF_RADIO->TASKS_DISABLE = 1;
	_mode = RHModeIdle;
    }
}

void RH_NRF51::setModeRx()
{
    if (_mode != RHModeRx)
    {
	setModeIdle(); // Can only start RX from DISABLE state
	// Radio will transition automatically to Disable state when a messageis received
	NRF_RADIO->PACKETPTR = (uint32_t)_buf;
	NRF_RADIO->EVENTS_DISABLED = 0U; // So we can detect end of transmission
	NRF_RADIO->TASKS_RXEN = 1;
	_mode = RHModeRx;
    }
}

void RH_NRF51::setModeTx()
{
    if (_mode != RHModeTx)
    {
	setModeIdle(); // Can only start RX from DISABLE state
	// Radio will transition automatically to Disable state at the end of transmission
	NRF_RADIO->PACKETPTR = (uint32_t)_buf;
	NRF_RADIO->EVENTS_DISABLED = 0U; // So we can detect end of transmission
	NRF_RADIO->TASKS_TXEN = 1;
	_mode = RHModeTx;
    }
}

bool RH_NRF51::send(const uint8_t* data, uint8_t len)
{
    if (len > RH_NRF51_MAX_MESSAGE_LEN)
	return false;
    // Set up the headers
    _buf[0] = len + RH_NRF51_HEADER_LEN;
    _buf[1] = _txHeaderTo;
    _buf[2] = _txHeaderFrom;
    _buf[3] = _txHeaderId;
    _buf[4] = _txHeaderFlags;
    memcpy(_buf+RH_NRF51_HEADER_LEN+1, data, len);

    _rxBufValid = false;
    setModeTx();
    // Radio will return to Disabled state after transmission is complete
    _txGood++;
    return true;
}

bool RH_NRF51::waitPacketSent()
{
    // If we are not currently in transmit mode, there is no packet to wait for
    if (_mode != RHModeTx)
	return false;

    // When the Disabled event occurs we know the transmission has completed
    while (NRF_RADIO->EVENTS_DISABLED == 0U)
    {
	YIELD;
    }
    setModeIdle();

    return true;
}

bool RH_NRF51::isSending()
{
    return (NRF_RADIO->STATE == RADIO_STATE_STATE_Tx) ? true : false;
}

bool RH_NRF51::printRegisters()
{
#ifdef RH_HAVE_SERIAL
    uint16_t i;
    uint32_t* p = (uint32_t*)NRF_RADIO;
    for (i = 0; (p + i) < (uint32_t*) (((NRF_RADIO_Type*)NRF_RADIO) + 1); i++)
    {
	Serial.print("Offset: ");
	Serial.print(i, DEC);
	Serial.print(" ");
	Serial.println(*(p+i), HEX);
    }
#endif

    return true;
}

// Check whether the latest received message is complete and uncorrupted
void RH_NRF51::validateRxBuf()
{
    if (_buf[0] < 4)
	return; // Too short to be a real message
    // Extract the 4 headers
    _rxHeaderTo    = _buf[1];
    _rxHeaderFrom  = _buf[2];
    _rxHeaderId    = _buf[3];
    _rxHeaderFlags = _buf[4];
    if (_promiscuous ||
	_rxHeaderTo == _thisAddress ||
	_rxHeaderTo == RH_BROADCAST_ADDRESS)
    {
	_rxGood++;
	_rxBufValid = true;
    }
}

bool RH_NRF51::available()
{
    if (!_rxBufValid)
    {
	if (_mode == RHModeTx)
	    return false;
	setModeRx();
	if (NRF_RADIO->EVENTS_DISABLED == 0U)
	    return false; // No message yet
	if (NRF_RADIO->CRCSTATUS == ((RADIO_CRCSTATUS_CRCSTATUS_CRCError << RADIO_CRCSTATUS_CRCSTATUS_Pos) & RADIO_CRCSTATUS_CRCSTATUS_Msk))
	{
	    // Bad CRC, restart the radio	    
	    _rxBad++;
	    setModeRx();
	    return false;
	}
	validateRxBuf(); 
	if (_rxBufValid)
	    setModeIdle(); // Got one
    }
    return _rxBufValid;
}

void RH_NRF51::clearRxBuf()
{
    _rxBufValid = false;
    _buf[0] = 0;
}

bool RH_NRF51::recv(uint8_t* buf, uint8_t* len)
{
    if (!available())
	return false;
    if (buf && len)
    {
	// Skip the 4 headers that are at the beginning of the rxBuf
	// the payload length is the first octet in _buf
	if (*len > _buf[0]-RH_NRF51_HEADER_LEN)
	    *len = _buf[0]-RH_NRF51_HEADER_LEN;
	memcpy(buf, _buf+RH_NRF51_HEADER_LEN+1, *len);
    }
    clearRxBuf(); // This message accepted and cleared
    return true;
}

uint8_t RH_NRF51::maxMessageLength()
{
    return RH_NRF51_MAX_MESSAGE_LEN;
}

#endif // NRF51
