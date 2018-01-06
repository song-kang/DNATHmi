#include "cdevlist.h"
#include "iconhelper.h"

#define iconSize		70
#define iconWidth		140
#define iconHeight		100
#define btnWidth		300
#define btnHeight		250

CDevList::CDevList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

CDevList::~CDevList()
{

}

void CDevList::Init()
{
	QList<QString> listColorBg;
	listColorBg << "#007947" << "#494e8f" << "#8f4b2e" << "#d71345";

	QList<QString> listColorText;
	listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

	QList<QChar> listChar;
	listChar << 0xf1ea << 0xf044 << 0xf03c << 0xf03b;

	QList<QString> listText;
	listText << tr("Device Browse") << tr("Device Edit") << tr("Device Import") << tr("Device Export");

	m_pToolBtns << ui.toolBtnBrowse << ui.toolBtnEdit << ui.toolBtnImport << ui.toolBtnExport;
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

void CDevList::InitUi()
{
	this->setObjectName(DeviceList);
}

void CDevList::InitSlot()
{
	connect(ui.toolBtnBrowse, SIGNAL(clicked(bool)), this, SLOT(SlotBrowseClicked()));
	connect(ui.toolBtnEdit, SIGNAL(clicked(bool)), this, SLOT(SlotEditClicked()));
	connect(ui.toolBtnImport, SIGNAL(clicked(bool)), this, SLOT(SlotImportClicked()));
	connect(ui.toolBtnExport, SIGNAL(clicked(bool)), this, SLOT(SlotExportClicked()));
}

void CDevList::SlotBrowseClicked()
{

}

void CDevList::SlotEditClicked()
{

}

void CDevList::SlotImportClicked()
{

}

void CDevList::SlotExportClicked()
{

}
