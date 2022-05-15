cmake_minimum_required(VERSION 3.10)
project(color_theme_manager)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Xml Gui Network Core LinguistTools REQUIRED)
qt5_wrap_ui(UI_HEADERS
        ui/mainwindow.ui
        ui/openthemeitem.ui
        ui/themeeditor.ui
        ui/colorpairitem.ui)

qt5_add_resources(QRC_FILES assets/resources.qrc)
qt5_add_translation(QM_FILES assets/lang/color_theme_manager_en.ts)


add_executable(color_theme_manager
        src/main.cpp
        src/Widgets/mainwindow.cpp
        src/Widgets/openthemeitem.cpp
        src/Widgets/themeeditor.cpp
        src/Widgets/colorpairitem.cpp
        src/colorPair.cpp
        src/xmlReader.cpp
        src/theme.cpp
        src/filedownloader.cpp

        include/xmlReader.h
        include/colorPair.h
        include/Widgets/mainwindow.h
        include/Widgets/openthemeitem.h
        include/Widgets/themeeditor.h
        include/Widgets/colorpairitem.h
        include/theme.h
        include/filedownloader.h
        include/utils.h

        ${QRC_FILES}

        ${UI_HEADERS}

        ${QM_FILES})

target_link_libraries(color_theme_manager
        Qt5::Core Qt5::Network Qt5::Xml Qt5::Gui Qt5::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
