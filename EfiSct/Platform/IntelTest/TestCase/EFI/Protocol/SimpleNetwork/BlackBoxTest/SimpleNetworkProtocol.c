/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleNetworkProtocol.c

Abstract:

  Simple Network protocol as defined in the EFI 1.0 specification.

--*/

#include "Efi.h"
#include "SimpleNetworkProtocol.h"


EFI_GUID gEfiSimpleNetworkProtocolGuid = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiSimpleNetworkProtocolGuid, "Simple Network Protocol", "EFI 1.0 Simple Network Protocol");
