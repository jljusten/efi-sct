/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BuildMenu.c

Abstract:

  This file provides the services to build a menu.

--*/

#include "BuildMenu.h"

//
// Variable Definitions
//

//
// Variables used to create menu system
//
UINTN                       mCols;
UINTN                       mRows;

//
// Prototypes (external)
//

EFI_STATUS
BuildMenuSystem (
  VOID
  );

EFI_STATUS
CreateStandardMenuPage (
  IN CHAR16                       *MenuItemHeaderText,
  OUT EFI_MENU_PAGE               **Page
  );

EFI_STATUS
DestroyMenuPage (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
AddHotKey (
  IN CHAR16                       *HotKeyNameText,
  IN CHAR16                       *HotKeyDescText,
  IN UINT16                       ScanCode,
  IN CHAR16                       UnicodeChar,
  IN KEY_FUNCTION                 KeyFunc,
  IN BOOLEAN                      Visible,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddSimpleMenuItem (
  IN EFI_ITEM_TYPE                ItemType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddEditMenuItem (
  IN EFI_ITEM_TYPE                SubType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddPopupMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddComboListMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
AddSeparateLine (
  IN UINTN                        Number,
  IN OUT EFI_MENU_PAGE            *Page
  );

EFI_STATUS
InsertValueQueue (
  IN OUT EFI_ITEM_VALUE_QUEUE     **ValueQueue,
  IN CHAR16                       *StringValue,
  IN UINTN                        IntValue
  );

EFI_STATUS
DestroyValueQueue (
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue
  );

EFI_STATUS
AddScrollBar (
  IN OUT EFI_MENU_PAGE             *Page
  );

//
// Functions
//

EFI_STATUS
SctMenu (
  VOID
  )
/*++

Routine Description:

  Build the menu system

Returns:

  EFI_SUCCESS   - Build the menu system successfully
  Other Value   - Somthing failed

--*/
{
  //
  // Get the cols and rows of the displayed screen
  //
  ST->ConOut->QueryMode (
                ST->ConOut,
                ST->ConOut->Mode->Mode,
                &mCols,
                &mRows
                );

  InitializeTestFrameworkUi ();

  //
  // Display the main menu
  //
  DisplayMainMenu ();

  TestFrameworkUiRestore ();
  return EFI_SUCCESS;
}


EFI_STATUS
CreateStandardMenuPage (
  IN CHAR16                       *MenuItemHeaderText,
  OUT EFI_MENU_PAGE               **Page
  )
/*++

Routine Description:

  Create a standard menu page

Arguments:

  MenuItemHeaderText  - A text string of menu item header
  Page                - A pointer to the standard menu page

Returns:

  EFI_SUCCESS         - Create successfully
  Other Values        - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_PAGE         *MyPage;

  //
  // Allocate memory for the menu page
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_PAGE),
                 &MyPage
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Page
  //
  MyPage->BackColor = EFI_BLACK;
  MyPage->HasHeader = TRUE;
  MyPage->HasBody   = TRUE;
  MyPage->HasFooter = TRUE;
  MyPage->Parent    = NULL;

  //
  // Header
  //
  MyPage->Header.HeaderString.Text      = PoolPrint (L"%s (v %s)", EFI_SCT_NAME, EFI_SCT_VERSION);
  MyPage->Header.HeaderString.TextColor = EFI_WHITE;
  MyPage->Header.HeaderString.Align     = EFI_ALIGNMENT_MIDDLE;

  MyPage->Header.HeaderRect.TopLeft.Row     = 0;
  MyPage->Header.HeaderRect.TopLeft.Col     = 0;
  MyPage->Header.HeaderRect.BottomRight.Row = EFI_MENU_HEADER_ROWS;
  MyPage->Header.HeaderRect.BottomRight.Col = mCols - 1;

  //
  // Body
  //
  MyPage->Body.BackColor = EFI_BACKGROUND_LIGHTGRAY;
  MyPage->Body.ForeColor = EFI_BLUE;

  MyPage->Body.BodyRect.TopLeft.Row     = EFI_MENU_HEADER_ROWS;
  MyPage->Body.BodyRect.TopLeft.Col     = 0;
  MyPage->Body.BodyRect.BottomRight.Row = mRows - EFI_MENU_FOOTER_ROWS - 1;
  MyPage->Body.BodyRect.BottomRight.Col = mCols - 1;

  MyPage->Body.SplitPoint.Row = EFI_MENU_HEADER_ROWS + 2;
  MyPage->Body.SplitPoint.Col = mCols - EFI_MENU_DESCRIPTOR_COLS - 1;

  MyPage->Body.MenuItemHeader.Text      = StrDuplicate (MenuItemHeaderText);
  MyPage->Body.MenuItemHeader.TextColor = EFI_BLACK;
  MyPage->Body.MenuItemHeader.Align     = EFI_ALIGNMENT_MIDDLE;

  MyPage->Body.DescriptionHeader.Text      = StrDuplicate (L"Description");
  MyPage->Body.DescriptionHeader.TextColor = EFI_BLACK;
  MyPage->Body.DescriptionHeader.Align     = EFI_ALIGNMENT_MIDDLE;

  MyPage->Body.HasScrollBar = FALSE;
  MyPage->Body.ScrollBar    = NULL;

  MyPage->Body.ItemList        = NULL;
  MyPage->Body.CurrentSelected = NULL;
  MyPage->Body.FirstInDisplay  = NULL;
  MyPage->Body.LastInDisplay   = NULL;

  //
  // Footer
  //
  MyPage->Footer.FooterRect.TopLeft.Row     = mRows - EFI_MENU_FOOTER_ROWS;
  MyPage->Footer.FooterRect.TopLeft.Col     = 0;
  MyPage->Footer.FooterRect.BottomRight.Row = mRows - 1;
  MyPage->Footer.FooterRect.BottomRight.Col = mCols - 1;

  MyPage->Footer.HotKeyList = NULL;

  //
  // Build a new standard menu page successfully
  //
  *Page = MyPage;
  return EFI_SUCCESS;
}


EFI_STATUS
DestroyMenuPage (
  IN EFI_MENU_PAGE      *Page
  )
/*++

Routine Description:

  Destroy a menu page

Arguments:

  Page          -  A pointer to the menu page

Returns:

  EFI_SUCCESS   - Destroy the menu page successfully
  Other Value   - Something failed

--*/
{
  EFI_HOT_KEY           *HotKey;
  EFI_HOT_KEY           *NextHotKey;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *NextMenuItem;

  //
  // Header
  //
  BS->FreePool (Page->Header.HeaderString.Text);

  //
  // Body
  //
  BS->FreePool (Page->Body.MenuItemHeader.Text);
  BS->FreePool (Page->Body.DescriptionHeader.Text);

  MenuItem = Page->Body.ItemList;

  //
  //free all the menu items.
  //
  while (MenuItem != NULL) {
    NextMenuItem = MenuItem->Next;

    //
    //combolist use ValueQueue store different value.
    //
    if ( MenuItem->ValueQueue != NULL ) {
      DestroyValueQueue (MenuItem->ValueQueue);
    }

    //
    //EDIT use ItemValue pointer to store string value.
    //
    if ((MENU_ITEM_TYPE (MenuItem->ItemType) == EFI_ITEM_HAVE_EDIT ||
         MENU_ITEM_TYPE (MenuItem->ItemType) == EFI_ITEM_HAVE_POPUP) &&
        (MenuItem->ItemValue != NULL)) {
      BS->FreePool (MenuItem->ItemValue);
    }
    BS->FreePool (MenuItem);
    MenuItem = NextMenuItem;
  }

  //
  //free scroll bar.
  //
  if (Page->Body.HasScrollBar) {
    BS->FreePool (Page->Body.ScrollBar);
  }

  //
  // Footer
  //
  HotKey = Page->Footer.HotKeyList;

  while (HotKey != NULL) {
    NextHotKey = HotKey->Next;

    BS->FreePool (HotKey->HotKeyName.Text);
    BS->FreePool (HotKey->HotKeyDesc.Text);
    BS->FreePool (HotKey);

    HotKey = NextHotKey;
  }

  //
  // Page
  //
  BS->FreePool (Page);

  return EFI_SUCCESS;
}


EFI_STATUS
AddHotKey (
  IN CHAR16                       *HotKeyNameText,
  IN CHAR16                       *HotKeyDescText,
  IN UINT16                       ScanCode,
  IN CHAR16                       UnicodeChar,
  IN KEY_FUNCTION                 KeyFunc,
  IN BOOLEAN                      Visible,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add a hot key to the menu page

Arguments:

  HotKeyNameText  - A name string of the hot key
  HotKeyDescText  - A description string of the hot key
  ScanCode        - A scan code of the hot key
  UnicodeChar     - A unicode char of the hot key
  KeyFunc         - A function pointer of the hot key
  Page            - A pointer to the menu page

Returns:

  EFI_SUCCESS     - Add the hot key successfully
  Other Value     - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_HOT_KEY           *HotKey;
  EFI_HOT_KEY           *LastHotKey;

  //
  // Allocate memory for hot key
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_HOT_KEY),
                 (VOID*)&HotKey
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Hot key
  //
  HotKey->HotKeyName.Text      = StrDuplicate (HotKeyNameText);
  HotKey->HotKeyName.TextColor = EFI_GREEN;
  HotKey->HotKeyName.Align     = EFI_ALIGNMENT_LEFT;

  HotKey->HotKeyDesc.Text      = StrDuplicate (HotKeyDescText);
  HotKey->HotKeyDesc.TextColor = EFI_WHITE;
  HotKey->HotKeyDesc.Align     = EFI_ALIGNMENT_LEFT;

  HotKey->KeyCode.ScanCode    = ScanCode;
  HotKey->KeyCode.UnicodeChar = UnicodeChar;

  HotKey->Context = KeyFunc;
  HotKey->Next    = NULL;
  HotKey->Visible = Visible;
  //
  // Add this hot key at the end of hot key list
  //
  LastHotKey = Page->Footer.HotKeyList;

  if (LastHotKey == NULL) {
    Page->Footer.HotKeyList = HotKey;
  } else {
    while (LastHotKey->Next != NULL) {
      LastHotKey = LastHotKey->Next;
    }
    LastHotKey->Next = HotKey;
  }

  //
  // Add the hot key successfully
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AddSimpleMenuItem (
  IN EFI_ITEM_TYPE                ItemType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add a simple menu item into the menu page

Arguments:

  ItemType      - Type of the menu item
  ItemNameText  - A name string of the menu item
  ItemDescText  - A description string of the menu item
  Context       - A pointer to store some infos of the menu item
  Page          - A pointer to the menu page

Returns:

  EFI_SUCCESS   - Add simple menu item successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *LastMenuItem;

  //
  // Allocate memory for menu item
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_ITEM),
                 (VOID*)&MenuItem
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BS->SetMem(MenuItem, sizeof (EFI_MENU_ITEM), 0);

  //
  // Menu item
  //
  MenuItem->ItemType = ItemType;

  MenuItem->ItemString.Text      = ItemNameText;
  MenuItem->ItemString.TextColor = EFI_BLACK;
  MenuItem->ItemString.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->ItemDesc.Text      = ItemDescText;
  MenuItem->ItemDesc.TextColor = EFI_BLACK;
  MenuItem->ItemDesc.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->IsSelected = FALSE;
  MenuItem->Skip       = 0;
  MenuItem->Context    = Context;
  MenuItem->DescPrint  = NULL;

  MenuItem->Next = NULL;
  MenuItem->Prev = NULL;

  //
  // Add this menu item at the end of menu item list
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    Page->Body.ItemList        = MenuItem;
    Page->Body.CurrentSelected = MenuItem;
    Page->Body.FirstInDisplay  = MenuItem;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Next = MenuItem;
    MenuItem->Prev     = LastMenuItem;
  }

  //
  // Add the menu item successfully
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AddEditMenuItem (
  IN EFI_ITEM_TYPE                SubType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add an Edit menu item into the menu page

Arguments:

  SubType       - Edit Sub Type such as Number and String
  ItemNameText  - A name string of the menu item
  ItemDescText  - A description string of the menu item
  ItemValue     - A pointer to store the Edit input string
  Context       - A pointer to store some infos of the menu item
  Page          - A pointer to the menu page

Returns:

  EFI_SUCCESS   - Add Edit menu item successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *LastMenuItem;

  if (ItemValue == NULL || Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if ((SubType&EFI_EDIT_SUB_TYPE_MASK) == 0 ||
      (SubType&EFI_EDIT_SUB_TYPE_MASK) == EFI_EDIT_SUB_TYPE_MASK) {

    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for menu item
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_ITEM),
                 (VOID*)&MenuItem
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BS->SetMem(MenuItem, sizeof (EFI_MENU_ITEM), 0);

  //
  // Menu item
  //
  MenuItem->ItemType = EFI_ITEM_HAVE_EDIT|SubType;

  MenuItem->ItemString.Text      = ItemNameText;
  MenuItem->ItemString.TextColor = EFI_BLACK;
  MenuItem->ItemString.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->ItemDesc.Text      = ItemDescText;
  MenuItem->ItemDesc.TextColor = EFI_BLACK;
  MenuItem->ItemDesc.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->IsSelected = FALSE;
  MenuItem->Skip       = 0;
  MenuItem->ItemValue  = ItemValue;
  MenuItem->Context    = Context;
  MenuItem->DescPrint  = NULL;
  MenuItem->CheckValue = FALSE;
  MenuItem->Next = NULL;
  MenuItem->Prev = NULL;

  //
  // Add this menu item at the end of menu item list
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    Page->Body.ItemList        = MenuItem;
    Page->Body.CurrentSelected = MenuItem;
    Page->Body.FirstInDisplay  = MenuItem;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Next = MenuItem;
    MenuItem->Prev     = LastMenuItem;
  }

  //
  // Add the Edit menu item successfully
  //
  return EFI_SUCCESS;
}


EFI_STATUS
AddCaseMenuItem (
  IN EFI_ITEM_TYPE                SubType,
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add a Case menu item into the menu page

Arguments:

  SubType       - Edit Sub Type such as Number and String
  ItemNameText  - A name string of the menu item
  ItemDescText  - A description string of the menu item
  ItemValue     - A pointer to store the Edit input string
  Context       - A pointer to store some infos of the menu item
  Page          - A pointer to the menu page

Returns:

  EFI_SUCCESS   - Add Edit menu item successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *LastMenuItem;

  if (ItemValue == NULL || Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if ((SubType&EFI_EDIT_SUB_TYPE_MASK) == 0 ||
      (SubType&EFI_EDIT_SUB_TYPE_MASK) == EFI_EDIT_SUB_TYPE_MASK) {

    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for menu item
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_ITEM),
                 (VOID*)&MenuItem
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BS->SetMem(MenuItem, sizeof (EFI_MENU_ITEM), 0);

  //
  // Menu item
  //
  MenuItem->ItemType = SubType;

  MenuItem->ItemString.Text      = ItemNameText;
  MenuItem->ItemString.TextColor = EFI_BLACK;
  MenuItem->ItemString.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->ItemDesc.Text      = ItemDescText;
  MenuItem->ItemDesc.TextColor = EFI_BLACK;
  MenuItem->ItemDesc.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->IsSelected = FALSE;
  MenuItem->Skip       = 0;
  MenuItem->ItemValue  = ItemValue;
  MenuItem->Context    = Context;
  MenuItem->DescPrint  = NULL;
  MenuItem->CheckValue = FALSE;
  MenuItem->Next = NULL;
  MenuItem->Prev = NULL;

  //
  // Add this menu item at the end of menu item list
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    Page->Body.ItemList        = MenuItem;
    Page->Body.CurrentSelected = MenuItem;
    Page->Body.FirstInDisplay  = MenuItem;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Next = MenuItem;
    MenuItem->Prev     = LastMenuItem;
  }

  //
  // Add the Edit menu item successfully
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AddMenuItemCheckValue (
  IN CHAR16                       *ItemNameText,
  IN UINTN                        MaxValue,
  IN UINTN                        MinValue,
  IN UINTN                        DefaultValue,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add number range for a number edit menu item in menu page

Arguments:

  ItemNameText  - A name string of the menu item
  MaxValue      - The maximum value of the menu item
  MinValue      - The minimum value of the menu item
  DefaultValue  - The default value of the menu item
  Page          - A pointer to the menu page

Returns:

  EFI_SUCCESS   - Add Edit menu item successfully
  Other Value   - Something failed

--*/
{
  EFI_MENU_ITEM         *MenuItem;

  if (ItemNameText == NULL || Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MenuItem = Page->Body.ItemList;

  //
  //Go through meun item list to search for the required menu item according to its name.
  //
  while(MenuItem != NULL) {
    if (StriCmp (MenuItem->ItemString.Text, ItemNameText) == 0) {

      //
      //Find a menu item matching the name, check its type
      //
      if ((MenuItem->ItemType & EFI_EDIT_SUB_TYPE_MASK) != EFI_ITEM_EDIT_NUMBER) {
        return EFI_INVALID_PARAMETER;
      }
      MenuItem->CheckValue = TRUE;
      MenuItem->MaxValue   = MaxValue;
      MenuItem->MinValue   = MinValue;
      MenuItem->DefaultValue = DefaultValue;
      break;
    }
    MenuItem = MenuItem->Next;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
AddPopupMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN CHAR16                       *ItemValue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add an Popup menu item into the menu page

Arguments:

  ItemNameText    - A name string of the menu item
  ItemDescText    - A description string of the menu item
  ItemQueue       - A pointer to Item String value
  Context         - A pointer to store some infos of the menu item
  Page            - A pointer to the menu page

Returns:

  EFI_SUCCESS     - Add Popup menu item successfully
  Other Value     - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *LastMenuItem;

  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for menu item
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_ITEM),
                 (VOID*)&MenuItem
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BS->SetMem(MenuItem, sizeof (EFI_MENU_ITEM), 0);

  //
  // Menu item
  //
  MenuItem->ItemType = EFI_ITEM_HAVE_POPUP;

  MenuItem->ItemString.Text      = ItemNameText;
  MenuItem->ItemString.TextColor = EFI_BLACK;
  MenuItem->ItemString.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->ItemDesc.Text      = ItemDescText;
  MenuItem->ItemDesc.TextColor = EFI_BLACK;
  MenuItem->ItemDesc.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->IsSelected = FALSE;
  MenuItem->Skip       = 0;
  MenuItem->ItemValue  = ItemValue;
  MenuItem->Context    = Context;
  MenuItem->DescPrint  = NULL;

  MenuItem->Next = NULL;
  MenuItem->Prev = NULL;

  //
  // Add this menu item at the end of menu item list
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    Page->Body.ItemList        = MenuItem;
    Page->Body.CurrentSelected = MenuItem;
    Page->Body.FirstInDisplay  = MenuItem;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Next = MenuItem;
    MenuItem->Prev     = LastMenuItem;
  }

  //
  // Add the Edit menu item successfully
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AddComboListMenuItem (
  IN CHAR16                       *ItemNameText,
  IN CHAR16                       *ItemDescText,
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue,
  IN VOID                         *Context,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add an Combo List menu item into the menu page

Arguments:

  ItemNameText    - A name string of the menu item
  ItemDescText    - A description string of the menu item
  ValueQueue      - A pointer to EFI_ITEM_VALUE_QUEUE
  Context         - A pointer to store some infos of the menu item
  Page            - A pointer to the menu page

Returns:

  EFI_SUCCESS     - Add Combo List menu item successfully
  Other Value     - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_ITEM         *MenuItem;
  EFI_MENU_ITEM         *LastMenuItem;

  if (ValueQueue == NULL || Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Allocate memory for menu item
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_MENU_ITEM),
                 (VOID*)&MenuItem
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BS->SetMem(MenuItem, sizeof (EFI_MENU_ITEM), 0);

  //
  // Menu item
  //
  MenuItem->ItemType = EFI_ITEM_HAVE_COMBOLIST;

  MenuItem->ItemString.Text      = ItemNameText;
  MenuItem->ItemString.TextColor = EFI_BLACK;
  MenuItem->ItemString.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->ItemDesc.Text      = ItemDescText;
  MenuItem->ItemDesc.TextColor = EFI_BLACK;
  MenuItem->ItemDesc.Align     = EFI_ALIGNMENT_LEFT;

  MenuItem->IsSelected = FALSE;
  MenuItem->Skip       = 0;
  MenuItem->ValueQueue = ValueQueue;
  MenuItem->ItemValue  = ValueQueue->StringValue;
  MenuItem->Context    = Context;
  MenuItem->DescPrint  = NULL;

  MenuItem->Next = NULL;
  MenuItem->Prev = NULL;

  //
  // Add this menu item at the end of menu item list
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    Page->Body.ItemList        = MenuItem;
    Page->Body.CurrentSelected = MenuItem;
    Page->Body.FirstInDisplay  = MenuItem;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Next = MenuItem;
    MenuItem->Prev     = LastMenuItem;
  }

  //
  // Add the Combo List menu item successfully
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AddSeparateLine (
  IN UINTN                        Number,
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  add space line in the last menu item

Arguments:

  Number        - the space line to add
  Page          - a pointer to the menu page

Returns:

  EFI_SUCCESS   - the space lines added successfully
  Other value   - some error happened

--*/
{
  EFI_MENU_ITEM         *LastMenuItem;

  //
  // Add skip line in the last menu item
  //
  LastMenuItem = Page->Body.ItemList;

  if (LastMenuItem == NULL) {
    return EFI_INVALID_PARAMETER;
  } else {
    while (LastMenuItem->Next != NULL) {
      LastMenuItem = LastMenuItem->Next;
    }
    LastMenuItem->Skip = LastMenuItem->Skip + Number;
    return EFI_SUCCESS;
  }
}

EFI_STATUS
InsertValueQueue (
  IN OUT EFI_ITEM_VALUE_QUEUE     **ValueQueue,
  IN CHAR16                       *StringValue,
  IN UINTN                        IntValue
  )
/*++

Routine Description:

  insert a item into a value queue

Arguments:

  ValueQueue    - A pointer to the value queue
  StringValue   - The String Value of the Value Queue Item
  IntValue      - The Int Value of the Value Queue Item

Returns:

  EFI_SUCCESS   - successfully add the value queue item

--*/
{
  EFI_ITEM_VALUE_QUEUE           *TempValueQueue;
  EFI_ITEM_VALUE_QUEUE           *NextValueQueue;
  EFI_STATUS                     Status;

  if (ValueQueue == NULL || StringValue == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  //allocate memory for Value Queue
  //
  Status = BS->AllocatePool (
          EfiBootServicesData,
          sizeof (EFI_ITEM_VALUE_QUEUE),
          &TempValueQueue
          );
  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }
  BS->SetMem (TempValueQueue, sizeof (EFI_ITEM_VALUE_QUEUE), 0);

  TempValueQueue->StringValue = StrDuplicate (StringValue);
  TempValueQueue->IntValue    = IntValue;
  TempValueQueue->Next        = TempValueQueue;
  TempValueQueue->Prev        = TempValueQueue;

  if (*ValueQueue == NULL) {
    *ValueQueue = TempValueQueue;
    return EFI_SUCCESS;
  } else {
    //
    //link this item to the tail of valuequeue
    //
    NextValueQueue              = *ValueQueue;
    TempValueQueue->Next        = NextValueQueue;
    TempValueQueue->Prev        = NextValueQueue ->Prev;
    NextValueQueue->Prev->Next  = TempValueQueue;
    NextValueQueue->Prev        = TempValueQueue;
    return EFI_SUCCESS;
  }
}

EFI_STATUS
DestroyValueQueue (
  IN EFI_ITEM_VALUE_QUEUE         *ValueQueue
  )
/*++

Routine Description:

  free value queue

Arguments:

  ValueQueue    - a pointer to the value queue

Returns:

  EFI_SUCCESS   - successfully freed the value queue

*/
{
  EFI_ITEM_VALUE_QUEUE      *NextValueQueue;
  EFI_ITEM_VALUE_QUEUE      *TempValueQueue;

  if (ValueQueue == NULL) {
    return EFI_SUCCESS;
  }
  NextValueQueue = ValueQueue;
  //
  //cut the bi-direction link
  //
  NextValueQueue->Prev->Next = NULL;

  while (NextValueQueue != NULL) {
    TempValueQueue = NextValueQueue->Next;

    if (NextValueQueue->StringValue != NULL) {
      BS->FreePool(NextValueQueue->StringValue);
    }

    BS->FreePool (NextValueQueue);

    NextValueQueue = TempValueQueue;
  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

EFI_STATUS
AddScrollBar (
  IN OUT EFI_MENU_PAGE            *Page
  )
/*++

Routine Description:

  Add a scroll bar to the menu page.

Arguments:

  Page          - a pointer to the menu page

Returns:

  EFI_SUCCESS   - successfully add scrollbar or no need to add scrollbar
  other value   - some error happened

--*/
{
  EFI_STATUS              Status;
  EFI_MENU_ITEM           *MenuItem;
  UINTN                   TotalLine;
  EFI_SCROLL_BAR          *ScrollBar;
  UINTN                   Index;
  UINTN                   CanShowedLine;

  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MenuItem = Page->Body.ItemList;
  if (MenuItem == NULL) {
    return EFI_SUCCESS;
  }
  TotalLine = 0;
  while (MenuItem->Next != NULL) {
    TotalLine = TotalLine + 1 + MenuItem->Skip;
    MenuItem = MenuItem->Next;
  }
  TotalLine = TotalLine + 1;
  CanShowedLine = Page->Body.BodyRect.BottomRight.Row - Page->Body.SplitPoint.Row - 1;
  if (TotalLine <= CanShowedLine) {
    //
    // the total line less or equal the can  showed line so no need to add
    // scroll bar.
    //
    return EFI_SUCCESS;
  }

  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof (EFI_SCROLL_BAR),
                 &ScrollBar
                 );
  if(!EFI_ERROR (Status)) {
    ScrollBar->ScrollBarRect.TopLeft.Row = Page->Body.SplitPoint.Row + 1 ;
    ScrollBar->ScrollBarRect.TopLeft.Col = Page->Body.SplitPoint.Col - 1;

    ScrollBar->ScrollBarRect.BottomRight.Row = Page->Body.BodyRect.BottomRight.Row - 1 ;
    ScrollBar->ScrollBarRect.BottomRight.Col = Page->Body.SplitPoint.Col - 1;

    ScrollBar->Count = TotalLine;
    ScrollBar->PinLength = (CanShowedLine * (CanShowedLine - 2)) / ScrollBar->Count;
    Index = (CanShowedLine * (CanShowedLine - 2)) % ScrollBar->Count;
    if(Index > ScrollBar->Count / 2 || ScrollBar->PinLength == 0) {
      ScrollBar->PinLength++;
    }
    ScrollBar->Pos          = 0;
    Page->Body.HasScrollBar = TRUE;
    Page->Body.ScrollBar    = ScrollBar;
  }

  //
  //add scroll bar successfully.
  //
  return EFI_SUCCESS;
}
