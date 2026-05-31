@echo off
call VsMSBuildCmd.bat
call VsDevCmd.bat

echo === End Setup ===

call nmake