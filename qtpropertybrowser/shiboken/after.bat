@echo off 
python %SRC_DIR%\sknrf\distribute.py shiboken %CONDA_PREFIX%\Library\bin\qtpropertybrowserpy %CONDA_PREFIX%\Library\bin
echo After Script Completed
