@echo off
SET CPP_DIR=%~dp0\..\src
SET SP_DIR=%CONDA_PREFIX%\Lib\site-packages
SET QT_INC=%QT_DIR%\include
SET QTCORE_INC=%QT_DIR%\include\QtCore
SET QTGUI_INC=%QT_DIR%\include\QtGui
SET QTWIDGETS_INC=%QT_DIR%\include\QtWidgets
SET SHIBOKEN_INC=%SP_DIR%\shiboken2_generator\include
SET PYSIDE_INC=%SP_DIR%\PySide2\include
SET PYTHON_INC=%CONDA_PREFIX%\include
SET QTTYPESYSTEM=%SP_DIR%\PySide2\typesystems
shiboken2 --generator-set=shiboken --enable-parent-ctor-heuristic ^
	  --enable-return-value-heuristic --use-isnull-as-nb_nonzero ^
	  --avoid-protected-hack ^
	  --enable-pyside-extensions ^
	  --include-paths=%CPP_DIR%;%QT_INC%;%QTCORE_INC%;%QTGUI_INC%;%QTWIDGETS_INC%;%SHIBOKEN_INC%;%PYSIDE_INC%;%PYTHON_INC% ^
          --typesystem-paths=.;%QTTYPESYSTEM% ^
          --output-directory=%~dp0 ^
          ./bindings.h ./bindings.xml

echo After Script Completed
