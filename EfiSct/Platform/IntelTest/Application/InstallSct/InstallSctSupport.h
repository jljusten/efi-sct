/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  InstallSctSupport.h

Abstract:

  This file provides the support services for the EFI SCT installation.

--*/

#ifndef _EFI_INSTALL_SCT_SUPPORT_H_
#define _EFI_INSTALL_SCT_SUPPORT_H_

#include "Efi.h"

//
// External functions
//

EFI_STATUS
GetFreeSpace (
  IN CHAR16             *FsName,
  OUT UINT64            *FreeSpace
  );

EFI_STATUS
DirFileExist (
  IN CHAR16             *Name,
  OUT BOOLEAN           *Exist
  );

EFI_STATUS
CreateDir (
  IN CHAR16             *DirName
  );

EFI_STATUS
RemoveDirFile (
  IN CHAR16             *Name
  );

EFI_STATUS
BackupDirFile (
  IN CHAR16             *Name
  );

EFI_STATUS
CopyDirFile (
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName,
  IN BOOLEAN            Recursive
  );

#endif
