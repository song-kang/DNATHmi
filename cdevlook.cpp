#include "cdevlook.h"
#include "iconhelper.h"
#include "lightbutton.h"

CDevLook::CDevLook(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
	InitTableLog();
	Start();
}

CDevLook::~CDevLook()
{
	foreach (NavButton *btn, m_listBtnFeed)
		delete btn;
	foreach (stuMeausre *mea, m_listMeausreCol1)
		delete mea;
	foreach (stuMeausre *mea, m_listMeausreCol2)
		delete mea;
	foreach (stuMeausre *mea, m_listMeausreCol3)
		delete mea;
	foreach (stuMeausre *mea, m_listPowerCol1)
		delete mea;
	foreach (stuMeausre *mea, m_listPowerCol2)
		delete mea;
	foreach (stuDigital *dgt, m_listDigital)
		delete dgt;

	m_listBtnFeed.clear();
	m_listMeausreCol1.clear();
	m_listMeausreCol2.clear();
	m_listMeausreCol3.clear();
	m_listPowerCol1.clear();
	m_listPowerCol2.clear();
	m_listDigital.clear();
}

void CDevLook::Init()
{
	ui.scrollArea->setFixedWidth(180);
	ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollAreaWidgetContents->setContentsMargins(0,0,0,0);

	ui.label_meaure->setText(tr("Measurement variables"));
	ui.label_meaure->setStyleSheet("color:#2D9191");
	ui.label_power->setText(tr("Power variables"));
	ui.label_power->setStyleSheet("color:#2D9191");
	ui.label_digital->setText(tr("Digital variables"));
	ui.label_digital->setStyleSheet("color:#2D9191");
	ui.label_log->setText(tr("Log information"));
	ui.label_log->setStyleSheet("color:#2D9191");

	ui.scrollArea_mea->setFixedHeight(310);
	ui.scrollArea_mea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea_mea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	ui.scrollArea_power->setFixedHeight(100);
	ui.scrollArea_power->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea_power->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	ui.scrollArea_dgt->setFixedWidth(300);
	ui.scrollArea_dgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.scrollArea_dgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	InitTableLog();

	QStringList qss;
	qss.append(QString("QWidget#widget_content{background-color:rgb(255,255,255,150);}"));
	qss.append(QString("QLabel#label_meaure{background:transparent;}"));
	qss.append(QString("QLabel#label_power{background:transparent;}"));
	qss.append(QString("QLabel#label_dgt{background:transparent;}"));
	qss.append(QString("QLabel#label_log{background:transparent;}"));
	qss.append(QString("QTableWidget#tableWidget_power{background:transparent;}"));
	qss.append(QString("QTableWidget#tableWidget_digital{background:transparent;}"));
	qss.append(QString("QTableWidget#tableWidget_log{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_mea{background:transparent;}"));
	qss.append(QString("QWidget#scrollAreaWidgetMea{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_power{background:transparent;}"));
	qss.append(QString("QWidget#scrollAreaWidgetPower{background:transparent;}"));
	qss.append(QString("QScrollArea#scrollArea_dgt{background:transparent;}"));
	qss.append(QString("QWidget#scrollAreaWidgetDgt{background:transparent;}"));
	this->setStyleSheet(qss.join(""));

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(true);
	ui.label_meaure->setFont(m_font);
	ui.label_power->setFont(m_font);
	ui.label_digital->setFont(m_font);
	ui.label_log->setFont(m_font);
}

#define COLUMN_NO			0
#define COLUMN_TIME			1
#define COLUMN_DESC			2
#define COLUMN_STATE		3
void CDevLook::InitTableLog()
{
	QStringList table_header;
	table_header << tr("No.") << tr("Time") << tr("Description") << tr("State");
	ui.tableWidget_log->setColumnCount(4);
	ui.tableWidget_log->setHorizontalHeaderLabels(table_header);
	ui.tableWidget_log->setColumnWidth(COLUMN_NO,80);
	ui.tableWidget_log->setColumnWidth(COLUMN_TIME,200);
	ui.tableWidget_log->setColumnWidth(COLUMN_DESC,400);
	ui.tableWidget_log->setColumnWidth(COLUMN_STATE,100);
	ui.tableWidget_log->setSelectionBehavior(QAbstractItemView::SelectRows);		//整行选择模式
	ui.tableWidget_log->setFocusPolicy(Qt::NoFocus);								//去除焦点，无虚框
	ui.tableWidget_log->verticalHeader()->setDefaultSectionSize(30);				//设置行高
	ui.tableWidget_log->verticalHeader()->setVisible(false);						//去除最前列
	//ui.tableWidget_log->horizontalHeader()->setVisible(false);						//去除表头
	//ui.tableWidget_log->setFrameShape(QFrame::NoFrame);								//设置无边框
	ui.tableWidget_log->horizontalHeader()->setStretchLastSection(true);			//设置充满表宽度
	ui.tableWidget_log->horizontalHeader()->setHighlightSections(false);			//点击表时不对表头行光亮
	ui.tableWidget_log->setShowGrid(false);											//设置不显示格子线
	ui.tableWidget_log->setSelectionMode(QAbstractItemView::ExtendedSelection);		//可多选（Ctrl、Shift、  Ctrl+A都可以）
	ui.tableWidget_log->setStyleSheet("selection-background-color:lightblue;");
	ui.tableWidget_log->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2D9191;color:#ffffff}"); //设置表头背景色
	ui.tableWidget_log->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CDevLook::InitUi()
{
	this->setObjectName(DeviceLook);
}

void CDevLook::InitSlot()
{

}

void CDevLook::Start()
{
	SetFeeder();
	SetMeasure();
	SetPower();
	SetDigital();
	SetLog();
	ShowMeasure();
	ShowPower();
	ShowDigital();
}

void CDevLook::SlotNavButtonClick()
{
	NavButton *btn = (NavButton *)sender();
	for (int i = 0; i < m_listBtnFeed.count(); i++)
		m_listBtnFeed.at(i)->setChecked(m_listBtnFeed.at(i) == btn);

	ui.label_meaure->setText(tr("%1 Measurement variables").arg(btn->text()));
	ui.label_power->setText(tr("%1 Power variables").arg(btn->text()));
	ui.label_digital->setText(tr("%1 Digital variables").arg(btn->text()));
	ui.label_log->setText(tr("%1 Log information").arg(btn->text()));
}

void CDevLook::SetFeeder()
{
	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(false);

	QVBoxLayout *vLayout = new QVBoxLayout();
	for (int i = 0,j = 1; i < 20; i++,j++) //假设20条馈线
	{
		NavButton *nav = new NavButton;
		nav->setFont(m_font);
		nav->setFixedHeight(55);
		nav->setText(tr("#%1 Feeder").arg(j));
		vLayout->addWidget(nav);
		m_listBtnFeed.append(nav);
	}
	vLayout->addStretch();
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0,0,0,0);
	ui.scrollAreaWidgetContents->setLayout(vLayout);

	QList<QChar> pixChar;
	for (int i = 0; i < 20; i++) //假设20条馈线
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

void CDevLook::SetMeasure()
{
	m_listMeausreCol1.clear();
	stuMeausre *mea = new stuMeausre(0xf1c0,"A相电流",5.00,"安培");
	m_listMeausreCol1.append(mea);
	mea = new stuMeausre(0xf1c0,"B相电流",4.08,"安培");
	m_listMeausreCol1.append(mea);
	mea = new stuMeausre(0xf1c0,"C相电流",4.91,"安培");
	m_listMeausreCol1.append(mea);
	mea = new stuMeausre(0xf1c0,"A相电压",100.21,"伏特");
	m_listMeausreCol1.append(mea);
	mea = new stuMeausre(0xf1c0,"B相电压",98.43,"伏特");
	m_listMeausreCol1.append(mea);
	mea = new stuMeausre(0xf1c0,"C相电压",99.30,"伏特");
	m_listMeausreCol1.append(mea);

	m_listMeausreCol2.clear();
	mea = new stuMeausre(0xf1c0,"A相保护电流",10.10,"安培");
	m_listMeausreCol2.append(mea);
	mea = new stuMeausre(0xf1c0,"B相保护电流",0.00,"安培");
	m_listMeausreCol2.append(mea);
	mea = new stuMeausre(0xf1c0,"C相保护电流",9.08,"安培");
	m_listMeausreCol2.append(mea);
	mea = new stuMeausre(0xf1c0,"A相保护电压",100.00,"伏特");
	m_listMeausreCol2.append(mea);
	mea = new stuMeausre(0xf1c0,"B相保护电压",102.23,"伏特");
	m_listMeausreCol2.append(mea);
	mea = new stuMeausre(0xf1c0,"C相保护电压",99.03,"伏特");
	m_listMeausreCol2.append(mea);

	m_listMeausreCol3.clear();
	mea = new stuMeausre(0xf1c0,"频率",50.00,"赫兹");
	m_listMeausreCol3.append(mea);
	mea = new stuMeausre(0xf1c0,"温度",36.4,"摄氏度");
	m_listMeausreCol3.append(mea);
}

void CDevLook::ShowMeasure()
{
	QVBoxLayout *v = new QVBoxLayout();
	foreach (stuMeausre *mea, m_listMeausreCol1)
	{
		QHBoxLayout *h = new QHBoxLayout();

		QPushButton *icon = new QPushButton;
		icon->setText("");
		icon->setIcon(QIcon(IconHelper::Instance()->getPixmap("#2D9191", mea->icon, 15, 30, 30)));
		icon->setStyleSheet("background:transparent;");

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(mea->desc));
		desc->setFixedWidth(80);
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		QLabel *val = new QLabel;
		val->setText(QString().sprintf("%5.2f",mea->value));
		val->setFixedWidth(60);
		val->setAlignment(Qt::AlignRight);
		val->setStyleSheet("font:14px");
		if (mea->value > 100.0)
			val->setStyleSheet("color:#ff0000");

		QLabel *unit = new QLabel;
		unit->setText(mea->unit);
		unit->setAlignment(Qt::AlignLeft);
		unit->setStyleSheet("font:14px");

		h->addWidget(icon,0,Qt::AlignVCenter|Qt::AlignRight);
		h->addWidget(desc,0,Qt::AlignVCenter);
		h->addWidget(val,0,Qt::AlignVCenter);
		h->addWidget(unit,0,Qt::AlignVCenter);
		h->setSpacing(5);
		v->addLayout(h);
	}
	v->addStretch();
	v->setSpacing(15);
	ui.gridLayout_m1->addLayout(v,0,0);

	v = new QVBoxLayout();
	foreach (stuMeausre *mea, m_listMeausreCol2)
	{
		QHBoxLayout *h = new QHBoxLayout();
		
		QPushButton *icon = new QPushButton;
		icon->setText("");
		icon->setIcon(QIcon(IconHelper::Instance()->getPixmap("#2D9191", mea->icon, 15, 30, 30)));
		icon->setStyleSheet("background:transparent;");

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(mea->desc));
		desc->setFixedWidth(100);
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		QLabel *val = new QLabel;
		val->setText(QString().sprintf("%5.2f",mea->value));
		val->setFixedWidth(60);
		val->setAlignment(Qt::AlignRight);
		val->setStyleSheet("font:14px");
		if (mea->value > 100.0)
			val->setStyleSheet("color:#ff0000");

		QLabel *unit = new QLabel;
		unit->setText(mea->unit);
		unit->setAlignment(Qt::AlignLeft);
		unit->setStyleSheet("font:14px");

		h->addWidget(icon,0,Qt::AlignVCenter|Qt::AlignRight);
		h->addWidget(desc,0,Qt::AlignVCenter);
		h->addWidget(val,0,Qt::AlignVCenter);
		h->addWidget(unit,0,Qt::AlignVCenter);
		h->setSpacing(5);
		v->addLayout(h);
	}
	v->addStretch();
	v->setSpacing(15);
	ui.gridLayout_m2->addLayout(v,0,0);

	v = new QVBoxLayout();
	foreach (stuMeausre *mea, m_listMeausreCol3)
	{
		QHBoxLayout *h = new QHBoxLayout();

		QPushButton *icon = new QPushButton;
		icon->setText("");
		icon->setIcon(QIcon(IconHelper::Instance()->getPixmap("#2D9191", mea->icon, 15, 30, 30)));
		icon->setStyleSheet("background:transparent;");

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(mea->desc));
		desc->setFixedWidth(40);
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		QLabel *val = new QLabel;
		val->setText(QString().sprintf("%5.2f",mea->value));
		val->setFixedWidth(60);
		val->setAlignment(Qt::AlignRight);
		val->setStyleSheet("font:14px");
		if (mea->value > 100.0)
			val->setStyleSheet("color:#ff0000");

		QLabel *unit = new QLabel;
		unit->setText(mea->unit);
		unit->setAlignment(Qt::AlignLeft);
		unit->setStyleSheet("font:14px");

		h->addWidget(icon,0,Qt::AlignVCenter|Qt::AlignRight);
		h->addWidget(desc,0,Qt::AlignVCenter);
		h->addWidget(val,0,Qt::AlignVCenter);
		h->addWidget(unit,0,Qt::AlignVCenter);
		h->setSpacing(5);
		v->addLayout(h);
	}
	v->addStretch();
	v->setSpacing(15);
	ui.gridLayout_m3->addLayout(v,0,0);
}

void CDevLook::SetPower()
{
	m_listPowerCol1.clear();
	stuMeausre *power = new stuMeausre(0xf1c0,"正向有功1",435.60,"KW");
	m_listPowerCol1.append(power);
	power = new stuMeausre(0xf1c0,"反向有功1",34.08,"KVar");
	m_listPowerCol1.append(power);

	m_listPowerCol2.clear();
	power = new stuMeausre(0xf1c0,"正向有功2",5.80,"KW");
	m_listPowerCol2.append(power);
	power = new stuMeausre(0xf1c0,"反向有功2",43435.08,"KVar");
	m_listPowerCol2.append(power);
}

void CDevLook::ShowPower()
{
	QVBoxLayout *v = new QVBoxLayout();
	foreach (stuMeausre *mea, m_listPowerCol1)
	{
		QHBoxLayout *h = new QHBoxLayout();

		QPushButton *icon = new QPushButton;
		icon->setText("");
		icon->setIcon(QIcon(IconHelper::Instance()->getPixmap("#2D9191", mea->icon, 15, 30, 30)));
		icon->setStyleSheet("background:transparent;");

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(mea->desc));
		desc->setFixedWidth(80);
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		QLabel *val = new QLabel;
		val->setText(QString().sprintf("%5.2f",mea->value));
		val->setFixedWidth(60);
		val->setAlignment(Qt::AlignRight);
		val->setStyleSheet("font:14px");
		if (mea->value > 100.0)
			val->setStyleSheet("color:#ff0000");

		QLabel *unit = new QLabel;
		unit->setText(mea->unit);
		unit->setAlignment(Qt::AlignLeft);
		unit->setStyleSheet("font:14px");

		h->addWidget(icon,0,Qt::AlignVCenter|Qt::AlignRight);
		h->addWidget(desc,0,Qt::AlignVCenter);
		h->addWidget(val,0,Qt::AlignVCenter);
		h->addWidget(unit,0,Qt::AlignVCenter);
		h->setSpacing(5);
		v->addLayout(h);
	}
	v->addStretch();
	v->setSpacing(15);
	ui.gridLayout_p1->addLayout(v,0,0);

	v = new QVBoxLayout();
	foreach (stuMeausre *mea, m_listPowerCol2)
	{
		QHBoxLayout *h = new QHBoxLayout();

		QPushButton *icon = new QPushButton;
		icon->setText("");
		icon->setIcon(QIcon(IconHelper::Instance()->getPixmap("#2D9191", mea->icon, 15, 30, 30)));
		icon->setStyleSheet("background:transparent;");

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(mea->desc));
		desc->setFixedWidth(80);
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		QLabel *val = new QLabel;
		val->setText(QString().sprintf("%5.2f",mea->value));
		val->setFixedWidth(60);
		val->setAlignment(Qt::AlignRight);
		val->setStyleSheet("font:14px");
		if (mea->value > 100.0)
			val->setStyleSheet("color:#ff0000");	

		QLabel *unit = new QLabel;
		unit->setText(mea->unit);
		unit->setAlignment(Qt::AlignLeft);
		unit->setStyleSheet("font:14px");

		h->addWidget(icon,0,Qt::AlignVCenter|Qt::AlignRight);
		h->addWidget(desc,0,Qt::AlignVCenter);
		h->addWidget(val,0,Qt::AlignVCenter);
		h->addWidget(unit,0,Qt::AlignVCenter);
		h->setSpacing(5);
		v->addLayout(h);
	}
	v->addStretch();
	v->setSpacing(15);
	ui.gridLayout_p2->addLayout(v,0,0);
}

void CDevLook::SetDigital()
{
	m_listDigital.clear();
	for (int i = 0; i < 30; i++)
	{
		stuDigital *dgt;
		if (i % 2)
			dgt = new stuDigital(LED_GREED,tr("遥信状态信号 %1").arg(i));
		else
			dgt = new stuDigital(LED_RED,tr("遥信状态信号 %1").arg(i));

		m_listDigital.append(dgt);
	}
}

void CDevLook::ShowDigital()
{
	foreach (stuDigital *dgt, m_listDigital)
	{
		LightButton *t = new LightButton;
		if (dgt->state == LED_GREED)
			t->setLightGreen();
		else
			t->setLightRed();
		t->setFixedWidth(20);

		QLabel *desc = new QLabel;
		desc->setText(tr("%1").arg(dgt->desc));
		desc->setAlignment(Qt::AlignLeft);
		desc->setStyleSheet("font:14px");

		ui.formLayout_dgt->addRow(t,desc);
	}
	ui.formLayout_dgt->setSpacing(8);
}

void CDevLook::SetLog()
{
	ui.tableWidget_log->clearContents();
	ui.tableWidget_log->setRowCount(20);

	QFont m_font;
	m_font.setFamily("Microsoft YaHei");
	m_font.setPixelSize(14);
	m_font.setBold(false);

	int row = 0;
	QTableWidgetItem *item;
	for (int i = 0; i < 20; i++)
	{
		item = new QTableWidgetItem(tr("%1").arg(i));
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setFont(m_font);
		ui.tableWidget_log->setItem(row,COLUMN_NO,item);

		QDateTime dt = QDateTime::currentDateTime();
		item = new QTableWidgetItem(dt.toString("yyyy-MM-dd hh:mm:ss.zzz"));
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setFont(m_font);
		ui.tableWidget_log->setItem(row,COLUMN_TIME,item);

		item = new QTableWidgetItem("系统关机......");
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setFont(m_font);
		ui.tableWidget_log->setItem(row,COLUMN_DESC,item);

		item = new QTableWidgetItem("正常");
		item->setBackgroundColor(QColor(0,0,0,0));
		item->setTextColor(QColor(0,0,0));
		item->setTextAlignment(Qt::AlignCenter);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));	//设置item项不可编辑
		item->setFont(m_font);
		ui.tableWidget_log->setItem(row,COLUMN_STATE,item);

		row ++;
	}
}
