#Create resource file(puts images in executable)
set( RC_FILES
	"imgs.qrc" )

add_custom_target( imgs ${QT_RCC_EXECUTABLE} -binary -compress 9 -o imgs.bqrc ${CMAKE_CURRENT_SOURCE_DIR}/${RC_FILES} )

install( FILES ${CMAKE_CURRENT_BINARY_DIR}/imgs.bqrc DESTINATION share/plivros )
