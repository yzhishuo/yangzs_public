@echo.��������......  
@echo off  
@cd %~dp0
@echo %~dp0
@sc create Myyangzs binPath= "%~dp0\My_windows_server.exe"   
@sc config Myyangzs start= AUTO
@net start Myyangzs 
@echo off  
@echo.������ϣ�  
@pause