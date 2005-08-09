/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  MiscRuntimeServicesBBTestMain.c

Abstract:

  Test Driver of Miscellaneous Runtime Services

--*/

#include "MiscRuntimeServicesBBTestMain.h"

EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  EFI_TPL_APPLICATION,
  EFI_TPL_CALLBACK,
  EFI_TPL_NOTIFY
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  MISC_RUNTIME_SERVICES_TEST_REVISION,
  MISC_RUNTIME_SERVICES_TEST_GUID,
  L"Misc Runtime Services Test",
  L"EFI1.10 Misc Runtime Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_INTERFACE_GUID,
    L"ResetSystem_Func",
    L"Interface Test for ResetSystem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestResetSystemInterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_GUID,
    L"ResetSystem_Func_Manual",
    L"Manual Test for ResetSystem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_MANUAL,
    BBTestResetSystemManualTest
  },
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_STRESS_TEST_GUID,
    L"ResetSystem_Stress",
    L"Stress Test for ResetSystem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestResetSystemStressTest
  },
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_STRESS_TEST_GUID,
    L"ResetSystem_Stress_Manual",
    L"Manual Stress Test for ResetSystem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_MANUAL,
    BBTestResetSystemManualStressTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestMiscRuntimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBBTestMiscRuntimeServices)

/**
 *  Miscellaneous Runtime Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestMiscRuntimeServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestMiscRuntimeServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestMiscRuntimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}