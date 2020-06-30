cmake_minimum_required(VERSION 3.1.0)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

message(STATUS ${CMAKE_SOURCE_DIR})

if(EXISTS ${CMAKE_SOURCE_DIR}/.git/)
    execute_process(
            COMMAND git rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

            OUTPUT_VARIABLE GIT_SHA
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (GIT_SHA STREQUAL "")
        set(GIT_SHA 0)
    endif()
else()
    set(VERSION_TWEAK 0)
endif()

project(komga-app VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

message(STATUS "komga-app version ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fno-sized-deallocation")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(komga_ui)
add_subdirectory(komga_api)
