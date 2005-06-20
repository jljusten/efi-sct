/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BbTest.h

Abstract:

  This file defines the EFI Black-Box Test Protocol.

--*/

#ifndef _EFI_BB_TEST_H_
#define _EFI_BB_TEST_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

//
// EFI Black-Box Test Protocol Definitions
//

#define EFI_BB_TEST_GUID                \
  { 0x8C41CE3E, 0xB255, 0x4966, 0xB5, 0x3C, 0x39, 0x76, 0x5A, 0xE1, 0x11, 0xD0 }

#define EFI_BB_TEST_REVISION            0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_BB_TEST_ENTRY);
EFI_FORWARD_DECLARATION (EFI_BB_TEST_PROTOCOL);

//
// EFI Black-Box Test Entry Point
//

typedef
EFI_STATUS
(EFIAPI *EFI_BB_ENTRY_POINT) (
  IN  EFI_BB_TEST_PROTOCOL              *This,
  IN  VOID                              *ClientInterface,
  IN  EFI_TEST_LEVEL                    TestLevel,
  IN  EFI_HANDLE                        SupportHandle
  );

//
// EFI Black-Box Test Entry
//

typedef struct _EFI_BB_TEST_ENTRY {
  EFI_BB_TEST_ENTRY                     *Next;
  EFI_GUID                              EntryId;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TEST_LEVEL                        TestLevelSupportMap;
  EFI_GUID                              *SupportProtocols;
  EFI_TEST_ATTRIBUTE                    CaseAttribute;
  EFI_BB_ENTRY_POINT                    EntryPoint;
} EFI_BB_TEST_ENTRY;

//
// EFI Black-Box Test Protocol
//

typedef struct _EFI_BB_TEST_PROTOCOL {
  UINT64                                TestRevision;
  EFI_GUID                              CategoryGuid;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_BB_TEST_ENTRY                     *EntryList;
} EFI_BB_TEST_PROTOCOL;

//
// Global ID for EFI Black-Box Test Protocol
//

extern EFI_GUID gEfiBbTestGuid;

#endif
