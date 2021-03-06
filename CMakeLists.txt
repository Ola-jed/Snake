cmake_minimum_required(VERSION 3.17)
project(Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets)
if( NOT Qt6_FOUND )
    set(QT_VERSION 5)
else()
    set(QT_VERSION 6)
endif()

set(REQUIRED_LIBS Core Gui Widgets Sql Multimedia)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Sql Qt${QT_VERSION}::Multimedia)

add_executable(${PROJECT_NAME} main.cpp include/style.hpp src/scoremanager.cpp include/scoremanager.hpp src/snake.cpp include/snake.hpp resources.qrc)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wunused")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()
include_directories(${Snake_SOURCE_DIR}/include)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})