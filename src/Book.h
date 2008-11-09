/**
 * @file Book.h
 *
 * @date Nov 1, 2008
 * @author Jonas M. Gastal
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <string>

#include <QtCore/QList>
#include <QtCore/QDate>

class Author;
class Publisher;
class Theme;

using namespace std;

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

class Book
{
	public:
		Book(char isbn[13], string title, unsigned short int ed, string cri,
			string desc, unsigned short int rat, string cov, string eb, QDate d,
			string UDC, QList<Author*> a, Author* tr, QList<Publisher*> p,
			QList<Theme*> t, unsigned int id = 0);
		unsigned int getId() const;
		void setId(unsigned int id);
		const char* getIsbn() const;
		void setIsbn(char ISBN[13]);
		string getTitle() const;
		void setTitle(string title);
		unsigned short int getEdition() const;
		void setEdition(unsigned short int edition);
		string getCritique() const;
		void setCritique(string critique);
		string getDescription() const;
		void setDescription(string description);
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
		QList<Author*> getAuthors() const;
		void setAuthors(QList<Author*> authors);
		Author *getTranslator() const;
		void setTranslator(Author *translator);
		QList<Publisher*> getPublishers() const;
		void setPublishers(QList<Publisher*> publishers);
		QList<Theme*> getThemes() const;
		void setThemes(QList<Theme*> themes);

	private:
		unsigned int id;
		char isbn[13]; //International Standard Book Number
		string title;
		unsigned short int edition;
		string critique;
		string description;
		unsigned short int rating;
		string cover; //path to file of cover picture
		string ebook; //path to file of ebook copy of this book
		QDate pubDate;
		string UDC; //Universal Decimal Classification
		QList<Author*> authors; //list of pointers to authors
		Author *translator;
		QList<Publisher*> publishers;
		QList<Theme*> themes;
};

#endif /* BOOK_H_ */
