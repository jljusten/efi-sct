/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ScsiPassThruBBTestMain.c

Abstract:

  Test Driver of Scsi Pass Through Protocol

--*/

#include "ScsiPassThruBBTestMain.h"
#include "EfiTestLib.h"


//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SCSI_PASS_THRU_PROTOCOL_TEST_REVISION,
  IHV_SCSI_PASS_THRU_PROTOCOL_GUID,
  L"Scsi Pass Through Protocol Test",
  L"EFI1.10 Scsi Pass Through Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_FUNCTION_AUTO_GUID,
    L"GetNextDevice_Func",
    L"Invoke GetNextDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID,
    L"BuildDevicePath_Func",
    L"Invoke BuildDevicePath() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID,
    L"GetTargetLun_Func",
    L"Invoke GetTargetLun() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID,
    L"ResetChannel_Func",
    L"Invoke ResetChannel() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetChannelFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_FUNCTION_AUTO_GUID,
    L"ResetTarget_Func",
    L"Invoke ResetTarget() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID,
    L"PassThru_Func",
    L"Invoke PassThru() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruFunctionAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_NEXT_DEVICE_CONFORMANCE_AUTO_GUID,
    L"GetNextDevice_Conf",
    L"Test whether GetNextDevice() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextDeviceConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID,
    L"BuildDevicePath_Conf",
    L"Test whether BuildDevicePath() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID,
    L"GetTargetLun_Conf",
    L"Test whether GetTargetLun() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetTargetLunConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_CONFORMANCE_AUTO_GUID,
    L"ResetTarget_Conf",
    L"Test whether ResetTarget() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetTargetConformanceAutoTest
  },

  {
    SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID,
    L"PassThru_Conf",
    L"Test whether PassThru() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruConformanceAutoTest
  },
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBBTestScsiPassThru)

/**
 *  Scsi Pass Through Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestScsiPassThruProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

EFI_STATUS
GetScsiDevice (
  IN EFI_SCSI_PASS_THRU_PROTOCOL *ScsiPassThru,
  IN OUT UINT32                  *Target,
  IN OUT UINT64                  *Lun
  )
{
  EFI_STATUS                             Status;
  EFI_DEVICE_PATH_PROTOCOL               *DevicePath;

  *Target = 0xFFFFFFFF;
  //
  // Get the first device's Target and Lun
  //
  Status = ScsiPassThru->GetNextDevice (ScsiPassThru, Target, Lun);
  while (!EFI_ERROR(Status)) {
    //
    // Probe if there is device present
    //
    Status = ScsiPassThru->BuildDevicePath (ScsiPassThru, *Target, *Lun, &DevicePath);
    if (!EFI_ERROR(Status)) {
      gtBS->FreePool (DevicePath);
      return EFI_SUCCESS;
    }
    //
    // Get the next device's Target and Lun
    //
    Status = ScsiPassThru->GetNextDevice (ScsiPassThru, Target, Lun);
  }
  return Status;
}