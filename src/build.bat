@echo off

mkdir ..\bin
pushd ..\bin
cl -Zi ..\src\main.cc
popd