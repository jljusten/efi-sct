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
#   Ia32.dsc
#
# Abstract:
#
#   This is a build description file used to build the test modules for IA32
#   platforms.
#
# Notes:
#
#   The info in this file is broken down into sections. The start of a section
#   is designated by a "[" in the first column. So the [=====] separater ends
#   a section.
#
#--*/

[=============================================================================]
#
# This section gets processed first by the ProcessDsc utility. Define any
# macros that you may use elsewhere in this description file. This is the
# mechanism by which you can pass parameters and defines to the makefiles
# generated for each component.
#
[Defines]
PROCESSOR                 = $(PROCESSOR)


[=============================================================================]
#
# The contents of this section get written directly to the makefile.out file
# that calls all the makefiles created for the individual components.
#
[makefile.out]
#
# ORIGIN: [makefile.out] section of the platform DSC file
#

!INCLUDE $(BUILD_DIR)\PlatformTools.env

all : libraries fvs fv_null_components

#
# summary target for components with FV=NULL to handle the case
# when no components exist with FV=NULL
#
fv_null_components ::
  @echo.

[=============================================================================]
#
# The contents of this section get expanded and dumped out to each component
# makefile after the component INF [defines] section of the INF file gets parsed.
#
[Makefile.Common]
#
# ORIGIN: [Makefile.Common] section of the platform DSC file
#
PROCESSOR        = $(PROCESSOR)
BASE_NAME        = $(BASE_NAME)
BUILD_NUMBER     = $(BUILD_NUMBER)
VERSION_STRING   = $(VERSION_STRING)
FILE_GUID        = $(FILE_GUID)
COMPONENT_TYPE   = $(COMPONENT_TYPE)
INF_FILENAME     = $(INF_FILENAME)
PACKAGE_FILENAME = $(PACKAGE_FILENAME)
FV_DIR           = $(BUILD_DIR)\FV
EDK_SOURCE       = $(EFI_SOURCE)\Edk
TOOLCHAIN        = $(TOOLCHAIN)

!IF "$(LANGUAGE)" != ""
LANGUAGE_FLAGS    = -lang $(LANGUAGE)
!ENDIF

!INCLUDE $(BUILD_DIR)\PlatformTools.env

!IF "$(COMPONENT_TYPE)" == "PE32_PEIM" || "$(COMPONENT_TYPE)" == "RELOCATABLE_PEIM" || "$(COMPONENT_TYPE)" == "COMBINED_PEIM_DRIVER"
DEPEX_TYPE = EFI_SECTION_PEI_DEPEX
!ELSE
DEPEX_TYPE = EFI_SECTION_DXE_DEPEX
!ENDIF

!MESSAGE ========== Building $(BASE_NAME) - $(INF_FILENAME)

[=============================================================================]
#
# Commands to compile an IA32, IPF or x64 C source file
#
# To support incremental builds, the MakeDeps tool scans all component source
# files to find #include statements, and then emits dependencies to a file
# that can be included by makefiles. The following build commands will call
# MakeDeps if the output file does not already exist, or simply !include the
# file otherwise. Thus the scan is only done on the first build.
#
[Compile.Ia32.c,Compile.Ipf.c,Compile.x64.c]
#
# ORIGIN: [Compile.$(PROCESSOR).c] section of the platform DSC file
#
DEP_FILE = $(DEST_DIR)\$(FILE).dep

!IF EXIST($(DEP_FILE))
!INCLUDE $(DEP_FILE)
!ENDIF
#
# This is how to create the dependency file the first time
#
$(DEP_FILE) : $(SOURCE_FILE_NAME)
  $(MAKEDEPS) -ignorenotfound -f $(SOURCE_FILE_NAME) -q -target \
    $(DEST_DIR)\$(FILE).obj -o $(DEP_FILE) $(INC)
#
# Compile the source file
#
$(DEST_DIR)\$(FILE).obj : $(SOURCE_FILE_NAME) $(INC_DEPS) $(DEP_FILE)
  $(CC) $(CC_FLAGS) $(SOURCE_FILE_NAME)

[=============================================================================]
[Compile.Ia32.Vfi,Compile.Ipf.Vfi,Compile.Ebc.Vfi,Compile.x64.Vfi]

$(DEST_DIR)\$(FILE).vfi : $(SOURCE_DIR)\$(FILE).vfi
  copy $(SOURCE_DIR)\$(FILE).vfi $(DEST_DIR)\$(FILE).vfi

[=============================================================================]
#
# Commands for compiling an IA32 assembly source file
#
[Compile.Ia32.asm,Compile.x64.asm]

$(DEST_DIR)\$(FILE).obj : $(SOURCE_FILE_NAME)
  $(ASM) $(ASM_FLAGS) $**

[=============================================================================]
#
# Commands for compiling IPF assembly source files
#
[Compile.Ipf.s]

$(DEST_DIR)\$(FILE).pro : $(SOURCE_FILE_NAME)
 $(CC) $(CC_PP_FLAGS) $(SOURCE_FILE_NAME) > $@

$(DEST_DIR)\$(FILE).obj : $(DEST_DIR)\$(FILE).pro
 $(ASM) $(ASM_FLAGS) $(DEST_DIR)\$(FILE).pro

[=============================================================================]
#
# Commands to compile a C source file for EBC
#
[Compile.Ebc.c]
#
# ORIGIN: [Compile.Ebc.c] section of the platform DSC file
#
!IF ("$(NO_MAKEDEPS)" == "")

!IF EXIST($(DEST_DIR)\$(FILE).dep)
!INCLUDE $(DEST_DIR)\$(FILE).dep
!ENDIF

DEP_FILE = $(DEST_DIR)\$(FILE).dep

$(DEP_FILE) : $(SOURCE_FILE_NAME)
  $(MAKEDEPS) -ignorenotfound -f $(SOURCE_FILE_NAME) -q -target \
    $(DEST_DIR)\$(FILE).obj \
    -o $(DEP_FILE) $(INC)

!ENDIF
#
# Redefine the entry point function if an entry point has been defined at all.
# This is required because all EBC entry point functions must be called
# EfiMain.
#
!IF DEFINED(IMAGE_ENTRY_POINT)
!IF "$(IMAGE_ENTRY_POINT)" != "EfiMain"
CC_FLAGS = $(CC_FLAGS) /D $(IMAGE_ENTRY_POINT)=EfiMain
!ENDIF
!ENDIF
#
# This is how to compile the source .c file.
# Use -P to get preprocessor output file (.i)
#
$(DEST_DIR)\$(FILE).obj : $(SOURCE_FILE_NAME) $(INF_FILENAME) $(DEP_FILE)
  $(CC) $(CC_FLAGS) -X $(INC) -Fa$(DEST_DIR)\$(FILE).cod \
    $(SOURCE_FILE_NAME) -Fo$(DEST_DIR)\$(FILE).obj

[=============================================================================]
#
# These are the commands used to build the different types of drivers (after
# the source files have been compiled).
# Since many of the steps are the same for the different component types, we
# share this section for BS_DRIVER, RT_DRIVER, .... and IFDEF the parts that
# differ.  The entire section gets dumped to the output makefile.
#
[=============================================================================]
[Build.Ia32.BS_DRIVER|RT_DRIVER|SAL_RT_DRIVER|PE32_PEIM|PEI_CORE|PIC_PEIM|RELOCATABLE_PEIM|DXE_CORE|APPLICATION|COMBINED_PEIM_DRIVER, Build.Ipf.BS_DRIVER|RT_DRIVER|SAL_RT_DRIVER|PEI_CORE|PE32_PEIM|PIC_PEIM|DXE_CORE|APPLICATION|COMBINED_PEIM_DRIVER,Build.x64.BS_DRIVER|RT_DRIVER|SAL_RT_DRIVER|PE32_PEIM|PEI_CORE|PIC_PEIM|RELOCATABLE_PEIM|DXE_CORE|APPLICATION|COMBINED_PEIM_DRIVER]
#
# ORIGIN: [Build.$(PROCESSOR).???] section of the platform DSC file
#
# If this driver supports localization, then we need to run our tools on
# the string files to build them into the driver.
#
!IF "$(LOCALIZE)" == "YES"

!IF "$(EFI_GENERATE_HII_EXPORT)" == "YES"
STRGATHER_FLAGS   = $(STRGATHER_FLAGS) -hpk $(DEST_DIR)\$(BASE_NAME)Strings.hpk
#
# In the end, we will have one HII pack containing all the strings. Add that file
# to the list of HII pack files we'll use to create our final HII export file.
#
HII_PACK_FILES    = $(HII_PACK_FILES) $(DEST_DIR)\$(BASE_NAME)Strings.hpk
LOCALIZE_TARGETS  = $(LOCALIZE_TARGETS) $(DEST_DIR)\$(BASE_NAME).hii
!ENDIF
#
# This is how we create our final string database file from all the individual
# string database files created during the build.
#
$(DEST_DIR)\$(BASE_NAME).sdb : $(SDB_FILES) $(SOURCE_FILES)
  $(STRGATHER) -scan -vdbr $(STRGATHER_FLAGS) -od $(DEST_DIR)\$(BASE_NAME).sdb \
    -skipext .uni -skipext .h $(SOURCE_FILES)

$(DEST_DIR)\$(BASE_NAME)Strings.c $(DEST_DIR)\$(BASE_NAME)StrDefs.h $(DEST_DIR)\$(BASE_NAME)Strings.hpk : $(DEST_DIR)\$(BASE_NAME).sdb
  $(STRGATHER) -dump $(LANGUAGE_FLAGS) -bn $(BASE_NAME)Strings -db $(DEST_DIR)\$(BASE_NAME).sdb \
    -oc $(DEST_DIR)\$(BASE_NAME)Strings.c -hpk $(DEST_DIR)\$(BASE_NAME)Strings.hpk -oh $(DEST_DIR)\$(BASE_NAME)StrDefs.h

OBJECTS = $(OBJECTS) $(DEST_DIR)\$(BASE_NAME)Strings.obj

$(DEST_DIR)\$(BASE_NAME)Strings.obj : $(DEST_DIR)\$(BASE_NAME)Strings.c
  $(CC) $(C_FLAGS) $(DEST_DIR)\$(BASE_NAME)Strings.c

LOCALIZE_TARGETS = $(LOCALIZE_TARGETS) $(DEST_DIR)\$(BASE_NAME)StrDefs.h

!ENDIF
#
# Defines for standard intermediate files and build targets
#
TARGET_DLL      = $(BIN_DIR)\$(BASE_NAME).dll
TARGET_EFI      = $(BIN_DIR)\$(BASE_NAME).efi
TARGET_DPX      = $(DEST_DIR)\$(BASE_NAME).dpx
TARGET_UI       = $(DEST_DIR)\$(BASE_NAME).ui
TARGET_VER      = $(DEST_DIR)\$(BASE_NAME).ver
TARGET_PDB      = $(PDB_OUTPUT_PATH)\$(BASE_NAME).pdb
TARGET_PE32     = $(DEST_DIR)\$(BASE_NAME).pe32
#
# Define the target output FFS file name
#
#TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).ffs
#
# Define the subsystem to use when linking, and the name of
# the FFS file that will be created by GenFfs file.
#
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER

!IF "$(COMPONENT_TYPE)" == "APPLICATION"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).app
SUBSYSTEM       = EFI_APPLICATION
!ELSE IF "$(COMPONENT_TYPE)" == "PEI_CORE"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).pei
!ELSE IF "$(COMPONENT_TYPE)" == "PE32_PEIM"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).pei
!ELSE IF "$(COMPONENT_TYPE)" == "RELOCATABLE_PEIM"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).pei
!ELSE IF "$(COMPONENT_TYPE)" == "PIC_PEIM"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).pei
!ELSE IF "$(COMPONENT_TYPE)" == "COMBINED_PEIM_DRIVER"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$BASE_NAME).pei
TARGET_DXE_DPX  = $(DEST_DIR)\$(BASE_NAME).dpxd
!ELSE IF "$(COMPONENT_TYPE)" == "RT_DRIVER"
SUBSYSTEM       = EFI_RUNTIME_DRIVER
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).dxe
!ELSE
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).dxe
!ENDIF

#
# If we're building a combined PEIM/Driver, then we potentially
# need two depex sections. Define the target dxe depex section
# only if we need it.
#
!IF "$(COMPONENT_TYPE)" == "COMBINED_PEIM_DRIVER"
TARGET_DXE_DPX  = $(DEST_DIR)\$(BASE_NAME).dpxd
!ENDIF
#
# Link all objects and libs to create the executable *.dll file
#
$(TARGET_DLL) : $(OBJECTS) $(LIBS)
  $(LINK) $(LINK_FLAGS) $(OBJECTS) $(LIBS) /ENTRY:$(IMAGE_ENTRY_POINT) \
     /OUT:$(TARGET_DLL) /PDB:$(TARGET_PDB)

#
# Run FWImage on the .dll file to create the .efi file
#
$(TARGET_EFI) : $(TARGET_DLL)
  $(FWIMAGE) -t 0 $(COMPONENT_TYPE) $(TARGET_DLL) $(TARGET_EFI)
  $(SETSTAMP) $(TARGET_EFI) $(BUILD_DIR)\GenStamp.txt

#
# Run GenSection on the .efi file to create an FFS section file
#
$(TARGET_PE32) : $(TARGET_EFI) $(INF_FILENAME)
  $(GENSECTION) -I $(TARGET_EFI) -O $(TARGET_PE32) -S EFI_SECTION_PE32
#
# Run GenSection to create a user interface section (even if it's not used)
#
$(TARGET_UI) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_UI) -S EFI_SECTION_USER_INTERFACE -A "$(BASE_NAME)"
#
# Run GenSection to create the version section
#

!IF "$(BUILD_NUMBER)" != ""
!IF "$(VERSION_STRING)" != ""
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER) -A "$(VERSION_STRING)"
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER)
!ENDIF
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  echo.>$(TARGET_VER)
  type $(TARGET_VER)>$(TARGET_VER)
!ENDIF

#
# Makefile entries to create the dependency expression section.
# Use the DPX file from the source directory unless an override file
# was specified.
# If no DPX source file was specified, then create an empty file to
# be used.
#
!IF "$(DPX_SOURCE)" != ""
DPX_SOURCE_FILE = $(SOURCE_DIR)\$(DPX_SOURCE)
!ENDIF

!IF "$(DPX_SOURCE_OVERRIDE)" != ""
DPX_SOURCE_FILE = $(DPX_SOURCE_OVERRIDE)
!ENDIF

!IF "$(DPX_SOURCE_FILE)" != ""
!IF EXIST ($(DPX_SOURCE_FILE))
$(TARGET_DPX) : $(DPX_SOURCE_FILE) $(INF_FILENAME)
  $(CC) $(INC) /EP $(DPX_SOURCE_FILE) > $*.tmp1
  $(GENDEPEX) -I $*.tmp1 -O $*.tmp2
  $(GENSECTION) -I $*.tmp2 -O $@ -S $(DEPEX_TYPE)
  del $*.tmp1 > NUL
  del $*.tmp2 > NUL
!ELSE
!MESSAGE $(INF_FILENAME) (1) : error 0001 : $(DPX_SOURCE_FILE) dependency source file does not exist
!ERROR Dependency expression source file "$(DPX_SOURCE_FILE)" does not exist.
!ENDIF
!ELSE
$(TARGET_DPX) : $(INF_FILENAME)
  echo. > $(TARGET_DPX)
  type $(TARGET_DPX) > $(TARGET_DPX)
!ENDIF

#
# Makefile entries for DXE DPX for combined PEIM drivers.
# If a DXE_DPX_SOURCE file was specified in the INF file, use it. Otherwise
# create an empty file and use it as a DPX file.
#
!IF "$(COMPONENT_TYPE)" == "COMBINED_PEIM_DRIVER"
!IF "$(DXE_DPX_SOURCE)" != ""

!IF EXIST ($(SOURCE_DIR)\$(DXE_DPX_SOURCE))
$(TARGET_DXE_DPX) : $(SOURCE_DIR)\$(DXE_DPX_SOURCE) $(INF_FILENAME)
  $(CC) $(INC) /EP $(SOURCE_DIR)\$(DXE_DPX_SOURCE) > $*.tmp1
  $(GENDEPEX) -I $*.tmp1 -O $*.tmp2
  $(GENSECTION) -I $*.tmp2 -O $@ -S EFI_SECTION_DXE_DEPEX
  del $*.tmp1 > NUL
  del $*.tmp2 > NUL
!ELSE
!MESSAGE $(INF_FILENAME) (1) : error 0001 : $(DXE_DPX_SOURCE) dependency source file does not exist
!ERROR Dependency expression source file "$(SOURCE_DIR)\$(DXE_DPX_SOURCE)" does not exist.
!ENDIF
!ELSE
$(TARGET_DXE_DPX) : $(INF_FILENAME)
  echo. > $(TARGET_DXE_DPX)
  type $(TARGET_DXE_DPX) > $(TARGET_DXE_DPX)
!ENDIF
!ENDIF

#
# Describe how to build the HII export file from all the input HII pack files.
# Use the FFS file GUID for the package GUID in the export file. Only used
# when multiple VFR share strings.
#
$(DEST_DIR)\$(BASE_NAME).hii : $(HII_PACK_FILES)
  $(HIIPACK) create -g $(FILE_GUID) -p $(HII_PACK_FILES) -o $(DEST_DIR)\$(BASE_NAME).hii
#
# If the build calls for creating an FFS file with the IFR included as
# a separate binary (not compiled into the driver), then build the binary
# section now. Note that the PACKAGE must be set correctly to actually get
# this IFR section pulled into the FFS file.
#
!IF ("$(HII_IFR_PACK_FILES)" != "")

$(DEST_DIR)\$(BASE_NAME)IfrBin.sec : $(HII_IFR_PACK_FILES)
  $(HIIPACK) create -novarpacks -p $(HII_IFR_PACK_FILES) -o $(DEST_DIR)\$(BASE_NAME)IfrBin.hii
  $(GENSECTION) -I $(DEST_DIR)\$(BASE_NAME)IfrBin.hii -O $(DEST_DIR)\$(BASE_NAME)IfrBin.sec -S EFI_SECTION_RAW

BIN_TARGETS = $(BIN_TARGETS) $(DEST_DIR)\$(BASE_NAME)IfrBin.sec

!ENDIF

#
# Final step -- build the FFS file from the sections
#
$(TARGET_FFS_FILE) : $(TARGET_PE32) $(TARGET_DPX) $(TARGET_UI) $(TARGET_VER) $(TARGET_DXE_DPX)
  $(GENFFSFILE) -B $(DEST_DIR) -P1 $(PACKAGE_FILENAME) -V

all: $(LOCALIZE_TARGETS) $(BIN_TARGETS) $(TARGET_FFS_FILE)

[=============================================================================]
[Build.Ia32.BS_DRIVER_EFI|APPLICATION_EFI,Build.Ebc.BS_DRIVER_EFI|APPLICATION_EFI,Build.x64.BS_DRIVER_EFI|APPLICATION_EFI]
#
# ORIGIN: [Build.$(PROCESSOR).*_EFI] section of the platform DSC file
#
# Defines for standard intermediate files and build targets. For the source
# .efi file, take the one in the source directory if it exists. If there's not
# one there, look for one in the processor-specfic subdirectory.
#
!IF EXIST ("$(SOURCE_DIR)\$(BASE_NAME).efi")
TARGET_EFI        = $(SOURCE_DIR)\$(BASE_NAME).efi
!ELSEIF EXIST ("$(SOURCE_DIR)\$(PROCESSOR)\$(BASE_NAME).efi")
TARGET_EFI        = $(SOURCE_DIR)\$(PROCESSOR)\$(BASE_NAME).efi
!ELSE
!ERROR Pre-existing $(BASE_NAME).efi file not found in $(SOURCE_DIR) nor $(SOURCE_DIR)\$(PROCESSOR)
!ENDIF

TARGET_FFS_FILE   = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).dxe
TARGET_DPX        = $(DEST_DIR)\$(BASE_NAME).dpx
TARGET_UI         = $(DEST_DIR)\$(BASE_NAME).ui
TARGET_VER        = $(DEST_DIR)\$(BASE_NAME).ver
TARGET_MAP        = $(DEST_DIR)\$(BASE_NAME).map
TARGET_PDB        = $(PDB_OUTPUT_PATH)\$(BASE_NAME).pdb
TARGET_PE32       = $(DEST_DIR)\$(BASE_NAME).pe32
TARGET_DLL        = $(BIN_DIR)\$(BASE_NAME).dll

#
# Take the .efi file and make a .pe32 file
#
$(TARGET_PE32) : $(TARGET_EFI) $(INF_FILENAME)
  $(GENSECTION) -I $(TARGET_EFI) -O $(TARGET_PE32) -S EFI_SECTION_PE32

#
# Create the user interface section
#
$(TARGET_UI) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_UI) -S EFI_SECTION_USER_INTERFACE -A "$(BASE_NAME)"

#
# Create the version section
#
!IF "$(BUILD_NUMBER)" != ""
!IF "$(VERSION_STRING)" != ""
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER) -A "$(VERSION_STRING)"
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER)
!ENDIF
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  echo. > $(TARGET_VER)
  type $(TARGET_VER) > $(TARGET_VER)
!ENDIF

#
# Create a DPX section.
# If a DPX file was specified in the INF file, use it. Otherwise create an
# empty file and use it as a DPX file.
#
!IF "$(DPX_SOURCE)" != ""
$(TARGET_DPX) : $(SOURCE_DIR)\$(DPX_SOURCE) $(INF_FILENAME)
  $(CC) $(INC) /EP $(SOURCE_DIR)\$(DPX_SOURCE) > $*.tmp1
  $(GENDEPEX) -I $*.tmp1 -O $*.tmp2
  $(GENSECTION) -I $*.tmp2 -O $@ -S $(DEPEX_TYPE)
  del $*.tmp1 > NUL
  del $*.tmp2 > NUL
!ELSE
$(TARGET_DPX) : $(INF_FILENAME)
  echo. > $(TARGET_DPX)
  type $(TARGET_DPX) > $(TARGET_DPX)
!ENDIF

#
# Build a FFS file from the sections and package
#
$(TARGET_FFS_FILE) : $(TARGET_PE32) $(TARGET_DPX) $(TARGET_UI) $(TARGET_VER)
  $(GENFFSFILE) -B $(DEST_DIR) -P1 $(PACKAGE_FILENAME) -V

all: $(TARGET_FFS_FILE)

[=============================================================================]
#
# Commands to build EBC targets
#
[=============================================================================]
[Build.Ebc.BS_DRIVER|APPLICATION]
#
# ORIGIN: [Build.Ebc.???] section of the platform DSC file
#
# Add the EBC library to our list of libs
#
LIBS = $(LIBS) $(EBC_TOOLS_PATH)\lib\EbcLib.lib
#
# If we have strings (localization), then process the string files.
#
!IF "$(LOCALIZE)" == "YES"

!IF "$(EFI_GENERATE_HII_EXPORT)" == "YES"
STRGATHER_FLAGS   = $(STRGATHER_FLAGS) -hpk $(DEST_DIR)\$(BASE_NAME)Strings.hpk
#
# There will be one HII pack containing all the strings. Add that file
# to the list of HII pack files we'll use to create our final HII export file.
#
HII_PACK_FILES    = $(HII_PACK_FILES) $(DEST_DIR)\$(BASE_NAME)Strings.hpk
LOCALIZE_TARGETS  = $(LOCALIZE_TARGETS) $(DEST_DIR)\$(BASE_NAME).hii

!ENDIF
#
# Create the composite string database file for this driver.
#
$(DEST_DIR)\$(BASE_NAME).sdb : $(SDB_FILES) $(SOURCE_FILES)
  $(STRGATHER) -scan -vdbr $(STRGATHER_FLAGS) -od $(DEST_DIR)\$(BASE_NAME).sdb \
    -skipext .uni -skipext .h $(SOURCE_FILES)

$(DEST_DIR)\$(BASE_NAME)Strings.c $(DEST_DIR)\$(BASE_NAME)StrDefs.h $(DEST_DIR)\$(BASE_NAME)Strings.hpk : $(DEST_DIR)\$(BASE_NAME).sdb
  $(STRGATHER) -dump $(LANGUAGE_FLAGS) -bn $(BASE_NAME)Strings -db $(DEST_DIR)\$(BASE_NAME).sdb \
    -oc $(DEST_DIR)\$(BASE_NAME)Strings.c -hpk $(DEST_DIR)\$(BASE_NAME)Strings.hpk -oh $(DEST_DIR)\$(BASE_NAME)StrDefs.h

OBJECTS = $(OBJECTS) $(DEST_DIR)\$(BASE_NAME)Strings.obj

$(DEST_DIR)\$(BASE_NAME)Strings.obj : $(DEST_DIR)\$(BASE_NAME)Strings.c
  $(CC) $(C_FLAGS) $(DEST_DIR)\$(BASE_NAME)Strings.c

LOCALIZE_TARGETS = $(LOCALIZE_TARGETS) $(DEST_DIR)\$(BASE_NAME)StrDefs.h

!ENDIF
#
# If building an application, then the target is a .app, not .dxe
#
!IF "$(COMPONENT_TYPE)" == "APPLICATION"
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).app
SUBSYSTEM       = EFI_APPLICATION
!ELSE
TARGET_FFS_FILE = $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME).dxe
SUBSYSTEM       = EFI_BOOT_SERVICE_DRIVER
!ENDIF
#
# Defines for standard intermediate files and build targets
#
TARGET_EFI  = $(BIN_DIR)\$(BASE_NAME).efi
TARGET_DPX  = $(DEST_DIR)\$(BASE_NAME).dpx
TARGET_UI   = $(DEST_DIR)\$(BASE_NAME).ui
TARGET_VER  = $(DEST_DIR)\$(BASE_NAME).ver
TARGET_MAP  = $(DEST_DIR)\$(BASE_NAME).map
TARGET_PDB  = $(PDB_OUTPUT_PATH)\$(BASE_NAME).pdb
TARGET_PE32 = $(DEST_DIR)\$(BASE_NAME).pe32

#
# First link all the objects and libs together to make a .efi file
#
$(TARGET_EFI) : $(OBJECTS) $(LIBS)
  $(LINK) $(LINK_FLAGS) /SUBSYSTEM:$(SUBSYSTEM) /ENTRY:EfiStart $(OBJECTS) $(LIBS) /OUT:$(TARGET_EFI)
  $(SETSTAMP) $(TARGET_EFI) $(BUILD_DIR)\GenStamp.txt
#
# Run GenSection to create the FFS section from the .efi file
#
$(TARGET_PE32) : $(TARGET_EFI) $(INF_FILENAME)
  $(GENSECTION) -I $(TARGET_EFI) -O $(TARGET_PE32) -S EFI_SECTION_PE32
#
# Run GenSection to create the UI section (even if it's not used)
#
$(TARGET_UI) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_UI) -S EFI_SECTION_USER_INTERFACE -A "$(BASE_NAME)"
#
# Run GenSection to create the version section (even if it's not used)
#
!IF "$(BUILD_NUMBER)" != ""
!IF "$(VERSION_STRING)" != ""
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER) -A "$(VERSION_STRING)"
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  $(GENSECTION) -O $(TARGET_VER) -S EFI_SECTION_VERSION -V $(BUILD_NUMBER)
!ENDIF
!ELSE
$(TARGET_VER) : $(INF_FILENAME)
  echo. > $(TARGET_VER)
  type $(TARGET_VER) > $(TARGET_VER)
!ENDIF

#
# Makefile entries to create the dependency expression section.
# Use the DPX file from the source directory unless an override file
# was specified.
# If no DPX source file was specified, then create an empty file to
# be used.
#
!IF "$(DPX_SOURCE)" != ""
DPX_SOURCE_FILE = $(SOURCE_DIR)\$(DPX_SOURCE)
!ENDIF

!IF "$(DPX_SOURCE_OVERRIDE)" != ""
DPX_SOURCE_FILE = $(DPX_SOURCE_OVERRIDE)
!ENDIF

!IF "$(DPX_SOURCE_FILE)" != ""
!IF EXIST ($(DPX_SOURCE_FILE))
$(TARGET_DPX) : $(DPX_SOURCE_FILE) $(INF_FILENAME)
  $(CC) $(INC) /EP $(DPX_SOURCE_FILE) > $*.tmp1
  $(GENDEPEX) -I $*.tmp1 -O $*.tmp2
  $(GENSECTION) -I $*.tmp2 -O $@ -S $(DEPEX_TYPE)
  del $*.tmp1 > NUL
  del $*.tmp2 > NUL
!ELSE
!ERROR Dependency expression source file "$(DPX_SOURCE_FILE)" does not exist.
!ENDIF
!ELSE
$(TARGET_DPX) : $(INF_FILENAME)
  echo. > $(TARGET_DPX)
  type $(TARGET_DPX) > $(TARGET_DPX)
!ENDIF
#
# Final step -- build an FFS file from the sections using the package definition
#
$(TARGET_FFS_FILE) : $(TARGET_PE32) $(TARGET_DPX) $(TARGET_UI) $(TARGET_VER)
  $(GENFFSFILE) -B $(DEST_DIR) -P1 $(PACKAGE_FILENAME) -V

all: $(LOCALIZE_TARGETS) $(TARGET_FFS_FILE)

[=============================================================================]
#
# Commands for building library components
#
[Build.Ia32.Library,Build.Ipf.Library,Build.Ebc.Library,Build.x64.Library]
#
# ORIGIN: [Build.$(PROCESSOR).Library] section of the platform DSC file
#
# LIB all the object files into to our target lib file. Put a dependency on
# the component's INF file in case it changes.
#
LIB_NAME = $(LIB_DIR)\$(BASE_NAME).lib

$(LIB_NAME) : $(OBJECTS) $(LIBS) $(INF_FILENAME)
  $(LIB) $(LIB_FLAGS) $(OBJECTS) $(LIBS) /OUT:$@

all: $(LIB_NAME)


[=============================================================================]
#
# These are commands to compile unicode .uni files.
# Emit an error message if the file's base name is the same as the
# component base name. This causes build issues.
#
[Compile.Ia32.Uni,Compile.Ipf.Uni,Compile.Ebc.Uni,Compile.x64.Uni]

!IF "$(FILE)" == "$(BASE_NAME)"
!ERROR Component Unicode string file name cannot be the same as the component BASE_NAME.
!ENDIF

$(DEST_DIR)\$(FILE).sdb : $(SOURCE_DIR)\$(FILE).uni
  $(STRGATHER) -parse -newdb -db $(DEST_DIR)\$(FILE).sdb $(INC) $(SOURCE_DIR)\$(FILE).uni

SDB_FILES       = $(SDB_FILES) $(DEST_DIR)\$(FILE).sdb
STRGATHER_FLAGS = $(STRGATHER_FLAGS) -db $(DEST_DIR)\$(FILE).sdb
LOCALIZE        = YES

[=============================================================================]
[Compile.Ia32.Vfr,Compile.Ipf.Vfr,Compile.Ebc.Vfr,Compile.x64.Vfr]

HII_PACK_FILES  = $(HII_PACK_FILES) $(DEST_DIR)\$(FILE).hpk

#
# Add a dummy command for building the HII pack file. In reality, it's built
# below, but the C_FLAGS macro reference the target as $@, so you can't specify
# the obj and hpk files as dual targets of the same command.
#
$(DEST_DIR)\$(FILE).hpk : $(DEST_DIR)\$(FILE).obj
  @echo.

$(DEST_DIR)\$(FILE).obj : $(SOURCE_DIR)\$(FILE).vfr $(INC_DEPS) $(DEST_DIR)\$(BASE_NAME)StrDefs.h
  $(VFRCOMPILE) $(VFRCOMPILE_FLAGS) $(INC) -ibin -od $(DEST_DIR)\$(SOURCE_RELATIVE_PATH) \
    -l $(VFR_FLAGS) $(SOURCE_DIR)\$(FILE).vfr
  $(CC) $(C_FLAGS) $(DEST_DIR)\$(FILE).c

[=============================================================================]
#
# Define the package templates used to create the FFS files from our
# drivers.
#
# The sections are named [Package.$(COMPONENT_TYPE).$(PACKAGE), where
# COMPONENT_TYPE is typically set in the component's .inf file, and
# PACKAGE is defined in the components section below.
#
[=============================================================================]
[Package.APPLICATION.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_APPLICATION
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    Tool (
      $(OEMTOOLPATH)\GenCRC32Section
      ARGS= -i $(DEST_DIR)\$(BASE_NAME).pe32
               $(DEST_DIR)\$(BASE_NAME).ui
               $(DEST_DIR)\$(BASE_NAME).ver
            -o $(DEST_DIR)\$(BASE_NAME).crc32
      OUTPUT = $(DEST_DIR)\$(BASE_NAME).crc32
    )
  }
}


[=============================================================================]
[Package.BINARY.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    Tool ( $(OEMTOOLPATH)\GenCRC32Section
      ARGS = -i $(DEST_DIR)\$(BASE_NAME).sec
             -o $(DEST_DIR)\$(BASE_NAME).crc32
      OUTPUT = $(DEST_DIR)\$(BASE_NAME).crc32
    )
  }
}

[=============================================================================]
[Build.Ia32.BINARY,Build.Ipf.BINARY,Build.x64.BINARY]
#
#
# Use GenFfsFile to convert it to an FFS file
#
$(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME)$(FFS_EXT) : $(DEST_DIR)\$(BASE_NAME).bin
  $(GENSECTION) -I $(DEST_DIR)\$(BASE_NAME).bin -O $(DEST_DIR)\$(BASE_NAME).sec -S EFI_SECTION_RAW
  $(GENFFSFILE) -B $(BIN_DIR) -P1 $(DEST_DIR)\$(BASE_NAME).pkg -V

all: $(BIN_DIR)\$(FILE_GUID)-$(BASE_NAME)$(FFS_EXT)

[=============================================================================]
[Compile.Ia32.Bin,Build.Ipf.Bin]
#
# We simply copy the 16 bit binary file from the source directory to the destination directory
#
$(DEST_DIR)\$(BASE_NAME).bin : $(SOURCE_DIR)\$(BASE_NAME).bin
  copy $** $@

[=============================================================================]
[Package.FILE.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).sec
}

[=============================================================================]
#
# Instructions for building a component that uses a custom makefile. Encoding
# is [build.$(PROCESSOR).$(BUILD_TYPE)].
#
# To build these components, simply call the makefile from the source
# directory.
#
[Build.Ia32.Custom_Makefile,Build.Ipf.Custom_Makefile,Build.Ebc.Custom_Makefile,Build.x64.Custom_Makefile]

#
# Just call the makefile from the source directory, passing in some
# useful info.
#
all :
  $(MAKE) -f $(SOURCE_DIR)\makefile all    \
          SOURCE_DIR=$(SOURCE_DIR)         \
          BUILD_DIR=$(BUILD_DIR)           \
          FILE_GUID=$(FILE_GUID)           \
          DEST_DIR=$(DEST_DIR)             \
          FILE_GUID=$(FILE_GUID)           \
          PROCESSOR=$(PROCESSOR)           \
          TOOLCHAIN=$(TOOLCHAIN)           \
          BASE_NAME=$(BASE_NAME)           \
          PLATFORM=$(PLATFORM)             \
          SOURCE_FV=$(SOURCE_FV)           \
          EFI_FVMAIN_COMPACT=$(EFI_FVMAIN_COMPACT) \
          PACKAGE_FILENAME=$(PACKAGE_FILENAME)

[=============================================================================]
[Build.Ia32.Makefile,Build.Ipf.Makefile,Build.Ebc.Makefile,Build.x64.Makefile]

#
# Copy the makefile directly from the source directory, then make it
# writable so we can copy over it later if we try to.
#
$(DEST_DIR)\makefile.new : $(SOURCE_DIR)\makefile.new
  copy $(SOURCE_DIR)\makefile.new $(DEST_DIR)\makefile.new
  attrib -r $(DEST_DIR)\makefile.new

#
# Make the all target, set some required macros.
#
call_makefile :
  $(MAKE) -f $(DEST_DIR)\makefile.new all   \
          SOURCE_DIR=$(SOURCE_DIR)          \
          BUILD_DIR=$(BUILD_DIR)            \
          FILE_GUID=$(FILE_GUID)            \
          DEST_DIR=$(DEST_DIR)              \
          FILE_GUID=$(FILE_GUID)            \
          PROCESSOR=$(PROCESSOR)            \
          TOOLCHAIN=TOOLCHAIN_$(PROCESSOR)  \
          BASE_NAME=$(BASE_NAME)            \
          PACKAGE_FILENAME=$(PACKAGE_FILENAME)

all : $(DEST_DIR)\makefile.new call_makefile

[=============================================================================]
[Package.PE32_PEIM.CompressPEIM]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_PEIM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).dpx
  Compress (dummy) {
    $(BASE_NAME).pe32
    $(BASE_NAME).ui
    $(BASE_NAME).ver
  }
}

[=============================================================================]
[Package.PEI_CORE.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_PEI_CORE
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).pe32
  $(BASE_NAME).ui
  $(BASE_NAME).ver
}

[=============================================================================]
[Package.PE32_PEIM.Relocatable]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_PEIM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).dpx
  $(BASE_NAME).pe32
}

[=============================================================================]
[Package.BS_DRIVER.DxeMain]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_DXE_CORE
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    $(BASE_NAME).pe32
    $(BASE_NAME).ui
    $(BASE_NAME).ver
  }
}

[=============================================================================]
[Package.BS_DRIVER.Default,Package.RT_DRIVER.Default,Package.SAL_RT_DRIVER.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_DRIVER
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    Tool (
      $(OEMTOOLPATH)\GenCRC32Section
      ARGS= -i $(DEST_DIR)\$(BASE_NAME).dpx
               $(DEST_DIR)\$(BASE_NAME).pe32
               $(DEST_DIR)\$(BASE_NAME).ui
               $(DEST_DIR)\$(BASE_NAME).ver
            -o $(DEST_DIR)\$(BASE_NAME).crc32
      OUTPUT = $(DEST_DIR)\$(BASE_NAME).crc32
    )
  }
}

[=============================================================================]
[Package.PE32_PEIM.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_PEIM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).dpx
  $(BASE_NAME).pe32
  $(BASE_NAME).ui
  $(BASE_NAME).ver
}

[=============================================================================]
#
# Package definition for a combined PEIM/DXE driver
#
[Package.COMBINED_PEIM_DRIVER.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  $(BASE_NAME).dpx
  $(BASE_NAME).pe32
  $(BASE_NAME).ui
  $(BASE_NAME).ver
}

[=============================================================================]
[Package.Logo.Logo,Package.Logo.Default]
PACKAGE.INF
\[.]
BASE_NAME                   = $(BASE_NAME)
FFS_FILEGUID                = $(FILE_GUID)
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (Dummy) {
    Tool ( $(OEMTOOLPATH)\GenCRC32Section
      ARGS = -i $(BIN_DIR)\$(BASE_NAME).sec
             -o $(BIN_DIR)\$(BASE_NAME).crc32
      OUTPUT = $(BIN_DIR)\$(BASE_NAME).crc32
    )
  }
}



[=============================================================================]
#
# Commands to build a firmware volume
#
[Build.Fv.FvMain64,Build.Fv.FvMain32]
#
# ORIGIN: [Build.Fv.*] section of the platform DSC file
#
Fv\$(FV_FILENAME).fv : $(DSC_FILENAME) $($(FV_FILENAME)_FILES) Fv\$(FV_FILENAME).inf
  @cd Fv
  $(GENFVIMAGE) -I $(FV_FILENAME).inf
  @cd ..

[=============================================================================]
#
# These control the generation of the FV files
#
[=============================================================================]
[Fv.FvMain64.Options,Fv.FvMain32.Options]
EFI_BASE_ADDRESS        = 0x100000
EFI_FILE_NAME           = $(FV_FILENAME).fv
EFI_NUM_BLOCKS          = 0x016
EFI_BLOCK_SIZE          = 0x010000

[=============================================================================]
[Fv.FvMain64.Attributes,Fv.FvMain32.Attributes]
EFI_READ_DISABLED_CAP   = TRUE
EFI_READ_ENABLED_CAP    = TRUE
EFI_READ_STATUS         = TRUE
EFI_WRITE_DISABLED_CAP  = TRUE
EFI_WRITE_ENABLED_CAP   = TRUE
EFI_WRITE_STATUS        = TRUE
EFI_LOCK_CAP            = TRUE
EFI_LOCK_STATUS         = FALSE
EFI_STICKY_WRITE        = TRUE
EFI_MEMORY_MAPPED       = TRUE
EFI_ERASE_POLARITY      = 1
EFI_ALIGNMENT_CAP       = TRUE
EFI_ALIGNMENT_2         = TRUE
EFI_ALIGNMENT_4         = TRUE
EFI_ALIGNMENT_8         = TRUE
EFI_ALIGNMENT_16        = TRUE
EFI_ALIGNMENT_32        = TRUE
EFI_ALIGNMENT_64        = TRUE
EFI_ALIGNMENT_128       = TRUE
EFI_ALIGNMENT_256       = TRUE
EFI_ALIGNMENT_512       = TRUE
EFI_ALIGNMENT_1K        = TRUE
EFI_ALIGNMENT_2K        = TRUE
EFI_ALIGNMENT_4K        = TRUE
EFI_ALIGNMENT_8K        = TRUE
EFI_ALIGNMENT_16K       = TRUE
EFI_ALIGNMENT_32K       = TRUE
EFI_ALIGNMENT_64K       = TRUE

[=============================================================================]

[Libraries]

DEFINE TOOLCHAIN=TOOLCHAIN_MSVC_IA32
DEFINE PROCESSOR=IA32

Edk\Foundation\Guid\EdkGuidLib.inf
Edk\Foundation\Framework\Guid\EdkFrameworkGuidLib.inf
Edk\Foundation\Efi\Guid\EfiGuidLib.inf
Edk\Foundation\Library\EfiCommonLib\EfiCommonLib.inf
Edk\Foundation\Cpu\Pentium\CpuIA32Lib\CpuIA32Lib.inf

Edk\Foundation\Ppi\EdkPpiLib.inf
Edk\Foundation\Framework\Ppi\EdkFrameworkPpiLib.inf
Edk\Foundation\Library\Pei\PeiLib\PeiLib.inf
Edk\Foundation\Library\Pei\Hob\PeiHobLib.inf
Edk\Foundation\Library\CustomizedDecompress\CustomizedDecompress.inf

Edk\Foundation\Protocol\EdkProtocolLib.inf
Edk\Foundation\Framework\Protocol\EdkFrameworkProtocolLib.inf
Edk\Foundation\Efi\Protocol\EfiProtocolLib.inf
Edk\Foundation\Core\Dxe\ArchProtocol\ArchProtocolLib.inf
Edk\Foundation\Library\Dxe\EfiDriverLib\EfiDriverLib.inf
Edk\Foundation\Library\RuntimeDxe\EfiRuntimeLib\EfiRuntimeLib.inf
Edk\Foundation\Library\Dxe\EfiIfrSupportLib\EfiIfrSupportLib.inf
Edk\Foundation\Library\Dxe\Print\PrintLib.inf
Edk\Foundation\Library\Dxe\PrintLite\PrintLib.inf
Edk\Foundation\Library\Dxe\Graphics\Graphics.inf
Edk\Foundation\Library\Dxe\GraphicsLite\Graphics.inf
Edk\Foundation\Library\Dxe\Hob\HobLib.inf

Edk\Other\Maintained\Application\Shell\Library\EfiShellLib.inf

Platform\IntelTest\Protocol\TestProtocolLib.inf
Platform\IntelTest\Library\EfiTestLib\EfiTestLib.inf
Platform\IntelTest\Library\EfiTestUtilityLib\EfiTestUtilityLib.inf

[=============================================================================]
#
# These are the components that will be built by the master makefile
#
[=============================================================================]
[Components]

DEFINE TOOLCHAIN=TOOLCHAIN_MSVC_IA32
DEFINE PROCESSOR=IA32

#
# The default package
#
DEFINE PACKAGE=Default

#
# Components
#

#
# Following are the SCT suite & related drivers
#

Platform\IntelTest\TestInfrastructure\SCT\Framework\Sct.inf
Platform\IntelTest\TestInfrastructure\SCT\Drivers\StandardTest\StandardTest.inf
Platform\IntelTest\TestInfrastructure\SCT\Drivers\TestProfile\TestProfile.inf
Platform\IntelTest\TestInfrastructure\SCT\Drivers\TestRecovery\TestRecovery.inf
Platform\IntelTest\TestInfrastructure\SCT\Drivers\TestLogging\TestLogging.inf

#
# Related SCT applications
#

Platform\IntelTest\Application\InstallSct\InstallSct.inf
Platform\IntelTest\Application\StallForKey\StallForKey.inf

#
# EFI test cases
#

Platform\IntelTest\TestCase\EFI\Generic\EfiCompliant\BlackBoxTest\EfiCompliantBbTest.inf

Platform\IntelTest\TestCase\EFI\BootServices\EventTimerTaskPriorityServices\BlackBoxTest\EventTimerTaskPriorityServicesBBTest.inf
Platform\IntelTest\TestCase\EFI\BootServices\ImageServices\BlackBoxTest\ImageBBTest.inf
Platform\IntelTest\TestCase\EFI\BootServices\MemoryAllocationServices\BlackBoxTest\MemoryAllocationServicesBBTest.inf
Platform\IntelTest\TestCase\EFI\BootServices\MiscBootServices\BlackBoxTest\MiscBootServicesBBTest.inf
Platform\IntelTest\TestCase\EFI\BootServices\ProtocolHandlerServices\BlackBoxTest\ProtocolHandlerBBTest.inf

Platform\IntelTest\TestCase\EFI\RuntimeServices\MiscRuntimeServices\BlackBoxTest\MiscRuntimeServicesBBTest.inf
Platform\IntelTest\TestCase\EFI\RuntimeServices\TimeServices\BlackBoxTest\TimeServicesBBTest.inf
Platform\IntelTest\TestCase\EFI\RuntimeServices\VariableServices\BlackBoxTest\VariableServicesBBTest.inf

Platform\IntelTest\TestCase\EFI\Protocol\Bis\BlackBoxTest\BisBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\BlockIo\BlackBoxTest\BlockIoBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\BusSpecificDriverOverride\BlackBoxTest\BusSpecificDriverOverrideBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\ComponentName\BlackBoxTest\ComponentNameBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DebugPort\BlackBoxTest\DebugPortBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DebugSupport\BlackBoxTest\DebugSupportBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\DecompressBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DeviceIo\BlackBoxTest\DeviceIoBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DevicePath\BlackBoxTest\DevicePathBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DiskIo\BlackBoxTest\DiskIoBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DriverConfiguration\BlackBoxTest\DriverConfigurationBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\DriverDiagnostics\BlackBoxTest\DriverDiagnosticsBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\Ebc\BlackBoxTest\EbcBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\LoadedImage\BlackBoxTest\LoadedImageBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\LoadFile\BlackBoxTest\LoadFileBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\PciIo\BlackBoxTest\PciIoBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\PciRootBridgeIo\BlackBoxTest\PciRootBridgeIoBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\PlatformDriverOverride\BlackBoxTest\PlatformDriverOverrideBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\PXEBaseCode\BlackBoxTest\PxeBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\ScsiPassThru\BlackBoxTest\ScsiPassThruBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SerialIo\BlackBoxTest\SerialIoBbTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SimpleNetwork\BlackBoxTest\SimpleNetworkBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SimpleFileSystem\BlackBoxTest\SimpleFileSystemBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SimplePointer\BlackBoxTest\SimplePointerBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SimpleTextIn\BlackBoxTest\SimpleTextInBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\SimpleTextOut\BlackBoxTest\SimpleTextOutBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\UgaDraw\BlackBoxTest\UgaDrawBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\UnicodeCollation\BlackBoxTest\UnicodeCollationBBTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\UsbHc\BlackBoxTest\UsbHcTest.inf
Platform\IntelTest\TestCase\EFI\Protocol\UsbIo\BlackBoxTest\UsbIoTest.inf

#
# Dependency files for EFI Compliant Test
#

Platform\IntelTest\TestCase\Efi\Generic\EfiCompliant\BlackBoxTest\Dependency\Config\Config.inf

#
# Dependency files for Image Services Test
#

Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\LoadFile\LoadFile.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\Application1\Application1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\Application2\Application2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\Application3\Application3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\Application4\Application4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver1\BootServicesDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver2\BootServicesDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver3\BootServicesDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver4\BootServicesDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver5\BootServicesDriver5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\BootServicesDriver6\BootServicesDriver6.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver1\RuntimeServicesDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver2\RuntimeServicesDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver3\RuntimeServicesDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver4\RuntimeServicesDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver5\RuntimeServicesDriver5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\RuntimeServicesDriver6\RuntimeServicesDriver6.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage1\CombinationImage1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage2\CombinationImage2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage3\CombinationImage3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage4\CombinationImage4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage5\CombinationImage5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage6\CombinationImage6.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage7\CombinationImage7.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage8\CombinationImage8.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage9\CombinationImage9.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\CombinationImage10\CombinationImage10.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage1\InvalidImage1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage2\InvalidImage2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage3\InvalidImage3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage4\InvalidImage4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage5\InvalidImage5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage6\InvalidImage6.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\InvalidImage7\InvalidImage7.inf
Platform\IntelTest\TestCase\Efi\BootServices\ImageServices\BlackBoxTest\Dependency\VeryLargeImage1\VeryLargeImage1.inf

#
# Dependency files for Protocol Handler Services Test
#

Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\BusDriver1\BusDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\BusDriver2\BusDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\BusDriver3\BusDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\BusDriver4\BusDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DBindingDriver1\DBindingDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DBindingDriver2\DBindingDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DBindingDriver3\DBindingDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DBindingDriver4\DBindingDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DBindingDriver5\DBindingDriver5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver1\DeviceDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver2\DeviceDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver3\DeviceDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver4\DeviceDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver5\DeviceDriver5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver6\DeviceDriver6.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver7\DeviceDriver7.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver11\DeviceDriver11.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver12\DeviceDriver12.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver13\DeviceDriver13.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver14\DeviceDriver14.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver15\DeviceDriver15.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver18\DeviceDriver18.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver19\DeviceDriver19.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver110\DeviceDriver110.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\DeviceDriver111\DeviceDriver111.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\TestDriver1\TestDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\TestDriver2\TestDriver2.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\TestDriver3\TestDriver3.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\TestDriver4\TestDriver4.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\TestDriver5\TestDriver5.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\PlatformOverrideDriver1\PlatformOverrideDriver1.inf
Platform\IntelTest\TestCase\Efi\BootServices\ProtocolHandlerServices\BlackBoxTest\Dependency\BusOverrideDriver1\BusOverrideDriver1.inf

#
# Dependency files for Decompress Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\Config\Config.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\CompressedFile1\CompressedFile1.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\CompressedFile2\CompressedFile2.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\UncompressedFile1\UncompressedFile1.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\UncompressedFile2\UncompressedFile2.inf
Platform\IntelTest\TestCase\EFI\Protocol\Decompress\BlackBoxTest\Dependency\InvalidCompressedFile1\InvalidCompressedFile1.inf

#
# Dependency files for Device IO Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\DeviceIo\BlackBoxTest\Dependency\Config\Config.inf

#
# Dependency files for EBC Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\Ebc\BlackBoxTest\Dependency\EbcDriverBin\EbcDriverBin.inf

#
# Dependency files for Loaded Image Protocol Test
#

Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\Application1\Application1.inf
Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\Application2\Application2.inf
Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\BootServicesDriver1\BootServicesDriver1.inf
Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\BootServicesDriver2\BootServicesDriver2.inf
Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\RuntimeServicesDriver1\RuntimeServicesDriver1.inf
Platform\IntelTest\TestCase\Efi\Protocol\LoadedImage\BlackBoxTest\Dependency\RuntimeServicesDriver2\RuntimeServicesDriver2.inf

#
# Dependency files for PCI IO Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\PciIo\BlackBoxTest\Dependency\Config\Config.inf
Platform\IntelTest\TestCase\EFI\Protocol\PciIo\BlackBoxTest\Dependency\MakeConfigWritable\MakeConfigWritable.inf

#
# Dependency files for PCI Root Bridge IO Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\PciRootBridgeIo\BlackBoxTest\Dependency\Config\Config.inf

#
# Dependency files for PXE Base Code Protocol Test
#

Platform\IntelTest\TestCase\EFI\Protocol\PxeBaseCode\BlackBoxTest\Dependency\Config\Config.inf

[=============================================================================]
