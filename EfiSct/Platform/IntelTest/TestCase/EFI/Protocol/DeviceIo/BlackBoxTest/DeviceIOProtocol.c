/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DeviceIoProtocol.c

Abstract:

  Device IO protocol as defined in the EFI 1.1 specification.

  Device IO is used to abstract hardware access to devices. It includes
  memory mapped IO, IO, PCI Config space, and DMA.


--*/

#include "Efi.h"
#include "DeviceIOProtocol.h"


EFI_GUID gEfiDeviceIoProtocolGuid = EFI_DEVICE_IO_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiDeviceIoProtocolGuid, "DeviceIo Protocol", "EFI 1.1 Device IO Protocol");
