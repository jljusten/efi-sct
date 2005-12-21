/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleFileSystemBBTestMain.c

Abstract:

  for EFI Simple File System Protocol and EFI_FILE Protocol Black Box Test

--*/
#include "SimpleFileSystemBBTest.h"

//
// global variable for this test driver's image handle
//
EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  EFI_TPL_APPLICATION,
  EFI_TPL_CALLBACK
};

EFI_HANDLE      mImageHandle;

EFI_DRIVER_ENTRY_POINT(InitializeBBTestSimpleFileSystem)

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_FILE_SYSTEM_TEST_REVISION,
  IHV_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
  L"Testing For Simple File System Protocol and EFI_FILE Protocol",
  L"Total # test cases for the Simple File System Protocol and EFI_FILE Protocol"
};

EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0101,
    L"OpenVolume_Func",
    L"Function Test for OpenVolume",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenVolumeBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0102,
    L"Open_Func",
    L"Function Test for Open",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0103,
    L"Close_Func",
    L"Function Test for Close",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCloseBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0104,
    L"Delete_Func",
    L"Function Test for Delete",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDeleteBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0105,
    L"Read_Func",
    L"Function Test for Read",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReadBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0106,
    L"Write_Func",
    L"Function Test for Write",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0107,
    L"Flush_Func",
    L"Function Test for Flush",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0108,
    L"SetPosition_Func",
    L"Function Test for SetPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetPositionBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0109,
    L"GetPosition_Func",
    L"Function Test for GetPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetPositionBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0110,
    L"GetInfo_Func",
    L"Function Test for GetInfo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetInfoBasicTest
  },
  {
    SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0111,
    L"SetInfo_Func",
    L"Function Test for SetInfo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetInfoBasicTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0201,
    L"Open_Conf",
    L"Conformance Test for Open",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0202,
    L"Delete_Conf",
    L"Conformance Test for Delete",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDeleteConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0203,
    L"Write_Conf",
    L"Conformance Test for Write",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestWriteConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0204,
    L"Flush_Conf",
    L"Conformance Test for Flush",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFlushConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0205,
    L"SetPosition_Conf",
    L"Conformance Test for SetPosition",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetPositionConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0206,
    L"GetPosition_Conf",
    L"Conformance Test for GetPosition",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetPositionConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0207,
    L"GetInfo_Conf",
    L"Conformance Test for GetInfo",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetInfoConformanceTest
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0208,
    L"SetInfo_Conf",
    L"Conformance Test for SetInfo",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetInfoConformanceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0301,
    L"Change Media Test (Manual)",
    L"Extensive Test 1",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest1
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0302,
    L"Remove Media Test (Manual)",
    L"Extensive Test 2",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest2
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0303,
    L"Write Protected Test (Manual)",
    L"Extensive Test 3",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest3
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0304,
    L"Volume Full Test (Manual)",
    L"Extensive Test 4",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSimpleFileSytemExtensiveTest4
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0305,
    L"File Access after File Deleted",
    L"Extensive Test 5",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemExtensiveTest5
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0306,
    L"File Read/Write Stress Test",
    L"Extensive Test 6",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemExtensiveTest6
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0307,
    L"Open_Stress",
    L"Stress test for Open",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemOpenStress
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0308,
    L"GetInfo_Stress",
    L"Stress test for GetInfo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemGetInfoStress
  },
  {
   SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0309,
    L"SetInfo_Stress",
    L"Stress test for SetInfo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSimpleFileSytemSetInfoStress
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
InitializeBBTestSimpleFileSystem (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  InitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSimpleFileSystemUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BBTestSimpleFileSystemUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
