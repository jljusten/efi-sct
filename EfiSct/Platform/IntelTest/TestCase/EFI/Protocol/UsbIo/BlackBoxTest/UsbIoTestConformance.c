/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  UsbIoTestConformance.c

Abstract:
  Source file for Usb Io conformance testing.

--*/

#include "Efi.h"
#include "EfiDriverLib.h"
#include "UsbIoTest.h"

//
// Prototypes (internal)
//

EFI_STATUS
UsbControlTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbControlTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbControlTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbBulkTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbBulkTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbBulkTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbBulkTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetDeviceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetConfigDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetInterfaceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetEndpointDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetEndpointDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbPortResetConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetStringDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
UsbGetStringDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  );

EFI_STATUS
GetUsbEndpointNotOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  );

EFI_STATUS
GetUsbEndpointOfAttr (
  IN  EFI_USB_IO_PROTOCOL                 *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
  ) ;

EFI_STATUS
UsbInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  );

EFI_STATUS
UsbIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
  );

//
// Functions
//

/**
 *  TDS 5.1 - Entry point for UsbIo->UsbControlTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.1.2.1
  //

  //
  // the parameter Direction is not valid
  //
  Status = UsbControlTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Request is NULL
  //
  Status = UsbControlTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbControlTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.2 - Entry point for UsbIo->UsbBulkTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.2.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbBulkTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Data is NULL
  //
  Status = UsbBulkTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter DateLength is NULL
  //
  Status = UsbBulkTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbBulkTransferConformanceSubTest4 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.3 - Entry point for UsbIo->UsbAsyncInterruptTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.3.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbAsyncInterruptTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter PollingInterval is not valid
  //
  Status = UsbAsyncInterruptTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.4 - Entry point for UsbIo->UsbSyncInterruptTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.4.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbSyncInterruptTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Data is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter DataLength is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest3 (UsbIo, StandardLib, LoggingLib);

  //
  // the parameter Status is NULL
  //
  Status = UsbSyncInterruptTransferConformanceSubTest4 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12 - Entry point for UsbIo->UsbAsyncIsochronousTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.12.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbAsyncIsochronousTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.11 - Entry point for UsbIo->UsbIsochronousTransfer() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.11.2.1
  //

  //
  // the parameter DeviceEndpoint is not valid
  //
  Status = UsbIsochronousTransferConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.5 - Entry point for UsbIo->UsbGetDeviceDescriptor() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbGetDeviceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.5.2.1
  //

  //
  // Call UsbGetDeviceDescriptor() with invalid parameter
  //
  Status = UsbGetDeviceDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.6 - Entry point for UsbIo->UsbGetConfigDescriptor() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbGetConfigDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.6.2.1
  //

  //
  // Call UsbGetConfigDescriptor() with invalid parameter
  //
  Status = UsbGetConfigDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7 - Entry point for UsbIo->UsbGetInterfaceDescriptor() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbGetInterfaceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.7.2.1
  //

  //
  // Call UsbGetInterfaceDescriptor() with invalid parameter
  //
  Status = UsbGetInterfaceDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.8 - Entry point for UsbIo->UsbGetEndpointDescriptor() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbGetEndpointDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.8.2.1
  //

  //
  // Call UsbGetEndpointDescriptor() with invalid parameter
  //
  Status = UsbGetEndpointDescriptorConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);


  //
  //TDS 5.8.2.2
  //

  //
  // Call UsbGetEndpointDescriptor() with non-existed endpoint
  //
  Status = UsbGetEndpointDescriptorConformanceSubTest2 (UsbIo, StandardLib, LoggingLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.9 - Entry point for UsbIo->UsbPortReset() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbPortResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  //TDS 5.9.2.1
  //

  //
  // Call UsbPortReset() with invalid parameter
  //
  Status = UsbPortResetConformanceSubTest1 (UsbIo, StandardLib, LoggingLib);


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.10 - Entry point for UsbIo->UsbGetStringDescriptor() Conformance Auto Test.
 *  @param This             A pointer to the EFI_BB_TEST_PROTOCOL instance.
 *  @param ClientInterface  A pointer to the interface to be tested.
 *  @param TestLevel        Test "thoroughness" control.
 *  @param SupportHandle    A handle containing support protocols.
 *  @return EFI_SUCCESS     Successfully.
 *  @return Other value     Something failed.
 */
EFI_STATUS
UsbGetStringDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_USB_IO_PROTOCOL                 *UsbIo;

  //
  // Get the Standard Test Support Library Interface
  //
  StandardLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the Test Logging Support Library Interface
  //
  LoggingLib = NULL;
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   &LoggingLib
                   );

  // Test Logging Support Library is optional

  //
  // Get the Usb Io protocol interface
  //
  UsbIo = (EFI_USB_IO_PROTOCOL *)ClientInterface;

  //
  // TDS 5.10.2.1
  // Call UsbGetStringDescriptor() with unsupported languageID
  //

  //
  // Comment it out, because no such description in EFI1.1 spec.
  //
//  Status = UsbGetStringDescriptorConformanceSubTest1(UsbIo, StandardLib, LoggingLib);

  //
  // TDS 5.10.2.1
  // Call UsbGetStringDescriptor() with unsupported StringIndex
  //

  //
  // Comment it out, because no such description in EFI1.1 spec.
  //
//  Status = UsbGetStringDescriptorConformanceSubTest2(UsbIo, StandardLib, LoggingLib);


  //
  // Done
  //
  return EFI_SUCCESS;
}


// Sub functions

/**
 *  TDS 5.1.2.1 - UsbControlTransfer should return EFI_INVALID_PARAMETER when Direction is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbControlTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest1",
                  L"TDS 5.1.2.1 - Direction is not valid\n"
                  );
  }

  //
  // build a request
  //
  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    -1,  // invalid Direction
                    3000,
                    NULL,
                    0,
                    &UsbStatus
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid001,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Direction being not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    0x7FFFFFF,  // invalid Direction
                    3000,
                    NULL,
                    0,
                    &UsbStatus
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid001,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Direction being not valid",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest1",
                  L"TDS 5.1.2.1 - Direction is not valid\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.1.2.1 - UsbControlTransfer should return EFI_INVALID_PARAMETER when the parameter Request is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbControlTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest2",
                  L"TDS 5.1.2.1 - the parameter Request is NULL\n"
                  );
  }

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    NULL, // Request is NULL
                    EfiUsbNoData,
                    3000,
                    NULL,
                    0,
                    &UsbStatus
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid002,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Request is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest2",
                  L"TDS 5.1.2.1 - the parameter Request is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.1.2.1 - UsbControlTransfer should return EFI_INVALID_PARAMETER when the parameter Status is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbControlTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_DEVICE_REQUEST  Request;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest3",
                  L"TDS 5.1.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // build a request
  //
  Request.RequestType = 0x21;
  Request.Request = 0xFF;
  Request.Value = 0;
  Request.Index = 0;
  Request.Length = 0;

  Status = UsbIo->UsbControlTransfer (
                    UsbIo,
                    &Request,
                    EfiUsbNoData,
                    3000,
                    NULL,
                    0,
                    NULL // Status is NULL
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid003,
                 L"EFI_USB_IO_PROTOCOL.UsbControlTransfer - UsbControlTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbControlTransferConformanceSubTest3",
                  L"TDS 5.1.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.2.2.1 - UsbBulkTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbBulkTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest1",
                  L"TDS 5.2.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                   );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid004,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                   );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid005,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                   );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid006,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                   );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid007,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // 2. The endpoint is not a BULK endpoint(with attribute != 0x02)
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a NonBulk endpoint. Skipped this test for BulkTransfer.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
    DataLength = 128;
    Status = UsbIo->UsbBulkTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      (VOID *)Data,
                      &DataLength,
                      1000,
                      &UsbStatus
                      );
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid008,
                   L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a BULK endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest1",
                  L"TDS 5.2.2.1 - DeviceEndpoint is not valid\n"
                  );
  }


  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.2.2.1 - UsbBulkTransfer should return EFI_INVALID_PARAMETER when Data is NULL.
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbBulkTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest2",
                  L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status  = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest2",
                    L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                    );
      }
    return Status;
  }

  //
  // 3. the parameter Data is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    NULL,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid009,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest2",
                  L"TDS 5.2.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.2.2.1 - UsbBulkTransfer should return EFI_INVALID_PARAMETER when DataLength is NULL.
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbBulkTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest3",
                  L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status  = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest3",
                    L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                    );
      }
    return Status;
  }

  //
  // 4. The Parameter DataLength is NULL
  //
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    NULL,
                    1000,
                    &UsbStatus
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid010,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with DataLength is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest3",
                  L"TDS 5.2.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.2.2.1 - UsbBulkTransfer should return EFI_INVALID_PARAMETER when Status is NULL.
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbBulkTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest4",
                  L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Attributes = 0x02 means this is a bulk endpoint
  //
  Status  = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x02, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbBulkTransfer: Failed to find a Bulk endpoint. Skipped other parameter tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbBulkTransferConformanceSubTest4",
                    L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                    );
      }
    return Status;
  }

  //
  // 5. The Parameter Status is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbBulkTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    NULL
                    );

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid011,
                 L"EFI_USB_IO_PROTOCOL.UsbBulkTransfer - UsbBulkTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbBulkTransferConformanceSubTest4",
                  L"TDS 5.2.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.3.2.1 - UsbAsyncInterruptTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbAsyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.3.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid012,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid013,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid014,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    TRUE,
                    100,
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid015,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Interrupt endpoint
  //
  // Attributes != 0x03 means this is not an Interrupt endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncInterruptTransfer: Failed to find an non-interrupt endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
    Status = UsbIo->UsbAsyncInterruptTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      TRUE,
                      100,
                      DataLength,
                      UsbInterruptCallBack,
                      NULL
                      );

    //
    // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) ||
        (Status == EFI_UNSUPPORTED      )) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid016,
                   L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Interrupt endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.3.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

/**
 *  TDS 5.3.2.1 - UsbAsyncInterruptTransfer should return EFI_INVALID_PARAMETER when PollingInterval is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbAsyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbAsyncInterruptTransferConformanceSubTest2",
                    L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                    );
    }

    return Status;
  }

  //
  // 3. the parameter PollingInterval is invalid
  // PollingInterval is 0
  //
  DataLength = 128;
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    TRUE,
                    0, //invalid polling interval
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid017,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // PollingInterval is 256
  //
  Status = UsbIo->UsbAsyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    TRUE,
                    256,//invalid polling interval
                    DataLength,
                    UsbInterruptCallBack,
                    NULL
                    );

  //
  // UsbAsyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid018,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncInterruptTransfer - UsbAsyncInterruptTransfer() returns EFI_INVALID_PARAMETER with PollingInterval is 256",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.3.2.1 - the parameter PollingInterval is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbSyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid019,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid020,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid021,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid022,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Interrupt endpoint
  //
  // Attributes != 0x03 means this is not an Interrupt endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer:  Failed to find an non-interrupt endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
    Status = UsbIo->UsbSyncInterruptTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      (VOID *)Data,
                      &DataLength,
                      1000,
                      &UsbStatus
                      );

    //
    // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) ||
        (Status == EFI_UNSUPPORTED      )) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid023,
                   L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Interrupt endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest1",
                  L"TDS 5.4.2.1 - Call UsbSyncInterruptTransfer() with Invalid Parameters\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when Data is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest2",
                    L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 3. the parameter Data is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    NULL,
                    &DataLength,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid024,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Data is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest2",
                  L"TDS 5.4.2.1 - the parameter Data is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when DataLength is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest3 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  UINT32                  UsbStatus;
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest3",
                    L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 4. The Parameter DataLength is NULL
  //
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    NULL,
                    1000,
                    &UsbStatus
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid025,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with DataLength is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest3",
                  L"TDS 5.4.2.1 - the parameter DataLength is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.4.2.1 - UsbSyncInterruptTransfer should return EFI_INVALID_PARAMETER when Status is NULL.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbSyncInterruptTransferConformanceSubTest4 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINT32                  Data[255];
  UINTN                   DataLength;

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Attributes = 0x03 means this is an Interrupt endpoint
  //
  Status = GetUsbEndpointOfAttr (UsbIo, StandardLib, 0x03, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbSyncInterruptTransfer :Failed to find an interrupt endpoint. Skipped other tests",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbSyncInterruptTransferConformanceSubTest4",
                    L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                    );
    }

    return Status;
  }

  //
  // 5. The Parameter Status is NULL
  //
  DataLength = 128;
  Status = UsbIo->UsbSyncInterruptTransfer (
                    UsbIo,
                    EndpointDesc.EndpointAddress,
                    (VOID *)Data,
                    &DataLength,
                    1000,
                    NULL
                    );

  //
  // UsbSyncInterruptTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid026,
                 L"EFI_USB_IO_PROTOCOL.UsbSyncInterruptTransfer - UsbSyncInterruptTransfer() returns EFI_INVALID_PARAMETER with Status is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbSyncInterruptTransferConformanceSubTest4",
                  L"TDS 5.4.2.1 - the parameter Status is NULL\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.12.2.1 - UsbAsyncIsochronousTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbAsyncIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                   );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid036,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid037,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid038,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbAsyncIsochronousTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    UsbIsochronousCallBack,
                    NULL
                    );

  //
  // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid039,
                 L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Isochronous endpoint
  //
  // Attributes != 0x01 means this is not an Isochronous endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x01, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbAsyncIsochronousTransfer: Failed to find an non-isochronous endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
    Status = UsbIo->UsbAsyncIsochronousTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      Data,
                      DataLength,
                      UsbIsochronousCallBack,
                      NULL
                      );

    //
    // UsbAsyncIsochronousTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) ||
        (Status == EFI_UNSUPPORTED      )) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid040,
                   L"EFI_USB_IO_PROTOCOL.UsbAsyncIsochronousTransfer - UsbAsyncIsochronousTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Isochronous endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbAsyncIsochronousTransferConformanceSubTest1",
                  L"TDS 5.12.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

/**
 *  TDS 5.11.2.1 - UsbIsochronousTransfer should return EFI_INVALID_PARAMETER when DeviceEndpoint is not valid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbIsochronousTransferConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  UINTN                   DataLength;
  UINT32                  UsbStatus;
  UINT32                  Data[255];

  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbIsochronousTransferConformanceSubTest1",
                  L"TDS 5.11.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  DataLength = 128;

  //
  // 1. DeviceEndpoint is neither between 0x01 and 0x0F nor between 0x81 and 0x8F
  //
  // DeviceEndpoint = 0
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid041,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 16
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    16, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid042,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 16",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x80
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0x80, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid043,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x80",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // DeviceEndpoint = 0x90
  //
  Status = UsbIo->UsbIsochronousTransfer (
                    UsbIo,
                    0x90, // invalid DeviceEndpoint
                    Data,
                    DataLength,
                    &UsbStatus
                    );

  //
  // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
  // the returned status code EFI_UNSUPPORTED is also a valid value.
  //
  if ((Status == EFI_INVALID_PARAMETER) ||
      (Status == EFI_UNSUPPORTED      )) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid044,
                 L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with DeviceEndpoint = 0x90",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // 2. DeviceEndpoint is not an Isochronous endpoint
  //
  // Attributes != 0x01 means this is not an Isochronous endpoint
  //
  Status = GetUsbEndpointNotOfAttr (UsbIo, StandardLib, 0x01, 0x03, &EndpointDesc) ;
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbIsochronousTransfer: Failed to find an non-isochronous endpoint. Skipped this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
    Status = UsbIo->UsbIsochronousTransfer (
                      UsbIo,
                      EndpointDesc.EndpointAddress,
                      Data,
                      DataLength,
                      &UsbStatus
                      );

    //
    // UsbIsochronousTransfer() can be a optional interface in pre-boot. So
    // the returned status code EFI_UNSUPPORTED is also a valid value.
    //
    if ((Status == EFI_INVALID_PARAMETER) ||
        (Status == EFI_UNSUPPORTED      )) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid045,
                   L"EFI_USB_IO_PROTOCOL.UsbIsochronousTransfer - UsbIsochronousTransfer() returns EFI_INVALID_PARAMETER with the endpoint is not a Isochronous endpoint",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbIsochronousTransferConformanceSubTest1",
                  L"TDS 5.11.2.1 - DeviceEndpoint is not valid\n"
                  );
  }

  return EFI_SUCCESS;
}

/**
 *  TDS 5.5.2.1 - UsbGetDeviceDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetDeviceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetDeviceDescriptorConformanceSubTest1",
                  L"TDS 5.5.2.1 - Call UsbGetDeviceDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter DeviceDescriptor is NULL
  //
  Status = UsbIo->UsbGetDeviceDescriptor (UsbIo, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid027,
                 L"EFI_USB_IO_PROTOCOL.UsbGetDeviceDescriptor - UsbGetDeviceDescriptor() returns EFI_INVALID_PARAMETER with DeviceDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetDeviceDescriptorConformanceSubTest1",
                  L"TDS 5.5.2.1 - Calling UsbGetDeviceDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  TDS 5.6.2.1 - UsbGetConfigDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetConfigDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetConfigDescriptorConformanceSubTest1",
                  L"TDS 5.6.2.1 - Call UsbGetConfigDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter ConfigurationDescriptor is NULL
  //
  Status = UsbIo->UsbGetConfigDescriptor (UsbIo, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid028,
                 L"EFI_USB_IO_PROTOCOL.UsbGetConfigDescriptor - UsbGetConfigDescriptor() returns EFI_INVALID_PARAMETER with ConfigurationDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetConfigDescriptorConformanceSubTest1",
                  L"TDS 5.6.2.1 - Calling UsbGetConfigDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.7.2.1 - UsbGetInterfaceDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetInterfaceDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetInterfaceDescriptorConformanceSubTest1",
                  L"TDS 5.7.2.1 - Call UsbGetInterfaceDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter InterfaceDescriptor is NULL
  //
  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, NULL);

  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid029,
                 L"EFI_USB_IO_PROTOCOL.UsbGetInterfaceDescriptor - UsbGetInterfaceDescriptor() returns EFI_INVALID_PARAMETER with InterfaceDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetInterfaceDescriptorConformanceSubTest1",
                  L"TDS 5.7.2.1 - Calling UsbGetInterfaceDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.8.2.1 - UsbGetEndpointDescriptor should return EFI_INVALID_PARAMETER when Parameter is invalid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetEndpointDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDescriptor;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest1",
                  L"TDS 5.8.2.1 - Call UsbGetEndpointDescriptor with invalid parameter\n"
                  );
  }

  //
  // the parameter EndpointDescriptor is NULL
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, 0, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid030,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_INVALID_PARAMETER with EndpointDescriptor is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );


  //
  // the parameter EndpointIndex > 15
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, 16, &EndpointDescriptor);
  if (Status == EFI_INVALID_PARAMETER) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid031,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_INVALID_PARAMETER with EndpointIndex > 15",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest1",
                  L"TDS 5.8.2.1 - Calling UsbGetEndpointDescriptor() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.8.2.2 - UsbGetEndpointDescriptor should return EFI_NOT_FOUND when endpoint is non-existed.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetEndpointDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_ENDPOINT_DESCRIPTOR  EndpointDescriptor;
  EFI_USB_INTERFACE_DESCRIPTOR InterfaceDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest2",
                  L"TDS 5.8.2.2 - Call UsbGetEndpointDescriptor with non-existed endpoint\n"
                  );
  }

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbGetEndpointDescriptorConformanceSubTest2: FAILED in UsbGetInterfaceDescriptor--Skip this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbGetEndpointDescriptorConformanceSubTest2--Skipped",
                    L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                    );
    }
    return Status ;
  }

  if (InterfaceDesc.NumEndpoints == 0){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbGetEndpointDescriptorConformanceSubTest2: Couldn't get an undefined endpoint--Skip this test",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (LoggingLib != NULL) {
      LoggingLib->ExitFunction (
                    LoggingLib,
                    L"UsbGetEndpointDescriptorConformanceSubTest2--Skipped",
                    L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                    );
    }
    return Status ;

  }


  //
  // the parameter EndpointIndex >= InterfaceDescriptor.NumEndpoints
  //
  Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, (UINT8)(InterfaceDesc.NumEndpoints), &EndpointDescriptor);
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid032,
                 L"EFI_USB_IO_PROTOCOL.UsbGetEndpointDescriptor - UsbGetEndpointDescriptor() returns EFI_NOT_FOUND with EndpointIndex >= InterfaceDescriptor.NumEndpoints",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetEndpointDescriptorConformanceSubTest2",
                  L"TDS 5.8.2.2 - Calling UsbGetEndpointDescriptor() with non-existed endpoint\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}

/**
 *  TDS 5.9.2.1 - UsbPortReset should return EFI_INVALID_PARAMETER when parameter is invalid.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbPortResetConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;
  EFI_USB_DEVICE_DESCRIPTOR    DeviceDesc;
  EFI_USB_INTERFACE_DESCRIPTOR InterfaceDesc;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbPortResetConformanceSubTest1",
                  L"TDS 5.9.2.1 - Call UsbPortReset with invalid parameter\n"
                  );
  }

  //
  // The controller specified by parameter This is a USB hub
  //

  Status = UsbIo->UsbGetDeviceDescriptor (UsbIo, &DeviceDesc);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbPortResetConformanceSubTest1: FAILEDin UsbGetDeviceDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status ;
  }

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"UsbPortResetConformanceSubTest1: FAILEDin UsbGetInterfaceDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status ;
  }

  //
  // this usbio is for usb hub
  //
  if ((DeviceDesc.DeviceClass == 0x09) &&
      (InterfaceDesc.InterfaceClass == 0x09)) {
    Status = UsbIo->UsbPortReset (UsbIo);
    if (Status == EFI_INVALID_PARAMETER) {
      Result = EFI_TEST_ASSERTION_PASSED;
    } else {
      Result = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   Result,
                   gUsbIoTestConformanceAssertionGuid033,
                   L"EFI_USB_IO_PROTOCOL.UsbPortReset - UsbPortReset() returns EFI_INVALID_PARAMETER with the controller specified by parameter This is a USB hub",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }else{
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"UsbPortResetConformanceSubTest1: The controller specified by parameter This is not a USB hub. Skip conf. test for portreset",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );
  }

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbPortResetConformanceSubTest1",
                  L"TDS 5.9.2.1 - Calling UsbPortReset() with invalid parameter\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
 }


/**
 *  TDS 5.10.2.1 - UsbGetStringDescriptor should return EFI_NOT_FOUND when LangID is not found.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetStringDescriptorConformanceSubTest1 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted LangID\n"
                  );
  }

  //
  // LangID=0
  //
  Status = UsbIo->UsbGetStringDescriptor (UsbIo, 0, 1, NULL);
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid034,
                 L"EFI_USB_IO_PROTOCOL.UsbGetStringDescriptor - UsbGetStringDescriptor() returns EFI_NOT_FOUND with LangID = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest1",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted LangID\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
 }

/**
 *  TDS 5.10.2.1 - UsbGetStringDescriptor should return EFI_NOT_FOUND when StringIndex is not found.
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
UsbGetStringDescriptorConformanceSubTest2 (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      Result;

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted StringIndex\n"
                  );
  }

  //
  // StringIndex=0
  //
  Status = UsbIo->UsbGetStringDescriptor (UsbIo, 1, 0, NULL);
  if (Status == EFI_NOT_FOUND) {
    Result = EFI_TEST_ASSERTION_PASSED;
  } else {
    Result = EFI_TEST_ASSERTION_FAILED;
  }

  //
  // Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 Result,
                 gUsbIoTestConformanceAssertionGuid035,
                 L"EFI_USB_IO_PROTOCOL.UsbGetStringDescriptor - UsbGetStringDescriptor() returns EFI_NOT_FOUND with StringIndex = 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"UsbGetStringDescriptorConformanceSubTest2",
                  L"TDS 5.10.2.1 - Call UsbGetStringDescriptor with unexisted StringIndex\n"
                  );
  }

  //
  // Done
  //
  return EFI_SUCCESS;
 }


/**
 *  @brief This function retrieves the endpoint descriptor to find an non-bulk endpoint
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param Attributes     The attribute of the endpoint we don't want to retrieve
 *  @param AttribMask     The mask of attribute of the endpoint we want to retrieve
 *  @param pEndpointDesc: A pointer to the caller allocated USB Endpoint Descriptor
 *                        to store the resulted non-bulk endpoint
 *  @return EFI_SUCESS if find an non-bulk endpoint
 *  @return EFI error message if fail to find an non-bulk endpoint.
 */
EFI_STATUS
GetUsbEndpointNotOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
)
{
  EFI_STATUS                   Status;
  EFI_USB_INTERFACE_DESCRIPTOR InterfaceDesc ;
  UINT8                        Index;

  Status = EFI_SUCCESS ;

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (( EFI_ERROR(Status))
    ||(InterfaceDesc.NumEndpoints == 0) ){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"GetUsbEndpointNotOfAttr: FAILED at UsbGetInterfaceDescriptor.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
     return EFI_ABORTED ;
  }

  for (Index = 0; Index < InterfaceDesc.NumEndpoints; Index++) {
    Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, Index, pEndpointDesc);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"GetUsbEndpointNotOfAttr: FAILED at UsbGetEndpointDescriptor.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );
       return EFI_ABORTED ;
    }
    if ((pEndpointDesc->Attributes & AttribMask) == (Attributes & AttribMask)) {
         break ;
    }
  }
  if (Index == InterfaceDesc.NumEndpoints){
    Status = EFI_SUCCESS ;
  } else {
    Status = EFI_NOT_FOUND ;
  }

  return Status ;
}

/**
 *  @brief This function retrieves the endpoint descriptor to find a bulk endpoint
 *  @param UsbIo          A pointer to the EFI_USB_IO_PROTOCOL instance
 *  @param Attributes     The attribute of the endpoint we want to retrieve
 *  @param AttribMask     The mask of attribute of the endpoint we want to retrieve
 *  @param pEndpointDesc: A pointer to the caller allocated USB Endpoint Descriptor
 *                        to store the resulted bulk endpoint
 *  @return EFI_SUCESS if find a bulk endpoint
 *  @return EFI error message if fail to find a bulk endpoint.
 */
EFI_STATUS
GetUsbEndpointOfAttr (
  IN EFI_USB_IO_PROTOCOL                  *UsbIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  UINT8                               Attributes,
  IN  UINT8                               AttribMask,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR         *pEndpointDesc
)
{
  EFI_STATUS                   Status;
  EFI_USB_INTERFACE_DESCRIPTOR InterfaceDesc ;
  UINT8                        Index;

  Status = EFI_SUCCESS ;

  Status = UsbIo->UsbGetInterfaceDescriptor (UsbIo, &InterfaceDesc);
  if (( EFI_ERROR(Status))
    ||(InterfaceDesc.NumEndpoints == 0) ){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"GetUsbEndpointOfAttr: FAILED at UsbGetInterfaceDescriptor.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
     return EFI_ABORTED ;
  }

  for (Index = 0; Index < InterfaceDesc.NumEndpoints; Index++) {
    Status = UsbIo->UsbGetEndpointDescriptor (UsbIo, Index, pEndpointDesc);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"GetUsbEndpointNotOfAttr: FAILED at UsbGetEndpointDescriptor.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );
       return EFI_ABORTED ;
    }
    if ((pEndpointDesc->Attributes & AttribMask) == (Attributes & AttribMask)) {
      break ;
    }
  }
  if (Index == InterfaceDesc.NumEndpoints){
    Status = EFI_NOT_FOUND ;
  } else {
    Status = EFI_SUCCESS ;
  }

  return Status ;
}

EFI_STATUS
UsbInterruptCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
UsbIsochronousCallBack (
  IN VOID     *Data,
  IN UINTN    DataLength,
  IN VOID     *Context,
  IN UINT32   Status
)
{
  return EFI_SUCCESS;
}
