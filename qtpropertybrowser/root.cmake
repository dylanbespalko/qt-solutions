cmake_minimum_required(VERSION 3.13.0)
# Environment Variables
set(CONDA_PREFIX $ENV{CONDA_PREFIX})
set(QT_DIR $ENV{QT_DIR})
## Python site-packages dir
if(WIN32)
    set(SP_DIR ${CONDA_PREFIX}/Lib/site-packages)
else()
    set(SP_DIR ${CONDA_PREFIX}/lib/python3.6/site-packages)
endif()

# Global Variables
## CMake
set(CMAKE_INSTALL_PREFIX ${CONDA_PREFIX})
set(CMAKE_PREFIX_PATH ${CONDA_PREFIX}/lib/cmake)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib ${QT_DIR}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

## C++
set(CMAKE_CXX_STANDARD 11)
if (WIN32)
    set(LIB_EXT ".dll")
elseif(APPLE)
    set(LIB_EXT ".dylib")
else()
    set(LIB_EXT ".so")
endif()

## Qt
set(QT_INC ${QT_DIR}/include)
set(QTCORE_INC ${QT_INC}/QtCore)
set(QTGUI_INC ${QT_INC}/QtGui)
set(QTWIDGETS_INC ${QT_INC}/QtWidgets)

## PySide/Shiboken
set(PYSIDE_INC ${SP_DIR}/PySide2/include)
set(PYSIDE_TYPE ${SP_DIR}/PySide2/typesystems)
set(SHIBOKEN_INC ${SP_DIR}/shiboken2_generator/include)
set(SHIBOKEN_OPT
    "--generator-set=shiboken "
    "--enable-parent-ctor-heuristic "
    "--enable-return-value-heuristic "
    "--use-isnull-as-nb_nonzero "
    "--avoid-protected-hack "
    "--include-paths=./../src:${QT_INC}:${QTCORE_INC}:${QTGUI_INC}:${QTWIDGETS_INC}:${SHIBOKEN_INC}:${PYSIDE_INC}:${PYTHON_INC} "
    "--typesystem-paths=.:${PYSIDE_TYPE} "
    "--output-directory=. ")

## Python
if(WIN32)
    set(PYTHON_INC ${CONDA_PREFIX}/include)
else()
    set(PYTHON_INC ${CONDA_PREFIX}/include/python3.6m)
endif()

# Macros
## Query Pyside Configuration (uses pyside2_config.py file).
macro(pyside2_config option output_var)
    if(${ARGC} GREATER 2)
        set(is_list ${ARGV2})
    else()
        set(is_list "")
    endif()

    execute_process(
      COMMAND ${python_interpreter} "${SP_DIR}/PySide2/examples/utils/pyside2_config.py"
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
