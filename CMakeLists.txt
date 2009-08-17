#just to avoid unnescessary warning
cmake_minimum_required( VERSION 2.6 )

project( plivros )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

option( DEBUG "Build with debugger symbols." ON )

enable_language( C )
find_package( Qt4 REQUIRED QtCore QtGUI )
set( QT_USE_QTMAIN 1 )
include( ${QT_USE_FILE} )

#Also search for modules in the project roo
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} )
find_package( DataBaseWrapper REQUIRED )
include_directories( ${DBWRAPPER_INCLUDE_DIR} )

#lib dirs for HoverPushButton and RatingWidgetPlugin
link_directories( ${QT_PLUGINS_DIR}/designer )

if( DEBUG )
	add_definitions( -O0 -g3 )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Debug )
else( DEBUG )
	add_definitions( -g0 -O3 )
	add_definitions( -DQT_NO_DEBUG )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Release )
endif( DEBUG )

if( WIN32 )
	add_definitions( -DWIN32 )
endif( WIN32 )

if( NOT DEFINED LIB_DIR )
	if( WIN32 )
                set( LIB_DIR "${CMAKE_INSTALL_PREFIX}/plivros/" )
        else( WIN32 )
                set( LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/" )
	endif( WIN32 )
endif( NOT DEFINED LIB_DIR )

add_subdirectory( imgs )
add_subdirectory( ts )
add_subdirectory( src )
