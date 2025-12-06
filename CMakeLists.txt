cmake_minimum_required(VERSION 3.16)

project(sans_titre VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AJOUTEZ Charts ici ↓
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
    Sql
    PrintSupport
    Network
    SerialPort
    Charts  # ← AJOUTEZ CETTE LIGNE
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
    Sql
    PrintSupport
    Network
    SerialPort
    Charts  # ← AJOUTEZ CETTE LIGNE
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    connection.cpp
    connection.h
    client.cpp
    client.h
    employe.cpp
    employe.h
    projet.cpp
    projet.h
    finance.cpp
    finance.h
    equipement.cpp
    equipement.h
    pdfexporter.cpp
    pdfexporter.h
    emailsmtpmanager.h
    emailsmtpmanager.cpp
    rfidmanager.cpp
    rfidmanager.h
    chatbotdialog.h chatbotdialog.cpp
    chatbotdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sans_titre
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(sans_titre SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(sans_titre
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# AJOUTEZ Charts ici aussi ↓
target_link_libraries(sans_titre PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::Charts  # ← AJOUTEZ CETTE LIGNE
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sans_titre)
endif()

set_target_properties(sans_titre PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS sans_titre
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sans_titre)
endif()
