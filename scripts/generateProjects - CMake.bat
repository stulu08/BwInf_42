@echo off
pushd %~dp0\..\
call .premake\premake5.exe cmake
popd
PAUSE