/**
 * @file EditPublisher.h
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef EDITPUBLISHER_H
#define EDITPUBLISHER_H

#include "PublisherForm.h"

#include "Publisher.h"
#include "Theme.h"

class Collection;

/**
 * @class EditPublisher EditPublisher.h
 *
 * @brief This widget is a form to add a publisher.
 */
class EditPublisher : public PublisherForm
{
	Q_OBJECT

	public:
		EditPublisher(Collection *c, Publisher p, QWidget *parent = 0);

	private slots:
		void save();

	private:
		Publisher p;
		void setSelectedThemes(QList<Theme> tList);
} ;

#endif //EDITPUBLISHER_H
