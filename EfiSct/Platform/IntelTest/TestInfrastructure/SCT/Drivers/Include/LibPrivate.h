/*++

Copyright (c) 2005, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the Eclipse Public License
which accompanies this distribution.  The full text of the license may be found at
http://www.opensource.org/licenses/eclipse-1.0.php

THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  LibPrivate.h

Abstract:

  This file defines the private interfaces of the test support libraries. Only
  the test management system can invokes these private interfaces to initialize
  and configure the test support libraries.

--*/

#ifndef _EFI_LIB_PRIVATE_H_
#define _EFI_LIB_PRIVATE_H_

//
// Includes
//
#include "Efi.h"
#include "EfiTest.h"
#include "LibConfig.h"
#include EFI_TEST_PROTOCOL_DEFINITION (TslInit)

//
// Private interface for each test support library
//

#define TSL_INIT_PRIVATE_DATA_SIGNATURE     EFI_SIGNATURE_32('T','S','L','I')

typedef struct {
  UINT32                              Signature;
  EFI_HANDLE                          ImageHandle;
  EFI_TSL_INIT_INTERFACE              TslInit;
} TSL_INIT_PRIVATE_DATA;

#define TSL_INIT_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, TSL_INIT_PRIVATE_DATA, TslInit, TSL_INIT_PRIVATE_DATA_SIGNATURE)

//
// Standard test library's private interface
//

EFI_FORWARD_DECLARATION(EFI_STANDARD_TSL_PRIVATE_INTERFACE);

typedef
EFI_STATUS
(EFIAPI * EFI_STSL_SET_CONFIG) (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  );

typedef
EFI_STATUS
(EFIAPI * EFI_STSL_BEGIN_LOGGING) (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This
  );

typedef
EFI_STATUS
(EFIAPI * EFI_STSL_END_LOGGING) (
  IN EFI_STANDARD_TSL_PRIVATE_INTERFACE     *This,
  IN EFI_STATUS                             TestStatus
  );

typedef struct _EFI_STANDARD_TSL_PRIVATE_INTERFACE {
  EFI_STSL_SET_CONFIG                       SetConfig;
  EFI_STSL_BEGIN_LOGGING                    BeginLogging;
  EFI_STSL_END_LOGGING                      EndLogging;
} EFI_STANDARD_TSL_PRIVATE_INTERFACE;

//
// Test logging library's private interface
//

EFI_FORWARD_DECLARATION(EFI_TLL_PRIVATE_INTERFACE);

typedef
EFI_STATUS
(EFIAPI * EFI_TLL_SET_CONFIG) (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_LIB_CONFIG_DATA                    *Config
  );

typedef
EFI_STATUS
(EFIAPI * EFI_TLL_BEGIN_LOGGING) (
  IN EFI_TLL_PRIVATE_INTERFACE              *This
  );

typedef
EFI_STATUS
(EFIAPI * EFI_TLL_END_LOGGING) (
  IN EFI_TLL_PRIVATE_INTERFACE              *This,
  IN EFI_STATUS                             TestStatus
  );

typedef struct _EFI_TLL_PRIVATE_INTERFACE {
  EFI_TLL_SET_CONFIG                        SetConfig;
  EFI_TLL_BEGIN_LOGGING                     BeginLogging;
  EFI_TLL_END_LOGGING                       EndLogging;
} EFI_TLL_PRIVATE_INTERFACE;

//
// Test recovery library's private interface
//

EFI_FORWARD_DECLARATION(EFI_TRL_PRIVATE_INTERFACE);

typedef
EFI_STATUS
(EFIAPI * EFI_TRL_SET_CONFIG) (
  IN EFI_TRL_PRIVATE_INTERFACE              *This,
  IN EFI_DEVICE_PATH_PROTOCOL               *DevicePath,
  IN CHAR16                                 *FileName
  );

typedef struct _EFI_TRL_PRIVATE_INTERFACE {
  EFI_TRL_SET_CONFIG                        SetConfig;
} EFI_TRL_PRIVATE_INTERFACE;

#endif
