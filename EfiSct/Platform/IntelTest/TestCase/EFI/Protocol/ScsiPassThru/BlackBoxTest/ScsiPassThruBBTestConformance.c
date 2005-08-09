/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ScsiPassThruBBTestConformance.c

Abstract:

  Conformance Test Cases of Scsi Pass Through Protocol

--*/


#include "ScsiPassThruBBTestMain.h"

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetNextDevice Conformance Test.
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
BBTestGetNextDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.1.2.1
  // Call GetNextDevice() with invalid parameter.
  //
  NewTarget = 0xFFFFFFFF;

  //
  // Get First Device Target and Lun.
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call GetNextDevice with invalid Target.
  //
  Target = 0xEEEEEEEE;
  Lun    = NewLun;
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &Target, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid002,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  //
  // Check point 2, call GetNextDevice with invalid Lun.
  //
  Target = NewTarget;
  Lun    = 0xEEEEEEEE;
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &Target, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid003,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice - call GetNextDevice with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  //
  // Check point 3, Call GetNextDevice() with Target=0xFFFFFFFF to get the
  //                first device. Then call it again to get the next device.
  //                Use the Target and Lun return from the first call to call
  //                the function.
  //
  Target = NewTarget;
  Lun = NewLun;

  //
  // Get the second Device Target and Lun.
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_SCSI_PASS_THRU_PROTOCOL.GetNextDevice",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.BuildDevicePath Conformance Test.
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
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.2.2.1
  // Call BuildDevicePath() with invalid Target and invalid Lun.
  //
  Status = GetScsiDevice (ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call BuildDevicePath with invalid Target.
  //
  Target = 0xEEEEEEEE;
  Lun    = NewLun;
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid004,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  //
  // Check point 2, call BuildDevicePath with invalid Lun.
  //
  Target = NewTarget;
  Lun    = 0xEEEEEEEE;
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, &DevicePath);

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid005,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  //
  // Assertion Point 4.2.2.2
  // Call BuildDevicePath() with NULL DevicePath.
  //
  Target = NewTarget;
  Lun    = NewLun;
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid006,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath - call BuildDevicePath with NULL DevicePath.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %d",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );



  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.GetTargetLun Conformance Test.
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
BBTestGetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.3.2.1
  // Call GetTargetLun()with NULL DevicePath, NULL Target and NULL Lun.
  //
  Status = GetScsiDevice (ScsiPassThru, &Target, &Lun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Get the valid Device Path Node.
  //
  Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, Target, Lun, &DevicePath);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath",
                   L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                   __FILE__,
                   __LINE__,
                   Status,
                   Target,
                   Lun
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check Point 1. NULL Device Path.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, NULL, &Target, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid007,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Device Path",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point 2. NULL Target.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, NULL, &Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid008,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Target",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point 3. NULL Lun.
  //
  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, &Target, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid009,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with NULL Lun",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Assertion Point 4.3.2.2
  // Call GetTargetLun()with unsupported DevicePath.
  //

  //
  // Set the Device Path to Non Scsi Device Path.
  //
  DevicePath->Type    = 5;
  DevicePath->SubType = 1;

  Status = ScsiPassThru->GetTargetLun (ScsiPassThru, DevicePath, &Target, &Lun);

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //Free the DevicePath.
  gtBS->FreePool (DevicePath);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid010,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.GetTargetLun - Invoke GetTargetLun() with unsupported Device Path",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.ResetTarget Conformance Test.
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
BBTestResetTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SCSI_PASS_THRU_PROTOCOL          *ScsiPassThru;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               Target;
  UINT64                               Lun;
  UINT32                               NewTarget;
  UINT64                               NewLun;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.4.2.1
  // Call ResetTarget() with invalid Target and invalid Lun.
  //
  Status = GetScsiDevice (ScsiPassThru, &NewTarget, &NewLun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Check point 1, call GetNextDevice with invalid Target.
  //
  Target = 0xEEEEEEEE;
  Lun    = NewLun;
  Status = ScsiPassThru->ResetTarget (ScsiPassThru, Target, Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid011,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetTarget - call ResetTarget with invalid Target.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  //
  // Check point 2, call GetNextDevice with invalid Lun.
  //
  Target = NewTarget;
  Lun    = 0xEEEEEEEE;
  Status = ScsiPassThru->ResetTarget (ScsiPassThru, Target, Lun);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid012,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.ResetTarget - call ResetTarget with invalid Lun.",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SCSI_PASS_THRU_PROTOCOL_GUID.PassThru Conformance Test.
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
BBTestPassThruConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_SCSI_PASS_THRU_PROTOCOL            *ScsiPassThru;
  EFI_TEST_ASSERTION                     AssertionType;
  UINT32                                 Target;
  UINT64                                 Lun;
  EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET Packet;
  UINT8                                  Cdb[6];
  UINT8                                  Data[100];
  //UINT8                                  Count;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  ScsiPassThru = (EFI_SCSI_PASS_THRU_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 4.5.2.1
  // Call PassThru() with too long TransferLength.
  //
  Status = GetScsiDevice (ScsiPassThru, &Target, &Lun);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Can't Get any Scsi Device",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // Initialize the Request Packet.
  //
  EfiCommonLibZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  EfiCommonLibZeroMem (Cdb, 6);
  EfiCommonLibZeroMem (Data, 100);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 100;

  Packet.Timeout = 0;
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  Packet.DataBuffer = Data;
  Packet.TransferLength = 0xFFFFFFFF;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, NULL);

  if (Status == EFI_BAD_BUFFER_SIZE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid013,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with with too long TransferLength",
                 L"%a:%d:Status - %r, Target - %d, Lun - %ld, The max length is %d",
                 __FILE__,
                 __LINE__,
                 Status,
                 Target,
                 Lun,
                 Packet.TransferLength
                 );

  //
  // Assertion Point 4.5.2.3
  // Call PassThru() with invalid parameter.
  //
  EfiCommonLibZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  EfiCommonLibZeroMem (Cdb, 6);
  EfiCommonLibZeroMem (Data, 100);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 100;

  Packet.Timeout = 0;
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  Packet.DataBuffer = Data;
  Packet.TransferLength = 100;
  Packet.DataDirection = 0;

  //
  // Check Point 1. Invalid Target
  //

  Status = ScsiPassThru->PassThru (ScsiPassThru, 0xEEEEEEEE, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid016,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Target",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point 2. Invalid Lun
  //
  EfiCommonLibZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));
  EfiCommonLibZeroMem (Cdb, 6);
  EfiCommonLibZeroMem (Data, 100);

  // Set to OP_INQUIRY.
  Cdb[0] = 0x12;
  Cdb[1] = (UINT8)(((UINT8)Lun << 5) & 0xE0);
  Cdb[4] = 100;

  Packet.Timeout = 0;
  Packet.Cdb = Cdb;
  Packet.CdbLength = 6;
  Packet.DataBuffer = Data;
  Packet.TransferLength = 100;
  Packet.DataDirection = 0;

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, 0xEEEEEEEE, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid017,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid Lun",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point 3. Invalid ScsiRequestPacket.
  //
  EfiCommonLibZeroMem (&Packet, sizeof (EFI_SCSI_PASS_THRU_SCSI_REQUEST_PACKET));

  Status = ScsiPassThru->PassThru (ScsiPassThru, Target, Lun, &Packet, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gScsiPassThruBBTestConformanceAssertionGuid018,
                 L"EFI_SCSI_PASS_THRU_PROTOCOL.PassThru - Call PassThru() with invalid ScsiRequestPacket",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
  return EFI_SUCCESS;
}
