cmake_minimum_required(VERSION 3.1.0)

project(komga-ui VERSION "${CMAKE_PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Make Qt Creator aware of where the QML modules live
set (_QML_IMPORT_PATHS "")

## Add new module paths here.
list (APPEND _QML_IMPORT_PATHS ${CMAKE_CURRENT_SOURCE_DIR})

set (
    QML_IMPORT_PATH
    ${_QML_IMPORT_PATHS}
    CACHE
    STRING
    "Path used to locate CMake modules by Qt Creator"
    FORCE
)

find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Network Qml Quick QuickControls2)

# otherwise imports from api in ui fail
# is it normal ?
include_directories(../komga_api)

configure_file(KomgaConfig.h.in KomgaConfig.h)

if(APPLE)
add_executable(komga-ui MACOSX_BUNDLE
    asyncimageprovider.cpp
    asyncimageprovider.h
    asyncimageresponse.cpp
    asyncimageresponse.h
    bookpageprovider.cpp
    bookpageprovider.h
    main.cpp
    assets.qrc
    qml.qrc
)
elseif(WIN32)
    add_executable(komga-ui WIN32
        asyncimageprovider.cpp
        asyncimageprovider.h
        asyncimageresponse.cpp
        asyncimageresponse.h
        bookpageprovider.cpp
        bookpageprovider.h
        main.cpp
        assets.qrc
        qml.qrc
    )
else()
add_executable(komga-ui
    asyncimageprovider.cpp
    asyncimageprovider.h
    asyncimageresponse.cpp
    asyncimageresponse.h
    bookpageprovider.cpp
    bookpageprovider.h
    main.cpp
    assets.qrc
    qml.qrc
)
endif()

target_include_directories(komga-ui PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
target_compile_definitions(komga-ui PUBLIC "$<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>")
target_link_libraries(komga-ui PUBLIC komga-api Qt5::Core Qt5::Quick Qt5::QuickControls2)
