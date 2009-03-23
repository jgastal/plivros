/**
 * @file AddBook.h
 *
 * @date 23/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef ADDBOOK_H
#define ADDBOOK_H

#include "BookForm.h"

class Collection;

/**
 * @class AddBook AddBook.h
 *
 * @brief This widget is a form to add a publisher.
 */
class AddBook : public BookForm
{
	Q_OBJECT

	public:
		AddBook(Collection *c, QWidget *parent = 0);

	private slots:
		void save();
} ;

#endif //ADDBOOK_H
