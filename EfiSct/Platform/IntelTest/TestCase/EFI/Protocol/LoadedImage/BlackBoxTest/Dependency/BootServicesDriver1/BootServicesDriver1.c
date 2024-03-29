/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BootServicesDriver1.c

Abstract:

  for Loaded Image Protocol Black Box Test

--*/

#include "Efi.h"
#include "EfiTestLib.h"

//
// data definition here
//
typedef struct {
  EFI_HANDLE      Handle;
  EFI_HANDLE      OpenHandle;
} BOOT_SERVICES_DRIVER_1_PRIVATE_DATA;

BOOT_SERVICES_DRIVER_1_PRIVATE_DATA   mPrivateData;

EFI_STATUS
InitializeBootServicesDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BootServicesDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBootServicesDriver1)

EFI_STATUS
InitializeBootServicesDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImage;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // UnLoad Function Handler
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID*)&LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  LoadedImage->Unload = BootServicesDriver1Unload;
  return EFI_SUCCESS;
}

EFI_STATUS
BootServicesDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EFI_SUCCESS;
}
