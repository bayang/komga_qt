cmake_minimum_required(VERSION 3.1.0)

project(komga-ui)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Network Qml Quick QuickControls2)

# otherwise imports from api in ui fail
# is it normal ?
include_directories(../komga_api)

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

target_link_libraries(komga-ui PUBLIC komga-api Qt5::Core Qt5::Quick Qt5::QuickControls2)
