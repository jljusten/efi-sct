/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
    BootServicesDriver2.c

Abstract:
    for Loaded Image Protocol Black Box Test

--*/

#include "LoadedImageBBTestProtocolDefinition.h"
#include "EfiTestLib.h"

EFI_STATUS
InitializeBootServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BootServicesDriver2Unload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBootServicesDriver2)

EFI_STATUS
InitializeBootServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImage;
  EFI_HANDLE                            Handle;
  UINTN                                 *Options;

  Handle = NULL;

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

  LoadedImage->Unload = BootServicesDriver2Unload;

  Options = (UINTN*)(LoadedImage->LoadOptions);

  if (Options == NULL) {
    return EFI_SUCCESS;
  }

  if (*Options == 3) {

    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol3Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  } else if (*Options == 4) {
    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol4Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mLoadedImageTestNoInterfaceProtocol3Guid,
            NULL
            );
    gtBS->UninstallProtocolInterface (
            Handle,
            &mLoadedImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }
  return EFI_SUCCESS;
}

EFI_STATUS
BootServicesDriver2Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EFI_SUCCESS;
}