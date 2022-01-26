@echo off

mkdir ..\bin
pushd ..\bin
cl  /O2 ..\src\main.cc
popd
