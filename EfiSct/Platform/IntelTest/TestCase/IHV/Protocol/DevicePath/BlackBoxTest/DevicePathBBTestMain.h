/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DevicePathBBTestMain.h

Abstract:

  BB test header file of Device Path protocol

--*/


#ifndef _DEVICE_PATH_BBTEST_H_
#define _DEVICE_PATH_BBTEST_H_


#include "Efi.h"
#include "EfiTest.h"
#include "DevicePathProtocol.h"
#include "Guid.h"
#include "EfiTestUtilityLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"


#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

#define  DEVICE_PATH_PROTOCOL_TEST_REVISION    0x00010001

#define  IHV_DEVICE_PATH_PROTOCOL_GUID         \
  { 0xac7b0fd0, 0x884d, 0x45a8, 0x9d, 0x90, 0x99, 0x2a, 0x41, 0xa7, 0x88, 0x09 }

EFI_STATUS
InitializeBBTestDevicePath (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDevicePathProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestDevicePathNodeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWholeDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

BOOLEAN
IsIhvInterface (
  IN VOID                       *ClientInterface,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//

//
// Entry GUIDs
//

#define DEVICE_PATH_PROTOCOL_DEVICEPATHNODE_CONFORMANCE_AUTO_GUID \
  { 0x8fcecc7a, 0xd158, 0x47d9, 0xaa, 0xab, 0xbd, 0x38, 0x96, 0xc6, 0xca, 0x33 }

#define DEVICE_PATH_PROTOCOL_WHOLEDEVICEPATH_CONFORMANCE_AUTO_GUID \
  { 0x2b50418f, 0x5c8c, 0x47a0, 0x96, 0x9c, 0xe3, 0x0a, 0x40, 0x99, 0x59, 0x30 }



#endif

