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
#   SctStartup.nsh
#
# Abstract:
#
#   Startup script for EFI SCT automatic running
#
#--*/

#
# NOTE: The file system name is hard coded since I don't know how to get the
# file system name in the script.
#

for %i in 0 1 2 3 4 5 6 7 8 9 A B C D E F
  if exist FS%i:\Sct then
    #
    # Found EFI SCT harness
    #
    FS%i:
    cd Sct

    echo Press any key to stop the EFI SCT automatic running

    stallforkey.efi 10
    if %lasterror% == 0 then
      goto Done
    endif

    if %efishellmode%. == . then
      #
      # It is an old shell
      #
      NewShell.efi
    else
      #
      # It is a new shell
      #
      Sct -c
    endif

    goto Done
  endif
endfor

:Done
