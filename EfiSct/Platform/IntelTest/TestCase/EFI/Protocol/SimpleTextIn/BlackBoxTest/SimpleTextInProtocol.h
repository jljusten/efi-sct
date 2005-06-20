/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleTextInProtocol.h

Abstract:

  Simple Input Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_SIMPLE_TEXT_INPUT_FOR_TEST_H_
#define _EFI_SIMPLE_TEXT_INPUT_FOR_TEST_H_

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_SIMPLE_TEXT_IN_PROTOCOL_GUID \
  { 0x387477c1, 0x69c7, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

EFI_FORWARD_DECLARATION(SIMPLE_INPUT_INTERFACE);


typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) (
  IN SIMPLE_INPUT_INTERFACE   *This,
  IN BOOLEAN              ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
  IN SIMPLE_INPUT_INTERFACE   *This,
  OUT EFI_INPUT_KEY       *Key
  );

typedef
struct _SIMPLE_INPUT_INTERFACE {
  EFI_INPUT_RESET                     Reset;
  EFI_INPUT_READ_KEY                  ReadKeyStroke;
  EFI_EVENT                           WaitForKey;
} SIMPLE_INPUT_INTERFACE;

extern EFI_GUID gEfiSimpleTextInProtocolGuid;

#endif
