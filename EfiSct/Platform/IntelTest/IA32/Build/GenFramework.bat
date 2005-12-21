@echo %DEBUG% OFF

rem /*++
rem
rem Copyright (c) 2005, Intel Corporation
rem All rights reserved. This program and the accompanying materials
rem are licensed and made available under the terms and conditions of the Eclipse Public License
rem which accompanies this distribution.  The full text of the license may be found at
rem http://www.opensource.org/licenses/eclipse-1.0.php
rem
rem THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
rem WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
rem
rem Module Name:
rem
rem   GenFramework.bat
rem
rem Abstract:
rem
rem   Generate the test package
rem
rem --*/

set ProcessorType=IA32
set Installer=Install32.efi

set Framework=SctPackage\%ProcessorType%

rem *********************************************
rem Create target directory
rem *********************************************

if exist %Framework% (
  rmdir /s /q %Framework%
)

mkdir %Framework%
mkdir %Framework%\Data
mkdir %Framework%\Dependency
mkdir %Framework%\Support
mkdir %Framework%\Test
mkdir %Framework%\Sequence
mkdir %Framework%\Report

rem *********************************************
rem Copy the SCT framework and the related application
rem *********************************************

copy %ProcessorType%\SCT.efi              %Framework%\            > NUL

copy %ProcessorType%\StandardTest.efi     %Framework%\Support\    > NUL
copy %ProcessorType%\TestProfile.efi      %Framework%\Support\    > NUL
copy %ProcessorType%\TestRecovery.efi     %Framework%\Support\    > NUL
copy %ProcessorType%\TestLogging.efi      %Framework%\Support\    > NUL

copy ..\..\Config\Script\SctStartup.nsh   SctPackage\             > NUL
copy %ProcessorType%\InstallSct.efi       SctPackage\%Installer%  > NUL
copy %ProcessorType%\StallForKey.efi      %Framework%\            > NUL

rem *********************************************
rem Copy the SCT configuration data
rem *********************************************

copy ..\..\Config\Data\Category.ini       %Framework%\Data\       > NUL
copy ..\..\Config\Data\GuidFile.txt       %Framework%\Data\       > NUL

rem *********************************************
rem For EFI SCT
rem *********************************************

if %1. EQU efi_sct. (
  rem *********************************************
rem Copy the EFI 1.10 Test Cases
rem *********************************************

copy %ProcessorType%\EfiCompliantBbTest.efi                   %Framework%\Test\ > NUL

copy %ProcessorType%\EventTimerTaskPriorityServicesBbTest.efi %Framework%\Test\ > NUL
copy %ProcessorType%\MemoryAllocationServicesBbTest.efi       %Framework%\Test\ > NUL
copy %ProcessorType%\ProtocolHandlerServicesBbTest.efi        %Framework%\Test\ > NUL
copy %ProcessorType%\ImageServicesBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\MiscBootServicesBbTest.efi               %Framework%\Test\ > NUL

copy %ProcessorType%\VariableServicesBbTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\TimeServicesBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\MiscRuntimeServicesBbTest.efi            %Framework%\Test\ > NUL

copy %ProcessorType%\BisBbTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\BlockIoBbTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\BusSpecificDriverOverrideBbTest.efi      %Framework%\Test\ > NUL
copy %ProcessorType%\ComponentNameBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\DebugPortBbTest.efi                      %Framework%\Test\ > NUL
copy %ProcessorType%\DebugSupportBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\DecompressBbTest.efi                     %Framework%\Test\ > NUL
copy %ProcessorType%\DeviceIoBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathBbTest.efi                     %Framework%\Test\ > NUL
copy %ProcessorType%\DiskIoBbTest.efi                         %Framework%\Test\ > NUL
copy %ProcessorType%\DriverDiagnosticsBbTest.efi              %Framework%\Test\ > NUL
copy %ProcessorType%\DriverConfigurationBbTest.efi            %Framework%\Test\ > NUL
copy %ProcessorType%\EbcBbTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\LoadedImageBbTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\LoadFileBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\PciIoBbTest.efi                          %Framework%\Test\ > NUL
copy %ProcessorType%\PciRootBridgeIoBbTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\PlatformDriverOverrideBbTest.efi         %Framework%\Test\ > NUL
copy %ProcessorType%\PxeBaseCodeBbTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\ScsiPassThruBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\SerialIoBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleFileSystemBbTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleNetworkBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimplePointerBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextInBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextOutBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\UgaDrawBbTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\UnicodeCollationBbTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\UsbHcTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\UsbIoTest.efi                            %Framework%\Test\ > NUL

rem *********************************************
rem Copy the test dependency files
rem *********************************************

call :CopyDependency EfiCompliant
call :CopyDependency ProtocolHandlerServices
call :CopyDependency ImageServices
call :CopyDependency Decompress
call :CopyDependency DeviceIo
call :CopyDependency Ebc
call :CopyDependency LoadedImage
call :CopyDependency PciIo
call :CopyDependency PciRootBridgeIo
call :CopyDependency PxeBaseCode
)

rem *********************************************
rem For IHV SCT
rem *********************************************

if %1. EQU ihv_sct. (
  rem *********************************************
  rem Copy the EFI 1.10 Test Cases for IHV
  rem *********************************************

  copy %ProcessorType%\IhvBlockIoBbTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvComponentNameBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvBusSpecificDriverOverrideBbTest.efi   %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDeviceIoBbTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDevicePathBbTest.efi                  %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDiskIoBbTest.efi                      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverBindingBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverConfigurationBbTest.efi         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverDiagnosticsBbTest.efi           %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvEbcBbTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPlatformDriverOverrideBbTest.efi      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPxeBaseCodeBbTest.efi                 %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvScsiPassThruBbTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSerialIoBbTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleFileSystemBbTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleNetworkBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimplePointerBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextInBbTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextOutBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUgaDrawBbTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUnicodeCollationBbTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUsbHcTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUsbIoTest.efi                         %Framework%\Test\ > NUL

  rem *********************************************
  rem Copy the test dependency files
  rem *********************************************

  call :CopyDependency DeviceIo
  call :CopyDependency Ebc
  call :CopyDependency PxeBaseCode
)

echo DONE!
goto :EOF


rem *********************************************
rem Copy the test dependency files for each test
rem *********************************************

:CopyDependency

mkdir %Framework%\Dependency\%1BbTest

dir /b %ProcessorType%\%1_*.       > temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.efi   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.ini   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.cmp   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.ucmp  >> temp.txt 2>NUL

for /F "tokens=*" %%i in (temp.txt) do (
  call :CopyDependencyFile %1 %%i
)

del /f temp.txt >NUL

goto :EOF


rem *********************************************
rem Copy each test dependency file
rem *********************************************

:CopyDependencyFile

setlocal

set Source=%2
set Target=%Source:*_=%

copy %ProcessorType%\%Source%     %Framework%\Dependency\%1BbTest\%Target%  > NUL

endlocal

goto :EOF
