/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctCore.h

Abstract:

  This file provides the SCT core initialization services.

--*/

#ifndef _EFI_SCT_CORE_H_
#define _EFI_SCT_CORE_H_

//
// External functions declarations
//

EFI_STATUS
InitializeSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
InitializeFrameworkTable (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
FreeFrameworkTable (
  VOID
  );

#endif
