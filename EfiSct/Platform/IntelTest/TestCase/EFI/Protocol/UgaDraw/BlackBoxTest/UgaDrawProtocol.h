/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UgaDrawProtocol.h

Abstract:

  UgaDraw Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_UGA_DRAW_FOR_TEST_H_
#define _EFI_UGA_DRAW_FOR_TEST_H_

#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define EFI_UGA_DRAW_PROTOCOL_GUID \
  { 0x982c298b, 0xf4fa, 0x41cb, 0xb8, 0x38, 0x77, 0xaa, 0x68, 0x8f, 0xb8, 0x39 }

EFI_FORWARD_DECLARATION(EFI_UGA_DRAW_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_GET_MODE) (
  IN  EFI_UGA_DRAW_PROTOCOL   *This,
  OUT UINT32                  *HorisontalResolution,
  OUT UINT32                  *VirticalResolution,
  OUT UINT32                  *ColorDepth,
  OUT UINT32                  *RefreshRate
  );

typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_SET_MODE) (
  IN EFI_UGA_DRAW_PROTOCOL    *This,
  IN UINT32                   HorisontalResolution,
  IN UINT32                   VirticalResolution,
  IN UINT32                   ColorDepth,
  IN UINT32                   RefreshRate
  );

typedef struct {
  UINT8   Blue;
  UINT8   Green;
  UINT8   Red;
  UINT8   Reserved;
} EFI_UGA_PIXEL;

typedef enum {
  EfiUgaVideoFill,
  EfiUgaVideoToBltBuffer,
  EfiUgaBltBufferToVideo,
  EfiUgaVideoToVideo,
  EfiUgaBltMax
} EFI_UGA_BLT_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_BLT) (
  IN EFI_UGA_DRAW_PROTOCOL    *This,
  IN INTN                     X,
  IN INTN                     Y,
  IN UINTN                    Width,
  IN UINTN                    Height,
  IN EFI_UGA_BLT_OPERATION    BltOperation,
  IN EFI_UGA_PIXEL            *BltBuffer,   OPTIONAL
  IN UINTN                    SourceX,      OPTIONAL
  IN UINTN                    SourceY       OPTIONAL
  );

typedef
struct _EFI_UGA_DRAW_PROTCOL {
  EFI_UGA_DRAW_PROTOCOL_GET_MODE        GetMode;
  EFI_UGA_DRAW_PROTOCOL_SET_MODE        SetMode;
  EFI_UGA_DRAW_PROTOCOL_BLT             Blt;
} EFI_UGA_DRAW_PROTOCOL;


extern EFI_GUID                           gEfiUgaDrawProtocolGuid;

#endif
