#include "stdafx.h"
#include "propertywidget.h"

PropertyWidget::PropertyWidget(QWidget *parent)
	: QWidget(parent)
{
	m_leHead = new QTextEdit(this);
	
	m_leTotalTime = new BoyLineEdit("TotalTime", this);
	m_leMLiveTime = new BoyLineEdit("LiveTime", this);
	m_leLevelCount = new BoyLineEdit("LevelCount", this);

	m_leBaseGold = new BoyLineEdit("BaseGold", this);
	m_leBaseAttack = new BoyLineEdit("BaseAttack", this);
	m_leBaseBlood = new BoyLineEdit("BaseBlood", this);

	m_leGoldRate = new BoyLineEdit("GoldRate", this);
	m_leAttackRate = new BoyLineEdit("AttackRate", this);
	m_leBloodRate = new BoyLineEdit("BloodRate", this);
	m_leExtra = new BoyLineEdit("Extra", this);


	m_leNormalMCount = new BoyLineEdit("MouseCount", this);
	//m_leNormalExtra = new BoyLineEdit("MouseÊý", this);


	m_leRandomMCount = new BoyLineEdit("RandomMCount", this);
	//m_leRandomExtra = new BoyLineEdit("¶îÍâ¹¥»÷", this);


	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(m_leHead);
	vlayout->addWidget(m_leTotalTime);
	vlayout->addWidget(m_leMLiveTime);
	vlayout->addWidget(m_leLevelCount);

	vlayout->addWidget(m_leBaseGold);
	vlayout->addWidget(m_leBaseAttack);
	vlayout->addWidget(m_leBaseBlood);

	vlayout->addWidget(m_leGoldRate);
	vlayout->addWidget(m_leAttackRate);
	vlayout->addWidget(m_leBloodRate);
	vlayout->addWidget(m_leExtra);

	vlayout->addWidget(m_leNormalMCount);

	vlayout->addWidget(m_leRandomMCount);

	setLayout(vlayout);
}

PropertyWidget::~PropertyWidget()
{

}

QString PropertyWidget::getInfo()
{
	QString info;

	//auto addInfo = [&](QString &addInfo){
	//	info = info + addInfo + "\n";
	//};
	//auto addSpaceline = [&](){
	//	info = info + "\n";
	//};

	//addInfo(m_leHead->toPlainText());
	//addSpaceline();


	return info;
}

//////////////////////////////////////////////////////////////////////////

BoyLineEdit::BoyLineEdit(QString text, QWidget *parent)
:QWidget(parent)
{
	m_lb = new QLabel(text, this);
	m_le = new QLineEdit;

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(m_lb);
	hlayout->addWidget(m_le, 100);
	setLayout(hlayout);
}

QString BoyLineEdit::getText()
{
	return m_le->text();
}

int BoyLineEdit::getInt()
{
	return m_le->text().toInt();
}

float BoyLineEdit::getFloat()
{
	return m_le->text().toFloat();
}

QLineEdit* BoyLineEdit::getLineEdit()
{
	return m_le;
}
