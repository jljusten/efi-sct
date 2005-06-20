/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  WbTest.h

Abstract:

  This file defines the EFI White-Box Test Protocol.

--*/

#ifndef _EFI_WB_TEST_H_
#define _EFI_WB_TEST_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

//
// EFI White-Box Test Protocol Definitions
//

#define EFI_WB_TEST_GUID                \
  { 0x0B486CED, 0x25EB, 0x448a, 0xB2, 0xB2, 0x22, 0x4E, 0x7A, 0x20, 0xCF, 0x57 }

#define EFI_WB_TEST_REVISION            0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_WB_TEST_ENTRY);
EFI_FORWARD_DECLARATION (EFI_WB_TEST_PROTOCOL);

//
// EFI White-Box Test Entry Point
//

typedef
EFI_STATUS
(EFIAPI *EFI_WB_ENTRY_POINT) (
  IN  EFI_WB_TEST_PROTOCOL              *This,
  IN  EFI_TEST_LEVEL                    TestLevel,
  IN  EFI_HANDLE                        SupportHandle
  );

//
// EFI White-Box Test Entry
//

typedef struct _EFI_WB_TEST_ENTRY {
  EFI_WB_TEST_ENTRY                     *Next;
  EFI_GUID                              EntryId;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TEST_LEVEL                        TestLevelSupportMap;
  EFI_GUID                              *SupportProtocols;
  EFI_TEST_ATTRIBUTE                    CaseAttribute;
  EFI_WB_ENTRY_POINT                    EntryPoint;
} EFI_WB_TEST_ENTRY;

//
// EFI White-Box Test Protocol
//

typedef struct _EFI_WB_TEST_PROTOCOL {
  UINT64                                TestRevision;
  EFI_GUID                              CategoryGuid;
  EFI_HANDLE                            ClientHandle;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_WB_TEST_ENTRY                     *EntryList;
} EFI_WB_TEST_PROTOCOL;

//
// Global ID for EFI White-Box Test Protocol
//

extern EFI_GUID gEfiWbTestGuid;

#endif
