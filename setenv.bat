@echo off
set INVICTUS_ROOT=%~dp0..\
echo Using %INVICTUS_ROOT% as Invictus root directory

set QTDIR=%INVICTUS_ROOT%\QT
set OPENSSL_ROOT=%INVICTUS_ROOT%\OpenSSL
set OPENSSL_ROOT_DIR=%OPENSSL_ROOT%
set OPENSSL_INCLUDE_DIR=%OPENSSL_ROOT%\include
set ICUROOT=%INVICTUS_ROOT%\ICU
if "%DBROOTDIR%" == "" set DBROOTDIR=%INVICTUS_ROOT%\BerkeleyDB

rem set BOOST_ROOT only if it is not yet configured
if "%BOOST_ROOT%" == "" set BOOST_ROOT=%INVICTUS_ROOT%\boost

set PATH=%QTDIR%\bin;%ICUROOT%\bin;%INVICTUS_ROOT%\bin;%INVICTUS_ROOT%\Cmake\bin;%PATH%

echo Setting up VS2012 environment...
call "%VS110COMNTOOLS%\..\..\VC\vcvarsall.bat"

