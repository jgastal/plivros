#just to avoid unnescessary warning
cmake_minimum_required(VERSION 2.6)

option( DEBUG "Build with debugger symbols" ON )

enable_language( C )
find_package( Qt4 REQUIRED QtCore )
set( QT_DONT_USE_QTGUI TRUE )
include( ${QT_USE_FILE} )

set( INC_PATH /usr/include/ )
set( LINK_PATH /usr/lib/ )

# Path to DataBaseWrapper project
set( DBWRAPPER_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../DataBaseWrapper/ )
# Path to DataBaseWrapper headers
set( DBWRAPPER_INC_DIR ${DBWRAPPER_ROOT}/src/ )

if(DEBUG)
	add_definitions( -O0 -g3 )
	set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Debug/ )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Debug )
else(DEBUG)
	add_definitions( -g0 -O3 )
	set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Release/ )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Release )
endif(DEBUG)

project(plivros)
add_subdirectory(src)