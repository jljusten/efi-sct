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
#   Makefile
#
# Abstract:
#
#   This file is used to build the EFI test build tools.
#
#--*/

#
# Everything depends on EDK_SOURCE. Make sure it's defined
#
!IFNDEF EDK_SOURCE
!ERROR EDK_SOURCE environmental variable not set
!ENDIF

!INCLUDE PlatformTools.env

#
# Define our toolchain before we include the master settings file
#
TOOLCHAIN = TOOLCHAIN_MSVC

#
# Define all the makefiles we want to call
#

MAKEFILES = $(TEST_TOOLS_SOURCE)\GenBin\Makefile        \
            $(TEST_TOOLS_SOURCE)\GenProfile\Makefile

#
# Define default all target which calls all our makefiles. The special
# bang (!) tells nmake to do the command for each out-of-date dependent.
#
# Create the BIN directory, which will only exist if you pull the source tree
# from version control.
#
all : $(MAKEFILES)
  -if not exist $(TEST_TOOLS_OUTPUT) mkdir $(TEST_TOOLS_OUTPUT)
  !$(MAKE) -f $? TOOLCHAIN=$(TOOLCHAIN) all

#
# Call all the tools makefiles with a clean target.
#
clean : $(MAKEFILES)
  !$(MAKE) -f $? TOOLCHAIN=$(TOOLCHAIN) clean
