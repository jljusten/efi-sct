/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  StandardTestLibrary.c

Abstract:

  EFI Standard Test Library Protocol

--*/

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

EFI_GUID gEfiStandardTestLibraryGuid = EFI_STANDARD_TEST_LIBRARY_GUID;

EFI_GUID_STRING (&gEfiStandardTestLibraryGuid, "Standard Test Library Protocol", "EFI Standard Test Library Protocol");

EFI_GUID gEfiNullGuid                    = EFI_NULL_GUID;
EFI_GUID gEfiGenericCategoryGuid         = EFI_GENERIC_CLIENT_GUID;
EFI_GUID gEfiBootServicesCategoryGuid    = EFI_BOOT_SERVICES_CLIENT_GUID;
EFI_GUID gEfiRuntimeServicesCategoryGuid = EFI_RUNTIME_SERVICES_CLIENT_GUID;
