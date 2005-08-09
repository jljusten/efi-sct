/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SerialIo.c

Abstract:

  Serial IO protocol as defined in the EFI 1.0 specification.

  Abstraction of a basic serial device. Targeted at 16550 UART, but
  could be much more generic.

  (just for test)

--*/

#include "Efi.h"
#include EFI_PROTOCOL_DEFINITION(SerialIo)

EFI_GUID  gEfiSerialIoProtocolGuid = EFI_SERIAL_IO_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiSerialIoProtocolGuid, "SerialIo Protocol", "EFI 1.0 Serial IO Protocol");

