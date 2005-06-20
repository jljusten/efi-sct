/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Debug.c

Abstract:

  Support for Debug primatives.

--*/

#include "lib.h"

EFI_DEBUG_ASSERT_PROTOCOL *mDebugAssert = NULL;

EFI_STATUS
EfiDebugAssertInit (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_GUID    DebugAssertProtocolGuid = EFI_DEBUG_ASSERT_PROTOCOL_GUID;

  Status = LibLocateProtocol (&DebugAssertProtocolGuid, (VOID **)&mDebugAssert);
  return Status;
}


VOID
EfiDebugAssert (
  IN CHAR8    *FileName,
  IN INTN     LineNumber,
  IN CHAR8    *Description
  )
/*++

Routine Description:

  Worker function for ASSERT(). If Error Logging hub is loaded log ASSERT
  information. If Error Logging hub is not loaded BREAKPOINT().

Arguments:

  FileName    - File name of failing routine.

  LineNumber  - Line number of failing ASSERT().

  Description - Descritption, usally the assertion,

Returns:

  None

--*/
{
  if (mDebugAssert != NULL) {
    mDebugAssert->Assert (mDebugAssert, FileName, LineNumber, Description);
  }
}


VOID
EfiDebugPrint (
  IN  UINTN   ErrorLevel,
  IN  CHAR8   *Format,
  ...
  )
/*++

Routine Description:

  Worker function for DEBUG(). If Error Logging hub is loaded log ASSERT
  information. If Error Logging hub is not loaded do nothing.

Arguments:

  ErrorLevel - If error level is set do the debug print.

  Format     - String to use for the print, followed by Print arguments.

Returns:

  None

--*/
{
  VA_LIST Marker;

  VA_START (Marker, Format);
  if (mDebugAssert != NULL) {
    mDebugAssert->Print (mDebugAssert, ErrorLevel, Format, Marker);
  }
  VA_END (Marker);
}

