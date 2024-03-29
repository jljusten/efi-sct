/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:
  TimerInterrupt.c

Abstract:
  Ia32 Source file for Mask/Unmask TimerInterrupt.

--*/

#include "UsbHcTest.h"

VOID MaskTimerInterrupt()
{
  __asm mov al, 0x0ff
  __asm out 0x21, al

  return;
}

VOID UnmaskTimerInterrupt()
{
  __asm mov al, 0x0fe
  __asm out 0x21, al

  return;
}