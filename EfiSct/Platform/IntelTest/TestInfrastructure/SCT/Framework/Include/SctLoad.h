/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctLoad.h

Abstract:

  This file provides the services to load test files and test support library
  files.

--*/

#ifndef _EFI_SCT_LOAD_H_
#define _EFI_SCT_LOAD_H_

//
// External functions declaration
//

//
// Test support file services
//

EFI_STATUS
LoadSupportFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive,
  OUT EFI_LIST_ENTRY              *SupportFileList
  );

EFI_STATUS
UnloadSupportFiles (
  IN EFI_LIST_ENTRY               *SupportFileList
  );

EFI_STATUS
OpenStandardSupportFiles (
  VOID
  );

EFI_STATUS
CloseStandardSupportFiles (
  VOID
  );

EFI_STATUS
OpenExtendedSupportFiles (
  IN EFI_GUID                     *Guids
  );

EFI_STATUS
CloseExtendedSupportFiles (
  IN EFI_GUID                     *Guids
  );

//
// Test file service
//

EFI_STATUS
LoadTestFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive,
  OUT EFI_LIST_ENTRY              *TestFileList
  );

EFI_STATUS
UnloadTestFiles (
  IN EFI_LIST_ENTRY               *TestFileList
  );

EFI_STATUS
FindTestFileByCaseGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_FILE           **TestFile,
  OUT VOID                        **TestProtocol,
  OUT VOID                        **TestEntry
  );

#endif
