cmake_minimum_required(VERSION 3.12.0)
# Global Variables
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(SEP "\\")
  set(PATH_SEP "\\;")
else ()
  set(SEP "/")
  set(PATH_SEP ":")
endif()
set(CONDA_PREFIX $ENV{CONDA_PREFIX})
string(REPLACE "${SEP}" "/" CONDA_PREFIX ${CONDA_PREFIX})
set(QT_DIR $ENV{QT_DIR})
string(REPLACE "${SEP}" "/" QT_DIR ${QT_DIR})

## CMake
if(WIN32)
    set(CMAKE_INSTALL_PREFIX ${CONDA_PREFIX}/Library)
    set(CMAKE_PREFIX_PATH ${CONDA_PREFIX}/Library/lib/cmake)
else()   
    set(CMAKE_INSTALL_PREFIX ${CONDA_PREFIX})
    set(CMAKE_PREFIX_PATH ${CONDA_PREFIX}/lib/cmake)
endif()
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib ${QT_DIR}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

## C++
set(CMAKE_CXX_STANDARD 11)

## Qt
set(QT_INC ${QT_DIR}/include)
set(QTCORE_INC ${QT_INC}/QtCore)
set(QTGUI_INC ${QT_INC}/QtGui)
set(QTWIDGETS_INC ${QT_INC}/QtWidgets)
set(Qt5_DIR ${QT_DIR}/lib/cmake/Qt5)
if(WIN32)
    message("!!!SET_QT_CREATOR_DIR!!")
elseif(APPLE)
    set(QT_CREATOR_DIR "${QT_DIR}/../../Qt Creator.app/Contents")
else()
    message("!!!SET_QT_CREATOR_DIR!!")
endif()
set(QT_PLUGIN_DIR ${QT_CREATOR_DIR}/PlugIns/designer)

## Python
set(PYTHON_VERSION_MAJOR 3)
set(PYTHON_VERSION_MINOR 6)
set(PYTHON_VERSION ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
string(REPLACE "." "" PYTHONVERSION ${PYTHON_VERSION})
if(WIN32)
    set(PYTHON_INC ${CONDA_PREFIX}/include)
    set(PYTHON_SP_DIR ${CONDA_PREFIX}/Lib/site-packages)
else()
    set(PYTHON_INC ${CONDA_PREFIX}/include/python${PYTHON_VERSION}m)
    set(PYTHON_SP_DIR ${CONDA_PREFIX}/lib/python${PYTHON_VERSION}/site-packages)
endif()

## PySide/Shiboken
set(PYSIDE_INC ${PYTHON_SP_DIR}/PySide2/include)
set(PYSIDE_TYPE ${PYTHON_SP_DIR}/PySide2/typesystems)
set(SHIBOKEN_INC ${PYTHON_SP_DIR}/shiboken2_generator/include)
set(SHIBOKEN_INCLUDEPATH "${CMAKE_CURRENT_SOURCE_DIR}/../src::${QT_INC}::${QTCORE_INC}::${QTGUI_INC}::${QTWIDGETS_INC}::${SHIBOKEN_INC}::${PYSIDE_INC}::${PYTHON_INC}")
string(REPLACE "::" "${PATH_SEP}" SHIBOKEN_INCLUDEPATH ${SHIBOKEN_INCLUDEPATH})
set(SHIBOKEN_TYPEPATH "${CMAKE_CURRENT_SOURCE_DIR}::${PYSIDE_TYPE}")
string(REPLACE "::" "${PATH_SEP}" SHIBOKEN_TYPEPATH ${SHIBOKEN_TYPEPATH})
set(SHIBOKEN_OPT
    "--generator-set=shiboken"
    "--enable-parent-ctor-heuristic"
    "--enable-return-value-heuristic"
    "--use-isnull-as-nb_nonzero"
    "--avoid-protected-hack"
    "--include-paths=${SHIBOKEN_INCLUDEPATH}"
    "--typesystem-paths=${SHIBOKEN_TYPEPATH}"
    "--output-directory=${CMAKE_CURRENT_SOURCE_DIR}")
# Macros
## Query Pyside Configuration (uses pyside2_config.py file).
macro(pyside2_config option output_var)
    if(${ARGC} GREATER 2)
        set(is_list ${ARGV2})
    else()
        set(is_list "")
    endif()

    execute_process(
      COMMAND ${python_interpreter} "${PYTHON_SP_DIR}/PySide2/examples/utils/pyside2_config.py"
              ${option}
      OUTPUT_VARIABLE ${output_var}
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    if ("${${output_var}}" STREQUAL "")
        message(FATAL_ERROR "Error: Calling pyside2_config.py ${option} returned no output.")
    endif()
    if(is_list)
        string (REPLACE " " ";" ${output_var} "${${output_var}}")
    endif()
endmacro()

# Check for Command-Line tools
## Python Interpreter
if(NOT python_interpreter)
    message(STATUS "Check for Python interpreter")
    find_program(python_interpreter "python")
    if(NOT EXISTS ${python_interpreter})
        message(FATAL_ERROR "Check for Python interpreter: NOT FOUND")
    endif()
    message(STATUS "Check for Python interpreter: ${python_interpreter}")
endif()

## Shiboken Python<->C++ Binding Generator
if(NOT shiboken_generator)
    message(STATUS "Check for Shiboken binding generator")
    pyside2_config(--shiboken2-generator-path shiboken2_generator_path)
    set(shiboken_generator "${shiboken2_generator_path}/shiboken2${CMAKE_EXECUTABLE_SUFFIX}")
    if(NOT EXISTS ${shiboken_generator})
        message(FATAL_ERROR "Check for Shiboken binding generator: NOT FOUND")
    endif()
    message(STATUS "Check for Shiboken binding generator: ${shiboken_generator}")
endif()
