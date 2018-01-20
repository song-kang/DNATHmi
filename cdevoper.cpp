#include "cdevoper.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "dnathmi.h"

#define charSize		20
#define iconSize		30
#define iconWidth		40
#define iconHeight		40
#define btnWidth		150
#define btnHeight		60

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
	ui.label_strap_off->setText("·ÖÕ¢ÈíÑ¹°å×´Ì¬");
	ui.label_strap_on->setText("ºÏÕ¢ÈíÑ¹°å×´Ì¬");
	ui.label_remote_locate->setText("Ô¶·½/¾ÍµØ×´Ì¬  ");
	ui.label_hard_strap->setText("Ó² Ñ¹ °å ×´ Ì¬ ");
	ui.label_off->setText("Ò£¿Ø·ÖÕ¢");
	ui.label_on->setText("Ò£¿ØºÏÕ¢");
	ui.label_reset->setText("ÐÅºÅ¸´¹é");

	m_pTimer = new QTimer();
	m_pTimer->setInterval(1000);
	m_iTimeOut = 0;

	ui.label_feeder->setFixedHeight(30);
	ui.strap_off_wait->setFixedSize(50,50);
	ui.strap_off_wait->setVisible(false);
	ui.strap_on_wait->setFixedSize(50,50);
	ui.strap_on_wait->setVisible(false);
	ui.remote_locate_wait->setFixedSize(50,50);
	ui.remote_locate_wait->setVisible(false);
	ui.hard_strap_wait->setFixedSize(50,50);
	ui.hard_strap_wait->setVisible(false);
	ui.widget_off_circlewait->setFixedWidth(50);
	ui.widget_off_circlewait->setColor(QColor("#383838"));
	ui.widget_off_circlewait->setVisible(false);
	ui.label_off_wait->setText(tr("In the operation, please wait......"));
	ui.label_off_wait->setVisible(false);
	ui.widget_on_circlewait->setFixedWidth(50);
	ui.widget_on_circlewait->setColor(QColor("#383838"));
	ui.widget_on_circlewait->setVisible(false);
	ui.label_on_wait->setText(tr("In the operation, please wait......"));
	ui.label_on_wait->setVisible(false);
	ui.widget_reset_circlewait->setFixedWidth(50);
	ui.widget_reset_circlewait->setColor(QColor("#383838"));
	ui.widget_reset_circlewait->setVisible(false);
	ui.label_reset_wait->setText(tr("In the operation, please wait......"));
	ui.label_reset_wait->setVisible(false);

	ui.widget_strap_off->setFixedSize(100,50);
	ui.widget_strap_on->setFixedSize(100,50);
	ui.widget_remote_locate->setFixedSize(100,50);
	ui.widget_remote_locate->setText("¾ÍµØ","Ô¶·½");
	ui.widget_remote_locate->setIsOper(false);
	ui.widget_hard_strap->setFixedSize(100,50);
	ui.widget_hard_strap->setIsOper(false);

	ui.scrollArea_strap_off->setFixedHeight(150);
	ui.scrollArea_strap_on->setFixedHeight(150);
	ui.scrollArea_remote->setFixedHeight(150);
}

void CDevOper::InitUi()
{
	this->setObjectName(DeviceOper);

	ui.scrollArea->setFixedWidth(180);
	ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollAreaWidgetContents->setContentsMargins(0,0,0,0);

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btn_off_select->setText("  Ñ¡Ôñ");
	ui.btn_off_select->setFixedSize(btnWidth,btnHeight);
	ui.btn_off_select->setIcon(QIcon(iconNormal));
	ui.btn_off_select->setStyleSheet(QString("QPushButton#btn_off_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf013, iconSize, iconWidth, iconHeight);
	ui.btn_off_exec->setText("  Ö´ÐÐ");
	ui.btn_off_exec->setFixedSize(btnWidth,btnHeight);
	ui.btn_off_exec->setIcon(QIcon(iconNormal));
	ui.btn_off_exec->setStyleSheet(QString("QPushButton#btn_off_exec{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btn_off_cancel->setText("  È¡Ïû");
	ui.btn_off_cancel->setFixedSize(150,btnHeight);
	ui.btn_off_cancel->setIcon(QIcon(iconNormal));
	ui.btn_off_cancel->setStyleSheet(QString("QPushButton#btn_off_cancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #80752c,stop:1 #80752c);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btn_on_select->setText("  Ñ¡Ôñ");
	ui.btn_on_select->setFixedSize(btnWidth,btnHeight);
	ui.btn_on_select->setIcon(QIcon(iconNormal));
	ui.btn_on_select->setStyleSheet(QString("QPushButton#btn_on_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf013, iconSize, iconWidth, iconHeight);
	ui.btn_on_exec->setText("  Ö´ÐÐ");
	ui.btn_on_exec->setFixedSize(btnWidth,btnHeight);
	ui.btn_on_exec->setIcon(QIcon(iconNormal));
	ui.btn_on_exec->setStyleSheet(QString("QPushButton#btn_on_exec{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btn_on_cancel->setText("  È¡Ïû");
	ui.btn_on_cancel->setFixedSize(btnWidth,btnHeight);
	ui.btn_on_cancel->setIcon(QIcon(iconNormal));
	ui.btn_on_cancel->setStyleSheet(QString("QPushButton#btn_on_cancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #80752c,stop:1 #80752c);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf01e, iconSize, iconWidth, iconHeight);
	ui.btn_reset->setText("  ¸´¹é");
	ui.btn_reset->setFixedSize(btnWidth,btnHeight);
	ui.btn_reset->setIcon(QIcon(iconNormal));
	ui.btn_reset->setStyleSheet(QString("QPushButton#btn_reset{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	QStringList qss;
	qss.append(QString("QWidget#scrollAreaWidgetStrapOff{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QWidget#scrollAreaWidgetStrapOn{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QWidget#scrollAreaWidgetRemote{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QWidget#scrollAreaWidgetOper{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QScrollArea#scrollArea_strap_off{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_strap_on{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_remote{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_oper{background:transparent;}"));
	qss.append(QString("QLabel#label_feeder{font:%1px;color:#383838;}").arg(20));
	qss.append(QString("QLabel#label_off_wait{font:%1px;color:#383838;}").arg(20));
	qss.append(QString("QLabel#label_on_wait{font:%1px;color:#383838;}").arg(20));
	qss.append(QString("QLabel#label_reset_wait{font:%1px;color:#383838;}").arg(20));
	qss.append(QString("QLabel#label_strap_off{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_strap_on{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_remote_locate{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_hard_strap{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_off{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_on{font:%1px;color:#383838;}").arg(30));
	qss.append(QString("QLabel#label_reset{font:%1px;color:#383838;}").arg(30));
	this->setStyleSheet(qss.join(""));
}

void CDevOper::InitSlot()
{
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotTimeout()));

	connect(ui.btn_off_select, SIGNAL(clicked(bool)), this, SLOT(SlotOffSelectClicked()));
	connect(ui.btn_off_exec, SIGNAL(clicked(bool)), this, SLOT(SlotOffExecClicked()));
	connect(ui.btn_off_cancel, SIGNAL(clicked(bool)), this, SLOT(SlotOffCancelClicked()));
	connect(ui.btn_on_select, SIGNAL(clicked(bool)), this, SLOT(SlotOnSelectClicked()));
	connect(ui.btn_on_exec, SIGNAL(clicked(bool)), this, SLOT(SlotOnExecClicked()));
	connect(ui.btn_on_cancel, SIGNAL(clicked(bool)), this, SLOT(SlotOnCancelClicked()));
	connect(ui.btn_reset, SIGNAL(clicked(bool)), this, SLOT(SlotResetClicked()));
	connect(ui.widget_strap_off, SIGNAL(checkedChanged(bool)), this, SLOT(SlotOffStrapChanged(bool)));
	connect(ui.widget_strap_on, SIGNAL(checkedChanged(bool)), this, SLOT(SlotOnStrapChanged(bool)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdFeeder()), this, SLOT(SlotCmdFeeder()));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdStrapRead()), this, SLOT(SlotCmdStrapRead()));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOffStrapOff(qint32)), this, SLOT(SlotCmdOffStrapOff(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOffStrapOn(qint32)), this, SLOT(SlotCmdOffStrapOn(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOnStrapOff(qint32)), this, SLOT(SlotCmdOnStrapOff(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOnStrapOn(qint32)), this, SLOT(SlotCmdOnStrapOn(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdSignalReset(qint32)), this, SLOT(SlotCmdSignalReset(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOffCtrlSelect(qint32)), this, SLOT(SlotCmdOffCtrlSelect(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOffCtrlExec(qint32)), this, SLOT(SlotCmdOffCtrlExec(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOffCtrlCancel(qint32)), this, SLOT(SlotCmdOffCtrlCancel(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOnCtrlSelect(qint32)), this, SLOT(SlotCmdOnCtrlSelect(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOnCtrlExec(qint32)), this, SLOT(SlotCmdOnCtrlExec(qint32)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdOnCtrlCancel(qint32)), this, SLOT(SlotCmdOnCtrlCancel(qint32)));
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
	ui.btn_off_select->setEnabled(true);
	ui.btn_off_exec->setEnabled(false);
	ui.btn_off_cancel->setEnabled(false);
	ui.btn_on_select->setEnabled(true);
	ui.btn_on_exec->setEnabled(false);
	ui.btn_on_cancel->setEnabled(false);
	ui.btn_off_select->setStyleSheet(QString("QPushButton#btn_off_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));
	ui.btn_on_select->setStyleSheet(QString("QPushButton#btn_on_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	m_pApp->m_pCommThread->SetFeeder(feederNo+1); //Ä¬ÈÏfeederNo´Ó1¿ªÊ¼
	m_pApp->m_pCommThread->SetCommand(CMD_STRAP_READ);
}

void CDevOper::SlotOffSelectClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_OFFCTRL_SELECT);
	HmiEnable(false);
	ui.widget_off_circlewait->setVisible(true);
	ui.label_off_wait->setVisible(true);
}

void CDevOper::SlotOffExecClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_OFFCTRL_EXEC);
	HmiEnable(false);
	ui.widget_off_circlewait->setVisible(true);
	ui.label_off_wait->setVisible(true);
}

void CDevOper::SlotOffCancelClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_OFFCTRL_CANCEL);
	HmiEnable(false);
	ui.widget_off_circlewait->setVisible(true);
	ui.label_off_wait->setVisible(true);
}

void CDevOper::SlotOnSelectClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_ONCTRL_SELECT);
	HmiEnable(false);
	ui.widget_on_circlewait->setVisible(true);
	ui.label_on_wait->setVisible(true);
}

void CDevOper::SlotOnExecClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_ONCTRL_EXEC);
	HmiEnable(false);
	ui.widget_on_circlewait->setVisible(true);
	ui.label_on_wait->setVisible(true);
}

void CDevOper::SlotOnCancelClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_ONCTRL_CANCEL);
	HmiEnable(false);
	ui.widget_on_circlewait->setVisible(true);
	ui.label_on_wait->setVisible(true);
}

void CDevOper::SlotResetClicked()
{
	m_pApp->m_pCommThread->SetCommand(CMD_SIGNALRESET);
	HmiEnable(false);
	ui.widget_reset_circlewait->setVisible(true);
	ui.label_reset_wait->setVisible(true);
}

void CDevOper::SlotOffStrapChanged(bool state)
{
	if (state)
		m_pApp->m_pCommThread->SetCommand(CMD_OFFSTRAP_ON);
	else
		m_pApp->m_pCommThread->SetCommand(CMD_OFFSTRAP_OFF);

	HmiEnable(false);
	ui.strap_off_wait->setVisible(true);
}

void CDevOper::SlotOnStrapChanged(bool state)
{
	if (state)
		m_pApp->m_pCommThread->SetCommand(CMD_ONSTRAP_ON);
	else
		m_pApp->m_pCommThread->SetCommand(CMD_ONSTRAP_OFF);

	HmiEnable(false);
	ui.strap_on_wait->setVisible(true);
}

void CDevOper::SlotCmdFeeder()
{
	ShowFeeder();
}

void CDevOper::SlotCmdStrapRead()
{
	m_pApp->m_pCommThread->m_mutex.lock();

	ui.widget_strap_off->setPress(m_pApp->m_pCommThread->m_bOffStrap);
	ui.widget_strap_on->setPress(m_pApp->m_pCommThread->m_bOnStrap);
	ui.widget_remote_locate->setPress(m_pApp->m_pCommThread->m_bRemoteLocate);
	ui.widget_hard_strap->setPress(m_pApp->m_pCommThread->m_bHardStrap);

	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOffStrapOff(qint32 ret)
{
	HmiEnable(true);
	ui.strap_off_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.widget_strap_off->setPress(m_pApp->m_pCommThread->m_bOffStrap);
	ShowBox(ret,"·ÖÕ¢ÈíÑ¹°å£¬ÍË³ö");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOffStrapOn(qint32 ret)
{
	HmiEnable(true);
	ui.strap_off_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.widget_strap_off->setPress(m_pApp->m_pCommThread->m_bOffStrap);
	ShowBox(ret,"·ÖÕ¢ÈíÑ¹°å£¬Í¶Èë");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOnStrapOff(qint32 ret)
{
	HmiEnable(true);
	ui.strap_on_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.widget_strap_on->setPress(m_pApp->m_pCommThread->m_bOnStrap);
	ShowBox(ret,"ºÏÕ¢ÈíÑ¹°å£¬ÍË³ö");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOnStrapOn(qint32 ret)
{
	HmiEnable(true);
	ui.strap_on_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.widget_strap_on->setPress(m_pApp->m_pCommThread->m_bOnStrap);
	ShowBox(ret,"ºÏÕ¢ÈíÑ¹°å£¬Í¶Èë");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdSignalReset(qint32 ret)
{
	HmiEnable(true);
	ui.widget_reset_circlewait->setVisible(false);
	ui.label_reset_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowBox(ret,tr("Signal Reset"));
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOffCtrlSelect(qint32 ret)
{
	HmiEnable(true);
	ui.widget_off_circlewait->setVisible(false);
	ui.label_off_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	if (ret == RET_SUCCESS)
	{
		ui.btn_off_select->setEnabled(false);
		ui.btn_off_exec->setEnabled(true);
		ui.btn_off_cancel->setEnabled(true);
		ui.btn_off_select->setStyleSheet(QString("QPushButton#btn_off_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
			"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #d93a49,stop:1 #d93a49);font:%1px;}").arg(charSize));
	}
	ShowBox(ret,"Ò£¿Ø·ÖÕ¢£¬Ñ¡Ôñ");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOffCtrlExec(qint32 ret)
{
	HmiEnable(true);
	ui.widget_off_circlewait->setVisible(false);
	ui.label_off_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.btn_off_select->setEnabled(true);
	ui.btn_off_exec->setEnabled(false);
	ui.btn_off_cancel->setEnabled(false);
	ui.btn_off_select->setStyleSheet(QString("QPushButton#btn_off_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));
	ShowBox(ret,"Ò£¿Ø·ÖÕ¢£¬Ö´ÐÐ");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOffCtrlCancel(qint32 ret)
{
	HmiEnable(true);
	ui.widget_off_circlewait->setVisible(false);
	ui.label_off_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.btn_off_select->setEnabled(true);
	ui.btn_off_exec->setEnabled(false);
	ui.btn_off_cancel->setEnabled(false);
	ui.btn_off_select->setStyleSheet(QString("QPushButton#btn_off_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));
	ShowBox(ret,"Ò£¿Ø·ÖÕ¢£¬È¡Ïû");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOnCtrlSelect(qint32 ret)
{
	HmiEnable(true);
	ui.widget_on_circlewait->setVisible(false);
	ui.label_on_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	if (ret == RET_SUCCESS)
	{
		ui.btn_on_select->setEnabled(false);
		ui.btn_on_exec->setEnabled(true);
		ui.btn_on_cancel->setEnabled(true);
		ui.btn_on_select->setStyleSheet(QString("QPushButton#btn_on_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
			"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #d93a49,stop:1 #d93a49);font:%1px;}").arg(charSize));
	}
	ShowBox(ret,"Ò£¿ØºÏÕ¢£¬Ñ¡Ôñ");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOnCtrlExec(qint32 ret)
{
	HmiEnable(true);
	ui.widget_on_circlewait->setVisible(false);
	ui.label_on_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.btn_on_select->setEnabled(true);
	ui.btn_on_exec->setEnabled(false);
	ui.btn_on_cancel->setEnabled(false);
	ui.btn_on_select->setStyleSheet(QString("QPushButton#btn_on_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));
	ShowBox(ret,"Ò£¿ØºÏÕ¢£¬Ö´ÐÐ");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::SlotCmdOnCtrlCancel(qint32 ret)
{
	HmiEnable(true);
	ui.widget_on_circlewait->setVisible(false);
	ui.label_on_wait->setVisible(false);
	m_pApp->m_pCommThread->m_mutex.lock();
	ui.btn_on_select->setEnabled(true);
	ui.btn_on_exec->setEnabled(false);
	ui.btn_on_cancel->setEnabled(false);
	ui.btn_on_select->setStyleSheet(QString("QPushButton#btn_on_select{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));
	ShowBox(ret,"Ò£¿ØºÏÕ¢£¬È¡Ïû");
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevOper::ShowBox(qint32 ret,QString text)
{
	switch (ret)
	{
	case RET_SUCCESS:
		MsgBox::Instance()->information(tr("%1Operate Success.").arg(text));
		break;
	case RET_FAILED:
		MsgBox::Instance()->critical(tr("%1Operate Failed.").arg(text));
		break;
	case RET_TIMEOUT:
		MsgBox::Instance()->critical(tr("%1Operate Timeout.").arg(text));
		break;
	default:
		MsgBox::Instance()->critical(tr("Unknown result %1.").arg(ret));
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
	ui.scrollArea_strap_off->setEnabled(enable);
	ui.scrollArea_strap_on->setEnabled(enable);
	ui.scrollArea_remote->setEnabled(enable);
	ui.scrollArea_oper->setEnabled(enable);
	ui.scrollArea->setEnabled(enable);
	m_pApp->HmiEnable(enable);
}
