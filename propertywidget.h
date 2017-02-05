#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H


class BoyLineEdit;

class PropertyWidget : public QWidget
{
	Q_OBJECT

public:
	PropertyWidget(QWidget *parent);
	~PropertyWidget();

	QString getInfo();

private:
	QTextEdit *m_leHead;


	BoyLineEdit *m_leTotalTime;
	BoyLineEdit *m_leMLiveTime;
	BoyLineEdit *m_leLevelCount;

	BoyLineEdit *m_leBaseGold;
	BoyLineEdit *m_leBaseAttack;
	BoyLineEdit *m_leBaseBlood;

	BoyLineEdit *m_leGoldRate;
	BoyLineEdit *m_leAttackRate;
	BoyLineEdit *m_leBloodRate;
	BoyLineEdit *m_leExtra;

	BoyLineEdit *m_leNormalMCount;
	BoyLineEdit *m_leNormalExtra;


	BoyLineEdit *m_leRandomMCount;
	BoyLineEdit *m_leRandomExtra;

};


class BoyLineEdit : public QWidget
{
	Q_OBJECT

public:
	BoyLineEdit(QString text, QWidget *parent);
	QString getText();
	int getInt();
	float getFloat();

	QLineEdit* getLineEdit();
private:
	QLabel *m_lb;
	QLineEdit *m_le;
};

#endif // PROPERTYWIDGET_H
