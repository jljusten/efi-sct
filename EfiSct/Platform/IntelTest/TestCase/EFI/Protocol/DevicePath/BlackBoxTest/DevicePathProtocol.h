/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DevicePathProtocol.h

Abstract:

--*/


#ifndef _DEVICE_PATH_FOR_TEST_H_
#define _DEVICE_PATH_FOR_TEST_H_

#include "EfiApi.h"

//
// Device Path protocol
//
#define EFI_DEVICE_PATH_PROTOCOL_GUID  \
  { 0x9576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#ifndef EFI_END_ENTIRE_DEVICE_PATH
#define EFI_END_ENTIRE_DEVICE_PATH          0xff
#endif

#ifndef EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE
#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE  0xff
#endif

#ifndef EFI_END_INSTANCE_DEVICE_PATH
#define EFI_END_INSTANCE_DEVICE_PATH        0x01
#endif

#ifndef EFI_END_DEVICE_PATH_LENGTH
#define EFI_END_DEVICE_PATH_LENGTH          (sizeof(EFI_DEVICE_PATH_PROTOCOL))
#endif

#ifndef EfiDevicePathNodeLength
#define EfiDevicePathNodeLength(a)  (((a)->Length[0]) | ((a)->Length[1] << 8))
#endif

#ifndef EfiNextDevicePathNode
#define EfiNextDevicePathNode(a)    ((EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + \
                                      EfiDevicePathNodeLength(a)))
#endif

#ifndef EfiDevicePathType
#define EfiDevicePathType(a)          ( ((a)->Type) & 0x7f )
#endif

#ifndef EfiIsDevicePathEndType
#define EfiIsDevicePathEndType(a)     (EfiDevicePathType(a) == 0x7f)
#endif

#ifndef EfiIsDevicePathEndSubType
#define EfiIsDevicePathEndSubType(a)          ((a)->SubType == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#endif

#ifndef EfiIsDevicePathEndInstanceSubType
#define EfiIsDevicePathEndInstanceSubType(a)  ((a)->SubType == EFI_END_INSTANCE_DEVICE_PATH)
#endif

#ifndef EfiIsDevicePathEnd
#define EfiIsDevicePathEnd(a)         ( EfiIsDevicePathEndType(a) && \
                                        EfiIsDevicePathEndSubType(a) )
#endif

#ifndef EfiIsDevicePathEndInstance
#define EfiIsDevicePathEndInstance(a) ( EfiIsDevicePathEndType(a) && \
                                        EfiIsDevicePathEndInstanceSubType(a) )
#endif

extern EFI_GUID gEfiDevicePathProtocolGuid;

#endif /* _DEVICE_PATH_FOR_TEST_H_ */

