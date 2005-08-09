/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  init.c

Abstract:

  Initialization function

--*/

#include "lib.h"


VOID
EFIDebugVariable (
  VOID
  );


VOID
InitializeLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Initializes EFI library for use

Arguments:

  Firmware's EFI system table

Returns:

  None

--*/
{
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  EFI_STATUS                Status;
  CHAR8                     *LangCode;

  if (!LibInitialized) {
    LibInitialized = TRUE;
    LibFwInstance = FALSE;

    //
    // Set up global pointer to the system table, boot services table,
    // and runtime services table
    //

    tST = SystemTable;
    tBS = SystemTable->BootServices;
    tRT = SystemTable->RuntimeServices;

    //
    // Initialize pool allocation type
    //

    if (ImageHandle) {
      Status = tBS->HandleProtocol (
                     ImageHandle,
                     &gEfiLoadedImageProtocolGuid,
                     (VOID*)&LoadedImage
                     );

      if (!EFI_ERROR(Status)) {
        PoolAllocationType = LoadedImage->ImageDataType;
      }

      EfiDebugAssertInit ();
      EFIDebugVariable ();
    }

    //
    // Initialize platform specific library
    //

    InitializeLibPlatform (ImageHandle,SystemTable);
  }

  if (ImageHandle && UnicodeInterface == &LibStubUnicodeInterface) {
    LangCode = 0;
    //
    // BUGBUG: Hard code here because variable service is not available in sync3.
    //
    // LangCode = LibGetVariable (VarLanguage, &EfiGlobalVariable);
    // InitializeUnicodeSupport (LangCode);
    InitializeUnicodeSupport ("eng");
    if (LangCode) {
      FreePool (LangCode);
    }
  }
}


VOID
InitializeUnicodeSupport (
  CHAR8 *LangCode
  )
/*++

Routine Description:

  Initializes Unicode support

Arguments:

  LangCode - Language Code specified

Returns:

  None

--*/
{
  EFI_UNICODE_COLLATION_PROTOCOL *Ui;
  EFI_STATUS                      Status;
  CHAR8                           *Languages;
  UINTN                           Index, Position, Length;
  UINTN                           NoHandles;
  EFI_HANDLE                      *Handles;

  //
  // If we don't know it, lookup the current language code
  //

  LibLocateHandle (ByProtocol, &gEfiUnicodeCollationProtocolGuid, NULL, &NoHandles, &Handles);
  if (!LangCode || !NoHandles) {
    goto Done;
  }

  //
  // Check all driver's for a matching language code
  //

  for (Index=0; Index < NoHandles; Index++) {
    Status = tBS->HandleProtocol (Handles[Index], &gEfiUnicodeCollationProtocolGuid, (VOID*)&Ui);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Check for a matching language code
    //

    Languages = Ui->SupportedLanguages;
    Length = strlena(Languages);
    for (Position=0; Position < Length; Position += ISO_639_2_ENTRY_SIZE) {

      //
      // If this code matches, use this driver
      //

      if (CompareMem (Languages+Position, LangCode, ISO_639_2_ENTRY_SIZE) == 0) {
        UnicodeInterface = Ui;
        goto Done;
      }
    }
  }

Done:
  //
  // Cleanup
  //

  if (Handles) {
    FreePool (Handles);
  }
}

VOID
EFIDebugVariable (
  VOID
  )
/*++

Routine Description:
  Initializes the EFIDebug variable for our build

Arguments:

  None

Returns:

  None

--*/
{
  EFI_STATUS      Status;
  UINT32          Attributes;
  UINTN           DataSize;
  UINTN           NewEFIDebug;

  DataSize = sizeof(EFIDebug);
  Status = tRT->GetVariable(L"EFIDebug", &tEfiGlobalVariable, &Attributes, &DataSize, &NewEFIDebug);
  if (!EFI_ERROR(Status)) {
    EFIDebug = NewEFIDebug;
  }
}
