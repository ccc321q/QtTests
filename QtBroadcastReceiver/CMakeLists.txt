
cmake_minimum_required(VERSION 3.5.1)
project(DirectoryTest)

# If you do not specify a build type at all, it will default to
# "Release" and thus CMAKE_CXX_FLAGS_RELEASE will be used.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Put the binary into the ../bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set C++ 11 standard
set (CMAKE_CXX_STANDARD 11)

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

set(QT_DIR "/home/c/Qt/5.12.5/gcc_64/")

list(APPEND CMAKE_PREFIX_PATH ${QT_DIR})
find_package(Qt5 COMPONENTS Core Gui Network Widgets REQUIRED)

# Bring the headers into the project
#include_directories(include "{QT_DIR}/include")

include_directories("{QT_DIR}/include")

# Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp src/MainWindow.cpp)

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Uses the SOURCES variable, rather than an explicit reference to
# each source file
add_executable(DirectoryTest ${SOURCES})

target_link_libraries(DirectoryTest
  Qt5::Widgets
  Qt5::Core
  Qt5::Gui
  Qt5::Network
)