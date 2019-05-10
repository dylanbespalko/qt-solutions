win32: SRC_DIR = $$system(echo %SRC_DIR%)
unix: SRC_DIR = $$system(echo $SRC_DIR)
include($$SRC_DIR/sknrf/root.pri)

######## Before Script #########
win32: message($$system(before.bat))
unix: message($$system(sh before.sh))

TEMPLATE = lib
TARGET = qtpropertybrowserpy
DEFINES += QT_QTPROPERTYBROWSER_IMPORT

HEADERS += \
    qtpropertybrowser/qtproperty_wrapper.h \
    qtpropertybrowser/qtvariantproperty_wrapper.h \
    qtpropertybrowser/qtbrowseritem_wrapper.h \
    \
    qtpropertybrowser/qtabstractpropertymanager_wrapper.h \
    qtpropertybrowser/qtgrouppropertymanager_wrapper.h \
    qtpropertybrowser/qtintpropertymanager_wrapper.h \
    qtpropertybrowser/qtboolpropertymanager_wrapper.h \
    qtpropertybrowser/qtdoublepropertymanager_wrapper.h \
    qtpropertybrowser/qtcomplexpropertymanager_wrapper.h \
    qtpropertybrowser/qtstringpropertymanager_wrapper.h \
    qtpropertybrowser/qtfilepropertymanager_wrapper.h \
    qtpropertybrowser/qtdatepropertymanager_wrapper.h \
    qtpropertybrowser/qttimepropertymanager_wrapper.h \
    qtpropertybrowser/qtdatetimepropertymanager_wrapper.h \
    qtpropertybrowser/qtkeysequencepropertymanager_wrapper.h \
    qtpropertybrowser/qtcharpropertymanager_wrapper.h \
    qtpropertybrowser/qtlocalepropertymanager_wrapper.h \
    qtpropertybrowser/qtpointpropertymanager_wrapper.h \
    qtpropertybrowser/qtpointfpropertymanager_wrapper.h \
    qtpropertybrowser/qtsizepropertymanager_wrapper.h \
    qtpropertybrowser/qtsizefpropertymanager_wrapper.h \
    qtpropertybrowser/qtrectpropertymanager_wrapper.h \
    qtpropertybrowser/qtrectfpropertymanager_wrapper.h \
    qtpropertybrowser/qtenumpropertymanager_wrapper.h \
    qtpropertybrowser/qtflagpropertymanager_wrapper.h \
    qtpropertybrowser/qtsizepolicypropertymanager_wrapper.h \
    qtpropertybrowser/qtfontpropertymanager_wrapper.h \
    qtpropertybrowser/qtcolorpropertymanager_wrapper.h \
    qtpropertybrowser/qtcursorpropertymanager_wrapper.h \
    qtpropertybrowser/qtcursorpropertymanager_wrapper.h \
    qtpropertybrowser/qtvariantpropertymanager_wrapper.h \
    #qtpropertybrowser/qtcomplexarraypropertymanager_wrapper.h \
    \
    qtpropertybrowser/qtabstracteditorfactorybase_wrapper.h \
    qtpropertybrowser/qtspinboxfactory_wrapper.h \
    qtpropertybrowser/qtinteditfactory_wrapper.h \
    qtpropertybrowser/qtsliderfactory_wrapper.h \
    qtpropertybrowser/qtscrollbarfactory_wrapper.h \
    qtpropertybrowser/qtcheckboxfactory_wrapper.h \
    qtpropertybrowser/qtdoublespinboxfactory_wrapper.h \
    qtpropertybrowser/qtdoubleeditfactory_wrapper.h \
    qtpropertybrowser/qtlineeditfactory_wrapper.h \
    qtpropertybrowser/qtcomplexeditfactory_wrapper.h \
    qtpropertybrowser/qtfileeditorfactory_wrapper.h \
    qtpropertybrowser/qtdateeditfactory_wrapper.h \
    qtpropertybrowser/qttimeeditfactory_wrapper.h \
    qtpropertybrowser/qtdatetimeeditfactory_wrapper.h \
    qtpropertybrowser/qtkeysequenceeditorfactory_wrapper.h \
    qtpropertybrowser/qtchareditorfactory_wrapper.h \
    qtpropertybrowser/qtenumeditorfactory_wrapper.h \
    qtpropertybrowser/qtcoloreditorfactory_wrapper.h \
    qtpropertybrowser/qtfonteditorfactory_wrapper.h \
    qtpropertybrowser/qtvarianteditorfactory_wrapper.h \
    #qtpropertybrowser/qtarrayeditfactory_wrapper.h \
    #qtpropertybrowser/qtequationeditfactory_wrapper.h \
    \
    qtpropertybrowser/qtabstractpropertybrowser_wrapper.h \
    qtpropertybrowser/qttreepropertybrowser_wrapper.h \
    qtpropertybrowser/qtgroupboxpropertybrowser_wrapper.h \
    qtpropertybrowser/qtbuttonpropertybrowser_wrapper.h \
    qtpropertybrowser/qtpropertybrowser_python.h

SOURCES += \
    qtpropertybrowser/qtproperty_wrapper.cpp \
    qtpropertybrowser/qtvariantproperty_wrapper.cpp \
    qtpropertybrowser/qtbrowseritem_wrapper.cpp \
    \
    qtpropertybrowser/qtabstractpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtgrouppropertymanager_wrapper.cpp \
    qtpropertybrowser/qtintpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtboolpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtdoublepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtcomplexpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtstringpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtfilepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtdatepropertymanager_wrapper.cpp \
    qtpropertybrowser/qttimepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtdatetimepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtkeysequencepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtcharpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtlocalepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtpointpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtpointfpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtsizepropertymanager_wrapper.cpp \
    qtpropertybrowser/qtsizefpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtrectpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtrectfpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtenumpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtflagpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtsizepolicypropertymanager_wrapper.cpp \
    qtpropertybrowser/qtfontpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtcolorpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtcursorpropertymanager_wrapper.cpp \
    qtpropertybrowser/qtvariantpropertymanager_wrapper.cpp \
    #qtpropertybrowser/qtcomplexarraypropertymanager_wrapper.cpp \
    \
    qtpropertybrowser/qtabstracteditorfactorybase_wrapper.cpp \
    qtpropertybrowser/qtspinboxfactory_wrapper.cpp \
    qtpropertybrowser/qtinteditfactory_wrapper.cpp \
    qtpropertybrowser/qtsliderfactory_wrapper.cpp \
    qtpropertybrowser/qtscrollbarfactory_wrapper.cpp \
    qtpropertybrowser/qtcheckboxfactory_wrapper.cpp \
    qtpropertybrowser/qtdoublespinboxfactory_wrapper.cpp \
    qtpropertybrowser/qtdoubleeditfactory_wrapper.cpp \
    qtpropertybrowser/qtcomplexeditfactory_wrapper.cpp \
    qtpropertybrowser/qtlineeditfactory_wrapper.cpp \
    qtpropertybrowser/qtfileeditorfactory_wrapper.cpp \
    qtpropertybrowser/qtdateeditfactory_wrapper.cpp \
    qtpropertybrowser/qttimeeditfactory_wrapper.cpp \
    qtpropertybrowser/qtdatetimeeditfactory_wrapper.cpp \
    qtpropertybrowser/qtkeysequenceeditorfactory_wrapper.cpp \
    qtpropertybrowser/qtchareditorfactory_wrapper.cpp \
    qtpropertybrowser/qtenumeditorfactory_wrapper.cpp \
    qtpropertybrowser/qtcursoreditorfactory_wrapper.cpp \
    qtpropertybrowser/qtcoloreditorfactory_wrapper.cpp \
    qtpropertybrowser/qtfonteditorfactory_wrapper.cpp \
    qtpropertybrowser/qtvarianteditorfactory_wrapper.cpp \
    #qtpropertybrowser/qtarrayeditfactory_wrapper.cpp \
    #qtpropertybrowser/qtequationeditfactory_wrapper.cpp \
    \
    qtpropertybrowser/qtabstractpropertybrowser_wrapper.cpp \
    qtpropertybrowser/qttreepropertybrowser_wrapper.cpp \
    qtpropertybrowser/qtgroupboxpropertybrowser_wrapper.cpp \
    qtpropertybrowser/qtbuttonpropertybrowser_wrapper.cpp \
    qtpropertybrowser/qtpropertybrowser_module_wrapper.cpp

INCLUDEPATH += $$SP_DIR/shiboken2_generator/include \
               $$PWD/../src \
               $$SP_DIR/PySide2/include \
               $$SP_DIR/PySide2/include/QtCore \
               $$SP_DIR/PySide2/include/QtGui \
               $$SP_DIR/PySide2/include/QtWidgets
win32: INCLUDEPATH += $$CONDA_PREFIX/include
unix: INCLUDEPATH += $$CONDA_PREFIX/include/python3.6m

win32 {
    LIBS += -L$$CONDA_PREFIX/Library/bin -lqtpropertybrowser
    LIBS += -L$$SP_DIR/shiboken2 -lshiboken2.cp36-win_amd64 \
            -L$$SP_DIR/PySide2 -lpyside2.cp36-win_amd64 \
            -L$$CONDA_PREFIX/libs -lpython36
}
macx {
    LIBS += -L$$CONDA_PREFIX/lib -lqtpropertybrowser
    LIBS += -L$$SP_DIR/shiboken2 -lshiboken2.cpython-36m-darwin.5.12 \
            -L$$SP_DIR/PySide2 -lpyside2.cpython-36m-darwin.5.12
    QMAKE_LFLAGS += "-undefined dynamic_lookup"
}
unix:!macx {
    LIBS += -L$$CONDA_PREFIX/lib -lqtpropertybrowser
    LIBS += $$SP_DIR/shiboken2/shiboken2.cpython-36m-x86_64-linux-gnu.so \
            $$SP_DIR/PySide2/libpyside2.cpython-36m-x86_64-linux-gnu.so.5.12
}

######## After Script #########
target.path = $$SRC_DIR/sknrf/build
win32: target.extra = after.bat
unix: target.extra = sh after.sh
INSTALLS += target
