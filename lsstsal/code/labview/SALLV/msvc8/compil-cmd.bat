@ECHO OFF

CALL .\compil-env-setup.bat 

echo "env. setup done"

start /B %WINDIR%\system32\cmd

start /B .\SALLVBindingForLabView.sln


