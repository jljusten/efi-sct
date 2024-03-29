/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  efidebug.h

Abstract:

  EFI library debug functions

--*/

#ifndef _EFI_DEBUG_H
#define _EFI_DEBUG_H

extern UINTN     EFIDebug;

#ifdef EFI_DEBUG

  #define DBGASSERT(a)        DbgAssert(__FILE__, __LINE__, #a)
  #define DEBUG(a)            DbgPrint a

#else

  #define DBGASSERT(a)
  #define DEBUG(a)

#endif

#ifdef EFI_DEBUG_CLEAR_MEMORY

  #define DBGSETMEM(a,l)      SetMem(a,l,(CHAR8)BAD_POINTER)

#else

  #define DBGSETMEM(a,l)

#endif

#define D_INIT        0x00000001          // Initialization style messages
#define D_WARN        0x00000002          // Warnings
#define D_LOAD        0x00000004          // Load events
#define D_FS          0x00000008          // EFI File system
#define D_POOL        0x00000010          // Alloc & Free's
#define D_PAGE        0x00000020          // Alloc & Free's
#define D_INFO        0x00000040          // Verbose
#define D_VAR         0x00000100          // Variable
#define D_PARSE       0x00000200          // Command parsing
#define D_BM          0x00000400          // Boot manager
#define D_BLKIO       0x00001000          // BlkIo Driver
#define D_BLKIO_ULTRA 0x00002000          // BlkIo Driver
#define D_NET         0x00004000          // SNI Driver
#define D_NET_ULTRA   0x00008000          // SNI Driver
#define D_TXTIN       0x00010000          // Simple Input Driver
#define D_TXTOUT      0x00020000          // Simple Text Output Driver
#define D_ERROR       0x80000000          // Error

#define D_RESERVED    0x7fffC880          // Bits not reserved above

//
// Current Debug level of the system, value of EFIDebug
//
//#define EFI_DBUG_MASK   (D_ERROR | D_WARN | D_LOAD | D_BLKIO | D_INIT)
#define EFI_DBUG_MASK   (D_ERROR)

//
//
//

#ifdef EFI_DEBUG

  #define ASSERT(a)               if(!(a))       DBGASSERT(a)
  #define ASSERT_LOCKED(l)        if(!(l)->Lock) DBGASSERT(l not locked)
  #define ASSERT_STRUCT(p,t)      DBGASSERT(t not structure), p

#else

  #define ASSERT(a)
  #define ASSERT_LOCKED(l)
  #define ASSERT_STRUCT(p,t)

#endif


#endif
