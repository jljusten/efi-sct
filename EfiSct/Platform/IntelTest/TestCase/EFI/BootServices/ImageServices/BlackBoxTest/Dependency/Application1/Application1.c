/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Application1.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "EfiTestLib.h"

//
// data definition here
//

EFI_STATUS
InitializeEfiApplication1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_APPLICATION_ENTRY_POINT(InitializeEfiApplication1)

EFI_STATUS
InitializeEfiApplication1 (
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

  Status = gtBS->InstallProtocolInterface (
                   &ImageHandle,
                   &mImageTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    goto Done;
  }

  Status = gtBS->OpenProtocol (
                   HandleBuffer[0],
                   &mImageTestNoInterfaceProtocol2Guid,
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
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );
  return EFI_SUCCESS;
}

