/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DecompressBBTestMain.h

Abstract:

  BB test main header file for Decompress protocol

--*/

#ifndef _DECOMPRESSTEST_H
#define _DECOMPRESSTEST_H

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)

#include "DecompressProtocol.h"
#include "guid.h"

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

#define EXAMPLE_TEST_REVISION 0x00010000

//
//TDS 4.1.1
//
EFI_STATUS
GetInfo_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.1.2
//
EFI_STATUS
Decompress_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.1
//
EFI_STATUS
GetInfo_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//TDS 4.2.2
//
EFI_STATUS
Decompress_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
InitializeDecompressProtocolBBTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
DecompressProtocolBBTestUnload (
  IN EFI_HANDLE       ImageHandle
  );

#endif
