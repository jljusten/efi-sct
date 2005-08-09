/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EventTimerTaskPriorityServicesBBTestRestoreTPL.c

Abstract:

  Test Driver of RestoreTPL() of Event and Timer and Task Priority Services

--*/

#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
BBTestRestoreTPL_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
BBTestRestoreTPL_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate standard test library
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // RestoreTPL() returns EFI_SUCCESS with valid parameters.
  //
  BBTestRestoreTPL_Func_Sub1 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestRestoreTPL_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  UINTN               Index;
  EFI_TPL             OldTpl;
  EFI_TPL             Tpl1;
  EFI_TPL             Tpl2;
  EFI_TPL             CheckTpls[] = {
                        EFI_TPL_APPLICATION,
                        EFI_TPL_CALLBACK,
                        EFI_TPL_NOTIFY,
                        EFI_TPL_HIGH_LEVEL,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Walk through all valid TPLs
  //
  for (Index = 0; CheckTpls[Index] != 0; Index ++) {
    //
    // Check the current TPL
    //
    OldTpl = gtBS->RaiseTPL (EFI_TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    if (OldTpl > CheckTpls[Index]) {
      continue;
    }

    //
    // Raise to check TPL and then to highest TPL
    //
    Tpl1 = gtBS->RaiseTPL (CheckTpls[Index]);
    gtBS->RestoreTPL (Tpl1);
    Tpl2 = gtBS->RaiseTPL (EFI_TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    if ((Tpl1 == OldTpl) && (Tpl2 == OldTpl)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestRestoreTPLAssertionGuid001,
                   L"BS.RestoreTPL - Restore TPL with valid parameters.",
                   L"%a:%d:OldTpl - %d, ToTpl - %d, Tpl1 - %d, Tpl2 - %d",
                   __FILE__,
                   __LINE__,
                   OldTpl,
                   CheckTpls[Index],
                   Tpl1,
                   Tpl2
                   );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
