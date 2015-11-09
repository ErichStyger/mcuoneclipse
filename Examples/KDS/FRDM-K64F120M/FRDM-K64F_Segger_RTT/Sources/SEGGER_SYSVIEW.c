/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2015  SEGGER Microcontroller GmbH & Co. KG               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* * This software may in its unmodified form be freely redistributed *
*   in source form.                                                  *
* * The source code may be modified, provided the source code        *
*   retains the above copyright notice, this list of conditions and  *
*   the following disclaimer.                                        *
* * Modified versions of this software in source or linkable form    *
*   may not be distributed without prior consent of SEGGER.          *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.10                                    *
*                                                                    *
**********************************************************************
--------  END-OF-HEADER  ---------------------------------------------

File        : SEGGER_SYSVIEW.c
Purpose     : System visualization API implementation.

Additional information:
  Packet format:
    Packets with IDs 0..23 are standard packets with known structure.
    For efficiency, they do *NOT* contain a length field.
    <ID><Data><TimeStampDelta>

    Packets with IDs 24..31 are standard packets with extendible
    structure and contain a length field.
    <ID><Lenght><Data><TimeStampDelta>

    Packets with IDs >= 32 always contain a length field.
    <ID><Length><Data><TimeStampDelta>

  Packet IDs:
       0..  31 : Standard packets, known by SysViewer.
      32..1023 : OS-definable packets, described in a SystemView description file.
    1024..2047 : User-definable packets, described in a SystemView description file.
    2048..32767: Undefined.

  Data encoding:
    Basic types (int, short, char, ...):
      Basic types are encoded little endian with most-significant bit variant
      encoding.
      Each encoded byte contains 7 data bits [6:0] and the MSB continuation bit.
      The continuation bit indicates whether the next byte belongs to the data
      (bit set) or this is the last byte (bit clear).
      The most significant bits of data are encoded first, proceeding to the
      least significant bits in the final byte (little endian).

      Example encoding:
        Data: 0x1F4 (500)
        Encoded: 0xF4 (First 7 data bits 74 | Continuation bit)
                 0x03 (Second 7 data bits 03, no continuation)

        Data: 0xFFFFFFFF
        Encoded: 0xFF 0xFF 0xFF 0xFF 0x0F

        Data: 0xA2 (162),   0x03 (3), 0x7000
        Encoded: 0xA2 0x01  0x03      0x80 0xE0 0x01

    Byte arrays and strings:
      Byte arrays and strings are encoded as <NumBytes> followed by the raw data.
      NumBytes is encoded as a basic type with a theoretical maximum of 4G.

      Example encoding:
        Data: "Hello World\0" (0x48 0x65 0x6C 0x6C 0x6F 0x20 0x57 0x6F 0x72 0x6C 0x64 0x00)
        Encoded: 0x0B 0x48 0x65 0x6C 0x6C 0x6F 0x20 0x57 0x6F 0x72 0x6C 0x64

  Examples packets:
  01 F4 03 80 80 10 // Overflow packet. Data is a single U32.
                       This packet means: 500 packets lost, Timestamp is 0x40000

  02 0F 50          // ISR(15) Enter. Timestamp 80 (0x50)

  03 20             // ISR Exit. Timestamp 32 (0x20) (Shortest possible packet.)

  Sample code for user defined Packets:
    #define MY_ID   0x400                // Any value between 0x400 and 0x7FF
    void SendMyPacket(unsigned Para0, unsigned Para1, const char* s) {
      U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 2 * SEGGER_SYSVIEW_QUANTA_U32 + MAX_STR_LEN + 1];
      U8* pPayload;
      //
      pPayload = SEGGER_SYSVIEW_PPREPARE_PACKET(aPacket);               // Prepare the packet for SystemView
      pPayload = SEGGER_SYSVIEW_EncodeU32(pPayload, Para0);             // Add the first parameter to the packet
      pPayload = SEGGER_SYSVIEW_EncodeU32(pPayload, Para1);             // Add the second parameter to the packet
      pPayload = SEGGER_SYSVIEW_EncodeString(pPayload, s, MAX_STR_LEN); // Add the string to the packet
      //
      SEGGER_SYSVIEW_SendPacket(&aPacket[0], pPayload, MY_ID);          // Send the packet with EventId = MY_ID
    }

    #define MY_ID_1 0x401
    void SendOnePara(unsigned Para0) {
      SEGGER_SYSVIEW_RecordU32(MY_ID_1, Para0);
    }

*/

/*********************************************************************
*
*       #include section
*
**********************************************************************
*/

#include "SEGGER_SYSVIEW_Int.h"
#include "SEGGER_RTT.h"
#include <string.h>

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/
#if SEGGER_SYSVIEW_ID_SHIFT
  #define SHRINK_ID(Id)   (((Id) - _SYSVIEW_Globals.RAMBaseAddress) >> SEGGER_SYSVIEW_ID_SHIFT)
#else
  #define SHRINK_ID(Id)   ((Id) - _SYSVIEW_Globals.RAMBaseAddress)
#endif

#if SEGGER_SYSVIEW_RTT_CHANNEL > 0
  #define CHANNEL_ID_UP   SEGGER_SYSVIEW_RTT_CHANNEL
  #define CHANNEL_ID_DOWN SEGGER_SYSVIEW_RTT_CHANNEL
#else
  #define CHANNEL_ID_UP   _SYSVIEW_Globals.UpChannel
  #define CHANNEL_ID_DOWN _SYSVIEW_Globals.DownChannel
#endif

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
// Timestamps may be less than full 32-bits, in which case we need to zero
// the unused bits to properly handle overflows.
// Note that this is a quite common scenario, as a 32-bit time such as
// SysTick might be scaled down to reduce bandwith
// or a 16-bit hardware time might be used.
#if SEGGER_SYSVIEW_TIMESTAMP_BITS < 32  // Eliminate unused bits in case hardware timestamps are less than 32 bits
  #define MAKE_DELTA_32BIT(Delta) Delta <<= 32 - SEGGER_SYSVIEW_TIMESTAMP_BITS; \
                                  Delta >>= 32 - SEGGER_SYSVIEW_TIMESTAMP_BITS;
#else
  #define MAKE_DELTA_32BIT(Delta)
#endif


/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/
#define ENABLE_STATE_OFF        0
#define ENABLE_STATE_ON         1
#define ENABLE_STATE_DROPPING   2

/*********************************************************************
*
*       Static constant data
*
**********************************************************************
*/
//
// 10 Zero bytes are used as synchronization mark periodically
//
static const U8 _abSync[10] = { SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP,
                                SEGGER_SYSVIEW_EVENT_ID_NOP};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static struct {
        U8                      EnableState;   // 0: Disabled, 1: Enabled, 2: Dropping
        U8                      UpChannel;
        U8                      DownChannel;
        U8                      RecursionCnt;
        U32                     SysFreq;
        U32                     CPUFreq;
        U32                     DropCount;
        U32                     LastTxTimeStamp;
        U32                     RAMBaseAddress;
        char                    DownBuffer[8];  // Small, fixed-size buffer, for back-channel comms
        char                    UpBuffer  [SEGGER_SYSVIEW_RTT_BUFFER_SIZE];
  const SEGGER_SYSVIEW_OS_API*  pOSAPI;
        SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC*   pfSendSysDesc;
} _SYSVIEW_Globals;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

#define ENCODE_U32(pDest, Value) {                                \
                                   U8* p;                         \
                                   U32 Data;                      \
                                   p = pDest;                     \
                                   Data = Value;                  \
                                   while(Data > 0x7F) {           \
                                     *p++ = (U8)(Data | 0x80);    \
                                     Data >>= 7;                  \
                                   };                             \
                                   *p++ = (U8)Data;               \
                                   pDest = p;                     \
                                 };

/*********************************************************************
*
*       _EncodeData()
*
*  Function description
*    Encode a byte buffer in variable-length format.
*
*  Parameters
*    pPayload - Pointer to where string will be encoded.
*    pSrc     - Pointer to data buffer to be encoded.
*    NumBytes - Number of bytes in the buffer to be encoded.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*
*  Additional information
*    The data is encoded as a count byte followed by the contents
*    of the data buffer.
*    Make sure NumBytes + 1 bytes are free for the payload.
*/
static U8* _EncodeData(U8* pPayload, const char* pSrc, unsigned NumBytes) {
  unsigned n;
  //
  n = 0;
  *pPayload++ = NumBytes;
  while (n < NumBytes) {
    *pPayload++ = *pSrc++;
    n++;
  }
  return pPayload;
}

/*********************************************************************
*
*       _EncodeStr()
*
*  Function description
*    Encode a string in variable-length format.
*
*  Parameters
*    pPayload - Pointer to where string will be encoded.
*    pText    - String to encode.
*    Limit    - Maximum number of characters to encode from string.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*
*  Additional information
*    The string is encoded as a count byte followed by the contents
*    of the string.
*    No more than 1 + Limit bytes will be encoded to the payload.
*/
static U8 *_EncodeStr(U8 *pPayload, const char *pText, unsigned Limit) {
  unsigned n;
  //
  for (n = 0; n < Limit && *pText; ++n) {
    pPayload[1+n] = *pText++;
  }
  pPayload[0] = n;
  return pPayload + n + 1;
}

/*********************************************************************
*
*       _PreparePacket()
*
*  Function description
*    Prepare a SystemView event packet header.
*
*  Parameters
*    pPacket - Pointer to start of packet to initialize.
*
*  Return value
*    Pointer to first byte of packet payload.
*
*  Additional information
*    The payload length and evnetId are not initialized.
*    PreparePacket only reserves space for them and they are
*    computed and filled in by the sending function.
*/
static U8* _PreparePacket(U8* pPacket) {
  return pPacket + 4;
}

/*********************************************************************
*
*       _HandleIncomingPacket()
*
*  Function description
*    Read an incoming command from the down channel and process it.
*
*  Additional information
*    This function is called each time after sending a packet.
*    Processing incoming packets is done asynchronous. SystemView might
*    already have sent event packets after the host has sent a command.
*/
static void _HandleIncomingPacket(void) {
  U8  Cmd;
  int Status;
  //
  Status = SEGGER_RTT_ReadNoLock(CHANNEL_ID_DOWN, &Cmd, 1);
  if (Status > 0) {
    switch (Cmd) {
    case SEGGER_SYSVIEW_COMMAND_ID_START:
      SEGGER_SYSVIEW_Start();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_STOP:
      SEGGER_SYSVIEW_Stop();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_SYSTIME:
      SEGGER_SYSVIEW_RecordSystime();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_TASKLIST:
      SEGGER_SYSVIEW_SendTaskList();
      break;
    case SEGGER_SYSVIEW_COMMAND_ID_GET_SYSDESC:
      SEGGER_SYSVIEW_GetSysDesc();
      break;
    }
  }
}

/*********************************************************************
*
*       _TrySendOverflowPacket()
*
*  Function description
*    Try to transmit an SystemView Overflow packet containing the
*    number of dropped packets.
*
*  Additional information
*    Format as follows:
*      01 <DropCnt><TimeStamp>  Max. packet len is 1 + 5 + 5 = 11
*
*    Example packets sent
*      01 20 40
*
*  Return value
*    !=0:  Success, Message sent (stored in RTT-Buffer)
*    ==0:  Buffer full, Message *NOT* stored
*
*/
static int _TrySendOverflowPacket(void) {
  U32 TimeStamp;
  I32 Delta;
  int Status;
  U8  aPacket[11];
  U8* pPayload;

  aPacket[0] = SEGGER_SYSVIEW_EVENT_ID_OVERFLOW;      // 1
  pPayload   = &aPacket[1];
  ENCODE_U32(pPayload, _SYSVIEW_Globals.DropCount);
  //
  // Compute time stamp delta and append it to packet.
  //
  TimeStamp  = SEGGER_SYSVIEW_GET_TIMESTAMP();
  Delta = TimeStamp - _SYSVIEW_Globals.LastTxTimeStamp;
  MAKE_DELTA_32BIT(Delta);
  ENCODE_U32(pPayload, Delta);
  //
  // Try to store packet in RTT buffer and update time stamp when this was successful
  //
  Status = SEGGER_RTT_WriteSkipNoLock(CHANNEL_ID_UP, aPacket, pPayload - aPacket);
  if (Status) {
    _SYSVIEW_Globals.LastTxTimeStamp = TimeStamp;
    _SYSVIEW_Globals.DropCount = 0;
    _SYSVIEW_Globals.EnableState--; // EnableState has been 2, will be 1. Always.
  } else {
    _SYSVIEW_Globals.DropCount++;
  }
  //
  return Status;
}

/*********************************************************************
*
*       _SendPacket()
*
*  Function description
*    Send a SystemView packet over RTT. RTT channel and mode are
*    configured by macros when the SysView component is initialized.
*    This function takes care of maintaining the packet drop count
*    and sending overflow packets when necessary.
*    The packet must be passed without Id and Length because this
*    function prepends it to the packet before transmission.
*
*  Parameters
*    pStartPacket - Pointer to start of packet payload.
*                   There must be at least 4 bytes free to prepend Id and Length.
*    pEndPacket   - Pointer to end of packet payload.
*    EventId      - Id of the event to send.
*
*/
static void _SendPacket(U8* pStartPacket, U8* pEndPacket, unsigned EventId) {
  unsigned  NumBytes;
  U32 TimeStamp;
  I32 Delta;
  int Status;

  SEGGER_SYSVIEW_LOCK();
  if (_SYSVIEW_Globals.EnableState == 1) {  // Enabled, no dropped packets remaining
    goto Send;
  }
  if (_SYSVIEW_Globals.EnableState == 0) {
    goto SendDone;
  }
  //
  // Handle buffer full situations:
  // Have packets been dropped before because buffer was full?
  // In this case try to send and overflow packet.
  //
  if (_SYSVIEW_Globals.EnableState == 2) {
    _TrySendOverflowPacket();
    if (_SYSVIEW_Globals.EnableState != 1) {
      goto SendDone;
    }
  }
Send:
  //
  // Prepare actual packet.
  // If it is a known packet, prepend eventId only,
  // otherwise prepend packet length and eventId.
  //
  if (EventId < 24) {
    *--pStartPacket = EventId;
  } else {
    NumBytes = pEndPacket - pStartPacket;
    if (NumBytes > 127) {
      *--pStartPacket = (NumBytes >> 7);
      *--pStartPacket = NumBytes | 0x80;
    } else {
      *--pStartPacket = NumBytes;
    }
    if (EventId > 127) {
      *--pStartPacket = (EventId >> 7);
      *--pStartPacket = EventId | 0x80;
    } else {
      *--pStartPacket = EventId;
    }
  }
  //
  // Compute time stamp delta and append it to packet.
  //
  TimeStamp  = SEGGER_SYSVIEW_GET_TIMESTAMP();
  Delta = TimeStamp - _SYSVIEW_Globals.LastTxTimeStamp;
  MAKE_DELTA_32BIT(Delta);
  ENCODE_U32(pEndPacket, Delta);
  //
  // Try to store packet in RTT buffer and update time stamp when this was successful
  //
  Status = SEGGER_RTT_WriteSkipNoLock(CHANNEL_ID_UP, pStartPacket, pEndPacket - pStartPacket);
  if (Status) {
    _SYSVIEW_Globals.LastTxTimeStamp = TimeStamp;
  } else {
    _SYSVIEW_Globals.EnableState++; // EnableState has been 1, will be 2. Always.
  }

  //
  // Check if host is sending data which needs to be processed.
  // Note that since this code is called for every packet, it is very time critical, so we do
  // only what is really needed here, which is checking if there is any data
  //
SendDone:
  if (SEGGER_RTT_HASDATA(CHANNEL_ID_DOWN)) {
    if (_SYSVIEW_Globals.RecursionCnt == 0) {   // Avoid uncontrolled nesting. This way, this routine can call itself once, but no more often than that.
      _SYSVIEW_Globals.RecursionCnt = 1;
      _HandleIncomingPacket();
      _SYSVIEW_Globals.RecursionCnt = 0;
    }
  }
  //
  SEGGER_SYSVIEW_UNLOCK();  // We are done. Unlock and return
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/

/*********************************************************************
*
*       SEGGER_SYSVIEW_Init()
*
*  Function description
*    Initializes the SYSVIEW module.
*    Must be called before SystemViewer attaches to the system.
*
*  Parameters
*    SysFreq        - Frequency of timestamp, i.e. CPU core clock frequency.
*    CPUFreq        - CPU core clock frequency.
*    pOSAPI         - Pointer to the API structure for OS-specific functions.
*    pfSendSysDesc  - Pointer to SendSysDesc callback function.
*
*  Additional information
*    This function initializes the RTT channel used to transport 
*    SEGGER SystemView packets. 
*    The channel is assigned the label "SysView" for client software 
*    to identify the SystemView channel.
*
*  Notes
*    The channel is configured by the macro SEGGER_SYSVIEW_RTT_CHANNEL.
*/
void SEGGER_SYSVIEW_Init(U32 SysFreq, U32 CPUFreq, const SEGGER_SYSVIEW_OS_API *pOSAPI, SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC pfSendSysDesc) {
#if SEGGER_SYSVIEW_RTT_CHANNEL > 0
  SEGGER_RTT_ConfigUpBuffer   (SEGGER_SYSVIEW_RTT_CHANNEL, "SysView", &_SYSVIEW_Globals.UpBuffer[0],   sizeof(_SYSVIEW_Globals.UpBuffer),   SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  SEGGER_RTT_ConfigDownBuffer (SEGGER_SYSVIEW_RTT_CHANNEL, "SysView", &_SYSVIEW_Globals.DownBuffer[0], sizeof(_SYSVIEW_Globals.DownBuffer), SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#else
  _SYSVIEW_Globals.UpChannel = SEGGER_RTT_AllocUpBuffer  ("SysView", &_SYSVIEW_Globals.UpBuffer[0],   sizeof(_SYSVIEW_Globals.UpBuffer),   SEGGER_RTT_MODE_NO_BLOCK_SKIP);
  //
  // TODO: Use SEGGER_RTT_AllocDownBuffer when SysViewer is able to handle another Down Channel than Up Channel.
  //
  _SYSVIEW_Globals.DownChannel = _SYSVIEW_Globals.UpChannel;
  SEGGER_RTT_ConfigDownBuffer (_SYSVIEW_Globals.DownChannel, "SysView", &_SYSVIEW_Globals.DownBuffer[0], sizeof(_SYSVIEW_Globals.DownBuffer), SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
  _SYSVIEW_Globals.RAMBaseAddress  = SEGGER_SYSVIEW_ID_BASE;
  _SYSVIEW_Globals.LastTxTimeStamp = SEGGER_SYSVIEW_GET_TIMESTAMP();
  _SYSVIEW_Globals.pOSAPI          = pOSAPI;
  _SYSVIEW_Globals.SysFreq         = SysFreq;
  _SYSVIEW_Globals.CPUFreq         = CPUFreq;
  _SYSVIEW_Globals.pfSendSysDesc   = pfSendSysDesc;
  _SYSVIEW_Globals.EnableState     = 0;
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_SetRAMBase()
*
*  Function description
*    Sets the RAM base address, which is subtracted from IDs in order
*     to save bandwidth.
*
*  Parameters
*    RAMBaseAddress - Lowest RAM Address. (i.e. 0x20000000 on most Cortex-M)
*/
void SEGGER_SYSVIEW_SetRAMBase(U32 RAMBaseAddress) {
  _SYSVIEW_Globals.RAMBaseAddress = RAMBaseAddress;
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordVoid()
*
*  Function description
*    Formats and sends a SystemView packet with an empty payload.
*
*  Parameters
*    EventID - SystemView event ID.
*/
void SEGGER_SYSVIEW_RecordVoid(unsigned EventID) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, EventID);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordU32()
*
*  Function description
*    Formats and sends a SystemView packet containing a single U32
*    parameter payload.
*
*  Parameters
*    EventID - SystemView event ID.
*    Value   - The 32-bit parameter encoded to SystemView packet payload.
*/
void SEGGER_SYSVIEW_RecordU32(unsigned EventID, U32 Value) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, Value);
  _SendPacket(pPayloadStart, pPayload, EventID);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordU32x2()
*
*  Function description
*    Formats and sends a SystemView packet containing 2 U32 parameter payload.
*
*  Parameters
*    EventID - SystemView event ID.
*    Para0   - The 32-bit parameter encoded to SystemView packet payload.
*    Para1   - The 32-bit parameter encoded to SystemView packet payload.
*/
void SEGGER_SYSVIEW_RecordU32x2(unsigned EventID, U32 Para0, U32 Para1) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 2 * SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;
  //
  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, Para0);
  ENCODE_U32(pPayload, Para1);
  _SendPacket(pPayloadStart, pPayload, EventID);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordU32x3()
*
*  Function description
*    Formats and sends a SystemView packet containing 3 U32 parameter payload.
*
*  Parameters
*    EventID - SystemView event ID.
*    Para0   - The 32-bit parameter encoded to SystemView packet payload.
*    Para1   - The 32-bit parameter encoded to SystemView packet payload.
*    Para2   - The 32-bit parameter encoded to SystemView packet payload.
*/
void SEGGER_SYSVIEW_RecordU32x3(unsigned EventID, U32 Para0, U32 Para1, U32 Para2) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 3 * SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;
  //
  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, Para0);
  ENCODE_U32(pPayload, Para1);
  ENCODE_U32(pPayload, Para2);
  _SendPacket(pPayloadStart, pPayload, EventID);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_Start()
*
*  Function description
*    Start recording SystemView events.
*    This function is triggered by the host application.
*
*  Additional information
*    This function enables transmission of SystemView packets recorded
*    by subsequent trace calls and records a SystemView Start event.
*
*    As part of start, a SystemView Init packet is sent, containing the system
*    frequency. The list of current tasks, the current system time and the
*    system description string is sent, too.
*
*  Notes
*    SEGGER_SYSVIEW_Start and SEGGER_SYSVIEW_Stop do not nest.
*/
void SEGGER_SYSVIEW_Start(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 4 * SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  if (_SYSVIEW_Globals.EnableState == 0) {
    _SYSVIEW_Globals.EnableState = 1;
    SEGGER_SYSVIEW_RecordVoid(SEGGER_SYSVIEW_EVENT_ID_TRACE_START);
    pPayloadStart = _PreparePacket(aPacket);
    pPayload = pPayloadStart;
    ENCODE_U32(pPayload, _SYSVIEW_Globals.SysFreq);
    ENCODE_U32(pPayload, _SYSVIEW_Globals.CPUFreq);
    ENCODE_U32(pPayload, _SYSVIEW_Globals.RAMBaseAddress);
    ENCODE_U32(pPayload, SEGGER_SYSVIEW_ID_SHIFT);
    _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_INIT);
    if (_SYSVIEW_Globals.pfSendSysDesc) {
      _SYSVIEW_Globals.pfSendSysDesc();
    }
    SEGGER_SYSVIEW_RecordSystime();
    SEGGER_SYSVIEW_SendTaskList();
  }
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_Stop()
*
*  Function description
*    Stop recording SystemView events.
*
*  Additional information
*    This function disables transmission of SystemView packets recorded
*    by subsequent trace calls.  If transmission is enabled when
*    this function is called, a single SystemView Stop event is recorded
*    to the trace, send, and then trace transmission is halted.
*/
void SEGGER_SYSVIEW_Stop(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;

  if (_SYSVIEW_Globals.EnableState) {
    pPayloadStart = _PreparePacket(aPacket);
    _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_TRACE_STOP);
    _SYSVIEW_Globals.EnableState = 0;
  }
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_GetSysDesc()
*
*  Function description
*    Triggers a send of the system information and description.
*
*/
void SEGGER_SYSVIEW_GetSysDesc(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 4 * SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;
  
  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, _SYSVIEW_Globals.SysFreq);
  ENCODE_U32(pPayload, _SYSVIEW_Globals.CPUFreq);
  ENCODE_U32(pPayload, _SYSVIEW_Globals.RAMBaseAddress);
  ENCODE_U32(pPayload, SEGGER_SYSVIEW_ID_SHIFT);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_INIT);
  if (_SYSVIEW_Globals.pfSendSysDesc) {
    _SYSVIEW_Globals.pfSendSysDesc();
  }
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_SendTaskInfo()
*
*  Function description
*    Send a Task Info Packet, containing TaskId for identification,
*    task priority and task name.
*
*  Parameters
*    pInfo - Pointer to task information to send.
*/
void SEGGER_SYSVIEW_SendTaskInfo(const SEGGER_SYSVIEW_TASKINFO *pInfo) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32 + 1 + 32];
  U8* pPayload;
  U8* pPayloadStart;
  //
  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, SHRINK_ID(pInfo->TaskID));
  ENCODE_U32(pPayload, pInfo->Prio);
  pPayload = _EncodeStr(pPayload, pInfo->sName, 32);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TASK_INFO);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_SendTaskList()
*
*  Function description
*    Send all tasks descriptors to the host.
*/
void SEGGER_SYSVIEW_SendTaskList(void) {
  if (_SYSVIEW_Globals.pOSAPI && _SYSVIEW_Globals.pOSAPI->pfSendTaskList) {
    _SYSVIEW_Globals.pOSAPI->pfSendTaskList();
  }
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_SendSysDesc()
*
*  Function description
*    Send the system description string to the host.
*    The system description is used by SysViewer to identify the
*    current application and handle events accordingly.
*
*  Parameters
*    sSysDesc - Pointer to the 0-terminated system description string.
*
*  Additional information
*    One system description string may not exceed 128 characters.
*
*    The Following items can be described in a system description string.
*    Each item is identified by its identifier, followed by '=' and the value.
*    Items are separated by ','.
*/
void SEGGER_SYSVIEW_SendSysDesc(const char *sSysDesc) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 1 + 128];
  U8* pPayload;
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  pPayload = _EncodeStr(pPayloadStart, sSysDesc, 128);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_SYSDESC);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordSystime()
*
*  Function description
*    Formats and sends a SystemView Systime containing a single U64 or U32
*    parameter payload.
*/
void SEGGER_SYSVIEW_RecordSystime(void) {
  U64 Systime;

  if (_SYSVIEW_Globals.pOSAPI && _SYSVIEW_Globals.pOSAPI->pfGetTime) {
    Systime = _SYSVIEW_Globals.pOSAPI->pfGetTime();
    SEGGER_SYSVIEW_RecordU32x2(SEGGER_SYSVIEW_EVENT_ID_SYSTIME_US,
                               (U32)(Systime),
                               (U32)(Systime >> 32));
  } else {
    SEGGER_SYSVIEW_RecordU32(SEGGER_SYSVIEW_EVENT_ID_SYSTIME_CYCLES, SEGGER_SYSVIEW_GET_TIMESTAMP());
  }
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordEnterISR()
*
*  Function description
*    Format and send an ISR entry event.
*
*  Additional information
*    Example packets sent
*      02 0F 50              // ISR(15) Enter. Timestamp is 80 (0x50)
*/

void SEGGER_SYSVIEW_RecordEnterISR(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;
  unsigned v;
  
  v = SEGGER_SYSVIEW_GET_INTERRUPT_ID();
  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, v);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_ISR_ENTER);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordExitISR()
*
*  Function description
*    Format and send an ISR exit event.
*
*  Additional information
*    Format as follows:
*      03 <TimeStamp>        // Max. packet len is 6
*
*    Example packets sent
*      03 20                // ISR Exit. Timestamp is 32 (0x20)
*/
void SEGGER_SYSVIEW_RecordExitISR(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;
  
  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_ISR_EXIT);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordExitISRToScheduler()
*
*  Function description
*    Format and send an ISR exit into scheduler event.
*
*  Additional information
*    Format as follows:
*      18 <TimeStamp>        // Max. packet len is 6
*
*    Example packets sent
*      18 20                // ISR Exit to Scheduler. Timestamp is 32 (0x20)
*/
void SEGGER_SYSVIEW_RecordExitISRToScheduler(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_ISR_TO_SCHEDULER);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordEnterTimer()
*
*  Function description
*    Format and send a Timer entry event.
*  
*  Parameters
*    TimerId - Id of the timer which starts.
*/
void SEGGER_SYSVIEW_RecordEnterTimer(unsigned TimerId) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  pPayload = pPayloadStart;
  ENCODE_U32(pPayload, SHRINK_ID(TimerId));
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TIMER_ENTER);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_RecordExitTimer()
*
*  Function description
*    Format and send a Timer exit event.
*/
void SEGGER_SYSVIEW_RecordExitTimer(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_TIMER_EXIT);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnIdle()
*
*  Function description
*    Record an Idle event.
*/
void SEGGER_SYSVIEW_OnIdle(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE];
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_IDLE);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnTaskCreate()
*
*  Function description
*    Record a Task Create event.  The Task Create event corresponds
*    to creating a task in the OS.
*
*  Parameters
*    TaskId        - Task ID of created task.
*/
void SEGGER_SYSVIEW_OnTaskCreate(unsigned TaskId) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  TaskId = SHRINK_ID(TaskId);
  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, TaskId);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TASK_CREATE);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnTaskStartExec()
*
*  Function description
*    Record a Task Start Execution event.  The Task Start event
*    corresponds to when a task has started to execute rather than
*    when it is ready to execute.
*
*  Parameters
*    TaskId - Task ID of task that started to execute.
*/
void SEGGER_SYSVIEW_OnTaskStartExec(unsigned TaskId) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  TaskId = SHRINK_ID(TaskId);
  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, TaskId);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TASK_START_EXEC);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnTaskStopExec()
*
*  Function description
*    Record a Task Stop Execution event.  The Task Stop event
*    corresponds to when a task stops executing.
*/
void SEGGER_SYSVIEW_OnTaskStopExec(void) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayloadStart;

  pPayloadStart = _PreparePacket(aPacket);
  _SendPacket(pPayloadStart, pPayloadStart, SEGGER_SYSVIEW_EVENT_ID_TASK_STOP_EXEC);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnTaskStartReady()
*
*  Function description
*    Record a Task Start Ready event.
*
*  Parameters
*    TaskId - Task ID of task that started to execute.
*/
void SEGGER_SYSVIEW_OnTaskStartReady(unsigned TaskId) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  TaskId = SHRINK_ID(TaskId);
  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, TaskId);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TASK_START_READY);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnTaskStopReady()
*
*  Function description
*    Record a Task Stop Ready event.
*
*  Parameters
*    TaskId - Task ID of task that completed execution.
*    Cause  - Reason for task to stop (i.e. Idle/Sleep)
*/
void SEGGER_SYSVIEW_OnTaskStopReady(unsigned TaskId, unsigned Cause) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + 2 * SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  TaskId = SHRINK_ID(TaskId);
  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, TaskId);
  ENCODE_U32(pPayload, Cause);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_TASK_STOP_READY);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnUserStart()
*
*  Function description
*    Send a user event start, such as start of a subroutine for profiling.
*
*  Parameters
*    UserId  - User defined ID for the event.
*/
void SEGGER_SYSVIEW_OnUserStart(unsigned UserId) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8* pPayload;
  U8* pPayloadStart;

  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, UserId);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_USER_START);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_OnUserStop()
*
*  Function description
*    Send a user event stop, such as return of a subroutine for profiling.
*
*  Parameters
*    UserId  - User defined ID for the event.
*/
void SEGGER_SYSVIEW_OnUserStop(unsigned UserId) {
  U8   aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32];
  U8 * pPayload;
  U8 * pPayloadStart;

  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, UserId);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_USER_STOP);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_NameResource()
*
*  Function description
*    Send the name of a resource to be displayed in SysViewer.
*
*  Parameters
*    ResourceId - Id of the resource to be named. i.e. its address.
*    sName      - Pointer to the resource name. (Max. 128 Bytes)
*/
void SEGGER_SYSVIEW_NameResource(U32 ResourceId, const char* sName) {
  U8  aPacket[SEGGER_SYSVIEW_INFO_SIZE + SEGGER_SYSVIEW_QUANTA_U32 + 1 + 128];
  U8* pPayload;
  U8* pPayloadStart;

  pPayload = pPayloadStart = _PreparePacket(aPacket);
  ENCODE_U32(pPayload, SHRINK_ID(ResourceId));
  pPayload = _EncodeStr(pPayload, sName, 128);
  _SendPacket(pPayloadStart, pPayload, SEGGER_SYSVIEW_EVENT_ID_NAME_RESOURCE);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_SendPacket()
*
*  Function description
*    Send an event packet.
*
*  Parameters
*    pPacket      - Pointer to the start of the packet.
*    pPayloadEnd  - Pointer to the end of the payload.
*                   Make sure there are at least 5 bytes free after the payload.
*    EventId      - Id of the event packet.
*
*  Return value
*    !=0:  Success, Message sent.
*    ==0:  Buffer full, Message *NOT* sent.
*/
int SEGGER_SYSVIEW_SendPacket(U8* pPacket, U8* pPayloadEnd, unsigned EventId) {
  _SendPacket(pPacket + 4, pPayloadEnd, EventId);
  return 0;
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_EncodeU32()
*
*  Function description
*    Encode a U32 in variable-length format.
*
*  Parameters
*    pPayload - Pointer to where U32 will be encoded.
*    Value    - The 32-bit value to be encoded.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*/
U8* SEGGER_SYSVIEW_EncodeU32(U8* pPayload, unsigned Value) {
  ENCODE_U32(pPayload, Value);
  return pPayload;
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_EncodeString()
*
*  Function description
*    Encode a string in variable-length format.
*
*  Parameters
*    pPayload - Pointer to where string will be encoded.
*    s        - String to encode.
*    MaxLen   - Maximum number of characters to encode from string.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*
*  Additional information
*    The string is encoded as a count byte followed by the contents
*    of the string.
*    No more than 1 + MaxLen bytes will be encoded to the payload.
*/
U8* SEGGER_SYSVIEW_EncodeString(U8* pPayload, const char* s, unsigned MaxLen) {
  return _EncodeStr(pPayload, s, MaxLen);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_EncodeData()
*
*  Function description
*    Encode a byte buffer in variable-length format.
*
*  Parameters
*    pPayload - Pointer to where string will be encoded.
*    pSrc     - Pointer to data buffer to be encoded.
*    NumBytes - Number of bytes in the buffer to be encoded.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*
*  Additional information
*    The data is encoded as a count byte followed by the contents
*    of the data buffer.
*    Make sure NumBytes + 1 bytes are free for the payload.
*/
U8* SEGGER_SYSVIEW_EncodeData(U8 *pPayload, const char* pSrc, unsigned NumBytes) {
  return _EncodeData(pPayload, pSrc, NumBytes);
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_EncodeId()
*
*  Function description
*    Encode a 32-bit Id in shrunken variable-length format.
*
*  Parameters
*    pPayload - Pointer to where the Id will be encoded.
*    Id       - The 32-bit value to be encoded.
*
*  Return value
*    Pointer to the byte following the value, i.e. the first free
*    byte in the payload and the next position to store payload
*    content.
*
*  Additional information
*    The parameters to shrink an Id can be configured in
*    SEGGER_SYSVIEW_Conf.h and via SEGGER_SYSVIEW_SetRAMBase().
*     SEGGER_SYSVIEW_ID_BASE: Lowest Id reported by the application.
*       (i.e. 0x20000000 when all Ids are an address in this RAM)
*     SEGGER_SYSVIEW_ID_SHIFT: Number of bits to shift the Id to
*       save bandwidth. (i.e. 2 when Ids are 4 byte aligned)
*/
U8* SEGGER_SYSVIEW_EncodeId(U8* pPayload, unsigned Id) {
  Id = SHRINK_ID(Id);
  ENCODE_U32(pPayload, Id);
  return pPayload;
}

/*********************************************************************
*
*       SEGGER_SYSVIEW_ShrinkId()
*
*  Function description
*    Get the shrunken value of an Id for further processing like in
*    SEGGER_SYSVIEW_NameResource().
*
*  Parameters
*    Id       - The 32-bit value to be shrunken.
*
*  Return value
*    Shrunken Id.
*
*  Additional information
*    The parameters to shrink an Id can be configured in
*    SEGGER_SYSVIEW_Conf.h and via SEGGER_SYSVIEW_SetRAMBase().
*     SEGGER_SYSVIEW_ID_BASE: Lowest Id reported by the application.
*       (i.e. 0x20000000 when all Ids are an address in this RAM)
*     SEGGER_SYSVIEW_ID_SHIFT: Number of bits to shift the Id to
*       save bandwidth. (i.e. 2 when Ids are 4 byte aligned)
*/
unsigned SEGGER_SYSVIEW_ShrinkId(unsigned Id) {
  return SHRINK_ID(Id);
}

/****** End Of File *************************************************/
