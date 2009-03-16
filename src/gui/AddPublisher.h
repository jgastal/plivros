/**
 * @file AddPublisher.h
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef ADDPUBLISHER_H
#define ADDPUBLISHER_H

#include "PublisherForm.h"

#include "Theme.h"

class Collection;

/**
 * @class AddPublisher AddPublisher.h
 *
 * @brief This widget is a form to add a publisher.
 */
class AddPublisher : public PublisherForm
{
	Q_OBJECT

	public:
		AddPublisher(Collection *c, QWidget *parent = 0);

	private slots:
		void save();
} ;

#endif //ADDPUBLISHER_H
