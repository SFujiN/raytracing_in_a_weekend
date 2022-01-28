@echo off

mkdir ..\bin
pushd ..\bin
Rem cl /Zi ..\src\main.cc
cl  /O2 ..\src\main.cc
popd
