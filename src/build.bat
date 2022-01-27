@echo off

mkdir ..\bin
pushd ..\bin
cl  /EHsc /Zi ..\src\main.cc
Rem cl  /O2 ..\src\main.cc
popd
