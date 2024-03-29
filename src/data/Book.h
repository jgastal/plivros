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
 * @file Book.h
 *
 * @date 01/11/2008
 * @author Jonas M. Gastal
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <QDate>
#include <QString>
#include <QList>
#include <QStringList>

#include "Author.h"
#include "Publisher.h"
#include "Theme.h"
#include "DataObject.h"

class Book : public DataObject
{
	public:
		Book();
		Book(char isbn[13], QString title, unsigned short int ed, QString cri,
			QString desc, unsigned short int rat, QString cov, QString eb, QDate d,
			QString UDC, QList<Author> a, const Author &tr, QList<Publisher> p,
			QList<Theme> t, unsigned int id = 0);
		const char* getIsbn() const;
		void setIsbn(const char ISBN[13]);
		QString getTitle() const;
		void setTitle(QString title);
		unsigned short int getEdition() const;
		void setEdition(unsigned short int edition);
		QString getCritique() const;
		void setCritique(QString critique);
		unsigned short int getRating() const;
		void setRating(unsigned short int rating);
		QString getCover() const;
		void setCover(QString cover);
		QString getEbook() const;
		void setEbook(QString ebook);
		QDate getPubDate() const;
		void setPubDate(QDate pubDate);
		QString getUDC() const;
		void setUDC(QString UDC);
		QList<Author> getAuthors() const;
		void setAuthors(QList<Author> authors);
		QString getAuthorsNames() const;
		Author getTranslator() const;
		QString getTranslatorName() const;
		void setTranslator(const Author &tr);
		QList<Publisher> getPublishers() const;
		QString getPublishersNames() const;
		void setPublishers(QList<Publisher> publishers);
		QList<Theme> getThemes() const;
		QString getThemesNames() const;
		void setThemes(QList<Theme> themes);
		QStringList getProperties() const;
		bool operator==(const Book b) const;

		enum book_field
		{
			b_isbn,
			b_title,
			b_edition,
			b_critique,
			b_description,
			b_rating,
			b_cover,
			b_ebook,
			b_pubdate,
			b_UDC,
			b_authors,
			b_translator,
			b_publishers,
			b_themes
		};
		static book_field getHeader(unsigned short int i);
		static QStringList getHeaders();

	private:
		char isbn[14]; //International Standard Book Number + '/0'
		QString title;
		unsigned short int edition;
		QString critique;
		unsigned short int rating;
		QString cover; //path to file of cover picture
		QString ebook; //path to file of ebook copy of this book
		QDate pubDate;
		QString UDC; //Universal Decimal Classification
		QList<Author> authors; //list of authors
		Author translator;
		QList<Publisher> publishers;
		QList<Theme> themes;
		static const char *headers[];
		static const unsigned short int propertiesCount;
};

#endif /* BOOK_H_ */
