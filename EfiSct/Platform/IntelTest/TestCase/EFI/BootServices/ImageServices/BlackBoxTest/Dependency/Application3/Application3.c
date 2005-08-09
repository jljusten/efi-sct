/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Application3.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "EfiTestLib.h"

//
// data definition here
//

EFI_STATUS
InitializeEfiApplication3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_APPLICATION_ENTRY_POINT(InitializeEfiApplication3)

EFI_STATUS
InitializeEfiApplication3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NoHandles;


  HandleBuffer = NULL;
  NoHandles    = 0;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  gtBS->InstallProtocolInterface (
          &ImageHandle,
          &mImageTestNoInterfaceProtocol3Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol4Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    goto Done;
  }

  gtBS->OpenProtocol (
          HandleBuffer[0],
          &mImageTestNoInterfaceProtocol4Guid,
          NULL,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_TEST_PROTOCOL
          );

Done:

  if (HandleBuffer != NULL && NoHandles > 0) {
    gtBS->FreePool (HandleBuffer);
  }


  gtBS->UninstallProtocolInterface (
          ImageHandle,
          &mImageTestNoInterfaceProtocol3Guid,
          NULL
          );


  gtBS->Exit (ImageHandle,EFI_SUCCESS,0,NULL);

  //
  //the code should not arrive here so we add a variable to verify if the Exit
  //return control to StartImage correctly.
  //

  //
  //first make sure there is no duplicated variable exist so we first delete once.
  //
  gtRT->SetVariable (
          IMAGE_APPLICATION3_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          0,
          (VOID*)&ImageHandle
          );

  //
  //then call SetVariable to set a variable.
  //

  gtRT->SetVariable (
          IMAGE_APPLICATION3_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          sizeof(EFI_HANDLE),
          (VOID*)&ImageHandle
          );

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}

