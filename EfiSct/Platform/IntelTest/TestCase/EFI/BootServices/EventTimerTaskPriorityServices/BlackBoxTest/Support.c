/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Support.c

Abstract:

  Test Driver of Event and Timer and Task Priority Services

--*/

#include "EventTimerTaskPriorityServicesBBTestMain.h"


VOID
NotifyFunction (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;

  if (Context != NULL) {
    Buffer = Context;

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) Event;
    }
  }

  return;
}


VOID
NotifyFunctionTpl (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;
  EFI_TPL   OldTpl;

  if (Context != NULL) {
    Buffer = Context;

    OldTpl = gtBS->RaiseTPL (EFI_TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) OldTpl;
    }
  }

  return;
}


VOID
NotifyFunctionSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  gtBS->SignalEvent (Event);
  return;
}

VOID
NotifyFunctionNoSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  return;
}
