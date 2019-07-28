cmake_minimum_required(VERSION 3.12.0)
project(qtpropertybrowser)

# Include
include(../root.cmake)

# Variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Build
add_library(qtpropertybrowser SHARED
    qttreepropertybrowser.cpp
    qtbuttonpropertybrowser.cpp
    qtgroupboxpropertybrowser.cpp
    qtpropertybrowser.cpp
    qtpropertymanager.cpp
    qteditorfactory.cpp
    qtpropertybrowserutils.cpp
    qtvariantproperty.cpp
    qtpropertybrowser.qrc)
set(headers
    qttreepropertybrowser.h
    qtbuttonpropertybrowser.h
    qtgroupboxpropertybrowser.h
    qtpropertybrowserutils_p.h
    qtpropertybrowser.h
    qtpropertymanager.h
    qtvariantproperty.h
    qteditorfactory.h)
set_target_properties(qtpropertybrowser PROPERTIES PUBLIC_HEADER "${headers}")
target_compile_definitions(qtpropertybrowser PRIVATE QT_QTPROPERTYBROWSER_EXPORT) # export WIN32 symbols in .lib file
target_compile_definitions(qtpropertybrowser PRIVATE _USE_MATH_DEFINES)

# Linking Flags
target_link_libraries(qtpropertybrowser Qt5::Widgets)

# Install
install (TARGETS qtpropertybrowser EXPORT qtpropertybrowser-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    PUBLIC_HEADER DESTINATION include)
##Export Library Interface
install (EXPORT qtpropertybrowser-targets
    FILE qtpropertybrowserTargets.cmake
    NAMESPACE qtpropertybrowser::
    DESTINATION lib/cmake/qtpropertybrowser)
add_library(qtpropertybrowser::qtpropertybrowser ALIAS qtpropertybrowser)
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_SOURCE_DIR}/qtpropertybrowserConfigVersion.cmake"
    VERSION 1
    COMPATIBILITY SameMajorVersion)
install(FILES "qtpropertybrowserConfig.cmake" "qtpropertybrowserConfigVersion.cmake"
        DESTINATION lib/cmake/qtpropertybrowser)
