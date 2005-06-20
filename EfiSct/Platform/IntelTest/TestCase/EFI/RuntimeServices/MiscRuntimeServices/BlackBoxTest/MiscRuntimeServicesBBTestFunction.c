/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  MiscRuntimeServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Miscellaneous Runtime Services

--*/

#include "MiscRuntimeServicesBBTestMain.h"

/**
 *  Entrypoint for gtRT->ResetSystem() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
BBTestResetSystemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   &RecoveryLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle recovery library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    //
    // Step 1
    //
  } else if (ResetData->Step == 1) {
    //
    // Step 2
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ResetSystemStep2;
    }
  } else if (ResetData->Step == 2) {
    //
    // Step 3
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ResetSystemStep3;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.1.2.1  ResetSystem must succeed when ResetType is EfiResetCold
    //
    ResetData->Step = 1;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     __LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error
    //
    Print (L"System will cold reset after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetCold,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ResetSystemStep2:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid001: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid002),
                   L"RT.ResetSystem - EfiResetCold",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.1.2.2  ResetSystem must succeed when ResetType is EfiResetWarm
    //
    ResetData->Step = 2;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     __LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error
    //
    Print (L"System will warm reset after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetWarm,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ResetSystemStep3:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesInterfaceTestAssertionGuid002: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid003: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid004),
                   L"RT.ResetSystem - EfiResetWarm",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->ResetSystem() Manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
BBTestResetSystemManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   &RecoveryLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle recovery library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    //
    // Step 1
    //
  } else if (ResetData->Step == 1) {
    //
    // Step 2
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ManualTestStep2;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.2.2.1  ResetSystem must succeed when ResetType is EfiResetShutdown
    //
    ResetData->Step = 1;
    ResetData->TplIndex = Index;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            Buffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     __LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error.
    //
    // And the stall a second is required to make sure the recovery data has
    // been written into the storage device.
    //
    Print (L"System will shut down (or cold reset) after 1 second...");
    gtBS->Stall (1000000);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    gtRT->ResetSystem (
            EfiResetShutdown,
            EFI_SUCCESS,
            0,
            NULL
            );
    gtBS->RestoreTPL (OldTpl);
    AssertionType = EFI_TEST_ASSERTION_FAILED;

ManualTestStep2:
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMiscRuntimeServicesCombinationTestAssertionGuid006: \
                   (Index == 1? \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid005: \
                    gMiscRuntimeServicesBBTestFunctionAssertionGuid006),
                   L"RT.ResetSystem - EfiResetShutdown",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  return EFI_SUCCESS;
}