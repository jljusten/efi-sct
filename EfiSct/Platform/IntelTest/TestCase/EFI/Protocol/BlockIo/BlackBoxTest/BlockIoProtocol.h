/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  BlockIoProtocol.h

Abstract:

  Block I/O Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_BLOCK_IO_FOR_TEST_H_
#define _EFI_BLOCK_IO_FOR_TEST_H_

//
// Prevent the original BlockIo.h is included
//
#define  __BLOCK_IO_H__

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_BLOCK_IO_PROTOCOL_GUID \
  { 0x964e5b21, 0x6459, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

EFI_FORWARD_DECLARATION(EFI_BLOCK_IO);

typedef struct {
  UINT32              MediaId;
  BOOLEAN             RemovableMedia;
  BOOLEAN             MediaPresent;

  BOOLEAN             LogicalPartition;
  BOOLEAN             ReadOnly;
  BOOLEAN             WriteCaching;

  UINT32              BlockSize;
  UINT32              IoAlign;

  EFI_LBA             LastBlock;
} EFI_BLOCK_IO_MEDIA;

typedef UINT64          EFI_LBA;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET) (
  IN EFI_BLOCK_IO   *This,
  IN BOOLEAN                ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ) (
  IN EFI_BLOCK_IO   *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                LBA,
  IN UINTN                  BufferSize,
  OUT VOID                  *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE) (
  IN EFI_BLOCK_IO   *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                LBA,
  IN UINTN                  BufferSize,
  IN VOID                   *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH) (
  IN EFI_BLOCK_IO   *This
  );

typedef struct _EFI_BLOCK_IO {
  UINT64                    Revision;
  EFI_BLOCK_IO_MEDIA        *Media;
  EFI_BLOCK_RESET           Reset;
  EFI_BLOCK_READ            ReadBlocks;
  EFI_BLOCK_WRITE           WriteBlocks;
  EFI_BLOCK_FLUSH           FlushBlocks;
} EFI_BLOCK_IO_PROTOCOL;


extern EFI_GUID                           gEfiBlockIoProtocolGuid;

#endif
