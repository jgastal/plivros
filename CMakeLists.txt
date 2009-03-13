#just to avoid unnescessary warning
cmake_minimum_required( VERSION 2.6 )

project( plivros )

option( DEBUG "Build with debugger symbols" ON )

enable_language( C )
find_package( Qt4 REQUIRED QtCore QtGUI )
include( ${QT_USE_FILE} )

# Path to DataBaseWrapper project
set( DBWRAPPER_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../DataBaseWrapper/ )
# Path to DataBaseWrapper headers
set( DBWRAPPER_INC_DIR ${DBWRAPPER_ROOT}/src/ )

if( DEBUG )
	add_definitions( -O0 -g3 )
	set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Debug/ )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Debug )
else( DEBUG )
	add_definitions( -g0 -O3 )
	add_definitions( -DQT_NO_DEBUG )
	set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Release/ )
	set( DBWRAPPER_LINK_DIR ${DBWRAPPER_ROOT}/Release )
endif( DEBUG )

add_subdirectory( src )
add_subdirectory( UI )
add_subdirectory( ts )