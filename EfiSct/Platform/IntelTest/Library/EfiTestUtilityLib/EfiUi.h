/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EfiUi.h

Abstract:

  Protocol used to build User Interface (UI) stuff.

  This protocol is just data. It is a multi dimentional array.
  For each string there is an array of UI_STRING_ENTRY. Each string
  is for a different language translation of the same string. The list
  is terminated by a NULL UiString. There can be any number of
  UI_STRING_ENTRY arrays. A NULL array terminates the list. A NULL array
  entry contains all zeros.

  Thus the shortest possible EFI_UI_PROTOCOL has three UI_STRING_ENTRY.
  The String, it's NULL terminator, and the NULL terminator for the entire
  thing.

--*/

#ifndef _EFI_UI_H
#define _EFI_UI_H

#define EFI_UI_PROTOCOL \
  { 0x32dd7981, 0x2d27, 0x11d4, 0xbc, 0x8b, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

//
// International Language
//

typedef UINT8   ISO_639_2;
#define ISO_639_2_ENTRY_SIZE    3


typedef enum {
  UiDeviceString,
  UiVendorString,
  UiMaxString
} UI_STRING_TYPE;

typedef struct {
  ISO_639_2   *LangCode;
  CHAR16      *UiString;
} UI_STRING_ENTRY;

#define EFI_UI_VERSION      0x00010000

typedef struct _UI_INTERFACE {
  UINT32          Version;
  UI_STRING_ENTRY *Entry;
} UI_INTERFACE;

#endif
