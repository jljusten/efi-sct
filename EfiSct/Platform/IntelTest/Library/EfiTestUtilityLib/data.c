/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  data.c

Abstract:

  EFI library global data

--*/

#include "lib.h"

//
// LibInitialized - TRUE once InitializeLib() is called for the first time
//

BOOLEAN  LibInitialized = FALSE;

//
// ST - pointer to the EFI system table
//

EFI_SYSTEM_TABLE        *tST;

//
// BS - pointer to the boot services table
//

EFI_BOOT_SERVICES       *tBS;


//
// Default pool allocation type
//

EFI_MEMORY_TYPE PoolAllocationType = EfiBootServicesData;

//
// Unicode collation functions that are in use
//

EFI_UNICODE_COLLATION_PROTOCOL   LibStubUnicodeInterface = {
    LibStubStriCmp,
    LibStubMetaiMatch,
    LibStubStrLwrUpr,
    LibStubStrLwrUpr,
    NULL,   // FatToStr
    NULL,   // StrToFat
    NULL    // SupportedLanguages
};

EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface = &LibStubUnicodeInterface;

//
// Root device path
//

//EFI_DEVICE_PATH_PROTOCOL RootDevicePath[] = {
//    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
//};

typedef struct {
  ACPI_HID_DEVICE_PATH              AcpiDevicePath;
  EFI_DEVICE_PATH_PROTOCOL          EndDevicePath;
} EFI_PCI_ROOT_BRIDGE_DEVICE_PATH;

EFI_PCI_ROOT_BRIDGE_DEVICE_PATH RootDevicePathTemp = {
  {
    ACPI_DEVICE_PATH,
    ACPI_DP,
    (UINT8) (sizeof(ACPI_HID_DEVICE_PATH)),
    (UINT8) ((sizeof(ACPI_HID_DEVICE_PATH)) >> 8),
    EISA_PNP_ID(0x0A03),
    0
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    END_DEVICE_PATH_LENGTH,
    0
  }
};

EFI_DEVICE_PATH_PROTOCOL  *RootDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)&RootDevicePathTemp;



EFI_DEVICE_PATH_PROTOCOL EndDevicePath[] = {
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
};

EFI_DEVICE_PATH_PROTOCOL EndInstanceDevicePath[] = {
    END_DEVICE_PATH_TYPE, END_INSTANCE_DEVICE_PATH_SUBTYPE, END_DEVICE_PATH_LENGTH, 0
};


//
// EFI IDs
//

EFI_GUID tEfiGlobalVariable  = EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID tNullGuid = { 0,0,0,0,0,0,0,0,0,0,0 };

//
// Protocol IDs
//

EFI_GUID gtEfiDevicePathProtocolGuid       = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gtEfiLoadedImageProtocolGuid      = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleTextInProtocolGuid     = EFI_SIMPLE_TEXT_IN_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleTextOutProtocolGuid    = EFI_SIMPLE_TEXT_OUT_PROTOCOL_GUID;
EFI_GUID gtEfiBlockIoProtocolGuid          = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID gtEfiDiskIoProtocolGuid           = EFI_DISK_IO_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
EFI_GUID gtEfiLoadFileProtocolGuid         = LOAD_FILE_PROTOCOL_GUID;
EFI_GUID gtEfiDeviceIoProtocolGuid         = EFI_DEVICE_IO_PROTOCOL_GUID;
EFI_GUID gtEfiUnicodeCollationProtocolGuid = EFI_UNICODE_COLLATION_PROTOCOL_GUID;
EFI_GUID gtEfiSerialIoProtocolGuid         = EFI_SERIAL_IO_PROTOCOL_GUID;
EFI_GUID gtEfiSimpleNetworkProtocolGuid    = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;
EFI_GUID gtEfiPxeBaseCodeProtocolGuid      = EFI_PXE_BASE_CODE_PROTOCOL_GUID;
EFI_GUID gtEfiPxeCallbackProtocolGuid      = EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID;
EFI_GUID gtEfiNetworkInterfaceIdentifierProtocolGuid = EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID;
EFI_GUID tUiProtocol               = EFI_UI_PROTOCOL;
//
// File system information IDs
//

EFI_GUID tGenericFileInfo           = EFI_FILE_INFO_ID;
EFI_GUID gtEfiFileSystemInfoGuid            = EFI_FILE_SYSTEM_INFO_ID_GUID;
EFI_GUID gtEfiFileSystemVolumeLabelInfoGuid = EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID_GUID;

//
// Reference implementation public protocol IDs
//

EFI_GUID gtEfiInternalShellProtocolGuid = INTERNAL_SHELL_GUID;
EFI_GUID gtEfiVariableStoreProtocolGuid = EFI_VARIABLE_STORE_PROTOCOL_GUID;
EFI_GUID tAdapterDebugProtocol = ADAPTER_DEBUG_PROTOCOL;

//
// Device path media protocol IDs
//
EFI_GUID tPcAnsiProtocol = DEVICE_PATH_MESSAGING_PC_ANSI;
EFI_GUID tVt100Protocol  = DEVICE_PATH_MESSAGING_VT_100;

//
// EFI GPT Partition Type GUIDs
//
EFI_GUID gtEfiPartTypeSystemPartitionGuid = EFI_PART_TYPE_EFI_SYSTEM_PART_GUID;
EFI_GUID gtEfiPartTypeLegacyMbrGuid = EFI_PART_TYPE_LEGACY_MBR_GUID;


//
// Reference implementation Vendor Device Path Guids
//
EFI_GUID gtEfiUnknownDeviceGuid      = UNKNOWN_DEVICE_GUID;

//
// Configuration Table GUIDs
//

EFI_GUID gtEfiMpsTableGuid             = EFI_MPS_TABLE_GUID;
EFI_GUID gtEfiAcpiTableGuid            = EFI_ACPI_TABLE_GUID;
EFI_GUID gtEfiAcpi20TableGuid          = EFI_ACPI_20_TABLE_GUID;
EFI_GUID gtEfiSMBIOSTableGuid          = EFI_SMBIOS_TABLE_GUID;
EFI_GUID gtEfiSalSystemTableGuid       = EFI_SAL_SYSTEM_TABLE_GUID;

EFI_GUID gEfiHiiProtocolGuid = EFI_HII_PROTOCOL_GUID;
