/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BusSpecificDriverOverrideBBTestMain.c

Abstract:

  Test Driver of Bus Specific Driver Override Protocol

--*/


#include "BusSpecificDriverOverrideBBTestMain.h"
#include "EfiTestLib.h"

EFI_EVENT              TimerEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION,
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID,
  L"Bus Specific Driver Override Protocol Test",
  L"EFI1.10 Bus Specific Driver Override Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_CONFORMANCE_GUID,
    L"GetDriver_Conf",
    L"Test whether GetDriver performs enough parameter checking",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverConformanceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_FUNCTION_MANUAL_GUID,
    L"GetDriver_Func_Manual",
    L"Perform manual function checkes on the GetDriver interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestGetDriverFunctionManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestBusSpecificDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBBTestBusSpecificDriverOverride)

/**
 *  Bus Specific Driver Override Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestBusSpecificDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);


  Status = gtBS->CreateEvent (EFI_EVENT_TIMER, 0, NULL, NULL, &TimerEvent);
  if (EFI_ERROR(Status)) {

  }

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestBusSpecificDriverOverrideProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestBusSpecificDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;
  Status = gtBS->CloseEvent (TimerEvent);
  if (EFI_ERROR(Status)) {

  }

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

/**
 *  assistant function to locate DevicePath Protocol from BusDriverOverride Protocol
 *  @param  BusDriverOverride protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromBusOverride (
  IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL    *BusOverride,
  IN EFI_DEVICE_PATH_PROTOCOL                     **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                       NoHandles, Index;
  EFI_HANDLE                                  *HandleBuffer;
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL   *OtherBusOverride;



  //
  // Locate the Handle that the DiskIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiBusSpecificDriverOverrideProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  if (NoHandles <= 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandle - LocateHandle",
                   L"%a:%d:Device Error",
                   __FILE__,
                   __LINE__
                   );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that BusOverride bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gEfiBusSpecificDriverOverrideProtocolGuid,
                       &OtherBusOverride
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - HandleProtocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );
      if (HandleBuffer != NULL) {
        gtBS->FreePool (HandleBuffer);
      }
      return Status;
    }
    if (OtherBusOverride == BusOverride) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to BusOverride Protocol
  //
  if (Index >= NoHandles) {
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    //
    // No Handle Found!!
    //
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   DevicePath
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - HandleProtocol",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
    return Status;
  }


  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }


  return EFI_SUCCESS;
}
