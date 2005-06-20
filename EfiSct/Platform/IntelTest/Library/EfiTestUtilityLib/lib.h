/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  lib.h

Abstract:

  EFI library header files

--*/

#include "Efi.h"
#include "EfiTestUtilityLib.h"

#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)
#include EFI_PROTOCOL_DEFINITION (SimpleTextOut)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCode)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCodeCallback)
#include EFI_PROTOCOL_DEFINITION (EfiNetworkInterfaceIdentifier)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION (SerialIo)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (VariableStore)
#include EFI_PROTOCOL_DEFINITION (DebugAssert)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics)
#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_GUID_DEFINITION (GlobalVariable)
#include EFI_GUID_DEFINITION (Gpt)
#include EFI_GUID_DEFINITION (Mps)
#include EFI_GUID_DEFINITION (Acpi)
#include EFI_GUID_DEFINITION (Smbios)
#include EFI_GUID_DEFINITION (SalSystemTable)

//
// Prototypes
//

INTN
LibStubStriCmp (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *S1,
    IN CHAR16                           *S2
    );

BOOLEAN
LibStubMetaiMatch (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *String,
    IN CHAR16                           *Pattern
    );

VOID
LibStubStrLwrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *Str
    );

BOOLEAN
LibMatchDevicePaths (
    IN  EFI_DEVICE_PATH_PROTOCOL *Multi,
    IN  EFI_DEVICE_PATH_PROTOCOL *Single
    );

EFI_DEVICE_PATH_PROTOCOL *
LibDuplicateDevicePathInstance (
    IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
    );


//
// Globals
//
extern BOOLEAN                          LibInitialized;
extern BOOLEAN                          LibFwInstance;
extern EFI_SIMPLE_TEXT_OUT_PROTOCOL     *LibRuntimeDebugOut;
extern EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface;
extern EFI_UNICODE_COLLATION_PROTOCOL   LibStubUnicodeInterface;
extern EFI_RAISE_TPL                    LibRuntimeRaiseTPL;
extern EFI_RESTORE_TPL                  LibRuntimeRestoreTPL;
extern UINTN                            EFIDebug;
