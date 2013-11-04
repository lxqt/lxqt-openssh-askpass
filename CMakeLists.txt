cmake_minimum_required( VERSION 2.6 )

# additional cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project( lxqt-openssh-askpass )

if (NOT CMAKE_BUILD_TYPE)
    set ( CMAKE_BUILD_TYPE Release )
endif (NOT CMAKE_BUILD_TYPE)

add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )

find_package(LXQT REQUIRED)
include(${LXQT_USE_FILE})

include_directories (
    ${LXQT_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
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

QT4_WRAP_CPP(MOCS ${lxqt-openssh-askpass_HDRS})
QT4_WRAP_UI(UIS ${lxqt-openssh-askpass_UIS})


add_executable ( lxqt-openssh-askpass ${lxqt-openssh-askpass_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} ${QM_FILES} )
target_link_libraries(lxqt-openssh-askpass ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${LXQT_LIBRARIES})
INSTALL(TARGETS lxqt-openssh-askpass RUNTIME DESTINATION bin)
