#ifndef CDEVLISTSEE_H
#define CDEVLISTSEE_H

#include <QWidget>
#include "ui_cdevlistsee.h"

#define DeviceListSee	"CDevListSee"

enum eListSeeState
{
	LISTSEE_NEW = 0,
	LISTSEE_MODIFY
};

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

class DNATHmi;
class CDevListSee : public QWidget
{
	Q_OBJECT

public:
	CDevListSee(QWidget *parent = 0);
	~CDevListSee();

private:
	Ui::CDevListSee ui;

	int m_iRow;
	eListSeeState m_eListSeeState;

private:
	void Init();
	void InitUi();
	void InitSlot();

	void SetDevices();
	void ShowDevices();
	void AddDevice(int row,QString id,QString manufacture,QString name,QString type,QString address);

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotNewClicked();
	void SlotModifyClicked();
	void SlotDeleteClicked();
	void SlotQRMakeClicked();
	void SlotQRShowClicked();
	void SlotQRPrintClicked();
	void SlotOkClicked();
	void SlotCancelClicked();
	void SlotComboBoxManufactureChanged(const QString& text);
	void SlotCmdDevList();

private:
	DNATHmi *m_pApp;

};

#endif // CDEVLISTSEE_H
