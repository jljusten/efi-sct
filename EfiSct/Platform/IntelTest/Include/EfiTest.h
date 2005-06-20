/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EfiTest.h

Abstract:

  EFI Test master include file. It produces the additional header file
  encapsule format for test.

--*/

#ifndef _EFI_TEST_H_
#define _EFI_TEST_H_

//
// Define macros for including test protocols
//

#define EFI_TEST_STRINGIZE(a)               #a
#define EFI_TEST_PROTOCOL_DEFINITION(a)     \
  EFI_TEST_STRINGIZE(Platform/IntelTest/Protocol/a/a.h)

//
// These should be used to include protocols.  If they are followed,
// intelligent build tools can be created to check dependencies at build
// time.
//
#define EFI_TEST_PROTOCOL_PRODUCER(a)       EFI_TEST_PROTOCOL_DEFINITION(a)
#define EFI_TEST_PROTOCOL_CONSUMER(a)       EFI_TEST_PROTOCOL_DEFINITION(a)

#endif
