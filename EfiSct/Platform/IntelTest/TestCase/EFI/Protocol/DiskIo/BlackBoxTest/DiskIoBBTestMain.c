/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DiskIoBBTestMain.c

Abstract:

  Test Driver of Disk I/O Protocol

--*/

#include "DiskIoBBTestMain.h"
#include "EfiTestLib.h"

EFI_EVENT              TimerEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DISK_IO_PROTOCOL_TEST_REVISION,
  EFI_DISK_IO_PROTOCOL_GUID,
  L"Disk I/O Protocol Test",
  L"EFI2.0 Disk I/O Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DISK_IO_PROTOCOL_READDISK_CONFORMANCE_AUTO_GUID,
    L"ReadDisk_Conf",
    L"Perform auto consistency checkes on the ReadDisk interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskConformanceAutoTest
  },
  //
  // Function test section
  //
  {
    DISK_IO_PROTOCOL_READDISK_FUNCTION_AUTO_GUID,
    L"ReadDisk_Func",
    L"Invoke ReadDisk and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskFunctionAutoTest
  },

  //
  // Combination test section
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    DISK_IO_PROTOCOL_WRITEDISK_CONFORMANCE_AUTO_GUID,
    L"WriteDisk_Conf",
    L"Perform auto consistency checkes on the WriteDisk interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskConformanceAutoTest
  },
  {
    DISK_IO_PROTOCOL_WRITEDISK_FUNCTION_AUTO_GUID,
    L"WriteDisk_Func",
    L"Invoke WriteDisk and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskFunctionAutoTest
  },
  {
    DISK_IO_PROTOCOL_READDISK_STRESS_AUTO_GUID,
    L"ReadDisk_Stress",
    L"Perform stress test on ReadDisk",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadDiskStressAutoTest
  },
  {
    DISK_IO_PROTOCOL_WRITEDISK_STRESS_AUTO_GUID,
    L"WriteDisk_Stress",
    L"Perform stress test on WriteDisk",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_DESTRUCTIVE,
    BBTestWriteDiskStressAutoTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT(InitializeBBTestDiskIo)

/**
 *  Disk I/O Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDiskIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);


  Status = gtBS->CreateEvent(EFI_EVENT_TIMER, 0, NULL, NULL, &TimerEvent);
  ASSERT_EFI_ERROR(Status);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDiskIoProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;
  Status = gtBS->CloseEvent(TimerEvent);
  ASSERT_EFI_ERROR(Status);

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

/**
 *  assistant function to verify two buffer
 *  @param  Buffer1 first buffer
 *  @param  Buffer2 second buffer
 *  @param  BufferSize size of the buffer
 *  @return Count of the different byte of two buffers
*/
UINTN
VerifyBuffer(
  IN UINT8           *Buffer1,
  IN UINT8           *Buffer2,
  IN UINTN           BufferSize
  )
{
  UINTN              Loop,Count;
  Count = 0;
  for (Loop = 0; Loop < BufferSize; Loop++) {
    if (Buffer1[Loop] != Buffer2[Loop]) {
      Count++;
    }
  }

  return Count;
}

/**
 *  assistant function to locate DevicePath Protocol from DiskIo Protocol
 *  @param  DiskIo protocol interface
 *  @param  BlockIo protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateBlockIoFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles,Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_DISK_IO_PROTOCOL                    *OtherDiskIo;

  //
  // Locate the Handle that the DiskIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gEfiDiskIoProtocolGuid,
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
  // Find the exact handle that DiskIo bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gEfiDiskIoProtocolGuid,
                       &OtherDiskIo
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
    if (OtherDiskIo == DiskIo) {
      break;
    }
  }

  //
  // Locate the BlockIo Protocol bound to DiskIo Protocol
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
                   &gEfiBlockIoProtocolGuid,
                   BlockIo
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


/**
 *  assistant function to locate DevicePath Protocol from DiskIo Protocol
 *  @param  DiskIo protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles,Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_DISK_IO_PROTOCOL                    *OtherDiskIo;

  //
  // Locate the Handle that the DiskIo interface is bound to
  //
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol,
                   &gEfiDiskIoProtocolGuid,
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
  // Find the exact handle that DiskIo bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol(
                       HandleBuffer[Index],
                       &gEfiDiskIoProtocolGuid,
                       &OtherDiskIo
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
    if (OtherDiskIo == DiskIo) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to DiskIo Protocol
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
