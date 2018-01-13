#include "dnathmi.h"
#include "iconhelper.h"
#include "msgbox.h"

#define topIcoWidth		18
#define topTitleSize	18
#define topBtnWidth		45

DNATHmi::DNATHmi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

DNATHmi::~DNATHmi()
{
	MsgBox::DestoryInstance();

	m_pQRThread->SetQuit(true);
	m_pCommThread->SetQuit(true);

	while (!m_pQRThread->isQuit())
		Common::UsSleep(100000);
	while (!m_pCommThread->isQuit())
		Common::UsSleep(100000);

	delete m_pQRThread;
	delete m_pCommThread;
}

void DNATHmi::Init()
{
	m_pHome = NULL;
	m_pLogin = NULL;
	m_pLoginCode = NULL;
	m_pLoginQRCode = NULL;
	m_pDevice = NULL;
	m_pDeviceList = NULL;
	m_pDeviceListSee = NULL;
	m_pDeviceListCheck = NULL;
	m_pDeviceLook = NULL;
	m_pDeviceOper = NULL;

	ui.labTitle->setText(tr("Automatic terminal management tool for distribution network"));
	ui.widgetTop->setFixedHeight(40);
	ui.btnClose->setToolTip(tr("Close"));
	ui.btnConfig->setToolTip(tr("Configure"));
	ui.btnHelp->setToolTip(tr("Help"));
	ui.btnConfig->setVisible(false);
	ui.btnHelp->setVisible(false);

	IconHelper::Instance()->setIcon(ui.btnReturn, 0xf015, topIcoWidth);
	IconHelper::Instance()->setIcon(ui.btnClose, 0xf011, topIcoWidth);
	IconHelper::Instance()->setIcon(ui.btnConfig, 0xf013, topIcoWidth);
	IconHelper::Instance()->setIcon(ui.btnHelp, 0xf128, topIcoWidth);

	QTime t= QTime::currentTime();
	qsrand(t.msec()+t.second()*1000);
	QStringList qss;
	qss.append(QString("*{outline:0px;}"));
	qss.append(QString("QWidget#widgetMain{border-image:url(\":/image/main%1\");}").arg(qrand()%7));
	qss.append(QString("QLabel#labTitle{font:%1px;color:#FEFEFE;}").arg(topTitleSize));
	qss.append(QString("QWidget#widgetTop{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}").arg("#00688B").arg("#093746"));
	qss.append(QString("QWidget#widgetTop QAbstractButton{background:none;border:none;min-width:%1px;max-width:%1px;color:#FEFEFE;}").arg(topBtnWidth));
	this->setStyleSheet(qss.join(""));

	m_pHome = new CHome(this);
	ui.stackedWidget->addWidget(m_pHome);
	ui.stackedWidget->setCurrentWidget(m_pHome);

	m_pCommThread = new CommThread(this);
	m_pCommThread->start();

	m_pQRThread = new QRThread(this);
}

void DNATHmi::InitUi()
{
	this->setWindowFlags(Qt::FramelessWindowHint);
}

void DNATHmi::InitSlot()
{
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnHelp, SIGNAL(clicked()), this, SLOT(SlotHelp()));
	connect(ui.btnReturn, SIGNAL(clicked()), this, SLOT(SlotReturn()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(SlotConfig()));
	connect(m_pHome, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
}

void DNATHmi::SlotHelp()
{

}

void DNATHmi::SlotReturn()
{
	QString name = ui.stackedWidget->currentWidget()->objectName();
	if (name == Login && m_pLogin)
	{
		disconnect(m_pLogin, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pHome);
		ui.stackedWidget->removeWidget(m_pLogin);
		IconHelper::Instance()->setIcon(ui.btnReturn, 0xf015, topIcoWidth);
		ui.labTitle->setText(tr("Automatic terminal management tool for distribution network"));
		delete m_pLogin;
		m_pLogin = NULL;
	}
	else if (name == LoginQRCode && m_pLoginQRCode)
	{
		m_pLoginQRCode->CloseCamera();
		disconnect(m_pLoginQRCode, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pLogin);
		ui.stackedWidget->removeWidget(m_pLoginQRCode);
		ui.labTitle->setText(tr("Device Login"));
		delete m_pLoginQRCode;
		m_pLoginQRCode = NULL;
	}
	else if (name == LoginCode && m_pLoginCode)
	{
		disconnect(m_pLoginCode, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pLogin);
		ui.stackedWidget->removeWidget(m_pLoginCode);
		ui.labTitle->setText(tr("Device Login"));
		delete m_pLoginCode;
		m_pLoginCode = NULL;
	}
	else if (name == Device && m_pDevice)
	{
		disconnect(m_pDevice, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pLogin);
		ui.stackedWidget->removeWidget(m_pDevice);
		ui.stackedWidget->removeWidget(m_pLoginCode);
		ui.stackedWidget->removeWidget(m_pLoginQRCode);
		ui.labTitle->setText(tr("Device Login"));
		delete m_pDevice;
		if (m_pLoginCode)
			delete m_pLoginCode;
		if (m_pLoginQRCode)
			delete m_pLoginQRCode;
		m_pDevice = NULL;
		m_pLoginCode = NULL;
	}
	else if (name == DeviceList && m_pDeviceList)
	{
		disconnect(m_pDeviceList, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pHome);
		ui.stackedWidget->removeWidget(m_pDeviceList);
		ui.labTitle->setText(tr("Device Login"));
		IconHelper::Instance()->setIcon(ui.btnReturn, 0xf015, topIcoWidth);
		ui.labTitle->setText(tr("Automatic terminal management tool for distribution network"));
		delete m_pDeviceList;
		m_pDeviceList = NULL;
	}
	else if (name == DeviceListSee && m_pDeviceListSee)
	{
		disconnect(m_pDeviceListSee, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pDeviceList);
		ui.stackedWidget->removeWidget(m_pDeviceListSee);
		ui.labTitle->setText(tr("DevList Manage"));
		delete m_pDeviceListSee;
		m_pDeviceListSee = NULL;
	}
	else if (name == DeviceListCheck && m_pDeviceListCheck)
	{
		disconnect(m_pDeviceListCheck, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pDeviceList);
		ui.stackedWidget->removeWidget(m_pDeviceListCheck);
		ui.labTitle->setText(tr("DevList Manage"));
		delete m_pDeviceListCheck;
		m_pDeviceListCheck = NULL;
	}
	else if (name == DeviceLook && m_pDeviceLook)
	{
		disconnect(m_pDeviceLook, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pDevice);
		ui.stackedWidget->removeWidget(m_pDeviceLook);
		ui.labTitle->setText(tr("Device Function"));
		delete m_pDeviceLook;
		m_pDeviceLook = NULL;
	}
	else if (name == DeviceOper && m_pDeviceOper)
	{
		disconnect(m_pDeviceOper, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pDevice);
		ui.stackedWidget->removeWidget(m_pDeviceOper);
		ui.labTitle->setText(tr("Device Function"));
		delete m_pDeviceOper;
		m_pDeviceOper = NULL;
	}
	else if (name == DeviceFactoryType && m_pDeviceType)
	{
		disconnect(m_pDeviceType, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.stackedWidget->setCurrentWidget(m_pHome);
		ui.stackedWidget->removeWidget(m_pDeviceType);
		ui.labTitle->setText(tr("Device Function"));
		delete m_pDeviceType;
		m_pDeviceType = NULL;
	}

	if (ui.stackedWidget->currentWidget()->objectName() != Home)
		IconHelper::Instance()->setIcon(ui.btnReturn, 0xf112, topIcoWidth);
}

void DNATHmi::SlotConfig()
{

}

void DNATHmi::SlotStatckWidgetName(QString name)
{
	if (name == Login)
	{
		m_pLogin = new CLogin(this);
		ui.stackedWidget->addWidget(m_pLogin);
		ui.stackedWidget->setCurrentWidget(m_pLogin);
		connect(m_pLogin, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Device Login"));
	}
	else if (name == LoginQRCode)
	{
		m_pLoginQRCode = new CLoginQRCode(this);
		ui.stackedWidget->addWidget(m_pLoginQRCode);
		ui.stackedWidget->setCurrentWidget(m_pLoginQRCode);
		connect(m_pLoginQRCode, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("QRCode Login"));
	}
	else if (name == LoginCode)
	{
		m_pLoginCode = new CLoginCode(this);
		ui.stackedWidget->addWidget(m_pLoginCode);
		ui.stackedWidget->setCurrentWidget(m_pLoginCode);
		connect(m_pLoginCode, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Code Login"));
	}
	else if (name == Device)
	{
		m_pDevice = new CDev(this);
		ui.stackedWidget->addWidget(m_pDevice);
		ui.stackedWidget->setCurrentWidget(m_pDevice);
		connect(m_pDevice, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Device Function"));
	}
	else if (name == DeviceList)
	{
		m_pDeviceList = new CDevList(this);
		ui.stackedWidget->addWidget(m_pDeviceList);
		ui.stackedWidget->setCurrentWidget(m_pDeviceList);
		connect(m_pDeviceList, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("DevList Manage"));
	}
	else if (name == DeviceListSee)
	{
		m_pDeviceListSee = new CDevListSee(this);
		ui.stackedWidget->addWidget(m_pDeviceListSee);
		ui.stackedWidget->setCurrentWidget(m_pDeviceListSee);
		connect(m_pDeviceListSee, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("DevList Browse"));
	}
	else if (name == DeviceListCheck)
	{
		m_pDeviceListCheck = new CDevListCheck(this);
		ui.stackedWidget->addWidget(m_pDeviceListCheck);
		ui.stackedWidget->setCurrentWidget(m_pDeviceListCheck);
		connect(m_pDeviceListCheck, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("DevList Check State"));
	}
	else if (name == DeviceLook)
	{
		m_pDeviceLook = new CDevLook(this);
		ui.stackedWidget->addWidget(m_pDeviceLook);
		ui.stackedWidget->setCurrentWidget(m_pDeviceLook);
		connect(m_pDeviceLook, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Device Browse"));
	}
	else if (name == DeviceOper)
	{
		m_pDeviceOper = new CDevOper(this);
		ui.stackedWidget->addWidget(m_pDeviceOper);
		ui.stackedWidget->setCurrentWidget(m_pDeviceOper);
		connect(m_pDeviceOper, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Device Operation"));
	}
	else if (name == DeviceFactoryType)
	{
		m_pDeviceType = new CDevType(this);
		ui.stackedWidget->addWidget(m_pDeviceType);
		ui.stackedWidget->setCurrentWidget(m_pDeviceType);
		connect(m_pDeviceType, SIGNAL(SigWidgetName(QString)), this, SLOT(SlotStatckWidgetName(QString)));
		ui.labTitle->setText(tr("Device Type Browse"));
	}

	IconHelper::Instance()->setIcon(ui.btnReturn, 0xf112, topIcoWidth);
}

void DNATHmi::closeEvent(QCloseEvent *e)
{
	int ret = MsgBox::Instance()->question(tr("Exit the application?"));
	if (ret != RET_YES) 
	{
		e->ignore();
		return;
	}

	QWidget::closeEvent(e);
}

void DNATHmi::HmiEnable(bool enable)
{
	ui.btnClose->setEnabled(enable);
	ui.btnReturn->setEnabled(enable);
	ui.btnConfig->setEnabled(enable);
	ui.btnHelp->setEnabled(enable);
}
