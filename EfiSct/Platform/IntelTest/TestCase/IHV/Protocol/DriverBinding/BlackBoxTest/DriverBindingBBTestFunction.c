/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DriverBindingBBTestFunction.c

Abstract:

  for EFI Driver Binding Protocol's Function Test

--*/

#include "DriverBindingBBTest.h"

//
// Definitions
//

#define DRIVER_BINDING_EMPTY                                    0xFF

#define DRIVER_BINDING_SUPPORTED_INVOKE                         0x00
#define DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS                 0x01
#define DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED         0x02
#define DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED           0x03
#define DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED             0x04

#define DRIVER_BINDING_START_INVOKE                             0x10
#define DRIVER_BINDING_START_RETURN_SUCCESS                     0x11
#define DRIVER_BINDING_START_RETURN_DEVICE_ERROR                0x12
#define DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES            0x13

#define DRIVER_BINDING_STOP_INVOKE                              0x20
#define DRIVER_BINDING_STOP_RETURN_SUCCESS                      0x21

typedef struct _DRIVER_BINDING_CHECK {
  UINT32                ID;
  EFI_GUID              Guid;
  EFI_TEST_ASSERTION    AssertionType;
  CHAR16                *Title;
} DRIVER_BINDING_CHECK;

DRIVER_BINDING_CHECK  mDriverBindingCheck[] = {
  {
    DRIVER_BINDING_SUPPORTED_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_001_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service gets called."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_002_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_003_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Supported() service returns EFI_ALREADY_STARTED with managed handle."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_004_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Supported() service returns EFI_ACCESS_DENIED with managed handle by other."
  },
  {
    DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_005_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Supported() service returns EFI_UNSUPPORTED with unsupported handle."
  },
  {
    DRIVER_BINDING_START_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_006_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Start() service gets called."
  },
  {
    DRIVER_BINDING_START_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_007_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Start() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_START_RETURN_DEVICE_ERROR,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_008_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Start() service returns EFI_DEVICE_ERROR due to a device error."
  },
  {
    DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_009_GUID,
    EFI_TEST_ASSERTION_WARNING,
    L"Start() service returns EFI_OUT_OF_RESOURCES due to resources limitation."
  },
  {
    DRIVER_BINDING_STOP_INVOKE,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_010_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Stop() service gets called."
  },
  {
    DRIVER_BINDING_STOP_RETURN_SUCCESS,
    EFI_TEST_DRIVERBINDINGBBTESTFUNCTION_ASSERTION_011_GUID,
    EFI_TEST_ASSERTION_FAILED,
    L"Stop() service returns EFI_SUCCESS with supported handle."
  },
  {
    DRIVER_BINDING_EMPTY
  }
};

EFI_DRIVER_BINDING_SUPPORTED  mOldDriverBindingSupported;
EFI_DRIVER_BINDING_START      mOldDriverBindingStart;
EFI_DRIVER_BINDING_STOP       mOldDriverBindingStop;

//
// Internal function declarations
//

EFI_STATUS
EFIAPI
ProxySupported (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
ProxyStart (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
ProxyStop (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN UINTN                                  NumberOfChildren,
  IN EFI_HANDLE                             * ChildHandleBuffer
  );

VOID
SetCheckResult (
  IN UINT32                                 ID,
  IN EFI_TEST_ASSERTION                     AssertionType
  );

//
// External function implementations
//

EFI_STATUS
BBTestDriverBindingFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DRIVER_BINDING_PROTOCOL          *DriverBinding;
  UINTN                                Index;
  UINTN                                NoHandles;
  EFI_HANDLE                           *HandleBuffer;
  DRIVER_BINDING_CHECK                 *Check;

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

  DriverBinding = (EFI_DRIVER_BINDING_PROTOCOL *)ClientInterface;

  //
  // Redirect the Driver Binding services to the proxy services
  //
  mOldDriverBindingSupported  = DriverBinding->Supported;
  mOldDriverBindingStart      = DriverBinding->Start;
  mOldDriverBindingStop       = DriverBinding->Stop;

  DriverBinding->Supported  = ProxySupported;
  DriverBinding->Start      = ProxyStart;
  DriverBinding->Stop       = ProxyStop;

  //
  // Disconnect all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                 );

    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->DisconnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Connect all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                 );

    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->ConnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL,
                    TRUE
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Connect all handles again
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - Locate all handles",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                 );

    DriverBinding->Supported  = mOldDriverBindingSupported;
    DriverBinding->Start      = mOldDriverBindingStart;
    DriverBinding->Stop       = mOldDriverBindingStop;

    return Status;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->ConnectController (
                    HandleBuffer[Index],
                    NULL,
                    NULL,
                    TRUE
                    );
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Restore back the redirected Driver Binding services
  //
  DriverBinding->Supported  = mOldDriverBindingSupported;
  DriverBinding->Start      = mOldDriverBindingStart;
  DriverBinding->Stop       = mOldDriverBindingStop;

  //
  // Record the test results
  //
  for (Check = mDriverBindingCheck; Check->ID != DRIVER_BINDING_EMPTY; Check++) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   Check->AssertionType,
                   Check->Guid,
                   Check->Title,
                   L"%a:%d:CheckId - %d",
                   __FILE__,
                   __LINE__,
                   Check->ID
                 );
  }

  return EFI_SUCCESS;
}

//
// Internal function implementations
//

EFI_STATUS
EFIAPI
ProxySupported (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_SUPPORTED_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingSupported) (
             This,
             ControllerHandle,
             RemainingDevicePath
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_ALREADY_STARTED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_ALREADY_STARTED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_ACCESS_DENIED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_ACCESS_DENIED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_UNSUPPORTED:
    SetCheckResult (
      DRIVER_BINDING_SUPPORTED_RETURN_UNSUPPORTED,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

EFI_STATUS
EFIAPI
ProxyStart (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_START_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingStart) (
             This,
             ControllerHandle,
             RemainingDevicePath
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_DEVICE_ERROR:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_DEVICE_ERROR,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  case EFI_OUT_OF_RESOURCES:
    SetCheckResult (
      DRIVER_BINDING_START_RETURN_OUT_OF_RESOURCES,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

EFI_STATUS
EFIAPI
ProxyStop (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN UINTN                                  NumberOfChildren,
  IN EFI_HANDLE                             * ChildHandleBuffer
  )
{
  EFI_STATUS  Status;

  SetCheckResult (
    DRIVER_BINDING_STOP_INVOKE,
    EFI_TEST_ASSERTION_PASSED
    );

  Status = (* mOldDriverBindingStop) (
             This,
             ControllerHandle,
             NumberOfChildren,
             ChildHandleBuffer
             );

  switch (Status) {
  case EFI_SUCCESS:
    SetCheckResult (
      DRIVER_BINDING_STOP_RETURN_SUCCESS,
      EFI_TEST_ASSERTION_PASSED
      );
    break;

  default:
    break;
  }

  return Status;
}

VOID
SetCheckResult (
  IN UINT32                                 ID,
  IN EFI_TEST_ASSERTION                     AssertionType
  )
{
  DRIVER_BINDING_CHECK  *Check;

  for (Check = mDriverBindingCheck; Check->ID != DRIVER_BINDING_EMPTY; Check++) {
    if (Check->ID == ID) {
      Check->AssertionType = AssertionType;
      break;
    }
  }
}
