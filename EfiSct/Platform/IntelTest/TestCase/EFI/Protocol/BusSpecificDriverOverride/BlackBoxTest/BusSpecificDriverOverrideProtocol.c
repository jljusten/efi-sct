/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BusSpecificDriverOverride.c

Abstract:

  Bus Specific Driver Override protocol as defined in the EFI 1.1 specification.

--*/

#include "Efi.h"
#include EFI_PROTOCOL_DEFINITION(BusSpecificDriverOverride)

EFI_GUID gEfiBusSpecificDriverOverrideProtocolGuid = EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiBusSpecificDriverOverrideProtocolGuid, "Bus Specific Driver Override Protocol", "EFI 1.1 Bus Specific Driver Override Protocol");
