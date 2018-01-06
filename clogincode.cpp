#include "clogincode.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "cdev.h"

#define charSize		20
#define titleSize		40
#define iconSize		40
#define iconWidth		40
#define iconHeight		40
#define btnHeight		60

CLoginCode::CLoginCode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
	InitUi();
	InitSlot();
}

CLoginCode::~CLoginCode()
{

}

void CLoginCode::Init()
{
	ui.widget_info->setVisible(false);

	ui.label_title->setText(tr("Please enter the device number"));
	ui.label_title->setStyleSheet(QString("QLabel#label_title{font:%1px;color:#383838;}").arg(titleSize));

	ui.lineEdit_no->setFixedHeight(iconHeight);
	ui.lineEdit_no->setFixedWidth(500);
	ui.lineEdit_no->setStyleSheet(QString("QLineEdit#lineEdit_no{font:%1px;border:2px solid #181d4b;border-radius:10px;}").arg(charSize));

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf090, iconSize, iconWidth, iconHeight);
	ui.btnLogin->setText(tr("  Login"));
	ui.btnLogin->setFixedHeight(btnHeight);
	ui.btnLogin->setIcon(QIcon(iconNormal));
	ui.btnLogin->setStyleSheet(QString("QPushButton#btnLogin{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	ui.label_id->setText(tr("ID Number:"));
	ui.label_factory->setText(tr("Manufacture:"));
	ui.label_type->setText(tr("Device Type:"));
	ui.label_addr->setText(tr("Device Addr:"));
	ui.label_id->setStyleSheet(QString("QLabel#label_id{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_factory->setStyleSheet(QString("QLabel#label_factory{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_type->setStyleSheet(QString("QLabel#label_type{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_addr->setStyleSheet(QString("QLabel#label_addr{font:%1px;color:#383838;}").arg(charSize+10));

	ui.label_id_text->setText(QString::null);
	ui.label_factory_text->setText(QString::null);
	ui.label_type_text->setText(QString::null);
	ui.label_addr_text->setText(QString::null);

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
	ui.btnOk->setText(tr("  Affirm"));
	ui.btnOk->setFixedHeight(iconHeight);
	ui.btnOk->setIcon(QIcon(iconNormal));
	ui.btnOk->setStyleSheet(QString("QPushButton#btnOk{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1d953f,stop:1 #1d953f);font:%1px;}").arg(charSize));

	iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00d, iconSize, iconWidth, iconHeight);
	ui.btnCancel->setText(tr("  Cancel"));
	ui.btnCancel->setFixedHeight(iconHeight);
	ui.btnCancel->setIcon(QIcon(iconNormal));
	ui.btnCancel->setStyleSheet(QString("QPushButton#btnCancel{border:1px solid #242424;border-radius:5px;color:#DCDCDC;padding:8px;"
		"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #3e4145,stop:1 #3e4145);font:%1px;}").arg(charSize));

}

void CLoginCode::InitUi()
{
	this->setObjectName(LoginCode);
}

void CLoginCode::InitSlot()
{
	connect(ui.btnLogin, SIGNAL(clicked(bool)), this, SLOT(SlotLoginClicked()));
	connect(ui.btnOk, SIGNAL(clicked(bool)), this, SLOT(SlotOkClicked()));
	connect(ui.btnCancel, SIGNAL(clicked(bool)), this, SLOT(SlotCancelClicked()));
}

void CLoginCode::SlotLoginClicked()
{
	if (ui.lineEdit_no->text().trimmed().isEmpty())
	{
		MsgBox::Instance()->warning(tr("Device number is empty!"));
		return;
	}

	if (!Start())
		return;

	ui.widget_login->setVisible(false);
	ui.widget_info->setVisible(true);
}

void CLoginCode::SlotOkClicked()
{
	emit SigWidgetName(Device);
}

void CLoginCode::SlotCancelClicked()
{
	ui.lineEdit_no->clear();
	ui.widget_info->setVisible(false);
	ui.widget_login->setVisible(true);
}

bool CLoginCode::Start()
{
	//测试数据
	ui.label_id_text->setText("W202987348749234");
	ui.label_factory_text->setText("江苏金智科技股份有限公司");
	ui.label_type_text->setText("DNT5000");
	ui.label_addr_text->setText("172.20.56.34");
	ui.label_id_text->setStyleSheet(QString("QLabel#label_id_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_factory_text->setStyleSheet(QString("QLabel#label_factory_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_type_text->setStyleSheet(QString("QLabel#label_type_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_addr_text->setStyleSheet(QString("QLabel#label_addr_text{font:%1px;color:#383838;}").arg(charSize+10));

	return true;
}
