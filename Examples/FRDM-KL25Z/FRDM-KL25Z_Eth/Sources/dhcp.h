/**
 * \file
 * \brief This is the interface for DHCP
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This implements the DHCP part for the W5100.
 */

#ifndef	DHCP_H_
#define	DHCP_H_

#include "Platform.h"
#if PL_USE_DHCP

#include "PE_Types.h"

/* Socket used in W5100 device */
#define DHCP_SOCKET							(0)

/* DHCP Port */
#define	DHCP_SERVER_PORT					(67)
#define DHCP_CLIENT_PORT					(68)

/* Op Codes */
#define DHCP_BOOTREQUEST	   				(1)
#define DHCP_BOOTREPLY		   				(2)

/* Messages */
#define DHCP_DISCOVER		   				(1)
#define DHCP_OFFER		      				(2)
#define DHCP_REQUEST	   	   				(3)
#define DHCP_DECLINE		     			(4)
#define DHCP_ACK		         			(5)
#define DHCP_NAK		         			(6)
#define DHCP_RELEASE		      			(7)
#define DHCP_INFORM		      				(8)
#define DHCP_RENEW            				(10)
#define DHCP_REREQUEST        				(11)

/* Hardware address type */
#define DHCP_HTYPE_10MB		   				(1)
#define DHCP_HTYPE_100MB	   				(2)

/* Hardware length */
#define DHCP_HLEN_ETHERNET	   				(6)

/* Hops */
#define DHCP_HOPS		         			(0x00)

/* Xid */
#define DHCP_XID              				(0x4DA59D26)

/* Secs */
#define DHCP_SECS		         			(0x0000)

/* Flags */
#define DHCP_FLAGS		      				(0x8000)

/* Magic cookie */
#define DHCP_MAGIC_COOKIE     				(0x63825363)

/* DHCP options */
typedef enum
{
	padOption		         				= 0,
	subnetMask	      	   					= 1,
	timerOffset		         				= 2,
	routersOnSubnet		  	 				= 3,
	timeServer		         				= 4,
	nameServer		        		 		= 5,
	dns		      	      					= 6,
	logServer	      	   					= 7,
	cookieServer		      				= 8,
	lprServer		        	 			= 9,
	impressServer		      				= 10,
	resourceLocationServer					= 11,
	hostName		            			= 12,
	bootFileSize		      				= 13,
	meritDumpFile		      				= 14,
	domainName		         				= 15,
	swapServer		         				= 16,
	rootPath		            			= 17,
	extentionsPath	      					= 18,
	IPforwarding	      					= 19,
	nonLocalSourceRouting					= 20,
	policyFilter	      					= 21,
	maxDgramReasmSize    					= 22,
	defaultIPTTL	      					= 23,
	pathMTUagingTimeout  					= 24,
	pathMTUplateauTable	   					= 25,
	ifMTU			            			= 26,
	allSubnetsLocal	   						= 27,
	broadcastAddr	      					= 28,
	performMaskDiscovery	   				= 29,
	maskSupplier		      				= 30,
	performRouterDiscovery					= 31,
	routerSolicitationAddr					= 32,
	staticRoute		         				= 33,
	trailerEncapsulation	   				= 34,
	arpCacheTimeout		   					= 35,
	ethernetEncapsulation					= 36,
	tcpDefaultTTL	      					= 37,
	tcpKeepaliveInterval	   				= 38,
	tcpKeepaliveGarbage  					= 39,
	nisDomainName		      				= 40,
	nisServers		         				= 41,
	ntpServers		         				= 42,
	vendorSpecificInfo	   					= 43,
	netBIOSnameServer	      				= 44,
	netBIOSdgramDistServer					= 45,
	netBIOSnodeType		   					= 46,
	netBIOSscope		      				= 47,
	xFontServer		         				= 48,
	xDisplayManager	   						= 49,
	dhcpRequestedIPaddr	   					= 50,
	dhcpIPaddrLeaseTime	   					= 51,
	dhcpOptionOverload	   					= 52,
	dhcpMessageType		   					= 53,
	dhcpServerIdentifier 					= 54,
	dhcpParamRequest	      				= 55,
	dhcpMsg			         				= 56,
	dhcpMaxMsgSize		      				= 57,
	dhcpT1value		         				= 58,
	dhcpT2value		         				= 59,
	dhcpClassIdentifier	   					= 60,
	dhcpClientIdentifier	   				= 61,
	endOption		         				= 255
} t_DHCPOption;

bool DHCP_GetIPAddress(void);
static bool DHCP_SendMessage(uint8_t u8Socket, uint8_t u8MessageType);
static uint8_t DHCP_Parse(uint8_t u8Socket);
#endif /* PL_USE_DHCP */

#endif
