@ECHO OFF

SET _BUILDBOT_SVNSKIPMAINTRUNK=0
SET _ROSBE_BASEDIR=C:\RosBE
SET _ROSBE_CACHESIZE=4
SET _ROSBE_DEBUG=0
SET _ROSBE_HOST_MINGWPATH=C:\projects\tools\MinGW64
SET _ROSBE_LOGDIR=RosBE-Logs
SET _ROSBE_MAKEX_JOBS=9
SET _ROSBE_NOSOUND=0
SET _ROSBE_ORIGINALPATH=C:\projects\tools\MinGW64\bin;C:\projects\tools\CMake\bin;C:\projects\tools\doxygen\bin;C:\projects\tools\ninja-win;C:\RosBE;C:\RosBE\bin;C:\RosBE\samples;C:\RosBE\bin;c:\qemu;C:\Git\cmd;C:\java\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\ATI Technologies\ATI.ACE\Core-Static;C:\Users\wade4\AppData\Local\Microsoft\WindowsApps;
SET _ROSBE_ROSSOURCEDIR=C:\Windows\system32
SET _ROSBE_SHOWTIME=1
SET _ROSBE_SHOWVERSION=0
SET _ROSBE_SYSPATH=1
SET _ROSBE_TARGET_MINGWPATH=C:\projects\tools\MinGW64
SET _ROSBE_USECCACHE=0
SET _ROSBE_VERSION=2.1.6
SET _ROSBE_WRITELOG=1

rmdir /s /q output-MinGW-i386
call configure Makefiles
cd output-MinGW-i386
call mingw32-make all bootcd livecd hybridcd
cd..