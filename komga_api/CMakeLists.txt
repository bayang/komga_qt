cmake_minimum_required(VERSION 3.1.0)

project(komga-api)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core)
find_package(Qt5Network)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(komga-api
    book.cpp
    bookmetadata.cpp
    bookmodel.cpp
    komga_api.cpp
    library.cpp
    librarymodel.cpp
    mastercontroller.cpp
    networkinformer.cpp
    series.cpp
    seriesfiltersortproxymodel.cpp
    seriesmodel.cpp
    book.h
    bookmetadata.h
    bookmodel.h
    komga_api_global.h
    komga_api.h
    library.h
    librarymodel.h
    mastercontroller.h
    networkinformer.h
    series.h
    seriesfiltersortproxymodel.h
    seriesmodel.h
)
target_compile_definitions(komga-api PUBLIC "$<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>")
target_link_libraries(komga-api Qt5::Core)
target_link_libraries(komga-api Qt5::Network)
