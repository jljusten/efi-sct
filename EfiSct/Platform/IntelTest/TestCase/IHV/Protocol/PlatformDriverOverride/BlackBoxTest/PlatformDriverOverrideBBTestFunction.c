/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  PlatformDriverOverrideBBTestFunction.c

Abstract:

  Interface Function Test Cases of PlatformDriverOverride Protocol

--*/


#include "PlatformDriverOverrideBBTestMain.h"

UINT8 EnterEvent;

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriver Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
BBTestGetDriverFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_HANDLE                             *DriverImageHandle;

  //
  // Verify whether it is one of IHV interfaces
  //
  if (! IsIhvInterface (ClientInterface, SupportHandle)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.1
  // Retrieve the image handle of the platform override driver for a controller in the system.
  //

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);


  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImageHandle = NULL;
    while(!EFI_ERROR(Status)) {
      Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles[HandleIndex], DriverImageHandle);
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPlatformDriverOverrideBBTestFunctionAssertionGuid001,
                   L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver - Invoke GetDriver() and verify interface correctness within test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (Handles) {
    FreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriverPath Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
BBTestGetDriverPathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath;

  //
  // Verify whether it is one of IHV interfaces
  //
  if (! IsIhvInterface (ClientInterface, SupportHandle)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.1
  // 3.2.2.1  Retrieves the device path of the platform override driver for a controller in the system.
  //

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);


  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImagePath = NULL;
    while(!EFI_ERROR(Status)) {
      Status = PlatformDriverOverride->GetDriverPath(PlatformDriverOverride, Handles[HandleIndex], &DriverImagePath);
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPlatformDriverOverrideBBTestFunctionAssertionGuid002,
                   L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath - Invoke GetDriverPath() and verify interface correctness within test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (Handles) {
    FreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.DriverLoaded Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
BBTestDriverLoadedFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *PlatformDriverOverride;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                             *Handles;
  EFI_HANDLE                             ControllerHandle;
  UINTN                                  HandlesNo;
  UINTN                                  HandleIndex;
  EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath;
  EFI_HANDLE                             DriverImageHandle;
  EFI_HANDLE                             NewDriverImageHandle;
  EFI_DEVICE_PATH_PROTOCOL               *FilePath;
  CHAR16                                 *TempFileName;

  //
  // Verify whether it is one of IHV interfaces
  //
  if (! IsIhvInterface (ClientInterface, SupportHandle)) {
    return EFI_UNSUPPORTED;
  }

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

  PlatformDriverOverride = (EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.3.2.1
  // Call DriverLoaded() to associate a driver image handle with a device path.
  //

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);

  ControllerHandle = NULL;
  DriverImagePath = NULL;
  DriverImageHandle = NULL;
  FilePath = NULL;
  TempFileName = L"PlatformDriverOverrideBBTest.efi";

  //
  // Get the Controller handle and the driver image path.
  //
  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImagePath = NULL;
    Status = PlatformDriverOverride->GetDriverPath(PlatformDriverOverride, Handles[HandleIndex], &DriverImagePath);
    if(Status == EFI_SUCCESS) {
      ControllerHandle = Handles[HandleIndex];
      break;
    }
  }

  //
  // Get the driver image handle.
  //
  FilePath = FileDevicePath (NULL, TempFileName);
  Status = gtBS->LoadImage(
                   FALSE,
                   DriverImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &DriverImageHandle
                   );

  Status = PlatformDriverOverride->DriverLoaded(PlatformDriverOverride, ControllerHandle, DriverImagePath, DriverImageHandle);

  if(Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestFunctionAssertionGuid003,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  NewDriverImageHandle = NULL;
  Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, ControllerHandle, NewDriverImageHandle);
  if(EFI_ERROR(Status)) {
    return Status;
  }

  if(NewDriverImageHandle == DriverImageHandle) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestFunctionAssertionGuid004,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke GetDriver() and verify whether the image handle is installed.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (Handles) {
    FreePool (Handles);
  }

  return EFI_SUCCESS;
}
