set( LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/data )

set( headers
	DataObject.h
	Book.h
	Author.h
	Publisher.h
	Theme.h )
set( sources
	DataObject.cpp
	Book.cpp
	Author.cpp
	Publisher.cpp
	Theme.cpp )

add_definitions( -fpic )

add_library( data SHARED ${headers} ${sources} )
target_link_libraries( data ${QT_LIBRARIES} )

install( TARGETS data LIBRARY DESTINATION lib )

