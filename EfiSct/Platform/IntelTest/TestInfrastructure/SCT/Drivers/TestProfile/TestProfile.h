/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestProfile.h

Abstract:

  Driver to publish the Test Profile Library Protocol.

--*/

#ifndef _EFI_TEST_PROFILE_H_
#define _EFI_TEST_PROFILE_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_TEST_PROTOCOL_DEFINITION (TSLInit)
#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

//
// Private Data definition for TestProfileLibrary protocol
//
#define TEST_PROFILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('A','D','V','L')

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         TestProfile;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FilePath;
} TEST_PROFILE_PRIVATE_DATA;

#define TEST_PROFILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, TEST_PROFILE_PRIVATE_DATA, TestProfile, TEST_PROFILE_PRIVATE_DATA_SIGNATURE)

//
// Private Data definition for EFI_INI_FILE interface
//
#define EFI_INI_FILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('I','N','I','F')

#define MAX_STRING_LEN      250
#define MAX_LINE_LEN        512

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (INI);
EFI_FORWARD_DECLARATION (COMMENTLINE);

typedef struct _INI {
  UINT32                          commentNo;
  CHAR8                           *ptrSection;
  CHAR8                           *ptrEntry;
  CHAR8                           *ptrValue;
  INI                             *ptrNext;
} INI;


typedef struct _COMMENTLINE {
  UINT32                          commentNo;
  CHAR8                           *ptrComment;
  COMMENTLINE                     *ptrNext;
} COMMENTLINE;

typedef struct {
  UINT32                          Signature;
  EFI_INI_FILE                    Handle;
  EFI_DEVICE_PATH_PROTOCOL        *DevPath;
  CHAR16                          *FileName;
  INI                             *Head;
  INI                             *Tail;
  COMMENTLINE                     *CommentLineHead;
  BOOLEAN                         isUnicode;
  BOOLEAN                         Modified;
} EFI_INI_FILE_PRIVATE_DATA;

#define EFI_INI_FILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, EFI_INI_FILE_PRIVATE_DATA, Handle, EFI_INI_FILE_PRIVATE_DATA_SIGNATURE)

#endif