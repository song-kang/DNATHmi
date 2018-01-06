#ifndef CDEVLOOK_H
#define CDEVLOOK_H

#include <QWidget>
#include <QPushButton>
#include "ui_cdevlook.h"
#include "navbutton.h"

#define DeviceLook	"CDevLook"

class CDevLook : public QWidget
{
	Q_OBJECT

public:
	enum eLedState
	{
		LED_GREED = 0,
		LED_RED
	};

	struct stuDigital
	{
		stuDigital(eLedState s,QString d)
		{
			state = s;
			desc = d;
		}
		eLedState state;
		QString desc;
	};

	struct stuMeausre
	{
		stuMeausre(QChar i,QString d,float v,QString u)
		{
			icon = i;
			desc = d;
			value = v;
			unit = u;
		}
		QChar icon;
		QString desc;
		float value;
		QString unit;
	};

public:
	CDevLook(QWidget *parent = 0);
	~CDevLook();

	void Start();

private:
	Ui::CDevLook ui;

	QList<NavButton*> m_listBtnFeed;
	QList<stuMeausre*> m_listMeausreCol1;
	QList<stuMeausre*> m_listMeausreCol2;
	QList<stuMeausre*> m_listMeausreCol3;
	QList<stuMeausre*> m_listPowerCol1;
	QList<stuMeausre*> m_listPowerCol2;
	QList<stuDigital*> m_listDigital;

private:
	void Init();
	void InitUi();
	void InitSlot();
	void InitTableLog();

	void SetFeeder();
	void SetMeasure();
	void SetPower();
	void SetDigital();
	void SetLog();
	void ShowMeasure();
	void ShowPower();
	void ShowDigital();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotNavButtonClick();

};

#endif // CDEVLOOK_H
