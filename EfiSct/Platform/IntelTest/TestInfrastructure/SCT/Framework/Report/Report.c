/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Report.c

Abstract:

  Description

--*/

/**
 *  Report generation services.
 */
/*++

Copyright (c)  1999 - 2004 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  Report.c

Abstract:

  This file provides the test report generation services.

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// External functions implemenation
//

EFI_STATUS
GetInstanceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *MetaName,
  OUT EFI_SCT_LOG_STATE           *FileState,
  OUT UINT32                      *Index,
  OUT UINT32                      *Iteration,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of a instance.

Arguments:

  DevicePath    - Device path of the key files.
  MetaName      - Meta name of the key files.
  FileState     - The log state.
  Index         - The index of the instance.
  Interation    - The index of the iteration.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;
  UINT32      InstanceIndex;
  UINT32      IterationIndex;
  UINTN       BufferSize;
  CHAR16      *Buffer;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (MetaName   == NULL) ||
      (FileState  == NULL) || (Index      == NULL) ||
      (Iteration  == NULL) || (PassNumber == NULL) ||
      (WarnNumber == NULL) || (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  *FileState  = EFI_SCT_LOG_STATE_UNKNOWN;
  *Index      = 0;
  *Iteration  = 0;
  *PassNumber = 0;
  *WarnNumber = 0;
  *FailNumber = 0;

  InstanceIndex  = 0;
  IterationIndex = 0;

  //
  // Found the maximum index of instance and iteration
  //
  for (InstanceIndex = 0; TRUE; InstanceIndex ++) {
    for (IterationIndex = 0; TRUE; IterationIndex ++) {
      FileName = PoolPrint (MetaName, InstanceIndex, IterationIndex);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      if (!FileExist (DevicePath, FileName)) {
        //
        // File does not exist
        //
        if (IterationIndex != 0) {
          *Index     = InstanceIndex;
          *Iteration = IterationIndex - 1;
        }

        BS->FreePool (FileName);
        break;
      }

      BS->FreePool (FileName);
    }

    if (IterationIndex == 0) {
      break;
    }
  }

  //
  // No instance file is found
  //
  if ((InstanceIndex == 0) && (IterationIndex == 0)) {
    *FileState = EFI_SCT_LOG_STATE_EMPTY;
    *Index     = 0;
    *Iteration = 0;
    return EFI_SUCCESS;
  }

  //
  // The maximum instance index is found
  //
  FileName = PoolPrint (MetaName, *Index, *Iteration);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Read the file to a buffer
  //
  Status = ReadFileToBuffer (
             DevicePath,
             FileName,
             &BufferSize,
             &Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file to buffer - %r", Status));
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Load the buffer to the GUID assertion table with duplicate
  //
  Status = LoadGuidAssertion (Buffer, TRUE, FileState);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID assertion - %r", Status));
    BS->FreePool (Buffer);
    return Status;
  }

  BS->FreePool (Buffer);

  //
  // Get the assertion number (free the GUID assertion table)
  //
  Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get assertion number - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetInterfaceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *MetaName,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of an interface.

Arguments:

  DevicePath    - Device path of the key files.
  MetaName      - Meta name of the key files.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS          Status;
  CHAR16              *FileName;
  UINT32              InstanceIndex;
  UINT32              IterationIndex;
  UINTN               BufferSize;
  CHAR16              *Buffer;
  EFI_SCT_LOG_STATE   FileState;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (MetaName   == NULL) ||
      (PassNumber == NULL) || (WarnNumber == NULL) ||
      (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  *PassNumber = 0;
  *WarnNumber = 0;
  *FailNumber = 0;

  //
  // For each instance file
  //
  for (InstanceIndex = 0; TRUE; InstanceIndex ++) {
    for (IterationIndex = 0; TRUE; IterationIndex ++) {
      FileName = PoolPrint (MetaName, InstanceIndex, IterationIndex);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      if (!FileExist (DevicePath, FileName)) {
        //
        // File does not exist
        //
        BS->FreePool (FileName);
        break;
      }

      //
      // Read the file to a buffer
      //
      Status = ReadFileToBuffer (
                 DevicePath,
                 FileName,
                 &BufferSize,
                 &Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Read file to buffer - %r", Status));
        BS->FreePool (FileName);
        return Status;
      }

      BS->FreePool (FileName);

      //
      // Load the buffer to the GUID assertion table without duplicate
      //
      Status = LoadGuidAssertion (Buffer, FALSE, &FileState);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID assertion - %r", Status));
        BS->FreePool (Buffer);
        return Status;
      }

      BS->FreePool (Buffer);

      //
      // Get the assertion number (free the GUID assertion table)
      //
      Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get assertion number - %r", Status));
        return Status;
      }
    }

    if (IterationIndex == 0) {
      break;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetProtocolAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  OUT UINT32                      *PassNumber,
  OUT UINT32                      *WarnNumber,
  OUT UINT32                      *FailNumber
  )
/*++

Routine Description:

  Get the assertion number of a protocol or service.

Arguments:

  DevicePath    - Device path of the key files.
  FilePath      - Path of the key files.
  PassNumber    - The number of passed assertions.
  WarnNumber    - The number of warning assertions.
  FailNumber    - The number of failed assertions.

Returns:

  EFI_SUCCESS   - Get instance assertion number successfully.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   LogDir;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath;
  UINTN                             BufferSize;
  CHAR16                            *Buffer;
  CHAR16                            *FileName;
  CHAR16                            *LogName;
  CHAR16                            *TempName;
  CHAR16                            *CaseIndexStr;
  CHAR16                            *CaseIterationStr;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath   == NULL) ||
      (PassNumber == NULL) || (WarnNumber == NULL) ||
      (FailNumber == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Locate the device handle
  //
  RemainingDevicePath = DevicePath;
  Status = BS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainingDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate device path - %r", Status));
    return Status;
  }

  //
  // Locate the simple file system
  //
  Status = BS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 &Vol
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Handle protocol - %r", Status));
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open volume - %r", Status));
    return Status;
  }

  //
  // Open the log directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &LogDir,
                      FilePath,
                      EFI_FILE_MODE_READ,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open directory - %r", Status));
    RootDir->Close (RootDir);
    return Status;
  }

  RootDir->Close (RootDir);

  //
  // Allocate memory for the entries in the directory
  //
  FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 FileInfoSize,
                 &FileInfo
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    LogDir->Close (LogDir);
    return Status;
  }

  //
  // Walk through each file in the directory
  //
  while (TRUE) {
    //
    // Read a file entry
    //
    FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

    Status = LogDir->Read (
                       LogDir,
                       &FileInfoSize,
                       FileInfo
                       );
    if (EFI_ERROR (Status) || (FileInfoSize == 0)) {
      break;
    }

    if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) == 0) {
      //
      // This is a file
      //

      //
      // Only deal with the EFI key file
      //
      if (!SctStrEndWith (FileInfo->FileName, L".ekl")) {
        continue;
      }

      //
      // Read the file to a buffer
      //
      FileName = PoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      Status = ReadFileToBuffer (
                 DevicePath,
                 FileName,
                 &BufferSize,
                 &Buffer
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Read file to buffer - %r", Status));
        BS->FreePool (FileName);
        continue;
      }

      BS->FreePool (FileName);

      //
      // Get the index and iteration from the file name
      //
      TempName = StrDuplicate (FileInfo->FileName);

      //
      // The following function didn't allocate memory for CaseIndexStr and
      // CaseIterationStr. So DON'T free the TempName before these two strings
      // are still used.
      //
      Status = GetIndexFromFileName (
                 TempName,
                 &CaseIndexStr,
                 &CaseIterationStr
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get index from file name - %r", Status));
        BS->FreePool (TempName);
        continue;
      }

      //
      // Load the buffer to the report information structure
      //
      LogName = SctStrEndReplace (FileInfo->FileName, L"log");

      Status = LoadReportInfor (
                 CaseIndexStr,
                 CaseIterationStr,
                 Buffer,
                 LogName
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Load report infor - %r", Status));
        BS->FreePool (TempName);
        BS->FreePool (LogName);
        BS->FreePool (Buffer);
        continue;
      }

      BS->FreePool (TempName);
      BS->FreePool (LogName);
      BS->FreePool (Buffer);

      //
      // Get the assertion number (free the GUID assertion table)
      //
      Status = GetAssertionNumber (PassNumber, WarnNumber, FailNumber);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get assertion number - %r", Status));
        continue;
      }

    } else {
      //
      // This is a directory
      //

      //
      // Skip the '.' and '..' dir
      //
      if ((StrCmp (FileInfo->FileName, L".")  == 0) ||
          (StrCmp (FileInfo->FileName, L"..") == 0)) {
        continue;
      }

      //
      // Get the report information from the sub directories
      //
      FileName = PoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
      if (FileName == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
        return EFI_OUT_OF_RESOURCES;
      }

      Status = GetProtocolAssertion (
                 DevicePath,
                 FileName,
                 PassNumber,
                 WarnNumber,
                 FailNumber
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get protocol assertion - %r", Status));
        BS->FreePool (FileName);
        continue;
      }

      BS->FreePool (FileName);
    }
  }

  //
  // Free resources
  //
  BS->FreePool (FileInfo);
  LogDir->Close (LogDir);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GenerateReport (
  IN EFI_DEVICE_PATH_PROTOCOL     *LogDevicePath,
  IN CHAR16                       *LogFilePath,
  IN EFI_DEVICE_PATH_PROTOCOL     *ReportDevicePath,
  IN CHAR16                       *ReportFileName
  )
/*++

Routine Description:

  Generate test report.

Arguments:

  LogDevicePath     - Device path of the key files.
  LogFilePath       - Path of the key files.
  ReportDevicePath  - Device path of the report file.
  ReportFileName    - Name of the report file.

  EFI_SUCCESS       - Generate the test report successfully.

--*/
{
  EFI_STATUS        Status;
  UINT32            PassNumber;
  UINT32            WarnNumber;
  UINT32            FailNumber;
  CHAR16            *FileName;
  CHAR16            *Buffer;
  UINTN             AsciiBufferSize;
  CHAR8             *AsciiBuffer;
  UINTN             ConfigBufferSize;
  CHAR8             *ConfigBuffer;
  EFI_FILE_HANDLE   Handle;

  //
  // Check parameters
  //
  if ((LogDevicePath    == NULL) || (LogFilePath    == NULL) ||
      (ReportDevicePath == NULL) || (ReportFileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  PassNumber = 0;
  WarnNumber = 0;
  FailNumber = 0;

  //
  // Get the configuration data. Start this operation at first since the next
  //  operations will take more time. We could stop the entire process if we
  //  meet any problem in configuration collection.
  //
  Status = SctReportConfig (
             &ConfigBufferSize,
             &ConfigBuffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctReportConfig: %r", Status));
    return Status;
  }

  //
  // Load the GUID database
  //
  FileName = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_GUID_DATABASE);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (ConfigBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = LoadGuidDatabase (gFT->DevicePath, FileName);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load GUID database - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Load the assertion information from the log directory
  //
  Status = GetProtocolAssertion (
             LogDevicePath,
             LogFilePath,
             &PassNumber,
             &WarnNumber,
             &FailNumber
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get protocol assertion - %r", Status));
    BS->FreePool (ConfigBuffer);
    UnloadGuidDatabase ();
    UnloadReportInfor ();
    return Status;
  }

  //
  // Get the report information to a buffer
  //
  Status = GetReportInfor (&Buffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get report infor - %r", Status));
    BS->FreePool (ConfigBuffer);
    UnloadGuidDatabase ();
    UnloadReportInfor ();
    return Status;
  }

  UnloadGuidDatabase ();
  UnloadReportInfor ();

  //
  // Convert the buffer to ASCII buffer
  //
  AsciiBufferSize = StrLen(Buffer) + 1;

  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 AsciiBufferSize,
                 &AsciiBuffer
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (Buffer);
    return Status;
  }

  Status = UnicodeToAscii (Buffer, AsciiBuffer);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Convert Unicode to ASCII - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (Buffer);
    BS->FreePool (AsciiBuffer);
    return Status;
  }

  BS->FreePool (Buffer);

  //
  // Create the report file
  //
  Status = SctCreateFileFromDevicePath (
             ReportDevicePath,
             ReportFileName,
             &Handle
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create report file - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (AsciiBuffer);
    return Status;
  }

  //
  // Write the ASCII buffer to the report file (remove the null-terminator)
  //
  AsciiBufferSize --;

  Status = Handle->Write (
                     Handle,
                     &AsciiBufferSize,
                     AsciiBuffer
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Write report file - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (AsciiBuffer);
    Handle->Close (Handle);
    return Status;
  }

  //
  // Write the config buffer to the report file
  //
  Status = Handle->Write (
                     Handle,
                     &ConfigBufferSize,
                     ConfigBuffer
                     );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Write report file - %r", Status));
    BS->FreePool (ConfigBuffer);
    BS->FreePool (AsciiBuffer);
    Handle->Close (Handle);
    return Status;
  }

  BS->FreePool (ConfigBuffer);
  BS->FreePool (AsciiBuffer);

  //
  // Close the report file
  //
  Handle->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}
