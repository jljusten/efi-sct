/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Output.c

Abstract:

  This file provides a default test output library.

--*/

#include "Sct.h"

//
// Prototypes of test output interfaces
//

EFI_STATUS
EFIAPI
TOLOpen (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FileName,
  IN BOOLEAN                                OverwriteFile,
  OUT EFI_FILE                              **FileHandle
  );

EFI_STATUS
EFIAPI
TOLClose (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_FILE                               *FileHandle
  );

EFI_STATUS
EFIAPI
TOLWrite (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_FILE                               *FileHandle,
  IN CHAR16                                 *String
  );

//
// Test output interface private data
//

TEST_OUTPUT_PRIVATE_DATA gOutputPrivate = {
  TEST_OUTPUT_PRIVATE_DATA_SIGNATURE,
  {
    TEST_OUTPUT_PRIVATE_DATA_REVISION,
    L"Test Output Library",
    L"EFI SCT Test Support Library",
    TOLOpen,
    TOLClose,
    TOLWrite
  },
  NULL
};

EFI_TEST_OUTPUT_LIBRARY_PROTOCOL *gOutputProtocol = &gOutputPrivate.TestOutput;

//
// Implementation
//

EFI_STATUS
EFIAPI
TOLOpen (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FileName,
  IN BOOLEAN                                OverwriteFile,
  OUT EFI_FILE                              **FileHandle
  )
/*++

Routine Description:

  One interface function of the TestOutputLibrary to open a file.

Arguments:

  This                  - the protocol instance structure.
  DevicePath            - the file's root device path.
  FileName              - the file's name relative to the root.
  OverwriteFile         - whether to overwrite the file.
  FileHandle            - return the file's handle.

Returns:

  EFI_SUCCESS           - open the file successfully.
  EFI_NOT_READY         - to overwrite an opened file is not allowed.
  EFI_OUT_OF_RESOURCES  - not enough memory.

--*/
{
  EFI_STATUS                        Status;
  TEST_OUTPUT_FILE                  *OutputFile;
  TEST_OUTPUT_PRIVATE_DATA          *Private;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  UINTN                             BufSize;
  CHAR8                             Buffer[2];
  EFI_DEVICE_PATH_PROTOCOL          *PreDevicePath;

  Private = TEST_OUTPUT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Search the file in OutputFileList to see whether the file has been opened
  //
  OutputFile = Private->OutputFileList;
  while (OutputFile != NULL) {
    if ((SctDevicePathCompare (DevicePath, OutputFile->DevicePath) == 0) &&
        (StrCmp (FileName, OutputFile->FileName)                   == 0)) {
      break;
    }
    OutputFile = OutputFile->Next;
  }

  if (OutputFile == NULL) {
    //
    // Not found, open the file and add to the list
    //

    PreDevicePath = DevicePath;
    //
    //  Determine device handle for fs protocol on specified device path
    //
    Status = BS->LocateDevicePath (
                   &gEfiSimpleFileSystemProtocolGuid,
                   &PreDevicePath,
                   &DeviceHandle
                   );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    //  Determine volume for file system on device handle
    //
    Status = BS->HandleProtocol (
                   DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID*)&Vol
                   );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Open volume for file system on device path
    //
    Status = Vol->OpenVolume (Vol, &RootDir);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Determine the existence of the file
    //
    Status = RootDir->Open (
                        RootDir,
                        &Handle,
                        FileName,
                        EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                        0
                        );
    if (Status == EFI_NOT_FOUND) {
      //
      // The file not exist, create it
      //
      Status = SctCreateFile (RootDir, FileName, &Handle);
      if (EFI_ERROR (Status)) {
        RootDir->Close (RootDir);
        return Status;
      }

      //
      // Write the head of Unicode text file
      //
      Buffer[0] = 0xff;
      Buffer[1] = 0xfe;
      BufSize = 2;
      Status = Handle->Write (Handle, &BufSize, Buffer);
      if (EFI_ERROR (Status)) {
        Handle->Close (Handle);
        return Status;
      }
    } else if (EFI_ERROR (Status)) {
      RootDir->Close(RootDir);
      return Status;
    }

    if (OverwriteFile) {
      //
      // Overwrite the file
      //

      //
      // Delete the file
      //
      Status = Handle->Delete (Handle);

      //
      // EFI_FILE.Delete() return a warning status
      //
      if (Status != EFI_SUCCESS) {
        RootDir->Close (RootDir);
        return EFI_UNSUPPORTED;
      }

      //
      // Recreate the file
      //
      Status = RootDir->Open (
                          RootDir,
                          &Handle,
                          FileName,
                          EFI_FILE_MODE_CREATE|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_READ,
                          0
                          );
      if (EFI_ERROR (Status)) {
        RootDir->Close (RootDir);
        return Status;
      }

      //
      // Write the head of Unicode text file
      //
      Buffer[0] = 0xff;
      Buffer[1] = 0xfe;
      BufSize = 2;
      Status = Handle->Write (Handle, &BufSize, Buffer);
      if (EFI_ERROR (Status)) {
        Handle->Close (Handle);
        return Status;
      }
    } else {
      //
      // Append the file
      //

      //
      // Set position to the end of file
      //
      Status = Handle->SetPosition (Handle, (UINT64)-1);
      if (EFI_ERROR (Status)) {
        RootDir->Close (RootDir);
        return Status;
      }
    }
    RootDir->Close (RootDir);

    //
    // Add the opened file to the OutputFileList
    //
    Status = BS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(TEST_OUTPUT_FILE),
                   (VOID **)&OutputFile
                   );
    if (EFI_ERROR (Status)) {
      Handle->Close (Handle);
      return Status;
    }
    ZeroMem (OutputFile, sizeof(TEST_OUTPUT_FILE));

    OutputFile->DevicePath = DuplicateDevicePath (DevicePath);
    if (OutputFile->DevicePath == NULL) {
      Handle->Close (Handle);
      BS->FreePool (OutputFile);
      return EFI_OUT_OF_RESOURCES;
    }
    OutputFile->FileName = StrDuplicate (FileName);
    if (OutputFile->FileName == NULL) {
      Handle->Close (Handle);
      BS->FreePool (OutputFile->DevicePath);
      BS->FreePool (OutputFile);
      return EFI_OUT_OF_RESOURCES;
    }

    OutputFile->FileHandle = Handle;
    OutputFile->Next = Private->OutputFileList;
    Private->OutputFileList = OutputFile;
  }

  //
  // Add the open count and return the file handle
  //
  OutputFile->OpenCount ++;
  *FileHandle = OutputFile->FileHandle;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TOLClose (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_FILE                               *FileHandle
  )
/*++

Routine Description:

  One interface function of the TestOutputLibrary to close a file.

Arguments:

  This          - the protocol instance structure.
  FileHandle    - the opened file's handle.

Returns:

  EFI_SUCCESS   - close the file successfully.
  EFI_NOT_FOUND - invalid FileHandle.

--*/
{
  TEST_OUTPUT_FILE                  *PrevFile;
  TEST_OUTPUT_FILE                  *OutputFile;
  TEST_OUTPUT_PRIVATE_DATA          *Private;

  Private = TEST_OUTPUT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Search the file in OutputFileList
  //
  PrevFile = NULL;
  OutputFile = Private->OutputFileList;
  while (OutputFile != NULL) {
    if (FileHandle == OutputFile->FileHandle) {
      break;
    }
    PrevFile = OutputFile;
    OutputFile = OutputFile->Next;
  }

  if (OutputFile == NULL) {
    return EFI_NOT_FOUND;
  }

  OutputFile->OpenCount --;
  if (OutputFile->OpenCount <= 0) {
    //
    // Remove the item from the OutputFileList
    //
    if (PrevFile == NULL) {
      Private->OutputFileList = OutputFile->Next;
    } else {
      PrevFile->Next = OutputFile->Next;
    }
    //
    // Delete the item
    //
    FileHandle->Close (FileHandle);
    BS->FreePool (OutputFile->DevicePath);
    BS->FreePool (OutputFile->FileName);
    BS->FreePool (OutputFile);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TOLWrite (
  IN EFI_TEST_OUTPUT_LIBRARY_PROTOCOL       *This,
  IN EFI_FILE                               *FileHandle,
  IN CHAR16                                 *String
  )
/*++

Routine Description:

  One interface function of the TestOutputLibrary to open a file.

Arguments:

  This          - the protocol instance structure.
  FileHandle    - the opened file's handle.

Returns:

  EFI_SUCCESS   - write the file successfully.
  EFI_NOT_FOUND - invalid FileHandle.

--*/
{
  EFI_STATUS                        Status;
  TEST_OUTPUT_FILE                  *OutputFile;
  TEST_OUTPUT_PRIVATE_DATA          *Private;
  UINTN                             BufSize;

  Private = TEST_OUTPUT_PRIVATE_DATA_FROM_THIS (This);

  //
  // Search the file in OutputFileList
  //
  OutputFile = Private->OutputFileList;
  while (OutputFile != NULL) {
    if (FileHandle == OutputFile->FileHandle) {
      break;
    }
    OutputFile = OutputFile->Next;
  }

  if (OutputFile == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Write the String to the file
  //
  BufSize = StrLen(String) * 2;
  Status = FileHandle->Write (FileHandle, &BufSize, String);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = FileHandle->Flush (FileHandle);

  return Status;
}
