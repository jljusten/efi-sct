/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Sct.c

Abstract:

  EFI SCT Framework

--*/

#include "Sct.h"

//
// Global veriables definition
//

EFI_SCT_FRAMEWORK_TABLE *gFT = NULL;

EFI_GUID gEfiSystemHangAssertionGuid = EFI_SYSTEM_HANG_ASSERTION_GUID;

UINTN gTestCaseMaxRunTimeMax = 0x7FFFFFFF;

//
// Internal functions declaration
//

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
ParseCommandLine (
  VOID
  );

EFI_STATUS
SctMainFunc (
  VOID
  );

//
// Entry point
//
EFI_DRIVER_ENTRY_POINT(InitializeSct)

EFI_STATUS
InitializeSct (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
/*++

Routine Description:

  Entry point of SCT.

Arguments:

  ImageHandle   - The image handle.
  SystemTable   - The system table.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Initialize libraries
  //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  //
  // Initialize the framework table
  //
  Status = InitializeFrameworkTable (ImageHandle, SystemTable);
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: Cannot initialize the framework table. Status - %r\n", Status);
    return Status;
  }

  //
  // Parse the command line
  //
  Status = ParseCommandLine ();
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: Invalid command line. Status - %r\n", Status);
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Invoke the SCT main function to do the operations
  //
  Status = SctMainFunc ();
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: Cannot do the operations. Status - %r\n", Status);
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Free the framework table
  //
  Status = FreeFrameworkTable ();
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: Cannot free the framework table. Status - %r\n", Status);
    return Status;
  }

  //
  // Done
  //
  Print (L"Done!\n");
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

VOID
PrintUsage (
  VOID
  )
/*++

Routine Description:

  Print out the usage model of the SCT.

--*/
{
  Print (
    L"%s, Version %s.\n"
    L"\n"
    L"usage: %s [-a | -c | -s <seq> | -u] [-r] [-g <report>]\n"
    L"  -a    Executes all test cases.\n"
    L"  -c    Continues execute the test cases.\n"
    L"  -g    Generates test report.\n"
    L"  -r    Resets all test results.\n"
    L"  -s    Executes the test cases in the test sequence file.\n"
    L"  -u    Turns into user-friendly interface.\n"
    L"\n",
    EFI_SCT_NAME,
    EFI_SCT_VERSION,
    EFI_SCT_SHORT_NAME
    );
}


EFI_STATUS
ParseCommandLine (
  VOID
  )
/*++

Routine Description:

  Parse the command line.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINTN       Argc;
  CHAR16      **Argv;

  //
  // Get the parameters from the shell interface
  //
  Argc = SI->Argc;
  Argv = SI->Argv;

  //
  // Check all parameters
  //
  for (Index = 1; Index < Argc; Index ++) {
    if ((Argv[Index][0] != L'-') || (Argv[Index][2] != L'\0')) {
      return EFI_INVALID_PARAMETER;
    }

    switch (Argv[Index][1]) {
    case L'a':
    case L'A':
      //
      // Execute all test cases
      //
      if ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) != 0) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_ALL;
      break;

    case L'c':
    case L'C':
      //
      // Continue execute the test cases
      //
      if ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) != 0) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_CONTINUE;
      break;

    case L'g':
    case L'G':
      //
      // Generate test report
      //
      if (((gFT->Operations & EFI_SCT_OPERATIONS_REPORT) != 0   ) ||
          (Index + 1                                     >= Argc)) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_REPORT;

      Status = ExpandFileName (
                 Argv[Index + 1],
                 &gFT->RepDevicePath,
                 &gFT->RepFileName
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Index ++;
      break;

    case L'r':
    case L'R':
      //
      // Reset all test results
      //
      if ((gFT->Operations & EFI_SCT_OPERATIONS_RESET) != 0) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_RESET;
      break;

    case L's':
    case L'S':
      //
      // Execute the test cases in the test sequence file
      //
      if (((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) != 0   ) ||
          (Index + 1                                       >= Argc)) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_SEQUENCE;

      Status = ExpandFileName (
                 Argv[Index + 1],
                 &gFT->SeqDevicePath,
                 &gFT->SeqFileName
                 );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Index ++;
      break;

    case L'u':
    case L'U':
      //
      // Turn into user-friendly interface
      //
      if ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) != 0) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_UI;
      break;

    case L'x':
    case L'X':
      //
      // Run in extended mode (just for internal users)
      //
      if ((gFT->Operations & EFI_SCT_OPERATIONS_EXTENDED) != 0) {
        return EFI_INVALID_PARAMETER;
      }
      gFT->Operations |= EFI_SCT_OPERATIONS_EXTENDED;
      break;

    case L'h':
    case L'H':
    case L'?':
      //
      // Print the help information. Skip the other parameters
      //
      gFT->Operations  = EFI_SCT_OPERATIONS_NONE;
      return EFI_SUCCESS;

    default:
      return EFI_INVALID_PARAMETER;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctMainFunc (
  VOID
  )
/*++

Routine Description:

  The main routine of SCT.

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Check the operations
  //
  if (gFT->Operations == EFI_SCT_OPERATIONS_NONE) {
    //
    // No operation. Print out the help information
    //
    PrintUsage ();
    return EFI_SUCCESS;
  }

  //
  // Attach the first stage test data (before the test files are loaded)
  //
  Status = AttachFirstStageTestData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach first stage test data - %r", Status));
    return Status;
  }

  //
  // Do the first stage operations (before the test files are loaded)
  //
  Status = DoFirstStageOperations ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"First stage operations - %r", Status));
    return Status;
  }

  //
  // Attach the second stage test data (after the test files are loaded)
  //
  Status = AttachSecondStageTestData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach second stage test data - %r", Status));
    return Status;
  }

  //
  // Do the second stage operations (after the test files are loaded)
  //
  Status = DoSecondStageOperations ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Second stage operations - %r", Status));
    return Status;
  }

  //
  // Do the third stage operations (generate report)
  //
  Status = DoThirdStageOperations ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Third stage operations - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
