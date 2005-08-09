/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ExecuteSupport.h

Abstract:

  This file provides the support services for test execution.

--*/

#ifndef _EFI_EXECUTE_SUPPORT_H_
#define _EFI_EXECUTE_SUPPORT_H_

//
// EFI_SCT_EXECUTE_INFO
//

typedef struct {
  EFI_SCT_TEST_CASE         *TestCase;

  EFI_SCT_CATEGORY_DATA     *Category;
  EFI_SCT_TEST_FILE         *TestFile;

  VOID                      *TestProtocol;
  VOID                      *TestEntry;

  EFI_SCT_LOG_STATE         State;

  UINT32                    Index;
  UINT32                    Iteration;
  UINT32                    Passes;
  UINT32                    Warnings;
  UINT32                    Failures;
} EFI_SCT_EXECUTE_INFO;

//
// Support functions declaration
//

EFI_STATUS
InitializeExecuteInfo (
  IN EFI_SCT_TEST_CASE            *TestCase,
  OUT EFI_SCT_EXECUTE_INFO        *ExecuteInfo
  );

EFI_STATUS
GetFileMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FilePath,
  OUT CHAR16                      **MetaName
  );

EFI_STATUS
GetFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  );

EFI_STATUS
GetKeyFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  );

EFI_STATUS
ResetExecuteTestResults (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  );

#endif
