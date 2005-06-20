/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ApTest.h

Abstract:

  This file defines a protocol interface for Application Test.

--*/

#ifndef _EFI_AP_TEST_H_
#define _EFI_AP_TEST_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

//
// EFI Application Test Interface definitions
//

#define EFI_AP_TEST_REVISION            0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_AP_TEST_ENTRY);

//
// EFI Application Test Entry Point
//

typedef struct _EFI_AP_TEST_ENTRY {
  EFI_AP_TEST_ENTRY     *Next;
  EFI_GUID              EntryId;
  CHAR16                *Name;
  CHAR16                *Description;
  UINT32                TestLevelSupportMap;
  EFI_GUID              *SupportProtocols;
  UINT32                CaseAttribute;
  CHAR16                *Parameters;
} EFI_AP_TEST_ENTRY;

//
// EFI Application Test Interface
//

typedef struct {
  UINT64                TestRevision;
  EFI_GUID              CategoryGuid;
  CHAR16                *Name;
  CHAR16                *Description;
  EFI_AP_TEST_ENTRY     *EntryList;
} EFI_AP_TEST_INTERFACE;

#endif
