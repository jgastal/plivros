include_directories( . ${CMAKE_SOURCE_DIR}/src/data ${DBWRAPPER_INC_DIR} )
link_directories( ${DBWRAPPER_LINK_DIR} )

set( LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/core )

set( headers
	Collection.h
	BookCollection.h
	AuthorCollection.h
	PublisherCollection.h
	ThemeCollection.h
	GenericSQL.h )
set( sources
	Collection.cpp
	BookCollection.cpp
	AuthorCollection.cpp
	PublisherCollection.cpp
	ThemeCollection.cpp
	GenericSQL.cpp )

add_definitions( -fpic )

add_library( collection SHARED ${headers} ${sources} )
target_link_libraries( collection DataBaseWrapper )
