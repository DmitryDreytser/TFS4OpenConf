@echo off

gcomp -d --filter �����䨪���늮�䨣��樨
perl check_max_id.pl
if errorlevel 1 goto Error

echo ����� ��������
gcomp -d -v| perl c:\scripts\auto_add.pl
goto End


:Error
echo ����� ��������

:End
