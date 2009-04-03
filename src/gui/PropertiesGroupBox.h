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

#include "Section.h"

class PropertiesGroupBox : public QGroupBox
{
	public:
		PropertiesGroupBox(QWidget *parent = 0);
		void init(Section::section t);
		unsigned short int getSelectedRadioButton();

	private:
		QGridLayout grid;
		QList<QRadioButton*> radButtons;
		Section::section t;
} ;

#endif //PROPERTIESGROUPBOX_H
