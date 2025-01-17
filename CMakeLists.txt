cmake_minimum_required(VERSION 3.0)
project(webdev VERSION 0.0.1 DESCRIPTION "a networking library")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(webdev SHARED
    cpp/RequestHandler.cpp
)

set_target_properties(webdev PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(webdev PROPERTIES PUBLIC_HEADER include/RequestHandler.hpp)

target_include_directories(webdev PRIVATE include)

include(GNUInstallDirs)
install(TARGETS webdev
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/webdev
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/webdev)

install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
