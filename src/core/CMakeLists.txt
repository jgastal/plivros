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

set( moc_in
	Collection.h )

qt4_wrap_cpp( moc_out ${moc_in} )

add_definitions( -fpic )

add_library( collection SHARED ${headers} ${sources} ${moc_out} )
target_link_libraries( collection data ${DBWRAPPER_LIBRARIES} ${QT_LIBRARIES} )

install( TARGETS collection LIBRARY DESTINATION ${LIB_DIR} )

