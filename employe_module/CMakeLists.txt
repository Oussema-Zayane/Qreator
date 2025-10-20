cmake_minimum_required(VERSION 3.16)
project(untitled3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Widgets PrintSupport Sql)

add_executable(untitled3
    main.cpp
    mainwindow.cpp
    mainwindow.h
    connection.cpp
    connection.h
    employe.cpp
    employe.h
    absence.cpp
    absence.h
)

target_link_libraries(untitled3 PRIVATE Qt6::Widgets Qt6::PrintSupport Qt6::Sql)
