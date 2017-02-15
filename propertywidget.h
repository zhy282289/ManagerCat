#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H


class MainPropertyWidget;
class MainPropertyWidgetArea : public QWidget
{
	Q_OBJECT

public:
	MainPropertyWidgetArea(QWidget *parent);

	MainPropertyWidget* getPropertyWidget();
Q_SIGNALS:
	void InfoSignal(QString info);
	void SaveSignal();
	void ExportSignal(QString path);
	void ClearSignal();
private:
	MainPropertyWidget *m_propertyWidget;
	QScrollArea *m_area;

	QPushButton *m_btnAdd;
	QPushButton *m_btnCalculate;
	QPushButton *m_btnSave;
	QPushButton *m_btnExport;
	QPushButton *m_btnClear;
};


class BoyPropertyHead;
class MainPropertyWidget : public QWidget
{
	Q_OBJECT

public:
	MainPropertyWidget(QWidget *parent);
	~MainPropertyWidget();

	void savePropertys();

	void add();
	void calculate();
	void save();
	void exportFile();

Q_SIGNALS:
	void InfoSignal(QString info);
	void SaveSignal();
	void ExportSignal(QString path);
private:
	QList<BoyPropertyHead*> getPropertyWidgets();

private:
	QVBoxLayout *m_mainLayout;

};


class PropertyData
{
public:
	QString desc;
	int totalTime;
	float mLiveTime;
	float mStandupTime;
	float mAttackRateTime;

	int levelCount;

	int baseGold;
	int baseMouseGold;
	int baseAttack;
	int baseBlood;

	float goldRate;
	float mouseGoldRate;
	float attackRate;
	float bloodRate;

	QString NormalMCountOneTime;
	
	int totalGold;
	QString goldDistributeRate;
	float DifficultyRate;
};
typedef QList<PropertyData> PropertyDatas;


class BoyLineEdit;

class PropertyWidget : public QWidget
{
	Q_OBJECT

public:
	PropertyWidget(QWidget *parent);
	~PropertyWidget();

	QString getInfo();

	void setData(PropertyData &data);
	PropertyData getData();

private:
	void initData();

private:
	BoyLineEdit *m_leHead;


	BoyLineEdit *m_leTotalTime;
	BoyLineEdit *m_leMLiveTime;
	BoyLineEdit *m_leMStandupTime;
	BoyLineEdit *m_leMAttackRateTime;

	BoyLineEdit *m_leLevelCount;

	BoyLineEdit *m_leBaseGold;
	BoyLineEdit *m_leBaseMouseGold;
	BoyLineEdit *m_leBaseAttack;
	BoyLineEdit *m_leBaseBlood;

	BoyLineEdit *m_leGoldRate;
	BoyLineEdit *m_leMouseGoldRate;
	BoyLineEdit *m_leAttackRate;
	BoyLineEdit *m_leBloodRate;


	BoyLineEdit *m_leNormalMCountOneTime;

	
	BoyLineEdit *m_leTotalGold;
	BoyLineEdit *m_leGoldDistributeRate;


	// 所有参数上升rate
	BoyLineEdit *m_leDifficultyRate;


	BoyLineEdit *m_leSellBlood;
	BoyLineEdit *m_leSellAttack;
};


class BoyLineEdit : public QWidget
{
	Q_OBJECT

public:
	BoyLineEdit(QString text, QWidget *parent);
	QString getText();
	void setText(QString text);

	int getInt();
	float getFloat();

	QString getText(int index);
	int getInt(int index);
	float getFloat(int index);


	QLineEdit* getLineEdit();
private:
	QLabel *m_lb;
	QLineEdit *m_le;
};



class BoyPropertyHead : public QWidget
{
	Q_OBJECT

public:
	BoyPropertyHead(QWidget *parent);

	PropertyWidget* getPropertyWidget();
	bool needDisplayInfo();

private:
	QPushButton *m_btnShow;
	QCheckBox *m_ckb;

	QPushButton *m_btnRemove;

	PropertyWidget *m_widget;
};


class SettingInit
{
public:
	static SettingInit* getInstance();

	SettingInit();

	PropertyDatas getPropertys();
	void savePropertys(PropertyDatas &datas);

	QString getDesc();
	void saveDesc(QString desc);
private:
	//QSettings *m_settings;
};



#endif // PROPERTYWIDGET_H
