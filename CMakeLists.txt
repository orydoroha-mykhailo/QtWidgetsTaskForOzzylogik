cmake_minimum_required(VERSION 3.5)

project(QtWidgetsTaskForOzzylogik VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        database_manager.cpp
        database_manager.h
        countries_table_manager.cpp
        countries_table_manager.h
        operators_table_manager.cpp
        operators_table_manager.h
        operator_editor_dialog.cpp
        operator_editor_dialog.h
        data_model.cpp
        data_model.h
        data_item.cpp
        data_item.h
        icon_delegate.cpp
        icon_delegate.h
        Assets.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtWidgetsTaskForOzzylogik
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtWidgetsTaskForOzzylogik APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtWidgetsTaskForOzzylogik SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtWidgetsTaskForOzzylogik
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtWidgetsTaskForOzzylogik PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QtWidgetsTaskForOzzylogik PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtWidgetsTaskForOzzylogik
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtWidgetsTaskForOzzylogik)
endif()

target_link_libraries(QtWidgetsTaskForOzzylogik PRIVATE Qt6::Sql)
