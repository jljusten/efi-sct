/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Sct.h

Abstract:

  SCT master include file.

--*/

#ifndef _EFI_SCT_H_
#define _EFI_SCT_H_

//
// Includes
//

#include "Efi.h"
#include "EfiShellLib.h"
#include "EfiTest.h"
#include "EfiTestLib.h"
#include "LibPrivate.h"
#include EFI_TEST_PROTOCOL_DEFINITION (BbTest)
#include EFI_TEST_PROTOCOL_DEFINITION (WbTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestLoggingLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestOutputLibrary)

#include "ApTest.h"

#include "SctTypes.h"
#include "SctCore.h"
#include "SctData.h"
#include "SctDataEx.h"
#include "SctDebug.h"
#include "SctExecute.h"
#include "SctLoad.h"
#include "SctMisc.h"
#include "SctOperation.h"
#include "SctOutput.h"
#include "SctReport.h"
#include "SctDeviceConfig.h"
#include "SctUi.h"

#include "SctDef.h"

#endif
