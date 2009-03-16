/**
 * @file AddPublisher.h
 *
 * @date 14/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef ADDPUBLISHER_H
#define ADDPUBLISHER_H

#include "ui_AddPublisher.h"

#include "Theme.h"

class Collection;

/**
 * @class AddPublisher AddPublisher.h
 *
 * @brief This widget is a form to add a publisher.
 */
class AddPublisher : public QWidget, private Ui::AddPublisher
{
	Q_OBJECT

	public:
		AddPublisher(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();

	private slots:
		void add();
		void close();
		void logoFileChooser();

	private:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		QWidget *parent;
		Collection *c;
		QList<Theme> themeList;
} ;

#endif //ADDPUBLISHER_H
