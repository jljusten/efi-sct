/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  VariableServicesBbTestMain.c

Abstract:
  The main source file for Variable Services Black-Box Test.

--*/

//
// Includes
//

#include "VariableServicesBbTestMain.h"

//
// Declarations
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  VARIABLE_SERVICES_BB_TEST_REVISION,
  VARIABLE_SERVICES_BB_TEST_GUID,
  L"Variable Services Test",
  L"EFI1.10 Variable Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    GET_VARIABLE_CONF_TEST_GUID,
    L"GetVariable_Conf",
    L"Perform the consistence check of GetVariable() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetVariableConfTest
  },
  {
    GET_NEXT_VARIABLE_NAME_CONF_TEST_GUID,
    L"GetNextVariableName_Conf",
    L"Perform the consistence check of GetNextVariableName() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetNextVariableNameConfTest
  },
  {
    SET_VARIABLE_CONF_TEST_GUID,
    L"SetVariable_Conf",
    L"Perform the consistence check of SetVariable() service.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetVariableConfTest
  },
  {
    GET_VARIABLE_FUNC_TEST_GUID,
    L"GetVariable_Func",
    L"Test the functionality of GetVariable() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetVariableFuncTest
  },
  {
    GET_NEXT_VARIABLE_NAME_FUNC_TEST_GUID,
    L"GetNextVariableName_Func",
    L"Test the functionality of GetNextVariableName() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    GetNextVariableNameFuncTest
  },
  {
    SET_VARIABLE_FUNC_TEST_GUID,
    L"SetVariable_Func",
    L"Test the functionality of SetVariable() service.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    SetVariableFuncTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MULTIPLE_STRESS_TEST_GUID,
    L"Multiple_Stress",
    L"Multiple tests on GetVariable(), GetNextVariableName(), and SetVariable() services.",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    MultipleStressTest
  },
  {
    OVERFLOW_STRESS_TEST_GUID,
    L"Overflow_Stress",
    L"Overflow tests on SetVariable() service",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    OverflowStressTest
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_GUID gTestVendor1Guid = TEST_VENDOR1_GUID;
EFI_GUID gTestVendor2Guid = TEST_VENDOR2_GUID;

//
// Prototypes
//

EFI_STATUS
InitializeVariableServicesBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
UnloadVariableServicesBbTest (
  IN EFI_HANDLE       ImageHandle
  );

//
// Functions
//

EFI_DRIVER_ENTRY_POINT(InitializeVariableServicesBbTest)

/**
 *  Creates/installs the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @param SystemTable    The system table.
 *  @return EFI_SUCCESS   The interface was installed successfully.
 *  @return EFI_OUT_OF_RESOURCES    Failed due to the lack of resources.
 *  @return EFI_INVALID_PARAMETER   One of parameters is invalid.
 */
EFI_STATUS
InitializeVariableServicesBbTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  InitializeLib (ImageHandle, SystemTable);
  EfiInitializeTestLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadVariableServicesBbTest,
           &gBBTestProtocolInterface
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
UnloadVariableServicesBbTest (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param RecoveryLib    A pointer to Test Recovery Support Protocol.
 *  @param LoggingLib     A pointer to Test Logging Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  **RecoveryLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  *StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test recovery support library interface
  //
  *RecoveryLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   RecoveryLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the test logging support library interface
  //
  *LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   LoggingLib
                   );
  // Test logging support library is optional

  //
  // Done
  //
  return EFI_SUCCESS;
}
