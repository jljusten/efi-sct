/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctOutput.h

Abstract:

  This file provides a default test output library.

--*/

#ifndef _EFI_SCT_OUTPUT_H_
#define _EFI_SCT_OUTPUT_H_

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (TestOutputLibrary)

//
// Private interface data structures of TestOutput protocol
//

#define TEST_OUTPUT_PRIVATE_DATA_SIGNATURE  EFI_SIGNATURE_32('T','O','L','I')

#define TEST_OUTPUT_PRIVATE_DATA_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//
EFI_FORWARD_DECLARATION (TEST_OUTPUT_FILE);

typedef struct _TEST_OUTPUT_FILE {
  TEST_OUTPUT_FILE            *Next;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  CHAR16                      *FileName;
  EFI_FILE_HANDLE             FileHandle;
  UINTN                       OpenCount;
} TEST_OUTPUT_FILE;

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          TestOutput;
  TEST_OUTPUT_FILE                          *OutputFileList;
} TEST_OUTPUT_PRIVATE_DATA;

#define TEST_OUTPUT_PRIVATE_DATA_FROM_THIS(a) \
  CR(a, TEST_OUTPUT_PRIVATE_DATA, TestOutput, TEST_OUTPUT_PRIVATE_DATA_SIGNATURE)

//
// Global variables
//

extern EFI_TEST_OUTPUT_LIBRARY_PROTOCOL *gOutputProtocol;

#endif
