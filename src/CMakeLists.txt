link_directories( ${EXECUTABLE_OUTPUT_PATH}/core/ )
link_directories( ${EXECUTABLE_OUTPUT_PATH}/data/ )
link_directories( ${EXECUTABLE_OUTPUT_PATH}/gui/ )
link_directories( ${DBWRAPPER_LINK_DIR} )


add_subdirectory( gui )
add_subdirectory( core )
add_subdirectory( data )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/data )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/core )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/gui )
include_directories( ${CMAKE_SOURCE_DIR}/UI )
include_directories( ${DBWRAPPER_INC_DIR} )

add_executable( plivros main.cpp )
target_link_libraries( plivros collection data gui ${QT_LIBRARIES} )
