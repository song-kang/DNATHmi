#include "cloginqrcode.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "dnathmi.h"
#include "cdev.h"

#define charSize		20
#define titleSize		20
#define iconSize		40
#define iconWidth		40
#define iconHeight		40
#define btnHeight		60

CLoginQRCode::CLoginQRCode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pApp = (DNATHmi *)parent;

	Init();
	InitUi();
	InitSlot();
	OpenCamera();
}

CLoginQRCode::~CLoginQRCode()
{

}

void CLoginQRCode::Init()
{
	ui.widget_info->setVisible(false);

	ui.label_hit->setText(tr("The QRCode in the identification box"));
	ui.label_hit->setStyleSheet(QString("QLabel#label_hit{font:%1px;color:#383838;}").arg(titleSize));

	ui.label_camera->setPixmap(IconHelper::Instance()->getPixmap("#181d4b", 0xf030, iconSize, 60, 60));
	ui.label_camera->setFixedSize(600, 480);
	ui.label_camera->setStyleSheet("QLabel#label_camera{background-color:#f2eada;border:3px solid #181d4b;border-radius:5px;}");

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
	ui.label_id_text->setStyleSheet(QString("QLabel#label_id_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_factory_text->setStyleSheet(QString("QLabel#label_factory_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_type_text->setStyleSheet(QString("QLabel#label_type_text{font:%1px;color:#383838;}").arg(charSize+10));
	ui.label_addr_text->setStyleSheet(QString("QLabel#label_addr_text{font:%1px;color:#383838;}").arg(charSize+10));

	QPixmap iconNormal = IconHelper::Instance()->getPixmap(QColor(255,255,255).name(), 0xf00c, iconSize, iconWidth, iconHeight);
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

	m_pReadFrameTimer = new QTimer(this);
}

void CLoginQRCode::InitUi()
{
	this->setObjectName(LoginQRCode);
}

void CLoginQRCode::InitSlot()
{
	connect(ui.btnOk, SIGNAL(clicked(bool)), this, SLOT(SlotOkClicked()));
	connect(ui.btnCancel, SIGNAL(clicked(bool)), this, SLOT(SlotCancelClicked()));
	connect(m_pReadFrameTimer, SIGNAL(timeout()), this, SLOT(SlotReadFrame()));
}

void CLoginQRCode::SlotOkClicked()
{
	m_pApp->SetDeviceId(ui.label_id_text->text());
	emit SigWidgetName(Device);
}

void CLoginQRCode::SlotCancelClicked()
{
	ui.widget_info->setVisible(false);
	ui.widget_login->setVisible(true);
	OpenCamera();
}

void CLoginQRCode::SlotReadFrame()
{
	if (!m_cap.isOpened())
		return ;

	cv::Mat frame;
	m_cap >> frame; //输出到界面显示用
	if(!m_pApp->m_pQRThread->m_frame.data)
		m_cap >> m_pApp->m_pQRThread->m_frame; //输出到线程识别用

	QImage image = QImage((const uchar*)frame.datastart, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
	float scaled = (float)(frame.cols*1.0f / frame.rows);
	int width = 50;
	QImage scaledImg = image.scaled(width, width / scaled);
	scaledImg = image.mirrored(true,false);  
	ui.label_camera->setPixmap(QPixmap::fromImage(scaledImg));

	QString text = m_pApp->m_pQRThread->m_sDecode;
	if(!text.isEmpty())
	{
		CloseCamera();
		ui.label_camera->setPixmap(IconHelper::Instance()->getPixmap("#181d4b", 0xf030, iconSize, 60, 60));
		ShowDecode(text);
	}
}

void CLoginQRCode::OpenCamera()
{
	m_cap.open(0);
	if (m_cap.isOpened())
	{
		m_pReadFrameTimer->start(100);
		m_pApp->m_pQRThread->SetQuit(false);
		m_pApp->m_pQRThread->start();
	}
}

void CLoginQRCode::CloseCamera()
{
	m_pReadFrameTimer->stop();
	m_pApp->m_pQRThread->SetQuit(true);
	m_cap.release();
}

void CLoginQRCode::ShowDecode(QString text)
{
	ui.widget_login->setVisible(false);
	ui.widget_info->setVisible(true);

	QStringList list = text.split("，");
	foreach (QString s, list)
	{
		if (s.split("：").at(0) == "ID")
			ui.label_id_text->setText(s.split("：").at(1));
		if (s.split("：").at(0) == "厂商")
			ui.label_factory_text->setText(s.split("：").at(1));
		if (s.split("：").at(0) == "型号")
			ui.label_type_text->setText(s.split("：").at(1));
		if (s.split("：").at(0) == "硬件版本")
			ui.label_addr_text->setText(s.split("：").at(1));
	}
}
