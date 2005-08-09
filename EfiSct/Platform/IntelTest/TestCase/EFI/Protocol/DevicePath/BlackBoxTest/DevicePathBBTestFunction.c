/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DevicePathBBTestFunction.c

Abstract:

  Interface Function Test Cases of Device Path Protocol

--*/


#include "DevicePathBBTestMain.h"

#define DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL    \
{0x37499A9D, 0x542F, 0x4C89, 0xA0, 0x26, 0x35, 0xDA, 0x14, 0x20, 0x94, 0xE4}

EFI_GUID gEfiDevicePathMessagingUartFlowControlGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;

/**
 *  Entrypoint for EFI_DEVICE_PATH_PROTOCOL_GUID Path Node Conformance Test.
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
BBTestDevicePathNodeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT16                               Type;
  UINT16                               SubType;
  UINT16                               Length;
  MEMMAP_DEVICE_PATH                   *MemMap;
  IPv4_DEVICE_PATH                     *IPv4;
  IPv6_DEVICE_PATH                     *IPv6;
  ATAPI_DEVICE_PATH                    *Atapi;
  UART_DEVICE_PATH                     *Uart;
  VENDOR_DEVICE_PATH                   *Vendor;
  HARDDRIVE_DEVICE_PATH                *Hd;
  CHAR16                               *DevStr;

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

  DevicePath = (EFI_DEVICE_PATH_PROTOCOL *)ClientInterface;

  DevStr = DevicePathToStr (DevicePath);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_QUIET,
                 L"\nVerifying device path: %s\n",
                 DevStr
                 );
  gtBS->FreePool (DevStr);

  while (!IsDevicePathEnd (DevicePath)) {
    Type    = (UINT16)DevicePathType (DevicePath);
    SubType = (UINT16)DevicePathSubType (DevicePath);
    Length  = (UINT16)DevicePathNodeLength (DevicePath);

    //
    // Assertion Point 3.1.2.2
    // Check End of Hardware Device Path: End This Device Path
    //
    if ((Type == 0x7F || Type == 0xFF) && (SubType == 0x01)) {
      if (Length == 4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid001,
                     L"EFI_DEVICE_PATH_PROTOCOL - End of Hardware Device Path - End This Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.3
    // Check Hardware Device Path: PCI Device Path
    //
    else if ((Type == 1) && (SubType == 1)) {
      if (Length == 6) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid002,
                     L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - PCI Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.4
    // Check Hardware Device Path: PCCARD Device Path
    //
    else if ((Type == 1) && (SubType == 2)) {
      if (Length == 5) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid003,
                     L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - PCCARD Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.5
    // Check Hardware Device Path: Memory Mapped Device Path
    //
    else if ((Type == 1) && (SubType == 3)) {
      MemMap = (MEMMAP_DEVICE_PATH *)DevicePath;
      if ((Length == 24) &&
          (MemMap->MemoryType < EfiMaxMemoryType || MemMap->MemoryType > 0x7FFFFFFF) &&
          (MemMap->EndingAddress >= MemMap->StartingAddress)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid004,
                     L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Memory Mapped Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.6
    // Check Hardware Device Path: Vendor Device Path
    //
    else if ((Type == 1) && (SubType == 4)) {
      if (Length >= 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid005,
                     L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Vendor Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.7
    // Check Hardware Device Path: Controller Device Path
    //
    else if ((Type == 1) && (SubType == 5)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid006,
                     L"EFI_DEVICE_PATH_PROTOCOL - Hardware Device Path - Controller Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.8
    // Check ACPI Device Path: ACPI Device Path
    //
    else if ((Type == 2) && (SubType == 1)) {
      if (Length == 12) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid007,
                     L"EFI_DEVICE_PATH_PROTOCOL - ACPI Device Path - ACPI Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.9
    // Check ACPI Device Path: Expanded ACPI Device Path
    //
    else if ((Type == 2) && (SubType == 2)) {
      if (Length >= 19) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid008,
                     L"EFI_DEVICE_PATH_PROTOCOL - ACPI Device Path - Expanded ACPI Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.10
    // Check Messaging Device Path: ATAPI Device Path
    //
    else if ((Type == 3) && (SubType == 1)) {
      Atapi = (ATAPI_DEVICE_PATH*)DevicePath;
      if ((Length == 8) &&
          (Atapi->PrimarySecondary == 0 || Atapi->PrimarySecondary == 1) &&
          (Atapi->SlaveMaster == 0 || Atapi->SlaveMaster == 1)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid009,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - ATAPI Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.11
    // Check Messaging Device Path: SCSI Device Path
    //
    else if ((Type == 3) && (SubType == 2)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid010,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - SCSI Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.12
    // Check Messaging Device Path: Fibre Channel Device Path
    //
    else if ((Type == 3) && (SubType == 3)) {
      if (Length == 24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid011,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Fibre Channel Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.13
    // Check Messaging Device Path: 1394 Device Path
    //
    else if ((Type == 3) && (SubType == 4)) {
      if (Length == 16) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid012,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - 1394 Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.14
    // Check Messaging Device Path: USB Device Path
    //
    else if ((Type == 3) && (SubType == 5)) {
      if (Length == 6) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid013,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.15
    // Check Messaging Device Path: USB Class Device Path
    //
    else if ((Type == 3) && (SubType == 15)) {
      if (Length == 11) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid014,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - USB Class Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.16
    // Check Messaging Device Path: I2O Device Path
    //
    else if ((Type == 3) && (SubType == 6)) {
      if (Length == 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid015,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - I2O Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.17
    // Check Messaging Device Path: MAC Address Device Path
    //
    else if ((Type == 3) && (SubType == 11)) {
      if (Length == 37) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid016,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - MAC Address Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.18
    // Check Messaging Device Path: IPv4 Device Path
    //
    else if ((Type == 3) && (SubType == 12)) {
      IPv4 = (IPv4_DEVICE_PATH*)DevicePath;
      if ((Length == 19) &&
          (IPv4->StaticIpAddress == 0 || IPv4->StaticIpAddress == 1)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid017,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - IPv4 Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.19
    // Check Messaging Device Path: IPv6 Device Path
    //
    else if ((Type == 3) && (SubType == 13)) {
      IPv6 = (IPv6_DEVICE_PATH*)DevicePath;
      if ((Length == 43) &&
          (IPv6->StaticIpAddress == 0 || IPv6->StaticIpAddress == 1)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid018,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - IPv6 Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.20
    // Check Messaging Device Path: InfiniBand Device Path
    //
    else if ((Type == 3) && (SubType == 9)) {
      if (Length == 48) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid019,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - InfiniBand Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.21
    // Check Messaging Device Path: UART Device Path
    //
    else if ((Type == 3) && (SubType == 14)) {
      Uart = (UART_DEVICE_PATH*)DevicePath;
      if ((Length == 19) &&
          (Uart->Parity >= 0x00 && Uart->Parity <= 0x05) &&
          (Uart->StopBits >= 0x00 && Uart->StopBits <= 0x03)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid020,
                     L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - UART Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    else if ((Type == 3) && (SubType == 10)) {
      Vendor = (VENDOR_DEVICE_PATH*)DevicePath;
      //
      // Assertion Point 3.1.2.22
      // Check Messaging Device Path: Vendor-Defined Device Path
      //
      if (CompareMem (&Vendor->Guid, &gEfiDevicePathMessagingUartFlowControlGuid, sizeof (EFI_GUID)) != 0) {
        if (Length >= 20) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gDevicePathBBTestFunctionAssertionGuid021,
                       L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - Vendor-Defined Device Path",
                       L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                       __FILE__,
                       __LINE__,
                       Type,
                       SubType,
                       Length
                       );
      }
      //
      // Assertion Point 3.1.2.23
      // Check Messaging Device Path: UART Flow Control Messaging Path
      //
      else {
        if (Length == 24) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gDevicePathBBTestFunctionAssertionGuid022,
                       L"EFI_DEVICE_PATH_PROTOCOL - Messaging Device Path - UART Flow Control Messaging Path",
                       L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                       __FILE__,
                       __LINE__,
                       Type,
                       SubType,
                       Length
                       );
      }
    }
    //
    // Assertion Point 3.1.2.24
    // Check Media Device Path: Hard Drive Media Device Path
    //
    else if ((Type == 4) && (SubType == 1)) {
      Hd = (HARDDRIVE_DEVICE_PATH*)DevicePath;
      if ((Length == 42) &&
          (Hd->MBRType == 0x01 || Hd->MBRType == 0x02) &&
          (Hd->SignatureType == 0x00 || Hd->SignatureType == 0x01 || Hd->SignatureType == 0x02)){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid023,
                     L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Hard Drive Media Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.25
    // Check Media Device Path: CD-ROM Media Device Path
    //
    else if ((Type == 4) && (SubType == 2)) {
      if (Length == 24) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid024,
                     L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - CD-ROM Media Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.26
    // Check Media Device Path: Vendor-Defined Media Device Path
    //
    else if ((Type == 4) && (SubType == 3)) {
      if (Length >= 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid025,
                     L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Vendor-Defined Media Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.27
    // Check Media Device Path: File Path Media Device Path
    //
    else if ((Type == 4) && (SubType == 4)) {
      if (Length >= 4) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid026,
                     L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - File Path Media Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.28
    // Check Media Device Path: Media Protocol Device Path
    //
    else if ((Type == 4) && (SubType == 5)) {
      if (Length == 20) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid027,
                     L"EFI_DEVICE_PATH_PROTOCOL - Media Device Path - Media Protocol Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.1.2.29
    // Check BIOS Boot Specification Device Path
    //
    else if ((Type == 5) && (SubType == 1)) {
      if (Length >= 8) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid028,
                     L"EFI_DEVICE_PATH_PROTOCOL - BIOS Boot Specification Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    } else {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"Unknown Node(Type - %d, Subtype - %d, Length - %d)\n",
                     Type,
                     SubType,
                     Length
                     );
    }


    DevicePath = NextDevicePathNode (DevicePath);
  }

  //
  // Assertion Point 3.1.2.1
  // Check End of Hardware Device Path: End Entire Device Path
  //
  Type    = (UINT16)DevicePathType (DevicePath);
  SubType = (UINT16)DevicePathSubType (DevicePath);
  Length  = (UINT16)DevicePathNodeLength (DevicePath);

  if ((Type == 0x7F || Type == 0xFF) && (SubType == 0xFF)) {
    if (Length == 4) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDevicePathBBTestFunctionAssertionGuid029,
                   L"EFI_DEVICE_PATH_PROTOCOL - End of Hardware Device Path - End Entire Device Path",
                   L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                   __FILE__,
                   __LINE__,
                   Type,
                   SubType,
                   Length
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_DEVICE_PATH_PROTOCOL whole device path conformance Test.
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
BBTestWholeDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT16                               Type;
  UINT16                               SubType;
  UINT16                               Length;
  UINT16                               Count;
  UINT16                               PCIRootFirst;
  UINT16                               SCSICount;
  UINT16                               ATAPICount;
  ACPI_HID_DEVICE_PATH                 *Acpi;
  CHAR16                               *DevStr;

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

  DevicePath = (EFI_DEVICE_PATH_PROTOCOL *)ClientInterface;

  DevStr = DevicePathToStr (DevicePath);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_QUIET,
                 L"\nVerifying device path: %s\n",
                 DevStr
                 );
  gtBS->FreePool (DevStr);

  Count = 0;
  PCIRootFirst = 0;
  SCSICount = 0;
  ATAPICount = 0;

  while (!IsDevicePathEnd (DevicePath)) {
    Type    = (UINT16)DevicePathType (DevicePath);
    SubType = (UINT16)DevicePathSubType (DevicePath);
    Length  = (UINT16)DevicePathNodeLength (DevicePath);

    Count++;
    //
    // Assertion Point 3.2.2.1
    // BIOS Root Specification Device Path
    //
    if ((Type == 5) && (SubType == 1)) {
      if (Count != 1) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        DevicePath = NextDevicePathNode (DevicePath);
        if(IsDevicePathEnd (DevicePath)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid030,
                     L"EFI_DEVICE_PATH_PROTOCOL - BIOS Root Specification Device Path",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
      break;
    }
    //
    // Assertion Point 3.2.2.2
    // PCI Root Bus Device Path Node
    //
    else if ((Type == 2) && (SubType == 1 || SubType == 2)) {
      Acpi = (ACPI_HID_DEVICE_PATH*)DevicePath;
      if (EISA_ID_TO_NUM(Acpi->HID) == 0x0A03) {
        if (Count == 1) {
          PCIRootFirst++;
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gDevicePathBBTestFunctionAssertionGuid031,
                       L"EFI_DEVICE_PATH_PROTOCOL - PCI Root Bus Device Path Node",
                       L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                       __FILE__,
                       __LINE__,
                       Type,
                       SubType,
                       Length
                       );
      }
    //
    // Assertion Point 3.2.2.5
    // EISA Device Path Node
    //
      else if ((EISA_ID_TO_NUM(Acpi->HID) == 0x0604) ||
              (EISA_ID_TO_NUM(Acpi->HID) == 0x0303) ||
              (EISA_ID_TO_NUM(Acpi->HID) == 0x0F03) ||
              (EISA_ID_TO_NUM(Acpi->HID) == 0x0501) ||
              (EISA_ID_TO_NUM(Acpi->HID) == 0x0401)) {
        if (Count == (PCIRootFirst + 1)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gDevicePathBBTestFunctionAssertionGuid032,
                       L"EFI_DEVICE_PATH_PROTOCOL - EISA Device Path Node",
                       L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                       __FILE__,
                       __LINE__,
                       Type,
                       SubType,
                       Length
                       );
      }
    }
    //
    // Assertion Point 3.2.2.3
    // PCI Device Path Node
    //
    else if ((Type == 1) && (SubType == 1)) {
      if (Count == (PCIRootFirst + 1)) {
        PCIRootFirst++;
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid033,
                     L"EFI_DEVICE_PATH_PROTOCOL - PCI Device Path Node",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.2.2.4
    // Memory Mapped Device Path Node
    //
    else if ((Type == 1) && (SubType == 3)) {
      if (Count == 1) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid034,
                     L"EFI_DEVICE_PATH_PROTOCOL - Memory Mapped Device Path Node",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }
    //
    // Assertion Point 3.2.2.6
    // ATAPI Device Path Node
    //
    else if ((Type == 3) && (SubType == 1)) {
      if (Count == (PCIRootFirst + 1)) {
        ATAPICount = (UINT16)(PCIRootFirst + 1);
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDevicePathBBTestFunctionAssertionGuid035,
                     L"EFI_DEVICE_PATH_PROTOCOL - ATAPI Device Path Node",
                     L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                     __FILE__,
                     __LINE__,
                     Type,
                     SubType,
                     Length
                     );
    }

    DevicePath = NextDevicePathNode (DevicePath);
  }
  //
  // Assertion Point 3.2.2.10
  // Device Path must be terminated
  //
  Type    = (UINT16)DevicePathType (DevicePath);
  SubType = (UINT16)DevicePathSubType (DevicePath);
  Length  = (UINT16)DevicePathNodeLength (DevicePath);

  if ((Type == 0x7F || Type == 0xFF) && (SubType == 0xFF)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDevicePathBBTestFunctionAssertionGuid039,
                 L"EFI_DEVICE_PATH_PROTOCOL - Device Path must be terminated",
                 L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                 __FILE__,
                 __LINE__,
                 Type,
                 SubType,
                 Length
                 );

  return EFI_SUCCESS;
}
