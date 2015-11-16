call %SYSTEMDRIVE%\WinDDK\7600.16385.1\bin\setenv.bat %SYSTEMDRIVE%\WinDDK\7600.16385.1\ fre x86 WXP no_oacr
pushd "%~dp0vendor\libwdi"
call ddk_build DLL
popd
pause
