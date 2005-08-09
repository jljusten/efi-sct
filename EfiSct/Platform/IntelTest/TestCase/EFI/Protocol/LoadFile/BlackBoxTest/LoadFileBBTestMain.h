/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  LoadFileBBTestMain.h

Abstract:

  Test Driver of LoadFile Protocol

--*/

#ifndef __EFI_LOAD_FILE_TEST_H__
#define __EFI_LOAD_FILE_TEST_H__


#include "Efi.h"
#include "Guid.h"
#include "EfiTest.h"
#include "EfiTypes.h"

#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION(DebugAssert)

#include "EfiTestUtilityLib.h"
#include "EfiDriverLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"

#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

#define LOAD_FILE_TEST_REVISION 0x00010000

#define LOAD_FILE_FUNCTION_TEST_GUID \
  {0x31248834, 0xca1b, 0x4004, 0xab, 0x7e, 0x39, 0xea, 0x5f, 0x2, 0x46, 0xe7}

EFI_STATUS
InitializeLoadFileTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
UnloadLoadFileTest (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestLoadFileFunctionTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

VOID
LoadFileTestWaitForAnyInput (
  );

#define SAMPLE_BOOT_FILE_SIZE 27
#endif
