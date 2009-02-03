#include <iostream>

#include "Collection.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

using namespace std;

void displayBooks(QList<Book> &blist);
void displayAuthors(QList<Author> &alist);
void displayPublishers(QList<Publisher> &plist);
void displayThemes(QList<Theme> &tlist);
void displayBook(Book &b);
void displayAuthor(Author &a);
void displayPublisher(Publisher &p);
void displayTheme(Theme &t);

int main(int argc, char **argv)
{
	try
	{
		Collection c("User");

		QList<Theme> themeList;
		QList<Author> authorList;
		QList<Publisher> publisherList;

		Theme t("theme1", "desc1");
		c.insertTheme(t);
		themeList.append(t);

		Publisher p("pub1", "desc", "", themeList);
		c.insertPublisher(p);
		publisherList.append(p);

		Author a("fn", "ln", "desc", "cri", 5, "", themeList);
		c.insertAuthor(a);
		authorList.append(a);

		Book b("0123456789123", "title", 1, "cri", "desc", 5, "cover", "ebook", QDate(2009,1,9),
			"UDC", authorList, a, publisherList, themeList);

		c.insertBook(b);

		QList<Book> bookList = c.searchBooks(Book::b_translator, "ln");
		displayBooks(bookList);
	}
	catch(bad_alloc e)
	{
		cout << "Not enough memory." << endl;
	}
	catch(out_of_range e)
	{
		cout << "Out of range error." << endl;
		cout << e.what() << endl;
	}
	catch(DataBaseException dbe)
	{
		cout << "DataBase error: " << dbe.what() << endl;
		cout << "Cause: " << dbe.where() << endl;
		cout << "Error code: " << dbe.getCode() << endl;
	}
}

void displayBooks(QList<Book> &blist)
{
	QList<Book>::iterator it;
	for(it = blist.begin(); it != blist.end(); it++)
		displayBook((*it));
}

void displayAuthors(QList<Author> &alist)
{
	QList<Author>::iterator it;
	for(it = alist.begin(); it != alist.end(); it++)
		displayAuthor((*it));
}

void displayPublishers(QList<Publisher> &plist)
{
	QList<Publisher>::iterator it;
	for(it = plist.begin(); it !=plist.end(); it++)
		displayPublisher((*it));
}

void displayThemes(QList<Theme> &tlist)
{
	QList<Theme>::iterator it;
	for(it = tlist.begin(); it != tlist.end(); it++)
		displayTheme((*it));
}

void displayBook(Book &b)
{
	cout << "--- Begin Book ---" << endl;
	cout << "Title: " << b.getTitle() << endl;
	cout << "ISBN: " << b.getIsbn() << endl;
	cout << "Edition: " << b.getEdition() << endl;
	cout << "Description: " << b.getDescription() << endl;
	cout << "Critique: " << b.getCritique() << endl;
	cout << "Rating: " << b.getRating() << endl;
	cout << "Cover: " << b.getCover() << endl;
	cout << "Ebook: " << b.getEbook() << endl;
	cout << "Publication Date: " << b.getPubDate().toString().toStdString() << endl;
	cout << "UDC: " << b.getUDC() << endl;
	cout << "Authors: " << endl;
	QList<Author> aList = b.getAuthors();
	displayAuthors(aList);
	cout << "Translator: " << endl;
	Author a = b.getTranslator();
	displayAuthor(a);
	cout << "Publishers: " << endl;
	QList<Publisher> pList = b.getPublishers();
	displayPublishers(pList);
	cout << "Themes: " << endl;
	QList<Theme> tList = b.getThemes();
	displayThemes(tList);
	cout << "--- End Book ---" << endl;
}

void displayAuthor(Author &a)
{
	cout << "--- Begin Author ---" << endl;
	cout << "First name: " << a.getFirstName() << endl;
	cout << "Last name: " << a.getLastName() << endl;
	cout << "Description: " << a.getDescription() << endl;
	cout << "Critique: " << a.getCritique() << endl;
	cout << "Rating: " << a.getRating() << endl;
	cout << "Picture: " << a.getPicture() << endl;
	cout << "Themes: " << endl;
	QList<Theme> tList = a.getThemes();
	displayThemes(tList);
	cout << "--- End Author ---" << endl;
}

void displayPublisher(Publisher &p)
{
	cout << "--- Begin Publisher ---" << endl;
	cout << "Name: " << p.getName() << endl;
	cout << "Description: " << p.getDescription() << endl;
	cout << "Critique: " << p.getCritique() << endl;
	cout << "Logo: " << p.getLogo() << endl;
	cout << "Themes: " << endl;
	QList<Theme> tList = p.getThemes();
	displayThemes(tList);
	cout << "--- End Publisher ---" << endl;
}

void displayTheme(Theme &t)
{
	cout << "--- Begin Theme ---" << endl;
	cout << "Name: " << t.getName() << endl;
	cout << "Description: " << t.getDescription() << endl;
	cout << "--- End Theme ---" << endl;
}
