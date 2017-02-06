#include "stdafx.h"
#include "propertywidget.h"


//////////////////////////////////////////////////////////////////////////
MainPropertyWidget::MainPropertyWidget(QWidget *parent)
:QWidget(parent)
{
	m_btnAdd = new QPushButton(("Add"), this);
	connect(m_btnAdd, &QPushButton::clicked, this, [&](){
		auto widget = new BoyPropertyHead(this);
		m_mainLayout->insertWidget(qMax(0, m_mainLayout->count() - 1), widget);
	});

	m_btnCalculate = new QPushButton(("Calculate"), this);
	connect(m_btnCalculate, &QPushButton::clicked, this, [&](){

		QString info;
		auto widgets = getPropertyWidgets();
		for (auto widget : widgets)
		{
			if (widget->needDisplayInfo())
			{
				info += widget->getPropertyWidget()->getInfo();
			}
		}

		emit InfoSignal(info);

	});

	m_btnSave = new QPushButton(("Save"), this);
	connect(m_btnSave, &QPushButton::clicked, this, [&](){
		emit SaveSignal();
	});


	m_btnExport = new QPushButton(("Export"), this);
	connect(m_btnExport, &QPushButton::clicked, this, [&](){
		static QString dir;
		QString path = QFileDialog::getSaveFileName(this, "export", dir, QString("txt(*.txt)"));
		if (!path.isEmpty())
		{
			dir = path;
			emit ExportSignal(path);
		}
	});

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(m_btnAdd);
	hlayout->addWidget(m_btnCalculate);
	hlayout->addWidget(m_btnSave);
	hlayout->addWidget(m_btnExport);
	hlayout->addStretch();

	m_mainLayout = new QVBoxLayout;
	m_mainLayout->addLayout(hlayout);

	m_mainLayout->addStretch(100);

	setLayout(m_mainLayout);



	auto propertys = SettingInit::getInstance()->getPropertys();
	for (auto temp : propertys)
	{
		auto widget = new BoyPropertyHead(this);
		widget->getPropertyWidget()->setData(temp);

		m_mainLayout->insertWidget(qMax(0, m_mainLayout->count() - 1), widget);
	}


}

MainPropertyWidget::~MainPropertyWidget()
{
}

void MainPropertyWidget::savePropertys()
{
	auto widgets = getPropertyWidgets();
	PropertyDatas datas;
	for (auto widget : widgets)
	{
		datas.push_back(widget->getPropertyWidget()->getData());
	}

	SettingInit::getInstance()->savePropertys(datas);
}

QList<BoyPropertyHead*> MainPropertyWidget::getPropertyWidgets()
{
	QList<BoyPropertyHead*> widgets;
	for (int i = 0; i < m_mainLayout->count(); ++i)
	{
		auto widget = dynamic_cast<QWidgetItem*>(m_mainLayout->itemAt(i));
		if (widget)
		{
			auto propertyWidget = qobject_cast<BoyPropertyHead*>(widget->widget());
			if (propertyWidget)
				widgets.push_back(propertyWidget);
		}
	}


	return widgets;
}


//////////////////////////////////////////////////////////////////////////
PropertyWidget::PropertyWidget(QWidget *parent)
	: QWidget(parent)
{
	m_leHead = new BoyLineEdit("title", this);
	
	m_leTotalTime = new BoyLineEdit("TotalTime", this);
	m_leMLiveTime = new BoyLineEdit("LiveTime", this);
	m_leMStandupTime = new BoyLineEdit("MStandupTime", this);
	m_leMAttackRateTime = new BoyLineEdit("MAttackRateTime", this);

	m_leLevelCount = new BoyLineEdit("LevelCount", this);


	m_leBaseGold = new BoyLineEdit("BaseGold", this);
	m_leBaseAttack = new BoyLineEdit("BaseAttack", this);
	m_leBaseBlood = new BoyLineEdit("BaseBlood", this);

	m_leGoldRate = new BoyLineEdit("GoldRate", this);
	m_leAttackRate = new BoyLineEdit("AttackRate", this);
	m_leBloodRate = new BoyLineEdit("BloodRate", this);


	m_leNormalMCountOneTime = new BoyLineEdit("NormalMCountOneTime", this);


	m_leGifGold = new BoyLineEdit("GifGold", this);
	m_leBossGold = new BoyLineEdit("BossGold", this);
	
	m_leDifficultyRate = new BoyLineEdit("DifficultyRate", this);



	initData();

	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->setSpacing(0);

	vlayout->addWidget(m_leHead);

	vlayout->addWidget(m_leTotalTime);
	vlayout->addWidget(m_leMLiveTime);
	vlayout->addWidget(m_leMStandupTime);
	vlayout->addWidget(m_leMAttackRateTime);
	vlayout->addWidget(m_leLevelCount);

	vlayout->addWidget(m_leBaseGold);
	vlayout->addWidget(m_leBaseAttack);
	vlayout->addWidget(m_leBaseBlood);

	vlayout->addWidget(m_leGoldRate);
	vlayout->addWidget(m_leAttackRate);
	vlayout->addWidget(m_leBloodRate);

	vlayout->addWidget(m_leNormalMCountOneTime);
	vlayout->addWidget(m_leGifGold);
	vlayout->addWidget(m_leBossGold);
	vlayout->addWidget(m_leDifficultyRate);

	setLayout(vlayout);
}

PropertyWidget::~PropertyWidget()
{

}

QString PropertyWidget::getInfo()
{
	auto toUnicode = [&](const char *t){
		QTextCodec *codec = QTextCodec::codecForName("GB18030");
		return codec->toUnicode(t);

	};
	
	int totalTime = 0;
	int totalAttackCount = 0;
	int totalAttack = 0;
	int totalGold = 0;
	int totalBlood = 0;
	int totalMouseCount = 0;
	QString totalInfo("------------------------------------------------------\n");

	auto nextValue = [](int count, float rate, float value){
		float ret = value;
		for (int i = 1; i <= count; ++i)
		{
			ret = ret + ret * rate;
		}
		return ret;
	};

	totalInfo += m_leHead->getText() + "\n";
	for (int i = 0; i < m_leLevelCount->getInt(); ++i)
	{
		int level = i;

		int time = m_leTotalTime->getInt(i);
		int mouseCount = (m_leNormalMCountOneTime->getInt(i) * (time / (m_leMLiveTime->getFloat(i) + m_leMStandupTime->getFloat(i))));
		int attackCount = m_leMLiveTime->getFloat(i) / m_leMAttackRateTime->getFloat(i) * mouseCount;
		int preAttack = nextValue(level, m_leAttackRate->getFloat(i), m_leBaseAttack->getInt(i)); // (m_leBaseAttack->getFloat(i) + m_leBaseAttack->getFloat(i) * level * m_leAttackRate->getFloat(i));
		int attack = attackCount * preAttack;
		int preGold = nextValue(level, m_leGoldRate->getFloat(i), m_leBaseGold->getInt(i));// (m_leBaseGold->getFloat(i) + m_leBaseGold->getFloat(i) * level * m_leGoldRate->getFloat(i));
		int gold = mouseCount * preGold;
		int preBlood = nextValue(level, m_leBloodRate->getFloat(i), m_leBaseBlood->getInt(i));// (m_leBaseBlood->getFloat(i) + m_leBaseBlood->getFloat(i) * level * m_leBloodRate->getFloat(i));
		int blood = mouseCount * preBlood;
		QString baseInfo = QString("Level:%1 \n TotalTime:%2 preAttack:%3 preGold:%4 preBlood:%5 \n MouseCount:%6 AttackCount:%7  TotalAttack:%8 TotalGold:%9 TotalBlood:%10 \n")
			.arg(level + 1)
			.arg(time)
			.arg(preAttack)
			.arg(preGold)
			.arg(preBlood)
			.arg(mouseCount)
			.arg(attackCount)
			.arg(attack)
			.arg(gold)
			.arg(blood)
			;

		totalInfo += baseInfo;
		
		totalTime += time;
		totalAttackCount += attackCount;
		totalAttack += attack;
		totalGold += gold;
		totalBlood += blood;
		totalMouseCount += mouseCount;

	}
	
	QString enterString("---------\n");
	totalInfo += enterString;

	totalInfo += QString("AllLevel: TotalTime:%1 TotalMouseCount:%2 AttackTimes:%3  TotalAttack:%4 TotalGold:%5 TotalBlood:%6 \n GiftGold:%7 BossGold:%8 \n")
		.arg(totalTime)
		.arg(totalMouseCount)
		.arg(totalAttackCount)
		.arg(totalAttack)
		.arg(totalGold)
		.arg(totalBlood)
		.arg(m_leGifGold->getInt())
		.arg(m_leBossGold->getInt())
		;

	//totalInfo += enterString;

	//float difficultyRate = m_leDifficultyRate->getFloat();
	//totalInfo += QString("After Difficult:%6 => TotalTime:%1 AttackTimes:%2  TotalAttack:%3 TotalGold:%4 TotalBlood:%5 \n")
	//	.arg(totalTime)
	//	.arg(totalAttackCount)
	//	.arg(totalAttack * difficultyRate)
	//	.arg(totalGold)
	//	.arg(totalBlood)
	//	.arg(difficultyRate)
	//	;

	return totalInfo;
}




void PropertyWidget::setData(PropertyData &data)
{
	auto int2String = [](int v){return QString::number(v); };
	auto float2String = [](float v){return QString("%1").arg(v, 0, 'f', 1); };
	m_leHead->setText(data.desc);
	m_leTotalTime->setText(int2String(data.totalTime));
	m_leMLiveTime->setText(float2String(data.mLiveTime));
	m_leMStandupTime->setText(float2String(data.mStandupTime));
	m_leMAttackRateTime->setText(float2String(data.mAttackRateTime));

	m_leLevelCount->setText(int2String(data.levelCount));

	m_leBaseGold->setText(int2String(data.baseGold));
	m_leBaseAttack->setText(int2String(data.baseAttack));
	m_leBaseBlood->setText(int2String(data.baseBlood));

	m_leGoldRate->setText(float2String(data.goldRate));
	m_leAttackRate->setText(float2String(data.attackRate));
	m_leBloodRate->setText(float2String(data.bloodRate));

	m_leNormalMCountOneTime->setText(data.NormalMCountOneTime);
	
	m_leGifGold->setText(int2String(data.giftGold));
	m_leBossGold->setText(int2String(data.bossGold));

	m_leDifficultyRate->setText(float2String(data.DifficultyRate));

}

PropertyData PropertyWidget::getData()
{
	PropertyData data;
	data.desc = m_leHead->getText();

	data.totalTime = m_leTotalTime->getInt();
	data.mLiveTime = m_leMLiveTime->getFloat();
	data.mStandupTime = m_leMStandupTime->getFloat();
	data.mAttackRateTime = m_leMAttackRateTime->getFloat();
	data.levelCount = m_leLevelCount->getInt();

	data.baseGold = m_leBaseGold->getInt();
	data.baseAttack = m_leBaseAttack->getInt();
	data.baseBlood = m_leBaseBlood->getInt();

	data.goldRate = m_leGoldRate->getFloat();
	data.attackRate = m_leAttackRate->getFloat();
	data.bloodRate = m_leBloodRate->getFloat();

	data.NormalMCountOneTime = m_leNormalMCountOneTime->getText();
	
	data.giftGold = m_leGifGold->getInt();
	data.bossGold = m_leBossGold->getInt();

	data.DifficultyRate = m_leDifficultyRate->getFloat();

	return data;
}

void PropertyWidget::initData()
{
	m_leTotalTime->setText("60");
	m_leMLiveTime->setText("2");
	m_leMStandupTime->setText("2");
	m_leMAttackRateTime->setText("1.2");

	m_leLevelCount->setText("10");
	m_leBaseGold->setText("100");
	m_leBaseAttack->setText("100");
	m_leBaseBlood->setText("100");
	m_leGoldRate->setText("0.4");
	m_leAttackRate->setText("0.4");
	m_leBloodRate->setText("0.4");

	m_leNormalMCountOneTime->setText("4");
	m_leGifGold->setText("0");
	m_leBossGold->setText("0");
	m_leDifficultyRate->setText("0.4");


}

//////////////////////////////////////////////////////////////////////////

BoyLineEdit::BoyLineEdit(QString text, QWidget *parent)
:QWidget(parent)
{
	m_lb = new QLabel(QString("%1:").arg(text), this);
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

QString BoyLineEdit::getText(int index)
{
	auto l = m_le->text().split(" ");

	if (!l.isEmpty())
	{
		QString temp;
		if (index < l.size())
		{
			return l[index];
		}
		else
			return l[l.size() - 1];
	}
	else
		return QString();
}

void BoyLineEdit::setText(QString text)
{
	m_le->setText(text);
}

int BoyLineEdit::getInt()
{
	return m_le->text().toInt();
}

int BoyLineEdit::getInt(int index)
{
	return getText(index).toInt();
}

float BoyLineEdit::getFloat()
{
	return m_le->text().toFloat();
}

float BoyLineEdit::getFloat(int index)
{
	return getText(index).toFloat();
}

QLineEdit* BoyLineEdit::getLineEdit()
{
	return m_le;
}

//////////////////////////////////////////////////////////////////////////
BoyPropertyHead::BoyPropertyHead(QWidget *parent)
:QWidget(parent)
{
	m_btnShow = new QPushButton("-", this);
	m_btnShow->setFixedWidth(22);
	connect(m_btnShow, &QPushButton::clicked, this, [&](){
		if (m_btnShow->text() == "+")
		{
			m_widget->show();
			m_btnShow->setText("-");
		}
		else
		{
			m_widget->hide();
			m_btnShow->setText("+");

		}
	});

	m_ckb = new QCheckBox(this);
	m_ckb->setChecked(true);

	m_btnRemove = new QPushButton("x", this);
	m_btnRemove->setFixedWidth(22);

	connect(m_btnRemove, &QPushButton::clicked, this, [&](){
		delete this;
	});

	m_widget = new PropertyWidget(this);


	QVBoxLayout *mainLayout = new QVBoxLayout;

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(m_ckb);
	hlayout->addWidget(m_btnShow);
	hlayout->addStretch();
	hlayout->addWidget(m_btnRemove);

	mainLayout->addLayout(hlayout);
	mainLayout->addWidget(m_widget, 100);

	setLayout(mainLayout);
}

PropertyWidget* BoyPropertyHead::getPropertyWidget()
{
	return m_widget;
}

bool BoyPropertyHead::needDisplayInfo()
{
	return m_ckb->isChecked();
}

//////////////////////////////////////////////////////////////////////////
static SettingInit *g_SettingInit = nullptr;
SettingInit* SettingInit::getInstance()
{
	if (g_SettingInit == nullptr)
		g_SettingInit = new SettingInit;
	return g_SettingInit;
}

SettingInit::SettingInit()
{
	//m_settings = new QSettings("MangerCat.ini", QSettings::IniFormat);
}

PropertyDatas SettingInit::getPropertys()
{
	QSettings settings("MangerCat.ini", QSettings::IniFormat);

	PropertyDatas datas;
	settings.beginGroup("property");

	auto groups = settings.childGroups();
	for (auto temp : groups)
	{
		settings.beginGroup(temp);
		PropertyData data;
		data.desc = settings.value("desc").toString();
		data.totalTime = settings.value("totalTime").toInt();
		data.mLiveTime = settings.value("mLiveTime").toFloat();
		data.mStandupTime = settings.value("mStandupTime").toFloat();
		data.mAttackRateTime = settings.value("mAttackRateTime").toFloat();
		data.levelCount = settings.value("levelCount").toInt();

		data.baseGold = settings.value("baseGold").toInt();
		data.baseAttack = settings.value("baseAttack").toInt();
		data.baseBlood = settings.value("baseBlood").toInt();

		data.goldRate = settings.value("goldRate").toFloat();
		data.attackRate = settings.value("attackRate").toFloat();
		data.bloodRate = settings.value("bloodRate").toFloat();

		data.NormalMCountOneTime = settings.value("NormalMCountOneTime").toString();
		data.giftGold = settings.value("giftGold").toInt();
		data.bossGold = settings.value("bossGold").toInt();
		data.DifficultyRate = settings.value("DifficultyRate").toFloat();

		settings.endGroup();

		datas.push_back(data);
	}
	settings.endGroup();

	return datas;
}

void SettingInit::savePropertys(PropertyDatas &datas)
{
	QSettings settings("MangerCat.ini", QSettings::IniFormat);
	settings.beginGroup("property");
	settings.remove("");
	for (int i = 0; i < datas.size(); ++i)
	{
		PropertyData &data = datas[i];
		settings.beginGroup(QString::number(i));
		settings.setValue("desc", data.desc);

		settings.setValue("totalTime", data.totalTime);
		settings.setValue("mLiveTime", data.mLiveTime);
		settings.setValue("mStandupTime", data.mStandupTime);
		settings.setValue("mAttackRateTime", data.mAttackRateTime);
		settings.setValue("levelCount", data.levelCount);

		settings.setValue("baseGold", data.baseGold);
		settings.setValue("baseAttack", data.baseAttack);
		settings.setValue("baseBlood", data.baseBlood);

		settings.setValue("goldRate", data.goldRate);
		settings.setValue("attackRate", data.attackRate);
		settings.setValue("bloodRate", data.bloodRate);		
		
		settings.setValue("NormalMCountOneTime", data.NormalMCountOneTime);
		settings.setValue("giftGold", data.giftGold);
		settings.setValue("bossGold", data.bossGold);
		settings.setValue("DifficultyRate", data.DifficultyRate);

		settings.endGroup();

	}
	settings.endGroup();
}

QString SettingInit::getDesc()
{
	QSettings settings("MangerCat.ini", QSettings::IniFormat);
	settings.beginGroup("desc");
	return settings.value("desc").toString();
}

void SettingInit::saveDesc(QString desc)
{
	QSettings settings("MangerCat.ini", QSettings::IniFormat);
	settings.beginGroup("desc");
	settings.setValue("desc", desc);
	settings.endGroup();
}
