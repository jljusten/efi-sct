/*++

Copyright 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  SctExecute.h

Abstract:

  This file provides the test execution services.

--*/

#ifndef _EFI_SCT_EXECUTE_H_
#define _EFI_SCT_EXECUTE_H_

//
// External functions declaration
//

//
// Execution services
//

EFI_STATUS
SctExecutePrepare (
  VOID
  );

EFI_STATUS
SctExecuteStart (
  VOID
  );

EFI_STATUS
SctExecute (
  VOID
  );

EFI_STATUS
SctContinueExecute (
  VOID
  );

//
// Reset services
//

EFI_STATUS
RemoveRecoveryFile (
  VOID
  );

EFI_STATUS
ResetAllTestResults (
  VOID
  );

#endif
