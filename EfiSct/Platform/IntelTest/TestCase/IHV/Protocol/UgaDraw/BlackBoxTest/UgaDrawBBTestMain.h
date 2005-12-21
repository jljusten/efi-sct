/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  UgaDrawBBTestMain.h

Abstract:

  BB test header file of UGA Draw Protocol

--*/


#ifndef _UGA_DRAW_BBTEST_H_
#define _UGA_DRAW_BBTEST_H_

#define TEST_CHIPSET_UGA_ONLY_NO
#define LOAD_INTEL_LOG

#include "Efi.h"
#include "Guid.h"
//#include "UgaDrawProtocol.h"
//#define  __UGA_DRAW_H__

#include "EfiTestUtilityLib.h"
#include "EfiDriverLib.h"
#include "EfiTestLib.h"
#include "EfiCommonLib.h"
#include EFI_PROTOCOL_DEFINITION (ConsoleControl)
#include EFI_PROTOCOL_DEFINITION (UgaDraw)
#include EFI_PROTOCOL_DEFINITION (UgaSplash)
#include EFI_PROTOCOL_DEFINITION (FirmwareVolume)

#include EFI_TEST_PROTOCOL_DEFINITION (BBTest)
#include EFI_TEST_PROTOCOL_DEFINITION (StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

#include EFI_GUID_DEFINITION (Bmp)

#define  UGA_DRAW_PROTOCOL_TEST_REVISION    0x00010000

#define  IHV_UGA_DRAW_PROTOCOL_GUID         \
  { 0x7fe24dea, 0xdc99, 0x46ee, 0x8e, 0x1e, 0x4e, 0xc3, 0x32, 0x31, 0xd4, 0x85 }


#define  DEMO_WIDTH_HEIGHT_ENUM             2
#define  DEMO_SOURCE_POSITION_ENUM          3
#define  DEMO_DESTINATION_POSITION_ENUM     3
#define  DEMO_DELTA_ENUM                    4

#define  STEP_WIDTH                         50
#define  STEP_WIDTH_BUFFER                  100
#define  MAX_SCREEN_WIDTH                   800
#define  MAX_SCREEN_HEIGHT                  600

typedef
struct _DEMO_RESOLUTION_TYPE {
  UINT32 HorizontalResolution;
  UINT32 VerticalResolution;
} DEMO_RESOLUTION_TYPE;

typedef  UINT32 DEMO_REFRESH_RATE_TYPE;
typedef  UINT32 DEMO_COLOR_DEPTH_TYPE;


extern   EFI_EVENT                TimerEvent;
extern   DEMO_RESOLUTION_TYPE     DemoResolution[]  ;
extern   DEMO_REFRESH_RATE_TYPE   DemoRefreshRate[] ;
extern   DEMO_COLOR_DEPTH_TYPE    DemoColorDepth[]  ;

extern   UINTN                    DemoResolutionMax ;
extern   UINTN                    DemoRefreshRateMax;
extern   UINTN                    DemoColorDepthMax ;

#define  PIXEL(Buffer,Width,i,j)        ((Buffer)+((Width)*(i) + (j)))

EFI_STATUS
InitializeBBTestUgaDraw (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUgaDrawProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

BOOLEAN
IsIhvInterface (
  IN VOID                       *ClientInterface,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoFillFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoBltBufferFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoToVideoFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance function
//
EFI_STATUS
BBTestGetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBltConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Extensive function
//

EFI_STATUS
BBTestVideoFillBufferToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestVideoFillVideoToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestVideoToBltBufferAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoFillStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoBltBufferStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoToVideoStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Associatianal function
//

UINTN
UgaPrintXY (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *String
  );

UINTN
PrintXY (
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *String
  );

UINTN
_IPrint (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Sto,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *Foreground,
  IN EFI_UGA_PIXEL                    *Background,
  IN CHAR16                           *String
  );

VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  ) ;

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

BOOLEAN
AutoJudgeUga(
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

EFI_STATUS
UgaDrawClearScreen(
  IN  EFI_UGA_DRAW_PROTOCOL      *UgaDraw,
  IN  UINT32                     HorizontalResolution,
  IN  UINT32                     VerticalResolution
  );

EFI_STATUS
LoadBmp(
  IN EFI_UGA_PIXEL  **BltBuffer,
  IN UINTN         *Width,
  IN UINTN         *Height
  );

EFI_STATUS
ConvertBmpToUgaBlt (
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth
  );

EFI_STATUS
GetGraphicsBitMapFromFV (
  IN  EFI_GUID      *FileNameGuid,
  OUT VOID          **Image,
  OUT UINTN         *ImageSize
  );

VOID
GetTestData(
  IN  UINTN         Index,
  IN  UINTN        *Width,
  IN  UINTN        *Height,
  IN  UINTN        *SourceX,
  IN  UINTN        *SourceY,
  IN  UINTN        *DestinationX,
  IN  UINTN        *DestinationY,
  IN  UINTN        *Delta,
  IN  UINT32       HorizontalResolution,
  IN  UINT32       VerticalResolution
  );

EFI_STATUS
OutputScreen(
  IN EFI_UGA_DRAW_PROTOCOL   *UgaDraw,
  IN UINTN                   SourceX,
  IN UINTN                   SourceY,
  IN UINTN                   DestinationX,
  IN UINTN                   DestinationY
  );

EFI_STATUS
LocateDevicePathFromUgaDraw(
  IN EFI_UGA_DRAW_PROTOCOL                *UgaDraw,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Entry GUIDs
//

#define UGA_DRAW_PROTOCOL_GETMODE_FUNCTION_AUTO_GUID \
  { 0x9149a710, 0x4a72, 0x4b66, 0x9c, 0x1c, 0x96, 0x36, 0x81, 0x02, 0x2a, 0x2a }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_FUNCTION_AUTO_GUID \
  { 0xcbb0cbea, 0xee26, 0x450e, 0xb3, 0xf7, 0x3d, 0x45, 0xd8, 0xb3, 0x89, 0x1f }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_FUNCTION_AUTO_GUID\
  { 0x39f1dc1c, 0x9ad9, 0x4b57, 0x9b, 0xb3, 0xdb, 0xd9, 0xc6, 0xc7, 0x4f, 0x4d }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_FUNCTION_AUTO_GUID\
  { 0x514b28be, 0x76d2, 0x4d32, 0xbf, 0x93, 0x65, 0xf0, 0x02, 0x80, 0xad, 0x3b }


//
// Conformance Test GUID
//

#define UGA_DRAW_PROTOCOL_GETMODE_CONFORMANCE_AUTO_GUID\
  { 0xbea65803, 0x270f, 0x42c2, 0x8a, 0xe0, 0x6f, 0xda, 0x98, 0xf1, 0xde, 0xf1 }

#define UGA_DRAW_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID\
  { 0xbd2a158d, 0x53cd, 0x4304, 0xa6, 0xa9, 0x4f, 0x7a, 0x71, 0x1a, 0x1f, 0x05 }

//
// Extensive Test Guid
//
#define UGA_DRAW_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID\
  { 0xd29c2bcd, 0xeccb, 0x45e1, 0x9a, 0x96, 0x54, 0x91, 0x80, 0xca, 0xa9, 0x4c }

#define UGA_DRAW_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID\
  { 0x2f9e7e94, 0xd382, 0x42e5, 0x95, 0x1e, 0xdb, 0xcf, 0x31, 0xeb, 0x0e, 0x8f }

#define UGA_DRAW_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID\
  { 0x01ccde0e, 0x2433, 0x4896, 0x9f, 0xbd, 0xd0, 0xea, 0x94, 0x23, 0xaf, 0x85 }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_STRESS_AUTO_GUID \
  { 0x1dbd26c7, 0x6217, 0x413f, 0x83, 0x79, 0xdc, 0xb8, 0xfb, 0xd0, 0xef, 0xb6 }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_STRESS_AUTO_GUID\
  { 0xb0531f65, 0x19e0, 0x4d85, 0x99, 0xa5, 0x9b, 0xe8, 0x1d, 0xcf, 0xf1, 0x35 }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_STRESS_AUTO_GUID\
  { 0xb4de7972, 0x0657, 0x4bfb, 0xae, 0x17, 0x23, 0x1e, 0x2f, 0x43, 0x7d, 0xcb }


#endif

