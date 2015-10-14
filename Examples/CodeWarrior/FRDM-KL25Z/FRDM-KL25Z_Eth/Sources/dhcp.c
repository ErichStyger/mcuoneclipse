/**
 * \file
 * \brief This is the implementation for DHCP
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This implements the DHCP part for the W5100.
 */

#include "Platform.h"
#if PL_USE_DHCP
#include "dhcp.h"
#include "w5100.h"
#include "socket.h"

static uint8_t g_DHCP_YourIPAddress[4];
static uint8_t g_DHCP_RouterIPAddress[4];
static uint8_t g_DHCP_DNSIPAddress[4];
static uint8_t g_DHCP_SubnetMask[4];
static uint8_t g_DHCP_ServerIPAddress[4];
static uint32_t g_DHCP_LeaseTime;


//---------------------------------------------------------------------------------------
// Name:        DHCP_GetIPAddress
// Param:		-
// Return:      TRUE in case of success, FALSE if an error occurred
//
// Description:	This function is used to get IP Address and other network parameters using DHCP
//---------------------------------------------------------------------------------------
bool DHCP_GetIPAddress(void) {
	uint8_t u8Index;
	uint8_t u8Socket = DHCP_SOCKET;
	bool bResult = FALSE;
	
	/* Initializations */
	g_DHCP_LeaseTime = 0;
	for (u8Index = 0; u8Index < 4; u8Index++)	{
		g_DHCP_YourIPAddress[u8Index] = 0;
		g_DHCP_RouterIPAddress[u8Index] = 0;
		g_DHCP_DNSIPAddress[u8Index] = 0;
		g_DHCP_SubnetMask[u8Index] = 0;
		g_DHCP_ServerIPAddress[u8Index] = 0;
	}
	
	/* Open a new socket */
	if (SOCK_OpenSocket(u8Socket, W5100_SKT_MR_UDP, DHCP_CLIENT_PORT)==ERR_OK) {
		/* Send DISCOVER message */
		if (DHCP_SendMessage(u8Socket, DHCP_DISCOVER) == TRUE) {
			/* Parse OFFER message */
			if (DHCP_Parse(u8Socket) == DHCP_OFFER) {
				/* Send REQUEST message */
				if (DHCP_SendMessage(u8Socket, DHCP_REQUEST) == TRUE) {
					/* Parse ACK message */
					if (DHCP_Parse(u8Socket) == DHCP_ACK) {
						/* Set Gateway IP Address  */
						W5100_MemWriteByte(W5100_GAR0, g_DHCP_RouterIPAddress[0]);
						W5100_MemWriteByte(W5100_GAR1, g_DHCP_RouterIPAddress[1]);
						W5100_MemWriteByte(W5100_GAR2, g_DHCP_RouterIPAddress[2]);
						W5100_MemWriteByte(W5100_GAR3, g_DHCP_RouterIPAddress[3]);
						
						/* Set Subnet Mask */
						W5100_MemWriteByte(W5100_SUBR0, g_DHCP_SubnetMask[0]);
						W5100_MemWriteByte(W5100_SUBR1, g_DHCP_SubnetMask[1]);
						W5100_MemWriteByte(W5100_SUBR2, g_DHCP_SubnetMask[2]);
						W5100_MemWriteByte(W5100_SUBR3, g_DHCP_SubnetMask[3]);
						
						/* Set my IP Address */
						W5100_MemWriteByte(W5100_SIPR0, g_DHCP_YourIPAddress[0]);
						W5100_MemWriteByte(W5100_SIPR1, g_DHCP_YourIPAddress[1]);
						W5100_MemWriteByte(W5100_SIPR2, g_DHCP_YourIPAddress[2]);
						W5100_MemWriteByte(W5100_SIPR3, g_DHCP_YourIPAddress[3]);
						
						bResult = TRUE;
					}
				}
			}
		}
		/* Close the socket (socket can be used later in the application) */
		SOCKET_Close(u8Socket);
	}
	return bResult;
}

//---------------------------------------------------------------------------------------
// Name:        DHCP_SendMessage
// Param:		Socket: socket to use
//				MessageType: message type to send
// Return:      TRUE in case of success, FALSE if an error occurred
//
// Description:	This function is used to send DHCP messages
//---------------------------------------------------------------------------------------
static bool DHCP_SendMessage(uint8_t u8Socket, uint8_t u8MessageType) {
	bool bResult = FALSE;
	uint8_t u8Index;
	uint16_t u16TxFreeSize;
	uint16_t u16TxPointer;
	uint16_t u16TxBaseAddress;
	uint16_t u16TxBufferSize;
	
	/* Check Message Type */
	if ((u8MessageType == DHCP_DISCOVER) || (u8MessageType == DHCP_REQUEST)) {
		/* Base Address and Buffer Size in W5100 device to transmit data */
		switch (u8Socket) {
			case 0: u16TxBaseAddress = W5100_TX_MEMORY_SOCKET_0_ADDRESS; u16TxBufferSize = W5100_TX_SOCKET_0_SIZE_BYTES; break;
			case 1: u16TxBaseAddress = W5100_TX_MEMORY_SOCKET_1_ADDRESS; u16TxBufferSize = W5100_TX_SOCKET_1_SIZE_BYTES; break;
			case 2: u16TxBaseAddress = W5100_TX_MEMORY_SOCKET_2_ADDRESS; u16TxBufferSize = W5100_TX_SOCKET_2_SIZE_BYTES; break;
			case 3: u16TxBaseAddress = W5100_TX_MEMORY_SOCKET_3_ADDRESS; u16TxBufferSize = W5100_TX_SOCKET_3_SIZE_BYTES; break;
			default: break;
		}
	
		/* Destination IP (broadcast) */
		W5100_MemWriteByte(W5100_Sn_DIPR0(u8Socket), 0xFF);
		W5100_MemWriteByte(W5100_Sn_DIPR1(u8Socket), 0xFF);   
		W5100_MemWriteByte(W5100_Sn_DIPR2(u8Socket), 0xFF);
		W5100_MemWriteByte(W5100_Sn_DIPR3(u8Socket), 0xFF);
		
		/* Port */
		W5100_MemWriteByte(W5100_Sn_DPORT0(u8Socket), (uint8_t)(DHCP_SERVER_PORT >> 8));
		W5100_MemWriteByte(W5100_Sn_DPORT1(u8Socket), (uint8_t)(DHCP_SERVER_PORT & 0x00FF));
	
		/* Get socket memory free size */
		u16TxFreeSize = W5100_ReadByte(W5100_Sn_TX_FSR0(u8Socket)) << 8;
		u16TxFreeSize += W5100_ReadByte(W5100_Sn_TX_FSR1(u8Socket));
	
		/* Check free size */
		if (u16TxFreeSize > 400)
		{
			/* Get TX pointer */
			u16TxPointer = W5100_ReadByte(W5100_Sn_TX_WR0(u8Socket)) << 8;
			u16TxPointer += W5100_ReadByte(W5100_Sn_TX_WR1(u8Socket));
		  
			/* Op Code */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), DHCP_BOOTREQUEST);
			u16TxPointer++;
		
			/* Htype */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), DHCP_HTYPE_10MB);
			u16TxPointer++;
      
			/* Hlen */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), DHCP_HLEN_ETHERNET);
			u16TxPointer++;
		
			/* Hops */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), DHCP_HOPS);
			u16TxPointer++;
		
			/* Wid */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_XID & 0xFF000000) >> 24));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_XID & 0x00FF0000) >> 16));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_XID & 0x0000FF00) >> 8));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_XID & 0x000000FF)));
			u16TxPointer++;
		
			/* Secs */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_SECS & 0xFF00) >> 8));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_SECS & 0x00FF)));
			u16TxPointer++;
		
			/* Flags */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_FLAGS & 0xFF00) >> 8));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_FLAGS & 0x00FF)));
			u16TxPointer++;
      
			/* Client IP Address */
			for (u8Index = 0; u8Index < 4; u8Index++) {
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
			
			/* Your IP Address */
			for (u8Index = 0; u8Index < 4; u8Index++) {
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
      
			/* Server IP Address */
			for (u8Index = 0; u8Index < 4; u8Index++)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
      
			/* Gateway IP Address Relay */
			for (u8Index = 0; u8Index < 4; u8Index++) {
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
      
			/* Client Hardware Address */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_0);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_1);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_2);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_3);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_4);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_5);
			u16TxPointer++;				
			
			for (u8Index = 0; u8Index < 10; u8Index++)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
			
			/* Sname */
			for (u8Index = 0; u8Index < 64; u8Index++)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
      
			/* File */
			for (u8Index = 0; u8Index < 128; u8Index++)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x00);
				u16TxPointer++;
			}
      
			/* Option: Magic cookie */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_MAGIC_COOKIE & 0xFF000000) >> 24));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_MAGIC_COOKIE & 0x00FF0000) >> 16));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_MAGIC_COOKIE & 0x0000FF00) >> 8));
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), (uint8_t)((DHCP_MAGIC_COOKIE & 0x000000FF)));
			u16TxPointer++;
		
			/* Option: DHCP Message Type */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpMessageType);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x01);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), u8MessageType);
			u16TxPointer++;
      
			/* Option: Client identifier */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpClientIdentifier);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x07);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x01);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_0);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_1);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_2);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_3);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_4);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), W5100_MAC_ADDRESS_5);
			u16TxPointer++;			
      
			/* Option: Requested IP address */
			if (u8MessageType == DHCP_REQUEST)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpRequestedIPaddr);
				u16TxPointer++;
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x04);
				u16TxPointer++;
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_YourIPAddress[0]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_YourIPAddress[1]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_YourIPAddress[2]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_YourIPAddress[3]);
				u16TxPointer++; 
			}
      
			/* Option: Server identifier */
			if (u8MessageType == DHCP_REQUEST)
			{
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpServerIdentifier);
				u16TxPointer++;
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x04);
				u16TxPointer++;
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_ServerIPAddress[0]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_ServerIPAddress[1]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_ServerIPAddress[2]);
				u16TxPointer++;  
				W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), g_DHCP_ServerIPAddress[3]);
				u16TxPointer++; 
			}

			/* Option: Parameter request list */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpParamRequest);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), 0x05);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), subnetMask);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), routersOnSubnet);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dns);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpT1value);
			u16TxPointer++;
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), dhcpT2value);
			u16TxPointer++;
			
			/* End options */
			W5100_MemWriteByte(u16TxBaseAddress + (u16TxPointer & (u16TxBufferSize - 1)), endOption);
			u16TxPointer++;
			
			/* Write TX Pointer */
			W5100_MemWriteByte(W5100_Sn_TX_WR0(u8Socket), (uint8_t)(u16TxPointer >> 8));
			W5100_MemWriteByte(W5100_Sn_TX_WR1(u8Socket), (uint8_t)(u16TxPointer & 0x00FF));
			
			/* Send data */
			W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_SEND);
			
			/* Wait */
			while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));
			
			/* Result */
			bResult = TRUE;
		}
	}
	
	return bResult;	
}


//---------------------------------------------------------------------------------------
// Name:        DHCP_Parse
// Param:		Socket: socket to use
// Return:      Message type received
//
// Description:	This function is used to parse incoming DHCP messages
//---------------------------------------------------------------------------------------
static uint8_t DHCP_Parse(uint8_t u8Socket) {
	uint16_t u16RxBaseAddress;
	uint16_t u16RxBufferSize;
	uint32_t u32Timeout;
	uint16_t u16RxRecvSize;
	uint16_t u16RxPointer;
	uint16_t u16MemoRxPointer;
	uint8_t u8TempBuffer[6];
	uint8_t u8MessageType = 0;
	uint8_t u8Index;
	uint8_t u8OptionType;
	uint8_t u8OptionLength;
	
	/* Base Address and Buffer Size in W5100 device to transmit data */
	switch (u8Socket) {
		case 0: u16RxBaseAddress = W5100_RX_MEMORY_SOCKET_0_ADDRESS; u16RxBufferSize = W5100_RX_SOCKET_0_SIZE_BYTES; break;
		case 1: u16RxBaseAddress = W5100_RX_MEMORY_SOCKET_1_ADDRESS; u16RxBufferSize = W5100_RX_SOCKET_1_SIZE_BYTES; break;
		case 2: u16RxBaseAddress = W5100_RX_MEMORY_SOCKET_2_ADDRESS; u16RxBufferSize = W5100_RX_SOCKET_2_SIZE_BYTES; break;
		case 3: u16RxBaseAddress = W5100_RX_MEMORY_SOCKET_3_ADDRESS; u16RxBufferSize = W5100_RX_SOCKET_3_SIZE_BYTES; break;
		default: break;
	}
	
	/* Get received size */
	u32Timeout = 1000000;
	do
	{
		u16RxRecvSize = W5100_ReadByte(W5100_Sn_RX_RSR0(u8Socket)) << 8;
		u16RxRecvSize += W5100_ReadByte(W5100_Sn_RX_RSR1(u8Socket));
		u32Timeout--;
	}
	while ((u16RxRecvSize == 0) && (u32Timeout > 0));
	
	if (u16RxRecvSize > 0)
	{
		/* Get RX pointer */
		u16RxPointer = W5100_ReadByte(W5100_Sn_RX_RD0(u8Socket)) << 8;
		u16RxPointer += W5100_ReadByte(W5100_Sn_RX_RD1(u8Socket));
   
		/* Memorize the RX Pointer */
		u16MemoRxPointer = u16RxPointer;
		
		/* Source IP Address of the reply */
		for (u8Index = 0; u8Index < 4; u8Index++)
		{
			u8TempBuffer[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
			u16RxPointer++;
		}
		
		/* If DHCP Server IP is known, check if the message comes from the DHCP Server */
		if ((g_DHCP_ServerIPAddress[0] != 0) || (g_DHCP_ServerIPAddress[1] != 0) ||
			(g_DHCP_ServerIPAddress[2] != 0) || (g_DHCP_ServerIPAddress[3] != 0))
		{
			if ((u8TempBuffer[0] != g_DHCP_ServerIPAddress[0]) || (u8TempBuffer[1] != g_DHCP_ServerIPAddress[1]) ||
				(u8TempBuffer[2] != g_DHCP_ServerIPAddress[2]) || (u8TempBuffer[3] != g_DHCP_ServerIPAddress[3]))
			{
				/* Update RX Pointer */
				u16RxPointer = u16MemoRxPointer + u16RxRecvSize;
				
				/* Save new RX Pointer */
				W5100_MemWriteByte(W5100_Sn_RX_RD0(u8Socket), (uint8_t)(u16RxPointer >> 8));
				W5100_MemWriteByte(W5100_Sn_RX_RD1(u8Socket), (uint8_t)(u16RxPointer & 0x00FF));
				
				/* Send Receive Command */
				W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_RECV);
				
				/* Wait */
				while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));

				return u8MessageType;
			}
		}
		
		/* Skip the rest of the header */
		u16RxPointer += 4;
		
		/* Check Op COde */
		if (W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1))) != DHCP_BOOTREPLY)
		{
			/* Update RX Pointer */
			u16RxPointer = u16MemoRxPointer + u16RxRecvSize;
			
			/* Save new RX Pointer */
			W5100_MemWriteByte(W5100_Sn_RX_RD0(u8Socket), (uint8_t)(u16RxPointer >> 8));
			W5100_MemWriteByte(W5100_Sn_RX_RD1(u8Socket), (uint8_t)(u16RxPointer & 0x00FF));
			
			/* Send Receive Command */
			W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_RECV);
			
			/* Wait */
			while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));

			return u8MessageType;
		}
		
		/* Skip */
		u16RxPointer += 4;
		
		/* Check Xid */
		for (u8Index = 0; u8Index < 4; u8Index++)
		{
			u8TempBuffer[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
			u16RxPointer++;
		}
		
		if ((u8TempBuffer[0] != (uint8_t)((DHCP_XID & 0xFF000000) >> 24)) || (u8TempBuffer[1] != (uint8_t)((DHCP_XID & 0x00FF0000) >> 16)) ||
			(u8TempBuffer[2] != (uint8_t)((DHCP_XID & 0x0000FF00) >> 8)) || (u8TempBuffer[3] != (uint8_t)((DHCP_XID & 0x000000FF))))
		{
			/* Update RX Pointer */
			u16RxPointer = u16MemoRxPointer + u16RxRecvSize;
			
			/* Save new RX Pointer */
			W5100_MemWriteByte(W5100_Sn_RX_RD0(u8Socket), (uint8_t)(u16RxPointer >> 8));
			W5100_MemWriteByte(W5100_Sn_RX_RD1(u8Socket), (uint8_t)(u16RxPointer & 0x00FF));
			
			/* Send Receive Command */
			W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_RECV);
			
			/* Wait */
			while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));

			return u8MessageType;
		}
		
		/* Skip */
		u16RxPointer += 8;
   
		/* Read Yiaddr */
		for (u8Index = 0; u8Index < 4; u8Index++)
		{
			g_DHCP_YourIPAddress[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
			u16RxPointer++;
		}
		
		/* Skip */
		u16RxPointer += 8;
   
		/* Read MAC */
		for (u8Index = 0; u8Index < 6; u8Index++)
		{
			u8TempBuffer[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
			u16RxPointer++;
		}
		
		if ((u8TempBuffer[0] != W5100_MAC_ADDRESS_0) || (u8TempBuffer[1] != W5100_MAC_ADDRESS_1) || (u8TempBuffer[2] != W5100_MAC_ADDRESS_2) ||
			(u8TempBuffer[3] != W5100_MAC_ADDRESS_3) || (u8TempBuffer[4] != W5100_MAC_ADDRESS_4) || (u8TempBuffer[5] != W5100_MAC_ADDRESS_5))
		{
			/* Update RX Pointer */
			u16RxPointer = u16MemoRxPointer + u16RxRecvSize;
			
			/* Save new RX Pointer */
			W5100_MemWriteByte(W5100_Sn_RX_RD0(u8Socket), (uint8_t)(u16RxPointer >> 8));
			W5100_MemWriteByte(W5100_Sn_RX_RD1(u8Socket), (uint8_t)(u16RxPointer & 0x00FF));
			
			/* Send Receive Command */
			W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_RECV);
			
			/* Wait */
			while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));

			return u8MessageType;
		}
   
		/* Skip */
		u16RxPointer += 206;
   
		/* Read options */
		while (u16RxPointer < u16MemoRxPointer + u16RxRecvSize)
		{
			/* Get option type */
			u8OptionType = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
			u16RxPointer++;
		
			switch (u8OptionType)
			{
				case dhcpMessageType:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					u8MessageType = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					break;
					
				case subnetMask:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					for (u8Index = 0; u8Index < 4; u8Index++)
					{
						g_DHCP_SubnetMask[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
						u16RxPointer++;
					}
					break;
					
				 case routersOnSubnet:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					for (u8Index = 0; u8Index < 4; u8Index++)
					{
						g_DHCP_RouterIPAddress[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
						u16RxPointer++;
					}
					break;
					
				 case dns:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					for (u8Index = 0; u8Index < 4; u8Index++)
					{
						g_DHCP_DNSIPAddress[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
						u16RxPointer++;
					}
					break;

				 case dhcpIPaddrLeaseTime:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					g_DHCP_LeaseTime = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1))) << 24;
					u16RxPointer++;
					g_DHCP_LeaseTime += W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1))) << 16;
					u16RxPointer++;
					g_DHCP_LeaseTime += W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1))) << 8;
					u16RxPointer++;
					g_DHCP_LeaseTime += W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					break;
					
				 case dhcpServerIdentifier:
					u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					u16RxPointer++;
					for (u8Index = 0; u8Index < 4; u8Index++)
					{
						g_DHCP_ServerIPAddress[u8Index] = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
						u16RxPointer++;
					}
					break;
					
				 case endOption:
					break;
				 
				 default:
					 u8OptionLength = W5100_ReadByte(u16RxBaseAddress + (u16RxPointer & (u16RxBufferSize - 1)));
					 u16RxPointer++;
					 /* Skip this option */
					 u16RxPointer += u8OptionLength;
				break;
			}
		}
		
		/* Update RX Pointer */
		u16RxPointer = u16MemoRxPointer + u16RxRecvSize;
					
		/* Save new RX Pointer */
		W5100_MemWriteByte(W5100_Sn_RX_RD0(u8Socket), (uint8_t)(u16RxPointer >> 8));
		W5100_MemWriteByte(W5100_Sn_RX_RD1(u8Socket), (uint8_t)(u16RxPointer & 0x00FF));
		
		/* Send Receive Command */
		W5100_MemWriteByte(W5100_Sn_CR(u8Socket), Sn_CR_RECV);
		
		/* Wait */
		while (W5100_ReadByte(W5100_Sn_CR(u8Socket)));
	}
	
	return u8MessageType;
}
#endif /* PL_USE_DHCP */
