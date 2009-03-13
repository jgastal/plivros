/**
 * @file PublisherCollection.h
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#ifndef PUBLISHERCOLLECTION_H_
#define PUBLISHERCOLLECTION_H_

#include <QtCore/QList>

#include "Publisher.h"
#include "DataBaseException.h"

class DataBase;

class PublisherCollection
{
	public:
		PublisherCollection(DataBase *db) throw();

		void insertPublisher(Publisher &p) throw(DataBaseException);
		bool deletePublisher(unsigned int id) throw(DataBaseException);
		void updatePublisher(Publisher p) throw(DataBaseException);

	private:
		DataBase *db;
};

#endif /* PUBLISHERCOLLECTION_H_ */