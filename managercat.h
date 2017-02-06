#ifndef MANAGERCAT_H
#define MANAGERCAT_H

#include <QtWidgets/QWidget>
#include "ui_managercat.h"

class MainPropertyWidget;
class ManagerCat : public QWidget
{
	Q_OBJECT

public:
	ManagerCat(QWidget *parent = 0);
	~ManagerCat();

protected:
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	void saveDisplay();
private:
	MainPropertyWidget *m_propertyWidget;
	QScrollArea *m_propertyWidgetArea;

	QTextEdit *m_display;

	QSplitter *m_splitter;
};

#endif // MANAGERCAT_H
