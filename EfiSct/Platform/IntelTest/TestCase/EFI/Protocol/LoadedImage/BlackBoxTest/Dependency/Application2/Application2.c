/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Application2.c

Abstract:

  for Loaded Image Protocol Black Box Test

--*/

#include "LoadedImageBBTestProtocolDefinition.h"
#include "EfiTestLib.h"

//
// data definition here
//

EFI_STATUS
InitializeEfiApplication2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_DRIVER_ENTRY_POINT(InitializeEfiApplication2)

EFI_STATUS
InitializeEfiApplication2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Handle;
  UINTN                   *Options;

  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;

  Handle = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   &LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Options = (UINTN*)(LoadedImage->LoadOptions);

  if (Options == NULL) {
    return EFI_SUCCESS;
  }

  if (*Options == 1) {

    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol1Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  } else if (*Options == 2) {
    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol2Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  }


  gtBS->UninstallProtocolInterface (
          Handle,
          &mLoadedImageTestNoInterfaceProtocol1Guid,
          NULL
          );
  gtBS->UninstallProtocolInterface (
          Handle,
          &mLoadedImageTestNoInterfaceProtocol2Guid,
          NULL
          );
  return EFI_SUCCESS;
}

