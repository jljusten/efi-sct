/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  TestNodeMenu.h

Abstract:

  Deal with the user interface menu for test nodes.

--*/

#ifndef _EFI_TEST_NODE_MENU_H_
#define _EFI_TEST_NODE_MENU_H_

//
//  Includes
//

#include "Sct.h"
#include "Ui.h"
#include "BuildMenu.h"
#include "Dialog.h"
#include EFI_PROTOCOL_DEFINITION(DevicePath)

//
// Definitions
//

#define ITERATION_NUMBER_MAX     999
#define ITERATION_NUMBER_MIN     0
#define ITERATION_NUMBER_DEFAULT 0

//
// Functions
//

EFI_STATUS
DisplayTestNodeMenu (
  IN EFI_LIST_ENTRY               *Root,
  IN EFI_MENU_PAGE                *ParentPage
  );

UINTN
CalculatePassNumber (
  EFI_SCT_TEST_NODE               *TestNode
  );

UINTN
CalculateTotalPassNumber (
  EFI_LIST_ENTRY                  *Root
  );

UINTN
CalculateFailNumber (
  EFI_SCT_TEST_NODE               *TestNode
  );

UINTN
CalculateTotalFailNumber (
  EFI_LIST_ENTRY                  *Root
  );

UINT32
GetTestCaseIterations (
  IN EFI_GUID                     *Guid
  );

#endif
