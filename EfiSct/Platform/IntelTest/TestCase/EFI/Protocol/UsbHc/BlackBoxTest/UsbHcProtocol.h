/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UsbHcProtocol.h

Abstract:

  UsbHc Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_USB_HC_FOR_TEST_H_
#define _EFI_USB_HC_FOR_TEST_H_

#include "usb.h"
#include EFI_PROTOCOL_DEFINITION(UsbIo)

#define EFI_USB_HC_PROTOCOL_GUID \
  {0xF5089266,0x1AA0,0x4953,0x97,0xD8,0x56,0x2F,0x8A,0x73,0xB5,0x19}

EFI_FORWARD_DECLARATION(EFI_USB_HC_PROTOCOL);

typedef enum {
  EfiUsbHcStateHalt,
  EfiUsbHcStateOperational,
  EfiUsbHcStateSuspend,
  EfiUsbHcStateMaximum
} EFI_USB_HC_STATE;

#define EFI_USB_HC_RESET_GLOBAL 0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER 0x0002


typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_RESET) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT16               Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_STATE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  OUT EFI_USB_HC_STATE    *State
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SET_STATE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN EFI_USB_HC_STATE     State
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_CONTROL_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL    *This,
  IN UINT8                  DeviceAddress,
  IN BOOLEAN                IsSlowDevice,
  IN UINT8                  MaximumPacketLength,
  IN EFI_USB_DEVICE_REQUEST *Request,
  IN EFI_USB_DATA_DIRECTION TransferDirection,
  IN OUT VOID               *Data OPTIONAL,
  IN OUT UINTN              *DataLength         OPTIONAL,
  IN UINTN                  TimeOut,
  OUT UINT32                *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_BULK_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN OUT UINTN            *DataLength,
  IN OUT UINT8            *DataToggle,
  IN UINTN                TimeOut,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL              *This,
  IN UINT8                            DeviceAddress,
  IN UINT8                            EndPointAddress,
  IN BOOLEAN                          IsSlowDevice,
  IN UINT8                            MaxiumPacketLength,
  IN BOOLEAN                          IsNewTransfer,
  IN OUT UINT8                        *DataToggle,
  IN UINTN                            PollingInterval OPTIONAL,
  IN UINTN                            DataLength OPTIONAL,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  CallBackFunction OPTIONAL,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN BOOLEAN              IsSlowDevice,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN OUT UINTN            *DataLength,
  IN OUT UINT8            *DataToggle,
  IN UINTN                TimeOut,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN UINTN                DataLength,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI * EFI_USB_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL              *This,
  IN UINT8                            DeviceAddress,
  IN UINT8                            EndPointAddress,
  IN UINT8                            MaximumPacketLength,
  IN OUT VOID                         *Data,
  IN UINTN                            DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallBack,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_NUMBER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  OUT UINT8               *PortNumber
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  OUT EFI_USB_PORT_STATUS *PortStatus
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  IN EFI_USB_PORT_FEATURE PortFeature
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  IN EFI_USB_PORT_FEATURE PortFeature
);

typedef struct _EFI_USB_HC_PROTOCOL {
  EFI_USB_HC_PROTOCOL_RESET                       Reset;
  EFI_USB_HC_PROTOCOL_GET_STATE                   GetState;
  EFI_USB_HC_PROTOCOL_SET_STATE                   SetState;
  EFI_USB_HC_PROTOCOL_CONTROL_TRANSFER            ControlTransfer;
  EFI_USB_HC_PROTOCOL_BULK_TRANSFER               BulkTransfer;
  EFI_USB_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER    AsyncInterruptTransfer;
  EFI_USB_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER     SyncInterruptTransfer;
  EFI_USB_HC_PROTOCOL_ISOCHRONOUS_TRANSFER        IsochronousTransfer;
  EFI_USB_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER  AsyncIsochronousTransfer;
  EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_NUMBER     GetRootHubPortNumber;
  EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS     GetRootHubPortStatus;
  EFI_USB_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE    SetRootHubPortFeature;
  EFI_USB_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE  ClearRootHubPortFeature;
  UINT16                                          MajorRevision;
  UINT16                                          MinorRevision;
} EFI_USB_HC_PROTOCOL;

extern EFI_GUID gEfiUsbHcProtocolGuid;

#endif
