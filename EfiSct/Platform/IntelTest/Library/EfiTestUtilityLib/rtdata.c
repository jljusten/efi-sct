/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  rtdata.c

Abstract:

  EFI library global data

--*/

#include "lib.h"

//
// RT - pointer to the runtime table
//

EFI_RUNTIME_SERVICES    *tRT;

//
// LibStandalone - TRUE if lib is linked in as part of the firmware.
// N.B. The EFI fw sets this value directly
//

BOOLEAN  LibFwInstance;

//
// EFIDebug - Debug mask
//

UINTN    EFIDebug    = EFI_DBUG_MASK;

//
// LibRuntimeDebugOut - Runtime Debug Output device
//

EFI_SIMPLE_TEXT_OUT_PROTOCOL    *LibRuntimeDebugOut;

//
// LibRuntimeRaiseTPL, LibRuntimeRestoreTPL - pointers to Runtime functions from the
//                                            Boot Services Table
//

EFI_RAISE_TPL   LibRuntimeRaiseTPL   = NULL;
EFI_RESTORE_TPL LibRuntimeRestoreTPL = NULL;

