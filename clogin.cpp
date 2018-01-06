#include "clogin.h"
#include "iconhelper.h"
#include "clogincode.h"

#define iconSize		70
#define iconWidth		140
#define iconHeight		100
#define btnWidth		300
#define btnHeight		250

CLogin::CLogin(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	Init();
	InitUi();
	InitSlot();
}

CLogin::~CLogin()
{

}

void CLogin::Init()
{
	QList<QString> listColorBg;
	listColorBg << "#1570A5" << "#16A085";

	QList<QString> listColorText;
	listColorText << "#FEFEFE" << "#FEFEFE";

	QList<QChar> listChar;
	listChar << 0xf029 << 0xf2bc;

	QList<QString> listText;
	listText << tr("QRCode Login") << tr("Code Login");

	m_pToolBtns << ui.toolBtnQRCode << ui.toolBtnCode;
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
}

void CLogin::InitUi()
{
	this->setObjectName(Login);
}

void CLogin::InitSlot()
{
	connect(ui.toolBtnQRCode, SIGNAL(clicked(bool)), this, SLOT(SlotQRCodeLoginClicked()));
	connect(ui.toolBtnCode, SIGNAL(clicked(bool)), this, SLOT(SlotCodeLoginClicked()));
}

void CLogin::SlotQRCodeLoginClicked()
{
	emit SigWidgetName(LoginQRCode);
}

void CLogin::SlotCodeLoginClicked()
{
	emit SigWidgetName(LoginCode);
}
