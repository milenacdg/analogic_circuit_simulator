# This file describes the building process.

cmake_minimum_required(VERSION 3.10)
project(circuit)

# Global description
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(PACKAGE_VERSION "1.00")
SET(PACKAGE_LICENSE "GPL")
SET(PROJECT_DESCRIPTION_SUMMARY "Library that simulates electrical circuits")

# This is C++ compiling settings
SET(CMAKE_BUILD_TYPE Debug)
SET(PROJECT_CFLAGS "-std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This tells where our .hpp will be installed.
SET(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}/" CACHE PATH "The subdirectory to the header prefix")


# Create pkg-config file
# if we need a library : add "Requires: library_name" after Version
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pc
"
Name: ${CMAKE_PROJECT_NAME}
Description: ${PROJECT_DESCRIPTION_SUMMARY}
Version: ${PACKAGE_VERSION}    
Libs: -l${CMAKE_PROJECT_NAME}
Cflags: -I\${includedir}
"
)

set(PKGCONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pc
        DESTINATION ${PKGCONFIG_INSTALL_DIR}
        COMPONENT devel)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)

add_subdirectory(livrables)