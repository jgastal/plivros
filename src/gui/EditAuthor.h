/**
 * @file EditAuthor.h
 *
 * @date 22/04/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITAUTHOR_H
#define EDITAUTHOR_H

#include "AuthorForm.h"

#include "Author.h"
#include "Theme.h"

class Collection;

/**
 * @class EditAuthor EditAuthor.h
 *
 * @brief This widget is a form to add a author.
 */
class EditAuthor : public AuthorForm
{
	Q_OBJECT

	public:
		EditAuthor(Collection *c, Author p, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Author a;
		void setSelectedThemes(QList<Theme> tList);
} ;

#endif //EDITAUTHOR_H
