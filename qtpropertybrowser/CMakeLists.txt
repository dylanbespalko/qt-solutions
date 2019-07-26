cmake_minimum_required(VERSION 3.13.0)

# Include
include(root.cmake)

# Top-Level Macros
## Find package only when it is not a subproject
macro(find_package)
    if(NOT ${ARGV0} IN_LIST subprojects)
        _find_package(${ARGV})
    endif()
endmacro()

# List Subprojects
set(subprojects qtpropertybrowser qttreepropertybrowserplugin)
add_subdirectory(src)
add_subdirectory(plugin)
add_subdirectory(shiboken)
