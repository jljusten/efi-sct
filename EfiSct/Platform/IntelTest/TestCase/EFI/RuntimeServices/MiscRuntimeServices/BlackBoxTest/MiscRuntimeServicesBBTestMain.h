/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  MiscRuntimeServicesBBTestMain.h

Abstract:

  BB test header file of Miscellaneous Runtime Services

--*/


#ifndef _MISC_RUNTIME_SERVICES
#define _MISC_RUNTIME_SERVICES

#include "Efi.h"
#include "EfiTestLib.h"
#include "EfiTestUtilityLib.h"
#include "Guid.h"

typedef struct _RESET_DATA {
  UINTN           Step;
  UINTN           TplIndex;
  UINT32          RepeatTimes;
} RESET_DATA;

#include EFI_TEST_PROTOCOL_DEFINITION (TestRecoveryLibrary)

#define MISC_RUNTIME_SERVICES_TEST_REVISION   0x00010000

#define MISC_RUNTIME_SERVICES_TEST_GUID       \
  { 0x65AB91D6, 0xAB78, 0x4a5d, 0xBA, 0x80, 0x1A, 0xBD, 0x23, 0x58, 0xC3, 0xA4 }

#define TPL_ARRAY_SIZE 3

extern EFI_TPL TplArray[TPL_ARRAY_SIZE];

//
// Prototypes of Interface Test
//

//
// TDS 4.1
//
EFI_STATUS
BBTestResetSystemInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestResetSystemManualTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Combination Test
//

//
// TDS 5.1
//
EFI_STATUS
BBTestResetSystemStressTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
BBTestResetSystemManualStressTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Internal Functions
//


//
// Entry GUIDs
//

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_INTERFACE_GUID \
  { 0x1dbeb615, 0x9504, 0x4e2f, 0xba, 0xfc, 0xb3, 0xc6, 0xb2, 0xde, 0xbc, 0x7b }

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_GUID \
  { 0x3ae30328, 0x85ef, 0x46af, 0x9a, 0xb7, 0x3c, 0x9e, 0x9a, 0x1a, 0x86, 0x10 }

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_STRESS_TEST_GUID \
  { 0x5cc0a7c, 0x62f6, 0x4971, 0xbe, 0x33, 0xec, 0x8a, 0xbd, 0x48, 0xf, 0xdd }

#define MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_STRESS_TEST_GUID \
  { 0x3966be0c, 0xf04b, 0x465f, 0xaa, 0x46, 0x22, 0x93, 0xd2, 0xdf, 0xd4, 0x6f }


#endif