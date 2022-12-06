@echo off


if "%1" == "" goto :tag_end

set BASE_FOLDER=.\res\skin_%1\

xcopy %BASE_FOLDER%*.bmp .\res /r /y
xcopy %BASE_FOLDER%*.exe .\res /r /y
xcopy %BASE_FOLDER%*.ico .\res /r /y
xcopy %BASE_FOLDER%string.txt .\res /r /y


:tag_end
