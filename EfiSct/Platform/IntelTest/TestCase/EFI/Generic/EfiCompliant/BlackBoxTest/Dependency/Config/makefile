#/*++
#
# Copyright (c) 2005, Intel Corporation
# All rights reserved. This program and the accompanying materials
# are licensed and made available under the terms and conditions of the Eclipse Public License
# which accompanies this distribution.  The full text of the license may be found at
# http://www.opensource.org/licenses/eclipse-1.0.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
# Module Name:
#
#   makefile
#
# Abstract:
#
#   This is the makefile for creating an INI file.
#
#--*/


#
# Define some useful macros, then include the master Efi toolchain setup
# file.
#
BIN_DIR     = $(BUILD_DIR)\$(PROCESSOR)
TOOLCHAIN   = TOOLCHAIN_$(PROCESSOR)

!INCLUDE $(BUILD_DIR)\PlatformTools.env

#
# We simply copy the INI file from the source directory to the build directory
#
$(BIN_DIR)\$(BASE_NAME).ini : $(SOURCE_DIR)\EfiCompliant.ini
  copy $(SOURCE_DIR)\EfiCompliant.ini $(BIN_DIR)\$(BASE_NAME).ini /y

all : $(BIN_DIR)\$(BASE_NAME).ini
