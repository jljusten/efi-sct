/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  Perf.c

Abstract:

  Support for Performance primatives.

--*/

#include "Efi.h"
#include "EfiTestUtilitylib.h"
#include EFI_PROTOCOL_DEFINITION(Performance)

EFI_PERFORMANCE_PROTOCOL *Perf=NULL;
EFI_GUID gEfiPerformanceProtocolGuid2 = EFI_PERFORMANCE_PROTOCOL_GUID;


EFI_STATUS
StartMeasure (
  EFI_HANDLE         Handle,
  IN UINT16           *Token,
  IN UINT16           *Host,
  IN UINT64           Ticker
  )
{
  EFI_STATUS Status;
  if ( !Perf ) {
    Status = tBS->LocateProtocol ( &gEfiPerformanceProtocolGuid2,
                                  NULL,
                                  (VOID **)&Perf);
    if ( Status != EFI_SUCCESS ) {
      return Status;
    }
  }

  return (Perf -> StartGauge)( Perf, Handle, Token, Host, Ticker);
}


EFI_STATUS
EndMeasure (
  EFI_HANDLE         Handle,
  IN UINT16           *Token,
  IN UINT16           *Host,
  IN UINT64           Ticker
  )
{
  EFI_STATUS Status;
  if ( !Perf ) {
    Status = tBS->LocateProtocol ( &gEfiPerformanceProtocolGuid2,
                                  NULL,
                                  (VOID **)&Perf);
    if ( Status != EFI_SUCCESS ) {
      return Status;
    }
  }

  return (Perf->EndGauge)( Perf, Handle, Token, Host, Ticker) ;
}








