include_directories( . ${DBWRAPPER_INC_DIR} ${QT4_INC_DIR} )
link_directories( ${DBWRAPPER_LINK_DIR} ${QT4_LINK_DIR} )
link_libraries( DataBaseWrapper QtCore sqlite3 )

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