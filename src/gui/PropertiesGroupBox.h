/**
 * @file PropertiesGroupBox.h
 *
 * @date 20/03/2009
 * @author Jonas M. Gastal
 * @brief Provides the class definition.
 */

#ifndef PROPERTIESGROUPBOX_H
#define PROPERTIESGROUPBOX_H

#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>

class PropertiesGroupBox : public QGroupBox
{
	public:
		enum type
		{
			book,
			author,
			publisher,
			theme
		} ;

		PropertiesGroupBox(QWidget *parent = 0);
		void init(type t);
		unsigned short int getSelectedRadioButton();

	private:
		QGridLayout grid;
		QList<QRadioButton*> radButtons;
		type t;
} ;

#endif //PROPERTIESGROUPBOX_H
