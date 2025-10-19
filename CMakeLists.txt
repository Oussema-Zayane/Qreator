cmake_minimum_required(VERSION 3.16)
project(untitled3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt meta-object / uic / rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt 6.7 Widgets + PrintSupport (for QPrinter)
find_package(Qt6 6.7 REQUIRED COMPONENTS Widgets PrintSupport)

# Use add_executable (avoids qt_add_executable)
add_executable(untitled3
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

# Link Qt libraries
target_link_libraries(untitled3 PRIVATE Qt6::Widgets Qt6::PrintSupport)
