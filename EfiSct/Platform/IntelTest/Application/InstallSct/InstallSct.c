/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  InstallSct.c

Abstract:

  The EFI SCT installation.

--*/

#include "InstallSct.h"

//
// Global variables
//

EFI_HANDLE gImageHandle = NULL_HANDLE;

//
// Internal function declarations
//

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
GetDestination (
  OUT CHAR16            **DirName
  );

EFI_STATUS
BackupTests (
  IN CHAR16             *DirName
  );

EFI_STATUS
BackupStartups (
  IN CHAR16             *DirName
  );

EFI_STATUS
InstallTest (
  IN CHAR16             *DirName
  );

EFI_STATUS
InstallStartup (
  IN CHAR16             *DirName
  );

//
// Entry point
//
EFI_DRIVER_ENTRY_POINT(InstallSct)

EFI_STATUS
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;
  CHAR16      *DirName;

  //
  // Initialize library
  //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  //
  // Check parameters
  //
  if (SI->Argc != 1) {
    PrintUsage ();
    return EFI_SUCCESS;
  }

  gImageHandle = ImageHandle;

  //
  // Get the destination directory
  //
  Print (L"\nGather system information ...\n");

  Status = GetDestination (&DirName);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Remove or backup the existing tests
  //
  Print (L"\nBackup the existing tests ...\n");

  Status = BackupTests (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Remove or backup the startup files
  //
  Status = BackupStartups (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Install the EFI SCT Harness
  //
  Print (L"\nInstalling...\n");

  Status = InstallTest (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Install the startup file
  //
  Status = InstallStartup (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  FreePool (DirName);

  //
  // Done
  //
  Print (L"\nDONE!\n");
  return EFI_SUCCESS;
}


//
// Internal function implementations
//

VOID
PrintUsage (
  VOID
  )
{
  Print (
    L"Install EFI SCT Harness, Version 0.9\n"
    L"\n"
    L"Notes: Make sure the shell commands CP, DEL, MKDIR, MV, and LS are enabled.\n"
    L"       They are used in this installation.\n"
    L"\n"
    L"Usage: Install%s\n"
    L"\n",
    INSTALL_SCT_PLATFORM_SHORT_NAME
    );
}


EFI_STATUS
GetDestination (
  OUT CHAR16            **DirName
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *FsName;
  UINTN       MaxExistIndex;
  UINTN       ExistFs[INSTALL_SCT_MAX_FILE_SYSTEM];
  UINT64      FreeSpaces[INSTALL_SCT_MAX_FILE_SYSTEM];
  CHAR16      InputBuffer[4];

  //
  // Search each file system
  //
  MaxExistIndex = 0;

  for (Index = 0; Index < INSTALL_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // NOTE: Here the file system name is hard coded. I don't know how to find
    // all file system names via a shell service.
    //

    //
    // Create the name of file system
    //
    FsName = PoolPrint (L"FS%x", Index);
    if (FsName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Get free space
    //
    Status = GetFreeSpace (FsName, &FreeSpaces[Index]);
    if (EFI_ERROR (Status)) {
      FreePool (FsName);
      continue;
    }

    ExistFs[MaxExistIndex] = Index;
    MaxExistIndex ++;

    //
    // Print system information
    //
    Print (
      L"  %d: %s: (Free Space: %d MB)\n",
      MaxExistIndex,
      FsName,
      (UINTN) DivU64x32 (FreeSpaces[Index], INSTALL_SCT_1M, NULL)
      );

    FreePool (FsName);
  }

  Print (
    L"  Space Required: %d MB\n",
    INSTALL_SCT_FREE_SPACE / INSTALL_SCT_1M
    );

  //
  // User must choice a required file system
  //
  while (TRUE) {
    //
    // Input the index of destination file system
    //
    Input (
      L"Input index of destination FS. 'q' to exit:",
      InputBuffer,
      4
      );

    Print (L"\n");

    //
    // Deal with the user input
    //
    if (StriCmp (InputBuffer, L"q") == 0) {
      return EFI_ABORTED;
    }

    //
    // Convert the input to an index
    //
    Index = Atoi(InputBuffer) - 1;
    if (Index >= MaxExistIndex) {
      Print (L"  Only 1 to %d is valid.\n", MaxExistIndex);
      continue;
    }

    //
    // Check the free space
    //
    if (FreeSpaces[ExistFs[Index]] < (UINT64) INSTALL_SCT_FREE_SPACE) {
      Print (L"  Free space is not enough.\n");
      continue;
    }

    break;
  }

  //
  // Create the destination directory
  //
  *DirName = PoolPrint (L"FS%x:\\SCT", ExistFs[Index]);
  if (*DirName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupTests (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *TmpName;
  BOOLEAN     Exist;
  CHAR16      *Prompt;
  CHAR16      InputBuffer[2];

  //
  // Initialize the input buffer
  //
  InputBuffer[0] = L'\0';

  for (Index = 0; Index < INSTALL_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // Create the potential existing directory name
    //
    TmpName = PoolPrint (L"FS%x:\\SCT", Index);
    if (TmpName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Exist or not?
    //
    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      return Status;
    }

    if (!Exist) {
      FreePool (TmpName);
      continue;
    }

    //
    // Exist. Need to remove or backup
    //
    if (StriCmp (InputBuffer, L"a") == 0) {
      //
      // Backup all
      //
      Status = BackupDirFile (TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
      continue;
    } else if (StriCmp (InputBuffer, L"l") == 0) {
      //
      // Remove all
      //
      Status = RemoveDirFile (TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
      continue;
    }

    //
    // User must input a selection
    //
    while (TRUE) {
      //
      // User input his selection
      //
      Prompt = PoolPrint (
                 L"Found the existing test '%s'.\n"
                 L"Select (B)ackup, Backup (A)ll, (R)emove, Remove A(l)l. 'q' to exit:",
                 TmpName
                 );
      if (Prompt == NULL) {
        FreePool (TmpName);
        return EFI_OUT_OF_RESOURCES;
      }

      Input (
        Prompt,
        InputBuffer,
        2
        );

      FreePool (Prompt);
      Print (L"\n");

      //
      // Deal with the user input
      //
      if (StriCmp (InputBuffer, L"q") == 0) {
        FreePool (TmpName);
        return EFI_ABORTED;
      }

      if ((StriCmp (InputBuffer, L"b") == 0) ||
          (StriCmp (InputBuffer, L"a") == 0)) {
        //
        // Backup or Backup All
        //
        Status = BackupDirFile (TmpName);
        if (EFI_ERROR (Status)) {
          FreePool (TmpName);
          return Status;
        }

        break;
      } else if ((StriCmp (InputBuffer, L"r") == 0) ||
                 (StriCmp (InputBuffer, L"l") == 0)) {
        //
        // Remove or Remove All
        //
        Status = RemoveDirFile (TmpName);
        if (EFI_ERROR (Status)) {
          FreePool (TmpName);
          return Status;
        }

        break;
      }
    }

    FreePool (TmpName);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupStartups (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *TmpName;
  BOOLEAN     Exist;
  CHAR16      *Prompt;
  CHAR16      InputBuffer[2];

  //
  // Initialize the input buffer
  //
  InputBuffer[0] = L'\0';

  for (Index = 0; Index < INSTALL_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // Create the existing startup script
    //
    TmpName = PoolPrint (L"FS%x:\\startup.nsh", Index);
    if (TmpName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Exist or not?
    //
    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      return Status;
    }

    if (!Exist) {
      FreePool (TmpName);
      continue;
    }

    //
    // Exist. Need to remove or backup
    //
    if (StriCmp (InputBuffer, L"a") == 0) {
      //
      // Backup all
      //
      Status = BackupDirFile (TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
      continue;
    } else if (StriCmp (InputBuffer, L"l") == 0) {
      //
      // Remove all
      //
      Status = RemoveDirFile (TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
      continue;
    }

    //
    // User must input a selection
    //
    while (TRUE) {
      //
      // User input his selection
      //
      Prompt = PoolPrint (
                 L"Found the existing startup script '%s'.\n"
                 L"Select (B)ackup, Backup (A)ll, (R)emove, Remove A(l)l. 'q' to exit:",
                 TmpName
                 );
      if (Prompt == NULL) {
        FreePool (TmpName);
        return EFI_OUT_OF_RESOURCES;
      }

      Input (
        Prompt,
        InputBuffer,
        2
        );

      FreePool (Prompt);
      Print (L"\n");

      //
      // Deal with user input
      //
      if (StriCmp (InputBuffer, L"q") == 0) {
        FreePool (TmpName);
        return EFI_ABORTED;
      }

      if ((StriCmp (InputBuffer, L"b") == 0) ||
          (StriCmp (InputBuffer, L"a") == 0)) {
        //
        // Backup or Backup All
        //
        Status = BackupDirFile (TmpName);
        if (EFI_ERROR (Status)) {
          FreePool (TmpName);
          return Status;
        }

        break;
      } else if ((StriCmp (InputBuffer, L"r") == 0) ||
                 (StriCmp (InputBuffer, L"l") == 0)) {
        //
        // Remove or Remove All
        //
        Status = RemoveDirFile (TmpName);
        if (EFI_ERROR (Status)) {
          FreePool (TmpName);
          return Status;
        }

        break;
      }
    }

    FreePool (TmpName);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallTest (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;

  //
  // Copy the EFI SCT Harness
  //
  Status = CopyDirFile (
             INSTALL_SCT_PLATFORM_NAME,
             DirName,
             TRUE                           // Recursive
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallStartup (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  CHAR16      *FsName;
  CHAR16      *FileName;
  UINTN       Index;
  UINTN       Length;

  //
  // Split to the file system name
  //
  FsName = StrDuplicate (DirName);
  if (FsName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (DirName);

  for (Index = 0; Index < Length; Index ++) {
    if (FsName[Index] == L':') {
      FsName[Index] = L'\0';
      break;
    }
  }

  //
  // Create the startup file name
  //
  FileName = PoolPrint (L"%s:\\Startup.nsh", FsName);
  if (FileName == NULL) {
    FreePool (FsName);
    return EFI_OUT_OF_RESOURCES;
  }

  FreePool (FsName);

  //
  // Copy the startup script file
  //
  Status = CopyDirFile (
             INSTALL_SCT_STARTUP_FILE,
             FileName,
             FALSE                          // Not recursive
             );
  if (EFI_ERROR (Status)) {
    FreePool (FileName);
    return Status;
  }

  FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}
