#Create resource file(puts images in executable)
set( RC_FILES
	"imgs.qrc" )
qt4_add_resources( rc_sources ${RC_FILES} )

add_library( rcc SHARED ${rc_sources} )
target_link_libraries( rcc ${QT_LIBRARIES} )
