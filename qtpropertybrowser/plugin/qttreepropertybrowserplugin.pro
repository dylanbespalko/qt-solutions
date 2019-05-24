win32: SRC_DIR = $$system(echo %SRC_DIR%)
unix: SRC_DIR = $$system(echo $SRC_DIR)
TEMPLATE = lib
include($$SRC_DIR/sknrf/root.pri)

######## Before Script #########
win32: message($$system(before.bat))
unix: message($$system(sh before.sh))

CONFIG += plugin
CONFIG -= full-pkg-config
TARGET = qtpropertybrowserplugin
DEFINES += QT_QTPROPERTYBROWSERPLUGIN_LIBRARY
DEFINES += QT_QTPROPERTYBROWSER_IMPORT
QT += designer

HEADERS = qttreepropertybrowserplugin.h

SOURCES = qttreepropertybrowserplugin.cpp

INCLUDEPATH += $$PWD/../src

win32: LIBS += -L$$CONDA_PREFIX/Library/bin -lqtpropertybrowser
unix: LIBS += -L$$CONDA_PREFIX/lib -lqtpropertybrowser

######## After Script #########
target.path = $$SRC_DIR/sknrf/build
win32: target.extra = after.bat
unix: target.extra = sh after.sh
INSTALLS += target
