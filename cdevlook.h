#ifndef CDEVLOOK_H
#define CDEVLOOK_H

#include <QWidget>
#include <QPushButton>
#include <QThread>
#include "ui_cdevlook.h"
#include "navbutton.h"
#include "lightbutton.h"

#define DeviceLook	"CDevLook"

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
	LightButton *light;
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
	QLabel *label;
};

struct stuSoe
{
	stuSoe(QString t,QString d,QString s)
	{
		time = t;
		desc = d;
		state = s;
	}
	QString time;
	QString desc;
	QString state;
};

class DNATHmi;
class CDevLook : public QWidget
{
	Q_OBJECT

public:
	CDevLook(QWidget *parent = 0);
	~CDevLook();

	void Start();

private:
	Ui::CDevLook ui;

	QList<NavButton*> m_listBtnFeed;
	QTimer *m_pTimer;
	
private:
	void Init();
	void InitUi();
	void InitSlot();
	void InitTableLog();

	void SetFeeder();
	void ShowFeeder();
	void ShowMeasure();
	void ShowPower();
	void ShowDigital();
	void ShowSoe();

	void RefreshMeasure();
	void RefreshPower();
	void RefreshDigital();

	void Clear();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotNavButtonClick();
	void SlotCmdFeeder();
	void SlotCmdSetAllData();
	void SlotCmdRefAllData();
	void SlotTimeout();

private:
	DNATHmi *m_pApp;

};

#endif // CDEVLOOK_H
