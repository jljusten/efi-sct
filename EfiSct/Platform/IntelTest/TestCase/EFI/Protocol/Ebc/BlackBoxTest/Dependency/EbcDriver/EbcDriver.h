/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EbcDriver.h

Abstract:
  Data definition for Ebc Driver

--*/

#ifndef _EBC_DRIVER_H
#define _EBC_DRIVER_H

#include "Efi.h"

//
// Driver Consumed Protocol Prototypes
//
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#define EBC_DRIVER_TEST_PROTOCOL \
  { 0xf01547c5, 0x6f06, 0x4c6d, 0xb6, 0x10, 0x88, 0x91, 0xe7, 0x74, 0x36, 0x45 }


#endif