cmake_minimum_required(VERSION 3.16)

project(tableViewHoosham VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apptableViewHoosham
    main.cpp
)

qt_add_qml_module(apptableViewHoosham
    URI tableViewHoosham
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    RESOURCES icons.qrc
    SOURCES
    QML_FILES
    QML_FILES
    SOURCES
    QML_FILES
    QML_FILES
    QML_FILES
    RESOURCES icons/airplane.png icons/motor.png icons/rocket.png icons/taxi.png icons/taxii.jpg icons/train.png
    RESOURCES icons.qrc
    RESOURCES icons/aircraft-icon.jpg icons/battle-icon.jpg icons/close-icon.jpg icons/down-icon.jpg icons/left-icon.jpg icons/more-icon.jpg icons/right-icon.jpg icons/search-icon.jpg icons/station-icon.jpg icons/system-icon.jpg icons/target-icon.jpg icons/up-icon.jpg
    QML_FILES
    RESOURCES icons/delete-icon.jpg icons/goto-icon.jpg icons/track-icon.jpg
    SOURCES list.h list.cpp
    QML_FILES MyTableView.qml
    RESOURCES Components.qrc
    QML_FILES
    QML_FILES
    QML_FILES Property.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptableViewHoosham PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptableViewHoosham
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_add_resources(apptableViewHoosham Components
    FILES MyTableView.qml icons
)

target_link_libraries(apptableViewHoosham
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apptableViewHoosham
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
