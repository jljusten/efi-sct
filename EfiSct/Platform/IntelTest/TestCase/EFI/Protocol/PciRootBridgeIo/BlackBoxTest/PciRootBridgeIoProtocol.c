/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  PciRootBridgeIoProtocol.c

Abstract:

  PCI Root Bridge I/O protocol as defined in the EFI 1.1 specification.

  PCI Root Bridge I/O protocol is used by PCI Bus Driver to perform PCI Memory, PCI I/O,
  and PCI Configuration cycles on a PCI Root Bridge. It also provides services to perform
  defferent types of bus mastering DMA

--*/

#include "Efi.h"

#include "PciRootBridgeIoProtocol.h"

EFI_GUID gEfiPciRootBridgeIoProtocolGuid = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiPciRootBridgeIoProtocolGuid, "PciRootBridgeIo Protocol", "EFI 1.1 Pci Root Bridge IO Protocol");
