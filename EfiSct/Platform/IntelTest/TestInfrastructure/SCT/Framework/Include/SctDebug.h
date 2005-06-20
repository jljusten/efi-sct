/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctDebug.h

Abstract:

  This file provides the debug macro definitions for SCT.

--*/

#ifndef _EFI_SCT_DEBUG_H_
#define _EFI_SCT_DEBUG_H_

//
// Definitions
//

#define EFI_SCT_D_ERROR           0x01
#define EFI_SCT_D_DEBUG           0x02
#define EFI_SCT_D_TRACE           0x04

#define EFI_SCT_D_MASK            \
  (EFI_SCT_D_ERROR | EFI_SCT_D_DEBUG | EFI_SCT_D_TRACE)

//
// Construction and destruction services
//

EFI_STATUS
InitializeDebugServices (
  VOID
  );

EFI_STATUS
FreeDebugServices (
  VOID
  );

//
// EFI_SCT_DEBUG worker function
//

VOID
EfiSctDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  );

#ifdef EFI_DEBUG
  #define EFI_SCT_DEBUG(a)    EfiSctDebug a
#else
  #define EFI_SCT_DEBUG(a)
#endif

#endif
