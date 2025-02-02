cmake_minimum_required(VERSION 3.0)
project(webdev VERSION 0.0.1 DESCRIPTION "networking library")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)

add_library(webdev SHARED
    cpp/requests.cpp
)

set_target_properties(webdev PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(webdev PROPERTIES PUBLIC_HEADER include/requests.hpp)

target_include_directories(webdev PRIVATE include)
target_include_directories(webdev PRIVATE shared)

include(GNUInstallDirs)
install(TARGETS webdev
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/webdev)

install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
