call VsMSBuildCmd.bat
call VsDevCmd.bat

echo == END SETUP ==

call nmake -f makefile
call nmake clean