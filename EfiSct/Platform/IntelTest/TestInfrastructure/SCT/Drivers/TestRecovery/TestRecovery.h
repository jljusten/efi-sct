/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestRecovery.h

Abstract:

  Driver to publish the Test Recovery Library Protocol.

--*/

#ifndef _EFI_TEST_RECOVERY_H_
#define _EFI_TEST_RECOVERY_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_TEST_PROTOCOL_DEFINITION (TslInit)
#include EFI_TEST_PROTOCOL_DEFINITION (TestRecoveryLibrary)

//
// Global definitions
//

#define MAX_BUFFER_SIZE                     1024

//
// Private data structures
//

#define TEST_RECOVERY_PRIVATE_DATA_SIGNATURE  EFI_SIGNATURE_32('T','R','L','P')

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL        TestRecovery;
  EFI_TRL_PRIVATE_INTERFACE                 PrivateInterface;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FileName;
} TEST_RECOVERY_PRIVATE_DATA;

#define TEST_RECOVERY_PRIVATE_DATA_FROM_TRL(a)  \
  CR(a, TEST_RECOVERY_PRIVATE_DATA, TestRecovery, TEST_RECOVERY_PRIVATE_DATA_SIGNATURE)

#define TEST_RECOVERY_PRIVATE_DATA_FROM_PI(a)   \
  CR(a, TEST_RECOVERY_PRIVATE_DATA, PrivateInterface, TEST_RECOVERY_PRIVATE_DATA_SIGNATURE)

#endif