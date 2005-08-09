/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestProfileLibrary.h

Abstract:

  This file defines the EFI Test Profile Library Protocol.

--*/

#ifndef _EFI_TEST_PROFILE_LIBRARY_H_
#define _EFI_TEST_PROFILE_LIBRARY_H_

//
// Includes
//

#include "Efi.h"
#include "EfiTest.h"
#include EFI_PROTOCOL_DEFINITION (DevicePath)

//
// EFI Test Profile Library Protocol Definitions
//

#define EFI_TEST_PROFILE_LIBRARY_GUID       \
  { 0x832c9023, 0x8e67, 0x453f, 0x83, 0xea, 0xdf, 0x71, 0x05, 0xfa, 0x74, 0x66 }

#define EFI_TEST_PROFILE_LIBRARY_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

EFI_FORWARD_DECLARATION (EFI_INI_FILE);
EFI_FORWARD_DECLARATION (EFI_TEST_PROFILE_LIBRARY_PROTOCOL);

//
// EFI INI File API - Flush
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_FLUSH) (
  IN  EFI_INI_FILE                      *This
  )
/*++

Routine Description:

  Flushes all modified data associated with the INI file to the storage device.
  Remember to invoke this function before of system reset if some modified data
  was not flushed.

Arguments:

  This          - EFI_INI_FILE protocol instance.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetString
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETSTRING) (
  IN     EFI_INI_FILE                   *This,
  IN     CHAR16                         *Section,
  IN     CHAR16                         *Entry,
     OUT CHAR16                         *String,
  IN OUT UINT32                         *MaxLength
  )
/*++

Routine Description:

  Reads a Unicode string from the specific section and entry in the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string which is read.

  MaxLength     - On input, the length of the Unicode string. On output, the
                  length of string returned in String.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - SetString
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_SETSTRING) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section,
  IN  CHAR16                            *Entry,
  IN  CHAR16                            *String
  )
/*++

Routine Description:

  Writes a Unicode string to the specific section and entry in the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - RmSection
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_RMSECTION) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section
  )
/*++

Routine Description:

  Removes a section from the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetStringByOrder
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETSTRING_BYORDER) (
  IN     EFI_INI_FILE                   *This,
  IN     UINT32                         Order,
  IN     CHAR16                         *Section,
  IN     CHAR16                         *Entry,
     OUT CHAR16                         *String,
  IN OUT UINT32                         *MaxLength
  )
/*++

Routine Description:

  Reads a Unicode string from the specific section and entry in the INI file. It
  can be used to deal with more than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be read. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string which is read.

  MaxLength     - On input, the length of the Unicode string. On output, the
                  length of string returned in String.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - SetStringByOrder
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_SETSTRING_BYORDER) (
  IN  EFI_INI_FILE                      *This,
  IN  UINT32                            Order,
  IN  CHAR16                            *Section,
  IN  CHAR16                            *Entry,
  IN  CHAR16                            *String
  )
/*++

Routine Description:

  Writes a Unicode string to the specific section and entry in the INI file. It
  can be used to deal with more than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be written. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - RmSectionByOrder
typedef
EFI_STATUS
(EFIAPI *EFI_INI_RMSECTION_BYORDER) (
  IN  EFI_INI_FILE                      *This,
  IN  UINT32                            Order,
  IN  CHAR16                            *Section
  )
/*++

Routine Description:

  Removes a section from the INI file. It can be used to deal with more than
  one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be removed. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetOrderNum
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETORDERNUM) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section,
  OUT UINT32                            *OrderNum
  )
/*++

Routine Description:

  Gets the number of sections in the input name. It is used when there are more
  than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  OrderNum      - The number of sections with this section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File
//

typedef struct _EFI_INI_FILE {
  UINT64                                Revision;
  EFI_INI_GETSTRING                     GetString;
  EFI_INI_SETSTRING                     SetString;
  EFI_INI_RMSECTION                     RmSection;
  EFI_INI_GETSTRING_BYORDER             GetStringByOrder;
  EFI_INI_SETSTRING_BYORDER             SetStringByOrder;
  EFI_INI_RMSECTION_BYORDER             RmSectionByOrder;
  EFI_INI_GETORDERNUM                   GetOrderNum;
  EFI_INI_FLUSH                         Flush;
} EFI_INI_FILE, *EFI_INI_FILE_HANDLE;

//
// EFI Test Profile Library Protocol API - IniOpen
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_OPEN) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  OUT EFI_INI_FILE                              **FileHandle
  )
/*++

Routine Description:

  Opens an INI file.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the file to be opened.

  FileName      - The name of the file to be opened.

  FileHandle    - The pointer to the opened file handle.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - IniCreate
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_CREATE) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  OUT EFI_INI_FILE                              **FileHandle
  )
/*++

Routine Description:

  Creates an INI file.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the file to be created.

  FileName      - The name of the file to be created.

  FileHandle    - The pointer to the opened file handle.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - IniClose
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_CLOSE) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_INI_FILE                              *FileHandle
  )
/*++

Routine Description:

  Closes an INI file.

Arguments:

  This          - Test profile library protocol instance.

  FileHandle    - The file handle to be closed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - GetSystemDevicePath
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_GET_SYSTEM_DEVICE_PATH) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  OUT EFI_DEVICE_PATH_PROTOCOL                  **DevicePath,
  OUT CHAR16                                    **FilePath
  )
/*++

Routine Description:

  Gets the test system device path. With this function, the test case needs not
  to care about the INI file's absolute path or the current working directory.
  The returned DevicePath and FilePath are the copy of system data. It is
  caller's responsibility to free them.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the test management system.

  FilePath      - The file path of the test management system.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - SetSystemDevicePath
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_SET_SYSTEM_DEVICE_PATH) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FilePath
  )
/*++

Routine Description:

  Sets the test system device path. This function should only be called by
  the test management system. Any test cases should not call this function to
  change the test system device path.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the test management system.

  FilePath      - The file path of the test management system.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol
//

typedef struct _EFI_TEST_PROFILE_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TPL_INI_OPEN                      EfiIniOpen;
  EFI_TPL_INI_CREATE                    EfiIniCreate;
  EFI_TPL_INI_CLOSE                     EfiIniClose;
  EFI_TPL_GET_SYSTEM_DEVICE_PATH        EfiGetSystemDevicePath;
  EFI_TPL_SET_SYSTEM_DEVICE_PATH        EfiSetSystemDevicePath;
} EFI_TEST_PROFILE_LIBRARY_PROTOCOL;

//
// Global ID for EFI Test Profile Library Protocol
//

extern EFI_GUID gEfiTestProfileLibraryGuid;

#endif
