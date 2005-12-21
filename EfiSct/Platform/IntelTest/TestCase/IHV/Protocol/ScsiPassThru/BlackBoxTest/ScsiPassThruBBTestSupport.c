/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ScsiPassThruBBTestSupport.c

Abstract:

  SCSI Pass Thru Protocol test support functions.

--*/

#include "ScsiPassThruBBTestMain.h"

#define EFI_SCT_FILE_DEVICE_CONFIG          L"Data\\DeviceConfig.ini"
#define EFI_SCT_SECTION_DEVICE_CONFIG       L"Device Configuration"

#define EFI_SCT_MAX_BUFFER_SIZE             512

//
// Internal function declarations
//

EFI_STATUS
GatherConfigHandles (
  IN EFI_HANDLE         SupportHandle,
  OUT UINTN             *NoConfigHandles,
  OUT EFI_HANDLE        **ConfigHandleBuffer
  );

VOID
InsertChildHandles (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle,
  IN BOOLEAN            Recursive
  );

BOOLEAN
InsertHandle (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle
  );

BOOLEAN
MatchHandleInterface (
  IN UINTN              NoHandles,
  IN EFI_HANDLE         *HandleBuffer,
  IN EFI_GUID           *ClientGuid,
  IN VOID               *ClientInterface
  );

EFI_STATUS
DeviceConfigGetOrderNum (
  IN EFI_INI_FILE_HANDLE    IniFile,
  OUT UINT32                *OrderNum
  );

EFI_STATUS
DeviceConfigGetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  OUT CHAR16                *Buffer
  );

EFI_STATUS
DeviceConfigSetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  IN CHAR16                 *Buffer
  );

//
// External function implementations
//

/**
 *  Verify whether it is one of IHV interfaces.
 */
BOOLEAN
IsIhvInterface (
  IN VOID                       *ClientInterface,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS            Status;
  BOOLEAN               Result;
  UINTN                 NoConfigHandles;
  EFI_HANDLE            *ConfigHandleBuffer;

  //
  // Gather all related handles from device configuration file
  //
  Status = GatherConfigHandles (
             SupportHandle,
             &NoConfigHandles,
             &ConfigHandleBuffer
             );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // Find the matched handle with interface
  //
  Result = MatchHandleInterface (
             NoConfigHandles,
             ConfigHandleBuffer,
             &gEfiScsiPassThruProtocolGuid,
             ClientInterface
             );

  //
  // Free sources
  //
  gtBS->FreePool (ConfigHandleBuffer);

  //
  // Done
  //
  return Result;
}

//
// Internal function implementation
//

EFI_STATUS
GatherConfigHandles (
  IN EFI_HANDLE         SupportHandle,
  OUT UINTN             *NoConfigHandles,
  OUT EFI_HANDLE        **ConfigHandleBuffer
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FilePath;
  CHAR16                              *ConfigFilePath;
  EFI_INI_FILE_HANDLE                 IniFile;
  UINT32                              Order;
  UINT32                              OrderNum;
  CHAR16                              Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  UINTN                               Index;
  UINTN                               NoHandles;
  EFI_HANDLE                          *HandleBuffer;
  CHAR16                              *DevicePathStr;

  //
  // Locate test profile library protocol
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   &ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ConfigFilePath = PoolPrint (L"%s\\%s", FilePath, EFI_SCT_FILE_DEVICE_CONFIG);
  if (ConfigFilePath == NULL) {
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (FilePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gtBS->FreePool (FilePath);

  //
  // Open the device configuration file
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         DevicePath,
                         ConfigFilePath,
                         &IniFile
                         );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool (DevicePath);
    gtBS->FreePool (ConfigFilePath);
    return Status;
  }

  gtBS->FreePool (DevicePath);
  gtBS->FreePool (ConfigFilePath);

  //
  // Get the number of device configuration data
  //
  Status = DeviceConfigGetOrderNum (
             IniFile,
             &OrderNum
             );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Get all handles
  //
  Status = gtBS->LocateHandleBuffer (
                   AllHandles,
                   NULL,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    return Status;
  }

  //
  // Initialize the output variables
  //
  *NoConfigHandles = 0;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof(EFI_HANDLE) * NoHandles,
                   (VOID **)ConfigHandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    ProfileLib->EfiIniClose (ProfileLib, IniFile);
    gtBS->FreePool (HandleBuffer);
    return Status;
  }

  //
  // Scan each device configuration data
  //
  for (Order = 0; Order < OrderNum; Order++) {
    //
    // Here, only need to find the matched device path in the system
    //
    Status = DeviceConfigGetString (
               IniFile,
               Order,
               L"DevicePath",
               Buffer
               );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Search the matched device path in the system
    //
    for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gEfiDevicePathProtocolGuid,
                       &DevicePath
                       );
      if (EFI_ERROR (Status)) {
        continue;
      }

      DevicePathStr = DevicePathToStr (DevicePath);

      if (StrCmp (Buffer, DevicePathStr) == 0) {
        gtBS->FreePool (DevicePathStr);
        break;
      }

      gtBS->FreePool (DevicePathStr);
    }

    //
    // Found it?
    //
    if (Index < NoHandles) {
      InsertChildHandles (
        NoConfigHandles,
        *ConfigHandleBuffer,
        HandleBuffer[Index],
        TRUE
        );
    }
  }

  //
  // Free resources
  //
  gtBS->FreePool (HandleBuffer);

  //
  // Close the device configuration file
  //
  ProfileLib->EfiIniClose (ProfileLib, IniFile);

  //
  // Done
  //
  return EFI_SUCCESS;
}

VOID
InsertChildHandles (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle,
  IN BOOLEAN            Recursive
  )
{
  EFI_STATUS                            Status;
  BOOLEAN                               Result;
  UINTN                                 Index1;
  UINTN                                 Index2;
  UINTN                                 ProtocolBufferCount;
  EFI_GUID                              **ProtocolBuffer;
  UINTN                                 EntryCount;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   *EntryBuffer;

  //
  // Insert the handle itself
  //
  Result = InsertHandle (
             NoHandles,
             HandleBuffer,
             Handle
             );
  if (!Result) {
    //
    // Return if this handle already exists (stands for it has been processed.)
    //
    return;
  }

  //
  // Locate all protocols on the handle
  //
  Status = gtBS->ProtocolsPerHandle (
                   Handle,
                   &ProtocolBuffer,
                   &ProtocolBufferCount
                   );
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Get the open protocol information for each protocol
  //
  for (Index1 = 0; Index1 < ProtocolBufferCount; Index1++) {
    //
    // Get the open protocol information
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     ProtocolBuffer[Index1],
                     &EntryBuffer,
                     &EntryCount
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    for (Index2 = 0; Index2 < EntryCount; Index2++) {
      //
      // Deal with the protocol opened by driver or by child controller
      //
      if ((EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER          ) ||
          (EntryBuffer[Index2].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) {
        //
        // Insert the agent handle
        //
        InsertHandle (
          NoHandles,
          HandleBuffer,
          EntryBuffer[Index2].AgentHandle
          );

        //
        // Insert the controller handle
        //
        if (Recursive) {
          InsertChildHandles (
            NoHandles,
            HandleBuffer,
            EntryBuffer[Index2].ControllerHandle,
            Recursive
            );
        }
      }
    }

    gtBS->FreePool (EntryBuffer);
  }

  //
  // Free resources
  //
  gtBS->FreePool (ProtocolBuffer);
}

BOOLEAN
InsertHandle (
  IN OUT UINTN          *NoHandles,
  IN OUT EFI_HANDLE     *HandleBuffer,
  IN EFI_HANDLE         Handle
  )
{
  UINTN   Index;

  for (Index = 0; Index < *NoHandles; Index++) {
    if (HandleBuffer[Index] == Handle) {
      return FALSE;
    }
  }

  HandleBuffer[*NoHandles] = Handle;
  (*NoHandles) ++;

  return TRUE;
}

BOOLEAN
MatchHandleInterface (
  IN UINTN              NoHandles,
  IN EFI_HANDLE         *HandleBuffer,
  IN EFI_GUID           *ClientGuid,
  IN VOID               *ClientInterface
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  VOID        *Interface;

  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     ClientGuid,
                     &Interface
                     );
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (Interface == ClientInterface) {
      return TRUE;
    }
  }

  return FALSE;
}

EFI_STATUS
DeviceConfigGetOrderNum (
  IN EFI_INI_FILE_HANDLE    IniFile,
  OUT UINT32                *OrderNum
  )
{
  return IniFile->GetOrderNum (
                    IniFile,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    OrderNum
                    );
}

EFI_STATUS
DeviceConfigGetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  OUT CHAR16                *Buffer
  )
{
  UINT32  BufferSize;

  BufferSize = EFI_SCT_MAX_BUFFER_SIZE;
  return IniFile->GetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer,
                    &BufferSize
                    );
}

EFI_STATUS
DeviceConfigSetString (
  IN EFI_INI_FILE_HANDLE    IniFile,
  IN UINT32                 Order,
  IN CHAR16                 *Key,
  IN CHAR16                 *Buffer
  )
{
  return IniFile->SetStringByOrder (
                    IniFile,
                    Order,
                    EFI_SCT_SECTION_DEVICE_CONFIG,
                    Key,
                    Buffer
                    );
}
