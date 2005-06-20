/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Main.c

Abstract:

  main source file for make pci configuraiton space writable

--*/
#include "Common.h"
#include "Main.h"
#include "EfiShellLib.h"

EFI_DRIVER_ENTRY_POINT (MakeConfigWritableEntryPoint)

EFI_STATUS
MakeConfigWritableEntryPoint (
  IN EFI_HANDLE                      ImageHandle,
  IN EFI_SYSTEM_TABLE                *SystemTable
  )
{
  EFI_STATUS     Status;
  PCIDev         *TestDev;

  //
  //Initialize Libraries
  //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  Status = FindTestCard (&TestDev);
  if (EFI_ERROR(Status)) {
    Print (L"Not found the Test Card, please insert the Pci Test Card and run this program again.\r\n");
    return Status;
  }

  Status = MakeConfigWritable (TestDev);
  if (EFI_ERROR(Status)) {
    Print (L"Failed make the configuration space writable.\r\n");
  } else {
    Print (L"Successfully make the configuration space writable.\r\n");
  }

  FreePool (TestDev);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}