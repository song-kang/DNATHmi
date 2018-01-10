#include "cdev.h"
#include "iconhelper.h"
#include "cdevlook.h"
#include "cdevoper.h"

#define iconSize		70
#define iconWidth		140
#define iconHeight		100
#define btnWidth		300
#define btnHeight		250

CDev::CDev(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

CDev::~CDev()
{

}

void CDev::Init()
{
	QList<QString> listColorBg;
	listColorBg << "#007947" << "#494e8f" << "#8f4b2e" << "#d71345" << "#e0861a" << "#00a6ac";

	QList<QString> listColorText;
	listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

	QList<QChar> listChar;
	listChar << 0xf1ea << 0xf0e3 << 0xf085 << 0xf1c0 << 0xf0ce << 0xf299;

	QList<QString> listText;
	listText << tr("Info Browse") << tr("Operation") << tr("Set manage") << tr("Statistics") << tr("Log manage") << tr("Advanced");

	m_pToolBtns << ui.toolBtnBrowse << ui.toolBtnOPerate << ui.toolBtnConfig << ui.toolBtnStatistics << ui.toolBtnLog << ui.toolBtnAdvanced;
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

void CDev::InitUi()
{
	this->setObjectName(Device);
}

void CDev::InitSlot()
{
	connect(ui.toolBtnBrowse, SIGNAL(clicked(bool)), this, SLOT(SlotBrowseClicked()));
	connect(ui.toolBtnOPerate, SIGNAL(clicked(bool)), this, SLOT(SlotOperateClicked()));
	connect(ui.toolBtnConfig, SIGNAL(clicked(bool)), this, SLOT(SlotConfigClicked()));
	connect(ui.toolBtnStatistics, SIGNAL(clicked(bool)), this, SLOT(SlotStatisticsClicked()));
	connect(ui.toolBtnLog, SIGNAL(clicked(bool)), this, SLOT(SlotLogClicked()));
	connect(ui.toolBtnAdvanced, SIGNAL(clicked(bool)), this, SLOT(SlotAdvancedClicked()));
}

void CDev::SlotBrowseClicked()
{
	emit SigWidgetName(DeviceLook);
}

void CDev::SlotOperateClicked()
{
	emit SigWidgetName(DeviceOper);
}

void CDev::SlotConfigClicked()
{

}

void CDev::SlotStatisticsClicked()
{

}

void CDev::SlotLogClicked()
{

}

void CDev::SlotAdvancedClicked()
{

}
