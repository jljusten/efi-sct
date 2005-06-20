/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctData.h

Abstract:

  This file provides the services to load, save, and manage all kind of test
  data.

--*/

#ifndef _EFI_SCT_DATA_H_
#define _EFI_SCT_DATA_H_

//
// External functions declaration
//

//
// Application test services
//

EFI_STATUS
LoadApTest (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_AP_TEST_INTERFACE       **ApTest
  );

EFI_STATUS
FreeApTest (
  IN EFI_AP_TEST_INTERFACE        *ApTest
  );

//
// Configuration data services
//

EFI_STATUS
LoadConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_CONFIG_DATA         *ConfigData
  );

EFI_STATUS
SaveConfigData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  );

EFI_STATUS
FreeConfigData (
  IN EFI_SCT_CONFIG_DATA          *ConfigData
  );

//
// Category data services
//

EFI_STATUS
LoadCategoryData (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_LIST_ENTRY              *CategoryList
  );

EFI_STATUS
FreeCategoryData (
  IN EFI_LIST_ENTRY               *CategoryList
  );

EFI_STATUS
FindCategoryByGuid (
  IN  EFI_GUID                    *Guid,
  OUT EFI_SCT_CATEGORY_DATA       **Category
);

//
// Test case services
//

EFI_STATUS
LoadTestCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_LIST_ENTRY              *TestCaseList
  );

EFI_STATUS
SaveTestCases (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_LIST_ENTRY               *TestCaseList
  );

EFI_STATUS
LoadTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN OUT EFI_LIST_ENTRY           *TestCaseList
  );

EFI_STATUS
SaveTestSequence (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_LIST_ENTRY               *TestCaseList
  );

EFI_STATUS
FreeTestCases (
  IN EFI_LIST_ENTRY               *TestCaseList
  );

EFI_STATUS
CreateTestCases (
  OUT EFI_LIST_ENTRY              *TestCaseList
  );

EFI_STATUS
MergeTestCases (
  IN OUT EFI_LIST_ENTRY           *DstTestCaseList,
  IN EFI_LIST_ENTRY               *SrcTestCaseList
  );

EFI_STATUS
FindTestCaseByGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_CASE           **TestCase
  );

//
// Test node services
//

EFI_STATUS
CreateTestNodes (
  OUT EFI_LIST_ENTRY              *TestNodeList
  );

EFI_STATUS
FreeTestNodes (
  IN EFI_LIST_ENTRY               *TestNodeList
  );

#endif
