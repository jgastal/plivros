/**
 * @file PublisherCollection.cpp
 *
 * @date 09/01/2009
 * @author Jonas M. Gastal
 */

#include "PublisherCollection.h"

#include "DataBase.h"
#include "DataBaseException.h"
#include "PreparedStatement.h"

#include "GenericSQL.h"
#include "Publisher.h"

PublisherCollection::PublisherCollection(DataBase *db) throw()
{
	this->db = db;
}


/**
 * @brief Adds publisher \a p to the collection.
 *
 * @param p Publisher to be added.
 *
 * @return Whether the operation was successful.
 *
 * This method creates two SQL commands, one to add the actual publisher and the
 * other one to add the themes associated with it, since internally they are kept
 * in separate tables. After the publisher is inserted in the database its ID is
 * set.
 */
void PublisherCollection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	PreparedStatement insPub("INSERT INTO publishers (name, description, critique,"
		"logo) VALUES ('%1', '%2', '%3', '%4')", db->getType());
	insPub.arg(p.getName());
	insPub.arg(p.getDescription());
	insPub.arg(p.getCritique());
	insPub.arg(p.getLogo());

	p.setId(db->insert(insPub));

	insertThemesReference(p);
}

/**
 * @brief Removes publisher from collection.
 *
 * @param id ID of publisher to be removed.
 *
 * @return Whether operation was successful.
 *
 * This method actually does very little, it just calls generic delete which does
 * all the heavy lifting.
 */
bool PublisherCollection::deletePublisher(unsigned int id) throw(DataBaseException)
{
	if(genericDelete(id, "publisher", db) == 1)
		return true;
	return false;
}

/**
 * @brief Updates publisher.
 *
 * @param p Publisher to be updated.
 *
 * @return Whether the operation was successful.
 *
 * This method constructs an SQL statement that updates every field of the publisher
 * except the id to match the object.
 */
void PublisherCollection::updatePublisher(Publisher p) throw(DataBaseException)
{
	PreparedStatement updPub("UPDATE publishers SET name = '%1', description"
		" = '%2', critique = '%3', logo = '%4' WHERE id = '%5'", db->getType());
	updPub.arg(p.getName());
	updPub.arg(p.getDescription());
	updPub.arg(p.getCritique());
	updPub.arg(p.getLogo());

	updateThemesReference(p);

	db->exec(updPub);
}

/**
 * @brief Updates the themes references to match that of \a p.
 *
 * @param p Publisher whose theme references need to be updated.
 */
void PublisherCollection::updateThemesReference(Publisher p) throw(DataBaseException)
{
	deleteReference("publisher", p.getId(), "theme", db);
	insertThemesReference(p);
}

/**
 * @brief Creates theme references to match that of \a p.
 *
 * @param p Publisher whose themes need to be referenced.
 */
void PublisherCollection::insertThemesReference(Publisher p) throw(DataBaseException)
{
	insertReferencePublisher(p, db);
}
