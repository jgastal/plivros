#include <iostream>

#include "Collection.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Theme.h"

using namespace std;

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

		Book b("0123456789123", "title", 0, "", "", 5, "", "", QDate(2009,1,9),
			"UDC", authorList, a, publisherList, themeList);

		c.insertBook(b);

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
		std::cout << "Error code: " << dbe.getCode() << std::endl;
	}
}
