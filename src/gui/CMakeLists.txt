include_directories( "${CMAKE_SOURCE_DIR}/UI/" )
include_directories( . )

set( LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/gui" )

set( headers
	Window.h )
set( sources
	Window.cpp )

add_definitions( -fpic )

add_library( gui SHARED ${headers} ${sources} )
