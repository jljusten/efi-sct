/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  InstallSctSupport.c

Abstract:

  This file provides the support services for the EFI SCT installation.

--*/

#include "InstallSct.h"
#include EFI_PROTOCOL_DEFINITION (FileInfo)
#include EFI_PROTOCOL_DEFINITION (FileSystemInfo)
#include EFI_PROTOCOL_DEFINITION (FileSystemVolumeLabelInfo)

//
// External function implementation
//

EFI_STATUS
GetFreeSpace (
  IN CHAR16             *FsName,
  OUT UINT64            *FreeSpace
  )
{
  EFI_STATUS                        Status;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootFs;
  EFI_FILE_SYSTEM_INFO              *SystemInfo;
  UINTN                             SystemInfoSize;

  //
  // Get the device path of file system
  //
  DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ShellGetMap (FsName);
  if (DevicePath == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Locate the file system protocol
  //
  Status = LibDevicePathToInterface (
             &gEfiSimpleFileSystemProtocolGuid,
             DevicePath,
             &Vol
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open the file system
  //
  Status = Vol->OpenVolume (Vol, &RootFs);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system information
  //
  SystemInfoSize = SIZE_OF_EFI_FILE_SYSTEM_INFO + 100;

  SystemInfo = (EFI_FILE_SYSTEM_INFO *) AllocatePool (SystemInfoSize);
  if (SystemInfo == NULL) {
    RootFs->Close (RootFs);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RootFs->GetInfo (
                     RootFs,
                     &gEfiFileSystemInfoGuid,
                     &SystemInfoSize,
                     SystemInfo
                     );
  if (EFI_ERROR (Status)) {
    FreePool (SystemInfo);
    RootFs->Close (RootFs);
    return Status;
  }

  *FreeSpace = SystemInfo->FreeSpace;

  FreePool (SystemInfo);
  RootFs->Close (RootFs);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DirFileExist (
  IN CHAR16             *Name,
  OUT BOOLEAN           *Exist
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;

  //
  // Create command line to list the directory or file
  //
  CmdLine = PoolPrint (
              L"LS \"%s\" > NUL",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );

  if (Status == EFI_INVALID_PARAMETER) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  //
  // Exist or not?
  //
  if (EFI_ERROR (Status)) {
    *Exist = FALSE;
  } else {
    *Exist = TRUE;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateDir (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  CHAR16      *TmpName;
  UINTN       Index;
  BOOLEAN     Done;
  BOOLEAN     Exist;

  //
  // Create the temp name
  //
  TmpName = StrDuplicate (DirName);
  if (TmpName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the directory one by one layer
  //
  Done = FALSE;

  for (Index = 0; !Done; Index ++) {
    if (TmpName[Index] == L'\0') {
      Done = TRUE;
    }

    if ((TmpName[Index] == L'\\') || (TmpName[Index] == L'\0')){
      TmpName[Index] = L'\0';

      //
      // Exist or not?
      //
      Status = DirFileExist (TmpName, &Exist);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      if (Exist) {
        TmpName[Index] = L'\\';
        continue;
      }

      //
      // Create command line to create this directory
      //
      CmdLine = PoolPrint (
                  L"MKDIR \"%s\"",
                  TmpName
                  );
      if (CmdLine == NULL) {
        FreePool (TmpName);
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Execute shell command
      //
      Status = ShellExecute (
                 gImageHandle,
                 CmdLine,
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        Print (L"Error: Could not execute \"%s\"\n", CmdLine);
        FreePool (CmdLine);
        FreePool (TmpName);
        return Status;
      }

      FreePool (CmdLine);
      TmpName[Index] = L'\\';
    }
  }

  FreePool (TmpName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
RemoveDirFile (
  IN CHAR16             *Name
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;

  //
  // Create command line to delete this directory or file
  //
  CmdLine = PoolPrint (
              L"DEL -q \"%s\"",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute this shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupDirFile (
  IN CHAR16             *Name
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  CHAR16      *PathName;
  CHAR16      *FileName;
  CHAR16      *TmpName;
  UINTN       Index;
  UINTN       Length;
  BOOLEAN     Exist;

  //
  // Split to the path name and the file name
  //
  PathName = StrDuplicate (Name);
  if (PathName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (PathName);
  FileName = PathName + Length;

  for (Index = 0; Index < Length; Index ++) {
    if (PathName[Length - Index - 1] == L'\\') {
      PathName[Length - Index - 1] = L'\0';
      FileName = PathName + Length - Index;
      break;
    }
  }

  //
  // Find the latest backup number
  //
  for (Index = 0; Index < INSTALL_SCT_MAX_BACKUP; Index ++) {
    //
    // Create the backup file name
    //
    TmpName = PoolPrint (
                L"\"%s\\bak%d.%s\"",
                PathName,
                Index,
                FileName
                );
    if (TmpName == NULL) {
      FreePool (PathName);
      return EFI_OUT_OF_RESOURCES;
    }

    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      FreePool (PathName);
      return Status;
    }

    FreePool (TmpName);

    if (!Exist) {
      break;
    }
  }

  //
  // Check the latest backup number
  //
  if (Index == INSTALL_SCT_MAX_BACKUP) {
    FreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create command line to backup it
  //
  CmdLine = PoolPrint (
              L"MV \"%s\" \"%s\\bak%d.%s\"",
              Name,
              PathName,
              Index,
              FileName
              );
  if (CmdLine == NULL) {
    FreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  FreePool (PathName);

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CopyDirFile (
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName,
  IN BOOLEAN            Recursive
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  CHAR16      *PathName;
  UINTN       Index;
  UINTN       Length;

  //
  // Split to the path name
  //
  PathName = StrDuplicate (DstName);
  if (PathName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (PathName);

  for (Index = 0; Index < Length; Index ++) {
    if (PathName[Length - Index - 1] == L'\\') {
      PathName[Length - Index - 1] = L'\0';
      break;
    }
  }

  //
  // Create the parent directory
  //
  Status = CreateDir (PathName);
  if (EFI_ERROR (Status)) {
    FreePool (PathName);
    return Status;
  }

  FreePool (PathName);

  //
  // Create command line to copy it
  //
  CmdLine = PoolPrint (
              L"CP %s -q \"%s\" \"%s\"",
              Recursive ? L"-r" : L"",
              SrcName,
              DstName
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}
