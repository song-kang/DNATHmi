#include "cdevoper.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "dnathmi.h"

#define iconSize		50
#define iconWidth		100
#define iconHeight		70
#define btnWidth		220
#define btnHeight		200
#define MaxTimeOut		15

CDevOper::CDevOper(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	m_pApp = (DNATHmi *)parent;
	
	Init();
	InitUi();
	InitSlot();
	Start();
}

CDevOper::~CDevOper()
{
	delete m_pTimer;
}

void CDevOper::Init()
{
	QList<QString> listColorBg;
	listColorBg << "#2e3a1f" << "#426ab3" << "#843900" << "#1d953f" << "#411445";

	QList<QString> listColorText;
	listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

	QList<QChar> listChar;
	listChar << 0xf1eb << 0xf204 << 0xf205 << 0xf124 << 0xf01e;

	QList<QString> listText;
	listText << tr("Remote Control") << tr("Soft Strap") << tr("Hard Strap") << tr("Distant / Local") << tr("Signal Reset");

	m_pToolBtns << ui.toolBtnYK << ui.toolBtnSYB << ui.toolBtnYYB << ui.toolBtnReLo << ui.toolBtnReset;
	for (int i = 0; i < m_pToolBtns.count(); i++) 
	{
		QToolButton *btn = m_pToolBtns.at(i);
		btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		btn->setFixedSize(QSize(btnWidth, btnHeight));
		btn->setIconSize(QSize(iconWidth, iconHeight));

		QPixmap pix = IconHelper::Instance()->getPixmap(listColorText.at(i), listChar.at(i), iconSize, iconWidth, iconHeight);
		btn->setIcon(QIcon(pix));
		btn->setText(listText.at(i));

		QStringList list;
		list.append(QString("QToolButton{font:%1px;background:%2;color:#FEFEFE;}").arg(iconSize / 3).arg(listColorBg.at(i)));
		list.append(QString("QToolButton{border:none;border-radius:20px;padding:50px;}"));
		list.append(QString("QToolButton:pressed{background:%1;}").arg("#737A97"));
		btn->setStyleSheet(list.join(""));
	}

	m_pTimer = new QTimer();
	m_pTimer->setInterval(1000);
	m_iTimeOut = 0;

	ui.label_feeder->setFixedHeight(30);
	ui.widget_wait->setFixedHeight(100);
	ui.widget_circlewait->setFixedWidth(100);
	ui.widget_circlewait->setColor(QColor("#383838"));
	ui.widget_circlewait->setVisible(false);
	ui.label_wait->setText(tr("In the operation, please wait......"));
	ui.label_wait->setVisible(false);
}

void CDevOper::InitUi()
{
	this->setObjectName(DeviceOper);

	ui.scrollArea->setFixedWidth(180);
	ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollAreaWidgetContents->setContentsMargins(0,0,0,0);

	QStringList qss;
	qss.append(QString("QWidget#widget_content{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QLabel#label_feeder{font:%1px;color:#383838;}").arg(20));
	qss.append(QString("QLabel#label_wait{font:%1px;color:#383838;}").arg(20));
	this->setStyleSheet(qss.join(""));
}

void CDevOper::InitSlot()
{
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotTimeout()));

	connect(ui.toolBtnYK, SIGNAL(clicked(bool)), this, SLOT(SlotRemoteControlClicked()));
	connect(ui.toolBtnSYB, SIGNAL(clicked(bool)), this, SLOT(SlotSoftStrapClicked()));
	connect(ui.toolBtnYYB, SIGNAL(clicked(bool)), this, SLOT(SlotHardStrapClicked()));
	connect(ui.toolBtnReLo, SIGNAL(clicked(bool)), this, SLOT(SlotDistantLocalClicked()));
	connect(ui.toolBtnReset, SIGNAL(clicked(bool)), this, SLOT(SlotSignalResetClicked()));

	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdFeeder()), this, SLOT(SlotCmdFeeder()));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdRmoteControl(qint32)), this, SLOT(SlotCmdRmoteControl(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdSoftStrap(qint32)), this, SLOT(SlotCmdSoftStrap(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdHardStrap(qint32)), this, SLOT(SlotCmdHardStrap(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdDistantLocal(qint32)), this, SLOT(SlotCmdDistantLocal(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdSignalReset(qint32)), this, SLOT(SlotCmdSignalReset(qint32)));
}

void CDevOper::Start()
{
	SetFeeder();
}

void CDevOper::SlotTimeout()
{

}

void CDevOper::SlotNavButtonClick()
{
	qint32 feederNo = 0;
	NavButton *btn = (NavButton *)sender();
	for (int feederNo = 0; feederNo < m_listBtnFeed.count(); feederNo++)
		m_listBtnFeed.at(feederNo)->setChecked(m_listBtnFeed.at(feederNo) == btn);

	ui.label_feeder->setText(tr("%1 Operation items").arg(btn->text()));

	m_pApp->m_pCommThread->SetFeeder(feederNo+1); //默认feederNo从1开始
}

void CDevOper::SlotRemoteControlClicked()
{
	int ret = MsgBox::Instance()->question("请选择控分或控合",3,"控合","控分","取消",0xf0c1,0xf127);
	if (ret == RET_YES) 
		m_pApp->m_pCommThread->SetOper(OPER_CLOSE);
	else if (ret == RET_NO)
		m_pApp->m_pCommThread->SetOper(OPER_OPEN);
	else if (ret == RET_CANCEL)
		return;

	m_pApp->m_pCommThread->SetCommand(CMD_REMOTE_CONTROL);
	HmiEnable(false);
}

void CDevOper::SlotSoftStrapClicked()
{
	int ret = MsgBox::Instance()->question("请选择控分或控合",3,"控合","控分","取消",0xf0c1,0xf127);
	if (ret == RET_YES) 
		m_pApp->m_pCommThread->SetOper(OPER_CLOSE);
	else if (ret == RET_NO)
		m_pApp->m_pCommThread->SetOper(OPER_OPEN);
	else if (ret == RET_CANCEL)
		return;

	m_pApp->m_pCommThread->SetCommand(CMD_SOFT_STRAP);
	HmiEnable(false);
}

void CDevOper::SlotHardStrapClicked()
{
	int ret = MsgBox::Instance()->question("请选择控分或控合",3,"控合","控分","取消",0xf0c1,0xf127);
	if (ret == RET_YES) 
		m_pApp->m_pCommThread->SetOper(OPER_CLOSE);
	else if (ret == RET_NO)
		m_pApp->m_pCommThread->SetOper(OPER_OPEN);
	else if (ret == RET_CANCEL)
		return;

	m_pApp->m_pCommThread->SetCommand(CMD_HARD_STRAP);
	HmiEnable(false);
}

void CDevOper::SlotDistantLocalClicked()
{
	int ret = MsgBox::Instance()->question("请选择远方或就地",3,"远方","就地","取消",0xf1d0,0xf124);
	if (ret == RET_YES) 
		m_pApp->m_pCommThread->SetOper(OPER_CLOSE);
	else if (ret == RET_NO)
		m_pApp->m_pCommThread->SetOper(OPER_OPEN);
	else if (ret == RET_CANCEL)
		return;

	m_pApp->m_pCommThread->SetCommand(CMD_DISTANT_LOCAL);
	HmiEnable(false);
}

void CDevOper::SlotSignalResetClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_SIGNALRESET);
	HmiEnable(false);
}

void CDevOper::SlotCmdFeeder()
{
	ShowFeeder();
}

void CDevOper::SlotCmdRmoteControl(qint32 ret)
{
	HmiEnable(true);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Remote Control"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdSoftStrap(qint32 ret)
{
	HmiEnable(true);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Soft Strap"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdHardStrap(qint32 ret)
{
	HmiEnable(true);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Hard Strap"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdDistantLocal(qint32 ret)
{
	HmiEnable(true);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Distant / Local"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdSignalReset(qint32 ret)
{
	HmiEnable(true);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Signal Reset"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::ShowBox(qint32 ret,QString text)
{
	switch (ret)
	{
	case RET_SUCCESS:
		MsgBox::Instance()->information(tr("%1 Operate Success.").arg(text));
		break;
	case RET_FAILED:
		MsgBox::Instance()->warning(tr("%1 Operate Failed.").arg(text));
		break;
	case RET_TIMEOUT:
		MsgBox::Instance()->warning(tr("%1 Operate Timeout.").arg(text));
		break;
	default:
		MsgBox::Instance()->warning(tr("Unknown result %1.").arg(ret));
		break;
	}
}

void CDevOper::SetFeeder()
{
	m_pApp->m_pCommThread->m_mutex.lock();
	m_pApp->m_pCommThread->SetCommand(CMD_FEEDER);
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::ShowFeeder()
{
	m_pApp->m_pCommThread->m_mutex.lock();

	int count = m_pApp->m_pCommThread->m_listFeeder.count();
	if (count <= 0)
		return;

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(false);

	QVBoxLayout *vLayout = new QVBoxLayout();
	foreach (QString s, m_pApp->m_pCommThread->m_listFeeder)
	{
		NavButton *nav = new NavButton;
		nav->setFont(m_font);
		nav->setFixedHeight(55);
		nav->setText(s);
		vLayout->addWidget(nav);
		m_listBtnFeed.append(nav);
	}
	vLayout->addStretch();
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0,0,0,0);
	ui.scrollAreaWidgetContents->setLayout(vLayout);

	m_pApp->m_pCommThread->m_mutex.unlock();

	QList<QChar> pixChar;
	for (int i = 0; i < count; i++)
		pixChar.append(0xf1fe);
	QColor normalBgColor = QColor("#2D9191");
	QColor hoverBgColor = QColor("#187294");
	QColor checkBgColor = QColor("#145C75");
	QColor normalTextColor = QColor("#FFFFFF");
	QColor hoverTextColor = QColor("#FFFFFF");
	QColor checkTextColor = QColor("#FFFFFF");
	for (int i = 0; i < m_listBtnFeed.count(); i++)
	{
		m_listBtnFeed.at(i)->setPaddingLeft(60);
		m_listBtnFeed.at(i)->setLineSpace(0);
		m_listBtnFeed.at(i)->setLineWidth(8);
		m_listBtnFeed.at(i)->setLineColor(QColor(255, 107, 107));
		m_listBtnFeed.at(i)->setShowTriangle(true);

		m_listBtnFeed.at(i)->setShowIcon(true);
		m_listBtnFeed.at(i)->setIconSpace(10);
		m_listBtnFeed.at(i)->setIconSize(QSize(22, 22));

		QChar icon = pixChar.at(i);
		QPixmap iconNormal = IconHelper::Instance()->getPixmap(normalTextColor.name(), icon, 15, 30, 30);
		QPixmap iconHover = IconHelper::Instance()->getPixmap(hoverTextColor.name(), icon, 15, 30, 30);
		QPixmap iconCheck = IconHelper::Instance()->getPixmap(checkTextColor.name(), icon, 15, 30, 30);

		m_listBtnFeed.at(i)->setIconNormal(iconNormal);
		m_listBtnFeed.at(i)->setIconHover(iconHover);
		m_listBtnFeed.at(i)->setIconCheck(iconCheck);

		m_listBtnFeed.at(i)->setNormalBgColor(normalBgColor);
		m_listBtnFeed.at(i)->setHoverBgColor(hoverBgColor);
		m_listBtnFeed.at(i)->setCheckBgColor(checkBgColor);
		m_listBtnFeed.at(i)->setNormalTextColor(normalTextColor);
		m_listBtnFeed.at(i)->setHoverTextColor(hoverTextColor);
		m_listBtnFeed.at(i)->setCheckTextColor(checkTextColor);

		connect(m_listBtnFeed.at(i), SIGNAL(clicked(bool)), this, SLOT(SlotNavButtonClick()));
	}

	m_listBtnFeed.at(0)->click();
}

void CDevOper::HmiEnable(bool enable)
{
	ui.toolBtnYK->setEnabled(enable);
	ui.toolBtnSYB->setEnabled(enable);
	ui.toolBtnYYB->setEnabled(enable);
	ui.toolBtnReLo->setEnabled(enable);
	ui.toolBtnReset->setEnabled(enable);
	ui.scrollArea->setEnabled(enable);
	m_pApp->HmiEnable(enable);

	ui.widget_circlewait->setVisible(!enable);
	ui.label_wait->setVisible(!enable);
}
