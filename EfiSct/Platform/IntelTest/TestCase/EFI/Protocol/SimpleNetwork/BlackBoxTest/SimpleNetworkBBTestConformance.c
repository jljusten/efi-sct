/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleNetworkBBTestConformance.c

Abstract:

  Conformance Test Cases of SimpleNetwork Protocol

--*/

#include "SimpleNetworkBBTestMain.h"

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Start() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.1
//
EFI_STATUS
BBTestStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStarted.
  // If not, change the state to EfiSimpleNetworkStarted.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.1.2.1
  // Call Start() function if network interface already started.
  //
  Status = SnpInterface->Start (SnpInterface);
  if ((Status == EFI_ALREADY_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStarted)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid001,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Start - Invoke Start() when network interface already started.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Stop() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.2
//
EFI_STATUS
BBTestStopConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.2.2.1
  // Call Stop() function if network interface not start.
  //
  Status = SnpInterface->Stop (SnpInterface);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid002,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Stop - Invoke Stop() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Initialize() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.3
//
EFI_STATUS
BBTestInitializeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.3.2.1
  // Call Initialize() function if network interface not start.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid003,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Initialize - Invoke Initialize() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Reset() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.4
//
EFI_STATUS
BBTestResetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.4.2.1
  // Call Reset() function when network interface not start.
  //
  Status = SnpInterface->Reset (SnpInterface, FALSE);

  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid004,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Reset - Invoke Reset() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.5
//
EFI_STATUS
BBTestShutdownConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.5.2.1
  // Call Shutdown() function if network interface not start.
  //
  Status = SnpInterface->Shutdown (SnpInterface);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid005,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown - Invoke Shutdown() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilter() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.6
//
EFI_STATUS
BBTestReceiveFilterConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.6.2.1
  // Call ReceiveFilters() function if network interface not start.
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, 0, NULL);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid006,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.6.2.2
  // Call ReceiveFilters() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, 0, NULL);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid007,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.6.2.3
  // Call ReceiveFilters() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //  Call ReceiveFilters with invalide Enable
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, ~(SnpInterface->Mode->ReceiveFilterMask), 0, FALSE, 0, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid008,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with invalid Enable.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  //  Call ReceiveFilters with invalide MCastFilterCnt
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, SnpInterface->Mode->MaxMCastFilterCount + 1, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid009,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with invalid MCastFilterCnt.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  //  Call ReceiveFilters with MCastFilterCnt not match MCastFilter
  //
  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, FALSE, 1, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid010,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() with MCastFilterCnt not match MCastFilter.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.7
//
EFI_STATUS
BBTestStationAddressConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  //EFI_MAC_ADDRESS                       MacAddress;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.7.2.1
  // Call StationAddress() function if network interface not start.
  //
  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid011,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke StationAddress() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.7.2.2
  // Call StationAddress() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid012,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke StationAddress() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Statistics() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.8
//
EFI_STATUS
BBTestStatisticsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  EFI_NETWORK_STATISTICS                StatisticsTable;
  UINTN                                 StatisticsSize;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  //
  // Assertion Point 5.8.2.1
  // Call Statistics() function if network interface not start.
  //
  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid014,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.8.2.2
  // Call Statistics() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid015,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.8.2.3
  // Call Statistics() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.8.2.4
  // Call Statistics() function with small buffer.
  //
  StatisticsSize = 0;

  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid017,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() with small buffer.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.MCastIPtoMAC() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.9
//
EFI_STATUS
BBTestMCastIPtoMACConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  EFI_IP_ADDRESS                        IP;
  EFI_MAC_ADDRESS                       MAC;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 5.9.2.1
  // Call MCastIPtoMAC() function if network interface not start.
  //
  IP.v4.Addr[0] = 255;
  IP.v4.Addr[1] = 255;
  IP.v4.Addr[2] = 255;
  IP.v4.Addr[3] = 255;
  EfiSetMem (&MAC, sizeof (EFI_MAC_ADDRESS), 0x0);

  Status = SnpInterface->MCastIPtoMAC(SnpInterface, FALSE, &IP, &MAC);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid018,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.MCastIPtoMAC - Invoke MCastIPtoMAC() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.NVData() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.10
//
EFI_STATUS
BBTestNVDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *Buffer;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  Status = gtBS->AllocatePool (EfiLoaderData, SnpInterface->Mode->NvRamSize, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.10.2.1
  // Call NvData() function if network interface not start.
  //

  Status = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamAccessSize, Buffer);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid020,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.10.2.2
  // Call NvData() function with invalid parameters.
  //

  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check Point A: "Offset" not be a multiple of NvRamAccessSize
  //
  Status = SnpInterface->NvData (SnpInterface, TRUE, (SnpInterface->Mode->NvRamAccessSize/2), SnpInterface->Mode->NvRamAccessSize, Buffer);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid021,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with Offset not be a multiple of NvRamAccessSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point B: "BufferSize" not be a multiple of NvRamAccessSize
  //
  Status = SnpInterface->NvData (SnpInterface, TRUE, 0, (SnpInterface->Mode->NvRamAccessSize/2), Buffer);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid022,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with BufferSize not be a multiple of NvRamAccessSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point C: "BufferSize" + "Offset" exceeds "NvRamSize"
  //
  Status = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamSize+100, Buffer);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid023,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() with BufferSize + Offset exceeds NvRamSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.11
//
EFI_STATUS
BBTestGetStatusConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *TxBuf;
  UINT32                                InterruptStatus;
  UINT32                                *pInterruptStatus;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  TxBuf = NULL;
  InterruptStatus = 0;

  //
  // Assertion Point 5.11.2.1
  // Call GetStatus() function if network interface not start.
  //
  Status = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid024,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.11.2.2
  // Call GetStatus () function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid025,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.11.2.3
  // Call GetStatus() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  pInterruptStatus = NULL;
  Status = SnpInterface->GetStatus (SnpInterface, pInterruptStatus, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid026,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() with invalid parameter.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Transmit() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.12
//
EFI_STATUS
BBTestTransmitConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *Buffer;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  HeaderSize = 0;
  BufferSize = 0;
  EfiSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  EfiSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  Protocol = SnpInterface->Mode->IfType;
  Status = gtBS->AllocatePool (EfiLoaderData, 2048, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Reset the MAC Address
  SnpInterface->StationAddress (SnpInterface, TRUE, NULL);

  //
  // Assertion Point 5.12.2.1
  // Call Transmit() function if network interface not start.
  //
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, NULL, NULL, 0);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid027,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.12.2.2
  // Call Transmit () function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, NULL, NULL, 0);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid028,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.12.2.3
  // Call Transmit() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check Point A: HeaderSize is nonzero and not equal to MediaHeaderSize.
  //
  HeaderSize = SnpInterface->Mode->MediaHeaderSize + 2;
  BufferSize = 1024;
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid029,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and not equal to MediaHeaderSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point B: BufferSize is less than  MediaHeaderSize.
  //
  HeaderSize = SnpInterface->Mode->MediaHeaderSize;
  BufferSize = SnpInterface->Mode->MediaHeaderSize - 2;
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid030,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with BufferSize is less than  MediaHeaderSize.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point C: Buffer is NULL.
  //
  BufferSize = 1024;
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, NULL, &SrcAddr, &DestAddr, &Protocol);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid031,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with Buffer is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point D: HeaderSize is nonzero and DestAddr is NULL.
  //
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, NULL, &Protocol);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid032,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and DestAddr is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point E: HeaderSize is nonzero and Protocol is NULL.
  //
  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SrcAddr, &DestAddr, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid033,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize is nonzero and Protocol is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Receive() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.13
//
EFI_STATUS
BBTestReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *Buffer;
  VOID                                  *Buffer1;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkStopped.
  // If not, change the state to EfiSimpleNetworkStopped.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkInitialized) {
    Status = SnpInterface->Shutdown (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Stop (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  Buffer1 = NULL;
  HeaderSize = 0;
  BufferSize = 0;
  EfiSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  EfiSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  Protocol = 0;
  Status = gtBS->AllocatePool (EfiLoaderData, 2048, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->AllocatePool (EfiLoaderData, 48, &Buffer1);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 5.13.2.1
  // Call Receive() function if network interface not start.
  //
  Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, NULL, NULL, 0);
  if ((Status == EFI_NOT_STARTED) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid038,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() when network interface not start.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.13.2.2
  // Call Receive() function if network interface not initialized.
  //
  Status = SnpInterface->Start (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, NULL, NULL, 0);
  if (Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid039,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() when network interface not initialized.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.13.2.3
  // Call Receive() function with invalid parameters.
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Enable receive filters
  //
  SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_UNICAST|EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST, 0, FALSE, 0, NULL);

  //
  // Check Point A: Buffer is NULL.
  //
  Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, NULL, &SrcAddr, &DestAddr, &Protocol);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid040,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() with Buffer is NULL.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 5.13.2.4
  // No Packet Received in the Network Interface when Receive()
  //
  Status = EFI_SUCCESS;
  BufferSize = 65;
  while (!EFI_ERROR(Status)) {
    Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);
  }
  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid042,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - No Packet Received in the Network Interface when Receive().",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->FreePool (Buffer1);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}