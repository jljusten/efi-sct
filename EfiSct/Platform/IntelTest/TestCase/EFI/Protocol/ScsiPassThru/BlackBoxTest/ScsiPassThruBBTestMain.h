/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ScsiPassThruBBTestMain.h

Abstract:

  BB test header file of Scsi Pass Through protocol

--*/


#ifndef _SCSI_PASS_THRU_BBTEST_H_
#define _SCSI_PASS_THRU_BBTEST_H_


#include "Efi.h"
#include "EfiTest.h"
#include "ScsiPassThruProtocol.h"
#include "Guid.h"
#include "EfiTestUtilityLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"


#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

#define  SCSI_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
InitializeBBTestScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestGetNextDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetChannelFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetTargetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestPassThruFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestResetTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
VOID
NotifyFunction (
  EFI_EVENT Event,
  VOID      *Context
  );

EFI_STATUS
GetScsiDevice (
  IN EFI_SCSI_PASS_THRU_PROTOCOL *ScsiPassThru,
  IN OUT UINT32                  *Target,
  IN OUT UINT64                  *Lun
  );

//
// Entry GUIDs
//

#define SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID \
  { 0xb76d1f7d, 0x9f06, 0x47be, { 0xb9, 0xbe, 0xde, 0x69, 0x90, 0x56, 0x2e, 0x6b } }

#define SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0x7d4e35d6, 0x4df6, 0x4025, { 0x86, 0xb9, 0x84, 0xf1, 0x41, 0x54, 0x5e, 0xc8 } }

#define SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xc0209d9d, 0x358, 0x4114, { 0xa3, 0xd1, 0x9b, 0x83, 0xf5, 0x35, 0xa6, 0xe8 } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID \
  { 0x71b547b6, 0x4664, 0x42f8, { 0xab, 0xe2, 0x34, 0xc, 0x1f, 0x25, 0xb7, 0x82 } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_FUNCTION_AUTO_GUID \
  { 0xa297afe, 0x5c9b, 0x46e8, { 0x8a, 0xe7, 0x3, 0x5f, 0xb5, 0x7a, 0x61, 0xcf } }

#define SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0x74689d99, 0xd1d5, 0x443f, { 0xa2, 0xb2, 0x46, 0x85, 0x95, 0xce, 0x16, 0xf5 } }

#define SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x2653f360, 0x53d3, 0x453d, { 0xa5, 0x4f, 0xaf, 0x4c, 0xb, 0xab, 0x1a, 0xc9 } }

#define SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0xe87a9621, 0xc849, 0x446e, { 0xad, 0x69, 0x38, 0xaa, 0xb1, 0x71, 0x4f, 0x67 } }

#define SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x3c38e7b1, 0x5cb0, 0x466a, { 0x85, 0x81, 0x85, 0x74, 0x57, 0x3f, 0xc7, 0x76 } }

#define SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_CONFORMANCE_AUTO_GUID \
  { 0x98c7f1e3, 0x5241, 0x48a0, { 0xb5, 0x28, 0x96, 0xdf, 0x64, 0xb3, 0xd4, 0xc6 } }

#define SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0x3a3371b2, 0x9300, 0x4856, { 0x80, 0xea, 0x29, 0xf7, 0xf8, 0x54, 0x5, 0x91 } }



#endif

