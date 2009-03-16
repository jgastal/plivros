include_directories( . )

set( LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/gui" )

set( headers
	MainWindow.h
	ThemeForm.h
	AddTheme.h
	PublisherForm.h
	AddPublisher.h
	MessageBoxDataBaseException.h )
set( sources
	MainWindow.cpp
	ThemeForm.cpp
	AddTheme.cpp
	PublisherForm.cpp
	AddPublisher.cpp
	MessageBoxDataBaseException.cpp )

#Target for uic generated headers
set( UI_FILES
	"UI/MainWindow.ui"
	"UI/ThemeForm.ui"
	"UI/PublisherForm.ui" )
qt4_wrap_ui( ui_out ${UI_FILES} )
#The gui headers include uic generated files
MACRO_ADD_FILE_DEPENDENCIES( ${headers} ${ui_out} )
#uic generated files are here
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

#Need to create moc files so that signal and slots will work
qt4_wrap_cpp( moc_sources ${headers} )

add_definitions( -fpic )

add_library( gui SHARED ${headers} ${sources} ${moc_sources} )
