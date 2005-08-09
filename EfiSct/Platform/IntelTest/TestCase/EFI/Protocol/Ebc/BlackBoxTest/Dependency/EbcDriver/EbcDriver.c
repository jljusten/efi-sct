/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EbcDriver.c

Abstract:

--*/

#include "EbcDriver.h"
#include "EfiDriverLib.h"
//#include "EfiPrintLib.h"
#include "EfiCommonLib.h"

EFI_GUID gEfiEbcDriverProtocolGuid = EBC_DRIVER_TEST_PROTOCOL;

//
// Prototypes
//

EFI_STATUS
EbcDriverEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EbcDriverUnload (
  IN EFI_HANDLE         ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(EbcDriverEntryPoint)
/**
 *  Ebc Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return  EFI_SUCCESS the driver is loaded successfully.
 *  @return EFI_ALREADY_STARTED the driver has already been loaded before.
 */
EFI_STATUS
EbcDriverEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_LOADED_IMAGE_PROTOCOL      *LoadedImage;

  // Initialize driver lib
  EfiInitializeDriverLib (ImageHandle, SystemTable);

  //
  // Fill in the Unload() function
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **)&LoadedImage,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // The unload function can't invoked in native code
  //
  LoadedImage->Unload = EbcDriverUnload;

  //
  // Open the EBC_DRIVER_TEST_PROTOCOL to perform the supported test.
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiEbcDriverProtocolGuid,
                  NULL,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    return EFI_ALREADY_STARTED;
  }

  //
  // Install EBC_DRIVER_TEST_PROTOCOL
  //
  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gEfiEbcDriverProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );

  return Status;
}

/**
 *  Unload function for the driver, uninstall EBC_DRIVER_TEST_PROTOCOL.
 *  @param ImageHandle the driver image handle.
 *  @return  EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EbcDriverUnload (
  IN EFI_HANDLE         ImageHandle
  )
{
  EFI_STATUS                     Status;
  VOID                           *Interface;

  //
  // Open the EBC_DRIVER_TEST_PROTOCOL
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiEbcDriverProtocolGuid,
                  &Interface,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Uninstall EBC_DRIVER_TEST_PROTOCOL
    //
    Status = gBS->UninstallProtocolInterface (
                    ImageHandle,
                    &gEfiEbcDriverProtocolGuid,
                    NULL
                    );
  }

  return Status;
}
