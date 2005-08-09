/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  UsbIoTest.h

Abstract:
  Header file for Usb I/O Protocol Interface testing.

--*/

#ifndef _USB_IO_TEST_H
#define _USB_IO_TEST_H


#include "Efi.h"
#include "EfiTest.h"
#include "Guid.h"
#include "EfiTestLib.h"
#include "UsbIoProtocol.h"

#include EFI_TEST_PROTOCOL_DEFINITION(BbTest)
#include EFI_TEST_PROTOCOL_DEFINITION(StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

//#include EFI_PROTOCOL_DEFINITION(UsbIo)

#define USB_IO_TEST_REVISION 0x00010001

//
// Definitions
//
#define USB_IO_USBCONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xba920a1f,0xdda9,0x4adb, {0xa6,0x67,0x1c,0x74,0x28,0x4e,0xed,0xc0}}
#define USB_IO_USBBULKTRANSFER_CONFORMANCE_AUTO_GUID  \
  {0x10b21512,0x9f9e,0x4b9d, {0xb8,0x99,0x32,0xfb,0xb9,0x86,0x08,0x92}}
#define USB_IO_USBASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x8e2c14fe,0x9ed9,0x4365, {0xa9,0xf1,0x51,0x9e,0xcf,0xe6,0x7a,0x3a}}
#define USB_IO_USBSYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xe9fe1709,0x17be,0x40f9, {0xb3,0xc2,0x87,0x56,0xa1,0x90,0xd4,0xa2}}
#define USB_IO_USBASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xcf24b302,0xe529,0x4085, {0xbf,0x16,0x89,0xad,0x79,0x25,0xba,0xca}}
#define USB_IO_USBISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xb5052347,0x1bb1,0x49af, {0xa8,0xe0,0xdb,0xaa,0x8e,0x2f,0x28,0x23}}
#define USB_IO_USBGETDEVICEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x75d43e12,0x1268,0x426a, {0xba,0x46,0xf6,0x9a,0xb7,0xd0,0xf1,0x66}}
#define USB_IO_USBGETCONFIGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0xa0d33285,0x3071,0x4cba, {0x8a,0x57,0x2e,0xec,0x14,0xfc,0x49,0x14}}
#define USB_IO_USBGETINTERFACEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x4ce53ccb,0x6431,0x4bde, {0x90,0x20,0xf4,0xbf,0xbe,0xd8,0x34,0xcd}}
#define USB_IO_USBGETENDPOINTDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0xcb32ea3d,0x468d,0x4bd7, {0x96,0xde,0x30,0xec,0x30,0x87,0xc9,0xee}}
#define USB_IO_USBPORTRESET_CONFORMANCE_AUTO_GUID \
  {0x1b8d123a,0x807a,0x433d, {0x9f,0x09,0xc5,0x68,0x2e,0xc1,0xf8,0x2c}}
#define USB_IO_USBGETSTRINGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x73f1b45f,0x9426,0x4512, {0xb5,0x3e,0xbe,0x1f,0x13,0x72,0x9c,0x92}}

//
// Prototypes
//

//
// TDS 5.1
//
EFI_STATUS
UsbControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
UsbBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
UsbAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
UsbSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.x
//
EFI_STATUS
UsbAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.x
//
EFI_STATUS
UsbIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
UsbGetDeviceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.6
//
EFI_STATUS
UsbGetConfigDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.7
//
EFI_STATUS
UsbGetInterfaceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.8
//
EFI_STATUS
UsbGetEndpointDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.9
//
EFI_STATUS
UsbPortResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.10
//
EFI_STATUS
UsbGetStringDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
InitializeBBTestUsbIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUsbIoUnload (
  IN EFI_HANDLE           ImageHandle
  );

#endif
