/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  VariableServicesBbTestConformance.c

Abstract:
  Source file for Variable Services Black-Box Test - Conformance Test.

--*/

#include "VariableServicesBbTestMain.h"

//
// Prototypes (external)
//

EFI_STATUS
GetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
GetNextVariableNameConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
SetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes (internal)
//

EFI_STATUS
GetVariableConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub5 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub6 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetVariableConfTestSub7 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetNextVariableNameConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetNextVariableNameConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetNextVariableNameConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetNextVariableNameConfTestSub4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetNextVariableNameConfTestSub5 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetVariableConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetVariableConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
SetVariableConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

//
// Functions
//

/**
 *  TDS 3.1 - Entry point for RT->GetVariable() Conformance Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
GetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_RUNTIME_SERVICES                *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;

  //
  // GetVariable when VariableName is NULL
  //
  Status = GetVariableConfTestSub1 (RT, StandardLib, LoggingLib);

  //
  // GetVariable when VendorGuid is NULL
  //
  Status = GetVariableConfTestSub2 (RT, StandardLib, LoggingLib);

  //
  // GetVariable when DataSize is NULL
  //
  Status = GetVariableConfTestSub3 (RT, StandardLib, LoggingLib);

  //
  // GetVariable when Data is NULL
  //
  Status = GetVariableConfTestSub4 (RT, StandardLib, LoggingLib);

  //
  // GetVariable with nonexistent VariableName
  //
  Status = GetVariableConfTestSub5 (RT, StandardLib, LoggingLib);

  //
  // GetVariable with nonexistent VendorGuid
  //
  Status = GetVariableConfTestSub6 (RT, StandardLib, LoggingLib);

  //
  // GetVariable without enough DataSize
  //
  Status = GetVariableConfTestSub7 (RT, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 3.2 - Entry point for RT->GetNextVariableName() Conformance Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Execute successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_RUNTIME_SERVICES                *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;

  //
  // GetNextVariableName when VariableNameSize is NULL
  //
  Status = GetNextVariableNameConfTestSub1 (RT, StandardLib, LoggingLib);

  //
  // GetNextVariableName when VariableName is NULL
  //
  Status = GetNextVariableNameConfTestSub2 (RT, StandardLib, LoggingLib);

  //
  // GetNextVariableName when VendorGuid is NULL
  //
  Status = GetNextVariableNameConfTestSub3 (RT, StandardLib, LoggingLib);

  //
  // GetNextVariableName without enough VariableNameSize
  //
  Status = GetNextVariableNameConfTestSub4 (RT, StandardLib, LoggingLib);

  //
  // GetNextVariableName after the entire variable list has been returned
  //
  Status = GetNextVariableNameConfTestSub5 (RT, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 3.3 - Entry point for RT->SetVariable() Conformance Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Execute successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
SetVariableConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_RUNTIME_SERVICES                *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;

  //
  // SetVariable when VariableName is an empty string
  //
  Status = SetVariableConfTestSub1 (RT, StandardLib, LoggingLib);

  //
  // SetVariable with invalid combination of attribute bits
  //
  Status = SetVariableConfTestSub2 (RT, StandardLib, LoggingLib);

  //
  // SCR #2863
  // SetVariable with a variable whose size is > 1024 bytes
  //
  // Status = SetVariableConfTestSub3 (RT, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

// ********************************************************
// Internal Functions
// ********************************************************

/**
 *  GetVariable when VariableName is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub1",
                  L"TDS 3.1.2.1"
                  );
  }

  //
  // GetVariable should not succeed when VariableName is NULL
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 NULL,                    // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid001,
                 L"RT.GetVariable - When VariableName is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub1",
                  L"TDS 3.1.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetVariable when VendorGuid is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub2",
                  L"TDS 3.1.2.2"
                  );
  }

  //
  // GetVariable should not succeed when VendorGuid is NULL
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 NULL,                    // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid002,
                 L"RT.GetVariable - When VendorGuid is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub2",
                  L"TDS 3.1.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetVariable when DataSize is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub3",
                  L"TDS 3.1.2.3"
                  );
  }

  //
  // Set a test variable
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                          // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub3",
                    L"TDS 3.1.2.3 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed when DataSize is NULL
  //
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 NULL,                    // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid003,
                 L"RT.GetVariable - With DataSize is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Delete the variable (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                           // DataSize
                 Data                         // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub3",
                  L"TDS 3.1.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetVariable when Data is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub4",
                  L"TDS 3.1.2.4"
                  );
  }

  //
  // Set a test variable
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                          // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub3",
                    L"TDS 3.1.2.3 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed when Data is NULL
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 NULL                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid004,
                 L"RT.GetVariable - With Data is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Delete the variable (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                           // DataSize
                 Data                         // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub4",
                  L"TDS 3.1.2.4"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetVariable with nonexistent VariableName.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub5 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub5",
                  L"TDS 3.1.2.5"
                  );
  }

  //
  // Insert a test variable
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                          // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub5",
                    L"TDS 3.1.2.5 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // Delete the test variable
  //
  Status = RT->SetVariable (
                 L"TestVariable",             // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                           // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot delete a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub5",
                    L"TDS 3.1.2.5 - Cannot delete a variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed with a nonexistent VariableName
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid005,
                 L"RT.GetVariable - With nonexistent VariableName",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_NOT_FOUND
                 );

  //
  // Insert two similar variables
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariableA",            // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                          // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert similar variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub5",
                    L"TDS 3.1.2.5 - Cannot insert similar variable"
                    );
    }

    return Status;
  }

  Status = RT->SetVariable (
                 L"TestVariabl",              // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                          // DataSize
                 Data                         // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert similar variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub5",
                    L"TDS 3.1.2.5 - Cannot insert similar variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed with a nonexistent VariableName
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid005,
                 L"RT.GetVariable - With nonexistent VariableName",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_NOT_FOUND
                 );

  //
  // Delete two similar variables (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariableA",            // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                           // DataSize
                 Data                         // Data
                 );

  Status = RT->SetVariable (
                 L"TestVariabl",              // VariableName
                 &gTestVendor1Guid,           // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                           // DataSize
                 Data                         // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub5",
                  L"TDS 3.1.2.5"
                  );
  }

  //
  // Done
  //
  return Status;
}


/**
 *  GetVariable with nonexistent VendorGuid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub6 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub6",
                  L"TDS 3.1.2.6"
                  );
  }

  //
  // Insert a test variables with the vendor GUID2
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }
  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor2Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub6",
                    L"TDS 3.1.2.6 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed with a nonexistent VendorGuid
  //
  DataSize = MAX_BUFFER_SIZE;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid006,
                 L"RT.GetVariable - With nonexistent VendorGuid",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_NOT_FOUND
                 );

  //
  // Delete the variable with the vendor GUID2 (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor2Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                       // DataSize
                 Data                     // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub6",
                  L"TDS 3.1.2.6"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetVariable without enough DataSize.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetVariableConfTestSub7 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINTN                 DataSize;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub7",
                  L"TDS 3.1.2.7"
                  );
  }

  //
  // Insert a variables with a specified DataSize
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetVariable - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetVariableConfTestSub7",
                    L"TDS 3.1.2.7 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // GetVariable should not succeed when DataSize is 0
  //
  DataSize = 0;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if ((Status   == EFI_BUFFER_TOO_SMALL) &&
      (DataSize == 10                  )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid007,
                 L"RT.GetVariable - With DataSize is 0",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_BUFFER_TOO_SMALL
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"DataSize=%d, Expected=%d\n",
                 DataSize,    10
                 );

  //
  // GetVariable should not succeed when DataSize is required - 1
  //
  DataSize = 9;
  Status = RT->GetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 NULL,                    // Attributes
                 &DataSize,               // DataSize
                 Data                     // Data
                 );
  if ((Status   == EFI_BUFFER_TOO_SMALL) &&
      (DataSize == 10                  )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion & message
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid008,
                 L"RT.GetVariable - With DataSize is required-1",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_BUFFER_TOO_SMALL
                 );

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"DataSize=%d, Expected=%d\n",
                 DataSize,    10
                 );

  //
  // Delete the variable (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                       // DataSize
                 Data                     // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetVariableConfTestSub7",
                  L"TDS 3.1.2.7"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetNextVariableName when VariableNameSize is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  CHAR16                VariableName[MAX_BUFFER_SIZE];
  EFI_GUID              VendorGuid;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub1",
                  L"TDS 3.2.2.1"
                  );
  }

  //
  // GetNextVariableName should not succeed when VariableNameSize is NULL
  //
  VariableName[0] = L'\0';
  Status = RT->GetNextVariableName (
                 NULL,                    // VariableNameSize
                 VariableName,            // VariableName
                 &VendorGuid              // VendorGuid
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid009,
                 L"RT.GetNextVariableName - With VariableNameSize is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub1",
                  L"TDS 3.2.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetNextVariableName when VariableName is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 VariableNameSize;
  EFI_GUID              VendorGuid;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub2",
                  L"TDS 3.2.2.2"
                  );
  }

  //
  // GetNextVariableName should not succeed when VariableNameSize is NULL
  //
  VariableNameSize = MAX_BUFFER_SIZE * sizeof (CHAR16);
  Status = RT->GetNextVariableName (
                 &VariableNameSize,       // VariableNameSize
                 NULL,                    // VariableName
                 &VendorGuid              // VendorGuid
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid010,
                 L"RT.GetNextVariableName - With VariableName is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub2",
                  L"TDS 3.2.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetNextVariableName when VendorGuid is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 VariableNameSize;
  CHAR16                VariableName[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub3",
                  L"TDS 3.2.2.3"
                  );
  }

  //
  // GetNextVariableName should not succeed when VariableNameSize is NULL
  //
  VariableName[0] = L'\0';
  VariableNameSize = MAX_BUFFER_SIZE * sizeof (CHAR16);
  Status = RT->GetNextVariableName (
                 &VariableNameSize,       // VariableNameSize
                 VariableName,            // VariableName
                 NULL                     // VendorGuid
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid011,
                 L"RT.GetNextVariableName - With VendorGuid is NULL",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub3",
                  L"TDS 3.2.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetNextVariableName without enough VariableNameSize.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTestSub4 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];
  UINTN                 VariableNameSize;
  CHAR16                VariableName[MAX_BUFFER_SIZE];
  EFI_GUID              VendorGuid;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub4",
                  L"TDS 3.2.2.4"
                  );
  }

  //
  // Insert a variable (at least one variable)
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetNextVariableName - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetNextVariableNameConfTestSub4",
                    L"TDS 3.2.2.4 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // GetNextVariableName should not succeed when VariableNameSize is 2
  // (The size of each variable should larger than 2.)
  //
  VariableName[0] = L'\0';
  VariableNameSize = 2;
  Status = RT->GetNextVariableName (
                 &VariableNameSize,       // VariableNameSize
                 VariableName,            // VariableName
                 &VendorGuid              // VendorGuid
                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid012,
                 L"RT.GetNextVariableName - With VariableNameSize is 2",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_BUFFER_TOO_SMALL
                 );

  //
  // Delete a variable (restore environment)
  //
  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                       // DataSize
                 Data                     // Data
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub4",
                  L"TDS 3.2.2.4"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  GetNextVariableName after the entire variable list has been returned.
 *    NOTES: Also check GetNextVariableName will not return deleted variable.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetNextVariableNameConfTestSub5 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];
  UINTN                 VariableNameSize;
  CHAR16                VariableName[MAX_BUFFER_SIZE];
  EFI_GUID              VendorGuid;

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub5",
                  L"TDS 3.2.2.5"
                  );
  }

  //
  // Insert a variable
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetNextVariableName - Cannot insert a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetNextVariableNameConfTestSub5",
                    L"TDS 3.2.2.5 - Cannot insert a variable"
                    );
    }

    return Status;
  }

  //
  // Delete the variable
  //
  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 0,                       // DataSize
                 Data                     // Data
                 );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"RT.GetNextVariableName - Cannot delete a variable",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"GetNextVariableNameConfTestSub5",
                    L"TDS 3.2.2.5 - Cannot delete a variable"
                    );
    }

    return Status;
  }

  //
  // Walk through all variables
  //
  VariableName[0] = L'\0';
  Result = EFI_TEST_ASSERTION_PASSED;

  while (TRUE) {
    VariableNameSize = MAX_BUFFER_SIZE * sizeof (CHAR16);
    Status = RT->GetNextVariableName (
                   &VariableNameSize,       // VariableNameSize
                   VariableName,            // VariableName
                   &VendorGuid              // VendorGuid
                   );
    if (EFI_ERROR(Status)) {
      if (Status != EFI_NOT_FOUND) {
        Result = EFI_TEST_ASSERTION_FAILED;
      }
      break;
    }

    if ((StrCmp (VariableName, L"TestVariable")       == 0) &&
        (CompareGuid (&VendorGuid, &gTestVendor1Guid) == 0)) {
      Result = EFI_TEST_ASSERTION_FAILED;
      break;
    }
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid013,
                 L"RT.GetNextVariableName - After entire variable list returned",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_NOT_FOUND
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"GetNextVariableNameConfTestSub5",
                  L"TDS 3.2.2.5"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetVariable when VariableName is an empty string.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetVariableConfTestSub1 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub1",
                  L"TDS 3.3.2.1"
                  );
  }

  //
  // SetVariable should not succeed when VariableName is an empty string
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"",                     // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid014,
                 L"RT.SetVariable - With VaribaleName is empty string",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub1",
                  L"TDS 3.3.2.1"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetVariable with invalid combination of attribute bits.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetVariableConfTestSub2 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub2",
                  L"TDS 3.3.2.2"
                  );
  }

  //
  // SetVariable should not succeed when Attributes is RA
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_RUNTIME_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid015,
                 L"RT.SetVariable - With Attributes is RA",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // SetVariable should not succeed when Attributes is NV | RA
  //
  for (DataIndex = 0; DataIndex < 10; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS,
                 10,                      // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid016,
                 L"RT.SetVariable - With Attributes is NV|RA",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub2",
                  L"TDS 3.3.2.2"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  SetVariable with too large variable.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SetVariableConfTestSub3 (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    Result;
  UINTN                 DataIndex;
  UINT8                 Data[MAX_BUFFER_SIZE];

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub3",
                  L"TDS 3.3.2.3"
                  );
  }

  //
  // Only initialize the Data buffer from 0 to MAX_BUFFER_SIZE
  //
  for (DataIndex = 0; DataIndex < MAX_BUFFER_SIZE; DataIndex++) {
    Data[DataIndex] = (UINT8)DataIndex;
  }

  Status = RT->SetVariable (
                 L"TestVariable",         // VariableName
                 &gTestVendor1Guid,       // VendorGuid
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 (UINTN)-1,               // DataSize
                 Data                     // Data
                 );
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gVariableServicesBbTestConformanceAssertionGuid017,
                 L"RT.SetVariable - With too large variable",
                 L"%a:%d:Status - %r, Expected - %r",
                 __FILE__,
                 __LINE__,
                 Status,      EFI_INVALID_PARAMETER
                 );

  //
  // Trace ...
  //
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SetVariableConfTestSub3",
                  L"TDS 3.3.2.3"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
