cmake_minimum_required(VERSION 2.8.11)
project(lxqt-openssh-askpass)

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_definitions(-Wall)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5Widgets REQUIRED QUIET)
find_package(Qt5LinguistTools REQUIRED QUIET)

find_package(lxqt REQUIRED QUIET)

include(${LXQT_USE_FILE})

include_directories (
    ${LXQT_INCLUDE_DIRS}
    "${CMAKE_CURRENT_BINARY_DIR}"
    ${QTX_INCLUDE_DIRS}
    src
)

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
)

lxqt_app_translation_loader(lxqt-openssh_QM_LOADER ${PROJECT_NAME})
#************************************************

qt5_wrap_cpp(MOCS ${lxqt-openssh-askpass_HDRS})
qt5_wrap_ui(UIS ${lxqt-openssh-askpass_UIS})

add_executable(lxqt-openssh-askpass
    ${lxqt-openssh-askpass_SRCS}
    ${UIS}
    ${RSCS}
    ${TRS}
    ${MOCS}
    ${QM_FILES}
    ${lxqt-openssh_QM_LOADER}
)
target_link_libraries(lxqt-openssh-askpass
    Qt5::Widgets
    ${LXQT_LIBRARIES}
)

INSTALL(TARGETS lxqt-openssh-askpass RUNTIME DESTINATION bin)


# building tarball with CPack -------------------------------------------------
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR ${LXQT_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${LXQT_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${LXQT_PATCH_VERSION})
set(CPACK_GENERATOR TBZ2)
set(CPACK_SOURCE_GENERATOR TBZ2)
set(CPACK_SOURCE_IGNORE_FILES /build/;.gitignore;.*~;.git;.kdev4;temp)
include(CPack)
