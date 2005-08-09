/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctData.h

Abstract:

  This file provides the services to manage the test cases with the test
  execution.

--*/

#ifndef _EFI_SCT_DATA_EX_H_
#define _EFI_SCT_DATA_EX_H_

//
// External functions declaration
//

EFI_STATUS
SelectTestCase (
  IN EFI_GUID                     *Guid,
  IN UINT32                       Iterations
  );

EFI_STATUS
UnselectTestCase (
  IN EFI_GUID                     *Guid
  );

EFI_STATUS
GetTestCaseState (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_STATE          *TestState
  );

UINT32
GetTestCaseOrder (
  IN EFI_GUID                     *Guid
  );

UINT32
GetTestCaseIterations (
  IN EFI_GUID                     *Guid
  );

UINT32
GetTestCasePasses (
  IN EFI_GUID                     *Guid
  );

UINT32
GetTestCaseWarnings (
  IN EFI_GUID                     *Guid
  );

UINT32
GetTestCaseFailures (
  IN EFI_GUID                     *Guid
  );

EFI_STATUS
GetRunningTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

EFI_STATUS
GetNextTestCase (
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

BOOLEAN
IsTestFinished (
  VOID
  );

EFI_STATUS
ResetTestCaseOrder (
  VOID
  );

EFI_STATUS
ResetTestCaseResults (
  VOID
  );

EFI_STATUS
ResetTestCaseOrderAndResults (
  VOID
  );

EFI_STATUS
BuildTestCaseOrder (
  VOID
  );

#endif
