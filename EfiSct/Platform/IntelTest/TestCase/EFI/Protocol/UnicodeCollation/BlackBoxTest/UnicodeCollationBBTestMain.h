/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UnicodeCollationBBTestMain.h

Abstract:

  BB test header file of Unicode Collation Protocol

--*/


#ifndef _UNICODE_COLLATION_BBTEST_H_
#define _UNICODE_COLLATION_BBTEST_H_


#include "Efi.h"
#include "EfiTest.h"
#include "Guid.h"
#include "UnicodeCollationProtocol.h"

#include "EfiDriverLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"



#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

#define  UNICODE_COLLATION_PROTOCOL_TEST_REVISION    0x00010000

#define  MAX_SIZE_OF_STRING                          255
#define  MAX_SIZE_OF_STRESS_STRING                   65535

extern   CHAR8                                       EngUpperMap[0x100];
extern   CHAR8                                       EngLowerMap[0x100];
extern   CHAR8                                       EngInfoMap[0x100];
extern   CHAR8                                       OtherChars[];


#define CHAR_FAT_VALID                               0x01

#define ToUpper(a)  (CHAR16)(a <= 0xFF ? EngUpperMap[a] : a)
#define ToLower(a)  (CHAR16)(a <= 0xFF ? EngLowerMap[a] : a)



typedef struct {
  CHAR16             *S1;
  CHAR16             *S2;
  INTN               Result;
} STRICOLL_TEST_DATA_FIELD;

#define  STRING_COMPARE_EQUAL     0
#define  STRING_COMPARE_LESS      -1
#define  STRING_COMPARE_MORE      1

typedef struct {
  CHAR16             *Pattern;
  CHAR16             *String;
  BOOLEAN            Result;
} METAIMATCH_TEST_DATA_FIELD;

EFI_STATUS
InitializeBBTestUnicodeCollation (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUnicodeCollationProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
BBTestStriCollFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMetaiMatchFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrLwrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrUprFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFatToStrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrToFatFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  );

BOOLEAN
CheckStrLwr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrUpr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrEql (
  IN CHAR16                     *s1,
  IN CHAR16                     *s2
  );

UINTN
GetStrLen8(
  IN CHAR8                      *s
  );

UINTN
GetStrLen16(
  IN CHAR16                     *s
  );

BOOLEAN
CheckFatToStr (
  IN CHAR8                      *Fat,
  IN UINTN                      FatSize,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrToFat (
  IN CHAR16                     *Source,
  IN UINTN                      FatSize,
  IN CHAR8                      *Fat,
  IN BOOLEAN                    IsLongFileName
  );

VOID
InitCharMapping();

BOOLEAN
CheckLongFileName(
  IN CHAR16                     *Source,
  IN UINTN                      FatSize
  ) ;

//
// Entry GUIDs
//

#define UNICODE_COLLATION_PROTOCOL_STRICOLL_FUNCTION_AUTO_GUID \
  { 0xeba6c269, 0x68ff, 0x424f, { 0xba, 0xd4, 0x4d, 0x99, 0x7f, 0x2e, 0x6c, 0xd0 } }

#define UNICODE_COLLATION_PROTOCOL_METAIMATCH_FUNCTION_AUTO_GUID \
  { 0x88b2ba4d, 0x9dfb, 0x4475, { 0x80, 0x33, 0xd4, 0x18, 0x85, 0x11, 0x39, 0x72 } }

#define UNICODE_COLLATION_PROTOCOL_STRLWR_FUNCTION_AUTO_GUID \
  { 0xb81010c8, 0xec5a, 0x4ffd, { 0xb6, 0x74, 0xe9, 0x94, 0xa1, 0x34, 0x20, 0x8b } }

#define UNICODE_COLLATION_PROTOCOL_STRUPR_FUNCTION_AUTO_GUID \
  { 0xfbe12d00, 0x4261, 0x411f, { 0x84, 0xcc, 0x58, 0xd5, 0x9d, 0x1f, 0xbd, 0xd7 } }

#define UNICODE_COLLATION_PROTOCOL_FATTOSTR_FUNCTION_AUTO_GUID \
  { 0x9c43ab23, 0x56b7, 0x43ba, { 0x80, 0xb2, 0x67, 0x8, 0x54, 0x89, 0xd6, 0x39 } }

#define UNICODE_COLLATION_PROTOCOL_STRTOFAT_FUNCTION_AUTO_GUID \
  { 0xe23dd0f6, 0x53f9, 0x4c4f, { 0x82, 0xdc, 0xff, 0xf3, 0x58, 0x49, 0x99, 0x66 } }

#define UNICODE_COLLATION_PROTOCOL_STRESS_AUTO_GUID \
  { 0xa0f933ba, 0x1839, 0x4c34, { 0x94, 0xce, 0xee, 0x91, 0x96, 0x2d, 0x2f, 0x8c } }

#endif

