v/**
 * @file PublisherForm.h
 *
 * @date 17/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef PUBLISHERFORM_H
#define PUBLISHERFORM_H

#include "ui_PublisherForm.h"

#include "Theme.h"

class Collection;

/**
 * @class PublisherForm PublisherForm.h
 *
 * @brief This widget is a form to add a publisher.
 */
class PublisherForm : public QWidget, protected Ui::PublisherForm
{
	Q_OBJECT

	public:
		PublisherForm(Collection *c, QWidget *parent = 0);

	public slots:
		void populateThemesListWidget();

	protected slots:
		virtual void save() = 0;
		void logoFileChooser();

	protected:
		bool validateInput();
		QList<Theme> getSelectedThemes();
		Collection *c;
		QList<Theme> themeList;

	signals:
		void closeRequested();
} ;

#endif //PUBLISHERFORM_H
