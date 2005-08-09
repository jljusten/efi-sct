/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  CombinationImage10.c

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
InitializeCombinationImage10 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_DRIVER_ENTRY_POINT(InitializeCombinationImage10)

EFI_STATUS
InitializeCombinationImage10 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_HANDLE                  Handle;

  //
  // Init
  //
  Handle = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  gtBS->InstallProtocolInterface (
          &Handle,
          &mImageTestNoInterfaceProtocol10Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  gtBS->UninstallProtocolInterface (
          Handle,
          &mImageTestNoInterfaceProtocol10Guid,
          NULL
          );

  gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}