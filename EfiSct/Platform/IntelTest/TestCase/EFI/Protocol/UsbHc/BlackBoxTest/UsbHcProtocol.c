/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UsbHcProtocol.c

Abstract:

  UsbHc Protocol (define according to the EFI Spec 1.1 )

--*/

#include "Efi.h"

#include "UsbHcProtocol.h"

EFI_GUID gEfiUsbHcProtocolGuid = EFI_USB_HC_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiUsbHcProtocolGuid, "Usb Host Controller Protocol", "USB 1.1 Host Controller");

