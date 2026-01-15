cmake_minimum_required(VERSION 3.16)

project(PIPAOProj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Backend - Model Classes
set(MODEL_SOURCES
        user.h user.cpp
        vehicle.h vehicle.cpp
        order.h order.cpp
)

# Backend - Service Classes
set(SERVICE_SOURCES
        userservice.h userservice.cpp
        vehicleservice.h vehicleservice.cpp
        orderservice.h orderservice.cpp
)

# Frontend - Dialogs
set(DIALOG_SOURCES
        loginwindow.h loginwindow.cpp loginwindow.ui
        addvehicledialog.h addvehicledialog.cpp addvehicledialog.ui
        addemployeedialog.h addemployeedialog.cpp addemployeedialog.ui
        addorderdialog.h addorderdialog.cpp addorderdialog.ui
)

# Database
set(DATABASE_SOURCES
        databasemanager.h databasemanager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PIPAOProj
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${MODEL_SOURCES}
        ${SERVICE_SOURCES}
        ${DIALOG_SOURCES}
        ${DATABASE_SOURCES}
    )
else()
    if(ANDROID)
        add_library(PIPAOProj SHARED
            ${PROJECT_SOURCES}
            ${MODEL_SOURCES}
            ${SERVICE_SOURCES}
            ${DIALOG_SOURCES}
            ${DATABASE_SOURCES}
        )
    else()
        add_executable(PIPAOProj
            ${PROJECT_SOURCES}
            ${MODEL_SOURCES}
            ${SERVICE_SOURCES}
            ${DIALOG_SOURCES}
            ${DATABASE_SOURCES}
        )
    endif()
endif()

target_link_libraries(PIPAOProj PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PIPAOProj)
endif()

set_target_properties(PIPAOProj PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PIPAOProj
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PIPAOProj)
endif()
