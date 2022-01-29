@echo off

mkdir ..\bin
mkdir ..\data
pushd ..\bin
Rem cl /Zi ..\src\main.cc
cl  /EHsc /O2 ..\src\main.cc
popd
