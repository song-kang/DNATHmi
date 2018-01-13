#include "chome.h"
#include "iconhelper.h"
#include "clogin.h"
#include "cdevlist.h"
#include "cdevtype.h"
#include "msgbox.h"

#define iconSize		70
#define iconWidth		140
#define iconHeight		100
#define btnWidth		300
#define btnHeight		250

CHome::CHome(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

CHome::~CHome()
{

}

void CHome::Init()
{
	QList<QString> listColorBg;
	listColorBg << "#007947" << "#494e8f" << "#8f4b2e";

	QList<QString> listColorText;
	listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

	QList<QChar> listChar;
	listChar << 0xf090 << 0xf0cb << 0xf00a;

	QList<QString> listText;
	listText << tr("Device Login") << tr("DevList Manage") << tr("Type Manage");

	m_pToolBtns << ui.toolBtnLogin << ui.toolBtnDevMan << ui.toolBtnTypeMan;
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

void CHome::InitUi()
{
	this->setObjectName(Home);
}

void CHome::InitSlot()
{
	connect(ui.toolBtnLogin, SIGNAL(clicked(bool)), this, SLOT(SlotLoginClicked()));
	connect(ui.toolBtnDevMan, SIGNAL(clicked(bool)), this, SLOT(SlotDevManClicked()));
	connect(ui.toolBtnTypeMan, SIGNAL(clicked(bool)), this, SLOT(SlotTypeManClicked()));
}

void CHome::SlotLoginClicked()
{
	emit SigWidgetName(Login);
}

void CHome::SlotDevManClicked()
{
	emit SigWidgetName(DeviceList);
}

void CHome::SlotTypeManClicked()
{
	emit SigWidgetName(DeviceFactoryType);
}
