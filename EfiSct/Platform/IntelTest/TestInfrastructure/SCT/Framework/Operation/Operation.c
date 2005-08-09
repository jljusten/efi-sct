/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Operation.c

Abstract:

  This file provides the main operations of SCT.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
AttachSupportFiles (
  VOID
  );

EFI_STATUS
AttachConfigData (
  VOID
  );

EFI_STATUS
AttachCategoryData (
  VOID
  );

EFI_STATUS
AttachTestCases (
  VOID
  );

EFI_STATUS
AttachTestFiles (
  VOID
  );

EFI_STATUS
DoPreOperationAll (
  VOID
  );

EFI_STATUS
DoPreOperationContinue (
  VOID
  );

EFI_STATUS
DoPreOperationSequence (
  VOID
  );

EFI_STATUS
DoPreOperationUi (
  VOID
  );


//
// External functions implementation
//

EFI_STATUS
AttachFirstStageTestData (
  VOID
  )
/*++

Routine Description:

  Attach the first stage test data (before the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Attach all test support files
  //
  Status = AttachSupportFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach support files - %r", Status));
    return Status;
  }

  //
  // Attach the test config data
  //
  Status = AttachConfigData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach config data - %r", Status));
    return Status;
  }

  //
  // Attach the test category data
  //
  Status = AttachCategoryData ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach category data - %r", Status));
    return Status;
  }

  //
  // Attach the test cases
  //
  Status = AttachTestCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach test cases - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachSecondStageTestData (
  VOID
  )
/*++

Routine Description:

  Attach the second stage test data (after the test files are loaded.)

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Attach the test files
  //
  Status = AttachTestFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Attach test files - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoFirstStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the first stage operations (before the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;
  BOOLEAN     UserInput;

  //
  // Check reset operation
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_RESET) != 0) {
    //
    // Check the last test is finished or not
    //
    if (!IsTestFinished ()) {
      //
      // Not finished, ask user to confirm that
      //
      Status = SctJudgeInput (
                 L"The last test is not finished. Are you sure to reset it? (Y/N)",
                 &UserInput
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Judge input - %r", Status));
        return Status;
      }

      if (!UserInput) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"User aborted!"));
        return EFI_ABORTED;
      }
    }

    //
    // Reset all test results
    //
    Status = ResetAllTestResults ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset all test results - %r", Status));
      return Status;
    }
  }

  //
  // Check execute all or execute sequence operation
  //
  if (((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == EFI_SCT_OPERATIONS_ALL     ) ||
      ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == EFI_SCT_OPERATIONS_SEQUENCE)) {
    //
    // Check the last test is finished or not
    //
    if (!IsTestFinished ()) {
      //
      // Not finished, ask user to confirm that
      //
      Status = SctJudgeInput (
                 L"The last test is not finished. Are you sure to start a new test? (Y/N)",
                 &UserInput
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Judge input - %r", Status));
        return Status;
      }

      if (!UserInput) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"User aborted!"));
        return EFI_ABORTED;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoSecondStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the second stage operations (after the test files are loaded).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Handle different operations
  //
  switch (gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) {
  case EFI_SCT_OPERATIONS_ALL:
    //
    // Execute all test cases
    //
    Status = DoPreOperationAll ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation ALL - %r", Status));
      return Status;
    }

    Status = SctExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation ALL - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_CONTINUE:
    //
    // Continue execute the test cases
    //
    Status = DoPreOperationContinue ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation CONTINUE - %r", Status));
      return Status;
    }

    Status = SctContinueExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation CONTINUE - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_SEQUENCE:
    //
    // Execute the test cases in the sequence file
    //
    Status = DoPreOperationSequence ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation SEQUENCE - %r", Status));
      return Status;
    }

    Status = SctExecute ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation SEQUENCE - %r", Status));
      return Status;
    }

    break;

  case EFI_SCT_OPERATIONS_UI:
    //
    // Turn into the user-friendly interface
    //
    Status = DoPreOperationUi ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre-operation UI - %r", Status));
      return Status;
    }

    Status = SctMenu ();
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Operation UI - %r", Status));
      return Status;
    }

    break;

  default:
    //
    // No operation needs to do
    //
    return EFI_SUCCESS;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoThirdStageOperations (
  VOID
  )
/*++

Routine Description:

  Do the third stage operations (generate report).

Returns:

  EFI_SUCCESS   - Successfully.
  OTHERS        - Something failed.

--*/
{
  EFI_STATUS        Status;
  CHAR16            *LogFilePath;
  EFI_FILE_HANDLE   Handle;

  //
  // Check report operation
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_REPORT) != 0) {
    Print (L"Generate test report. Expect this to take about one minute ...\n");

    LogFilePath = PoolPrint (
                    L"%s\\%s",
                    gFT->FilePath,
                    EFI_SCT_PATH_LOG
                    );
    if (LogFilePath == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Try to create the report file
    //
    Status = SctCreateFileFromDevicePath (
               gFT->RepDevicePath,
               gFT->RepFileName,
               &Handle
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create report file - %r", Status));
      Print (L"  ERROR: Cannot create the report file. Status - %r\n", Status);
      BS->FreePool (LogFilePath);
      return Status;
    }

    Handle->Close (Handle);

    //
    // Generate the report file
    //
    Status = GenerateReport (
               gFT->DevicePath,
               LogFilePath,
               gFT->RepDevicePath,
               gFT->RepFileName
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Generate report file - %r", Status));
      Print (L"  ERROR: Cannot generate the report file. Status - %r\n", Status);
      BS->FreePool (LogFilePath);
      return Status;
    }

    Print (L"  Succeed!\n");
    BS->FreePool (LogFilePath);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
AttachSupportFiles (
  VOID
  )
/*++

Routine Description:

  Attach the test support files.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  //
  // Create the test support file path
  //
  FilePath = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_SUPPORT
               );
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test support files
  //
  Print (L"Load support files ...\n");

  Status = LoadSupportFiles (
             gFT->DevicePath,
             FilePath,
             TRUE,                // Recursive
             &gFT->SupportFileList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load support files - %r", Status));
    BS->FreePool (FilePath);
    return Status;
  }

  BS->FreePool (FilePath);

  //
  // Open the standard test support files
  //
  Status = OpenStandardSupportFiles ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open standard support files - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AttachConfigData (
  VOID
  )
/*++

Routine Description:

  Attach the test configuration data.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Allocate memory for the configuration data
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_CONFIG_DATA),
                 &gFT->ConfigData
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  //
  // Create the configuration data file name
  //
  FileName = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CONFIG
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the configuration data
  //
  Status = LoadConfigData (
             gFT->DevicePath,
             FileName,
             gFT->ConfigData
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load config data - %r", Status));
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
AttachCategoryData (
  VOID
  )
/*++

Routine Description:

  Attach the category data.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the category data file name
  //
  FileName = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CATEGORY
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the category data
  //
  Status = LoadCategoryData (
             gFT->DevicePath,
             FileName,
             &gFT->CategoryList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load category data - %r", Status));
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
AttachTestCases (
  VOID
  )
/*++

Routine Description:

  Attach the test cases.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the test cases file name
  //
  FileName = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_TEST_CASE
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the test cases
  //
  Status = LoadTestCases (
             gFT->DevicePath,
             FileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test cases - %r", Status));
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
AttachTestFiles (
  VOID
  )
/*++

Routine Description:

  Attach the test files.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;

  //
  // Check operations
  //
  if ((gFT->Operations & EFI_SCT_OPERATIONS_LOW_MASK) == 0) {
    //
    // No execute operation. Need not attach the test files
    //
    return EFI_SUCCESS;
  }

  //
  // Create the test file path
  //
  FilePath = PoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_PATH_TEST
               );
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load test files
  //
  Print (L"Load test files ...\n");

  Status = LoadTestFiles (
             gFT->DevicePath,
             FilePath,
             TRUE,                // Recursive
             &gFT->TestFileList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test files - %r", Status));
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
DoPreOperationAll (
  VOID
  )
/*++

Routine Description:

  Do the pre-operation for operation ALL.

--*/
{
  EFI_STATUS      Status;
  EFI_LIST_ENTRY  *Link;
  EFI_LIST_ENTRY  TestCaseList;

  InitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!IsListEmpty (&TestCaseList)) {
    Link = TestCaseList.Flink;
    RemoveEntryList (Link);
    InsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Reset the order of test cases
  //
  Status = ResetTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order - %r", Status));
    return Status;
  }

  //
  // Create the test nodes
  //
  Status = CreateTestNodes (&gFT->TestNodeList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test nodes - %r", Status));
    return Status;
  }

  //
  // Build the order of test cases
  //
  Status = BuildTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Build test case order - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationContinue (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation CONTINUE.

--*/
{
  EFI_STATUS      Status;
  EFI_LIST_ENTRY  *Link;
  EFI_LIST_ENTRY  TestCaseList;

  InitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!IsListEmpty (&TestCaseList)) {
    Link = TestCaseList.Flink;
    RemoveEntryList (Link);
    InsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationSequence (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation SEQUENCE.

--*/
{
  EFI_STATUS      Status;
  EFI_LIST_ENTRY  *Link;
  EFI_LIST_ENTRY  TestCaseList;

  InitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!IsListEmpty (&TestCaseList)) {
    Link = TestCaseList.Flink;
    RemoveEntryList (Link);
    InsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Reset the order of test cases
  //
  Status = ResetTestCaseOrder ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order - %r", Status));
    return Status;
  }

  //
  // Load the test sequence
  //
  Status = LoadTestSequence (
             gFT->SeqDevicePath,
             gFT->SeqFileName,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test sequence - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DoPreOperationUi (
  VOID
  )
/*++

Routine Description:

  Do pre-operation for operation UI.

--*/
{
  EFI_STATUS      Status;
  EFI_LIST_ENTRY  *Link;
  EFI_LIST_ENTRY  TestCaseList;

  InitializeListHead (&TestCaseList);

  //
  // Create the test cases
  //
  Status = CreateTestCases (&TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test cases - %r", Status));
    return Status;
  }

  //
  // Merge the test cases
  //
  Status = MergeTestCases (
             &TestCaseList,
             &gFT->TestCaseList
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Merge tet cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  //
  // Free the old test cases and add the new one
  //
  Status = FreeTestCases (&gFT->TestCaseList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test cases - %r", Status));
    FreeTestCases (&TestCaseList);
    return Status;
  }

  while (!IsListEmpty (&TestCaseList)) {
    Link = TestCaseList.Flink;
    RemoveEntryList (Link);
    InsertTailList (&gFT->TestCaseList, Link);
  }

  //
  // Create the test nodes
  //
  Status = CreateTestNodes (&gFT->TestNodeList);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create test nodes - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
