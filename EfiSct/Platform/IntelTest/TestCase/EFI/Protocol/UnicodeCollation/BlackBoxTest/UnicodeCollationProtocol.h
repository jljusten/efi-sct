/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UnicodeCollationProtocol.h

Abstract:

  Unicode Collation Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_UNICODE_COLLATION_FOR_TEST_H_
#define _EFI_UNICODE_COLLATION_FOR_TEST_H_

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_UNICODE_COLLATION_PROTOCOL_GUID \
  { 0x1d85cd7f, 0xf43d, 0x11d2, 0x9a, 0xc,  0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }

EFI_FORWARD_DECLARATION(EFI_UNICODE_COLLATION_PROTOCOL);


typedef
INTN
(EFIAPI *EFI_UNICODE_COLLATION_STRICOLL) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *s1,
  IN CHAR16                           *s2
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_METAIMATCH) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN CHAR16                           *Pattern
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRLWR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN OUT CHAR16                       *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRUPR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN OUT CHAR16                       *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_FATTOSTR) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN UINTN                            FatSize,
  IN CHAR8                            *Fat,
  OUT CHAR16                          *String
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_STRTOFAT) (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN UINTN                            FatSize,
  OUT CHAR8                           *Fat
  );

typedef struct _EFI_UNICODE_COLLATION_PROTOCOL {
  EFI_UNICODE_COLLATION_STRICOLL          StriColl;
  EFI_UNICODE_COLLATION_METAIMATCH        MetaiMatch;
  EFI_UNICODE_COLLATION_STRLWR            StrLwr;
  EFI_UNICODE_COLLATION_STRUPR            StrUpr;
  EFI_UNICODE_COLLATION_FATTOSTR          FatToStr;
  EFI_UNICODE_COLLATION_STRTOFAT          StrToFat;
  CHAR8                                   *SupportedLanguages;
} EFI_UNICODE_COLLATION_PROTOCOL;

extern EFI_GUID                           gEfiUnicodeCollationProtocolGuid;

#endif
