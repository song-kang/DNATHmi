#ifndef DNATHMI_H
#define DNATHMI_H

#include <QtGui/QWidget>
#include "ui_dnathmi.h"
#include "chome.h"
#include "clogin.h"
#include "clogincode.h"
#include "cloginqrcode.h"
#include "cdev.h"
#include "cdevlist.h"
#include "cdevlook.h"

class DNATHmi : public QWidget
{
	Q_OBJECT

public:
	DNATHmi(QWidget *parent = 0);
	~DNATHmi();

private:
	Ui::DNATHmiClass ui;

	CHome *m_pHome;
	CLogin *m_pLogin;
	CLoginCode *m_pLoginCode;
	CLoginQRCode *m_pLoginQRCode;
	CDev *m_pDevice;
	CDevList *m_pDeviceList;
	CDevLook *m_pDeviceLook;

private:
	void Init();
	void InitUi();
	void InitSlot();
	void closeEvent(QCloseEvent *e);

private slots:
	void SlotHelp();
	void SlotReturn();
	void SlotConfig();
	void SlotStatckWidgetName(QString name);

};

#endif // DNATHMI_H
