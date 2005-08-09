/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctDebug.c

Abstract:

  This file provides the debug macro services for SCT.

--*/

#include "Sct.h"

//
// Module variables
//

EFI_FILE *mLogFile = NULL;

//
// External functions implementation
//

EFI_STATUS
InitializeDebugServices (
  VOID
  )
/*++

Routine Description:

  Initialize the debug services.

Returns:

  EFI_SUCCESS   - Successful.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Check the pre-conditions
  //
  if ((gFT == NULL) || (gFT->TolProtocol == NULL)) {
    return EFI_NOT_READY;
  }

  //
  // Open the system log file
  //
  FileName = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_LOG);
  if (FileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gFT->TolProtocol->Open (
                               gFT->TolProtocol,
                               gFT->DevicePath,
                               FileName,
                               TRUE,                  // Overwrite
                               &mLogFile
                               );
  if (EFI_ERROR(Status)) {
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeDebugServices (
  VOID
  )
/*++

Routine Description:

  Free the debug services.

Returns:

  EFI_SUCCESS   - Successful.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Check the pre-conditions
  //
  if (mLogFile == NULL) {
    return EFI_SUCCESS;
  }

  //
  // Close the system log file
  //
  Status = gFT->TolProtocol->Close (
                               gFT->TolProtocol,
                               mLogFile
                               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  mLogFile = NULL;

  //
  // Done
  //
  return EFI_SUCCESS;
}


VOID
EfiSctDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Worker function for EFI_SCT_DEBUG marco.

--*/
{
  EFI_STATUS  Status;
  VA_LIST     Marker;
  CHAR16      Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  CHAR16      *String;

  //
  // Check the pre-conditions
  //
  if (mLogFile == NULL) {
    return;
  }

  //
  // Check the debug masks
  //
  if ((Level & EFI_SCT_D_MASK) == 0) {
    return;
  }

  VA_START (Marker, Format);
  VSPrint (Buffer, EFI_SCT_MAX_BUFFER_SIZE, Format, Marker);
  VA_END (Marker);

  //
  // Deal with different error level
  //
  switch (Level) {
  case EFI_SCT_D_ERROR:
    String = PoolPrint (L"ERROR: %s\n", Buffer);
    break;

  case EFI_SCT_D_DEBUG:
    String = PoolPrint (L"DEBUG: %s\n", Buffer);
    break;

  case EFI_SCT_D_TRACE:
    String = PoolPrint (L"TRACE: %s\n", Buffer);
    break;

  default:
    return;
  }

  //
  // Record into the system log file
  //
  Status = gFT->TolProtocol->Write (
                               gFT->TolProtocol,
                               mLogFile,
                               String
                               );
  if (EFI_ERROR(Status)) {
    BS->FreePool (String);
    return;
  }

  BS->FreePool (String);
}
