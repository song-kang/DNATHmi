#ifndef DNATHMI_H
#define DNATHMI_H

#include <QtGui/QWidget>
#include "ui_dnathmi.h"
#include "commthread.h"
#include "qrthread.h"
#include "chome.h"
#include "clogin.h"
#include "clogincode.h"
#include "cloginqrcode.h"
#include "cdev.h"
#include "cdevlist.h"
#include "cdevlistsee.h"
#include "cdevlistcheck.h"
#include "cdevlook.h"
#include "cdevoper.h"

class DNATHmi : public QWidget
{
	Q_OBJECT

public:
	DNATHmi(QWidget *parent = 0);
	~DNATHmi();

	void HmiEnable(bool enable);
	void SetDeviceId(QString id) { m_pCommThread->SetDevice(id); }

public:
	CommThread *m_pCommThread;
	QRThread *m_pQRThread;

private:
	Ui::DNATHmiClass ui;

	CHome *m_pHome;
	CLogin *m_pLogin;
	CLoginCode *m_pLoginCode;
	CLoginQRCode *m_pLoginQRCode;
	CDev *m_pDevice;
	CDevList *m_pDeviceList;
	CDevListSee *m_pDeviceListSee;
	CDevListCheck *m_pDeviceListCheck;
	CDevLook *m_pDeviceLook;
	CDevOper *m_pDeviceOper;

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
