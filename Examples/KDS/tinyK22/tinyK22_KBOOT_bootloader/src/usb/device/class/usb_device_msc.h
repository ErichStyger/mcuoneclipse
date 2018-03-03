/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_DEVICE_MSC_H__
#define __USB_DEVICE_MSC_H__

#include "usb_device_msc_ufi.h"
/*!
 * @addtogroup usb_msc
 * @{
 */
#define USB_DEVICE_CONFIG_MSC_MAX_INSTANCE (1U)
/*! @brief prevent media removal flag */
#define USB_DEVICE_CONFIG_MSC_SUPPORT_DISK_LOCKING_MECHANISM (0U)
#define USB_DEVICE_CONFIG_MSC_IMPLEMENTING_DISK_DRIVE (0U)
/*! @brief The class code of the MSC class */
#define USB_DEVICE_CONFIG_MSC_CLASS_CODE (0x08U)

/*! @brief Bulk-Only Mass Storage Reset (class-specific request) */
#define USB_DEVICE_MSC_BULK_ONLY_MASS_STORAGE_RESET (0xFFU)
/*! @brief Get Maximum LUN (class-specific request) */
#define USB_DEVICE_MSC_GET_MAX_LUN (0xFEU)

/*! @brief CBW dCBWSignature*/
#define USB_DEVICE_MSC_DCBWSIGNATURE USB_LONG_TO_BIG_ENDIAN(0x55534243U)
/*! @brief CSW dCSSWSignature*/
#define USB_DEVICE_MSC_DCSWSIGNATURE USB_LONG_TO_BIG_ENDIAN(0x55534253U)
/*! @brief CSW bmCBWFlags bit7 */
#define USB_DEVICE_MSC_CBW_DIRECTION_BIT (0x80U)
#define USB_DEVICE_MSC_CBW_DIRECTION_SHIFT (7U)
/*! @brief CBW command length*/
#define USB_DEVICE_MSC_CBW_LENGTH (31U)
/*! @brief CSW command length*/
#define USB_DEVICE_MSC_CSW_LENGTH (13U)
/*! @brief Command Block Status Values*/
#define USB_DEVICE_MSC_COMMAND_PASSED (0x00U)
#define USB_DEVICE_MSC_COMMAND_FAILED (0x01U)
#define USB_DEVICE_MSC_PHASE_ERROR (0x02U)
/*! @brief UFI Commands code*/
#define USB_DEVICE_MSC_INQUIRY_COMMAND (0x12U)
#define USB_DEVICE_MSC_READ_10_COMMAND (0x28U)
#define USB_DEVICE_MSC_READ_12_COMMAND (0xA8U)
#define USB_DEVICE_MSC_REQUEST_SENSE_COMMAND (0x03U)
#define USB_DEVICE_MSC_TEST_UNIT_READY_COMMAND (0x00U)
#define USB_DEVICE_MSC_WRITE_10_COMMAND (0x2AU)
#define USB_DEVICE_MSC_WRITE_12_COMMAND (0xAAU)
#define USB_DEVICE_MSC_PREVENT_ALLOW_MEDIUM_REM_COMMAND (0x1EU)
#define USB_DEVICE_MSC_FORMAT_UNIT_COMMAND (0x04U)
#define USB_DEVICE_MSC_READ_CAPACITY_10_COMMAND (0x25U)
#define USB_DEVICE_MSC_READ_CAPACITY_16_COMMAND (0x9EU)
#define USB_DEVICE_MSC_READ_FORMAT_CAPACITIES_COMMAND (0x23U)
#define USB_DEVICE_MSC_MODE_SENSE_10_COMMAND (0x5AU)
#define USB_DEVICE_MSC_MODE_SENSE_6_COMMAND (0x1AU)
#define USB_DEVICE_MSC_MODE_SELECT_10_COMMAND (0x55U)
#define USB_DEVICE_MSC_MODE_SELECT_6_COMMAND (0x15U)
#define USB_DEVICE_MSC_SEND_DIAGNOSTIC_COMMAND (0x1DU)
#define USB_DEVICE_MSC_VERIFY_COMMAND (0x2FU)
#define USB_DEVICE_MSC_START_STOP_UNIT_COMMAND (0x1BU)

/*Max transfer length */
#define USB_DEVICE_MSC_MAX_RECV_TRANSFER_LENGTH (65536U)
#define USB_DEVICE_MSC_MAX_SEND_TRANSFER_LENGTH (65536U)

/*! @brief Command Block Wrapper(CBW) */
typedef struct _usb_device_msc_cbw
{
    uint32_t signature;          /*!< Byte 0-3 dCBWSignature*/
    uint32_t tag;                /*!< Byte 4-7 dCBWTag*/
    uint32_t dataTransferLength; /*!< Byte 8-11 dCBWDataTransferLength*/
    uint8_t flags;               /*!< Byte 12 bmCBWFlags*/
    uint8_t logicalUnitNumber;   /*!< Byte 13 bCBWLUN*/
    uint8_t cbLength;            /*!< Byte 14 bCBWCBLength*/
    uint8_t cbwcb[16];           /*!< Byte 15-30 CBWCB, CBWCB is used to store UFI command*/
} usb_device_msc_cbw_t;
/*! @brief Command Status Wrapper(CSW) */
typedef struct _usb_device_msc_csw
{
    uint32_t signature;   /*!< Byte 0-3 dCSWSignature*/
    uint32_t tag;         /*!< Byte 4-7 dCSWTag*/
    uint32_t dataResidue; /*!< Byte 8-11 dCSWDataResidue*/
    uint8_t cswStatus;    /*!< Byte 12 bCSWStatus*/
} usb_device_msc_csw_t;
/*! @brief Read/write information */
typedef struct _usb_lba_transfer_information_struct
{
    uint32_t startingLogicalBlockAddress; /*!< The logical block at which the read/write operation shall begin*/
    uint32_t transferNumber; /*!< The number of contiguous logical blocks of data that shall be transferred*/
} usb_lba_transfer_information_struct_t;
/*! @brief device information */
typedef struct _usb_device_lba_information_struct
{
    uint32_t totalLbaNumberSupports;    /*!< Total blocks number supported*/
    uint32_t lengthOfEachLba;           /*!< Length of each block*/
    uint32_t bulkInBufferSize;          /*!< Bulk in buffer size*/
    uint32_t bulkOutBufferSize;         /*!< Bulk out buffer size*/
    uint8_t logicalUnitNumberSupported; /*!< Number of LUN*/
} usb_device_lba_information_struct_t;

/*! @brief Data transfer information */
typedef struct _usb_device_lba_app_struct
{
    uint32_t offset; /*!< Offset of the block need to access*/
    uint32_t size;   /*!< Size of the transferred data*/
    uint8_t *buffer; /*!< Buffer address of the transferred data*/
} usb_device_lba_app_struct_t;
/*! @brief The thirteen possible use cases of host expectations and device intent in the absence of
overriding error conditions. */
typedef struct _usb_device_msc_thirteen_case_struct
{
    uint32_t hostExpectedDataLength;   /*!< The number of bytes of data that the host expects to transfer */
    uint32_t deviceExpectedDataLength; /*!< The number of bytes of data that the device expects to transfer */
    uint8_t *buffer;                   /*!< Data buffer*/
    usb_lba_transfer_information_struct_t lbaInformation; /*!< Read/write information*/
    uint8_t lbaSendRecvSelect;                            /*!< Whether the command is read or write command*/
    uint8_t hostExpectedDirection;                        /*!< Host expected data direction*/
    uint8_t deviceExpectedDirection;                      /*!< Device expected data direction*/
} usb_device_msc_thirteen_case_struct_t;
/*! @brief stall flag */
typedef enum
{
    USB_DEVICE_MSC_STALL_IN_CBW = 1U, /*!< Stall in CBW*/
    USB_DEVICE_MSC_STALL_IN_DATA,     /*!< Stall in data transfer*/
    USB_DEVICE_MSC_STALL_IN_CSW,      /*!< Stall in CSW*/
} usb_devcie_msc_stall_type;
/*! @brief Available common EVENT types in MSC class callback */
typedef enum
{
    kUSB_DeviceMscEventReadResponse = 0x01U, /*!< Send data completed */
    kUSB_DeviceMscEventWriteResponse,        /*!< Data received */
    kUSB_DeviceMscEventWriteRequest,         /*!< Host write data*/
    kUSB_DeviceMscEventReadRequest,          /*!< Host read data*/
    kUSB_DeviceMscEventGetLbaInformation,    /*!< Get device information */
    kUSB_DeviceMscEventFormatComplete,       /*!< Format complete */
    kUSB_DeviceMscEventRemovalRequest,       /*!< Prevent_allow_medium_command */
    kUSB_DeviceMscEventStopEjectMedia,       /*!< Start_stop_unit_command */

} USB_DeviceMscEvent_t;
/*! @brief The MSC device UFI command status structure */
typedef struct _usb_device_msc_ufi_struct
{
    usb_device_request_sense_data_struct_t requestSense;     /*!< Request Sense Standard Data*/
    usb_device_msc_thirteen_case_struct_t thirteenCase;      /*!< Thirteen possible cases*/
    usb_device_read_capacity_struct_t readCapacity;          /*!< READ CAPACITY Data*/
    usb_device_read_capacity16_data_struct_t readCapacity16; /*!< READ CAPACITY Data*/
    usb_device_inquiry_data_fromat_struct_t InquiryInfo;     /*!< Standard INQUIRY Data*/
    usb_device_mode_parameters_header_struct_t ModeParametersHeader;/*!< Mode Parameter Header*/
    uint8_t formattedDisk;                                   /*!< *Formatted or unformatted media*/
    uint8_t formatCapacityData[sizeof(usb_device_capacity_list_header_struct_t) +
                               sizeof(usb_device_current_max_capacity_descriptor_struct_t) +
                               sizeof(usb_device_formattable_capacity_descriptor_struct_t) * 3];
    /*!< Capacity List*/
} usb_device_msc_ufi_struct_t;
/*! @brief The MSC device structure */
typedef struct _usb_device_msc_struct
{
    usb_device_handle handle;                              /*!< The device handle */
    usb_device_class_config_struct_t *configurationStruct; /*!< The configuration of the class*/
    usb_device_interface_struct_t *interfaceHandle;        /*!< Current interface handle */
    uint32_t transferRemaining;                            /*!< Transfer remaining data */
    uint32_t currentOffset;                                /*!< Current address offset */
    uint32_t totalLogicalBlockNumber;                      /*!< Total logical block number of device */
    uint32_t lengthOfEachLba;                              /*!< Length of logical block */
    uint32_t implementingDiskDrive;                        /*!< Disk drive*/
    uint32_t bulkInBufferSize;                             /*!< Bulk in buffer size*/
    uint32_t bulkOutBufferSize;                            /*!< Bulk out buffer size*/

    usb_device_msc_cbw_t mscCbw; /*!< CBW structure */
    usb_device_msc_csw_t mscCsw; /*!< CSW structure */

    usb_device_msc_ufi_struct_t mscUfi; /*!< UFI command information structure*/

    uint8_t dataOutFlag;          /*!< CBW indicating bulk out transfer, clear this flag when data transfer done*/
    uint8_t dataInFlag;           /*!< CBW indicating bulk in transfer, clear this flag when data transfer done*/
    uint8_t inEndpointStallFlag;  /*!< In endpoint stall flag*/
    uint8_t outEndpointStallFlag; /*!< Out endpoint stall flag*/
    uint8_t cbwValidFlag; /*!< The CBW was received after the device had sent a CSW or after a reset ,or else it is
                             invalid*/
    uint8_t performResetRecover;  /*!< Device need reset command from host*/
    uint8_t performResetDoneFlag; /*!< Device has perform reset command */
    uint8_t needInStallFlag;      /*!< In endpoint should be stalled*/
    uint8_t needOutStallFlag;     /*!< Out endpoint should be stalled*/
    uint8_t cbwPrimeFlag; /*!< CBW prime flag, prime means device MSC has been ready to receive CBW, the bulk out
                             endpoint has got the prepared buffer*/
    uint8_t cswPrimeFlag; /*!< CSW prime flag, prime means device MSC has been ready to receive CSW, the bulk in
                             endpoint has got the prepared buffer*/
    uint8_t stallStatus;  /*!< Stall status*/

    uint8_t logicalUnitNumber; /*!< Supported logical units number of device. See bulk only specification 3.2 Get Maximum LUN
                                  (class-specific request)*/
    uint8_t bulkInEndpoint;    /*!< Bulk in endpoint number*/
    uint8_t bulkOutEndpoint;   /*!< Bulk out endpoint number*/
    uint8_t alternate;         /*!< Current alternate setting of the interface */
    uint8_t configuration;     /*!< Current configuration */
    uint8_t interfaceNumber;   /*!< The interface number of the class */
} usb_device_msc_struct_t;

/*!
 * @name USB device MSC class APIs
 * @{
 */
/*!
* @brief Initializes the MSC class.
*
* This function is used to initialize the MSC class.
*
* @param controllerId   The controller ID of the USB IP. See the enumeration usb_controller_index_t.
* @param config          The class configuration information.
* @param handle          An parameter used to return pointer of the MSC class handle to the caller.
*
* @return A USB error code or kStatus_USB_Success.
*/
extern usb_status_t USB_DeviceMscInit(uint8_t controllerId,
                                      usb_device_class_config_struct_t *config,
                                      class_handle_t *handle);
/*!
 * @brief Deinitializes the device MSC class.
 *
 * The function deinitializes the device MSC class.
 *
 * @param handle The MSC class handle received from usb_device_class_config_struct_t::classHandle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceMscDeinit(class_handle_t handle);

/*! @}*/

extern usb_status_t USB_DeviceMscEvent(void *handle, uint32_t event, void *param);
extern usb_status_t USB_DeviceMscLbaTransfer(usb_device_msc_struct_t *mscHandle,
                                             uint8_t direction,
                                             usb_lba_transfer_information_struct_t *lba_info_ptr);

#ifdef __cplusplus
extern "C" {
#endif

extern usb_status_t USB_DeviceMscUfiThirteenCasesCheck(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiRequestSenseCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiInquiryCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiReadCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiWriteCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiTestUnitReadyCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiVerifyCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiModeSenseCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiModeSelectCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiReadCapacityCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiReadFormatCapacityCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiFormatUnitCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiPreventAllowMediumCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiSendDiagnosticCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiStartStopUnitCommand(usb_device_msc_struct_t *mscHandle);
extern usb_status_t USB_DeviceMscUfiUnsupportCommand(usb_device_msc_struct_t *mscHandle);
#ifdef __cplusplus
}
#endif

/*! @}*/

#endif
