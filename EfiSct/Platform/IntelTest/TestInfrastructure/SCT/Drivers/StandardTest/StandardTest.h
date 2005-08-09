/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  StandardTest.h

Abstract:

  Driver to publish the Standard Test Library Protocol.

--*/

#ifndef _EFI_STANDARD_TEST_H_
#define _EFI_STANDARD_TEST_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_TEST_PROTOCOL_DEFINITION (TslInit)
#include EFI_TEST_PROTOCOL_DEFINITION (TestOutputLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

//
// Global definitions
//

#define EFI_MAX_PRINT_BUFFER                1024

//
// Private data structures
//

#define STANDARD_TEST_PRIVATE_DATA_SIGNATURE  EFI_SIGNATURE_32('S','T','S','L')

typedef struct {
  BOOLEAN                                   EnableScreenOutput;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FileName;
  BOOLEAN                                   OverwriteFile;
  EFI_FILE_HANDLE                           FileHandle;
} EFI_LIB_CONFIG_FILE_HANDLE;

typedef struct {
  UINT32                                    Signature;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL        StandardTest;
  EFI_STANDARD_TSL_PRIVATE_INTERFACE        PrivateInterface;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *OutputProtocol;

  EFI_LIB_CONFIG_FILE_HANDLE                SystemLogFile;
  EFI_LIB_CONFIG_FILE_HANDLE                SystemKeyFile;
  EFI_LIB_CONFIG_FILE_HANDLE                CaseLogFile;
  EFI_LIB_CONFIG_FILE_HANDLE                CaseKeyFile;

  CHAR16                                    *BiosId;
  UINT32                                    PlatformNumber;
  UINT32                                    ConfigurationNumber;
  CHAR16                                    *ScenarioString;

  UINT64                                    TestRevision;
  CHAR16                                    *TestName;
  EFI_GUID                                  EntryId;
  CHAR16                                    *EntryName;
  CHAR16                                    *EntryDescription;
  EFI_GUID                                  *SupportProtocols;
  EFI_VERBOSE_LEVEL                         VerboseLevel;

  BOOLEAN                                   IsRecovery;
  UINT32                                    PassCount;
  UINT32                                    WarningCount;
  UINT32                                    FailCount;

  CHAR16                                    *TestCategory;
  CHAR16                                    *DevicePath;

  BOOLEAN                                   BeginLogging;
  EFI_TIME                                  StartTime;
} STANDARD_TEST_PRIVATE_DATA;

#define STANDARD_TEST_PRIVATE_DATA_FROM_STSL(a) \
  CR(a, STANDARD_TEST_PRIVATE_DATA, StandardTest, STANDARD_TEST_PRIVATE_DATA_SIGNATURE)

#define STANDARD_TEST_PRIVATE_DATA_FROM_PI(a)   \
  CR(a, STANDARD_TEST_PRIVATE_DATA, PrivateInterface, STANDARD_TEST_PRIVATE_DATA_SIGNATURE)

#endif
