set( LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/data )

set( headers
	Book.h
	Author.h
	Publisher.h
	Theme.h )
set( sources
	Book.cpp
	Author.cpp
	Publisher.cpp
	Theme.cpp )

add_definitions( -fpic )

add_library( data SHARED ${headers} ${sources} )
