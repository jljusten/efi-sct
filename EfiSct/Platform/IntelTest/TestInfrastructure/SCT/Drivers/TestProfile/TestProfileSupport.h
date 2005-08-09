/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestProfileSupport.h

Abstract:

  Provides the support services for the test profile library driver.

--*/

#ifndef _EFI_TEST_PROFILE_SUPPORT_H_
#define _EFI_TEST_PROFILE_SUPPORT_H_


#include "efi.h"

#define  toupper(c)  (((c <= 'z') && (c >= 'a')) ? (c + 'A' - 'a') : c)
#define  tolower(c)  (((c <= 'Z') && (c >= 'A')) ? (c - 'A' + 'a') : c)

VOID *
memset(
  VOID        *b,
  INTN        c,
  UINTN       len
  );

VOID *
calloc(
  UINTN       NMemb,
  UINTN       MembSize
  );

VOID*
malloc(
  UINTN       size
  );

VOID
free(
  VOID        *addr
  );

INTN
memcmp(
  VOID        *s1,
  VOID        *s2,
  UINTN       n
  );

VOID *
memcpy(
  VOID        *dst,
  VOID        *src,
  UINTN       len
  );

INTN
strcmp(
  CHAR8       *s1,
  CHAR8       *s2
  );

INTN
stricmp(
  CHAR8       *s1,
  CHAR8       *s2
  );

CHAR8 *
strchr(
  CHAR8       *p,
  INTN        ch
  );

CHAR8 *
strcpy(
  CHAR8       *to,
  CHAR8       *from
  );

CHAR8 *
strncpy(
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  );

CHAR8 *
strcat(
  CHAR8       *s,
  CHAR8       *append
  );

UINTN
strlen(
  CHAR8       *str
  );

CHAR8 *
strdup(
  CHAR8       *str
);

CHAR16 *
wcsdup (
  CHAR16      *str
);

CHAR16 *
wcschr(
  CHAR16      *p,
  INTN        ch
  );

CHAR16 *
wcscpy(
  CHAR16      *to,
  CHAR16      *from
  );

UINTN
wcslen(
  CHAR16      *str
  );

UINTN
wcstombs(
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  );

UINTN
mbstowcs(
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  );

#endif
