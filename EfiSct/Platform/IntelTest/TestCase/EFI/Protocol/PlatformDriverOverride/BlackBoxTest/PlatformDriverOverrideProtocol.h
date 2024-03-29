/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  PlatformDriverOverrideProtocol.h

Abstract:

  Platform Driver Override protocol as defined in the EFI 1.1 specification.

--*/


#ifndef _PLATFORM_DRIVER_OVERRIDE_FOR_TEST_H_
#define _PLATFORM_DRIVER_OVERRIDE_FOR_TEST_H_

//
// Global ID for the Platform Driver Override Protocol
//
#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID \
    { 0x6b30c738, 0xa391, 0x11d4, 0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}

EFI_FORWARD_DECLARATION(EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL);

//
// Prototypes for the Platform Driver Override Protocol
//

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER) (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL          *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_HANDLE                                     *DriverImageHandle
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH) (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL          *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL                       **DriverImagePath
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED) (
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL          *This,
  IN EFI_HANDLE                                     ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL                       *DriverImagePath,
  IN EFI_HANDLE                                     DriverImageHandle
  );

//
// Interface structure for the Platform Driver Override Protocol
//
typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER       GetDriver;
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH  GetDriverPath;
  EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED    DriverLoaded;
} EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

extern EFI_GUID gEfiPlatformDriverOverrideProtocolGuid;

#endif /* _PLATFORM_DRIVER_OVERRIDE_FOR_TEST_H_ */

