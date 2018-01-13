#ifndef CDEVLISTCHECK_H
#define CDEVLISTCHECK_H

#include <QWidget>
#include "ui_cdevlistcheck.h"

#define DeviceListCheck	"CDevListCheck"

enum eDevCheck
{
	CHK_YES = 0,
	CHK_NO
};

struct stuDevCheck
{
	stuDevCheck(QString i,QString m,QString n,QString t,QString p,eDevCheck c)
	{
		id = i;
		manufacture = m;
		name = n;
		type = t;
		ip = p;
		check = c;
	}
	QString id;
	QString manufacture;
	QString name;
	QString type;
	QString ip;
	eDevCheck check;
};

class DNATHmi;
class CDevListCheck : public QWidget
{
	Q_OBJECT

public:
	CDevListCheck(QWidget *parent = 0);
	~CDevListCheck();

private:
	void Init();
	void InitUi();
	void InitSlot();

	void SetDevices();
	void ShowDevices();

private:
	Ui::CDevListCheck ui;

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotCmdDevCheck();

private:
	DNATHmi *m_pApp;

};

#endif // CDEVLISTCHECK_H
