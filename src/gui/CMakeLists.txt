include_directories( . )

set( LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/gui" )

set( headers
	MainWindow.h
	SearchForm.h
	ThemeForm.h
	AddTheme.h
	EditTheme.h
	PublisherForm.h
	AddPublisher.h
	EditPublisher.h
	AuthorForm.h
	AddAuthor.h
	BookForm.h
	AddBook.h
	CategoryFrame.h
	PropertiesGroupBox.h
	DataTableWidget.h
	MessageBoxDataBaseException.h )
set( sources
	MainWindow.cpp
	SearchForm.cpp
	ThemeForm.cpp
	AddTheme.cpp
	EditTheme.cpp
	PublisherForm.cpp
	AddPublisher.cpp
	EditPublisher.cpp
	AuthorForm.cpp
	AddAuthor.cpp
	BookForm.cpp
	AddBook.cpp
	CategoryFrame.cpp
	PropertiesGroupBox.cpp
	DataTableWidget.cpp
	MessageBoxDataBaseException.cpp )
set( UI_FILES
	"UI/MainWindow.ui"
	"UI/ThemeForm.ui"
	"UI/PublisherForm.ui"
	"UI/AuthorForm.ui"
	"UI/BookForm.ui"
	"UI/SearchForm.ui"
	"UI/CategoryFrame.ui" )
set( RC_FILES
	"imgs.qrc" )

qt4_wrap_ui( ui_out ${UI_FILES} )
#The gui headers include uic generated files
MACRO_ADD_FILE_DEPENDENCIES( ${headers} ${ui_out} )
#uic generated files are here
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

#Need to create moc files so that signal and slots will work
qt4_wrap_cpp( moc_sources ${headers} )

#Create resource file(puts images in executable)
qt4_add_resources( rc_sources ${RC_FILES} )

add_definitions( -fpic )

add_library( gui SHARED ${headers} ${sources} ${moc_sources} ${rc_sources} )
target_link_libraries( gui RatingWidgetPlugin HoverPushButton )
