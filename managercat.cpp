#include "stdafx.h"
#include "managercat.h"

#include "propertywidget.h"


ManagerCat::ManagerCat(QWidget *parent)
	: QWidget(parent)
{
	resize(800, 600);
	m_propertyWidget = new PropertyWidget(this);
}

ManagerCat::~ManagerCat()
{

}

void ManagerCat::resizeEvent(QResizeEvent *event)
{
	m_propertyWidget->setGeometry(rect());
}
