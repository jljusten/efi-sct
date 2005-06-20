/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestNode.c

Abstract:

  This file provides the services to manage the test nodes.

  Test Node is the basic test element in the user interface of EFI SCT. It can
  be used to describe the test category information and test case information.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
InsertEntryListToTestNode (
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *EntryList,
  OUT EFI_SCT_TEST_NODE           *RootNode
  );

EFI_STATUS
CreateSingleTestNode (
  OUT EFI_SCT_TEST_NODE           **TestNode
  );

EFI_STATUS
FreeSingleTestNode (
  IN EFI_SCT_TEST_NODE            *TestNode
  );

EFI_STATUS
AddRootTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_GUID                     *Guid,
  IN OUT EFI_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **RootNode
  );

EFI_STATUS
AddTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_SCT_TEST_NODE_TYPE       Type,
  IN EFI_GUID                     *Guid,
  IN OUT EFI_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  );

EFI_STATUS
FindTestNodeByName (
  IN CHAR16                       *Name,
  IN EFI_LIST_ENTRY               *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  );


//
// External functions implementation
//

EFI_STATUS
CreateTestNodes (
  OUT EFI_LIST_ENTRY              *TestNodeList
  )
/*++

Routine Description:

  Create the test node list from the category list and the test file list.

Arguments:

  TestNodeList  - Pointer to the test node list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS              Status;
  EFI_LIST_ENTRY          *CategoryList;
  EFI_LIST_ENTRY          *TestFileList;
  EFI_LIST_ENTRY          *Link;
  EFI_SCT_CATEGORY_DATA   *Category;
  EFI_SCT_TEST_FILE       *TestFile;
  EFI_BB_TEST_PROTOCOL    *BbTest;
  EFI_WB_TEST_PROTOCOL    *WbTest;
  EFI_AP_TEST_INTERFACE   *ApTest;
  VOID                    *EntryList;
  UINTN                   Index;
  EFI_GUID                *CategoryGuid;
  CHAR16                  *CategoryName;
  CHAR16                  *CategoryDescription;
  CHAR16                  CategoryGuidStr[40];
  EFI_SCT_TEST_NODE       *RootNode;

  //
  // Check parameters
  //
  if (TestNodeList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test files
  //
  CategoryList = &gFT->CategoryList;
  TestFileList = &gFT->TestFileList;

  for (Link = TestFileList->Flink; Link != TestFileList; Link = Link->Flink) {
    TestFile = CR (Link, EFI_SCT_TEST_FILE, Link, EFI_SCT_TEST_FILE_SIGNATURE);

    //
    // Deal with the different types of test files
    //
    switch (TestFile->Type) {
    case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
      //
      // Black-box test file
      //
      BbTest       = (EFI_BB_TEST_PROTOCOL *) TestFile->Context;
      EntryList    = BbTest->EntryList;
      CategoryGuid = &BbTest->CategoryGuid;
      break;

    case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
      //
      // White-box test file
      //
      WbTest       = (EFI_WB_TEST_PROTOCOL *) TestFile->Context;
      EntryList    = WbTest->EntryList;
      CategoryGuid = &WbTest->CategoryGuid;
      break;

    case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
    case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
      //
      // Application or script test file
      //
      ApTest       = (EFI_AP_TEST_INTERFACE *) TestFile->Context;
      EntryList    = ApTest->EntryList;
      CategoryGuid = &ApTest->CategoryGuid;
      break;

    default:
      //
      // Unsupported test file
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupport test file"));
      return EFI_UNSUPPORTED;
    }

    //
    // Skip the empty entry list
    //
    if (EntryList == NULL) {
      continue;
    }

    //
    // Find the category data
    //
    Status = FindCategoryByGuid (
               CategoryGuid,
               &Category
               );
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find category by GUID - %r", Status));
      continue;
    }

    if (Status == EFI_NOT_FOUND) {
      Index               = (UINTN) -1;
      SctGuidToStr (CategoryGuid, CategoryGuidStr);
      CategoryName        = PoolPrint (L"Unknown\\%s", CategoryGuidStr);
      CategoryDescription = StrDuplicate (L"");
    } else {
      Index               = Category->Index;
      CategoryName        = StrDuplicate (Category->Name);
      CategoryDescription = StrDuplicate (Category->Description);
    }

    if ((CategoryName        == NULL) ||
        (CategoryDescription == NULL)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Output of resources"));
      continue;
    }

    //
    // Add the root test node from the category name
    //
    Status = AddRootTestNode (
               Index,
               CategoryName,
               CategoryDescription,
               CategoryGuid,
               TestNodeList,
               &RootNode
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add root test node - %r", Status));
      BS->FreePool (CategoryName);
      BS->FreePool (CategoryDescription);
      continue;
    }

    //
    // Insert the test entry list into the test node list
    //
    Status = InsertEntryListToTestNode (
               TestFile->Type,
               EntryList,
               RootNode
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Insert entry list to test node - %r", Status));
      BS->FreePool (CategoryName);
      BS->FreePool (CategoryDescription);
      continue;
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeTestNodes (
  IN EFI_LIST_ENTRY               *TestNodeList
  )
/*++

Routine Description:

  Free the test node list.

Arguments:

  TestNodeList  - Pointer to the test node list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_TEST_NODE   *TestNode;

  //
  // Check parameters
  //
  if (TestNodeList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes
  //
  while (!IsListEmpty (TestNodeList)) {
    TestNode = CR (TestNodeList->Flink, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    RemoveEntryList (&TestNode->Link);

    if (!IsListEmpty (&TestNode->Child)) {
      FreeTestNodes (&TestNode->Child);
    }

    FreeSingleTestNode (TestNode);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
InsertEntryListToTestNode (
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *EntryList,
  OUT EFI_SCT_TEST_NODE           *RootNode
  )
/*++

Routine Description:

  Insert a entry list into the test node.

--*/
{
  EFI_STATUS          Status;
  EFI_BB_TEST_ENTRY   *BbEntry;
  EFI_WB_TEST_ENTRY   *WbEntry;
  EFI_AP_TEST_ENTRY   *ApEntry;
  EFI_SCT_TEST_NODE   *TestNode;

  //
  // Check parameters
  //
  if ((EntryList == NULL) || (RootNode == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Deal with different kinds of test files
  //
  switch (Type) {
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
    //
    // Black-box test file
    //
    BbEntry = (EFI_BB_TEST_ENTRY *) EntryList;

    while (BbEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 BbEntry->Name,
                 BbEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &BbEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      BbEntry = BbEntry->Next;
    }

    break;

  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // White-box test file
    //
    WbEntry = (EFI_WB_TEST_ENTRY *) EntryList;

    while (WbEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 WbEntry->Name,
                 WbEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &WbEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      WbEntry = WbEntry->Next;
    }

    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    ApEntry = (EFI_AP_TEST_ENTRY *) EntryList;

    while (ApEntry != NULL) {
      Status = AddTestNode (
                 (UINTN) -1,
                 ApEntry->Name,
                 ApEntry->Description,
                 EFI_SCT_TEST_NODE_TYPE_CASE,
                 &ApEntry->EntryId,
                 &RootNode->Child,
                 &TestNode
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }

      ApEntry = ApEntry->Next;
    }

    break;

  default:
    //
    // Unsupported test file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported test file"));
    return EFI_UNSUPPORTED;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleTestNode (
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Create a test node.

--*/
{
  EFI_STATUS          Status;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if (TestNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for the test node
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_TEST_NODE),
                 &TempTestNode
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  ZeroMem (TempTestNode, sizeof(EFI_SCT_TEST_NODE));

  //
  // Initiailize the items of test node
  //
  TempTestNode->Signature = EFI_SCT_TEST_NODE_SIGNATURE;
  TempTestNode->Revision  = EFI_SCT_TEST_NODE_REVISION;

  InitializeListHead (&TempTestNode->Child);

  //
  // Done
  //
  *TestNode = TempTestNode;
  return EFI_SUCCESS;
}


EFI_STATUS
FreeSingleTestNode (
  IN EFI_SCT_TEST_NODE            *TestNode
  )
/*++

Routine Description:

  Free a test node.

--*/
{
  //
  // Check parameters
  //
  if (TestNode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Free the items of test node
  //
  if (TestNode->Name != NULL) {
    BS->FreePool (TestNode->Name);
    TestNode->Name = NULL;
  }

  if (TestNode->Description != NULL) {
    BS->FreePool (TestNode->Description);
    TestNode->Description = NULL;
  }

  //
  // Free the test node itself
  //
  BS->FreePool (TestNode);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AddRootTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_GUID                     *Guid,
  IN OUT EFI_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **RootNode
  )
/*++

Routine Description:

  Add a root test node from the category name.

--*/
{
  EFI_STATUS          Status;
  BOOLEAN             IsEnd;
  CHAR16              *TempName;
  CHAR16              *Token;
  CHAR16              *End;
  EFI_LIST_ENTRY      *SubList;
  EFI_SCT_TEST_NODE   *TempRootNode;

  //
  // Check parameters
  //
  if ((Name         == NULL) || (Description == NULL) || (Guid == NULL) ||
      (TestNodeList == NULL) || (RootNode    == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize
  //
  IsEnd    = FALSE;
  TempName = StrDuplicate (Name);
  Token    = TempName;
  End      = TempName;
  SubList  = TestNodeList;
  TempRootNode = NULL;

  //
  // Walk through all tokens in the name
  //
  while (!IsEnd) {
    //
    // Find the token
    //
    while ((*End != L'\0') && (*End != L'\\') && (*End != L'/')) {
      End ++;
    }

    if (*End == L'\0') {
      IsEnd = TRUE;
    } else {
      *End = L'\0';
      End ++;
    }

    if (StrLen (Token) == 0) {
      continue;
    }

    //
    // Find the test node
    //
    Status = FindTestNodeByName (Token, SubList, &TempRootNode);
    if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Find node by name - %r", Status));
      break;
    }

    if (Status == EFI_NOT_FOUND) {
      if (!IsEnd) {
        Status = AddTestNode (
                   Index,
                   Token,
                   L"",
                   EFI_SCT_TEST_NODE_TYPE_CATEGORY,
                   &gEfiNullGuid,
                   SubList,
                   &TempRootNode
                   );
      } else {
        Status = AddTestNode (
                   Index,
                   Token,
                   Description,
                   EFI_SCT_TEST_NODE_TYPE_CATEGORY,
                   Guid,
                   SubList,
                   &TempRootNode
                   );
      }

      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Add test node - %r", Status));
        break;
      }
    }

    //
    // Recursive
    //
    Token   = End;
    SubList = &TempRootNode->Child;
  }

  //
  // Free resources
  //
  BS->FreePool (TempName);

  //
  // Done
  //
  *RootNode = TempRootNode;
  return EFI_SUCCESS;
}


EFI_STATUS
AddTestNode (
  IN UINTN                        Index,
  IN CHAR16                       *Name,
  IN CHAR16                       *Description,
  IN EFI_SCT_TEST_NODE_TYPE       Type,
  IN EFI_GUID                     *Guid,
  IN OUT EFI_LIST_ENTRY           *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Add a test node.

--*/
{
  EFI_STATUS          Status;
  EFI_LIST_ENTRY      *Link;
  EFI_SCT_TEST_NODE   *Last;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if ((Name         == NULL) || (Description == NULL) || (Guid == NULL) ||
      (TestNodeList == NULL) || (TestNode    == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Create a test node
  //
  Status = CreateSingleTestNode (&TempTestNode);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test node - %r", Status));
    return Status;
  }

  //
  // Set the items of test node
  //
  TempTestNode->Index       = Index;
  TempTestNode->Name        = StrDuplicate (Name);
  TempTestNode->Description = StrDuplicate (Description);
  TempTestNode->Type        = Type;
  CopyMem (&TempTestNode->Guid, Guid, sizeof(EFI_GUID));

  //
  // Add the test node into the test node list
  //
  for (Link = TestNodeList->Flink; Link != TestNodeList; Link = Link->Flink) {
    Last = CR (Link, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    if (Last->Index > Index) {
      break;
    }

    if ((Last->Index == Index) && (StriCmp (Last->Name, Name) > 0)) {
      break;
    }
  }

  InsertTailList (Link, &TempTestNode->Link);

  //
  // Done
  //
  *TestNode = TempTestNode;
  return EFI_SUCCESS;
}


EFI_STATUS
FindTestNodeByName (
  IN CHAR16                       *Name,
  IN EFI_LIST_ENTRY               *TestNodeList,
  OUT EFI_SCT_TEST_NODE           **TestNode
  )
/*++

Routine Description:

  Seach a test node based on the name.

--*/
{
  EFI_LIST_ENTRY      *Link;
  EFI_SCT_TEST_NODE   *TempTestNode;

  //
  // Check parameters
  //
  if ((Name == NULL) || (TestNodeList == NULL) || (TestNode == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test nodes on one layer
  //
  for (Link = TestNodeList->Flink; Link != TestNodeList; Link = Link->Flink) {
    TempTestNode = CR (Link, EFI_SCT_TEST_NODE, Link, EFI_SCT_TEST_NODE_SIGNATURE);

    if (StriCmp (TempTestNode->Name, Name) == 0) {
      //
      // Got it!
      //
      *TestNode = TempTestNode;
      return EFI_SUCCESS;
    }
  }

  //
  // Not found
  //
  return EFI_NOT_FOUND;
}
