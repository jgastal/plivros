set( UI_FILES
	MainWindow.ui )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/UI/ )
foreach( ui ${UI_FILES} )
	string(REPLACE ".ui" ".h" out "${ui}")
	set( out "ui_"${out} )
	string(REPLACE ";" "" out "${out}")
	QT4_WRAP_UI( ${out} ${ui} )
endforeach( ui )
