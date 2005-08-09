/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ReportConfig.c

Abstract:

  Reports the system under test configuration.

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// External function implatmentation
//

EFI_STATUS
SctReportConfig (
  OUT UINTN               *BufferSize,
  OUT UINT8               **Buffer
  )
/*++

Routine Description:

  Report the system configuration via shell commands.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *CmdLine;
  CHAR16      *FileName;
  CHAR16      *CmdList[] = {
                L"map -v",
                L"memmap",
                L"pci",
                L"ver",
                L"dh -v",
                L""
              };

  //
  // Record an empty line to a file via shell command
  //

  CmdLine = PoolPrint (
              L"ECHO \" \" >a %s",
              EFI_SCT_FILE_CFG
              );
  if (CmdLine == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = ShellExecute (
             gFT->ImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"ShellExecute: %s - %r", CmdLine, Status));
    BS->FreePool (CmdLine);
    return Status;
  }

  BS->FreePool (CmdLine);

  //
  // For each shell command
  //

  for (Index = 0; CmdList[Index][0] != L'\0'; Index++) {

    //
    // Record the command to a file via shell command
    //

    CmdLine = PoolPrint (
                L"ECHO \"%s\" >>a %s",
                CmdList[Index],
                EFI_SCT_FILE_CFG
                );
    if (CmdLine == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    Status = ShellExecute (
               gFT->ImageHandle,
               CmdLine,
               FALSE
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"ShellExecute: %s - %r", CmdLine, Status));
      BS->FreePool (CmdLine);
      return Status;
    }

    BS->FreePool (CmdLine);

    //
    // Get the system configuration to a file via shell command
    //

    CmdLine = PoolPrint (
                L"%s >>a %s",
                CmdList[Index],
                EFI_SCT_FILE_CFG
                );
    if (CmdLine == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    Status = ShellExecute (
               gFT->ImageHandle,
               CmdLine,
               FALSE
               );
    if (EFI_ERROR (Status)) {
      //
      // Just record as a debug info. It is acceptable for this command return
      //  an error status
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"ShellExecute: %s - %r", CmdLine, Status));
    }

    BS->FreePool (CmdLine);
  }

  //
  // Get the system configuration from the file
  //

  FileName = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CFG
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = ReadFileToBuffer (
             gFT->DevicePath,
             FileName,
             BufferSize,
             Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"ReadFileToBuffer: %s - %r", FileName, Status));
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}
