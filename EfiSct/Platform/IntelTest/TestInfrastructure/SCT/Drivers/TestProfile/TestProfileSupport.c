/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestProfileSupport.c

Abstract:

  Provides the support services for the test profile library driver.

--*/

#include "TestProfileSupport.h"

extern EFI_BOOT_SERVICES *gBS;

VOID *
memset(
  VOID        *b,
  INTN        c,
  UINTN       len
  )
{
  CHAR8 *p;
  UINTN i;

  p = b;
  for (i = 0; i < len; i++) {
    p[i] = (CHAR8)c;
  }
  return (p);
}

VOID *
calloc(
  UINTN       NMemb,
  UINTN       MembSize
  )
{
  UINTN NewSize;
  VOID *NewMem;

  NewSize = NMemb * MembSize;
  NewMem = malloc (NewSize);
  if (NewMem) {
    memset (NewMem, 0, NewSize);
  }

  return NewMem;
}

VOID*
malloc (
  UINTN       size
  )
{
  VOID  *pMem;

  if (gBS->AllocatePool (EfiBootServicesData, size, &pMem) != EFI_SUCCESS) {
    return NULL;
  }
  return pMem;
}

VOID
free (
  VOID        *addr
  )
{
  gBS->FreePool (addr);
}

INTN
memcmp(
  VOID        *s1,
  VOID        *s2,
  UINTN       n
  )
{
  CHAR8 *p1, *p2;

  p1 = s1;
  p2 = s2;
  if (n != 0) {
    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return (0);
}

VOID *
memcpy(
  VOID        *dst,
  VOID        *src,
  UINTN       len
  )
{
  CHAR8 *d, *s;

  d = dst;
  s = src;
  while (len--) {
    *(d++) = *(s++);
  }
  return dst;
}

CHAR8 *
strchr(
  CHAR8       *p,
  INTN        ch
  )
{
  for (; ; ++p) {
    if (*p == ch)
      return((CHAR8 *)p);
    if (!*p)
      return((CHAR8 *)NULL);
  }
  /* NOTREACHED */
}

INTN
strcmp(
  CHAR8       *s1,
  CHAR8       *s2
  )
{
  while (*s1 == *s2++) {
    if (*s1++ == 0)
      return 0;
  }
  return (*s1 - *s2 - 1);
}

INTN
stricmp(
  CHAR8       *s1,
  CHAR8       *s2
  )
{
  while (toupper(*s1) == toupper(*s2)) {
    s2++;
    if (*s1++ == 0)
      return (0);
  }
  return (*s1 - *s2);
}

CHAR8 *
strcpy(
  CHAR8       *to,
  CHAR8       *from
  )
{
  CHAR8 *save;

  save = to;
  for (; (*to = *from) != 0 ; ++from, ++to)
    ;
  return(save);
}

CHAR8 *
strncpy(
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  )
{
  CHAR8 *d;
  CHAR8 *s;

  d = dst;
  s = src;
  if (n != 0) {
    do {
      if ((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while (--n != 0)
          *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  return (dst);
}

UINTN
strlen(
  CHAR8       *str
  )
{
  CHAR8 *s;

  for (s = str; *s; ++s)
    ;
  return (UINTN)(s - str);
}

CHAR8 *
strdup(
  CHAR8       *str
)
{
  CHAR8 *copy;

  if (str != NULL) {
    copy = malloc(strlen(str) + 1);
    if (copy != NULL)
      return strcpy(copy, str);
  }
  return NULL;
}

CHAR8 *
strcat(
  CHAR8       *s,
  CHAR8       *append
)
{
  CHAR8 *save;

  save = s;
  for (; *s; ++s)
    ;
  while ( (*s++ = *append++) != 0)
    ;
  return(save);
}

CHAR16 *
wcsdup (
  CHAR16      *str
)
{
  CHAR16 *copy;

  if (str != NULL) {
    copy = calloc(wcslen(str) + 1, sizeof(CHAR16));
    if (copy != NULL)
      return wcscpy(copy, str);
  }
  return NULL;
}

CHAR16 *
wcschr(
  CHAR16      *p,
  INTN        ch
  )
{
  for (;; ++p) {
    if (*p == ch)
      return((CHAR16 *)p);
    if (!*p)
      return((CHAR16 *)NULL);
  }
  /* NOTREACHED */
}

CHAR16 *
wcscpy(
  CHAR16      *to,
  CHAR16      *from
  )
{
  CHAR16 *save;

  save = to;
  for (; (*to = *from) != 0; ++from, ++to)
    ;
  return(save);
}

UINTN
wcslen(
  CHAR16      *str
  )
{
  CHAR16 *s;

  for (s = str; *s; ++s)
    ;
  return (UINTN)(s - str);
}

UINTN
wcstombs(
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *s = (CHAR8) (*pwcs++ & 0x00ff);
    if (*s++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}

UINTN
mbstowcs(
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *pwcs = (CHAR16)(*s++ & 0x00ff);
    if (*pwcs++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}
