/*
 *  Copyright (C) 2009 Jonas Mauricio Gastal.
 *  Contact: Jonas Mauricio Gastal (jgastal@gmail.com)
 *
 *  This file is part of Parabola Biblioteca.
 *
 *  Parabola Biblioteca is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License.
 *
 *  Parabola Biblioteca is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Parabola Biblioteca.  If not, see <http://www.gnu.org/licenses/>.
 */
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
 * This method adds the publisher to the database it however does not add the
 * references to the themes.
 */
void PublisherCollection::insertPublisher(Publisher &p) throw(DataBaseException)
{
	PreparedStatement insPub("INSERT INTO publishers (name, description, critique,"
		"logo) VALUES ('%1', '%2', '%3', '%4')", db->getType());
	insPub.arg(p.getName().toStdString());
	insPub.arg(p.getDescription().toStdString());
	insPub.arg(p.getCritique().toStdString());
	insPub.arg(p.getLogo().toStdString());

	p.setId(db->insert(insPub));
}

/**
 * @brief Removes publisher from collection.
 *
 * @param id ID of publisher to be removed.
 *
 * @return Whether operation was successful.
 *
 * This method deletes the publisher from the DataBase with no consideration for
 * posible references.
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
 * This method updates every field of the publisher except referenced themes and
 * the id.
 */
void PublisherCollection::updatePublisher(Publisher p) throw(DataBaseException)
{
	PreparedStatement updPub("UPDATE publishers SET name = '%1', description"
		" = '%2', critique = '%3', logo = '%4' WHERE id = '%5'", db->getType());
	updPub.arg(p.getName().toStdString());
	updPub.arg(p.getDescription().toStdString());
	updPub.arg(p.getCritique().toStdString());
	updPub.arg(p.getLogo().toStdString());

	db->exec(updPub);
}
