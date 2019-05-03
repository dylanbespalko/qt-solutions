CPP_DIR=$PWD/../src
SP_DIR=$CONDA_PREFIX/lib/python3.6/site-packages
QT_INC=$QT_DIR/include
QTCORE_INC=$QT_DIR/include/QtCore
QTGUI_INC=$QT_DIR/include/QtGui
QTWIDGETS_INC=$QT_DIR/include/QtWidgets
SHIBOKEN_INC=$SP_DIR/shiboken2_generator/include
PYSIDE_INC=$SP_DIR/PySide2/include
PYTHON_INC=$CONDA_PREFIX/include/python3.6m
QTTYPESYSTEM=$SP_DIR/PySide2/typesystems

shiboken2 --generator-set=shiboken --enable-parent-ctor-heuristic \
          --enable-return-value-heuristic --use-isnull-as-nb_nonzero \
          --avoid-protected-hack \
          --enable-pyside-extensions \
          --include-paths=$CPP_DIR:$QT_INC:$QTCORE_INC:$QTGUI_INC:$QTWIDGETS_INC:$SHIBOKEN_INC:$PYSIDE_INC:$PYTHON_INC \
          --typesystem-paths=.:$QTTYPESYSTEM \
          --output-directory=$PWD \
          ./bindings.h ./bindings.xml

echo Before Script Completed
