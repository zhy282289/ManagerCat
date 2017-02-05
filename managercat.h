#ifndef MANAGERCAT_H
#define MANAGERCAT_H

#include <QtWidgets/QWidget>
#include "ui_managercat.h"

class PropertyWidget;
class ManagerCat : public QWidget
{
	Q_OBJECT

public:
	ManagerCat(QWidget *parent = 0);
	~ManagerCat();

protected:
	void resizeEvent(QResizeEvent *event);

private:
	PropertyWidget *m_propertyWidget;

};

#endif // MANAGERCAT_H
