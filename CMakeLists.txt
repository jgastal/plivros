#just to avoid unnescessary warning
cmake_minimum_required( VERSION 2.6 )

project( plivros )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

option( DEBUG "Build with debugger symbols." ON )
option( WIN32 "If building for windows OS." OFF )

enable_language( C )
find_package( Qt4 REQUIRED QtCore QtGUI )
include( ${QT_USE_FILE} )

# Path to DataBaseWrapper project
set( DBWRAPPER_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../DataBaseWrapper/ )
# Path to DataBaseWrapper headers
set( DBWRAPPER_INC_DIR ${DBWRAPPER_ROOT}/src/ )
# Path to RatingWidget headers, CHANGE THIS TO SOMETHING BETTER
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../RatingWidgetPlugin )
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../RatingWidgetPlugin )
# Path to HoverPushButton headers, CHANGE THIS TO SOMETHING BETTER
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../HoverPushButton )
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../HoverPushButton )

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

add_subdirectory( imgs )
add_subdirectory( src )
