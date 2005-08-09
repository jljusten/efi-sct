/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  InstallSct.h

Abstract:

  The EFI SCT installation.

--*/

#ifndef _EFI_INSTALL_SCT_H_
#define _EFI_INSTALL_SCT_H_

//
// Includes
//

#include "Efi.h"
#include "EfiShellLib.h"
#include "InstallSctDef.h"
#include "InstallSctSupport.h"

//
// Global definitions
//

#define INSTALL_SCT_1M                  (1024 * 1024)
#define INSTALL_SCT_FREE_SPACE          (1024 * 1024 * 100)

#define INSTALL_SCT_MAX_FILE_SYSTEM     0xFF
#define INSTALL_SCT_MAX_BACKUP          0xFF

#define INSTALL_SCT_STARTUP_FILE        L"SctStartup.nsh"

//
// Global variables
//

extern EFI_HANDLE gImageHandle;

//
// External functions
//

EFI_STATUS
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

#endif
