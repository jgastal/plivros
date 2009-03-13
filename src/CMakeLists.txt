include_directories( . ../UI/ ${DBWRAPPER_INC_DIR} )
link_directories( ${DBWRAPPER_LINK_DIR} )

set( headers
	Collection.h
	BookCollection.h
	AuthorCollection.h
	PublisherCollection.h
	ThemeCollection.h
	Book.h
	Author.h
	Publisher.h
	Theme.h
	GenericSQL.h )
set( sources
	main.cpp
	Collection.cpp
	BookCollection.cpp
	AuthorCollection.cpp
	PublisherCollection.cpp
	ThemeCollection.cpp
	Book.cpp
	Author.cpp
	Publisher.cpp
	Theme.cpp
	GenericSQL.cpp )

add_executable( plivros ${headers} ${sources} )
target_link_libraries( plivros DataBaseWrapper ${QT_LIBRARIES} )
