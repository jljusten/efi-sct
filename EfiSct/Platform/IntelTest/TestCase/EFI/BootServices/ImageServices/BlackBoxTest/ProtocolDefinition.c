/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ProtocolDefinition.c

Abstract:

  Protocols that will be used during the Image Boot Services Test

--*/

#include "ProtocolDefinition.h"

//
// module globals
//
EFI_GUID mImageTestNoInterfaceProtocol1Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mImageTestNoInterfaceProtocol2Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_2_GUID;
EFI_GUID mImageTestNoInterfaceProtocol3Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_3_GUID;
EFI_GUID mImageTestNoInterfaceProtocol4Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_4_GUID;
EFI_GUID mImageTestNoInterfaceProtocol5Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_5_GUID;
EFI_GUID mImageTestNoInterfaceProtocol6Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_6_GUID;
EFI_GUID mImageTestNoInterfaceProtocol7Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_7_GUID;
EFI_GUID mImageTestNoInterfaceProtocol8Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_8_GUID;
EFI_GUID mImageTestNoInterfaceProtocol9Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_9_GUID;
EFI_GUID mImageTestNoInterfaceProtocol10Guid = IMAGE_TEST_NO_INTERFACE_PROTOCOL_10_GUID;

EFI_GUID mImageTestForLoadFileProtocol1Guid = IMAGE_TEST_FOR_LOAD_FILE_PROTOCOL_1_GUID;

EFI_GUID mImageTestVariableVendorGuid       = IMAGE_TEST_VARIABLE_VENDOR_GUID;

EFI_GUID mImageTestVendorDevicePath1Guid = IMAGE_TEST_VENDOR_DEVICE_PATH_1_GUID;

EFI_GUID mImageTestLoadFileDriverPathGuid       = IMAGE_TEST_LOAD_FILE_DRIVER_PATH_GUID;
EFI_GUID mImageTestLoadFileApplicationPathGuid  = IMAGE_TEST_LOAD_FILE_APPLICATION_PATH_GUID;
EFI_GUID mImageTestLoadFileBootPathGuid         = IMAGE_TEST_LOAD_FILE_BOOT_PATH_GUID;
EFI_GUID mImageTestLoadFileRuntimePathGuid      = IMAGE_TEST_LOAD_FILE_RUNTIME_PATH_GUID;
