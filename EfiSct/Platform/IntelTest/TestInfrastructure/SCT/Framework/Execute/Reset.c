/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Reset.c

Abstract:

  This file provides the services to deal with the system reset, the test
  execution reset, and so on.

--*/

#include "Sct.h"
#include "ExecuteSupport.h"

//
// Internal functions declaration
//

EFI_STATUS
RemoveMetaFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN CHAR16                       *MetaName
  );

EFI_STATUS
RemoveFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  );


//
// External functions implementation
//

EFI_STATUS
RemoveRecoveryFile (
  VOID
  )
/*++

Routine Description:

  Remove the recovery file.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the name of recovery file
  //
  FileName = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_RECOVERY);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Remove it
  //
  Status = RemoveFile (gFT->DevicePath, FileName);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove file - %r", Status));
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetAllTestResults (
  VOID
  )
/*++

Routine Description:

  Reset all test results, including the recovery file, the test results of
  test cases, and the test log files.

  It is used to clean up all test information.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;
  CHAR16      *FilePath;

  //
  // Reset the order and test results of all test case
  //
  Status = ResetTestCaseOrderAndResults ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order and results - %r", Status));
    return Status;
  }

  //
  // Save the test cases
  //
  FileName = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_TEST_CASE);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = SaveTestCases (
             gFT->DevicePath,
             FileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Remove the recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove recovery file - %r", Status));
    return Status;
  }

  //
  // Remove the log files
  //
  FilePath = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_LOG);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RemoveMetaFiles (
             gFT->DevicePath,
             FilePath,
             L"*"                     // All files
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove meta files - %r", Status));
    BS->FreePool (FilePath);
    return Status;
  }

  BS->FreePool (FilePath);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetExecuteTestResults (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Reset the test results of test cases to be executed.

  It is used to prepare the test environment for the next execution.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  CHAR16                *FileName;
  CHAR16                *FilePath;
  CHAR16                *MetaName;
  CHAR16                *TempName;

  //
  // Set the running state
  //
  ExecuteInfo->TestCase->Passes   = EFI_SCT_TEST_CASE_RUNNING;
  ExecuteInfo->TestCase->Failures = EFI_SCT_TEST_CASE_RUNNING;

  //
  // Save the test cases
  //
  FileName = PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_TEST_CASE);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = SaveTestCases (
             gFT->DevicePath,
             FileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR(Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    BS->FreePool (FileName);
    return Status;
  }

  BS->FreePool (FileName);

  //
  // Remove the recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove recovery file - %r", Status));
    return Status;
  }

  //
  // Remove the log files
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get test meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta name with wildcard character '*'
  //
  TempName = PoolPrint (MetaName, L"*", L"*", L"*");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"PoolPrint: Out of resource"));
    BS->FreePool (FilePath);
    BS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  BS->FreePool (MetaName);

  //
  // Remove the log and key files
  //
  Status = RemoveMetaFiles (
             gFT->DevicePath,
             FilePath,
             TempName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove meta files - %r", Status));
    BS->FreePool (FilePath);
    BS->FreePool (TempName);
    return Status;
  }

  BS->FreePool (FilePath);
  BS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
RemoveMetaFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN CHAR16                       *MetaName
  )
/*++

Routine Description:

  Remove meta files (with wildcard characters in file name).

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  EFI_FILE_HANDLE                   ChildHandle;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  CHAR16                            *SubDir;
  EFI_DEVICE_PATH_PROTOCOL          *RemainderDevicePath;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath == NULL) || (MetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Locate the device handle from the device path
  //
  RemainderDevicePath = DevicePath;

  Status = BS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainderDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Locate system volume from the device handle
  //
  Status = BS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 &Vol
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FilePath,
                      EFI_FILE_MODE_READ,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR(Status)) {
    //
    // Not found, misson complete!
    //
    RootDir->Close (RootDir);
    return EFI_SUCCESS;
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
  if (EFI_ERROR(Status)) {
    Handle->Close (Handle);
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

    Status = Handle->Read (
                       Handle,
                       &FileInfoSize,
                       FileInfo
                       );
    if (EFI_ERROR(Status) || (FileInfoSize == 0)) {
      break;
    }

    //
    // Skip the '.' and '..'
    //
    if ((StrCmp (FileInfo->FileName, L".")  == 0) ||
        (StrCmp (FileInfo->FileName, L"..") == 0)) {
      continue;
    }

    if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) != 0) {
      //
      // It is a directory
      //
      SubDir = PoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);

      Status = RemoveMetaFiles (
                 DevicePath,
                 SubDir,
                 MetaName
                 );
      if (EFI_ERROR(Status)) {
        BS->FreePool (SubDir);
        continue;
      }

      BS->FreePool (SubDir);
    }

    //
    // Remove the file or the directory
    //
    if (MetaiMatch (FileInfo->FileName, MetaName)) {
      Status = Handle->Open (
                         Handle,
                         &ChildHandle,
                         FileInfo->FileName,
                         EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                         0
                         );
      if (EFI_ERROR(Status)) {
        continue;
      }

      Status = ChildHandle->Delete (ChildHandle);
      if (Status != EFI_SUCCESS) {
        //
        // NOTE: A warning status will be returned from Delete()
        //
        continue;
      }
    }
  }

  //
  // Free resources
  //
  BS->FreePool (FileInfo);
  Handle->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
RemoveFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Remove a file.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  EFI_DEVICE_PATH_PROTOCOL          *RemainderDevicePath;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // locate the device handle from the device path
  //
  RemainderDevicePath = DevicePath;

  Status = BS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainderDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Locate system volume from the device handle
  //
  Status = BS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 &Vol
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      0
                      );
  if (Status == EFI_NOT_FOUND) {
    //
    // Not found, misson complete!
    //
    RootDir->Close (RootDir);
    return EFI_SUCCESS;
  }

  //
  // Delete the file
  //
  Status = Handle->Delete (Handle);
  if (Status != EFI_SUCCESS) {
    //
    // NOTE: A warning status will be returned from Delete()
    //
    RootDir->Close (RootDir);
    return EFI_UNSUPPORTED;
  }

  //
  // Close the root directory
  //
  RootDir->Close (RootDir);

  //
  // Done
  //
  return EFI_SUCCESS;
}
