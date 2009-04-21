#include "ui_CategoryFrame.h"

#include "CategoryFrame.h"

#include "Section.h"

static QString bgss = "QWidget#%1 { "
"background: url(:bgs/%2);\n"
"background-repeat: no-repeat;\n"
"background-position: center center; }";

CategoryFrame::CategoryFrame(QWidget *parent) : QFrame(parent)
{
	setupUi(this);

	connect(themeHoverPushButton, SIGNAL(hoverEnter()), this, SIGNAL(themeHover()));
	connect(themeHoverPushButton, SIGNAL(hoverLeave()), this, SIGNAL(leaveHover()));
	connect(publisherHoverPushButton, SIGNAL(hoverEnter()), this, SIGNAL(publisherHover()));
	connect(publisherHoverPushButton, SIGNAL(hoverLeave()), this, SIGNAL(leaveHover()));
	connect(authorHoverPushButton, SIGNAL(hoverEnter()), this, SIGNAL(authorHover()));
	connect(authorHoverPushButton, SIGNAL(hoverLeave()), this, SIGNAL(leaveHover()));
	connect(bookHoverPushButton, SIGNAL(hoverEnter()), this, SIGNAL(bookHover()));
	connect(bookHoverPushButton, SIGNAL(hoverLeave()), this, SIGNAL(leaveHover()));

	bgss = bgss.arg(parentWidget()->objectName());
}

void CategoryFrame::setThemeText()
{
	themeHoverPushButton->setText(tr("Themes"));
	QString ss = themeHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	themeHoverPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_themes2.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setPublisherText()
{
	publisherHoverPushButton->setText(tr("Publishers"));
	QString ss = publisherHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	publisherHoverPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_publishers.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setAuthorText()
{
	authorHoverPushButton->setText(tr("Authors"));
	QString ss = authorHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	authorHoverPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_authors.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setBookText()
{
	bookHoverPushButton->setText(tr("Books"));
	QString ss = bookHoverPushButton->styleSheet();
	ss += "\nfont: bold 20pt;";
	bookHoverPushButton->setStyleSheet(ss);
	ss = parentWidget()->styleSheet();
	ss += bgss.arg("big_books2.jpeg");
	parentWidget()->setStyleSheet(ss);
}

void CategoryFrame::setEmptyText()
{
	static_cast<HoverPushButton*>(sender())->setText("");
	QString ss = static_cast<HoverPushButton*>(sender())->styleSheet();
	ss.remove("\nfont: bold 20pt;");
	static_cast<HoverPushButton*>(sender())->setStyleSheet(ss);
	parentWidget()->setStyleSheet("");
}

void CategoryFrame::themeClicked()
{
	emit clicked(Section::Theme);
}

void CategoryFrame::publisherClicked()
{
	emit clicked(Section::Publisher);
}

void CategoryFrame::authorClicked()
{
	emit clicked(Section::Author);
}

void CategoryFrame::bookClicked()
{
	emit clicked(Section::Book);
}
