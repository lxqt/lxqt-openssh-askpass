cmake_minimum_required( VERSION 2.6 )

# additional cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project( lxqt-openssh-askpass )

if (NOT CMAKE_BUILD_TYPE)
    set ( CMAKE_BUILD_TYPE Release )
endif (NOT CMAKE_BUILD_TYPE)

add_definitions ( -Wall )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(USE_QT5 "Build with Qt5." $ENV{USE_QT5})
if(USE_QT5)
    find_package(Qt5Widgets REQUIRED QUIET)
    find_package(Qt5LinguistTools REQUIRED QUIET)

    find_package(lxqt-qt5 REQUIRED QUIET)

    set(QTX_INCLUDE_DIRS ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR})
    set(QTX_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
else()
    find_package(Qt4 REQUIRED)
    include(${QT_USE_FILE})

    find_package(LXQT REQUIRED)
    set(QTX_INCLUDE_DIRS ${Qt4Widgets_INCLUDE_DIR})
    set(QTX_LIBRARIES ${Qt4Widgets_LIBRARY})
endif()

include(${LXQT_USE_FILE})

include_directories (
    ${LXQT_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QTX_INCLUDE_DIRS}
    src
)

set ( lxqt-openssh-askpass_HDRS
    src/mainwindow.h
    )

set ( lxqt-openssh-askpass_SRCS
    src/main.cpp
    src/mainwindow.cpp
    )

set ( lxqt-openssh-askpass_UIS
        src/mainwindow.ui
        )

# Translations **********************************
include(LxQtTranslate)
lxqt_translate_ts(QM_FILES
    SOURCES
        ${lxqt-openssh-askpass_HDRS}
        ${lxqt-openssh-askpass_SRCS}
        ${lxqt-openssh-askpass_UIS}
)
#************************************************

if(USE_QT5)
    qt5_wrap_cpp(MOCS ${lxqt-openssh-askpass_HDRS})
    qt5_wrap_ui(UIS ${lxqt-openssh-askpass_UIS})
else()
    qt4_wrap_cpp(MOCS ${lxqt-openssh-askpass_HDRS})
    qt4_wrap_ui(UIS ${lxqt-openssh-askpass_UIS})
endif()

add_executable ( lxqt-openssh-askpass ${lxqt-openssh-askpass_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} ${QM_FILES} )
target_link_libraries(lxqt-openssh-askpass ${QTX_LIBRARIES} ${LXQT_LIBRARIES})
INSTALL(TARGETS lxqt-openssh-askpass RUNTIME DESTINATION bin)


# building tarball with CPack -------------------------------------------------
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR ${LXQT_MAJOR_VERSION})
set (CPACK_PACKAGE_VERSION_MINOR ${LXQT_MINOR_VERSION})
set (CPACK_PACKAGE_VERSION_PATCH ${LXQT_PATCH_VERSION})
set (CPACK_GENERATOR TBZ2)
set (CPACK_SOURCE_GENERATOR TBZ2)
set (CPACK_SOURCE_IGNORE_FILES /build/;.gitignore;.*~;.git;.kdev4;temp)
include (CPack)
