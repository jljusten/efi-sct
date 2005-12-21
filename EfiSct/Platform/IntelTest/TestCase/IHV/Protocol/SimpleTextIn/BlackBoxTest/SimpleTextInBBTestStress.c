/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SimpleTextInBBTestStress.c

Abstract:

  Extensive Test Cases of Simple Input Protocol

--*/


#include "SimpleTextInBBTestMain.h"


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke/WaitForKey() Entensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.1
//
EFI_STATUS
BBTestReadKeyStrokeManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_INPUT_KEY                        Key;
  CHAR16                               KeyBuffer[MAX_KEY_BUFFER_SIZE];

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINTN                                Index;

  //
  // Verify whether it is one of IHV interfaces
  //
  if (! IsIhvInterface (ClientInterface, SupportHandle)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  SimpleIn = (EFI_SIMPLE_TEXT_IN_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_In_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextIn (SimpleIn, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = DevicePathToStr(DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       __LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/TxtIn"
                   );
  }

  //
  // wait for times
  //
  Print (L"\r\nReadKeyStroke Stress Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.3.2.1
  // ReadKeyStroke()
  //
    Status = SimpleIn->Reset (SimpleIn,TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset with ExtendedVeirification as TRUE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }
  Print (L"\r\nPlease input some displayabed characters in 5 seconds\r\n");

  gtBS->Stall (5000000);

  //
  // Assume user has input some key, go on verification
  // Read all key
  //
  Index=0;
  do {
    Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
    if (Status == EFI_SUCCESS) {
      KeyBuffer[Index++] = Key.UnicodeChar;
    }

  } while (Status == EFI_SUCCESS && Index < MAX_KEY_BUFFER_SIZE);

  //
  // Echo the input keys
  //
  if (Status != EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextInExtensiveTestAssertionGuid001,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() when no key input",
                   L"%a:%d, Status = %r, Expected = %r",
                   __FILE__,
                   __LINE__,
                   Status,
                   EFI_NOT_READY
                   );
  }

  KeyBuffer[Index] = 0;

  Print (L"The keys input are:%s", KeyBuffer);

  //
  // Prompt for user judge
  //
  if (AutoJudge (5,TRUE,L"\r\nEcho correct?\r\n") == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInExtensiveTestAssertionGuid002,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input, user's view",
                 L"%a:%d",
                 __FILE__,
                 __LINE__
                 );

  return EFI_SUCCESS;
}


