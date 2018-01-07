#ifndef CDEVLISTSEE_H
#define CDEVLISTSEE_H

#include <QWidget>
#include "ui_cdevlistsee.h"

#define DeviceListSee	"CDevListSee"

class CDevListSee : public QWidget
{
	Q_OBJECT

public:
	struct stuDev
	{
		stuDev(QString i,QString m,QString n,QString t,QString p)
		{
			id = i;
			manufacture = m;
			name = n;
			type = t;
			ip = p;
		}
		QString id;
		QString manufacture;
		QString name;
		QString type;
		QString ip;
	};

public:
	CDevListSee(QWidget *parent = 0);
	~CDevListSee();

private:
	Ui::CDevListSee ui;

	QList<stuDev*> m_listDevice;

private:
	void Init();
	void InitUi();
	void InitSlot();

	void SetDevices();
	void ShowDevices();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotNewClicked();
	void SlotModifycked();
	void SlotDeleteClicked();
	void SlotOkClicked();
	void SlotCancelClicked();

};

#endif // CDEVLISTSEE_H
