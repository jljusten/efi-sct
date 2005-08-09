/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DecompressProtocol.h

Abstract:

  The Decompress Protocol Interface (Just for Test)

--*/

#ifndef _DECOMPRESS_TEST_H_
#define _DECOMPRESS_TEST_H_

#define EFI_DECOMPRESS_PROTOCOL_GUID  \
  { 0xd8117cfe, 0x94a6, 0x11d4, 0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }

EFI_FORWARD_DECLARATION(EFI_DECOMPRESS_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_DECOMPRESS_GET_INFO) (
  IN   EFI_DECOMPRESS_PROTOCOL  *This,
  IN   VOID                     *Source,
  IN   UINT32                   SourceSize,
  OUT  UINT32                   *DestinationSize,
  OUT  UINT32                   *ScratchSize
  );

typedef
EFI_STATUS
(EFIAPI *EFI_DECOMPRESS_DECOMPRESS) (
  IN     EFI_DECOMPRESS_PROTOCOL  *This,
  IN     VOID*                    Source,
  IN     UINT32                   SourceSize,
  IN OUT VOID*                    Destination,
  IN     UINT32                   DestinationSize,
  IN OUT VOID*                    Scratch,
  IN     UINT32                   ScratchSize
  );

typedef struct _EFI_DECOMPRESS_PROTOCOL {
  EFI_DECOMPRESS_GET_INFO    GetInfo;
  EFI_DECOMPRESS_DECOMPRESS  Decompress;
} EFI_DECOMPRESS_PROTOCOL;

extern EFI_GUID gEfiDecompressProtocolGuid;

#endif
