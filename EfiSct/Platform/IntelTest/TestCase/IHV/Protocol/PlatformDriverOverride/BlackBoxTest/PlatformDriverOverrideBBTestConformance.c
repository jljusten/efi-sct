/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  PlatformDriverOverrideBBTestConformance.c

Abstract:

  Conformance Test Cases of Platform Driver Override Protocol

--*/


#include "PlatformDriverOverrideBBTestMain.h"

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriver Conformance Test.
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
BBTestGetDriverConformanceAutoTest (
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
  // Assertion Point 4.1.2.1
  // Check Point 1
  // Invoke GetDriver() with invalide controller handle
  //
  DriverImageHandle = NULL;
  Handles = NULL;
  Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles, DriverImageHandle);
  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformDriverOverrideBBTestConformanceAssertionGuid001,
             L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver - Invoke GetDriver() with invalid controller handle",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );

  //
  // Check Point 2
  // Invoke GetDriver() with invalide DriverImageHandle
  //

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);


  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImageHandle = NULL;
    Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles[HandleIndex], DriverImageHandle);
    if(Status == EFI_SUCCESS){
      Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles[HandleIndex], NULL);
      if(Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid002,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver - Invoke GetDriver() with invalid DriverImageHandle.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
    }
  }

  if (Handles) {
    FreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.GetDriverPath Conformance Test.
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
BBTestGetDriverPathConformanceAutoTest (
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
  // Assertion Point 4.2.2.1
  // Check Point 1
  // Invoke GetDriverPath() with invalide controller handle
  //
  DriverImagePath = NULL;
  Handles = NULL;
  Status = PlatformDriverOverride->GetDriverPath(PlatformDriverOverride, Handles, &DriverImagePath);
  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid003,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath - Invoke GetDriverPath() with invalid controller handle",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check Point 2
  // Invoke GetDriverPath() with invalide DriverImagePath
  //

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);


  for(HandleIndex = 0; HandleIndex < HandlesNo; HandleIndex++)
  {
    DriverImagePath = NULL;
    Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles[HandleIndex], &DriverImagePath);
    if(Status == EFI_SUCCESS){
      Status = PlatformDriverOverride->GetDriver(PlatformDriverOverride, Handles[HandleIndex], NULL);
      if(Status == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPlatformDriverOverrideBBTestConformanceAssertionGuid004,
                     L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath - Invoke GetDriverPath() with invalid DriverImageHandle.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );
    }
  }

  if (Handles) {
    FreePool (Handles);
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID.DriverLoaded Conformance Test.
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
BBTestDriverLoadedConformanceAutoTest (
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
  EFI_DEVICE_PATH_PROTOCOL               *NewDriverImagePath;
  EFI_HANDLE                             DriverImageHandle;
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

  // Get all the handles in the system.
  LibLocateHandle (AllHandles, NULL, NULL, &HandlesNo, &Handles);

  ControllerHandle = NULL;
  DriverImagePath = NULL;
  NewDriverImagePath = NULL;
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
      NewDriverImagePath = DriverImagePath;
      Status = PlatformDriverOverride->GetDriverPath(PlatformDriverOverride, Handles[HandleIndex], &NewDriverImagePath);
      if(Status == EFI_SUCCESS) {
        break;
      }
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

  //
  // Assertion Point 4.3.2.1
  // Call DriverLoaded() with DriverImagePath not got from the prior call to GetDriverPath().
  //
  Status = PlatformDriverOverride->DriverLoaded(PlatformDriverOverride, ControllerHandle, DriverImagePath, DriverImageHandle);

  if(Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid005,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with DriverImagePath not got from the prior call to GetDriverPath().",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );



  //
  // Assertion Point 4.3.2.2
  // Check point 1. Invalid ControllerHandle.
  //
  Status = PlatformDriverOverride->DriverLoaded(PlatformDriverOverride, NULL, DriverImagePath, DriverImageHandle);

  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid006,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid ControllerHandle.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check point 2. Invalid DriverImagePath.
  //
  Status = PlatformDriverOverride->DriverLoaded(PlatformDriverOverride, ControllerHandle, NULL, DriverImageHandle);

  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid007,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid DriverImagePath.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Check point 3. Invalid DriverImageHandle.
  //
  Status = PlatformDriverOverride->DriverLoaded(PlatformDriverOverride, ControllerHandle, DriverImagePath, NULL);

  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPlatformDriverOverrideBBTestConformanceAssertionGuid008,
                 L"EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded - Invoke DriverLoaded() with invalid DriverImageHandle.",
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
