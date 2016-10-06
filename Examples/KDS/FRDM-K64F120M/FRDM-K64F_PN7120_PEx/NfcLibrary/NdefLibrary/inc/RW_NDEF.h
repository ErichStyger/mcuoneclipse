#define RW_MAX_NDEF_FILE_SIZE 500

extern unsigned char NdefBuffer[RW_MAX_NDEF_FILE_SIZE];

typedef void RW_NDEF_Callback_t (unsigned char*, unsigned short);

#define RW_NDEF_TYPE_T1T	0x1
#define RW_NDEF_TYPE_T2T	0x2
#define RW_NDEF_TYPE_T3T	0x3
#define RW_NDEF_TYPE_T4T	0x4

extern unsigned char *pNdefMessage;
extern unsigned short NdefMessage_size;

extern RW_NDEF_Callback_t *pRW_NDEF_PullCb;
extern RW_NDEF_Callback_t *pRW_NDEF_PushCb;

void RW_NDEF_Reset(unsigned char type);
void RW_NDEF_Read_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
void RW_NDEF_Write_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
