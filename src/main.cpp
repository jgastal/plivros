#include <iostream>

#include "Collection.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

using namespace std;

int main(int argc, char **argv)
{
	Collection *c;
	try
	{
		c = new Collection("DefaultUser");

		QList<Theme*> emptyThemeList;
		QList<Author*> emptyAuthorList;
		QList<Publisher*> emptyPublisherList;

		Theme t("theme1", "desc1");
		Publisher p("pub1", "desc", "", emptyThemeList);
		Author a("fn", "ln", "desc", "cri", 5, "", emptyThemeList);

		Book b("0123456789123", "title", 0, "", "", 5, "", "", QDate(),
			"UDC", emptyAuthorList, NULL, emptyPublisherList, emptyThemeList);

		c->insertBook(b);

		std::cout << "Good times." << std::endl;
	}
	catch(bad_alloc b)
	{
		std::cout << "Not enough memory." << std::endl;
	}
	catch(DataBaseException dbe)
	{
		std::cout << "DataBase error: " << dbe.what() << std::endl;
		std::cout << "Cause: " << dbe.where() << std::endl;
	}

	delete c;
}
