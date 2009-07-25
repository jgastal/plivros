#DataBaseWrapper library dir
link_directories( ${DBWRAPPER_LINK_DIR} )

#includes from this project
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/data" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/core" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/gui" )
#include of uic generated headers(they are generated in the build tree, not the source tree)
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/gui" )

#include for DataBaseWrapper
include_directories( ${DBWRAPPER_INC_DIR} )

add_subdirectory( gui )
add_subdirectory( core )
add_subdirectory( data )

# When building normal RPATH
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "${QT_PLUGINS_DIR}/designer/")

add_executable( plivros main.cpp OS.h )
target_link_libraries( plivros collection data gui ${QT_LIBRARIES} )
if( WIN32 )
	SET_TARGET_PROPERTIES( plivros PROPERTIES LINK_FLAGS -Wl,-subsystem,windows )
endif( WIN32 )

add_dependencies( plivros gui collection data )

install( TARGETS plivros DESTINATION bin )
