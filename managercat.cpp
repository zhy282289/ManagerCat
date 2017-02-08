#include "stdafx.h"
#include "managercat.h"

#include "propertywidget.h"


ManagerCat::ManagerCat(QWidget *parent)
	: QWidget(parent)
{
	resize(1024, 720);


	m_propertyWidget = new MainPropertyWidgetArea(this);

	connect(m_propertyWidget, &MainPropertyWidgetArea::InfoSignal, this, [&](QString info){
		m_display->append(info);
	});
	connect(m_propertyWidget, &MainPropertyWidgetArea::SaveSignal, this, [&](){
		m_propertyWidget->getPropertyWidget()->savePropertys();
		saveDisplay();
	});

	connect(m_propertyWidget, &MainPropertyWidgetArea::ExportSignal, this, [&](QString path){
		QFile file(path);
		file.open(QIODevice::WriteOnly);
		file.write(m_display->toPlainText().toLocal8Bit());
	});


	m_display = new QTextEdit(this);
	m_display->setPlainText(SettingInit::getInstance()->getDesc());

	m_splitter = new QSplitter(Qt::Horizontal, this);

	m_splitter->addWidget(m_propertyWidget);
	m_splitter->addWidget(m_display);

	m_splitter->setChildrenCollapsible(false);
	m_splitter->setStretchFactor(0, 30);
	m_splitter->setStretchFactor(1, 70);
}

ManagerCat::~ManagerCat()
{
}

void ManagerCat::resizeEvent(QResizeEvent *event)
{
	m_splitter->setGeometry(rect());
}

void ManagerCat::closeEvent(QCloseEvent *event)
{
	if (QMessageBox::Yes == QMessageBox::question(this, "", "save?", QMessageBox::Yes | QMessageBox::No))
	{
		m_propertyWidget->getPropertyWidget()->savePropertys();
		saveDisplay();
	}
	event->accept();
}

void ManagerCat::saveDisplay()
{
	SettingInit::getInstance()->saveDesc(m_display->toPlainText());

}

