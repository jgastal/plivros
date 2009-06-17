#DataBaseWrapper library dir
link_directories( ${DBWRAPPER_LINK_DIR} )

#includes from this project
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

add_executable( plivros main.cpp )
target_link_libraries( plivros collection data gui ${QT_LIBRARIES} )
if( WIN32 )
	SET_TARGET_PROPERTIES( plivros PROPERTIES LINK_FLAGS -Wl,-subsystem,windows )
	add_definitions( -DIMGS_FOLDER=".\imgs\ " )
	add_definitions( -DFONTS_FOLDER=".\fonts\ " )
else( WIN32 )
	add_definitions( -DIMGS_FOLDER="/usr/share/plivros/" )
	add_definitions( -DFONTS_FOLDER="/usr/share/fonts/misc/ " )
endif( WIN32 )

add_dependencies( plivros gui collection data )
