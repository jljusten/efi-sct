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
#   This makefile is used to build the test modules for IPF platforms.
#
#--*/

#
# Everything depends on EFI_SOURCE. Make sure it's defined.
#
!IFNDEF EFI_SOURCE
!ERROR EFI_SOURCE environmental variable not set
!ENDIF

#
# Include the platform-specific settings file
#
!INCLUDE PlatformTools.env

PROCESSOR=IPF

#
# Default target to build EFI SCT package
#
all : efi_sct

#
# Build EFI SCT package
#
efi_sct : build_tools makefiles builds efi_framework

#
# Build IHV SCT package
#
ihv_sct : build_tools makefiles builds ihv_framework

#
# Make all the build tools by calling the makefile
#
build_tools :
  $(MAKE) -f $(EDK_TOOLS_SOURCE)\makefile PROCESSOR=$(PROCESSOR) TOOLCHAIN=TOOLCHAIN_MSVC EDK_SOURCE=$(EDK_SOURCE) BUILD_DIR=$(BUILD_DIR)
  $(MAKE) -f $(TEST_TOOLS_SOURCE)\makefile PROCESSOR=$(PROCESSOR) TOOLCHAIN=TOOLCHAIN_MSVC EDK_SOURCE=$(EDK_SOURCE) BUILD_DIR=$(BUILD_DIR)
  $(GUIDCHK) -b $(EDK_TOOLS_OUTPUT)\GuidDatabase.txt

#
# Run ProcessDsc on our main description files to generate the
# makefiles and package files. Specify -v option for more verbose output.
# Specify "-xref filename" to generate a cross-reference file of
# basename-to-fileguid that can be used by VolInfo
#
makefiles :
  $(PROCESSDSC)                             \
    -d EDK_SOURCE=$(EDK_SOURCE)             \
    -d EFI_SOURCE=$(EFI_SOURCE)             \
    -d PROCESSOR=$(PROCESSOR)               \
    -d PROJECT_NAME=$(PROJECT_NAME)         \
    -d PROJECT_FAMILY=$(PROJECT_FAMILY)     \
    -g $(EDK_TOOLS_OUTPUT)\GuidDatabase.txt \
    -d OEMTOOLPATH=$(EDK_TOOLS_OUTPUT)      \
    $(PROJECT_NAME).dsc

#
# Call all the makefiles that were generated by ProcessDsc. ProcessDsc
# creates the makefile.out that calls all the component makefiles.
#
builds :
  $(MAKE) -f makefile.out

#
# Generate the test suite and test cases
#
efi_framework :
  GenFramework.bat efi_sct

ihv_framework :
  GenFramework.bat ihv_sct

#
# Create a target to clean up all build directories
#
clean :
  - @if exist vc??.* del vc??.* > NUL
  - @if exist *.bak del *.bak > NUL
  - @if exist ia32 rd /s/q ia32 > NUL
  - @if exist ipf rd /s /q ipf > NUL
  - @if exist ebc rd /s /q ebc > NUL
  - @if exist x64 rd /s /q x64 > NUL
  - @if exist fv rd /s /q fv > NUL
  - @if exist Tools rd /s /q Tools > NUL
  - @if exist SctPackage rd /s /q SctPackage > NUL
  - @if exist Framework rd /s /q Framework > NUL
  - @if exist makefile.out del makefile.out > NUL
  - @echo All targets cleaned
