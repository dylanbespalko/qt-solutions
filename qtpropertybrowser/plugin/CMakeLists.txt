cmake_minimum_required(VERSION 3.12.0)
project(qttreepropertybrowserplugin)

# Include
include(../root.cmake)

# Variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(qtpropertybrowser REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Build
add_library(qttreepropertybrowserplugin SHARED
    qttreepropertybrowserplugin.cpp)
target_compile_definitions(qttreepropertybrowserplugin PRIVATE QT_QTPROPERTYBROWSER_IMPORT) # export WIN32 symbols in .lib file
target_compile_definitions(qttreepropertybrowserplugin PRIVATE QT_QTPROPERTYBROWSERPLUGIN_LIBRARY)

# Include Flags
target_include_directories(qttreepropertybrowserplugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Linking Flags
target_link_libraries(qttreepropertybrowserplugin qtpropertybrowser::qtpropertybrowser)
target_link_libraries(qttreepropertybrowserplugin Qt5::Widgets)

# Install
install (TARGETS qttreepropertybrowserplugin EXPORT qttreepropertybrowserplugin-targets
    LIBRARY DESTINATION ${QT_PLUGIN_DIR})
