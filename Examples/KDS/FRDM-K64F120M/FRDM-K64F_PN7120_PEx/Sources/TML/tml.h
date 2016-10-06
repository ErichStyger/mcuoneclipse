#define TIMEOUT_INFINITE	0
#define TIMEOUT_100MS		100
#define TIMEOUT_1S			1000
#define TIMEOUT_2S			2000

void tml_Connect(void);
void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent);
void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout);
