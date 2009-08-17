#Create translation files
set( TS_FILES
	"plivros_pt_BR.ts" )

QT4_ADD_TRANSLATION( qm_files ${CMAKE_CURRENT_SOURCE_DIR}/${TS_FILES} )

add_custom_target(ts DEPENDS ${qm_files} )

if( WIN32 )
	install( FILES ${qm_files} DESTINATION bin )
else( WIN32 )
	install( FILES ${qm_files} DESTINATION share/plivros )
endif( WIN32 )
