/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Execute.c

Abstract:

  This file provides the test execution services.

--*/

#include "Sct.h"
#include "ExecuteSupport.h"

//
// Internal functions declaration
//

EFI_STATUS
ExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
ContinueExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  );

EFI_STATUS
ExecuteMainFunc (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteBbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteWbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteApTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
ExecuteBbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN VOID                         *Interface OPTIONAL,
  IN EFI_HANDLE                   Handle OPTIONAL
  );

EFI_STATUS
ExecuteWbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL
  );

EFI_STATUS
ExecuteApTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

EFI_STATUS
PreExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT BOOLEAN                     *IsSkip
  );

EFI_STATUS
PostExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_STATUS                   TestStatus
  );

EFI_STATUS
InitializeTestConfigData (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  );

EFI_STATUS
FreeTestConfigData (
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  );


//
// External functions implementation
//

EFI_STATUS
SctExecute (
  VOID
  )
/*++

Routine Description:

  Execute the test cases.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_TEST_CASE     *TestCase;

  Print (L"Test preparing...\n");

  //
  // Reset the test results of the selected test cases
  //
  Status = ResetTestCaseResults ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case results - %r", Status));
    return Status;
  }

  //
  // Find the next test case
  //
  Status = GetNextTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get next test case - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // No test case is found, all test cases have been executed
    //
    return EFI_SUCCESS;
  }

  //
  // Start the execution
  //
  Status = ExecuteStart (TestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute start - %r", Status));
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctContinueExecute (
  VOID
  )
/*++

Routine Description:

  Continue to execute the test cases after system reset or any interrupts.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_TEST_CASE     *TestCase;

  Print (L"Continue test preparing...\n");

  //
  // Initialize the first time execute flag
  //
  gFT->IsFirstTimeExecute = FALSE;

  //
  // Find the running test case
  //
  Status = GetRunningTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get running test case - %r", Status));
    return Status;
  }

  if (Status != EFI_NOT_FOUND) {
    //
    // Continue start the execution
    //
    Status = ContinueExecuteStart (TestCase);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Continue execute start - %r", Status));
      return Status;
    }

    //
    // Done
    //
    return EFI_SUCCESS;
  }

  //
  // No running test case is found, start normal execution
  //

  //
  // Find the next test case
  //
  Status = GetNextTestCase (&TestCase);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get next test case - %r", Status));
    return Status;
  }

  if (Status == EFI_NOT_FOUND) {
    //
    // No test case is found, all test cases have been executed
    //
    return EFI_SUCCESS;
  }

  //
  // Start the execution
  //
  Status = ExecuteStart (TestCase);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute start - %r", Status));
    return Status;
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
ExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Start the test execution from the input test case.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_EXECUTE_INFO  ExecuteInfo;
  CHAR16                *FileName;

  //
  // Initialize the execute information
  //
  Status = InitializeExecuteInfo (
             TestCase,
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
    return Status;
  }

  //
  // Reset the execute test results
  //
  Status = ResetExecuteTestResults (
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset execute test results - %r", Status));
    return Status;
  }

  //
  // Start the execution
  //
  Status = ExecuteMainFunc (&ExecuteInfo);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
    return Status;
  }

  //
  // Create the name of test case file
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
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ContinueExecuteStart (
  IN EFI_SCT_TEST_CASE            *TestCase
  )
/*++

Routine Description:

  Continue to start the test execution from the input test case.

--*/
{
  EFI_STATUS            Status;
  EFI_SCT_EXECUTE_INFO  ExecuteInfo;
  CHAR16                *FullMetaName;
  CHAR16                *FileName;

  //
  // Initialize the execute information
  //
  Status = InitializeExecuteInfo (
             TestCase,
             &ExecuteInfo
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
    return Status;
  }

  //
  // Get the full meta name of key files
  //
  Status = GetKeyFileFullMetaName (
             &ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get key file full meta name - %r", Status));
    return Status;
  }

  //
  // Get the test information from the key files
  //
  Status = GetInstanceAssertion (
             gFT->DevicePath,
             FullMetaName,
             &ExecuteInfo.State,
             &ExecuteInfo.Index,
             &ExecuteInfo.Iteration,
             &ExecuteInfo.Passes,
             &ExecuteInfo.Warnings,
             &ExecuteInfo.Failures
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get instance assertion - %r", Status));
    BS->FreePool (FullMetaName);
    return Status;
  }

  BS->FreePool (FullMetaName);

  //
  // Start the execution
  //
  Status = ExecuteMainFunc (&ExecuteInfo);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
    return Status;
  }

  //
  // Create the name of test case file
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
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteMainFunc (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  It is main routine for test execution.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_CASE   *TestCase;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Execute test cases"));

  //
  // Walk through all test cases
  //
  while (TRUE) {
    //
    // Execute the test case
    //
    Status = ExecuteTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute test case - %r", Status));
      return Status;
    }

    //
    // Find the next test case
    //
    Status = GetNextTestCase (&TestCase);
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get running test case - %r", Status));
      return Status;
    }

    if (Status == EFI_NOT_FOUND) {
      //
      // No test case is found, all test cases have been executed
      //
      return EFI_SUCCESS;
    }

    //
    // Initialize the execute information
    //
    Status = InitializeExecuteInfo (
               TestCase,
               ExecuteInfo
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize execute info - %r", Status));
      return Status;
    }

    //
    // Reset the execute test results
    //
    Status = ResetExecuteTestResults (
               ExecuteInfo
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset execute test results - %r", Status));
      return Status;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute a test case.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FullMetaName;
  UINT32      Passes;
  UINT32      Warnings;
  UINT32      Failures;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Deal with the different kind of test files
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    Status = ExecuteBbTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute BB test case - %r", Status));
      return Status;
    }
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    Status = ExecuteWbTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute WB test case - %r", Status));
      return Status;
    }
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    Status = ExecuteApTestCase (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute AP test case - %r", Status));
      return Status;
    }
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Get the full meta name of key files
  //
  Status = GetKeyFileFullMetaName (
             ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get key file full meta name - %r", Status));
    return Status;
  }

  //
  // Get the results of test case
  //
  Status = GetInterfaceAssertion (
             gFT->DevicePath,
             FullMetaName,
             &Passes,
             &Warnings,
             &Failures
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get interface assertion - %r", Status));
    BS->FreePool (FullMetaName);
    return Status;
  }

  BS->FreePool (FullMetaName);

  //
  // Store the test results
  //
  ExecuteInfo->TestCase->Passes   = Passes;
  ExecuteInfo->TestCase->Failures = Failures;

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteBbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute a black-box test case.

--*/
{
  EFI_STATUS            Status;
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  EFI_GUID              *Guid;
  VOID                  *Interface;
  EFI_BB_TEST_PROTOCOL  *BbTest;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Black-box test protocol
  //
  BbTest = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;

  //
  // Get the GUID of tested interface
  //
  if (ExecuteInfo->Category != NULL) {
    Guid = &ExecuteInfo->Category->InterfaceGuid;
  } else {
    Guid = &BbTest->CategoryGuid;
  }

  //
  // Get the tested interface from the GUID
  //
  if (CompareGuid (Guid, &gEfiGenericCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Generic services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      Print (L"  Generic services test: %s\n", ExecuteInfo->TestCase->Name);
      Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with NULL interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, NULL, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else if (CompareGuid (Guid, &gEfiBootServicesCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Boot services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      Print (L"  Boot services test: %s\n", ExecuteInfo->TestCase->Name);
      Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with BS interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, BS, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else if (CompareGuid (Guid, &gEfiRuntimeServicesCategoryGuid) == 0) {
    while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
      //
      // Runtime services test
      //
      if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
        EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
        continue;
      }

      //
      // Process information
      //
      Print (L"  Runtime services test: %s\n", ExecuteInfo->TestCase->Name);
      Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

      //
      // Start the test case with RT interface
      //
      Status = ExecuteBbTestInstance (ExecuteInfo, RT, NULL);
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance - %r", Status));
        return Status;
      }

      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
    }

  } else {
    //
    // Protocol test
    //
    Status = BS->LocateHandleBuffer (
                   ByProtocol,
                   Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
    if (EFI_ERROR (Status) || (NoHandles == 0)) {
      //
      // Cannot find the tested protocol instance
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"No tested protocol instance"));
      return EFI_SUCCESS;
    }

    //
    // Walk through each instance need to be tested
    //
    while (ExecuteInfo->Index < NoHandles) {
      Status = BS->HandleProtocol (
                     HandleBuffer[ExecuteInfo->Index],
                     Guid,
                     &Interface
                     );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Handle protocol - %r", Status));
        return Status;
      }

      while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
        if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
          EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
          ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
          ExecuteInfo->Iteration ++;
          continue;
        }

        //
        // Process information
        //
        Print (L"  Protocol test: %s\n", ExecuteInfo->TestCase->Name);
        Print (L"  Instances: %d/%d\n", ExecuteInfo->Index + 1, NoHandles);
        Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

        Status = ExecuteBbTestInstance (
                   ExecuteInfo,
                   Interface,
                   HandleBuffer[ExecuteInfo->Index]
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a BB test instance- %r", Status));
          return Status;
        }

        ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
        ExecuteInfo->Iteration ++;
      }

      ExecuteInfo->Iteration = 0;
      ExecuteInfo->Index ++;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteWbTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute a white-box test case.

--*/
{
  EFI_STATUS            Status;
  EFI_WB_TEST_PROTOCOL  *WbTest;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // White-box test protocol
  //
  WbTest = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;

  while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
    //
    // White-box test
    //
    if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
      continue;
    }

    //
    // Process infromation
    //
    Print (L"  White-box test: %s\n", ExecuteInfo->TestCase->Name);
    Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

    Status = ExecuteWbTestInstance (ExecuteInfo, WbTest->ClientHandle);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute a WB test instance - %r", Status));
      return Status;
    }

    ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
    ExecuteInfo->Iteration ++;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteApTestCase (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute an application or a script test case.

--*/
{
  EFI_STATUS              Status;
  EFI_AP_TEST_INTERFACE   *ApTest;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Application test interface
  //
  ApTest = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;

  while (ExecuteInfo->Iteration < ExecuteInfo->TestCase->Iterations) {
    //
    // Application test
    //
    if (ExecuteInfo->State == EFI_SCT_LOG_STATE_FINISHED) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Recovery finished"));
      ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
      ExecuteInfo->Iteration ++;
      continue;
    }

    //
    // Process infromation
    //
    Print (L"  Application test: %s\n", ExecuteInfo->TestCase->Name);
    Print (L"  Iterations: %d/%d\n", ExecuteInfo->Iteration + 1, ExecuteInfo->TestCase->Iterations);

    Status = ExecuteApTestInstance (ExecuteInfo);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute an AP test instance - %r", Status));
      return Status;
    }

    ExecuteInfo->State = EFI_SCT_LOG_STATE_UNKNOWN;
    ExecuteInfo->Iteration ++;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteBbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN VOID                         *Interface OPTIONAL,
  IN EFI_HANDLE                   Handle OPTIONAL
  )
/*++

Routine Description:

  Execute a black-box test instance.

--*/
{
  EFI_STATUS            Status;
  EFI_STATUS            TestStatus;
  BOOLEAN               IsSkip;
  EFI_BB_TEST_PROTOCOL  *BbTest;
  EFI_BB_TEST_ENTRY     *BbEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Black-box test instance
  //
  BbTest  = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
  BbEntry = (EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             Handle,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (BbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      TestStatus = BbEntry->EntryPoint (
                              BbTest,
                              Interface,
                              gFT->ConfigData->TestLevel,
                              gFT->SupportHandle
                              );
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (BbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((BbEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      RT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteWbTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL
  )
/*++

Routine Description:

  Execute a white-box test instance.

--*/
{
  EFI_STATUS            Status;
  EFI_STATUS            TestStatus;
  BOOLEAN               IsSkip;
  EFI_WB_TEST_PROTOCOL  *WbTest;
  EFI_WB_TEST_ENTRY     *WbEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // White-box test instance
  //
  WbTest  = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
  WbEntry = (EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             Handle,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (WbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      TestStatus = WbEntry->EntryPoint (
                              WbTest,
                              gFT->ConfigData->TestLevel,
                              gFT->SupportHandle
                              );
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (WbEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((WbEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      RT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ExecuteApTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Execute an application or a script test instance.

--*/
{
  EFI_STATUS              Status;
  EFI_STATUS              TestStatus;
  BOOLEAN                 IsSkip;
  CHAR16                  *CmdLine;
  EFI_AP_TEST_INTERFACE   *ApTest;
  EFI_AP_TEST_ENTRY       *ApEntry;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Application test instance
  //
  ApTest  = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;
  ApEntry = (EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry;

  TestStatus = EFI_UNSUPPORTED;

  //
  // Do pre-operations for a test instance
  //
  Status = PreExecuteTestInstance (
             ExecuteInfo,
             NULL_HANDLE,
             &IsSkip
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pre execute test instance - %r", Status));
    return Status;
  }

  if (!IsSkip) {
    //
    // Open the test support files
    //
    Status = OpenExtendedSupportFiles (ApEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Open support files - %r", Status));
    }

    if (!EFI_ERROR (Status)) {
      //
      // Invoke the test entry point
      //
      CmdLine = PoolPrint (
                  L"\"%s\" %s",
                  ExecuteInfo->TestFile->FileName,
                  ApEntry->Parameters
                  );
      if (CmdLine == NULL) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
      }

      if (CmdLine != NULL) {
        TestStatus = ShellExecute (
                       gFT->ImageHandle,
                       CmdLine,
                       FALSE
                       );
      }
    }

    //
    // Close the test support files
    //
    Status = CloseExtendedSupportFiles (ApEntry->SupportProtocols);
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Close support files - %r", Status));
    }
  }

  //
  // Do post-operations for a test instance
  //
  Status = PostExecuteTestInstance (
             ExecuteInfo,
             TestStatus
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Post execute test instance - %r", Status));
    return Status;
  }

  //
  // Deal with the specific attributes of test case
  //
  if (!IsSkip) {
    //
    // Reset required
    //
    if ((ApEntry->CaseAttribute & EFI_TEST_CASE_RESET_REQUIRED) != 0) {
      RT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InitializeTestConfigData (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT EFI_LIB_CONFIG_DATA         *ConfigData
  )
/*++

Routine Description:

  Initialize the test configuration data for test support libraries.

--*/
{
  EFI_STATUS                Status;
  CHAR16                    *FullMetaName;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_BB_TEST_PROTOCOL      *BbTest;
  EFI_BB_TEST_ENTRY         *BbEntry;
  EFI_WB_TEST_PROTOCOL      *WbTest;
  EFI_WB_TEST_ENTRY         *WbEntry;
  EFI_AP_TEST_INTERFACE     *ApTest;
  EFI_AP_TEST_ENTRY         *ApEntry;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (ConfigData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (ConfigData, sizeof(EFI_LIB_CONFIG_DATA));

  //
  // Get th full meta name of log files
  //
  Status = GetFileFullMetaName (
             ExecuteInfo,
             &FullMetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file full meta name - %r", Status));
    return Status;
  }

  //
  // Set the test configuration data
  //
  ConfigData->OutputProtocol      = gFT->TolProtocol;

  //
  // Set the recovery information
  //
  if (ExecuteInfo->State == EFI_SCT_LOG_STATE_RUNNING) {
    ConfigData->IsRecovery        = TRUE;
    ConfigData->PassCount         = ExecuteInfo->Passes;
    ConfigData->WarningCount      = ExecuteInfo->Warnings;
    ConfigData->FailCount         = ExecuteInfo->Failures;
  } else {
    ConfigData->IsRecovery        = FALSE;
    ConfigData->PassCount         = 0;
    ConfigData->WarningCount      = 0;
    ConfigData->FailCount         = 0;
  }

  //
  // Set the system log file and key file
  //
  ConfigData->SystemLogFile.EnableScreenOutput = FALSE;
  ConfigData->SystemLogFile.DevicePath         = gFT->DevicePath;
  ConfigData->SystemLogFile.FileName           =
    PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_SUMMARY_LOG);
  ConfigData->SystemLogFile.OverwriteFile      = gFT->IsFirstTimeExecute;

  ConfigData->SystemKeyFile.EnableScreenOutput = FALSE;
  ConfigData->SystemKeyFile.DevicePath         = gFT->DevicePath;
  ConfigData->SystemKeyFile.FileName           =
    PoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_SUMMARY_EKL);
  ConfigData->SystemKeyFile.OverwriteFile      = gFT->IsFirstTimeExecute;

  //
  // Set the case log file and key file
  //
  ConfigData->CaseLogFile.EnableScreenOutput   = gFT->ConfigData->EnableScreenOutput;
  ConfigData->CaseLogFile.DevicePath           = gFT->DevicePath;
  ConfigData->CaseLogFile.FileName             =
    PoolPrint (FullMetaName, ExecuteInfo->Index, ExecuteInfo->Iteration, L"log");
  ConfigData->CaseLogFile.OverwriteFile        = (BOOLEAN) !ConfigData->IsRecovery;

  ConfigData->CaseKeyFile.EnableScreenOutput   = FALSE;
  ConfigData->CaseKeyFile.DevicePath           = gFT->DevicePath;
  ConfigData->CaseKeyFile.FileName             =
    PoolPrint (FullMetaName, ExecuteInfo->Index, ExecuteInfo->Iteration, L"ekl");
  ConfigData->CaseKeyFile.OverwriteFile        = (BOOLEAN) !ConfigData->IsRecovery;

  //
  // Set the platform information
  //
  ConfigData->BiosId              = gFT->ConfigData->BiosId;
  ConfigData->PlatformNumber      = (UINT32) gFT->ConfigData->PlatformNumber;
  ConfigData->ConfigurationNumber = (UINT32) gFT->ConfigData->ConfigurationNumber;
  ConfigData->ScenarioString      = gFT->ConfigData->ScenarioString;

  //
  // Set the test information
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    BbTest  = (EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
    BbEntry = (EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = BbTest->TestRevision;
    ConfigData->TestName         = BbTest->Name;
    ConfigData->EntryId          = &BbEntry->EntryId;
    ConfigData->EntryName        = BbEntry->Name;
    ConfigData->EntryDescription = BbEntry->Description;
    ConfigData->SupportProtocols = BbEntry->SupportProtocols;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    WbTest  = (EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol;
    WbEntry = (EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = WbTest->TestRevision;
    ConfigData->TestName         = WbTest->Name;
    ConfigData->EntryId          = &WbEntry->EntryId;
    ConfigData->EntryName        = WbEntry->Name;
    ConfigData->EntryDescription = WbEntry->Description;
    ConfigData->SupportProtocols = WbEntry->SupportProtocols;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    ApTest  = (EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol;
    ApEntry = (EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry;

    ConfigData->TestRevision     = ApTest->TestRevision;
    ConfigData->TestName         = ApTest->Name;
    ConfigData->EntryId          = &ApEntry->EntryId;
    ConfigData->EntryName        = ApEntry->Name;
    ConfigData->EntryDescription = ApEntry->Description;
    ConfigData->SupportProtocols = ApEntry->SupportProtocols;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    FreeTestConfigData (ConfigData);
    return EFI_UNSUPPORTED;
  }

  ConfigData->VerboseLevel        = gFT->ConfigData->VerboseLevel;

  //
  // Set the test category and device path info
  //
  if (ExecuteInfo->Category != NULL) {
    ConfigData->TestCategory = StrDuplicate (ExecuteInfo->Category->Name);
  } else {
    ConfigData->TestCategory = StrDuplicate (L"Unknown");
  }

  if (Handle != NULL_HANDLE) {
    DevicePath = DevicePathFromHandle (Handle);
    if (DevicePath != NULL) {
      ConfigData->DevicePath = LibDevicePathToStr (DevicePath);
    } else {
      ConfigData->DevicePath = StrDuplicate (L"No device path");
    }
  } else {
    ConfigData->DevicePath = StrDuplicate (L"No device path");
  }

  //
  // Free resources
  //
  BS->FreePool (FullMetaName);

  //
  // Check error
  //
  if ((ConfigData->SystemLogFile.FileName == NULL) ||
      (ConfigData->SystemKeyFile.FileName == NULL) ||
      (ConfigData->CaseLogFile.FileName   == NULL) ||
      (ConfigData->CaseKeyFile.FileName   == NULL) ||
      (ConfigData->TestCategory           == NULL) ||
      (ConfigData->DevicePath             == NULL)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    FreeTestConfigData (ConfigData);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeTestConfigData (
  IN EFI_LIB_CONFIG_DATA          *ConfigData
  )
/*++

Routine Description:

  Free the test configuration data.

--*/
{
  //
  // Free the items of test configuration data
  //
  if (ConfigData->SystemLogFile.FileName != NULL) {
    BS->FreePool (ConfigData->SystemLogFile.FileName);
    ConfigData->SystemLogFile.FileName = NULL;
  }

  if (ConfigData->SystemKeyFile.FileName != NULL) {
    BS->FreePool (ConfigData->SystemKeyFile.FileName);
    ConfigData->SystemKeyFile.FileName = NULL;
  }

  if (ConfigData->CaseLogFile.FileName != NULL) {
    BS->FreePool (ConfigData->CaseLogFile.FileName);
    ConfigData->CaseLogFile.FileName = NULL;
  }

  if (ConfigData->CaseKeyFile.FileName != NULL) {
    BS->FreePool (ConfigData->CaseKeyFile.FileName);
    ConfigData->CaseKeyFile.FileName = NULL;
  }

  if (ConfigData->TestCategory != NULL) {
    BS->FreePool (ConfigData->TestCategory);
    ConfigData->TestCategory = NULL;
  }

  if (ConfigData->DevicePath != NULL) {
    BS->FreePool (ConfigData->DevicePath);
    ConfigData->DevicePath = NULL;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
PreExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_HANDLE                   Handle OPTIONAL,
  OUT BOOLEAN                     *IsSkip
  )
/*++

Routine Description:

  Do the pre-operations (start logging, set watchdog timer, etc) before the
  test execution.

--*/
{
  EFI_STATUS                Status;
  UINTN                     BufferSize;
  UINT8                     Buffer[1024];
  EFI_LIB_CONFIG_DATA       ConfigData;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (IsSkip == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the test configuration data
  //
  Status = InitializeTestConfigData (
             ExecuteInfo,
             Handle,
             &ConfigData
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Initialize test config data - %r", Status));
    return Status;
  }

  //
  // Now, we can set the first time execute flag to FALSE
  //
  gFT->IsFirstTimeExecute = FALSE;

  //
  // Set the configuration data to standard test
  //
  Status = gFT->StslInterface->SetConfig (
                                 gFT->StslInterface,
                                 &ConfigData
                                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Set standard test config - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Set the configuration data to test logging
  //
  Status = gFT->TllInterface->SetConfig (
                                gFT->TllInterface,
                                &ConfigData
                                );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Set test logging config - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Start the logging
  //
  Status = gFT->StslInterface->BeginLogging (gFT->StslInterface);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Start standard test - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  Status = gFT->TllInterface->BeginLogging (gFT->TllInterface);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Start test logging - %r", Status));
    FreeTestConfigData (&ConfigData);
    return Status;
  }

  //
  // Free resources
  //
  Status = FreeTestConfigData (&ConfigData);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Free test config data - %r", Status));
    return Status;
  }

  //
  // Check the test recovery data
  //
  *IsSkip = FALSE;

  if (ExecuteInfo->State != EFI_SCT_LOG_STATE_UNKNOWN) {
    Status = gFT->TrlProtocol->ReadResetRecord (
                                 gFT->TrlProtocol,
                                 &BufferSize,
                                 Buffer
                                 );
    if (EFI_ERROR (Status) || (BufferSize == 0)) {
      //
      // No recovery data, record a SYSTEM_HANG assertion
      //
      gFT->StslProtocol->RecordAssertion (
                           gFT->StslProtocol,
                           EFI_TEST_ASSERTION_FAILED,
                           gEfiSystemHangAssertionGuid,
                           L"Sysem hangs or stops abnormally.",
                           L"%a:%d",
                           __FILE__,
                           __LINE__
                           );

      //
      // Skip this test instance
      //
      *IsSkip = TRUE;
    }
  }

  //
  // Set the watchdog timer for recovery
  //
  Status = BS->SetWatchdogTimer (
                 gFT->ConfigData->TestCaseMaxRunTime,
                 0,
                 0,
                 NULL
                 );
  if (EFI_ERROR (Status)) {
    //
    // Platform supported? It was not handled as an error
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Set watchdog timer - %r", Status));
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
PostExecuteTestInstance (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  IN EFI_STATUS                   TestStatus
  )
/*++

Routine Description:

  Do the post-operations (reset watchdog timer, end logging, etc) after the
  test execution.

--*/
{
  EFI_STATUS  Status;

  //
  // Check parameters
  //
  if (ExecuteInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Reset the watchdog timer
  //
  Status = BS->SetWatchdogTimer (
                 0,
                 0,
                 0,
                 NULL
                 );
  if (EFI_ERROR (Status)) {
    //
    // Platform supported? It was not handled as an error
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Set watchdog timer - %r", Status));
  }

  //
  // Stop the logging
  //
  Status = gFT->StslInterface->EndLogging (
                                 gFT->StslInterface,
                                 TestStatus
                                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Stop standard test - %r", Status));
  }

  Status = gFT->TllInterface->EndLogging (
                                gFT->TllInterface,
                                TestStatus
                                );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Stop test logging - %r", Status));
  }

  //
  // Remove recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove recovery file - %r", Status));
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
