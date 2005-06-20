/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  salpal.c

Abstract:

  Functions to make SAL and PAL proc calls

--*/

#include "lib.h"
#include "Libsalpal.h"


SAL_PROC                        mSalProc;
EFI_PLABEL                      mSalProcPlabel;
PAL_PROC                        mPalProc;
EFI_PLABEL                      mPalProcPlabel;
SAL_SYSTEM_TABLE_HEADER         *mSalSystemTable;
BOOLEAN                         SalPalLibInitialized=FALSE;


EFI_STATUS
LibInitSalAndPalProc (
  VOID
    )
{
  SAL_ST_ENTRY_POINT_DESCRIPTOR       *SalEpDesc;
  EFI_PLABEL                          *PlabelPtr;
  UINT8                               Checksum;
  UINT8                               *TableByte;
  UINTN                               Offset;
  EFI_STATUS                          Status;

  if (!SalPalLibInitialized) {
    SalPalLibInitialized = TRUE;
    mSalProc = NULL;
    mPalProc = NULL;
    mSalSystemTable = NULL;


    Status = LibGetSystemConfigurationTable(&gtEfiSalSystemTableGuid, (VOID **)(&mSalSystemTable));
    if (EFI_ERROR(Status)) {
      Print(L"Error : Sal System Table NOT found\r\n");
      return EFI_SUCCESS;
    }


    //
    // Check signature, number of entries and size. Then checksum the table.
    //

    if ( ((CompareMem(&mSalSystemTable->Signature, EFI_SAL_ST_HEADER_SIGNATURE, 4)) != 0) &&
         (mSalSystemTable->EntryCount == 0) &&
         (mSalSystemTable->Length == 0)) {
      return EFI_SUCCESS;
    }


    TableByte = (UINT8 *)mSalSystemTable;
    Checksum = 0;
    for (Offset=0;Offset<mSalSystemTable->Length;Offset++, TableByte++) {
      Checksum = Checksum + *TableByte;
    }

    if (Checksum !=0) {
      Print(L"Error : Sal System Table checksum is invalid\r\n");
      return EFI_SUCCESS;
    }

    SalEpDesc = NULL;
    SalEpDesc = (SAL_ST_ENTRY_POINT_DESCRIPTOR *) LibSearchSalSystemTable (EFI_SAL_ST_ENTRY_POINT);

    if (SalEpDesc == NULL) {
      Print(L"Error : Sal entry point not found\r\n");
      return EFI_SUCCESS;
    }

    mSalProcPlabel.EntryPoint  = SalEpDesc->SalProcEntry;
    mSalProcPlabel.GP          = SalEpDesc->SalGlobalDataPointer;
    PlabelPtr                  = &mSalProcPlabel;
    mSalProc                   = *(SAL_PROC *) (&PlabelPtr);

    if ( (mSalProc == NULL) || (mSalProcPlabel.EntryPoint == 0) ) {
      Print(L"Error : Sal entry point invalid\r\n");
      return EFI_SUCCESS;
    }


    mPalProcPlabel.EntryPoint = SalEpDesc->PalProcEntry;
    mPalProcPlabel.GP         = SalEpDesc->SalGlobalDataPointer;
    PlabelPtr                 = &mPalProcPlabel;
    mPalProc                  = *(PAL_PROC *) (&PlabelPtr);

    if (mPalProcPlabel.EntryPoint == 0) {
      Print(L"Error : PAL entry point invalid\r\n");
      return EFI_SUCCESS;
    }
  }

    return EFI_SUCCESS;
}


EFI_STATUS
LibGetSalVersionInfo (
  IN  OUT   UINT16  *SalSpecRev,
  IN  OUT   UINT16  *SalARev,
  IN  OUT   UINT16  *SalBRev
)
{
  if( mSalSystemTable == NULL) {
    return EFI_UNSUPPORTED;
  }

  *SalSpecRev = mSalSystemTable->SalRevision;
  *SalARev    = mSalSystemTable->SalAVersion;
  *SalBRev    = mSalSystemTable->SalBVersion;
  return  EFI_SUCCESS;
}





EFI_STATUS
LibGetSalIoPortMapping (
    OUT UINT64  *IoPortMapping
    )
/*++

  Get the IO Port Map from the SAL System Table.

--*/
{
  SAL_ST_MEMORY_DESCRIPTOR_ENTRY      *SalMemDesc;

  SalMemDesc = (SAL_ST_MEMORY_DESCRIPTOR_ENTRY *) LibSearchSalSystemTable (EFI_SAL_ST_MEMORY_DESCRIPTOR);

  if(SalMemDesc == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (SalMemDesc->Type == EFI_SAL_ST_MEMORY_DESCRIPTOR) {
    if (SalMemDesc->MemoryType == SAL_IO_PORT_MAPPING) {
      *IoPortMapping = SalMemDesc->PhysicalMemoryAddress;
      return EFI_SUCCESS;
    }
   SalMemDesc++;
  }
  return EFI_UNSUPPORTED;
}

EFI_STATUS
LibGetSalIpiBlock (
    OUT UINT64  *IpiBlock
    )
/*++

  Get the IPI block from the SAL system table

--*/
{
  SAL_ST_MEMORY_DESCRIPTOR_ENTRY      *SalMemDesc;

  SalMemDesc = (SAL_ST_MEMORY_DESCRIPTOR_ENTRY *) LibSearchSalSystemTable (EFI_SAL_ST_MEMORY_DESCRIPTOR);

  if(SalMemDesc == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (SalMemDesc->Type == EFI_SAL_ST_MEMORY_DESCRIPTOR) {
    if (SalMemDesc->MemoryType == SAL_SAPIC_IPI_BLOCK) {
      *IpiBlock = SalMemDesc->PhysicalMemoryAddress;
      return EFI_SUCCESS;
    }
    SalMemDesc++;
  }
  return EFI_UNSUPPORTED;
}

EFI_STATUS
LibGetSalWakeupVector (
    OUT UINT64  *WakeVector
    )
/*++

Get the wakeup vector from the SAL system table

--*/
{
    SAL_ST_AP_WAKEUP_DECRIPTOR      *ApWakeUp;

    ApWakeUp = (SAL_ST_AP_WAKEUP_DECRIPTOR *) LibSearchSalSystemTable (EFI_SAL_ST_AP_WAKEUP);
    if (!ApWakeUp) {
        return EFI_UNSUPPORTED;
    }
    *WakeVector = ApWakeUp->ExternalInterruptVector;
    return EFI_SUCCESS;
}

VOID *
LibSearchSalSystemTable (
    IN  UINT8   EntryType
    )
{

    UINT8                               *SalTableHack;
    UINT16                              EntryCount;
    UINT16                              Count;


    if (mSalSystemTable == NULL) {
        return NULL;
    }


    EntryCount = mSalSystemTable->EntryCount;
    if (EntryCount == 0) {
        return NULL;
    }

    //
    // BugBug: Add code to test checksum on the Sal System Table
    //

    SalTableHack = (UINT8 *)mSalSystemTable;
    SalTableHack += sizeof (SAL_SYSTEM_TABLE_HEADER);

    for (Count = 0; Count < EntryCount ;Count++) {
        if (*SalTableHack == EntryType) {
            return (VOID *)SalTableHack;
        }
        switch (*SalTableHack) {
        case EFI_SAL_ST_ENTRY_POINT:
            SalTableHack += sizeof (SAL_ST_ENTRY_POINT_DESCRIPTOR);
            break;
        case EFI_SAL_ST_MEMORY_DESCRIPTOR:
            SalTableHack += sizeof (SAL_ST_MEMORY_DESCRIPTOR_ENTRY);
            break;
        case EFI_SAL_ST_PLATFORM_FEATURES:
            SalTableHack += sizeof (SAL_ST_PLATFORM_FEATURES);
            break;
        case EFI_SAL_ST_TR_USAGE:
            SalTableHack += sizeof (SAL_ST_TR_DECRIPTOR);
            break;
        case EFI_SAL_ST_PTC:
            SalTableHack += sizeof (SAL_ST_CACHE_COHERENCE_DECRIPTOR);
            break;
        case EFI_SAL_ST_AP_WAKEUP:
            SalTableHack += sizeof (SAL_ST_AP_WAKEUP_DECRIPTOR);
            break;
        default:
            ASSERT(FALSE);
            break;
        }
    }
    return NULL;
}


SAL_RETURN_REGS
LibSalProc (
    IN  UINT64    Arg1,
    IN  UINT64    Arg2,
    IN  UINT64    Arg3,
    IN  UINT64    Arg4,
    IN  UINT64    Arg5,
    IN  UINT64    Arg6,
    IN  UINT64    Arg7,
    IN  UINT64    Arg8
    )
{
    return mSalProc(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);
}

