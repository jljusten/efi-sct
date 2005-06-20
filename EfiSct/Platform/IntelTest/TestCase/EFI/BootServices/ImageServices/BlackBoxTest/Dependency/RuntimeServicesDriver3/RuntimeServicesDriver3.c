/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  RuntimeServicesDriver3.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "EfiTestLib.h"

//
// data definition here
//
typedef struct {
  EFI_HANDLE      Handle;
  EFI_HANDLE      OpenHandle;
} RUNTIME_SERVICES_DRIVER_3_PRIVATE_DATA;

RUNTIME_SERVICES_DRIVER_3_PRIVATE_DATA   mPrivateData;

EFI_STATUS
InitializeRuntimeServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
RuntimeServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeRuntimeServicesDriver3)

EFI_STATUS
InitializeRuntimeServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  mPrivateData.Handle = NULL;
  mPrivateData.OpenHandle = NULL;
  HandleBuffer = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
          ImageHandle,
          &gEfiLoadedImageProtocolGuid,
          (VOID*)&LoadedImageInfoPtr
          );

  LoadedImageInfoPtr->Unload = RuntimeServicesDriver3Unload;

  gtBS->InstallProtocolInterface (
          &mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

  mPrivateData.OpenHandle = HandleBuffer[0];
  gtBS->OpenProtocol (
          mPrivateData.OpenHandle,
          &mImageTestNoInterfaceProtocol2Guid,
          NULL,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_TEST_PROTOCOL
          );

  gtBS->FreePool (HandleBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
RuntimeServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
          mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );

  return EFI_UNSUPPORTED;
}