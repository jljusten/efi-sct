/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestLoggingLibrary.c

Abstract:

  EFI Test Logging Library Protocol

--*/

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (TestLoggingLibrary)

EFI_GUID gEfiTestLoggingLibraryGuid = EFI_TEST_LOGGING_LIBRARY_GUID;

EFI_GUID_STRING (&gEfiTestLoggingLibraryGuid, "Test Logging Library Protocol", "EFI Test Logging Library Protocol");
