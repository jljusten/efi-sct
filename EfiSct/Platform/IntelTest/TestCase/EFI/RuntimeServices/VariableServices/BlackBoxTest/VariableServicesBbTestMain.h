/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  VariableServicesBbTestMain.h

Abstract:
  Header file for Variable Services Black-Box Test.

--*/

#ifndef _VARIABLE_SERVICES_BB_TEST_MAIN_H
#define _VARIABLE_SERVICES_BB_TEST_MAIN_H

//
// Includes
//
#include "Efi.h"
#include "Guid.h"
#include "EfiTest.h"
#include "EfiTestLib.h"
#include "EfiTestUtilityLib.h"
#include EFI_TEST_PROTOCOL_DEFINITION(BbTest)
#include EFI_TEST_PROTOCOL_DEFINITION(StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

//
// Definitions
//

#define VARIABLE_SERVICES_BB_TEST_REVISION    0x00010000

#define VARIABLE_SERVICES_BB_TEST_GUID        \
  { 0xD6844631, 0x0A1E, 0x42d1, 0xA5, 0x94, 0x60, 0x35, 0x48, 0x47, 0xB6, 0x76 }

#define MAX_BUFFER_SIZE                       256

#define TEST_VENDOR1_GUID                         \
  { 0xF6FAB04F, 0xACAF, 0x4af3, { 0xB9, 0xFA, 0xDC, 0xF9, 0x7F, 0xB4, 0x42, 0x6F } }
#define TEST_VENDOR2_GUID                         \
  { 0x49b08eba, 0xa56c, 0x4015, { 0xb7, 0x03, 0xe7, 0x73, 0xc3, 0x32, 0x62, 0x8b } }

#define GET_VARIABLE_CONF_TEST_GUID               \
  { 0xd90941aa, 0xb626, 0x4665, { 0xba, 0x14, 0x64, 0x08, 0x43, 0x96, 0xf3, 0x1d } }
#define GET_NEXT_VARIABLE_NAME_CONF_TEST_GUID     \
  { 0xe8014c92, 0x15c4, 0x42a8, { 0x8b, 0x0d, 0x60, 0x80, 0xc4, 0x7d, 0x37, 0x78 } }
#define SET_VARIABLE_CONF_TEST_GUID               \
  { 0xc0391b41, 0x591f, 0x4173, { 0x8c, 0xe3, 0x5f, 0xf9, 0x15, 0x8a, 0x94, 0x8c } }

#define GET_VARIABLE_FUNC_TEST_GUID               \
  { 0x5e7928aa, 0xcf97, 0x469c, { 0xa6, 0xca, 0xa5, 0x57, 0x71, 0x35, 0xc1, 0x0c } }
#define GET_NEXT_VARIABLE_NAME_FUNC_TEST_GUID     \
  { 0x66a7216f, 0xa855, 0x47d3, { 0x91, 0x9c, 0xb6, 0xd3, 0x46, 0x68, 0xbe, 0x8e } }
#define SET_VARIABLE_FUNC_TEST_GUID               \
  { 0xd4700fe8, 0x9832, 0x4353, { 0x96, 0x1f, 0x74, 0x68, 0x2d, 0x37, 0x01, 0xf6 } }

#define MULTIPLE_STRESS_TEST_GUID                 \
  { 0xe244a6b3, 0x3e18, 0x4fdc, { 0x92, 0x5a, 0x0b, 0xfc, 0xdd, 0x29, 0x28, 0xee } }
#define OVERFLOW_STRESS_TEST_GUID                 \
  { 0xa9f04a54, 0x1f65, 0x44d2, { 0x8b, 0x52, 0xe6, 0xd4, 0xa0, 0x7f, 0x82, 0x1e } }

//
// Global Variables
//

extern EFI_GUID gTestVendor1Guid;
extern EFI_GUID gTestVendor2Guid;

//
// Prototypes
//

//
// TDS 3.1
//
EFI_STATUS
GetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
GetNextVariableNameConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
SetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1
//
EFI_STATUS
GetVariableFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
GetNextVariableNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
SetVariableFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1
//
EFI_STATUS
MultipleStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
OverflowStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Support functions
//
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );

#endif
