cmake_minimum_required(VERSION 3.5)

project(war_db VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED )
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED )

set(PROJECT_SOURCES
        main.cpp
        wardbwindow.cpp
        wardbwindow.h
        wardbwindow.ui
        assaultriflestablewindow.h
        assaultriflestablewindow.cpp
        assaultriflestablewindow.ui
        insertdialog.h
        insertdialog.cpp
        insertdialog.ui
        unitweaponstable.h
        unitweaponstable.cpp
        unitweaponstable.ui
        warregionwindow.h
        warregionwindow.cpp
        warregionwindow.ui
        placewindow.h placewindow.cpp placewindow.ui
        unittransport.h unittransport.cpp unittransport.ui
        unitconstructionwindow.h unitconstructionwindow.cpp unitconstructionwindow.ui
        rifleswindow.h rifleswindow.cpp rifleswindow.ui
        artillerieswindow.h artillerieswindow.cpp artillerieswindow.ui
        missileweaponswindow.h missileweaponswindow.cpp missileweaponswindow.ui
        infantrycombatvehicleswindow.h infantrycombatvehicleswindow.cpp infantrycombatvehicleswindow.ui
        tankswindow.h tankswindow.cpp tankswindow.ui
        tractorswindow.h tractorswindow.cpp tractorswindow.ui
        vehicleswindow.h vehicleswindow.cpp vehicleswindow.ui
        generalswindow.h generalswindow.cpp generalswindow.ui
        colonelswindow.h colonelswindow.cpp colonelswindow.ui
        lieutenantcolonelswindow.h lieutenantcolonelswindow.cpp lieutenantcolonelswindow.ui
        majorswindow.h majorswindow.cpp majorswindow.ui
        captainswindow.h captainswindow.cpp captainswindow.ui
        lieutenantswindow.h lieutenantswindow.cpp lieutenantswindow.ui
        sergeantmajorswindow.h sergeantmajorswindow.cpp sergeantmajorswindow.ui
        sergeantswindow.h sergeantswindow.cpp sergeantswindow.ui
        ensignswindow.h ensignswindow.cpp ensignswindow.ui
        corporalswindow.h corporalswindow.cpp corporalswindow.ui
        soldierswindow.h soldierswindow.cpp soldierswindow.ui
        militaryunitwindow.h militaryunitwindow.cpp militaryunitwindow.ui
        arrmywindow.h arrmywindow.cpp arrmywindow.ui
        brigadewindow.h brigadewindow.cpp brigadewindow.ui
        corpwindow.h corpwindow.cpp corpwindow.ui
        divisionwindow.h divisionwindow.cpp divisionwindow.ui
        companywindow.h companywindow.cpp companywindow.ui
        platoonwindow.h platoonwindow.cpp platoonwindow.ui
        squadwindow.h squadwindow.cpp squadwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(war_db
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET war_db APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(war_db SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(war_db
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(war_db PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(war_db PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(war_db)
endif()
