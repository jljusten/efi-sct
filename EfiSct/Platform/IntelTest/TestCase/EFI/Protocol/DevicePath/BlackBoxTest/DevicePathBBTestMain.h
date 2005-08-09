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

#define  DEVICE_PATH_PROTOCOL_TEST_REVISION    0x00010001

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

//
// Other function declaration section
//

//
// Entry GUIDs
//

#define DEVICE_PATH_PROTOCOL_DEVICEPATHNODE_CONFORMANCE_AUTO_GUID \
  { 0xc24c24fa, 0x4a52, 0x4968, { 0xba, 0x54, 0x16, 0x57, 0xf, 0x9, 0xbc, 0xa3 } }

#define DEVICE_PATH_PROTOCOL_WHOLEDEVICEPATH_CONFORMANCE_AUTO_GUID \
  { 0xde977427, 0x9f39, 0x40de, { 0x8f, 0xa9, 0xb4, 0xe8, 0x9, 0xd2, 0x74, 0x48 } }



#endif

