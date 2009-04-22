/**
 * @file EditBook.h
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITBOOK_H
#define EDITBOOK_H

#include "BookForm.h"

#include "Book.h"
#include "Publisher.h"
#include "Author.h"
#include "Theme.h"

class Collection;

/**
 * @class EditBook EditBook.h
 *
 * @brief This widget is a form to add a book.
 */
class EditBook : public BookForm
{
	Q_OBJECT

	public:
		EditBook(Collection *c, Book b, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Book b;
		void setSelectedThemes(QList<Theme> tList);
		void setSelectedAuthors(QList<Author> aList);
		void setSelectedTranslator(Author a);
		void setSelectedPublishers(QList<Publisher> pList);
} ;

#endif //EDITBOOK_H
