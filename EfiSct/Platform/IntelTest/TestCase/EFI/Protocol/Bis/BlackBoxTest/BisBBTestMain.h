/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BisBBTestMain.h

Abstract:

  BB test header file of Bis Protocol

--*/


#ifndef _BOOT_INTEGRITY_SERVICES_H_
#define _BOOT_INTEGRITY_SERVICES_H_

#include "Efi.h"
#include "guid.h"
#include "EfiTestLib.h"
#include "BisProtocol.h"
#include "EfiTestUtilityLib.h"
#include "EfiDriverLib.h"

#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)

#define BIS_TEST_REVISION 0x00010000

//
// file names definition
//
#define DUMP_CERTIFICATE_FILE_NAME                L"Certificate.dump"
#define DUMP_TOKEN_FILE_NAME                      L"Token.dump"
#define CREDENTIAL_FILE_NAME                      L"Credential"
#define DATA_FILE_NAME                            L"Dataobject"
#define CERTIFICATE_FILE_NAME                     L"Certificate"
#define SECTION_NAME                              "TestObject"

//
// Prototypes of BB Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Internal Functions
//
EFI_STATUS
ReadFloppyFile (
  IN CHAR16       *FileName,
  OUT UINT32      *Length,
  OUT VOID        **Buffer
  );

EFI_STATUS
WriteFloppyFile (
  IN CHAR16      *FileName,
  IN OUT UINT32  Length,
  IN VOID        *Buffer
  );

VOID
PressAnyKey ();

BOOLEAN
PressYes ();

CHAR16 *
AlgToStr (
  BIS_ALG_ID      AlgId
);

//
// Entry GUIDs
//

#define BIS_MANUAL_TEST_GUID \
  { 0x26f4f004, 0x3616, 0x455e, 0xb1, 0x4a, 0xce, 0x74, 0x38, 0x6d, 0x4c, 0xa5 }

#endif
