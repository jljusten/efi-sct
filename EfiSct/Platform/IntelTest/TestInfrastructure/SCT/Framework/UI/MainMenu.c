/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  MainMenu.c

Abstract:

  Deal with the main menu in the user interface.

--*/

#include "BuildMenu.h"
#include "Dialog.h"
#include "FileDialog.h"

#include "TestNodeMenu.h"

//
// Definitions
//

#define EFI_MENU_ITEM_CONFIG              0
#define EFI_MENU_ITEM_CASE_MANAGEMENT     1
#define EFI_MENU_ITEM_REPORT_GENERATOR    2
#define EFI_MENU_ITEM_VIEW_LOG            3
#define EFI_MENU_ITEM_UTILITY             4

//
// a globel variable indicating continue exec flag
//
BOOLEAN                gContinueExec;
EFI_LIST_ENTRY         *TestTree;

//
// A variable imported from UI.c
//
extern BOOLEAN          gMenuExit;

//
// Prototypes (external)
//

EFI_STATUS
DisplayMainMenu (
  VOID
  );

//
// Prototypes (internal)
//

VOID
DisplayReportGenerator(
  IN EFI_MENU_PAGE                *Page
  );

VOID
DisplayLog(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuEnterFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuEscFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuLoadSeqFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuSaveSeqFunc (
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  );

EFI_STATUS
MainMenuClearFunc (
  IN EFI_MENU_PAGE                *Page
  );

//
// Functions
//

EFI_STATUS
DisplayMainMenu (
  VOID
  )
/*++

Routine Description:

  Display the main menu

Returns:

  EFI_SUCCESS   - Display the menu successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS            Status;
  EFI_MENU_PAGE         *Page;
  EFI_DIALOG_CONTEXT    DialogContext;
  CHAR16                *DialogTitle;

  //
  // Create a standard menu
  //
  Status = CreateStandardMenuPage (
             L"Main Menu",
             &Page
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Main Menu Items
  //  - Test Case Management
  //  - Test Environment Configuration
  //  - Test Report Generator ...
  //  - Help
  //
  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Case Management",
             L"Select and execute test cases",
             (VOID *)(UINTN)EFI_MENU_ITEM_CASE_MANAGEMENT,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Environment Configuration",
             L"Set configuration data for testing",
             (VOID *)(UINTN)EFI_MENU_ITEM_CONFIG,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"View Test Log ...",
             L"View test log",
             (VOID *)(UINTN)EFI_MENU_ITEM_VIEW_LOG,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Test Report Generator ...",
             L"Generate test report",
             (VOID *)(UINTN)EFI_MENU_ITEM_REPORT_GENERATOR,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddSimpleMenuItem (
             EFI_ITEM_HAVE_SUBITEMS,
             L"Help",
             L"EFI Self Certification Test is a toolkit to check an EFI1.10 "
             L"implementation is EFI1.10 Specification compliant or not.",
             (VOID *)(UINTN)EFI_MENU_ITEM_UTILITY,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  //
  // Main Menu Hot Keys
  //  - Up, Down, Enter, Esc, F5, F6
  //
  Status = AddHotKey (
             L"Up/Dn",
             L"Select Item",
             SCAN_UP,
             CHAR_NULL,
             UpFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Down",
             L"Select Item",
             SCAN_DOWN,
             CHAR_NULL,
             DownFunc,
             FALSE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F4",
             L"Reset results",
             SCAN_F4,
             CHAR_NULL,
             MainMenuClearFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F5",
             L"Load Sequence",
             SCAN_F5,
             CHAR_NULL,
             MainMenuLoadSeqFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F6",
             L"Save Sequence",
             SCAN_F6,
             CHAR_NULL,
             MainMenuSaveSeqFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"Enter",
             L"Select SubMenu",
             SCAN_NULL,
             CHAR_CARRIAGE_RETURN,
             MainMenuEnterFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"ESC",
             L"Exit",
             SCAN_ESC,
             CHAR_NULL,
             MainMenuEscFunc,
             TRUE,
             Page
             );
  if (EFI_ERROR(Status)) {
    DestroyMenuPage (Page);
    return Status;
  }

  Status = AddHotKey (
             L"F9",
             L"Run",
             SCAN_F9,
             CHAR_NULL,
             MainMenuF9Func,
             FALSE,
             Page
             );
  if (EFI_ERROR (Status)) {
    DestroyMenuPage (Page);
    return Status;
  }
  //
  // Display the main menu
  //
  MenuPageRefresh (Page);

  //
  //If start from recovery, remind user to continue running
  //
  if (!IsTestFinished ()) {
    //
    //Execution was not finished in last time. Display yes or no dialog
    //
    DialogContext.Type = EFI_DIALOG_TYPE_YES_OR_NO;

    //
    //Set Yes as default choise
    //
    DialogContext.ChooseNumber = EFI_DIALOG_SELECT_YES;
    DialogTitle = StrDuplicate (L"Continue Run?");

    //
    //Display ask dialog
    //
    DoDialog (DialogTitle, &DialogContext);

    if (DialogContext.ChooseNumber == EFI_DIALOG_SELECT_YES) {

      //
      //Change to running background
      //
      ST->ConOut->SetAttribute (
                    ST->ConOut,
                    EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                    );
      ST->ConOut->ClearScreen (ST->ConOut);
      Status = SctContinueExecute ();
      gContinueExec = FALSE;
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Continue execute - %r", Status));
      }
    } else {

      //
      //user choose not to continue run immediatly, set global flag, let user to
      //continue run later
      //
      gContinueExec = TRUE;
    }
    MenuPageRefresh (Page);
  } else {

    //
    //not start from recovery mode
    //
    gContinueExec = FALSE;
  }

  //
  // Start to handle input keys
  //
  MenuPageKeyInput ();

  return EFI_SUCCESS;
}

EFI_STATUS
MainMenuEnterFunc (
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle Enter key in main menu

Arguments:

  Page          - A pointer to the menu

Reutrns

  EFI_SUCCESS   - Handle Enter key successfully
  Other Value   - Something failed

--*/
{
  //
  // Based on current selected item, display different menu page
  //
  switch ((UINTN)Page->Body.CurrentSelected->Context) {
    case EFI_MENU_ITEM_CONFIG:
      DisplayConfigMenu (Page);
      break;

    case EFI_MENU_ITEM_CASE_MANAGEMENT:
      DisplayTestNodeMenu (&gFT->TestNodeList, Page);
      break;

    case EFI_MENU_ITEM_REPORT_GENERATOR:
      DisplayReportGenerator(Page);
      break;

    case EFI_MENU_ITEM_VIEW_LOG:
      DisplayLog(Page);
      break;

    case EFI_MENU_ITEM_UTILITY:
      break;

    default:  // Error
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
MainMenuEscFunc (
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle ESC key in main menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle ESC key successfully
  Other Value   - Something failed

--*/
{
  //
  // Destroy the main menu page
  //
  DestroyMenuPage (Page);

  //
  // Stop to handle input keys, and exit menu system
  //
  gMenuExit = TRUE;

  return EFI_SUCCESS;
}

VOID
DisplayReportGenerator(
  IN EFI_MENU_PAGE                *Page
  )
{

  EFI_STATUS               Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;
  CHAR16                  *LogFilePath;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID *)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return;
  }

  BS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_SAVE_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_CSV;

  //
  //get filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = StrDuplicate (L"Generate Report Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
      && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (StrLen (DialogContext->FileName) > 4 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 4, L".csv") == 0) {
      FileName = StrDuplicate (DialogContext->FileName);
    } else if ( StrLen (DialogContext->FileName) > 1 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 1, L".") == 0) {
      FileName = PoolPrint (L"%scsv", DialogContext->FileName);
    } else {
      FileName = PoolPrint (L"%s.csv", DialogContext->FileName);
    }
    if (FileName == NULL) {
      BS->FreePool (DialogContext->DevicePath);
      BS->FreePool (DialogContext->FileName);
      BS->FreePool (DialogContext);
      return;
    }

    MsgDialogTitle = StrDuplicate (L"Wait a few minutes...");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    LogFilePath = PoolPrint (
                    L"%s\\%s",
                    gFT->FilePath,
                    EFI_SCT_PATH_LOG
                    );
    if (LogFilePath == NULL) {
      return;
    }

    //
    // Generate the report file
    //
    Status = GenerateReport (
               gFT->DevicePath,
               LogFilePath,
               DialogContext->DevicePath,
               FileName
               );

    if (EFI_ERROR (Status)) {
      MsgDialogTitle = StrDuplicate (L"Generate Report Error!");
    } else {
      MsgDialogTitle = StrDuplicate (L"Generate Report Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;

    DoDialog (MsgDialogTitle, &MsgDialogContext);

    BS->FreePool (FileName);
    BS->FreePool (DialogContext->DevicePath);
    BS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      BS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      BS->FreePool (DialogContext->DevicePath);
    }
  }

  BS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return;
}


VOID
DisplayLog (
  IN EFI_MENU_PAGE                *Page
  )
{

  EFI_STATUS               Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;
  CHAR16                  *CmdLine;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID *)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return;
  }

  BS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_LOG;

  //
  //get filename through FileDialog
  //
  Status = DoLogFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = StrDuplicate (L"Display Log Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
      && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (StrLen (DialogContext->FileName) > 4 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 4, L".log") == 0) {
      FileName = StrDuplicate (DialogContext->FileName);
    }else if ( StrLen (DialogContext->FileName) > 1 &&
       StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 1, L".") == 0) {
       FileName = PoolPrint (L"%slog", DialogContext->FileName);
    }else {
      FileName = PoolPrint (L"%s.log", DialogContext->FileName);
    }
    if (FileName == NULL) {
      BS->FreePool (DialogContext->DevicePath);
      BS->FreePool (DialogContext->FileName);
      BS->FreePool (DialogContext);
      return;
    }

    MsgDialogTitle = StrDuplicate (L"Wait a few minutes...");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;

    //
    //set default Console Attribute and clear the screen
    //
    ST->ConOut->SetAttribute (ST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
    ST->ConOut->ClearScreen (ST->ConOut);

    CmdLine = PoolPrint (L"%s \"%s\"", gFT->ConfigData->EditCommandString, FileName);
    if (CmdLine != NULL) {
      Status = ShellExecute (
                 gFT->ImageHandle,
                 CmdLine,
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        MsgDialogTitle = StrDuplicate (L"Cannot open the log file! Please check the edit command in the configuration page.");
        MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;

        DoDialog (MsgDialogTitle, &MsgDialogContext);
      }

      BS->FreePool (CmdLine);
    }

    BS->FreePool (FileName);
    BS->FreePool (DialogContext->DevicePath);
    BS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      BS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      BS->FreePool (DialogContext->DevicePath);
    }
  }

  BS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return;
}

EFI_STATUS
MainMenuLoadSeqFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS              Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID *)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  BS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_OPEN_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_SEQ;

  //
  //get filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = StrDuplicate (L"Load Sequence Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
    && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    FileName = StrDuplicate (DialogContext->FileName);
    if (FileName == NULL) {
      BS->FreePool (DialogContext->DevicePath);
      BS->FreePool (DialogContext->FileName);
      BS->FreePool (DialogContext);
      return EFI_DEVICE_ERROR;
    }

    Status = ResetTestCaseOrder ();

    Status = LoadTestSequence (
               gFT->DevicePath,
               FileName,
               &gFT->TestCaseList
               );
    if (EFI_ERROR (Status)) {
      MsgDialogTitle = StrDuplicate (L"Load Sequence Error!");
    } else {
      MsgDialogTitle = StrDuplicate (L"Load Sequence Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    BS->FreePool (FileName);
    BS->FreePool (DialogContext->DevicePath);
    BS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      BS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      BS->FreePool (DialogContext->DevicePath);
    }
  }

  BS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return EFI_SUCCESS;
}


EFI_STATUS
MainMenuSaveSeqFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS              Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID *)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  BS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_SAVE_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_SEQ;

  //
  //get devicepath and filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = StrDuplicate (L"Save Sequence Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
    && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (StrLen (DialogContext->FileName) > 4 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 4, L".seq") == 0) {
      FileName = StrDuplicate (DialogContext->FileName);
    }else if ( StrLen (DialogContext->FileName) > 1 &&
       StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 1, L".") == 0) {
       FileName = PoolPrint (L"%sseq", DialogContext->FileName);
    }else {
      FileName = PoolPrint (L"%s.seq", DialogContext->FileName);
    }
    if (FileName == NULL) {
      BS->FreePool (DialogContext->DevicePath);
      BS->FreePool (DialogContext->FileName);
      BS->FreePool (DialogContext);
      return EFI_DEVICE_ERROR;
    }

    Status = SaveTestSequence (
               gFT->DevicePath,
               FileName,
               &gFT->TestCaseList
               );
    if (EFI_ERROR (Status)) {
      MsgDialogTitle = StrDuplicate (L"Save sequence Error!");
    } else {
      MsgDialogTitle = StrDuplicate (L"Save sequence Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    BS->FreePool (FileName);
    BS->FreePool (DialogContext->DevicePath);
    BS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      BS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      BS->FreePool (DialogContext->DevicePath);
    }
  }

  BS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return EFI_SUCCESS;
}

EFI_STATUS
MainMenuF9Func(
  IN EFI_MENU_PAGE                *Page
  )
/*++

Routine Description:

  Handle F9 key in case menu

Arguments:

  Page          - A pointer to the menu

Returns:

  EFI_SUCCESS   - Handle Space key successfully
  Other Value   - Something failed

--*/
{
  EFI_STATUS                Status;
  EFI_INPUT_KEY             Key;
  EFI_DIALOG_CONTEXT        MsgDialogContext;
  CHAR16                   *MsgDialogTitle;

  //
  //check parameter.
  //
  if (Page == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MsgDialogTitle = StrDuplicate (L"Prepare running...");
  MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
  DoDialog (MsgDialogTitle, &MsgDialogContext);

  ST->ConOut->SetAttribute (
                ST->ConOut,
                EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK
                );
  ST->ConOut->ClearScreen (ST->ConOut);

  Status = SctExecute ();
  if (Status != EFI_SUCCESS) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Execute - %r", Status));
  }

  //
  //Clear surplus key stroke.
  //
  Status = EFI_SUCCESS;
  while(!EFI_ERROR(Status)) {
    Status = ST->ConIn->ReadKeyStroke (ST->ConIn, &Key);
  }

  MenuPageRefresh (Page);
  return Status;
}

EFI_STATUS
MainMenuClearFunc (
  IN EFI_MENU_PAGE                *Page
  )
{
  EFI_STATUS               Status;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;

  MsgDialogTitle = StrDuplicate (L"Deleting files ...");
  MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;

  DoDialog (MsgDialogTitle, &MsgDialogContext);

  Status = ResetAllTestResults ();
  MenuPageRefresh (Page);
  if (EFI_ERROR(Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test results - %r", Status));
    return Status;
  }

  gContinueExec = FALSE;
  return EFI_SUCCESS;
}
