#ifdef RW_SUPPORT
#include <tool.h>
#include <RW_NDEF.h>

const unsigned char RW_NDEF_T4T_APP_Select[] = {0x00,0xA4,0x04,0x00,0x07,0xD2,0x76,0x00,0x00,0x85,0x01,0x01};
const unsigned char RW_NDEF_T4T_CC_Select[] = {0x00,0xA4,0x00,0x0C,0x02,0xE1,0x03};
const unsigned char RW_NDEF_T4T_NDEF_Select[] = {0x00,0xA4,0x00,0x0C,0x02,0xE1,0x04};
const unsigned char RW_NDEF_T4T_Read[] = {0x00,0xB0,0x00,0x00,0x0F};

const unsigned char RW_NDEF_T4T_OK[] = {0x90, 0x00};

typedef enum
{
	Initial,
    Selecting_NDEF_Application20,
    Selecting_NDEF_Application10,
    Selecting_CC,
	Reading_CC,
    Selecting_NDEF,
	Reading_NDEF_Size,
	Reading_NDEF
} RW_NDEF_T4T_state_t;

typedef struct
{
	unsigned char MappingVersion;
	unsigned short MLe;
	unsigned short MLc;
	unsigned char FileID[2];
	unsigned short MaxNdefFileSize;
	unsigned char RdAccess;
	unsigned char WrAccess;
	unsigned short MessagePtr;
	unsigned short MessageSize;
	unsigned char *pMessage;
} RW_NDEF_T4T_Ndef_t;

static RW_NDEF_T4T_state_t eRW_NDEF_T4T_State = Initial;
static RW_NDEF_T4T_Ndef_t RW_NDEF_T4T_Ndef;

void RW_NDEF_T4T_Reset(void)
{
	eRW_NDEF_T4T_State = Initial;
	RW_NDEF_T4T_Ndef.pMessage = NdefBuffer;
}

void RW_NDEF_T4T_Read_Next(unsigned char *pRsp, unsigned short Rsp_size, unsigned char *pCmd, unsigned short *pCmd_size)
{
	/* By default no further command to be sent */
	*pCmd_size = 0;

	switch(eRW_NDEF_T4T_State)
	{
	case Initial:
		/* Select NDEF Application in version 2.0 */
		memcpy(pCmd, RW_NDEF_T4T_APP_Select, sizeof(RW_NDEF_T4T_APP_Select));
		*pCmd_size = sizeof(RW_NDEF_T4T_APP_Select);
		eRW_NDEF_T4T_State = Selecting_NDEF_Application20;
		break;

	case Selecting_NDEF_Application20:
		/* Is NDEF Application Selected ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			/* Select CC */
			memcpy(pCmd, RW_NDEF_T4T_CC_Select, sizeof(RW_NDEF_T4T_CC_Select));
			*pCmd_size = sizeof(RW_NDEF_T4T_CC_Select);
			eRW_NDEF_T4T_State = Selecting_CC;
		}
		else
		{
			/* Select NDEF Application in version 1.0 */
			memcpy(pCmd, RW_NDEF_T4T_APP_Select, sizeof(RW_NDEF_T4T_APP_Select));
			pCmd[11] = 0x0;
			*pCmd_size = sizeof(RW_NDEF_T4T_APP_Select);
			eRW_NDEF_T4T_State = Selecting_NDEF_Application10;
		}
		break;

	case Selecting_NDEF_Application10:
		/* Is NDEF Application Selected ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			/* Select CC */
			memcpy(pCmd, RW_NDEF_T4T_CC_Select, sizeof(RW_NDEF_T4T_CC_Select));
			pCmd[3] = 0x00;
			*pCmd_size = sizeof(RW_NDEF_T4T_CC_Select);
			eRW_NDEF_T4T_State = Selecting_CC;
		}
		break;

	case Selecting_CC:
		/* Is CC Selected ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			/* Read CC */
			memcpy(pCmd, RW_NDEF_T4T_Read, sizeof(RW_NDEF_T4T_Read));
			*pCmd_size = sizeof(RW_NDEF_T4T_Read);
			eRW_NDEF_T4T_State = Reading_CC;
		}
		break;

	case Reading_CC:
		/* Is CC Read ?*/
		if ((!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK))) && (Rsp_size == 15 + 2))
		{
			/* Fill CC structure */
			RW_NDEF_T4T_Ndef.MappingVersion = pRsp[2];
			RW_NDEF_T4T_Ndef.MLe = (pRsp[3] << 8) + pRsp[4];
			RW_NDEF_T4T_Ndef.MLc = (pRsp[5] << 8) + pRsp[6];
			RW_NDEF_T4T_Ndef.FileID[0] = pRsp[9];
			RW_NDEF_T4T_Ndef.FileID[1] = pRsp[10];
			RW_NDEF_T4T_Ndef.MaxNdefFileSize = (pRsp[11] << 8) + pRsp[12];
			RW_NDEF_T4T_Ndef.RdAccess = pRsp[13];
			RW_NDEF_T4T_Ndef.WrAccess = pRsp[14];
			
			/* Select NDEF */
			memcpy(pCmd, RW_NDEF_T4T_NDEF_Select, sizeof(RW_NDEF_T4T_NDEF_Select));
			if (RW_NDEF_T4T_Ndef.MappingVersion == 0x10) pCmd[3] = 0x00;
			pCmd[5] = RW_NDEF_T4T_Ndef.FileID[0];
			pCmd[6] = RW_NDEF_T4T_Ndef.FileID[1];
			*pCmd_size = sizeof(RW_NDEF_T4T_NDEF_Select);
			eRW_NDEF_T4T_State = Selecting_NDEF;
		}
		break;

	case Selecting_NDEF:
		/* Is NDEF Selected ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			/* Get NDEF file size */
			memcpy(pCmd, RW_NDEF_T4T_Read, sizeof(RW_NDEF_T4T_Read));
			*pCmd_size = sizeof(RW_NDEF_T4T_Read);
			pCmd[4] = 2;
			eRW_NDEF_T4T_State = Reading_NDEF_Size;
		}
		break;

	case Reading_NDEF_Size:
		/* Is Read Success ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			RW_NDEF_T4T_Ndef.MessageSize = (pRsp[0] << 8) + pRsp[1];

			/* If provisioned buffer is not large enough, notify the application and stop reading */
			if (RW_NDEF_T4T_Ndef.MessageSize > RW_MAX_NDEF_FILE_SIZE)
			{
				if(pRW_NDEF_PullCb != NULL) pRW_NDEF_PullCb(NULL, 0);
				break;
			}

			RW_NDEF_T4T_Ndef.MessagePtr = 0;

			/* Read NDEF data */
			memcpy(pCmd, RW_NDEF_T4T_Read, sizeof(RW_NDEF_T4T_Read));
			pCmd[3] =  2;
			pCmd[4] = (RW_NDEF_T4T_Ndef.MessageSize > RW_NDEF_T4T_Ndef.MLe-1) ? RW_NDEF_T4T_Ndef.MLe-1 : (unsigned char) RW_NDEF_T4T_Ndef.MessageSize;
			*pCmd_size = sizeof(RW_NDEF_T4T_Read);
			eRW_NDEF_T4T_State = Reading_NDEF;
		}
		break;

	case Reading_NDEF:
		/* Is Read Success ?*/
		if (!memcmp(&pRsp[Rsp_size - 2], RW_NDEF_T4T_OK, sizeof(RW_NDEF_T4T_OK)))
		{
			memcpy(&RW_NDEF_T4T_Ndef.pMessage[RW_NDEF_T4T_Ndef.MessagePtr], pRsp, Rsp_size - 2);
			RW_NDEF_T4T_Ndef.MessagePtr += Rsp_size - 2;
			
			/* Is NDEF message read completed ?*/
			if (RW_NDEF_T4T_Ndef.MessagePtr == RW_NDEF_T4T_Ndef.MessageSize)
			{
				/* Notify application of the NDEF reception */
				if(pRW_NDEF_PullCb != NULL) pRW_NDEF_PullCb(RW_NDEF_T4T_Ndef.pMessage, RW_NDEF_T4T_Ndef.MessageSize);
			}
			else
			{
				/* Read NDEF data */
				memcpy(pCmd, RW_NDEF_T4T_Read, sizeof(RW_NDEF_T4T_Read));
				pCmd[3] =  RW_NDEF_T4T_Ndef.MessagePtr + 2;
				pCmd[4] = ((RW_NDEF_T4T_Ndef.MessageSize - RW_NDEF_T4T_Ndef.MessagePtr) > RW_NDEF_T4T_Ndef.MLe-1) ? RW_NDEF_T4T_Ndef.MLe-1 : (unsigned char) (RW_NDEF_T4T_Ndef.MessageSize - RW_NDEF_T4T_Ndef.MessagePtr);
				*pCmd_size = sizeof(RW_NDEF_T4T_Read);
			}
		}
		break;

	default:
		break;
	}
}
#endif
