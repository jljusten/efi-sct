/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctInit.c

Abstract:

  Provides SCT initialization services.

--*/

#include "Sct.h"

//
// External functions implementation
//

EFI_STATUS
InitializeFrameworkTable (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
/*++

Routine Description:

  Initialize the framework table.

Arguments:

  ImageHandle    - The image handle.
  SystemTable    - The system table.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Allocate memory for the framework table
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_FRAMEWORK_TABLE),
                 &gFT
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (gFT, sizeof(EFI_SCT_FRAMEWORK_TABLE));

  //
  // Initialize the items of framework table
  //
  gFT->Signature = EFI_SCT_FRAMEWORK_TABLE_SIGNATURE;
  gFT->Revision  = EFI_SCT_FRAMEWORK_TABLE_REVISION;

  InitializeListHead (&gFT->CategoryList);
  InitializeListHead (&gFT->TestFileList);
  InitializeListHead (&gFT->SupportFileList);
  InitializeListHead (&gFT->TestCaseList);
  InitializeListHead (&gFT->TestNodeList);

  //
  // Initialize the image data
  //
  gFT->ImageHandle = ImageHandle;
  gFT->SystemTable = SystemTable;

  Status = ExpandFilePath (
             SI->Argv[0],
             &gFT->DevicePath,
             &gFT->FilePath
             );
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Initialize the test data
  //
  gFT->Operations    = EFI_SCT_OPERATIONS_NONE;
  gFT->SeqDevicePath = NULL;
  gFT->SeqFileName   = NULL;
  gFT->RepDevicePath = NULL;
  gFT->RepFileName   = NULL;

  gFT->IsFirstTimeExecute = TRUE;

  //
  // The configuration data will be initialized later
  //

  //
  // Initialize the test support protocols
  //
  gFT->TolProtocol = gOutputProtocol;

  //
  // Initialize the debug services
  //
  Status = InitializeDebugServices ();
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Get the maximum watchdog timer
  //
  Status = GetMaxWatchdogTimer (&gTestCaseMaxRunTimeMax);
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeFrameworkTable (
  VOID
  )
/*++

Routine Description:

  Free the framework table.

--*/
{
  //
  // Close the standard test support files
  //
  CloseStandardSupportFiles ();

  //
  // Free the items of framework table
  //
  if (gFT->ConfigData != NULL) {
    FreeConfigData (gFT->ConfigData);
    BS->FreePool (gFT->ConfigData);
    gFT->ConfigData = NULL;
  }

  FreeCategoryData (&gFT->CategoryList);

  FreeTestCases (&gFT->TestCaseList);
  FreeTestNodes (&gFT->TestNodeList);

  UnloadTestFiles (&gFT->TestFileList);
  UnloadSupportFiles (&gFT->SupportFileList);

  if (gFT->DevicePath != NULL) {
    BS->FreePool (gFT->DevicePath);
    gFT->DevicePath = NULL;
  }

  if (gFT->FilePath != NULL) {
    BS->FreePool (gFT->FilePath);
    gFT->FilePath = NULL;
  }

  if (gFT->SeqDevicePath != NULL) {
    BS->FreePool (gFT->SeqDevicePath);
    gFT->SeqDevicePath = NULL;
  }

  if (gFT->SeqFileName != NULL) {
    BS->FreePool (gFT->SeqFileName);
    gFT->SeqFileName = NULL;
  }

  if (gFT->RepDevicePath != NULL) {
    BS->FreePool (gFT->RepDevicePath);
    gFT->RepDevicePath = NULL;
  }

  if (gFT->RepFileName != NULL) {
    BS->FreePool (gFT->RepFileName);
    gFT->RepFileName = NULL;
  }

  //
  // Free the debug services
  //
  FreeDebugServices ();

  //
  // Free the framework table itself
  //
  BS->FreePool (gFT);

  //
  // Done
  //
  return EFI_SUCCESS;
}
