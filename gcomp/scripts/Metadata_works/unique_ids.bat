@echo off

perl unique_ids.pl
if errorlevel 1 goto err
echo ��� ��訡���
goto end

:err
echo ���� ��㭨����� �����䨪����!

:end