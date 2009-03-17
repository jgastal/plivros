/**
 * @file Book.h
 *
 * @date Nov 1, 2008
 * @author Jonas M. Gastal
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <string>

#include <QList>
#include <QDate>
#include <QStringList>

#include "Author.h"
#include "Publisher.h"
#include "Theme.h"
#include "DataObject.h"

using namespace std;

class Book : public DataObject
{
	public:
		Book();
		Book(char isbn[13], string title, unsigned short int ed, string cri,
			string desc, unsigned short int rat, string cov, string eb, QDate d,
			string UDC, QList<Author> a, const Author &tr, QList<Publisher> p,
			QList<Theme> t, unsigned int id = 0);
		const char* getIsbn() const;
		void setIsbn(const char ISBN[13]);
		string getTitle() const;
		void setTitle(string title);
		unsigned short int getEdition() const;
		void setEdition(unsigned short int edition);
		string getCritique() const;
		void setCritique(string critique);
		unsigned short int getRating() const;
		void setRating(unsigned short int rating);
		string getCover() const;
		void setCover(string cover);
		string getEbook() const;
		void setEbook(string ebook);
		QDate getPubDate() const;
		void setPubDate(QDate pubDate);
		string getUDC() const;
		void setUDC(string UDC);
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

	private:
		void initHeaders();
		char isbn[14]; //International Standard Book Number + '/0'
		string title;
		unsigned short int edition;
		string critique;
		unsigned short int rating;
		string cover; //path to file of cover picture
		string ebook; //path to file of ebook copy of this book
		QDate pubDate;
		string UDC; //Universal Decimal Classification
		QList<Author> authors; //list of authors
		Author translator;
		QList<Publisher> publishers;
		QList<Theme> themes;
};

#endif /* BOOK_H_ */
