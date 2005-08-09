/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  DiskIoProtocol.h

Abstract:

  Disk I/O Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_DISK_IO_FOR_TEST_H_
#define _EFI_DISK_IO_FOR_TEST_H_

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_DISK_IO_PROTOCOL_GUID \
  { 0xce345171, 0xba0b, 0x11d2,  0x8e, 0x4f, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

EFI_FORWARD_DECLARATION(EFI_DISK_IO);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ) (
  IN EFI_DISK_IO                  *This,
  IN UINT32                       MediaId,
  IN UINT64                       Offset,
  IN UINTN                        BufferSize,
  OUT VOID                        *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE) (
  IN EFI_DISK_IO                  *This,
  IN UINT32                       MediaId,
  IN UINT64                       Offset,
  IN UINTN                        BufferSize,
  IN VOID                         *Buffer
  );

typedef struct _EFI_DISK_IO {
  UINT64                          Revision;
  EFI_DISK_READ                   ReadDisk;
  EFI_DISK_WRITE                  WriteDisk;
} EFI_DISK_IO_PROTOCOL;


extern EFI_GUID                           gEfiDiskIoProtocolGuid;

#endif
