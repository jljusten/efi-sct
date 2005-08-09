/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleTextOutProtocol.c

Abstract:

  Simple Text Output Protocol (define according to the EFI Spec 1.1 )

--*/

#include "Efi.h"

#include "SimpleTextOutputProtocol.h"

EFI_GUID gEfiSimpleTextProtocolGuid = SIMPLE_TEXT_OUTPUT_PROTOCOL;

EFI_GUID_STRING(&gEfiSimpleTextProtocolGuid, "Simple Text Output Protocol", "EFI 1.0 Simple Text Output Protocol");

