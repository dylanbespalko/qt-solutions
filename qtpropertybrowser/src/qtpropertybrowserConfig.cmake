get_filename_component(QTPROPERTYBROWSER_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(NOT TARGET qtpropertybrowser::qtpropertybrowser)
    include(${QTPROPERTYBROWSER_CMAKE_DIR}/qtpropertybrowserTargets.cmake)
endif()
