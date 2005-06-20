/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  str.c

Abstract:

  String operation functions

--*/

#include "lib.h"


INTN
StrCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2
    )
// compare strings
{
    while (*s1) {
        if (*s1 != *s2) {
            break;
        }

        s1 += 1;
        s2 += 1;
    }

    return *s1 - *s2;
}

INTN
StrnCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2,
    IN UINTN    len
    )
// compare strings
{
    while (*s1  &&  len) {
        if (*s1 != *s2) {
            break;
        }

        s1  += 1;
        s2  += 1;
        len -= 1;
    }

    return len ? *s1 - *s2 : 0;
}


INTN
LibStubStriCmp (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *s1,
    IN CHAR16                           *s2
    )
{
    return StrCmp (s1, s2);
}

VOID
LibStubStrLwrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *Str
    )
{
}

INTN
StriCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2
    )
// compare strings
{
    return UnicodeInterface->StriColl(UnicodeInterface, s1, s2);
}

VOID
StrLwr (
    IN CHAR16   *Str
    )
// lwoer case string
{
    UnicodeInterface->StrLwr(UnicodeInterface, Str);
}

VOID
StrUpr (
    IN CHAR16   *Str
    )
// upper case string
{
    UnicodeInterface->StrUpr(UnicodeInterface, Str);
}

VOID
StrCpy (
    IN CHAR16   *Dest,
    IN CHAR16   *Src
    )
// copy strings
{
    while (*Src) {
        *(Dest++) = *(Src++);
    }
    *Dest = 0;
}

VOID
StrCat (
    IN CHAR16   *Dest,
    IN CHAR16   *Src
    )
{
    StrCpy(Dest+StrLen(Dest), Src);
}

UINTN
StrLen (
    IN CHAR16   *s1
    )
// string length
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return len;
}

UINTN
StrSize (
    IN CHAR16   *s1
    )
// string size
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return (len + 1) * sizeof(CHAR16);
}

CHAR16 *
StrDuplicate (
    IN CHAR16   *Src
    )
// duplicate a string
{
    CHAR16      *Dest;
    UINTN       Size;

    Size = StrSize(Src);
    Dest = AllocatePool (Size);
    if (Dest) {
        CopyMem (Dest, Src, Size);
    }
    return Dest;
}

UINTN
strlena (
    IN CHAR8    *s1
    )
// string length
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return len;
}

UINTN
strcmpa (
    IN CHAR8    *s1,
    IN CHAR8    *s2
    )
// compare strings
{
    while (*s1) {
        if (*s1 != *s2) {
            break;
        }

        s1 += 1;
        s2 += 1;
    }

    return *s1 - *s2;
}

UINTN
strncmpa (
    IN CHAR8    *s1,
    IN CHAR8    *s2,
    IN UINTN    len
    )
// compare strings
{
    while (*s1  &&  len) {
        if (*s1 != *s2) {
            break;
        }

        s1  += 1;
        s2  += 1;
        len -= 1;
    }

    return len ? *s1 - *s2 : 0;
}



UINTN
xtoi (
    CHAR16  *str
    )
// convert hex string to uint
{
    UINTN       u;
    CHAR16      c;

    // skip preceeding white space
    while (*str && *str == ' ') {
        str += 1;
    }

    // skip preceeding zeros
    while (*str && *str == '0') {
        str += 1;
    }

    // skip preceeding white space
    if (*str && (*str == 'x' || *str == 'X')) {
        str += 1;
    }

    // convert hex digits
    u = 0;
    c = *(str++);
    while (c) {
        if (c >= 'a'  &&  c <= 'f') {
            c -= 'a' - 'A';
        }

        if ((c >= '0'  &&  c <= '9')  ||  (c >= 'A'  &&  c <= 'F')) {
            u = u << 4  |  c - (c >= 'A' ? 'A'-10 : '0');
        } else {
            break;
        }
        c = *(str++);
    }

    return u;
}

UINTN
Atoi (
    CHAR16  *str
    )
// convert hex string to uint
{
    UINTN       u;
    CHAR16      c;

    // skip preceeding white space
    while (*str && *str == ' ') {
        str += 1;
    }

    // convert digits
    u = 0;
    c = *(str++);
    while (c) {
        if (c >= '0' && c <= '9') {
            u = (u * 10) + c - '0';
        } else {
            break;
        }
        c = *(str++);
    }

    return u;
}

BOOLEAN
MetaMatch (
    IN CHAR16   *String,
    IN CHAR16   *Pattern
    )
{
    CHAR16  c, p, l;

    for (; ;) {
        p = *Pattern;
        Pattern += 1;

        switch (p) {
        case 0:
            // End of pattern.  If end of string, TRUE match
            return (BOOLEAN)(*String ? FALSE : TRUE);

        case '*':
            // Match zero or more chars
            while (*String) {
                if (MetaMatch (String, Pattern)) {
                    return TRUE;
                }
                String += 1;
            }
            return MetaMatch (String, Pattern);

        case '?':
            // Match any one char
            if (!*String) {
                return FALSE;
            }
            String += 1;
            break;

        case '[':
            // Match char set
            c = *String;
            if (!c) {
                return FALSE;                       // syntax problem
            }

            l = 0;
            p = *Pattern++;
            while ( p ) {
                if (p == ']') {
                    return FALSE;
                }

                if (p == '-') {                     // if range of chars,
                    p = *Pattern;                   // get high range
                    if (p == 0 || p == ']') {
                        return FALSE;               // syntax problem
                    }

                    if (c >= l && c <= p) {         // if in range,
                        break;                      // it's a match
                    }
                }

                l = p;
                if (c == p) {                       // if char matches
                    break;                          // move on
                }
                p = *Pattern++;
            }

            // skip to end of match char set
            while (p && p != ']') {
                p = *Pattern;
                Pattern += 1;
            }

            String += 1;
            break;

        default:
            c = *String;
            if (c != p) {
                return FALSE;
            }

            String += 1;
            break;
        }
    }
}


BOOLEAN
LibStubMetaiMatch (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *String,
    IN CHAR16                           *Pattern
    )
{
    return MetaMatch (String, Pattern);
}


BOOLEAN
MetaiMatch (
    IN CHAR16   *String,
    IN CHAR16   *Pattern
    )
{
    return UnicodeInterface->MetaiMatch(UnicodeInterface, String, Pattern);
}
