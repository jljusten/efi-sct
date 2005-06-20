/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  ExecuteSupport.c

Abstract:

  This file provides the support services for test execution.

--*/

#include "Sct.h"
#include "ExecuteSupport.h"

//
// Internal functions declarations
//

EFI_STATUS
ConvertFilePath (
  IN OUT CHAR16                   *FilePath
  );

EFI_STATUS
ConvertFileName (
  IN OUT CHAR16                   *FileName
  );


//
// External functions implementation
//

EFI_STATUS
InitializeExecuteInfo (
  IN EFI_SCT_TEST_CASE            *TestCase,
  OUT EFI_SCT_EXECUTE_INFO        *ExecuteInfo
  )
/*++

Routine Description:

  Initialize the execute information.

Arguments:

  TestCase      - Pointer to the test case.
  ExecuteInfo   - Pointer to the execute information.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  EFI_GUID    *CategoryGuid;

  //
  // Check parameters
  //
  if ((TestCase == NULL) || (ExecuteInfo == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the items of execute information
  //
  ExecuteInfo->TestCase     = TestCase;

  ExecuteInfo->Category     = NULL;
  ExecuteInfo->TestFile     = NULL;

  ExecuteInfo->TestProtocol = NULL;
  ExecuteInfo->TestEntry    = NULL;

  ExecuteInfo->State        = EFI_SCT_LOG_STATE_UNKNOWN;

  ExecuteInfo->Index        = 0;
  ExecuteInfo->Iteration    = 0;
  ExecuteInfo->Passes       = 0;
  ExecuteInfo->Warnings     = 0;
  ExecuteInfo->Failures     = 0;

  //
  // Search the related test file
  //
  Status = FindTestFileByCaseGuid (
             &TestCase->Guid,
             &ExecuteInfo->TestFile,
             &ExecuteInfo->TestProtocol,
             &ExecuteInfo->TestEntry
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find test file by case GUID - %r", Status));;
    return Status;
  }

  //
  // Get the category GUID from different kinds of test files
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    CategoryGuid = &((EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    CategoryGuid = &((EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    CategoryGuid = &((EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol)->CategoryGuid;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Find the related category data
  //
  Status = FindCategoryByGuid (
             CategoryGuid,
             &ExecuteInfo->Category
             );
  if (EFI_ERROR (Status)) {
    //
    // If the category data doesn't exist, use the empty setting
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Find category by GUID - %r", Status));
    ExecuteInfo->Category = NULL;;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetFileMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FilePath,
  OUT CHAR16                      **MetaName
  )
/*++

Routine Description:

  Get the file path and the meta file name. The format of meta name will be
  "Name_%s_%s_GUID.%s". (Here, "%s" stands for the real string "%s".)

  Notice: If you need to change the format of this meta name, you should also
  review the code of each caller. The caller will generate the real file name
  based on the meta name returned by this function.

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FilePath      - The path of log files.
  MetaName      - The meta name of log files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_GUID  *CategoryGuid;
  CHAR16    CategoryGuidStr[40];
  EFI_GUID  *EntryGuid;
  CHAR16    EntryGuidStr[40];
  CHAR16    *EntryName;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FilePath == NULL) || (MetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the GUID and name of the test entry
  //
  switch (ExecuteInfo->TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    CategoryGuid = &((EFI_BB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_BB_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    CategoryGuid = &((EFI_WB_TEST_PROTOCOL *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_WB_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    CategoryGuid = &((EFI_AP_TEST_INTERFACE *) ExecuteInfo->TestProtocol)->CategoryGuid;
    SctGuidToStr (CategoryGuid, CategoryGuidStr);

    EntryGuid = &((EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry)->EntryId;
    SctGuidToStr (EntryGuid, EntryGuidStr);

    EntryName = ((EFI_AP_TEST_ENTRY *) ExecuteInfo->TestEntry)->Name;
    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Create the file path
  //
  if (ExecuteInfo->Category == NULL) {
    *FilePath = PoolPrint (
                  L"%s\\%s\\Unknown\\%s",
                  gFT->FilePath,
                  EFI_SCT_PATH_LOG,
                  CategoryGuidStr
                  );
  } else {
    *FilePath = PoolPrint (
                  L"%s\\%s\\%s",
                  gFT->FilePath,
                  EFI_SCT_PATH_LOG,
                  ExecuteInfo->Category->Name
                  );
  }

  if (*FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  ConvertFilePath (*FilePath);

  //
  // Create the meta file name
  //
  *MetaName = PoolPrint (
                L"%s_%s_%s_%s.%s",
                EntryName,
                L"%s",              // Index
                L"%s",              // Iteration
                EntryGuidStr,
                L"%s"               // Extension
                );
  if (*MetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (*FilePath);
    return EFI_OUT_OF_RESOURCES;
  }

  ConvertFileName (*MetaName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  )
/*++

Routine Description:

  Get the full meta name of log files. The format of full meta name will be
  "Path\Name_%d_%d_GUID.%s". (Here, "%d" stands for the real string "%d".)

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FullMetaName  - Full meta name of log files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;
  CHAR16      *MetaName;
  CHAR16      *TempName;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FullMetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the file meta name
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta file name to number file name
  //
  TempName = PoolPrint (MetaName, L"%d", L"%d", L"%s");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (FilePath);
    BS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the full meta name
  //
  *FullMetaName = PoolPrint (L"%s\\%s", FilePath, TempName);
  if (*FullMetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (FilePath);
    BS->FreePool (MetaName);
    BS->FreePool (TempName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  BS->FreePool (FilePath);
  BS->FreePool (MetaName);
  BS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
GetKeyFileFullMetaName (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo,
  OUT CHAR16                      **FullMetaName
  )
/*++

Routine Description:

  Get the full meta name of key files. The format of full meta name will be
  "Path\Name_%d_%d_GUID.ekl". (Here, "%d" stands for the real string "%d".)

Arguments:

  ExecuteInfo   - Pointer to the execute information.
  FullMetaName  - Full meta name of key files.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FilePath;
  CHAR16      *MetaName;
  CHAR16      *TempName;

  //
  // Check parameters
  //
  if ((ExecuteInfo == NULL) || (FullMetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Get the file meta name
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Get file meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta file name to number file name
  //
  TempName = PoolPrint (MetaName, L"%d", L"%d", L"ekl");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (FilePath);
    BS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the full meta name
  //
  *FullMetaName = PoolPrint (L"%s\\%s", FilePath, TempName);
  if (*FullMetaName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"PoolPrint: Out of resources"));
    BS->FreePool (FilePath);
    BS->FreePool (MetaName);
    BS->FreePool (TempName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Free resources
  //
  BS->FreePool (FilePath);
  BS->FreePool (MetaName);
  BS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
ConvertFilePath (
  IN OUT CHAR16                   *FilePath
  )
/*++

Routine Description:

  Convert the illegal characters (* ? < > , ; : " = |) of file path to '_'.

--*/
{
  UINTN       Index;
  UINTN       SubIndex;
  CHAR16      *IllegalChar = L"*?<>,;:\"=|";

  //
  // Convert the invalid characters to '_'
  //
  for (Index = 0; FilePath[Index] != L'\0'; Index ++) {
    for (SubIndex = 0; IllegalChar[SubIndex] != L'\0'; SubIndex ++) {
      if (FilePath[Index] == IllegalChar[SubIndex]) {
        FilePath[Index] = L'_';
        break;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ConvertFileName (
  IN OUT CHAR16                   *FileName
  )
/*++

Routine Description:

  Convert the illegal characters (/ * ? < > , ; : " \ = |) of file name to '_'.

--*/
{
  UINTN       Index;
  UINTN       SubIndex;
  CHAR16      *IllegalChar = L"/*?<>,;:\"\\=|";

  //
  // Convert the invalid characters to '_'
  //
  for (Index = 0; FileName[Index] != L'\0'; Index ++) {
    for (SubIndex = 0; IllegalChar[SubIndex] != L'\0'; SubIndex ++) {
      if (FileName[Index] == IllegalChar[SubIndex]) {
        FileName[Index] = L'_';
        break;
      }
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
