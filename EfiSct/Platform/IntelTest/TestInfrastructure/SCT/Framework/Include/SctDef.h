/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctDef.h

Abstract:

  This file defines the global definitions and variables.

--*/

#ifndef _EFI_SCT_DEF_H_
#define _EFI_SCT_DEF_H_

//
// Global definitions
//

#define EFI_SCT_NAME                        L"EFI Self Certification Test"
#define EFI_SCT_VERSION                     L"0.93"

#define EFI_SCT_SHORT_NAME                  L"SCT"

//
// The global directory and file names
//

#define EFI_SCT_PATH_DATA                   L"Data"
#define EFI_SCT_PATH_LOG                    L"Log"
#define EFI_SCT_PATH_OVERALL                L"Overall"
#define EFI_SCT_PATH_REPORT                 L"Report"
#define EFI_SCT_PATH_SEQUENCE               L"Sequence"
#define EFI_SCT_PATH_SUPPORT                L"Support"
#define EFI_SCT_PATH_TEST                   L"Test"

#define EFI_SCT_FILE_LOG                    L"Sct.log"
#define EFI_SCT_FILE_CFG                    L"Sct.cfg"

#define EFI_SCT_FILE_CONFIG                 L"Data\\Config.ini"
#define EFI_SCT_FILE_CATEGORY               L"Data\\Category.ini"
#define EFI_SCT_FILE_GUID_DATABASE          L"Data\\GuidFile.txt"
#define EFI_SCT_FILE_RECOVERY               L"Data\\Recovery.dat"
#define EFI_SCT_FILE_TEST_CASE              L"Data\\TestCase.ini"

#define EFI_SCT_FILE_SUMMARY_LOG            L"Overall\\Summary.log"
#define EFI_SCT_FILE_SUMMARY_EKL            L"Overall\\Summary.ekl"

//
// Maximum buffer size in the SCT
//
#define EFI_SCT_MAX_BUFFER_SIZE             512
#define MAX_STRING_LEN                      250

//
// System hang assertion
//
#define EFI_SYSTEM_HANG_ASSERTION_GUID      \
  { 0xde687a18, 0x0bbd, 0x4396, 0x85, 0x09, 0x49, 0x8f, 0xf2, 0x32, 0x34, 0xf1 }

//
// Global variables
//

extern EFI_SCT_FRAMEWORK_TABLE *gFT;

extern EFI_GUID gEfiSystemHangAssertionGuid;

extern UINTN gTestCaseMaxRunTimeMax;

#endif
