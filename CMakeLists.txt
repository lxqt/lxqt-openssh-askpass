cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

project(lxqt-openssh-askpass)

add_definitions(-Wall)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

find_package(Qt5LinguistTools REQUIRED)
find_package(Qt5Widgets REQUIRED)
message(STATUS "Building with Qt${Qt5Core_VERSION}")

find_package(lxqt REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Patch Version
set(LXQT_ASKPASS_PATCH_VERSION 0)

set(LXQT_ASKPASS_VERSION ${LXQT_MAJOR_VERSION}.${LXQT_MINOR_VERSION}.${LXQT_ADMIN_ASKPASS_VERSION})
add_definitions("-DLXQT_ASKPASS_VERSION=\"${LXQT_ASKPASS_VERSION}\"")

include(LXQtCompilerSettings NO_POLICY_SCOPE)

set(lxqt-openssh-askpass_HDRS
    src/mainwindow.h
)

set(lxqt-openssh-askpass_SRCS
    src/main.cpp
    src/mainwindow.cpp
)

set(lxqt-openssh-askpass_UIS
    src/mainwindow.ui
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Translations **********************************
include(LXQtTranslate)

lxqt_translate_ts(QM_FILES
    UPDATE_TRANSLATIONS
        ${UPDATE_TRANSLATIONS}
    SOURCES
        ${lxqt-openssh-askpass_HDRS}
        ${lxqt-openssh-askpass_SRCS}
        ${lxqt-openssh-askpass_UIS}
    INSTALL_DIR
        "${LXQT_TRANSLATIONS_DIR}/${PROJECT_NAME}"
    PULL_TRANSLATIONS
        ${PULL_TRANSLATIONS}
    CLEAN_TRANSLATIONS
        ${CLEAN_TRANSLATIONS}
    TRANSLATIONS_REPO
        ${TRANSLATIONS_REPO}
    TRANSLATIONS_REFSPEC
        ${TRANSLATIONS_REFSPEC}
)

lxqt_app_translation_loader(lxqt-openssh_QM_LOADER ${PROJECT_NAME})
#************************************************

add_executable(lxqt-openssh-askpass
    ${lxqt-openssh-askpass_SRCS}
    ${TRS}
    ${QM_FILES}
    ${lxqt-openssh_QM_LOADER}
)
target_link_libraries(lxqt-openssh-askpass
    Qt5::Widgets
    lxqt
)

INSTALL(TARGETS
    lxqt-openssh-askpass
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)
