#define P2P_NDEF_MAX_NDEF_MESSAGE_SIZE 240

void P2P_NDEF_Reset(void);
void P2P_NDEF_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
