/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  lock.c

Abstract:

  Implements FLOCK

--*/

#include "lib.h"


VOID
InitializeLock (
  IN OUT FLOCK    *Lock,
  IN EFI_TPL      Priority
  )
/*++

Routine Description:

  Initialize a basic mutual exclusion lock.   Each lock
  provides mutual exclusion access at it's task priority
  level.  Since there is no-premption (at any TPL) or
  multiprocessor support, acquiring the lock only consists
  of raising to the locks TPL.

  Note on a debug build the lock is acquired and released
  to help ensure proper usage.

Arguments:

  Lock        - The FLOCK structure to initialize

  Priority    - The task priority level of the lock


Returns:

  An initialized F Lock structure.

--*/
{
  Lock->Tpl = Priority;
  Lock->OwnerTpl = 0;
  Lock->Lock = 0;
}


VOID
AcquireLock (
  IN FLOCK    *Lock
  )
/*++

Routine Description:

  Raising to the task priority level of the mutual exclusion
  lock, and then acquires ownership of the lock.

Arguments:

  Lock        - The lock to acquire

Returns:

  Lock owned

--*/
{
  if (tBS) {
    if (tBS->RaiseTPL != NULL) {
      Lock->OwnerTpl = tBS->RaiseTPL(Lock->Tpl);
    }
  } else {
    if (LibRuntimeRaiseTPL != NULL) {
      Lock->OwnerTpl = LibRuntimeRaiseTPL(Lock->Tpl);
    }
  }
  Lock->Lock += 1;
  ASSERT (Lock->Lock == 1);
}


VOID
ReleaseLock (
  IN FLOCK    *Lock
  )
/*++

Routine Description:

  Releases ownership of the mutual exclusion lock, and
  restores the previous task priority level.

Arguments:

  Lock        - The lock to release

Returns:

  Lock unowned

--*/
{
  EFI_TPL     Tpl;

  Tpl = Lock->OwnerTpl;
  ASSERT(Lock->Lock == 1);
  Lock->Lock -= 1;
  if (tBS) {
    if (tBS->RestoreTPL != NULL) {
      tBS->RestoreTPL (Tpl);
    }
  } else {
    if (LibRuntimeRestoreTPL != NULL) {
      LibRuntimeRestoreTPL(Tpl);
    }
  }
}
