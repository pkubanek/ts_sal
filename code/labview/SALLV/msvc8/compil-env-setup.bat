@ECHO off

:: ======== SALLV HOST 
::set SALLV_HOST=localhost:20000

::------------------------------------------------------------------------
:: ======== VC++ 8 ======== 
::------------------------------------------------------------------------
SET PSDK=C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2
CALL "C:\Program Files\Microsoft Visual Studio 8\VC\bin\vcvars32.bat"

::------------------------------------------------------------------------
:: ======== MAVEN ======== 
::------------------------------------------------------------------------
SET M2_ROOT=C:\Documents and Settings\leclercq\.m2\repository

:: ======== NI-LabVIEW PATHS 
set LV_ROOT=C:\Program Files\National Instruments\LabVIEW 2010
set LV_INC=%LV_ROOT%\cintools
set LV_LIB=%LV_ROOT%\cintools
SET LV_LIB_LIST=labview.lib

::------------------------------------------------------------------------
:: ======== YAT PATHS ======== 
::------------------------------------------------------------------------
set YAT_ROOT=%M2_ROOT%\fr\soleil\lib\YAT-x86-Windows-msvc-static-release\x.x.x\nar
set YAT_INC=%YAT_ROOT%\include
set YAT_LIB=%YAT_ROOT%\lib\x86-Windows-msvc\static
set YAT_LIB_LIST=YAT-x86-Windows-msvc-static-release-x.x.x.lib

::------------------------------------------------------------------------
:: ======== YAT FOR SALLV PATHS ======== 
::------------------------------------------------------------------------
set YAT_FOR_SALLV_ROOT=%M2_ROOT%\fr\soleil\lib\YAT4SALLV-x86-Windows-msvc-static-release\x.x.x\nar
set YAT_FOR_SALLV_INC=%YAT_FOR_SALLV_ROOT%\include
set YAT_FOR_SALLV_LIB=%YAT_FOR_SALLV_ROOT%\lib\x86-Windows-msvc\static
set YAT_FOR_SALLV_LIB_LIST=YAT4SALLV-x86-Windows-msvc-static-release-x.x.x.lib

::------------------------------------------------------------------------
:: ======== SALLV ======== 
::------------------------------------------------------------------------
SET SALLV_ROOT=D:\Projets\soleil-root-SALLV-7.2.6-win32\SALLV
SET SALLV_INC=%SALLV_ROOT%\include
SET SALLV_LIB=%SALLV_ROOT%\lib\shared
SET SALLV_BIN=%SALLV_ROOT%\bin
SET SALLV_LIB_LIST=SALLV726.lib log4SALLV.lib
SET PATH=%SALLV_BIN%;%PATH%

::------------------------------------------------------------------------
:: ======== OMNIORB ======== 
::------------------------------------------------------------------------
SET OMNIORB_ROOT=D:\Projets\soleil-root-SALLV-7.2.6-win32\omniorb
SET OMNIORB_INC=%OMNIORB_ROOT%\include
SET OMNIORB_LIB=%OMNIORB_ROOT%\lib\shared
SET OMNIORB_BIN=%OMNIORB_ROOT%\bin
SET OMNIORB_LIB_LIST=omnithread34_rt.lib omniORB414_rt.lib COS414_rt.lib omniDynamic414_rt.lib
SET PATH=%OMNIORB_BIN%;%PATH%



