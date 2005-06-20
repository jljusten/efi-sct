/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestLoggingLibrary.h

Abstract:

  This file defines the EFI Test Logging Library Protocol.

--*/

#ifndef _EFI_TEST_LOGGING_LIBRARY_H_
#define _EFI_TEST_LOGGING_LIBRARY_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)

//
// EFI Test Logging Library Protocol Definitions
//

#define EFI_TEST_LOGGING_LIBRARY_GUID       \
  { 0x1ab99b08, 0x58c6, 0x40dd, 0x86, 0xd8, 0xe8, 0xff, 0x2f, 0xa8, 0x4e, 0x4d }

#define EFI_TEST_LOGGING_LIBRARY_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_TEST_LOGGING_LIBRARY_PROTOCOL);

//
// EFI Test Logging Library Protocol API - Line
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_LINE) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  UINT32                                      Length
  )
/*++

Routine Description:

  Writes a line into the log file. Generally it is for separating the different
  test results or message.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - EnterFunction
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_ENTER_FUNCTION) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  CHAR16                                      *FunctionName,
  IN  CHAR16                                      *Format,
  ...
  )
/*++

Routine Description:

  Records the tracing message of entering a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.

  FunctionName  - Name of enter function.

  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - ExitFunction
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_EXIT_FUNCTION) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  CHAR16                                      *FunctionName,
  IN  CHAR16                                      *Format,
  ...
  )
/*++

Routine Description:

  Records the tracing message of exiting a function. This message will only be
  recorded when the test is run in EXHAUSTIVE mode.

Argument:

  This          - Test logging library protocol instance.

  FunctionName  - Name of exit function.

  Message       - Format string for the detail test information.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol API - DumpMask
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_DUMP_MASK) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  UINT32                                      BitMask,
  IN  UINT32                                      Length
  )
/*++

Routine Description:

  Dump a bit-map mask.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

  BitMask       - Bit Mask to be dumpped.

  Length        - The number of bits to be dumpped.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

#define EFI_DUMP_HEX    0x01
#define EFI_DUMP_ASCII  0x02

//
// EFI Test Logging Library Protocol API - DumpBuf
//
typedef
EFI_STATUS
(EFIAPI *EFI_TLL_DUMP_BUF) (
  IN  EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *This,
  IN  EFI_VERBOSE_LEVEL                           VerboseLevel,
  IN  CHAR16                                      *Buffer,
  IN  UINT32                                      Length,
  IN  UINT32                                      Flags
  )
/*++

Routine Description:

  Dump a buffer in Hex, ASCII, or both styles.

Argument:

  This          - Test logging library protocol instance.

  VerboseLevel  - Minimal verbose level to record this message. For example,
                  EFI_VERBOSE_LEVEL_QUIET means this message should be recorded
                  even the test is run in QUIET mode. On the contrary,
                  EFI_VERBOSE_LEVEL_EXHAUSTIVE means this message will only be
                  recorded when the test is run in EXHAUSTIVE mode.

  Buffer        - Buffer to be dumpped.

  Length        - The number of bytes to be dumpped.

  Flags         - Dumpping format. HEX, ASCII, or BOTH.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Logging Library Protocol
//

typedef struct _EFI_TEST_LOGGING_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TLL_LINE                          Line;
  EFI_TLL_ENTER_FUNCTION                EnterFunction;
  EFI_TLL_EXIT_FUNCTION                 ExitFunction;
  EFI_TLL_DUMP_MASK                     DumpMask;
  EFI_TLL_DUMP_BUF                      DumpBuf;
} EFI_TEST_LOGGING_LIBRARY_PROTOCOL;

//
// Global ID for EFI Test Logging Library Protocol
//

extern EFI_GUID gEfiTestLoggingLibraryGuid;

#endif
