/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DebugPortBBTestMain.h

Abstract:

  BB test header file of Debug Port protocol

--*/


#ifndef _DEBUG_PORT_BBTEST_H_
#define _DEBUG_PORT_BBTEST_H_


#include "Efi.h"
#include "EfiTest.h"
#include "DebugPortProtocol.h"
#include "Guid.h"
#include "EfiTestUtilityLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"


#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

#define  DEBUG_PORT_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
InitializeBBTestDebugPort (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDebugPortProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestPollFunctionManualTest (
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

#define DEBUG_PORT_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0xf0b3ed11, 0x549f, 0x4307, { 0x83, 0x6e, 0xee, 0x5e, 0x20, 0x7a, 0xc2, 0x46 } }

#define DEBUG_PORT_PROTOCOL_WRITE_FUNCTION_MANUAL_GUID \
  { 0xa14dee25, 0xa225, 0x43de, { 0x8d, 0x2c, 0xc2, 0xb, 0x77, 0x27, 0x51, 0x32 } }

#define DEBUG_PORT_PROTOCOL_READ_FUNCTION_MANUAL_GUID \
  { 0xd673d5e0, 0x43e, 0x41ee, { 0xb0, 0x3e, 0xc7, 0xeb, 0x61, 0x9c, 0x10, 0x42 } }

#define DEBUG_PORT_PROTOCOL_POLL_FUNCTION_MANUAL_GUID \
  { 0x35dd9073, 0x215e, 0x4afb, { 0xbb, 0x1d, 0xdd, 0x4f, 0x11, 0x65, 0x93, 0x98 } }



#endif

