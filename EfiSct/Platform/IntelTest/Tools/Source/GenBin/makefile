#/*++
#
# Copyright 2005, Intel Corporation
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
#   Makefile
#
# Abstract:
#
#   This file is used to build the EFI test build tool.
#
#--*/

#
# Do this if you want to compile from this directory
#
!IFNDEF TOOLCHAIN
TOOLCHAIN = TOOLCHAIN_MSVC
!ENDIF

!INCLUDE PlatformTools.env

#
# Common information
#

INC=$(INC)

#
# Target specific information
#

TARGET_NAME       = GenBin

TARGET_EXE        = $(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).exe

TARGET_SOURCE_DIR = $(TEST_TOOLS_SOURCE)\$(TARGET_NAME)
TARGET_EXE_SOURCE = $(TARGET_SOURCE_DIR)\$(TARGET_NAME).c

#
# Build targets
#

all: $(TARGET_EXE)

#
# Build EXE
#

$(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).obj: $(TARGET_EXE_SOURCE)
  $(CC) $(C_FLAGS) $(INC) $(TARGET_EXE_SOURCE) /Fo$(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).obj

$(TARGET_EXE): $(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).obj
  $(LINK) $(MSVS_LINK_LIBPATHS) $(L_FLAGS) $(LIBS) /out:$(TARGET_EXE) $(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).obj

clean:
  @if exist $(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).* del $(TEST_TOOLS_OUTPUT)\$(TARGET_NAME).* > NUL
