cmake_minimum_required(VERSION 3.5.0)
project(snap-installation-monitor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)

add_executable(snap-installation-monitor main.cpp)
target_link_libraries(snap-installation-monitor Qt5::Widgets Qt5::DBus)
