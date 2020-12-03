cmake_minimum_required(VERSION 3.5)

project(ApplicationLauncher LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(HAVE_X11 ON)

find_package(Qt5 COMPONENTS Widgets DBus LinguistTools REQUIRED)
if(HAVE_X11)
    find_package(Qt5X11Extras)
    find_package(X11)
    add_definitions(-DHAVE_X11)
endif()
find_package(Qt5Xdg)

set(PROJECT_SOURCES
    main.cpp
    applicationlauncher.cpp
    applicationlauncher.h
    launcheritem.cpp
    launcheritem.h
)

set(LANGUAGES de es fr)
foreach(LANGUAGE ${LANGUAGES})
    set(TS_FILES ${TS_FILES} translations/${LANGUAGE}.ts)
endforeach(LANGUAGE)

qt5_create_translation(QM_FILES
    ${PROJECT_SOURCES}
    ${TS_FILES}
)

add_executable(ApplicationLauncher
    ${PROJECT_SOURCES}
    ${QM_FILES}
)

target_link_libraries(ApplicationLauncher PRIVATE Qt5::Widgets Qt5::DBus Qt5Xdg)
if (HAVE_X11)
    target_link_libraries(ApplicationLauncher PRIVATE Qt5X11Extras X11)
endif()

install(TARGETS ApplicationLauncher RUNTIME DESTINATION bin)
