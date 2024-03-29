/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleNetworkProtocol.h

Abstract:

  Simple Network protocol as defined in the EFI 1.0 specification.

--*/

#ifndef _SIMPLE_NETWORK_FOR_TEST_H_
#define _SIMPLE_NETWORK_FOR_TEST_H_

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID \
  { 0xA19832B9, 0xAC25, 0x11D3, 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }

EFI_FORWARD_DECLARATION(EFI_SIMPLE_NETWORK_PROTOCOL);


//
// Simple Network Protocol data structures
//

typedef struct {

  //
  // Total number of frames received.  Includes frames with errors and
  // dropped frames.
  //
  UINT64  RxTotalFrames;

  //
  // Number of valid frames received and copied into receive buffers.
  //
  UINT64  RxGoodFrames;

  //
  // Number of frames below the minimum length for the media.
  // This would be <64 for ethernet.
  //
  UINT64  RxUndersizeFrames;

  //
  // Number of frames longer than the maxminum length for the
  // media.  This would be >1500 for ethernet.
  //
  UINT64  RxOversizeFrames;

  //
  // Valid frames that were dropped because receive buffers were full.
  //
  UINT64  RxDroppedFrames;

  //
  // Number of valid unicast frames received and not dropped.
  //
  UINT64  RxUnicastFrames;

  //
  // Number of valid broadcast frames received and not dropped.
  //
  UINT64  RxBroadcastFrames;

  //
  // Number of valid mutlicast frames received and not dropped.
  //
  UINT64  RxMulticastFrames;

  //
  // Number of frames w/ CRC or alignment errors.
  //
  UINT64  RxCrcErrorFrames;

  //
  // Total number of bytes received.  Includes frames with errors
  // and dropped frames.
  //
  UINT64  RxTotalBytes;

  //
  // Transmit statistics.
  //
  UINT64  TxTotalFrames;
  UINT64  TxGoodFrames;
  UINT64  TxUndersizeFrames;
  UINT64  TxOversizeFrames;
  UINT64  TxDroppedFrames;
  UINT64  TxUnicastFrames;
  UINT64  TxBroadcastFrames;
  UINT64  TxMulticastFrames;
  UINT64  TxCrcErrorFrames;
  UINT64  TxTotalBytes;

  //
  // Number of collisions detection on this subnet.
  //
  UINT64  Collisions;

  //
  // Number of frames destined for unsupported protocol.
  //
  UINT64  UnsupportedProtocol;

} EFI_NETWORK_STATISTICS;


typedef enum {
  EfiSimpleNetworkStopped,
  EfiSimpleNetworkStarted,
  EfiSimpleNetworkInitialized,
  EfiSimpleNetworkMaxState
} EFI_SIMPLE_NETWORK_STATE;


#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST               0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST             0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST             0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS           0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10


#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT        0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT       0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT        0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT       0x08

#define MAX_MCAST_FILTER_CNT    16
typedef struct {
  UINT32                      State;
  UINT32                      HwAddressSize;
  UINT32                      MediaHeaderSize;
  UINT32                      MaxPacketSize;
  UINT32                      NvRamSize;
  UINT32                      NvRamAccessSize;
  UINT32                      ReceiveFilterMask;
  UINT32                      ReceiveFilterSetting;
  UINT32                      MaxMCastFilterCount;
  UINT32                      MCastFilterCount;
  EFI_MAC_ADDRESS             MCastFilter[MAX_MCAST_FILTER_CNT];
  EFI_MAC_ADDRESS             CurrentAddress;
  EFI_MAC_ADDRESS             BroadcastAddress;
  EFI_MAC_ADDRESS             PermanentAddress;
  UINT8                       IfType;
  BOOLEAN                     MacAddressChangeable;
  BOOLEAN                     MultipleTxSupported;
  BOOLEAN                     MediaPresentSupported;
  BOOLEAN                     MediaPresent;
} EFI_SIMPLE_NETWORK_MODE;


//
// Protocol Member Functions
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_START) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  )
/*++

  Routine Description:
    Changes the state of a network interface from "stopped" to "started".

  Arguments:
    This - Protocol instance pointer.

  Returns:
    EFI_SUCCESS - The network interface was started.
    EFI_ALREADY_STARTED   - The network interface is already in the started state.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STOP) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  )
/*++

  Routine Description:
    Changes the state of a network interface from "started" to "stopped".

  Arguments:
    This - Protocol instance pointer.

  Returns:
    EFI_SUCCESS - The network interface was stopped.
    EFI_ALREADY_STARTED   - The network interface is already in the stopped state.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_INITIALIZE) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN UINTN                        ExtraRxBufferSize  OPTIONAL,
  IN UINTN                        ExtraTxBufferSize  OPTIONAL
  )
/*++

  Routine Description:
   Resets a network adapter and allocates the transmit and receive buffers
   required by the network interface; optionally, also requests allocation
   of additional transmit and receive buffers.

  Arguments:
    This - Protocol instance pointer.
    ExtraRxBufferSize - The size, in bytes, of the extra receive buffer space
                        that the driver should allocate for the network interface.
                        Some network interfaces will not be able to use the extra
                        buffer, and the caller will not know if it is actually
                        being used.
    ExtraTxBufferSize - The size, in bytes, of the extra transmit buffer space
                        that the driver should allocate for the network interface.
                        Some network interfaces will not be able to use the extra
                        buffer, and the caller will not know if it is actually
                        being used.

  Returns:
    EFI_SUCCESS     - The network interface was initialized.
    EFI_NOT_STARTED - The network interface has not been started
    EFI_OUT_OF_RESOURCES  - There was not enough memory for the transmit and
                             receive buffers.   .
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RESET) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL    *This,
  IN BOOLEAN                        ExtendedVerification
  )
/*++

  Routine Description:
   Resets a network adapter and re-initializes it with the parameters that were
   provided in the previous call to Initialize().

  Arguments:
    This                 - Protocol instance pointer.
    ExtendedVerification - Indicates that the driver may perform a more
                           exhaustive verification operation of the device
                           during reset.


  Returns:
    EFI_SUCCESS     - The network interface was reset.
    EFI_NOT_STARTED - The network interface has not been started
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_SHUTDOWN) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  )
/*++

  Routine Description:
   Resets a network adapter and leaves it in a state that is safe for
   another driver to initialize.

  Arguments:
    This                 - Protocol instance pointer.

  Returns:
    EFI_SUCCESS     - The network interface was shutdown.
    EFI_NOT_STARTED - The network interface has not been started
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE_FILTERS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  IN UINT32                               Enable,
  IN UINT32                               Disable,
  IN BOOLEAN                              ResetMCastFilter,
  IN UINTN                                MCastFilterCnt     OPTIONAL,
  IN EFI_MAC_ADDRESS                      *MCastFilter       OPTIONAL
  )
/*++

  Routine Description:
    Manages the multicast receive filters of a network interface.

  Arguments:
    This    - Protocol instance pointer.
    Enable  - A bit mask of receive filters to enable on the network interface.
    Disable - A bit mask of receive filters to disable on the network interface.
    ResetMCastFilter - Set to TRUE to reset the contents of the multicast receive
                        filters on the network interface to their default values.
    McastFilterCnt   - Number of multicast HW MAC addresses in the new
                        MCastFilter list. This value must be less than or equal to
                        the MCastFilterCnt field of EFI_SIMPLE_NETWORK_MODE. This
                        field is optional if ResetMCastFilter is TRUE.
    MCastFilter      - A pointer to a list of new multicast receive filter HW MAC
                        addresses. This list will replace any existing multicast
                        HW MAC address list. This field is optional if
                        ResetMCastFilter is TRUE.

  Returns:
    EFI_SUCCESS     - The multicast receive filter list was updated.
    EFI_NOT_STARTED - The network interface has not been started
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STATION_ADDRESS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL            *This,
  IN BOOLEAN                                Reset,
  IN EFI_MAC_ADDRESS                        *New      OPTIONAL
  )
/*++

  Routine Description:
    Modifies or resets the current station address, if supported.

  Arguments:
    This  - Protocol instance pointer.
    Reset - Flag used to reset the station address to the network interface's
             permanent address.
    New   - New station address to be used for the network interface.

  Returns:
    EFI_SUCCESS     - The network interface's station address was updated.
    EFI_NOT_STARTED - The network interface has not been started
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STATISTICS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  IN BOOLEAN                              Reset,
  IN OUT UINTN                            *StatisticsSize   OPTIONAL,
  OUT EFI_NETWORK_STATISTICS              *StatisticsTable  OPTIONAL
  )
/*++

  Routine Description:
    Resets or collects the statistics on a network interface.

  Arguments:
    This  - Protocol instance pointer.
    Reset - Set to TRUE to reset the statistics for the network interface.
    StatisticsSize  - On input the size, in bytes, of StatisticsTable. On
                       output the size, in bytes, of the resulting table of
                       statistics.
    StatisticsTable - A pointer to the EFI_NETWORK_STATISTICS structure that
                       contains the statistics.

  Returns:
    EFI_SUCCESS     - The statistics were collected from the network interface.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_BUFFER_TOO_SMALL - The Statistics buffer was too small. The current buffer
                            size needed to hold the statistics is returned in
                            StatisticsSize.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  IN BOOLEAN                              IPv6,
  IN EFI_IP_ADDRESS                       *IP,
  OUT EFI_MAC_ADDRESS                     *MAC
  )
/*++

  Routine Description:
    Converts a multicast IP address to a multicast HW MAC address.

  Arguments:
    This - Protocol instance pointer.
    IPv6 - Set to TRUE if the multicast IP address is IPv6 [RFC 2460]. Set
            to FALSE if the multicast IP address is IPv4 [RFC 791].
    IP   - The multicast IP address that is to be converted to a multicast
            HW MAC address.
    MAC  - The multicast HW MAC address that is to be generated from IP.

  Returns:
    EFI_SUCCESS     - The multicast IP address was mapped to the multicast
                       HW MAC address.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_BUFFER_TOO_SMALL - The Statistics buffer was too small. The current buffer
                            size needed to hold the statistics is returned in
                            StatisticsSize.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_NVDATA) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  IN BOOLEAN                              ReadWrite,
  IN UINTN                                Offset,
  IN UINTN                                BufferSize,
  IN OUT VOID                             *Buffer
  )
/*++

  Routine Description:
    Performs read and write operations on the NVRAM device attached to a
    network interface.

  Arguments:
    This - Protocol instance pointer.
    ReadWrite - TRUE for read operations, FALSE for write operations.
    Offset    - Byte offset in the NVRAM device at which to start the read or
                 write operation. This must be a multiple of NvRamAccessSize and
                 less than NvRamSize.
    BufferSize - The number of bytes to read or write from the NVRAM device.
                  This must also be a multiple of NvramAccessSize.
    Buffer     - A pointer to the data buffer.

  Returns:
    EFI_SUCCESS     - The NVRAM access was performed.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_GET_STATUS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  OUT UINT32                              *InterruptStatus  OPTIONAL,
  OUT VOID                                **TxBuf           OPTIONAL
  )
/*++

  Routine Description:
    Reads the current interrupt status and recycled transmit buffer status from
    a network interface.

  Arguments:
    This - Protocol instance pointer.
    InterruptStatus - A pointer to the bit mask of the currently active interrupts
                       If this is NULL, the interrupt status will not be read from
                       the device. If this is not NULL, the interrupt status will
                       be read from the device. When the  interrupt status is read,
                       it will also be cleared. Clearing the transmit  interrupt
                       does not empty the recycled transmit buffer array.
    TxBuf           - Recycled transmit buffer address. The network interface will
                       not transmit if its internal recycled transmit buffer array
                       is full. Reading the transmit buffer does not clear the
                       transmit interrupt. If this is NULL, then the transmit buffer
                       status will not be read. If there are no transmit buffers to
                       recycle and TxBuf is not NULL, * TxBuf will be set to NULL.

  Returns:
    EFI_SUCCESS     - The status of the network interface was retrieved.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_TRANSMIT) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  IN UINTN                                HeaderSize,
  IN UINTN                                BufferSize,
  IN VOID                                 *Buffer,
  IN EFI_MAC_ADDRESS                      *SrcAddr     OPTIONAL,
  IN EFI_MAC_ADDRESS                      *DestAddr    OPTIONAL,
  IN UINT16                               *Protocol    OPTIONAL
  )
/*++

  Routine Description:
    Places a packet in the transmit queue of a network interface.

  Arguments:
    This - Protocol instance pointer.
    HeaderSize - The size, in bytes, of the media header to be filled in by
                  the Transmit() function. If HeaderSize is non-zero, then it
                  must be equal to This->Mode->MediaHeaderSize and the DestAddr
                  and Protocol parameters must not be NULL.
    BufferSize - The size, in bytes, of the entire packet (media header and
                  data) to be transmitted through the network interface.
    Buffer   - A pointer to the packet (media header followed by data) to be
                transmitted. This parameter cannot be NULL. If HeaderSize is zero,
                then the media header in Buffer must already be filled in by the
                caller. If HeaderSize is non-zero, then the media header will be
                filled in by the Transmit() function.
    SrcAddr  - The source HW MAC address. If HeaderSize is zero, then this parameter
                is ignored. If HeaderSize is non-zero and SrcAddr is NULL, then
                This->Mode->CurrentAddress is used for the source HW MAC address.
    DsetAddr - The destination HW MAC address. If HeaderSize is zero, then this
                parameter is ignored.
    Protocol - The type of header to build. If HeaderSize is zero, then this
                parameter is ignored. See RFC 1700, section "Ether Types", for
                examples.

  Returns:
    EFI_SUCCESS     - The packet was placed on the transmit queue.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_NOT_READY   - The network interface is too busy to accept this transmit
                       request.
    EFI_BUFFER_TOO_SMALL  - The BufferSize parameter is too small.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL          *This,
  OUT UINTN                               *HeaderSize  OPTIONAL,
  IN OUT UINTN                            *BufferSize,
  OUT VOID                                *Buffer,
  OUT EFI_MAC_ADDRESS                     *SrcAddr     OPTIONAL,
  OUT EFI_MAC_ADDRESS                     *DestAddr    OPTIONAL,
  OUT UINT16                              *Protocol    OPTIONAL
  )
/*++

  Routine Description:
    Receives a packet from a network interface.

  Arguments:
    This - Protocol instance pointer.
    HeaderSize - The size, in bytes, of the media header received on the network
                  interface. If this parameter is NULL, then the media header size
                  will not be returned.
    BufferSize - On entry, the size, in bytes, of Buffer. On exit, the size, in
                  bytes, of the packet that was received on the network interface.
    Buffer   - A pointer to the data buffer to receive both the media header and
                the data.
    SrcAddr  - The source HW MAC address. If this parameter is NULL, the
                HW MAC source address will not be extracted from the media
                header.
    DsetAddr - The destination HW MAC address. If this parameter is NULL,
                the HW MAC destination address will not be extracted from the
                media header.
    Protocol - The media header type. If this parameter is NULL, then the
                protocol will not be extracted from the media header. See
                RFC 1700 section "Ether Types" for examples.

  Returns:
    EFI_SUCCESS     - The received data was stored in Buffer, and BufferSize has
                       been updated to the number of bytes received.
    EFI_NOT_STARTED - The network interface has not been started.
    EFI_NOT_READY   - The network interface is too busy to accept this transmit
                       request.
    EFI_BUFFER_TOO_SMALL  - The BufferSize parameter is too small.
    EFI_INVALID_PARAMETER - One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR - The command could not be sent to the network interface.
    EFI_UNSUPPORTED  - This function is not supported by the network interface.

--*/
;


#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION   0x00010000

typedef struct _EFI_SIMPLE_NETWORK_PROTOCOL {
  UINT64                              Revision;
  EFI_SIMPLE_NETWORK_START            Start;
  EFI_SIMPLE_NETWORK_STOP             Stop;
  EFI_SIMPLE_NETWORK_INITIALIZE       Initialize;
  EFI_SIMPLE_NETWORK_RESET            Reset;
  EFI_SIMPLE_NETWORK_SHUTDOWN         Shutdown;
  EFI_SIMPLE_NETWORK_RECEIVE_FILTERS  ReceiveFilters;
  EFI_SIMPLE_NETWORK_STATION_ADDRESS  StationAddress;
  EFI_SIMPLE_NETWORK_STATISTICS       Statistics;
  EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC  MCastIPtoMAC;
  EFI_SIMPLE_NETWORK_NVDATA           NvData;
  EFI_SIMPLE_NETWORK_GET_STATUS       GetStatus;
  EFI_SIMPLE_NETWORK_TRANSMIT         Transmit;
  EFI_SIMPLE_NETWORK_RECEIVE          Receive;
  EFI_EVENT                           WaitForPacket;
  EFI_SIMPLE_NETWORK_MODE             *Mode;
} EFI_SIMPLE_NETWORK_PROTOCOL;

extern EFI_GUID gEfiSimpleNetworkProtocolGuid;


#endif
