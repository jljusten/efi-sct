/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  RuntimeServicesDriver2.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "Misc.h"
#include "EfiTestLib.h"

//
// data definition here
//

EFI_STATUS
InitializeRuntimeServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_DRIVER_ENTRY_POINT(InitializeRuntimeServicesDriver2)

EFI_STATUS
InitializeRuntimeServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  CHAR16                                *ExitData;
  CHAR16                                *ErrorMessage;
  UINTN                                 ExitSize;
  EFI_HANDLE                            Handle;

  Handle = NULL;
  HandleBuffer = NULL;
  ExitData = NULL;
  ExitSize = 0;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return Status;
  }

  gtBS->OpenProtocol (
          HandleBuffer[0],
          &mImageTestNoInterfaceProtocol2Guid,
          NULL,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_TEST_PROTOCOL
          );

  gtBS->InstallProtocolInterface (
          &Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );
  //
  // clean resources before exit
  //
  gtBS->UninstallProtocolInterface (
          Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );

  gtBS->FreePool (HandleBuffer);

  ErrorMessage = ERROR_MESSAGE_FOR_RUNTIME_SERVICES_DRIVER_2;

  ExitSize = StrSize (ErrorMessage);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ExitSize,
                   (VOID**)&ExitData
                   );
  if (!EFI_ERROR(Status)) {
    gtBS->CopyMem (ExitData, ErrorMessage, ExitSize);
  }

  gtBS->Exit (ImageHandle, EFI_NOT_FOUND, ExitSize, ExitData);

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}