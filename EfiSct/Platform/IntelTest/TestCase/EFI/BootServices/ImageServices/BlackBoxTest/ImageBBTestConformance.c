/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ImageBBTestConformance.c

Abstract:

  for Image Boot Services' Consistency Test

--*/

#include "Misc.h"

/**
 *  @brief Entrypoint for gtBS->LoadImage() Consistency Test.
 *         4 check points will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.1
//
EFI_STATUS
BBTestLoadImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       **ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ParentImageHandle[3];
  CHAR16                               *FileName;
  EFI_DEVICE_PATH_PROTOCOL             *ValidFilePath;
  UINTN                                Index;
  EFI_HANDLE                           ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL             *IrrelevantFilePath;
  EFI_DEVICE_PATH_PROTOCOL             *NonExistentDevicePath;
  UINT8                                *SourceBuffer;
  UINTN                                SourceBufferSize;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  FileName = APPLICATION_IMAGE_1_NAME;
  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             FileName,
             &ValidFilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.1.2.1  LoadImage should not succeed with an invalid ParentImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ParentImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ParentImageHandle[1]);
  ImageTestCreateNewHandle (&ParentImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->LoadImage (
                     FALSE,
                     ParentImageHandle[Index],
                     ValidFilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid001,
                   L"BS.LoadImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ParentImageHandle[1]);
  ImageTestReleaseNewHandle (ParentImageHandle[2]);

  //
  // Checkpoint 2:
  // 3.1.2.2  LoadImage should not succeed with NULL FilePath
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NULL,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid002,
                 L"BS.LoadImage - ConsistencyTestCheckpoint2",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Checkpoint 3:
  // 3.1.2.3  LoadImage should not succeed with an irrelevant FilePath
  //
  ImageTestLocateNonFilePath (&IrrelevantFilePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   IrrelevantFilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid003,
                 L"BS.LoadImage - ConsistencyTestCheckpoint3",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  // Checkpoint 4:
  // 3.1.2.4  LoadImage should not succeed with a non-existent FilePath
  //
  ImageTestCreateNonExistentDevicePath (&NonExistentDevicePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NonExistentDevicePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  gtBS->FreePool (NonExistentDevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid004,
                 L"BS.LoadImage - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  //
  //Create a DevicePath that combined a Media DevicePath and Vendor Devicepath.
  //
  NonExistentDevicePath = NULL;

  ImageTestCreateCombinedNonExistentDevicePath (&NonExistentDevicePath);
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   NonExistentDevicePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  gtBS->FreePool (NonExistentDevicePath);
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid004,
                 L"BS.LoadImage - ConsistencyTestCheckpoint4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );



  //
  // ASSERT in CoreLoadImage (Core\Image.c Line1231),
  // so comments this checkpoint out temporarily until it is fixed.
  //

  //
  // Checkpoint 5:
  // 3.1.2.5  LoadImage should not succeed with NULL ImageHandle
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   ValidFilePath,
                   NULL,
                   0,
                   NULL
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid005,
                 L"BS.LoadImage - ConsistencyTestCheckpoint5",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );


  //
  // Checkpoint 6:
  // 3.1.2.6  LoadImage with SourceSize as 0 it should return EFI_LOAD_ERROR.
  //
  SourceBuffer     = NULL;
  Status = ImageTestCopySimpleFileToMemory (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &SourceBuffer,
             &SourceBufferSize
             );

  if (!EFI_ERROR(Status) && (SourceBuffer != NULL)) {

    SourceBufferSize = 0;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     NULL,
                     SourceBuffer,
                     SourceBufferSize,
                     &ImageHandle
                     );

    if (EFI_LOAD_ERROR == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid010,
                   L"BS.LoadImage - ConsistencyTestCheckpoint6",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    gtBS->FreePool (SourceBuffer);

  } else {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCopySimpleFileToMemory -Error.",
                   L"%a:%d:Status - %r, ImageName - %s",
                   __FILE__,
                   __LINE__,
                   Status,
                   APPLICATION_IMAGE_1_NAME
                   );
  }

  gtBS->FreePool (ValidFilePath);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->StartImage() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.2
//
EFI_STATUS
BBTestStartImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       **ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                ExitDataSize;
  CHAR16                               *ExitData;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.2.2.1  StartImage should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->StartImage (
                     ImageHandle[Index],
                     &ExitDataSize,
                     &ExitData
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid006,
                   L"BS.StartImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}


/**
 *  @brief Entrypoint for gtBS->UnloadImage() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.3
//
EFI_STATUS
BBTestUnloadImageConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       **ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                Index;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.3.2.1  UnloadImage should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->UnloadImage (
                     ImageHandle[Index]
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid007,
                   L"BS.UnloadImage - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->Exit() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.4
//
EFI_STATUS
BBTestExitConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       **ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_HANDLE                           ImageHandle[3];
  UINTN                                Index;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.4.2.1  Exit should not succeed with an invalid ImageHandle
  //
  //
  // invalid handle could be: NULL; invalid handle; not a image handle
  //
  ImageHandle[0] = NULL;
  ImageTestCreateInvalidHandle (&ImageHandle[1]);
  ImageTestCreateNewHandle (&ImageHandle[2]);

  for (Index = 0; Index < 3; Index++) {

    Status = gtBS->Exit (
                     ImageHandle[Index],
                     EFI_SUCCESS,
                     0,
                     NULL
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConsistencyTestAssertionGuid008,
                   L"BS.Exit - ConsistencyTestCheckpoint1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }
  //
  // restore environment
  //
  ImageTestReleaseInvalidHandle (ImageHandle[1]);
  ImageTestReleaseNewHandle (ImageHandle[2]);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
  }
  return Status;
}

/**
 *  @brief Entrypoint for gtBS->ExitBootServices() Consistency Test.
 *         1 check point will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 3.5
//
EFI_STATUS
BBTestExitBootServicesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       **ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                MapKey;

  UINTN                                Numbers;

  //
  // Init
  //
  StandardLib = NULL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - check environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 3.5.2.1  ExitBootServices should not succeed with an invalid MapKey
  //
  //
  // the steps to make a invalid MapKey could be:
  //   1) call BS->GetMemoryMap() to retrieve the correct MapKey
  //   2) add a randomn value to the correct MapKey.
  //
  Status = ImageTestRetrieveCurrentMapKey (&MapKey);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" BS.GetMemoryMap - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  MapKey += MapKey;

  Status = gtBS->ExitBootServices (
                   mImageHandle,
                   MapKey
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConsistencyTestAssertionGuid009,
                 L"BS.ExitBootServices - ConsistencyTestCheckpoint1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Numbers - %d",
                   __FILE__,
                   __LINE__,
                   Status,
                   Numbers
                   );
  }
  return EFI_SUCCESS;
}

