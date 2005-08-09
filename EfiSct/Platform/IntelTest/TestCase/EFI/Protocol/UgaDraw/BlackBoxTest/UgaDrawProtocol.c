/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UgaDrawProtocol.c

Abstract:

  UgaDraw Protocol (define according to the EFI Spec 1.1 )

--*/

#include "Efi.h"

#include "UgaDrawProtocol.h"

EFI_GUID gEfiUgaDrawProtocolGuid = EFI_UGA_DRAW_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiUgaDrawProtocolGuid, "UgaDraw Protocol", "EFI 1.0 Uga Draw protocol");

