/**
 * @file BookForm.h
 *
 * @date 23/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef BOOKFORM_H
#define BOOKFORM_H

#include "ui_BookForm.h"

#include "Data.h"

class Collection;

/**
 * @class BookForm BookForm.h
 *
 * @brief This class is a form containing all books fields.
 */
class BookForm : public QWidget, protected Ui::BookForm
{
	Q_OBJECT

	public:
		BookForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();
		void populatePublishersListWidget();
		void populateAuthorsListWidget();
		void populateTranslatorListWidget();

	protected slots:
		virtual void save() = 0;
		void coverFileChooser();
		void ebookFileChooser();

	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		QList<Publisher> getSelectedPublishers();
		QList<Author> getSelectedAuthors();
		Author getSelectedTranslator();
		Collection *c;
		QList<Theme> themeList;
		QList<Publisher> publisherList;
		QList<Author> authorList;

	signals:
		void closeRequested();
} ;

#endif //BOOKFORM_H
