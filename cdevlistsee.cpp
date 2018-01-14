#include "cdevlistsee.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "dnathmi.h"

#define charSize		20
#define iconSize		40
#define iconWidth		50
#define iconHeight		50
#define btnHeight		60

CDevListSee::CDevListSee(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pApp = (DNATHmi *)parent;

	Init();
	InitUi();
	InitSlot();

	SetDevices();
}

CDevListSee::~CDevListSee()
{
	
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
	//ui.tableWidget_dev->setSelectionMode(QAbstractItemView::ExtendedSelection);		//可多选（Ctrl、Shift、  Ctrl+A都可以）
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
	ui.btnModify->setText(tr("  Modify"));
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

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf029, iconSize, iconWidth, iconHeight);
	ui.btnQRMake->setText(tr("  QR Make"));
	ui.btnQRMake->setFixedHeight(btnHeight);
	ui.btnQRMake->setIcon(QIcon(iconNormal));
	ui.btnQRMake->setStyleSheet(QString("QPushButton#btnQRMake{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #f58220,stop:1 #f58220);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf109, iconSize, iconWidth, iconHeight);
	ui.btnQRShow->setText(tr("  QR Show"));
	ui.btnQRShow->setFixedHeight(btnHeight);
	ui.btnQRShow->setIcon(QIcon(iconNormal));
	ui.btnQRShow->setStyleSheet(QString("QPushButton#btnQRShow{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #494e8f,stop:1 #494e8f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf02f, iconSize, iconWidth, iconHeight);
	ui.btnQRPrint->setText(tr("  QR Print"));
	ui.btnQRPrint->setFixedHeight(btnHeight);
	ui.btnQRPrint->setIcon(QIcon(iconNormal));
	ui.btnQRPrint->setStyleSheet(QString("QPushButton#btnQRPrint{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #8f4b2e,stop:1 #8f4b2e);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btnOk->setText(tr("  Affirm"));
	ui.btnOk->setFixedHeight(btnHeight);
	ui.btnOk->setIcon(QIcon(iconNormal));
	ui.btnOk->setStyleSheet(QString("QPushButton#btnOk{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btnCancel->setText(tr("  Cancel"));
	ui.btnCancel->setFixedHeight(btnHeight);
	ui.btnCancel->setIcon(QIcon(iconNormal));
	ui.btnCancel->setStyleSheet(QString("QPushButton#btnCancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #3e4145,stop:1 #3e4145);font:%1px;}").arg(charSize));

	ui.label_id->setText(tr("ID Number:"));
	ui.label_manufacture->setText(tr("Manufacture:"));
	ui.label_name->setText(tr("Device Name:"));
	ui.label_type->setText(tr("Device Type:"));
	ui.label_address->setText(tr("Device Addr:"));
	ui.label_id->setStyleSheet(QString("QLabel#label_id{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_manufacture->setStyleSheet(QString("QLabel#label_manufacture{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_name->setStyleSheet(QString("QLabel#label_name{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_type->setStyleSheet(QString("QLabel#label_type{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_address->setStyleSheet(QString("QLabel#label_address{font:%1px;color:#383838;}").arg(charSize+10));

	ui.lineEdit_id->setFixedHeight(iconHeight);
	ui.lineEdit_id->setFixedWidth(500);
	ui.lineEdit_id->setStyleSheet(QString("QLineEdit#lineEdit_id{font:%1px;border:1px solid #181d4b;border-radius:5px;}").arg(charSize));

	ui.comboBox_manufacture->setFixedHeight(iconHeight);
	ui.comboBox_manufacture->setFixedWidth(500);

	ui.lineEdit_name->setFixedHeight(iconHeight);
	ui.lineEdit_name->setFixedWidth(500);
	ui.lineEdit_name->setStyleSheet(QString("QLineEdit#lineEdit_name{font:%1px;border:1px solid #181d4b;border-radius:5px;}").arg(charSize));

	ui.comboBox_type->setFixedHeight(iconHeight);
	ui.comboBox_type->setFixedWidth(500);

	ui.lineEdit_address->setFixedHeight(iconHeight);
	ui.lineEdit_address->setFixedWidth(500);
	ui.lineEdit_address->setStyleSheet(QString("QLineEdit#lineEdit_address{font:%1px;border:1px solid #181d4b;border-radius:5px;}").arg(charSize));

	m_iRow = -1;

	ui.comboBox_manufacture->addItem("");
	QDir dir(Common::GetCurrentAppPath()+"devices");
	dir.setFilter(QDir::Dirs);
	QFileInfoList list = dir.entryInfoList();
	foreach (QFileInfo fileInfo,list)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		ui.comboBox_manufacture->addItem(fileInfo.fileName());
	}
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
	connect(ui.btnModify, SIGNAL(clicked(bool)), this, SLOT(SlotModifyClicked()));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(SlotDeleteClicked()));
	connect(ui.btnQRMake, SIGNAL(clicked(bool)), this, SLOT(SlotQRMakeClicked()));
	connect(ui.btnQRShow, SIGNAL(clicked(bool)), this, SLOT(SlotQRShowClicked()));
	connect(ui.btnQRPrint, SIGNAL(clicked(bool)), this, SLOT(SlotQRPrintClicked()));
	connect(ui.btnOk, SIGNAL(clicked(bool)), this, SLOT(SlotOkClicked()));
	connect(ui.btnCancel, SIGNAL(clicked(bool)), this, SLOT(SlotCancelClicked()));
	connect(ui.comboBox_manufacture, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(SlotComboBoxManufactureChanged(const QString&)));
	connect(m_pApp->m_pCommThread, SIGNAL(SigCmdDevList()), this, SLOT(SlotCmdDevList()));
}

void CDevListSee::SlotNewClicked()
{
	ui.lineEdit_id->clear();
	ui.comboBox_manufacture->setCurrentIndex(0);
	ui.lineEdit_name->clear();
	ui.comboBox_type->setCurrentIndex(0);
	ui.lineEdit_address->clear();

	ui.widget_dev->setVisible(false);
	ui.widget_edit->setVisible(true);

	m_eListSeeState = LISTSEE_NEW;
}

void CDevListSee::SlotModifyClicked()
{
	QList<QTableWidgetSelectionRange> ranges = ui.tableWidget_dev->selectedRanges();
	if (ranges.count() <= 0)
	{
		MsgBox::Instance()->information(tr("Please select item."));
		return;
	}
	else if (ranges.count() > 1 || (ranges.count() == 1 && (ranges.at(0).bottomRow() - ranges.at(0).topRow() > 0)))
	{
		MsgBox::Instance()->information(tr("Please select a item."));
		return;
	}

	m_iRow = ranges.at(0).topRow();
	ui.lineEdit_id->setText(ui.tableWidget_dev->item(m_iRow,COLUMN_ID)->text());
	ui.lineEdit_name->setText(ui.tableWidget_dev->item(m_iRow,COLUMN_NAME)->text());
	ui.lineEdit_address->setText(ui.tableWidget_dev->item(m_iRow,COLUMN_IPADDR)->text());

	bool bFind = false;
	for (int i = 0; i < ui.comboBox_manufacture->count(); i++)
	{
		QString a = ui.tableWidget_dev->item(m_iRow,COLUMN_MANUFACTURE)->text();
		QString b = ui.comboBox_manufacture->itemText(i);
		if (ui.tableWidget_dev->item(m_iRow,COLUMN_MANUFACTURE)->text() == ui.comboBox_manufacture->itemText(i))
		{
			ui.comboBox_manufacture->setCurrentIndex(i);
			bFind = true;
		}
	}
	if (!bFind)
		ui.comboBox_manufacture->setCurrentIndex(0);

	SlotComboBoxManufactureChanged(ui.comboBox_manufacture->currentText());
	bFind = false;
	for (int i = 0; i < ui.comboBox_type->count(); i++)
	{
		if (ui.tableWidget_dev->item(m_iRow,COLUMN_TYPE)->text() == ui.comboBox_type->itemText(i))
		{
			ui.comboBox_type->setCurrentIndex(i);
			bFind = true;
		}
	}
	if (!bFind)
		ui.comboBox_type->setCurrentIndex(0);

	ui.widget_dev->setVisible(false);
	ui.widget_edit->setVisible(true);

	m_eListSeeState = LISTSEE_MODIFY;
}

void CDevListSee::SlotDeleteClicked()
{
	QList<QTableWidgetSelectionRange> ranges = ui.tableWidget_dev->selectedRanges();
	if (ranges.count() <= 0)
	{
		MsgBox::Instance()->information(tr("Please select item."));
		return;
	}

	QMap<int,QString> mapRow;
	for(int i = 0; i < ranges.count(); i++)
	{
		int topRow = ranges.at(i).topRow();
		int bottomRow = ranges.at(i).bottomRow();
		for(int row = topRow; row <= bottomRow; row++)
			mapRow.insert(row,ui.tableWidget_dev->item(row,COLUMN_ID)->text());
	}

	QList<int> rowList;
	QMapIterator<int,QString> iter(mapRow);
	while (iter.hasNext())	
	{
		iter.next();
		rowList.insert(0,iter.key());
	}

	foreach (int row, rowList)
		ui.tableWidget_dev->removeRow(row);
}

void CDevListSee::SlotQRMakeClicked()
{

}

void CDevListSee::SlotQRShowClicked()
{

}

void CDevListSee::SlotQRPrintClicked()
{

}

void CDevListSee::SlotOkClicked()
{
	if (ui.lineEdit_id->text().isEmpty())
	{
		MsgBox::Instance()->warning("Please input device ID.");
		return;
	}

	if (ui.comboBox_manufacture->currentText().isEmpty())
	{
		MsgBox::Instance()->warning("Please input device manfacture.");
		return;
	}

	if (ui.lineEdit_name->text().isEmpty())
	{
		MsgBox::Instance()->warning("Please input device name.");
		return;
	}

	if (ui.comboBox_type->currentText().isEmpty())
	{
		MsgBox::Instance()->warning("Please input device type.");
		return;
	}

	if (ui.lineEdit_address->text().isEmpty())
	{
		MsgBox::Instance()->warning("Please input device IP address.");
		return;
	}

	if (m_eListSeeState == LISTSEE_NEW)
	{
		int count = ui.tableWidget_dev->rowCount();
		ui.tableWidget_dev->setRowCount(count+1);
		AddDevice(count,
			ui.lineEdit_id->text(),
			ui.comboBox_manufacture->currentText(),
			ui.lineEdit_name->text(),
			ui.comboBox_type->currentText(),
			ui.lineEdit_address->text());
		//应该需要修改对应存放设备列表的文件
	}
	else if (m_eListSeeState == LISTSEE_MODIFY)
	{
		ui.tableWidget_dev->item(m_iRow,COLUMN_ID)->setText(ui.lineEdit_id->text());
		ui.tableWidget_dev->item(m_iRow,COLUMN_MANUFACTURE)->setText(ui.comboBox_manufacture->currentText());
		ui.tableWidget_dev->item(m_iRow,COLUMN_NAME)->setText(ui.lineEdit_name->text());
		ui.tableWidget_dev->item(m_iRow,COLUMN_TYPE)->setText(ui.comboBox_type->currentText());
		ui.tableWidget_dev->item(m_iRow,COLUMN_IPADDR)->setText(ui.lineEdit_address->text());
		//应该需要修改对应存放设备列表的文件
	}

	SlotCancelClicked();
}

void CDevListSee::SlotCancelClicked()
{
	ui.widget_dev->setVisible(true);
	ui.widget_edit->setVisible(false);
}

void CDevListSee::SlotComboBoxManufactureChanged(const QString& text)
{
	if (text.isEmpty())
		return;

	ui.comboBox_type->clear();
	ui.comboBox_type->addItem("");
	QDir dir(Common::GetCurrentAppPath()+"devices/"+text);
	dir.setFilter(QDir::Dirs);
	QFileInfoList list = dir.entryInfoList();
	foreach (QFileInfo fileInfo,list)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		ui.comboBox_type->addItem(fileInfo.fileName());
	}
}

void CDevListSee::SlotCmdDevList()
{
	m_pApp->m_pCommThread->m_mutex.lock();
	ShowDevices();
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevListSee::SetDevices()
{
	SlotComboBoxManufactureChanged(ui.comboBox_manufacture->currentText());

	foreach (stuDev *dev, m_pApp->m_pCommThread->m_listDevice)
		delete dev;
	m_pApp->m_pCommThread->m_listDevice.clear();

	m_pApp->m_pCommThread->m_mutex.lock();
	m_pApp->m_pCommThread->SetCommand(CMD_DEVLIST);
	m_pApp->m_pCommThread->m_mutex.unlock();
}

void CDevListSee::ShowDevices()
{
	ui.tableWidget_dev->clearContents();
	ui.tableWidget_dev->setRowCount(m_pApp->m_pCommThread->m_listDevice.count());

	int row = 0;
	foreach (stuDev *dev, m_pApp->m_pCommThread->m_listDevice)
		AddDevice(row++,dev->id,dev->manufacture,dev->name,dev->type,dev->ip);
}

void CDevListSee::AddDevice(int row,QString id,QString manufacture,QString name,QString type,QString address)
{
	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(16);
	m_font.setBold(false);

	QTableWidgetItem *item;
	item = new QTableWidgetItem(id);
	item->setBackgroundColor(QColor(0,0,0,0));
	item->setTextColor(QColor(0,0,0));
	item->setTextAlignment(Qt::AlignCenter);
	item->setFont(m_font);
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
	ui.tableWidget_dev->setItem(row,COLUMN_ID,item);

	item = new QTableWidgetItem(manufacture);
	item->setBackgroundColor(QColor(0,0,0,0));
	item->setTextColor(QColor(0,0,0));
	item->setTextAlignment(Qt::AlignCenter);
	item->setFont(m_font);
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
	ui.tableWidget_dev->setItem(row,COLUMN_MANUFACTURE,item);

	item = new QTableWidgetItem(name);
	item->setBackgroundColor(QColor(0,0,0,0));
	item->setTextColor(QColor(0,0,0));
	item->setTextAlignment(Qt::AlignCenter);
	item->setFont(m_font);
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
	ui.tableWidget_dev->setItem(row,COLUMN_NAME,item);

	item = new QTableWidgetItem(type);
	item->setBackgroundColor(QColor(0,0,0,0));
	item->setTextColor(QColor(0,0,0));
	item->setTextAlignment(Qt::AlignCenter);
	item->setFont(m_font);
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
	ui.tableWidget_dev->setItem(row,COLUMN_TYPE,item);

	item = new QTableWidgetItem(address);
	item->setBackgroundColor(QColor(0,0,0,0));
	item->setTextColor(QColor(0,0,0));
	item->setTextAlignment(Qt::AlignCenter);
	item->setFont(m_font);
	item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
	ui.tableWidget_dev->setItem(row,COLUMN_IPADDR,item);
}
