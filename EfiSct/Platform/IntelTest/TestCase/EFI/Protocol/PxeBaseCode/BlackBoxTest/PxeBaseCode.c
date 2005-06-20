/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  PxeBaseCode.c

Abstract:
  PxeBaseCode GUID declaration.

--*/

#include "Efi.h"
#include EFI_PROTOCOL_DEFINITION(PxeBaseCode)

EFI_GUID gEfiPxeBaseCodeProtocolGuid = EFI_PXE_BASE_CODE_PROTOCOL_GUID;

EFI_GUID_STRING(
  &gEfiPxeBaseCodeProtocolGuid,
  "PXE Base Code Protocol",
  "EFI PXE Base Code Protocol");

