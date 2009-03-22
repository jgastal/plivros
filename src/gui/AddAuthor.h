/**
 * @file AddAuthor.h
 *
 * @date 22/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include "AuthorForm.h"

#include "Theme.h"

class Collection;

/**
 * @class AddAuthor AddAuthor.h
 *
 * @brief This widget is a form to add a publisher.
 */
class AddAuthor : public AuthorForm
{
	Q_OBJECT

	public:
		AddAuthor(Collection *c, QWidget *parent = 0);

	private slots:
		void save();
} ;

#endif //ADDAUTHOR_H
