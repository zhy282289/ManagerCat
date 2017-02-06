#include "stdafx.h"
#include "managercat.h"

#include "propertywidget.h"


ManagerCat::ManagerCat(QWidget *parent)
	: QWidget(parent)
{
	resize(1024, 720);
	m_propertyWidget = new MainPropertyWidget(this);

	connect(m_propertyWidget, &MainPropertyWidget::InfoSignal, this, [&](QString info){
		m_display->append(info);
	});
	connect(m_propertyWidget, &MainPropertyWidget::SaveSignal, this, [&](){
		m_propertyWidget->savePropertys();
		saveDisplay();
	});

	connect(m_propertyWidget, &MainPropertyWidget::ExportSignal, this, [&](QString path){
		QFile file(path);
		file.open(QIODevice::WriteOnly);
		file.write(m_display->toPlainText().toLocal8Bit());
	});


	m_propertyWidgetArea = new QScrollArea(this);
	m_propertyWidgetArea->setWidgetResizable(true);
	m_propertyWidgetArea->setWidget(m_propertyWidget);

	m_display = new QTextEdit(this);
	m_display->setPlainText(SettingInit::getInstance()->getDesc());

	m_splitter = new QSplitter(Qt::Horizontal, this);

	m_splitter->addWidget(m_propertyWidgetArea);
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
		m_propertyWidget->savePropertys();
		saveDisplay();
	}
	event->accept();
}

void ManagerCat::saveDisplay()
{
	SettingInit::getInstance()->saveDesc(m_display->toPlainText());

}

