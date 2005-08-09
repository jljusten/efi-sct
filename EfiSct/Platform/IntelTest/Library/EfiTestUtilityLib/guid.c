/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  guid.c

Abstract:

  Misc EFI support functions

--*/

#include "lib.h"

//
// Additional Known guids
//

#define SHELL_INTERFACE_PROTOCOL \
  { 0x47c7b223, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define ENVIRONMENT_VARIABLE_ID  \
  { 0x47c7b224, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define DEVICE_PATH_MAPPING_ID  \
  { 0x47c7b225, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define PROTOCOL_ID_ID  \
  { 0x47c7b226, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define ALIAS_ID  \
  { 0x47c7b227, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

static EFI_GUID ShellInterfaceProtocol = SHELL_INTERFACE_PROTOCOL;
static EFI_GUID SEnvId                 = ENVIRONMENT_VARIABLE_ID;
static EFI_GUID SMapId                 = DEVICE_PATH_MAPPING_ID;
static EFI_GUID SProtId                = PROTOCOL_ID_ID;
static EFI_GUID SAliasId               = ALIAS_ID;

struct {
  EFI_GUID        *Guid;
  CHAR16          *GuidName;
} KnownGuids[] = {
  &tNullGuid,                  L"G0",
  &tEfiGlobalVariable,         L"Efi",

  &gtEfiVariableStoreProtocolGuid,     L"varstore",
  &gtEfiDevicePathProtocolGuid,        L"dpath",
  &gtEfiLoadedImageProtocolGuid,       L"image",
  &gtEfiSimpleTextInProtocolGuid,      L"txtin",
  &gtEfiSimpleTextOutProtocolGuid,     L"txtout",
  &gtEfiBlockIoProtocolGuid,           L"blkio",
  &gtEfiDiskIoProtocolGuid,            L"diskio",
  &gtEfiSimpleFileSystemProtocolGuid,  L"fs",
  &gtEfiLoadFileProtocolGuid,          L"load",
  &gtEfiDeviceIoProtocolGuid,          L"DevIo",

  &tGenericFileInfo,                   L"GenFileInfo",
  &gtEfiFileSystemInfoGuid,            L"FileSysInfo",

  &gtEfiUnicodeCollationProtocolGuid,  L"UnicodeCollation",
  &gtEfiSerialIoProtocolGuid,          L"serialio",
  &gtEfiSimpleNetworkProtocolGuid,     L"net",
  &gtEfiNetworkInterfaceIdentifierProtocolGuid,    L"nii",
  &gtEfiPxeBaseCodeProtocolGuid,       L"pxebc",
  &gtEfiPxeCallbackProtocolGuid,       L"pxecb",

  &tPcAnsiProtocol,            L"PcAnsi",
  &tVt100Protocol,             L"Vt100",
  &gtEfiUnknownDeviceGuid,             L"Unknown Device",

  &gtEfiPartTypeSystemPartitionGuid,    L"ESP",
  &gtEfiPartTypeLegacyMbrGuid,          L"GPT MBR",

  &ShellInterfaceProtocol,    L"ShellInt",
  &SEnvId,                    L"SEnv",
  &SProtId,                   L"ShellProtId",
  &SMapId,                    L"ShellDevPathMap",
  &SAliasId,                  L"ShellAlias",

  NULL
};

EFI_LIST_ENTRY          GuidList;


INTN
CompareGuid(
  IN EFI_GUID     *Guid1,
  IN EFI_GUID     *Guid2
  )
/*++

Routine Description:

  Compares to GUIDs

Arguments:

  Guid1       - guid to compare
  Guid2       - guid to compare

Returns:
  = 0     if Guid1 == Guid2

--*/
{
  INT32       *g1, *g2, r;

  //
  // Compare 32 bits at a time
  //

  g1 = (INT32 *) Guid1;
  g2 = (INT32 *) Guid2;

  r  = g1[0] - g2[0];
  r |= g1[1] - g2[1];
  r |= g1[2] - g2[2];
  r |= g1[3] - g2[3];

  return r;
}


VOID
GuidToString (
  OUT CHAR16      *Buffer,
  IN EFI_GUID     *Guid
  )
/*++

Routine Description:

  Converts Guid to a string

Arguments:

  Buffer      - On return, a pointer to the buffer which contains the string.
  Guid        - guid to compare

Returns:
  none

--*/
{

  UINTN           Index;

  //
  // Else, (for now) use additional internal function for mapping guids
  //
  for (Index=0; KnownGuids[Index].Guid; Index++) {
    if (CompareGuid(Guid, KnownGuids[Index].Guid) == 0) {
      SPrint (Buffer, 0, KnownGuids[Index].GuidName);
      return ;
    }
  }

  //
  // Else dump it
  //
  SPrint (Buffer, 0, L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        Guid->Data1,
        Guid->Data2,
        Guid->Data3,
        Guid->Data4[0],
        Guid->Data4[1],
        Guid->Data4[2],
        Guid->Data4[3],
        Guid->Data4[4],
        Guid->Data4[5],
        Guid->Data4[6],
        Guid->Data4[7]
        );
}
