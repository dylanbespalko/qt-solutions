@echo off
python %SRC_DIR%\sknrf\distribute.py plugin %CONDA_PREFIX%\Library\bin\qtpropertybrowserplugin %CONDA_PREFIX%\Library\plugins\designer
echo After Script Completed
