//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "demo.h"
#include "CLS1.h"
#include "ShellPrintf.h"
#include <stdarg.h>
/* Freescale includes. */
#if 0
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
#endif
//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------
#include "tool.h"
#include "Nfc.h"

#define printf   CLS_printf

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define TASK_NFC_STACK_SIZE		1024
#define TASK_NFC_STACK_PRIO		(configMAX_PRIORITIES - 1)

#define print_buf(x,y,z)  {int loop; printf(x); for(loop=0;loop<z;loop++) printf("0x%.2x ", y[loop]); printf("\n");}

#if defined P2P_SUPPORT || defined RW_SUPPORT
#define NDEF_RECORD_MB_MASK		0x80
#define NDEF_RECORD_ME_MASK		0x40
#define NDEF_RECORD_CF_MASK		0x20
#define NDEF_RECORD_SR_MASK		0x10
#define NDEF_RECORD_IL_MASK		0x08
#define NDEF_RECORD_TNF_MASK	0x07

#define NDEF_EMPTY			0x00
#define NDEF_WELL_KNOWN		0x01
#define NDEF_MEDIA			0x02
#define NDEF_ABSOLUTE_URI	0x03
#define NDEF_EXTERNAL		0x04
#define NDEF_UNKNOWN		0x05
#define NDEF_UNCHANGED		0x06
#define NDEF_RESERVED		0x07

typedef enum {
	WELL_KNOWN_SIMPLE_TEXT,
	WELL_KNOWN_SIMPLE_URI,
	WELL_KNOWN_SMART_POSTER,
	WELL_KNOWN_HANDOVER_SELECT,
	MEDIA_VCARD,
	MEDIA_HANDOVER_WIFI,
	MEDIA_HANDOVER_BT,
	ABSOLUTE_URI,
	UNSUPPORTED_NDEF_RECORD = 0xFF
} NdefRecordType_e;

char * auth(unsigned char x) {
	switch (x) {
	case 0x01:
		return "Open";
	case 0x02:
		return "WPA-Personal";
	case 0x04:
		return "Shared";
	case 0x08:
		return "WPA-Entreprise";
	case 0x10:
		return "WPA2-Entreprise";
	case 0x20:
		return "WPA2-Personal";
	default:
		return "unknown";
	}
}

char * encrypt(unsigned char x) {
	switch (x) {
	case 0x01:
		return "None";
	case 0x02:
		return "WEP";
	case 0x04:
		return "TKIP";
	case 0x08:
		return "AES";
	case 0x10:
		return "AES/TKIP";
	default:
		return "unknown";
	}
}

#define NDEF_PRINT_URI_CODE(x) {    switch(x)									\
									{                                           \
									case 1: printf("http://www."); break;       \
									case 2: printf("https://www."); break;      \
									case 3: printf("http://"); break;           \
									case 4: printf("https://"); break;          \
									case 5: printf("tel:"); break;              \
									case 6: printf("mailto:"); break;           \
									default: break;                             \
									}                                           \
							   }

NdefRecordType_e DetectNdefRecordType(unsigned char *pNdefRecord,
		unsigned short NdefRecordSize) {
	uint8_t typeField;

	/* Short or normal record */
	if (pNdefRecord[0] & NDEF_RECORD_SR_MASK)
		typeField = 3;
	else
		typeField = 6;

	/* Well known Record Type? */
	if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_WELL_KNOWN) {
		if (pNdefRecord[1] == 0x1) {
			switch (pNdefRecord[typeField]) {
			case 'T':
				return WELL_KNOWN_SIMPLE_TEXT;
				break;
			case 'U':
				return WELL_KNOWN_SIMPLE_URI;
				break;
			}
		} else if (pNdefRecord[1] == 0x2) {
			if (memcmp(&pNdefRecord[typeField], "Sp", pNdefRecord[1]) == 0x0) {
				return WELL_KNOWN_SMART_POSTER;
			}
			if (memcmp(&pNdefRecord[typeField], "Hs", pNdefRecord[1]) == 0x0) {
				return WELL_KNOWN_HANDOVER_SELECT;
			}
		}
	}
	/* Media Record Type? */
	else if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_MEDIA) {
		if ((memcmp(&pNdefRecord[typeField], "text/x-vCard", pNdefRecord[1])
				== 0x0)
				|| (memcmp(&pNdefRecord[typeField], "text/vcard",
						pNdefRecord[1]) == 0x0)) {
			return MEDIA_VCARD;
		} else if (memcmp(&pNdefRecord[typeField], "application/vnd.wfa.wsc",
				pNdefRecord[1]) == 0x0) {
			return MEDIA_HANDOVER_WIFI;
		} else if (memcmp(&pNdefRecord[typeField],
				"application/vnd.bluetooth.ep.oob", pNdefRecord[1]) == 0x0) {
			return MEDIA_HANDOVER_WIFI;
		}
	}
	/* Absolute URI Record Type? */
	else if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_ABSOLUTE_URI) {
		return ABSOLUTE_URI;
	}

	return UNSUPPORTED_NDEF_RECORD;
}

void NdefPull_Cb(unsigned char *pNdefRecord, unsigned short NdefRecordSize) {
	NdefRecordType_e NdefRecordType;

	if (pNdefRecord == NULL) {
		printf(
				"--- Issue during NDEF message reception (check provisioned buffer size) \n");
		return;
	}

	printf("--- NDEF message received:\n");

	NdefRecordType = DetectNdefRecordType(pNdefRecord, NdefRecordSize);

	switch (NdefRecordType) {
	case MEDIA_VCARD: {
		char *pString;
		printf("   vCard found:\n");
		/* Short record or normal record */
		if (pNdefRecord[0] & NDEF_RECORD_SR_MASK)
			pString = strstr((char*) &pNdefRecord[3], "BEGIN");
		else
			pString = strstr((char*) &pNdefRecord[6], "BEGIN");
		printf("%s", pString);
	}
		break;

	case WELL_KNOWN_SIMPLE_TEXT: {
		pNdefRecord[7 + pNdefRecord[2]] = '\0';
	//	printf("   Text record (language = %c%c): %s\n", pNdefRecord[5],
	//			pNdefRecord[6], &pNdefRecord[7]);
	}
		break;

	case WELL_KNOWN_SIMPLE_URI: {
		printf("   URI record: ");
		NDEF_PRINT_URI_CODE(pNdefRecord[4])
		pNdefRecord[4 + pNdefRecord[2]] = '\0';
		printf("%s\n", &pNdefRecord[5]);
	}
		break;

	case MEDIA_HANDOVER_WIFI: {
		unsigned char index = 26, i;

		printf("--- Received WIFI credentials:\n");
		if ((pNdefRecord[index] == 0x10) && (pNdefRecord[index + 1] == 0x0e))
			index += 4;
		while (index < NdefRecordSize) {
			if (pNdefRecord[index] == 0x10) {
				if (pNdefRecord[index + 1] == 0x45) {
					printf("- SSID = ");
					for (i = 0; i < pNdefRecord[index + 3]; i++) {
						printf("%c", pNdefRecord[index + 4 + i]);
					}
					printf("\n");
				} else if (pNdefRecord[index + 1] == 0x03) {
					printf("- Authenticate Type = %s\n",
							auth(pNdefRecord[index + 5]));
				} else if (pNdefRecord[index + 1] == 0x0f) {
					printf("- Encryption Type = %s\n",
							encrypt(pNdefRecord[index + 5]));
				} else if (pNdefRecord[index + 1] == 0x27) {
					printf("- Network key = ");
					for (i = 0; i < pNdefRecord[index + 3]; i++) {
						printf("#");
					}
					printf("\n");
				}
				index += 4 + pNdefRecord[index + 3];
			} else
				continue;
		}
	}
		break;

	default:
		printf("   Unsupported NDEF record, cannot parse\n");
		break;
	}
	printf("\n");
}
#endif

#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
const char NDEF_RECORD[] = { 0xD1,   // MB/ME/CF/1/IL/TNF
		0x01,   // TYPE LENGTH
		0x07,   // PAYLOAD LENTGH
		'T',    // TYPE
		0x02,   // Status
		'e', 'n', // Language
		'T', 'e', 's', 't' };

void NdefPush_Cb(unsigned char *pNdefRecord, unsigned short NdefRecordSize) {
	printf("--- NDEF Record sent\n\n");
}
#endif

void MIFARE_scenario(void) {
	bool status;
	unsigned char i;
	unsigned char Resp[256];
	unsigned char RespSize;
	/* Authenticate sector 1 with generic keys */
	unsigned char Auth[] = { 0x40, 0x01, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF };
	/* Read block 4 */
	unsigned char Read[] = { 0x10, 0x30, 0x04 };
	/* Write block 4 */
	unsigned char WritePart1[] = { 0x10, 0xA0, 0x04 };
	unsigned char WritePart2[] = { 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
			0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

	/* Authenticate */
	status = NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize);
	if ((status == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		printf(" Authenticate sector %d failed with error 0x%02x\n", Auth[1],
				Resp[RespSize - 1]);
		return;
	}
	printf(" Authenticate sector %d succeed\n", Auth[1]);

	/* Read block */
	status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
	if ((status == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		printf(" Read block %d failed with error 0x%02x\n", Read[2],
				Resp[RespSize - 1]);
		return;
	}
	printf(" Read block %d: ", Read[2]);
	for (i = 0; i < RespSize - 2; i++) {
		printf("0x%02X ", Resp[i + 1]);
	}
	printf("\n");

	/* Write block */
	status = NxpNci_ReaderTagCmd(WritePart1, sizeof(WritePart1), Resp,
			&RespSize);
	if ((status == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		printf(" Write block %d failed with error 0x%02x\n", WritePart1[2],
				Resp[RespSize - 1]);
		return;
	}
	status = NxpNci_ReaderTagCmd(WritePart2, sizeof(WritePart2), Resp,
			&RespSize);
	if ((status == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		printf(" Write block %d failed with error 0x%02x\n", WritePart1[2],
				Resp[RespSize - 1]);
		return;
	}
	printf(" Block %d written\n", WritePart1[2]);

	/* Read block */
	status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
	if ((status == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		printf(" Read failed with error 0x%02x\n", Resp[RespSize - 1]);
		return;
	}
	printf(" Read block %d: ", Read[2]);
	for (i = 0; i < RespSize - 2; i++) {
		printf("0x%02X ", Resp[i + 1]);
	}
	printf("\n");

	/* Perform presence check */
	while (1) {
		Sleep(500);
		status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
		if ((status == NFC_ERROR) || (Resp[RespSize - 1] == 0xb2))
			break;
	}
}

void ISO15693_scenario (void)
{
	bool status;
	unsigned char Resp[256];
	unsigned char RespSize;
	unsigned char Inventory[] = {0x26, 0x01, 0x00};

	/* Perform presence check */
	while (1)
	{
		Sleep(500);
		status = NxpNci_ReaderTagCmd(Inventory, sizeof(Inventory), Resp, &RespSize);
		if((status == NFC_ERROR) || (Resp[RespSize-1] == 0xb2)) break;
	}
}

void displayCardInfo(NxpNci_RfIntf_t RfIntf)
{
	switch(RfIntf.ModeTech)
	{
		case (MODE_POLL | TECH_PASSIVE_NFCA):
			printf("\tSENS_RES = 0x%.2x 0x%.2x\n", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
			//print_buf("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
			if(RfIntf.Info.NFC_APP.SelResLen != 0) printf("\tSEL_RES = 0x%.2x\n", RfIntf.Info.NFC_APP.SelRes[0]);
		break;

		case (MODE_POLL | TECH_PASSIVE_NFCB):
			//if(RfIntf.Info.NFC_BPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_BPP.SensRes, RfIntf.Info.NFC_BPP.SensResLen);
		break;

		case (MODE_POLL | TECH_PASSIVE_NFCF):
			printf("\tBitrate = %s\n", (RfIntf.Info.NFC_FPP.BitRate==1)?"212":"424");
			if(RfIntf.Info.NFC_FPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_FPP.SensRes, RfIntf.Info.NFC_FPP.SensResLen);
		break;

		case (MODE_POLL | TECH_PASSIVE_15693):
			print_buf("\tID = ", RfIntf.Info.NFC_VPP.ID, sizeof(RfIntf.Info.NFC_VPP.ID));
			printf("\tAFI = 0x%.2x\n", RfIntf.Info.NFC_VPP.AFI);
			printf("\tDSFID = 0x%.2x\n", RfIntf.Info.NFC_VPP.DSFID);
		break;

		default:
		break;
	}
}

void task_nfc_loop(void)
{
	NxpNci_RfIntf_t RfInterface;
	unsigned char mode = 0;
	unsigned char DiscoveryTechnologies[] = {
#if defined P2P_SUPPORT || defined RW_SUPPORT
			MODE_POLL | TECH_PASSIVE_NFCA,
			MODE_POLL | TECH_PASSIVE_NFCF,
#endif
#ifdef RW_SUPPORT
			MODE_POLL | TECH_PASSIVE_NFCB,
			MODE_POLL | TECH_PASSIVE_15693,
#endif
#ifdef P2P_SUPPORT
			MODE_POLL | TECH_ACTIVE_NFCF,
#endif
#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
			MODE_LISTEN | TECH_PASSIVE_NFCA,
#endif
#if defined CARDEMU_SUPPORT
			MODE_LISTEN | TECH_PASSIVE_NFCB,
#endif
#ifdef P2P_SUPPORT
			MODE_LISTEN | TECH_PASSIVE_NFCF,
			MODE_LISTEN | TECH_ACTIVE_NFCA,
			MODE_LISTEN | TECH_ACTIVE_NFCF,
#endif
			};

	/* Open connection to NXPNCI device */
	if (NxpNci_Connect() == NFC_ERROR) {
		printf("Error: cannot connect to NXPNCI device\n");
		return;
	}

	if (NxpNci_ConfigureSettings() == NFC_ERROR) {
		printf("Error: cannot configure NXPNCI settings\n");
		return;
	}

	/* Set NXPNCI in all modes */
	#ifdef CARDEMU_SUPPORT
	mode |= NXPNCI_MODE_CARDEMU;
	#endif
	#ifdef P2P_SUPPORT
	mode |= NXPNCI_MODE_P2P;
	#endif
	#ifdef RW_SUPPORT
	mode |= NXPNCI_MODE_RW;
	#endif

	if (NxpNci_ConfigureMode(mode) == NFC_ERROR)
	{
		printf("Error: cannot configure NXPNCI\n");
		return;
	}

	/* Start Discovery */
	if (NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies)) != NFC_SUCCESS)
	{
		printf("Error: cannot start discovery\n");
		return;
	}

	while(1)
	{
		printf("\nWAITING FOR DEVICE DISCOVERY\n");

		/* Wait until a peer is discovered */
		NxpNci_WaitForDiscoveryNotification(&RfInterface);

	#ifdef CARDEMU_SUPPORT
		/* Is activated from remote T4T ? */
		if ((RfInterface.Interface == INTF_ISODEP) && ((RfInterface.ModeTech & MODE_MASK) == MODE_LISTEN))
		{
			printf(" - LISTEN MODE: Activated from remote Reader\n");
			NxpNci_ProcessCardMode(RfInterface);
			printf("READER DISCONNECTED\n");
		}
		else
	#endif

	#ifdef P2P_SUPPORT
		/* Is activated from remote T4T ? */
		if (RfInterface.Interface == INTF_NFCDEP)
		{
			if ((RfInterface.ModeTech & MODE_LISTEN) == MODE_LISTEN) printf(" - P2P TARGET MODE: Activated from remote Initiator\n");
			else printf(" - P2P INITIATOR MODE: Remote Target activated\n");

			/* Process with SNEP for NDEF exchange */
			NxpNci_ProcessP2pMode(RfInterface);

			printf("PEER LOST\n");
		}
		else
	#endif
	#ifdef RW_SUPPORT
		if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL)
		{
			/* Is card detected MIFARE ?*/
			if(RfInterface.Protocol == PROT_MIFARE)
			{
				printf(" - POLL MODE: Remote MIFARE card activated\n");
				displayCardInfo(RfInterface);

				/* Run dedicated scenario to demonstrate MIFARE card management */
				MIFARE_scenario();

				/* Restart discovery loop */
				NxpNci_RestartDiscovery();
			}
			/* Is card detected ISO15693 ?*/
			else if (RfInterface.ModeTech == TECH_PASSIVE_15693)
			{
				printf(" - POLL MODE: Remote ISO15693 card activated\n");
				displayCardInfo(RfInterface);

				/* Run dedicated scenario to demonstrate ISO15693 card management */
				ISO15693_scenario();

				/* Restart discovery loop */
				NxpNci_RestartDiscovery();
			}
			/* Is known target ?*/
			else if ((RfInterface.Protocol != PROT_NFCDEP) && (RfInterface.Interface != INTF_UNDETERMINED))
			{
				printf(" - POLL MODE: Remote T%dT activated\n", RfInterface.Protocol);
				displayCardInfo(RfInterface);

				/* Process NDEF message read */
				NxpNci_ProcessReaderMode(RfInterface, READ_NDEF);

#ifdef NDEF_WRITING
				RW_NDEF_SetMessage ((unsigned char *) NDEF_RECORD, sizeof(NDEF_RECORD), *NdefPush_Cb);
				/* Process NDEF message read */
				NxpNci_ProcessReaderMode(RfInterface, WRITE_NDEF);
#endif
				/* Process card Presence check */
				NxpNci_ProcessReaderMode(RfInterface, PRESENCE_CHECK);

				printf("CARD REMOVED\n");

				/* Restart the discovery loop */
				NxpNci_RestartDiscovery();
			}
			else
			{
				printf(" - POLL MODE: Undetermined target\n");
				/* Restart discovery loop */
				NxpNci_StopDiscovery();
				NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
			}
		}
		else
	#endif
		{
			printf("WRONG DISCOVERY\n");
		}
	}
}

static void task_nfc(void *params) {
  task_nfc_loop(); /* shall not return */
  for(;;) {}
}

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------
int demo_run(void) {
#if 0
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
#endif
	printf("\nRunning the NXP-NCI project.\n");

	/* Create NFC task */
    if (xTaskCreate((TaskFunction_t) task_nfc,
    				(const char*) "NFC_task",
					TASK_NFC_STACK_SIZE,
					NULL,
					TASK_NFC_STACK_PRIO,
					NULL) != pdPASS)
    {
        printf("Failed to create NFC task");
    }
	/* Register for NFC functionalities */
#ifdef CARDEMU_SUPPORT
	/* Register NDEF message to be sent to remote reader */
	T4T_NDEF_EMU_SetMessage((unsigned char *) NDEF_RECORD, sizeof(NDEF_RECORD),
			*NdefPush_Cb);
#endif

#ifdef P2P_SUPPORT
	/* Register NDEF message to be sent to remote peer */
	P2P_NDEF_SetMessage((unsigned char *) NDEF_RECORD, sizeof(NDEF_RECORD),
			*NdefPush_Cb);

	/* Register callback for reception of NDEF message from remote peer */
	P2P_NDEF_RegisterPullCallback(*NdefPull_Cb);
#endif

#ifdef RW_SUPPORT
	/* Register callback for reception of NDEF message from remote cards */
	RW_NDEF_RegisterPullCallback(*NdefPull_Cb);
#endif

    vTaskStartScheduler();
    while(1);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
