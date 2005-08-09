/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BusDriver4.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "misc.h"
#include "..\inc\TestDriver.h"

//
// TestBusDriver3:
// Consume TestNoInterfaceProtocol2;
// Will create 3 child handles:
// ChildHandle1 - InterfaceTestProtocol1
// ChildHandle2 - InterfaceTestProtocol2
// ChildHandle3 - InterfaceTestProtocol3
//

//
// data definition here
//
typedef struct {
  EFI_DRIVER_BINDING_PROTOCOL           DriverBinding;
  EFI_HANDLE                            HandleArray[3];
  EFI_HANDLE                            ControllerHandle;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1    InterfaceFunctionTestProtocol1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2    InterfaceFunctionTestProtocol2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    InterfaceFunctionTestProtocol3;
} BUS_DRIVER_4_PRIVATE_DATA;

#define BUS_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 _CR(a, BUS_DRIVER_4_PRIVATE_DATA, DriverBinding)

BUS_DRIVER_4_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
InitializeBusDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BusDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
BusDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
BusDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

EFI_STATUS
BusDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//
EFI_DRIVER_ENTRY_POINT(InitializeBusDriver4)

EFI_STATUS
InitializeBusDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // allocate memory for PrivateData
  //
  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (BUS_DRIVER_4_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (BUS_DRIVER_4_PRIVATE_DATA),0);

  InitializeDriverBinding (&mPrivateData->DriverBinding);

  Status = gtBS->InstallProtocolInterface (
            &ImageHandle,
            &gEfiDriverBindingProtocolGuid,
            EFI_NATIVE_INTERFACE,
            &mPrivateData->DriverBinding
            );
  mPrivateData->DriverBinding.ImageHandle = ImageHandle;
  mPrivateData->DriverBinding.DriverBindingHandle = ImageHandle;
  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID*)&LoadedImageInfoPtr
        );

  LoadedImageInfoPtr->Unload = BusDriver4Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
BusDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                      Controller,
                      &mTestNoInterfaceProtocol2Guid,
                      NULL,
                      This->DriverBindingHandle,
                      Controller,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BusDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  BUS_DRIVER_4_PRIVATE_DATA             *PrivateData;
  UINTN                                 Index;
  VOID                                  *ProtArray[3];
  EFI_GUID                              GuidArray[3];
  VOID                                  *ProtInstance;

  PrivateData = BUS_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol2Guid,
                     &ProtInstance,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol1 (&PrivateData->InterfaceFunctionTestProtocol1);
  InitializeInterfaceFunctionTestProtocol2 (&PrivateData->InterfaceFunctionTestProtocol2);
  InitializeInterfaceFunctionTestProtocol3 (&PrivateData->InterfaceFunctionTestProtocol3);

  GuidArray[0] = mInterfaceFunctionTestProtocol1Guid;
  GuidArray[1] = mInterfaceFunctionTestProtocol2Guid;
  GuidArray[2] = mInterfaceFunctionTestProtocol3Guid;

  ProtArray[0] = &PrivateData->InterfaceFunctionTestProtocol1;
  ProtArray[1] = &PrivateData->InterfaceFunctionTestProtocol2;
  ProtArray[2] = &PrivateData->InterfaceFunctionTestProtocol3;


  PrivateData->ControllerHandle = Controller;
  for (Index = 0; Index < 3; Index ++) {

    PrivateData->HandleArray[Index] = NULL;

    Status = gtBS->InstallMultipleProtocolInterfaces (
                  &PrivateData->HandleArray[Index],
                  &GuidArray[Index],
                  ProtArray[Index],
                  NULL
                  );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol2Guid,
                     &ProtInstance,
                     This->DriverBindingHandle,
                     PrivateData->HandleArray[Index],
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
    if (EFI_ERROR(Status)) {
      gtBS->UninstallMultipleProtocolInterfaces (
                    PrivateData->HandleArray[Index],
                    &GuidArray[Index],
                    ProtArray[Index],
                    NULL
                    );
      return Status;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BusDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  BUS_DRIVER_4_PRIVATE_DATA          *PrivateData;
  EFI_STATUS                         Status;
  BOOLEAN                            AllChildrenStopped;
  VOID                               *ProtArray[3];
  EFI_GUID                           GuidArray[3];
  UINTN                              Index;
  UINTN                              MatchIndex;

  PrivateData = BUS_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  GuidArray[0] = mInterfaceFunctionTestProtocol1Guid;
  GuidArray[1] = mInterfaceFunctionTestProtocol2Guid;
  GuidArray[2] = mInterfaceFunctionTestProtocol3Guid;

  ProtArray[0] = &PrivateData->InterfaceFunctionTestProtocol1;
  ProtArray[1] = &PrivateData->InterfaceFunctionTestProtocol2;
  ProtArray[2] = &PrivateData->InterfaceFunctionTestProtocol3;

  if (NumberOfChildren == 0) {

    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
    return EFI_SUCCESS;
  }

  AllChildrenStopped = TRUE;

  for (Index = 0; Index < NumberOfChildren; Index++) {

    for (MatchIndex = 0; MatchIndex < 3; MatchIndex ++) {

      if (ChildHandleBuffer[Index] == PrivateData->HandleArray[MatchIndex]) {
        break;
      }
    }

    if (MatchIndex == 3) {
      continue;
    }

    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            PrivateData->HandleArray[MatchIndex]
            );

    Status = gtBS->UninstallMultipleProtocolInterfaces (
                  PrivateData->HandleArray[MatchIndex],
                  &GuidArray[MatchIndex],
                  ProtArray[MatchIndex],
                  NULL
                  );

    if (EFI_ERROR (Status)) {
      AllChildrenStopped = FALSE;
    } else {
      PrivateData->HandleArray[MatchIndex] = NULL;
    }
  }

  if (!AllChildrenStopped) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = BusDriver4BindingSupported;
  DriverBinding->Start                = BusDriver4BindingStart;
  DriverBinding->Stop                 = BusDriver4BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BusDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  UINTN               Index;
  VOID                *ProtArray[3];
  EFI_GUID            GuidArray[3];

  GuidArray[0] = mInterfaceFunctionTestProtocol1Guid;
  GuidArray[1] = mInterfaceFunctionTestProtocol2Guid;
  GuidArray[2] = mInterfaceFunctionTestProtocol3Guid;

  ProtArray[0] = &mPrivateData->InterfaceFunctionTestProtocol1;
  ProtArray[1] = &mPrivateData->InterfaceFunctionTestProtocol2;
  ProtArray[2] = &mPrivateData->InterfaceFunctionTestProtocol3;
  //
  // free resources
  //
  for (Index = 0; Index < 3; Index ++) {

    if (mPrivateData->HandleArray[Index] != NULL) {
      gtBS->CloseProtocol (
              mPrivateData->ControllerHandle,
              &mTestNoInterfaceProtocol2Guid,
              mPrivateData->DriverBinding.DriverBindingHandle,
              mPrivateData->HandleArray[Index]
              );

      gtBS->UninstallMultipleProtocolInterfaces (
                    mPrivateData->HandleArray[Index],
                    &GuidArray[Index],
                    ProtArray[Index],
                    NULL
                    );
    }
  }

  gtBS->CloseProtocol (
            mPrivateData->ControllerHandle,
            &mTestNoInterfaceProtocol2Guid,
            mPrivateData->DriverBinding.DriverBindingHandle,
            mPrivateData->ControllerHandle
            );

  gtBS->UninstallProtocolInterface (
              mPrivateData->DriverBinding.DriverBindingHandle,
              &gEfiDriverBindingProtocolGuid,
              &mPrivateData->DriverBinding
              );

  gtBS->FreePool (mPrivateData);

  return EFI_SUCCESS;
}