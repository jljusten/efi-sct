/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestDriver.h

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include "Efi.h"
#include "EfiTestLib.h"
#include "ProtocolDefinition.h"

#define MAX_STRING_LEN      250

#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (PlatformDriverOverride)
#include EFI_PROTOCOL_DEFINITION (BusSpecificDriverOverride)

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

typedef struct {
  EFI_HANDLE                  Handle;
  EXTERNAL_DRIVER_PROTOCOL_1  ExProt1;
  EFI_STATUS                  *StatusArray;
  EFI_HANDLE                  *HandleArray;
  EFI_GUID                    *ProtGuidArray;
  UINTN                       ArrayCount;
  UINTN                       Count;
  EFI_HANDLE                  ChildHandle;
} TEST_DRIVER_PRIVATE_DATA;

typedef struct {
  EFI_HANDLE                  Handle;
  EXTERNAL_DRIVER_PROTOCOL_1  ExProt1;
  EFI_DRIVER_BINDING_PROTOCOL DriverBinding;
  EFI_STATUS                  *StatusArray;
  EFI_HANDLE                  *HandleArray;
  EFI_GUID                    *ProtGuidArray;
  UINTN                       ArrayCount;
  UINTN                       Count;
  EFI_HANDLE                  ChildHandle;
} DBINDING_DRIVER_PRIVATE_DATA;

#endif