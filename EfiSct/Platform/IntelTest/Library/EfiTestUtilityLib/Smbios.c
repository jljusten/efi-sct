/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Smbios.c

Abstract:

  Lib fucntions for SMBIOS. Used to get system serial number and GUID

--*/

#include "lib.h"


EFI_STATUS
LibGetSmbiosSystemGuidAndSerialNumber (
  IN  EFI_GUID    *SystemGuid,
  OUT CHAR8       **SystemSerialNumber
  )
{
  EFI_STATUS                  Status;
  SMBIOS_STRUCTURE_TABLE      *SmbiosTable;
  SMBIOS_STRUCTURE_POINTER    Smbios;
  SMBIOS_STRUCTURE_POINTER    SmbiosEnd;
  UINT16                      Index;

  Status = LibGetSystemConfigurationTable(&gtEfiSMBIOSTableGuid, (VOID **)&SmbiosTable);
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  //
  // BUGBUG: Disabled warnings 4306, converting a 32 bit pointer into a
  // 64 bit pointer. In SMBIOS tables, the addresses are 32 bit, and
  // causes warning:4306 with 64 bit pointers. Probably need a better
  // solution.
  //
#pragma warning ( disable : 4306 )

  Smbios.Hdr = (SMBIOS_HEADER *)SmbiosTable->TableAddress;

  SmbiosEnd.Raw = (UINT8 *)(SmbiosTable->TableAddress + SmbiosTable->TableLength);
  for (Index = 0; Index < SmbiosTable->TableLength ; Index++) {
    if (Smbios.Hdr->Type == 1) {
      if (Smbios.Hdr->Length < 0x19) {
        //
        // Older version did not support Guid and Serial number
        //
        continue;
      }

      //
      // SMBIOS tables are byte packed so we need to do a byte copy to
      //  prevend alignment faults on Itanium-based platform.
      //
      CopyMem (SystemGuid, &Smbios.Type1->Uuid, sizeof(EFI_GUID));
      *SystemSerialNumber = LibGetSmbiosString(&Smbios, Smbios.Type1->SerialNumber);
      return EFI_SUCCESS;
    }

    //
    // Make Smbios point to the next record
    //
    LibGetSmbiosString (&Smbios, (UINT16)(-1));

    if (Smbios.Raw >= SmbiosEnd.Raw) {
      //
      // SMBIOS 2.1 incorrectly stated the length of SmbiosTable as 0x1e.
      //  given this we must double check against the lenght of
      /// the structure. My home PC has this bug.ruthard
      //
      return EFI_SUCCESS;
    }
  }

  return EFI_SUCCESS;
}

CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  )
/*++

  Return SMBIOS string given the string number.

  Arguments:
      Smbios - Pointer to SMBIOS structure
      StringNumber - String number to return. -1 is used to skip all strings and
          point to the next SMBIOS structure.

  Returns:
      Pointer to string, or pointer to next SMBIOS strcuture if StringNumber == -1
--*/
{
  UINT16  Index;
  CHAR8   *String;

  //
  // Skip over formatted section
  //
  String = (CHAR8 *)(Smbios->Raw + Smbios->Hdr->Length);

  //
  // Look through unformated section
  //
  for (Index = 1; Index <= StringNumber; Index++) {
    if (StringNumber == Index) {
      return String;
    }

    //
    // Skip string
    //
    for (; *String != 0; String++);
    String++;

    if (*String == 0) {
      //
      // If double NULL then we are done.
      //  Retrun pointer to next structure in Smbios.
      //  if you pass in a -1 you will always get here
      //
      Smbios->Raw = (UINT8 *)++String;
      return NULL;
    }
  }
  return NULL;
}
#pragma warning ( default : 4306 )
