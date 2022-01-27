@echo off

mkdir ..\bin
pushd ..\bin
cl  /Zi ..\src\main.cc
Rem cl  /O2 ..\src\main.cc
popd
