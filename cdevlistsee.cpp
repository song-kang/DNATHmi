#include "cdevlistsee.h"
#include "iconhelper.h"

#define charSize		20
#define iconSize		40
#define iconWidth		50
#define iconHeight		50
#define btnHeight		60

CDevListSee::CDevListSee(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();

	SetDevices();
	ShowDevices();
}

CDevListSee::~CDevListSee()
{
	foreach (stuDev *dev, m_listDevice)
		delete dev;
	m_listDevice.clear();
}

#define COLUMN_ID			0
#define COLUMN_MANUFACTURE	1
#define COLUMN_NAME			2
#define COLUMN_TYPE			3
#define COLUMN_IPADDR		4
void CDevListSee::Init()
{
	QStringList table_header;
	table_header << tr("ID") << tr("Manufacture") << tr("Name") << tr("Type") << tr("IP Address");
	ui.tableWidget_dev->setColumnCount(5);
	ui.tableWidget_dev->setHorizontalHeaderLabels(table_header);
	ui.tableWidget_dev->setColumnWidth(COLUMN_ID,300);
	ui.tableWidget_dev->setColumnWidth(COLUMN_MANUFACTURE,250);
	ui.tableWidget_dev->setColumnWidth(COLUMN_NAME,350);
	ui.tableWidget_dev->setColumnWidth(COLUMN_TYPE,200);
	ui.tableWidget_dev->setColumnWidth(COLUMN_IPADDR,200);
	ui.tableWidget_dev->setSelectionBehavior(QAbstractItemView::SelectRows);		//整行选择模式
	ui.tableWidget_dev->setFocusPolicy(Qt::NoFocus);								//去除焦点，无虚框
	ui.tableWidget_dev->verticalHeader()->setDefaultSectionSize(35);				//设置行高
	ui.tableWidget_dev->verticalHeader()->setVisible(false);						//去除最前列
	ui.tableWidget_dev->horizontalHeader()->setVisible(false);						//去除表头
	ui.tableWidget_dev->setFrameShape(QFrame::NoFrame);								//设置无边框
	ui.tableWidget_dev->horizontalHeader()->setStretchLastSection(true);			//设置充满表宽度
	ui.tableWidget_dev->horizontalHeader()->setHighlightSections(false);			//点击表时不对表头行光亮
	ui.tableWidget_dev->setShowGrid(false);											//设置不显示格子线
	ui.tableWidget_dev->setSelectionMode(QAbstractItemView::ExtendedSelection);		//可多选（Ctrl、Shift、  Ctrl+A都可以）
	ui.tableWidget_dev->setStyleSheet("selection-background-color:lightblue;");
	ui.tableWidget_dev->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2D9191;color:#ffffff}"); //设置表头背景色
	//ui.tableWidget_dev->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//设置水平、垂直滚动条样式
	ui.tableWidget_dev->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	ui.tableWidget_dev->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");

	ui.widget_dev->setVisible(true);
	ui.widget_edit->setVisible(false);

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf0f6, iconSize, iconWidth, iconHeight);
	ui.btnNew->setText(tr("  New"));
	ui.btnNew->setFixedHeight(btnHeight);
	ui.btnNew->setIcon(QIcon(iconNormal));
	ui.btnNew->setStyleSheet(QString("QPushButton#btnNew{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf044, iconSize, iconWidth, iconHeight);
	ui.btnModify->setText(tr("  Modity"));
	ui.btnModify->setFixedHeight(btnHeight);
	ui.btnModify->setIcon(QIcon(iconNormal));
	ui.btnModify->setStyleSheet(QString("QPushButton#btnModify{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #494e8f,stop:1 #494e8f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btnDelete->setText(tr("  Delete"));
	ui.btnDelete->setFixedHeight(btnHeight);
	ui.btnDelete->setIcon(QIcon(iconNormal));
	ui.btnDelete->setStyleSheet(QString("QPushButton#btnDelete{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #3e4145,stop:1 #3e4145);font:%1px;}").arg(charSize));
}

void CDevListSee::InitUi()
{
	QStringList qss;
	qss.append(QString("QWidget#widget_main{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QTableWidget#tableWidget_dev{background:transparent;}"));
	this->setStyleSheet(qss.join(""));
}

void CDevListSee::InitSlot()
{
	connect(ui.btnNew, SIGNAL(clicked(bool)), this, SLOT(SlotNewClicked()));
	connect(ui.btnModify, SIGNAL(clicked(bool)), this, SLOT(SlotModifycked()));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(SlotDeleteClicked()));
	connect(ui.btnOk, SIGNAL(clicked(bool)), this, SLOT(SlotOkClicked()));
	connect(ui.btnCancel, SIGNAL(clicked(bool)), this, SLOT(SlotCancelClicked()));
}

void CDevListSee::SetDevices()
{
	for (int i = 0; i < 30; i++)
	{
		stuDev *dev = new stuDev(tr("F320000000000%1").arg(i),"金智科技",tr("配网终端%1").arg(i),"PACS-5612F",tr("192.168.1.%1").arg(i)); 
		m_listDevice.append(dev);
	}
}

void CDevListSee::ShowDevices()
{
	ui.tableWidget_dev->clearContents();
	ui.tableWidget_dev->setRowCount(m_listDevice.count());

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(16);
	m_font.setBold(false);

	int row = 0;
	QTableWidgetItem *item;
	foreach (stuDev *dev, m_listDevice)
	{
		item = new QTableWidgetItem(dev->id);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFont(m_font);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		ui.tableWidget_dev->setItem(row,COLUMN_ID,item);

		item = new QTableWidgetItem(dev->manufacture);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFont(m_font);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		ui.tableWidget_dev->setItem(row,COLUMN_MANUFACTURE,item);

		item = new QTableWidgetItem(dev->name);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFont(m_font);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		ui.tableWidget_dev->setItem(row,COLUMN_NAME,item);

		item = new QTableWidgetItem(dev->type);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFont(m_font);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		ui.tableWidget_dev->setItem(row,COLUMN_TYPE,item);

		item = new QTableWidgetItem(dev->ip);
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFont(m_font);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		ui.tableWidget_dev->setItem(row,COLUMN_IPADDR,item);

		row ++;
	}
}

void CDevListSee::SlotNewClicked()
{
	ui.widget_dev->setVisible(false);
	ui.widget_edit->setVisible(true);
}

void CDevListSee::SlotModifycked()
{

}

void CDevListSee::SlotDeleteClicked()
{

}

void CDevListSee::SlotOkClicked()
{
	ui.widget_dev->setVisible(true);
	ui.widget_edit->setVisible(false);
}

void CDevListSee::SlotCancelClicked()
{

}
