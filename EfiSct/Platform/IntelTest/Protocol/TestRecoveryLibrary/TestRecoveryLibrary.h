/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestRecoveryLibrary.h

Abstract:

  This file defines the EFI Test Recovery Library Protocol.

--*/

#ifndef _EFI_TEST_RECOVERY_LIBRARY_H_
#define _EFI_TEST_RECOVERY_LIBRARY_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"

//
// EFI Test Recovery Library Protocol Definitions
//

#define EFI_TEST_RECOVERY_LIBRARY_GUID      \
  { 0x7fd8c38d, 0x7c5c, 0x42fc, 0xb0, 0x44, 0x3a, 0x83, 0x4a, 0x61, 0x74, 0x76 }

#define EFI_TEST_RECOVERY_LIBRARY_REVISION  0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_TEST_RECOVERY_LIBRARY_PROTOCOL);

//
// EFI Test Recovery Library Protocol API - ReadResetRecord
//
typedef
EFI_STATUS
(EFIAPI *EFI_TRL_READ_RESET_RECORD) (
  IN  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL          *This,
  OUT UINTN                                       *Size,
  OUT VOID                                        *Buffer
  )
/*++

Routine Description:

  Reads the information which is recorded before of system reset. It can
  only be used to transfer the data between system reset in one test case. The
  test management system will clean up all recorded information after a test
  case is completed.

Arguments:

  This          - Test recovery library protocol instance.

  Size          - The number of byte returned in the Buffer.

  Buffer        - The buffer is used to restore the output information. The
                  buffer is allocated by the caller and should be larger than
                  1024 bytes.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Recovery Library Protocol API - WriteResetRecord
//
typedef
EFI_STATUS
(EFIAPI *EFI_TRL_WRITE_RESET_RECORD) (
  IN  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL          *This,
  IN  UINTN                                       Size,
  IN  VOID                                        *Buffer
  )
/*++

Routine Description:

  Writes the information which will be used after system reset. It is also used
  to indicate this system reset is scheduled by the test case in plan. The test
  management system will restart this test case if it finds any recorded
  information. So the test case should clean up the recorded information after
  it is restarted.

Arguments:

  This          - Test recovery library protocol instance.

  Size          - The number of byte to be written.

  Buffer        - The buffer is used to restore the output information. This
                  buffer should not larger than 1024 bytes.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Recovery Library Protocol
//

typedef struct _EFI_TEST_RECOVERY_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TRL_READ_RESET_RECORD             ReadResetRecord;
  EFI_TRL_WRITE_RESET_RECORD            WriteResetRecord;
} EFI_TEST_RECOVERY_LIBRARY_PROTOCOL;

//
// Global ID for EFI Test Recovery Library Protocol
//

extern EFI_GUID gEfiTestRecoveryLibraryGuid;

#endif
