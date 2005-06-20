/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleNetworkBBTestFunction.c

Abstract:

  Basic Test Cases of SimpleNetwork Protocol

--*/

#include "SimpleNetworkBBTestMain.h"
#include EFI_TEST_PROTOCOL_DEFINITION (TestLoggingLibrary)

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Start() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
BBTestStartFunctionTest (
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
  // Assertion Point 4.1.2.1
  // Call Start() function to change the state from "Stopped" to "Started".
  //
  Status = SnpInterface->Start (SnpInterface);
  if ((Status == EFI_SUCCESS) && (SnpInterface->Mode->State == EfiSimpleNetworkStarted)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid001,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Start - Invoke Start() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Stop() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
BBTestStopFunctionTest (
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
  // Assertion Point 4.2.2.1
  // Call Stop() function to change the state from "Started" to "Stopped".
  //
  Status = SnpInterface->Stop (SnpInterface);
  if ((Status == EFI_SUCCESS) && (SnpInterface->Mode->State == EfiSimpleNetworkStopped)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid002,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Stop - Invoke Stop() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Initialize() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
BBTestInitializeFunctionTest (
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
  // Assertion Point 4.3.2.1
  // Call Initialize() function to change the state from "Started" to "Initialized".
  //
  Status = SnpInterface->Initialize (SnpInterface, 0, 0);
  if ((Status == EFI_SUCCESS) && (SnpInterface->Mode->State == EfiSimpleNetworkInitialized)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid003,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Initialize - Invoke Initialize() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.3.2.2
  // Call Initialize() function with extra Tx/Rx specified to change the state from "Started" to "Initialized".
  //
  Status = SnpInterface->Shutdown (SnpInterface);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Initialize (SnpInterface, 32, 32);
  if ((Status == EFI_SUCCESS) && (SnpInterface->Mode->State == EfiSimpleNetworkInitialized)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid004,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Initialize - Invoke Initialize() with extra Tx/Rx specified and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Reset() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
BBTestResetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  EFI_SIMPLE_NETWORK_MODE               Mode;
  UINT32                                InterruptStatus;
  VOID                                  *TxBuf;
  EFI_NETWORK_STATISTICS                StatisticsTable1;
  UINTN                                 StatisticsSize1;
  EFI_NETWORK_STATISTICS                StatisticsTable2;
  UINTN                                 StatisticsSize2;
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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 4.4.2.1
  // Call Reset() function with ExtendedVerification is FALSE.
  //
  EfiSetMem (&Mode, sizeof (EFI_SIMPLE_NETWORK_MODE), 0x0);
  EfiCommonLibCopyMem (&Mode, SnpInterface->Mode, sizeof (EFI_SIMPLE_NETWORK_MODE));

  EfiSetMem (&StatisticsTable1, sizeof (EFI_NETWORK_STATISTICS), 0x0);
  StatisticsSize1 = sizeof (EFI_NETWORK_STATISTICS);
  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize1, &StatisticsTable1);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = SnpInterface->Reset (SnpInterface, FALSE);

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if ((Mode.State != SnpInterface->Mode->State) ||
      (Mode.ReceiveFilterMask != SnpInterface->Mode->ReceiveFilterMask) ||
      (Mode.ReceiveFilterSetting != SnpInterface->Mode->ReceiveFilterSetting) ||
      EfiCompareMem (&(Mode.CurrentAddress), &(SnpInterface->Mode->CurrentAddress), sizeof (EFI_MAC_ADDRESS)) ||
      EfiCompareMem (&(Mode.PermanentAddress), &(SnpInterface->Mode->PermanentAddress), sizeof (EFI_MAC_ADDRESS))) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  TxBuf = NULL;
  Status1 = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  if (EFI_ERROR(Status1)) {
    return Status1;
  }
  if (InterruptStatus != 0 || TxBuf != NULL) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  EfiSetMem (&StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS), 0x0);
  StatisticsSize2 = sizeof (EFI_NETWORK_STATISTICS);
  Status1 = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize2, &StatisticsTable2);
  if (EFI_ERROR(Status1)) {
    return Status1;
  }

  if ((StatisticsSize1 != StatisticsSize2) ||
      EfiCompareMem (&StatisticsTable1, &StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS))) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid005,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Reset - Invoke Reset() with ExtendedVerification is FALSE and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.4.2.2
  // Call Reset() function with ExtendedVerification is TRUE.
  //
  Status = SnpInterface->Reset (SnpInterface, TRUE);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid006,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Reset - Invoke Reset() with ExtendedVerification is TRUE and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
BBTestShutdownFunctionTest (
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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 4.5.2.1
  // Call Shutdown() function.
  //
  Status = SnpInterface->Shutdown (SnpInterface);

  if ((Status == EFI_SUCCESS) &&
      (SnpInterface->Mode->State == EfiSimpleNetworkStarted)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid007,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Shutdown - Invoke Shutdown() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilter() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.6
//
EFI_STATUS
BBTestReceiveFilterFunctionTest (
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
  EFI_SIMPLE_NETWORK_MODE               Mode;
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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  EfiSetMem (&Mode, sizeof (EFI_SIMPLE_NETWORK_MODE), 0x0);
  EfiCommonLibCopyMem (&Mode, SnpInterface->Mode, sizeof (EFI_SIMPLE_NETWORK_MODE));

  //
  // Assertion Point 4.6.2.1
  // Modify multicast receive filters masks.
  //

  // Check point B. Disable Specified bit.
  //Status = SnpInterface->ReceiveFilters(SnpInterface, 0, SnpInterface->Mode->ReceiveFilterMask, FALSE, 0, NULL);
  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS, FALSE, 0, NULL);

  if ((Status == EFI_SUCCESS) &&
      ((SnpInterface->Mode->ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid008,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() to modify multicast receive filters masks(Disable Specified bit) and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Filter - %x",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->ReceiveFilterSetting
                 );

  // Check point A. Enable Specified bit.
  Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS, 0, FALSE, 0, NULL);

  if ((Status == EFI_SUCCESS) &&
      ((SnpInterface->Mode->ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) != 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid009,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters () to modify multicast receive filters masks (Enable Specified bit) and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Filter - %x",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->ReceiveFilterSetting
                 );

  // Check point C. Enable and Disable Specified bit together.
  Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS, EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS, FALSE, 0, NULL);

  if ((Status == EFI_SUCCESS) &&
      ((SnpInterface->Mode->ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid010,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() to modify multicast receive filters masks(Enable and Disable Specified bit together) and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Filter - %x",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->ReceiveFilterSetting
                 );

  //
  // Assertion Point 4.6.2.2
  // Modify multicast receive filters list.
  //
  EfiSetMem (&MAC, sizeof (MAC), 0x00);
  MAC.Addr[0] = 0x01;
  MAC.Addr[1] = 0x00;
  MAC.Addr[2] = 0x5e;
  MAC.Addr[3] = 0x00;
  MAC.Addr[4] = 0x00;
  MAC.Addr[5] = 0x02;
  Status = SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST, 0, FALSE, 1, &MAC);
  if ((Status == EFI_SUCCESS) &&
      (SnpInterface->Mode->State == EfiSimpleNetworkInitialized) &&
      (SnpInterface->Mode->MCastFilterCount == 1) &&
      (!EfiCompareMem (SnpInterface->Mode->MCastFilter, &MAC, sizeof (EFI_MAC_ADDRESS)))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid011,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() to modify multicast receive filters list and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Filter - %x, Mask - %x, Count - %d, Address - %x,%x,%x",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->ReceiveFilterSetting,
                 SnpInterface->Mode->ReceiveFilterMask,
                 SnpInterface->Mode->MCastFilterCount,
                 SnpInterface->Mode->MCastFilter[0].Addr[0],
                 SnpInterface->Mode->MCastFilter[0].Addr[5],
                 SnpInterface->Mode->MCastFilter[1].Addr[0]
                 );

  //
  // Assertion Point 4.6.2.3
  // Reset multicast receive filters list.
  //

  Status = SnpInterface->ReceiveFilters (SnpInterface, 0, 0, TRUE, 0, NULL);

  if ((Status == EFI_SUCCESS) &&
      (SnpInterface->Mode->State == EfiSimpleNetworkInitialized) &&
      (SnpInterface->Mode->MCastFilterCount == Mode.MCastFilterCount) &&
      (CompareMem (SnpInterface->Mode->MCastFilter, Mode.MCastFilter, Mode.MCastFilterCount*sizeof (EFI_MAC_ADDRESS)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid012,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.ReceiveFilters - Invoke ReceiveFilters() to reset multicast receive filters list and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Filter - %x, Mask - %x,Count - %d(%d), Address - %x, %x, %x",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->ReceiveFilterSetting,
                 SnpInterface->Mode->ReceiveFilterMask,
                 SnpInterface->Mode->MCastFilterCount,
                 Mode.MCastFilterCount,
                 SnpInterface->Mode->MCastFilter[0].Addr[0],
                 SnpInterface->Mode->MCastFilter[0].Addr[5],
                 SnpInterface->Mode->MCastFilter[1].Addr[0]
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.7
//
EFI_STATUS
BBTestStationAddressFunctionTest (
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
  EFI_MAC_ADDRESS                       MacAddress;
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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 4.7.2.1
  // Call StationAddress to reset its MAC Address.
  //

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);

  if ((Status == EFI_SUCCESS) &&
      (!EfiCompareMem (&SnpInterface->Mode->CurrentAddress, &SnpInterface->Mode->PermanentAddress, sizeof (EFI_MAC_ADDRESS)))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid013,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke ReceiveFilters() to reset its MAC Address and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.7.2.2
  // Call StationAddress to modify its MAC Address.
  //
  EfiSetMem (&MacAddress, sizeof (EFI_MAC_ADDRESS), 0x0);

  Status = SnpInterface->StationAddress (SnpInterface, FALSE, &MacAddress);

  if ((Status == EFI_SUCCESS) &&
      (!EfiCompareMem (&SnpInterface->Mode->CurrentAddress, &MacAddress, sizeof (EFI_MAC_ADDRESS)))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid014,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.StationAddress - Invoke ReceiveFilters() to modify its MAC Address and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Statistics() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.8
//
EFI_STATUS
BBTestStatisticsFunctionTest (
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
  EFI_NETWORK_STATISTICS                StatisticsTable1;
  EFI_NETWORK_STATISTICS                StatisticsTable2;
  UINTN                                 StatisticsSize;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;

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
  // Get the Logginh Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 4.8.2.2
  // Collect statistics information without reset the statistics.
  //
  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  EfiSetMem (&StatisticsTable1, sizeof (EFI_NETWORK_STATISTICS), 0x0);
  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable1);
  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  EfiSetMem (&StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS), 0x0);
  Status = SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable2);

  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)& (StatisticsTable1), sizeof (EFI_NETWORK_STATISTICS)/2, EFI_DUMP_HEX);
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&(StatisticsTable2), sizeof (EFI_NETWORK_STATISTICS)/2, EFI_DUMP_HEX);

  if ((Status == EFI_SUCCESS) &&
      (!EfiCompareMem (&StatisticsTable1, &StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS)))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid015,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() without reset the statistics and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.8.2.1
  // Collect statistics information and reset the statistics.
  //
  EfiSetMem (&StatisticsTable1, sizeof (EFI_NETWORK_STATISTICS), 0x0);
  EfiSetMem (&StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS), 0x0);

  Status = SnpInterface->Statistics (SnpInterface, TRUE, &StatisticsSize, &StatisticsTable1);
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&(StatisticsTable1), sizeof (EFI_NETWORK_STATISTICS)/2, EFI_DUMP_HEX);


  if ((Status == EFI_SUCCESS) &&
      (!EfiCompareMem (&StatisticsTable1, &StatisticsTable2, sizeof (EFI_NETWORK_STATISTICS)))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid016,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Statistics - Invoke Statistics() and reset the statistics and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.MCastIPtoMAC() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.9
//
EFI_STATUS
BBTestMCastIPtoMACFunctionTest (
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
  EFI_MAC_ADDRESS                       MAC1;
  EFI_MAC_ADDRESS                       MAC2;

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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Assertion Point 4.9.2.1
  // Change IPV4 to Multicast MAC
  //
  IP.v4.Addr[0] = 234;
  IP.v4.Addr[1] = 0;
  IP.v4.Addr[2] = 0;
  IP.v4.Addr[3] = 1;
  EfiSetMem (&MAC1, sizeof (EFI_MAC_ADDRESS), 0x0);
  EfiSetMem (&MAC2, sizeof (EFI_MAC_ADDRESS), 0x0);
  MAC2.Addr[0] = 0x01;
  MAC2.Addr[1] = 0x00;
  MAC2.Addr[2] = 0x5E;
  MAC2.Addr[3] = 0x00;
  MAC2.Addr[4] = 0x00;
  MAC2.Addr[5] = 0x01;

  Status = SnpInterface->MCastIPtoMAC(SnpInterface, FALSE, &IP, &MAC1);

  //
  // Do not check the MAC address, because this is based on ethernet.
  //

  // if ((Status == EFI_SUCCESS) && (!EfiCompareMem(&MAC1, &MAC2, sizeof(EFI_MAC_ADDRESS)))) {
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid017,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.MCastIPtoMAC - Invoke MCastIPtoMAC() and verify interface correctness within test case",
                 L"%a:%d:Status - %r, MAC address - %02x%02x%02x%02x%02x%02x",
                 __FILE__,
                 __LINE__,
                 Status,
                 MAC1.Addr[0],
                 MAC1.Addr[1],
                 MAC1.Addr[2],
                 MAC1.Addr[3],
                 MAC1.Addr[4],
                 MAC1.Addr[5]
                 );

  //
  // Assertion Point 4.9.2.2
  // Change IPV6 to Multicast MAC
  //

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.NVData() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.10
//
EFI_STATUS
BBTestNVDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *Buffer;
  VOID                                  *Buffer1;
  VOID                                  *Buffer2;

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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  Buffer = NULL;
  Buffer1 = NULL;
  Buffer2 = NULL;
  Status = gtBS->AllocatePool (EfiLoaderData, SnpInterface->Mode->NvRamSize, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->AllocatePool (EfiLoaderData, SnpInterface->Mode->NvRamSize, &Buffer1);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gtBS->AllocatePool (EfiLoaderData, SnpInterface->Mode->NvRamSize, &Buffer2);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 4.10.2.1
  // Read NVRam
  //

  //Check Point A(0, n*NvRamAccessSize)
  EfiSetMem (Buffer, SnpInterface->Mode->NvRamSize, 0x0);
  Status = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamSize, Buffer);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid018,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() to read(0, n*NvRamAccessSize) and verify interface correctness within test case",
                 L"%a:%d:Status - %r, NvRamSize - %d, NvRamAccessSize - %d",
                 __FILE__,
                 __LINE__,
                 Status,
                 SnpInterface->Mode->NvRamSize,
                 SnpInterface->Mode->NvRamAccessSize
                 );

  //Check Point B(NvRamAccessSize, (n-1)*NvRamAccessSize)
  EfiSetMem (Buffer, SnpInterface->Mode->NvRamSize, 0x0);
  Status = SnpInterface->NvData (SnpInterface, TRUE, SnpInterface->Mode->NvRamAccessSize, (SnpInterface->Mode->NvRamSize - SnpInterface->Mode->NvRamAccessSize), Buffer);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid019,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() to read(NvRamAccessSize, (n-1)*NvRamAccessSize) and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //Check Point C((n-1)*NvRamAccessSize, NvRamAccessSize)
  EfiSetMem (Buffer, SnpInterface->Mode->NvRamSize, 0x0);
  Status = SnpInterface->NvData (SnpInterface, TRUE, (SnpInterface->Mode->NvRamSize - SnpInterface->Mode->NvRamAccessSize), SnpInterface->Mode->NvRamAccessSize, Buffer);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid020,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() to read((n-1)*NvRamAccessSize, NvRamAccessSize) and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.10.2.2
  // Write NVRam
  //

  EfiSetMem (Buffer1, SnpInterface->Mode->NvRamSize, 0x0);
  EfiSetMem (Buffer2, SnpInterface->Mode->NvRamSize, 0x0);
  // Save the NvData
  Status1 = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamSize, Buffer2);
    if (EFI_ERROR(Status1)) {
    return Status1;
  }

  Status = SnpInterface->NvData (SnpInterface, FALSE, 0, SnpInterface->Mode->NvRamSize, Buffer);

  // Read the buffer content which was written just now.
  Status1 = SnpInterface->NvData (SnpInterface, TRUE, 0, SnpInterface->Mode->NvRamSize, Buffer1);
    if (EFI_ERROR(Status1)) {
    return Status1;
  }

  // recover the NvData
  Status1 = SnpInterface->NvData (SnpInterface, FALSE, 0, SnpInterface->Mode->NvRamSize, Buffer2);
    if (EFI_ERROR(Status1)) {
    return Status1;
  }

  if ((Status == EFI_SUCCESS) &&
      (!EfiCompareMem (Buffer, Buffer1, SnpInterface->Mode->NvRamSize))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid021,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.NvData - Invoke NvData() to write and verify interface correctness within test case",
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
  Status = gtBS->FreePool (Buffer2);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.11
//
EFI_STATUS
BBTestGetStatusFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  VOID                                  *TxBuf;
  UINT32                                InterruptStatus;

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
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  TxBuf = NULL;
  InterruptStatus = 0;

  //
  // Assertion Point 4.11.2.1
  // Call GetStatus()
  //
  Status = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);
  Status1 = SnpInterface->GetStatus (SnpInterface, &InterruptStatus, &TxBuf);

  if (Status == EFI_SUCCESS && InterruptStatus == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid022,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.GetStatus - Invoke GetStatus() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Transmit() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.12
//
EFI_STATUS
BBTestTransmitFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_STATUS                            StatCode;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_SIMPLE_NETWORK_STATE              State;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  VOID                                  *Buffer;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;
  EFI_NETWORK_STATISTICS                StatisticsTable;
  EFI_NETWORK_STATISTICS                StatisticsTable1;
  UINTN                                 StatisticsSize;
  UINTN                                 WaitIndex;
  EFI_INPUT_KEY                         Key;
  EFI_EVENT                             TimeoutEvent;
  UINT32                                IntStatus;
  VOID                                  *TxBuf;


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
  // Get the Logginh Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Initialize the variables.
  //

  Buffer = NULL;
  HeaderSize = 0;
  BufferSize = 0;
  EfiSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0xFF);
  EfiSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0xFF);
  Protocol = 0;
  Status = gtBS->AllocatePool (EfiLoaderData, 1024, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 4.12.2.2
  // Call Transmit() with HeaderSize != 0
  //

  //Need to put correct conten of a packet into the Buffer.
  EfiSetMem (Buffer, 1024, 0x0);
  HeaderSize = SnpInterface->Mode->MediaHeaderSize;
  BufferSize = 128;
  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);

  Protocol = 0x0806;

  //
  // Get the Statistics before invoke the Transmit();
  //
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);

  Status = SnpInterface->Transmit (SnpInterface, HeaderSize, BufferSize, Buffer, &SnpInterface->Mode->CurrentAddress, &DestAddr, &Protocol);

  //
  // Wait the package to be sent
  //
  if (!EFI_ERROR(Status)) {
    StatCode =gtBS->CreateEvent (
        EFI_EVENT_TIMER,
        EFI_TPL_CALLBACK,
        NULL,
        NULL,
        &TimeoutEvent
        );
    if (EFI_ERROR(StatCode)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - CreateEvent",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     StatCode
                     );
      return StatCode;
    }

    StatCode = gtBS->SetTimer (
        TimeoutEvent,
        TimerRelative,
        50000);  /* 5 milliseconds */
    if (EFI_ERROR(StatCode)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - SetTimer",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     StatCode
                     );
      return StatCode;
    }

    for (;;) {
      StatCode = SnpInterface->GetStatus (SnpInterface, &IntStatus, &TxBuf);

      if (EFI_ERROR(StatCode)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - GetStatus",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       __LINE__,
                       StatCode
                       );
        return StatCode;
      }

      if (TxBuf == Buffer) {
        break;
      }

      if (!EFI_ERROR(gBS->CheckEvent (TimeoutEvent))) {
        StatCode = EFI_TIMEOUT;
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Time out",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       __LINE__,
                       StatCode
                       );
        return StatCode;
      }
    }

    gBS->CloseEvent (TimeoutEvent);
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (EFI_ERROR(Status) || SnpInterface->Mode->State != EfiSimpleNetworkInitialized) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable1);

  //
  // Verify the functionality manually.
  //
  Print (L"Please verify whether the packet is captured by the sniffert, right press \"Y\", wrong press \"N\"");

  //
  // Get the input key.
  //
  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if ((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      Print (L"Please press \"Y\" or \"N\"\n");
    }
  }
  if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid024,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Transmit - Invoke Transmit() with HeaderSize != 0 and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_NETWORK_PROTOCOL.Receive() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.13
//
EFI_STATUS
BBTestReceiveFunctionTest (
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
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  VOID                                  *Buffer;
  UINTN                                 HeaderSize;
  UINTN                                 BufferSize;
  EFI_MAC_ADDRESS                       SrcAddr;
  EFI_MAC_ADDRESS                       DestAddr;
  UINT16                                Protocol;
  EFI_NETWORK_STATISTICS                StatisticsTable;
  EFI_NETWORK_STATISTICS                StatisticsTable1;
  UINTN                                 StatisticsSize;
  UINTN                                 WaitIndex;
  EFI_INPUT_KEY                         Key;


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
  // Get the Logginh Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_SIMPLE_NETWORK_PROTOCOL Protocol interface to be tested
  //
  SnpInterface = (EFI_SIMPLE_NETWORK_PROTOCOL *)ClientInterface;

  //
  // Check whether the state of network interface is EfiSimpleNetworkInitialized.
  // If not, change the state to EfiSimpleNetworkInitialized.
  //
  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStopped) {
    Status = SnpInterface->Start (SnpInterface);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  };

  State = SnpInterface->Mode->State;
  if (State == EfiSimpleNetworkStarted) {
    Status = SnpInterface->Initialize (SnpInterface, 0, 0);
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  //
  // Enable receive filters
  //
  SnpInterface->ReceiveFilters (SnpInterface, EFI_SIMPLE_NETWORK_RECEIVE_UNICAST|EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST, 0, FALSE, 0, NULL);

  //
  // Initialize the variables.
  //

  Buffer = NULL;
  HeaderSize = 0;
  BufferSize = 0;
  EfiSetMem (&SrcAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  EfiSetMem (&DestAddr, sizeof (EFI_MAC_ADDRESS), 0x0);
  Protocol = 0;
  Status = gtBS->AllocatePool (EfiLoaderData, 1024, &Buffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  EfiSetMem (Buffer, 1024, 0x0);
  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);

  //
  // Get the Statistics before invoke the Receive();
  //
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);

  //
  // Wait for the host send the packet.
  //
  Print (L"\nWait for the host send, yes press \"Y\", no press \"N\"\n");

  //
  // Get the input key.
  //
  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if ((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      Print (L"Please press \"Y\" or \"N\"");
    }
  }

  //
  // BufferSize is smaller than the received Packets.
  //
  BufferSize = 0;
  Status = SnpInterface->Receive (SnpInterface, 0, &BufferSize, Buffer, NULL, NULL, 0);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestConformanceAssertionGuid041,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() with BufferSize is smaller than the received Packets.",
                 L"%a:%d:Status - %r, BufferSize Needed - %d",
                 __FILE__,
                 __LINE__,
                 Status,
                 BufferSize
                 );

  //
  // Assertion Point 4.13.2.1
  // Call Receive() with all optional NULL
  //
  BufferSize = 1024;
  Status = SnpInterface->Receive (SnpInterface, 0, &BufferSize, Buffer, NULL, NULL, 0);

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (EFI_ERROR(Status) || SnpInterface->Mode->State != EfiSimpleNetworkInitialized) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable1);

  //
  // Verify the functionality manually.
  //
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)Buffer, (UINT32)BufferSize/2, EFI_DUMP_HEX);
  Print (L"Please verify whether the received packet is right?\nRight press \"Y\", wrong press \"N\"\n");

  //
  // Get the input key.
  //
  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if ((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      Print (L"Please press \"Y\" or \"N\"");
    }
  }
  if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid025,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() with all optional NULL and verify interface correctness within test case",
                 L"%a:%d:Status - %r, Received Buffer Size - %d",
                 __FILE__,
                 __LINE__,
                 Status,
                 BufferSize
                 );

  //
  // Assertion Point 4.13.2.2
  // Call Receive() with all optional parameters
  //

  EfiSetMem (Buffer, 1024, 0x0);
  BufferSize = 1024;
  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);

  //
  // Get the Statistics before invoke the Receive();
  //
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable);

  //
  // Wait for the host send the packet.
  //
  Print (L"Wait for the host send, yes press \"Y\", no press \"N\"");

  //
  // Get the input key.
  //
  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if ((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      Print (L"Please press \"Y\" or \"N\"");
    }
  }
  Status = SnpInterface->Receive (SnpInterface, &HeaderSize, &BufferSize, Buffer, &SrcAddr, &DestAddr, &Protocol);

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (EFI_ERROR(Status) || SnpInterface->Mode->State != EfiSimpleNetworkInitialized) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
  SnpInterface->Statistics (SnpInterface, FALSE, &StatisticsSize, &StatisticsTable1);

  //
  // Verify the functionality manually.
  //
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)Buffer, (UINT32)BufferSize/2, EFI_DUMP_HEX);
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&SrcAddr, sizeof (EFI_MAC_ADDRESS)/2, EFI_DUMP_HEX);
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&DestAddr, sizeof (EFI_MAC_ADDRESS)/2, EFI_DUMP_HEX);
  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&Protocol, sizeof (UINT16)/2, EFI_DUMP_HEX);
  Print (L"Please verify whether the received packet is right?\nRight press \"Y\", wrong press \"N\"\n");

  //
  // Get the input key.
  //
  while (1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if ((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      Print (L"Please press \"Y\" or \"N\"");
    }
  }
  if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleNetworkBBTestFunctionAssertionGuid026,
                 L"EFI_SIMPLE_NETWORK_PROTOCOL.Receive - Invoke Receive() with all optional parameters and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
