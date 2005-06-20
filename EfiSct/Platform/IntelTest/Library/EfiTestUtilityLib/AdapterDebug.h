/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  AdapterDebug.h

Abstract:

  Protocol to debug the EDD 3.0 enablement of BIOS option ROMs

--*/

#ifndef _ADAPTER_DEBUG_H
#define _ADAPTER_DEBUG_H

// {82F86881-282B-11d4-BC7D-0080C73C8881}
#define ADAPTER_DEBUG_PROTOCOL \
{ 0x82f86881, 0x282b, 0x11d4, 0xbc, 0x7d, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

//
// This protocol points to the BIOS_LEGACY_DRIVE data structure
//  see edd.h for more details
//

#endif
