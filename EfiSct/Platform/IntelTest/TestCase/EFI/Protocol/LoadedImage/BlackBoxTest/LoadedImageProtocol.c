/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

 LoadedImageProtocol.c

Abstract:

  EFI 1.0 Loaded Image Protocol definition.

  Every EFI driver and application is passed an image handle when it is loaded.
  This image handle will contain a Loaded Image Protocol.

--*/

#include "Efi.h"
#include "LoadedImageProtocol.h"

EFI_GUID gEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiLoadedImageProtocolGuid, "LoadedImage Protocol", "EFI 1.0 Loaded Image Protocol");
