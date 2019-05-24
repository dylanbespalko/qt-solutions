win32: SRC_DIR = $$system(echo %SRC_DIR%)
unix: SRC_DIR = $$system(echo $SRC_DIR)
TEMPLATE=lib
include($$SRC_DIR/sknrf/root.pri)

######## Before Script #########
win32: message($$system(before.bat))
unix: message($$system(sh before.sh))

CONFIG += qt dll qtpropertybrowser-buildlib
CONFIG += shared
include(../src/qtpropertybrowser.pri)
CONFIG += release
TARGET = $$QTPROPERTYBROWSER_LIBNAME

######## After Script #########
target.path = $$SRC_DIR/sknrf/build
win32: target.extra = after.bat
unix: target.extra = sh after.sh
INSTALLS += target
