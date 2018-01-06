#include "cloginqrcode.h"
#include "iconhelper.h"
#include "msgbox.h"
#include "cdev.h"
//#include "QZXing.h"

#define charSize		20
#define titleSize		20
#define iconSize		40
#define iconWidth		40
#define iconHeight		40
#define btnHeight		60

string ZbarDecoder(cv::Mat img)
{
	string result;
	zbar::ImageScanner scanner;
	const void *raw = (&img)->data;

	scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1); // configure the reader
	zbar::Image image(img.cols, img.rows, "Y800", raw, img.cols * img.rows); // wrap image data
	int n = scanner.scan(image); // scan the image for barcodes
	result = image.symbol_begin()->get_data(); // extract results
	image.set_data(NULL, 0);

	return result;
}

string GetQRInBinImg(cv::Mat binImg)
{
	//对二值图像进行识别，如果失败则开运算进行二次识别
	string result = ZbarDecoder(binImg);
	if (result.empty())
	{
		cv::Mat openImg;
		cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
		morphologyEx(binImg, openImg, cv::MORPH_OPEN, element);
		result = ZbarDecoder(openImg);
	}

	return result;
}

string GetQR(cv::Mat img)
{
	cv::Mat binImg;
	
	int thre = threshold(img, binImg, 0, 255, cv::THRESH_OTSU); //在otsu二值结果的基础上，不断增加阈值，用于识别模糊图像
	string result;
	while(result.empty() && thre < 255)
	{
		threshold(img, binImg, thre, 255, cv::THRESH_BINARY);
		result = GetQRInBinImg(binImg);
		thre += 20; //阈值步长设为20，步长越大，识别率越低，速度越快
	}

	return result;
}

QString Utf8ToGb2312(std::string &strUtf8)
{
	QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
	QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

	QString strUnicode=utf8Codec->toUnicode(strUtf8.c_str());
	QByteArray ByteGb2312=gb2312Codec->fromUnicode(strUnicode);

	return ByteGb2312.data();
}

///////////////////  TQRDecode  /////////////////////////
TQRDecode::TQRDecode(QObject *parent)
	: QThread(parent)
{
	
}

TQRDecode::~TQRDecode()
{

}

void TQRDecode::run()
{
	m_sDecode = QString::null;
	m_frame.data = NULL; //避免放弃时两次登录
	while(1)
	{
		if(!m_frame.data) 
		{
			QThread::sleep(1); //每1秒检查一下有无图像
			continue;
		}

		IplImage imgTmp = m_frame;
		IplImage *srcImage = cvCloneImage(&imgTmp);
		m_frame.data = 0;
		IplImage *Grayimage = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U, 1); //转变为灰度图
		cvCvtColor(srcImage,Grayimage,CV_BGR2GRAY);
		
		cv::Mat im = cv::cvarrToMat(Grayimage); //解码图片必需为灰度图
		std::string ret = GetQR(im);
		m_sDecode = Utf8ToGb2312(ret);
		if(!m_sDecode.isEmpty())
		{
			cvReleaseImage(&srcImage);  
			cvReleaseImage(&Grayimage);
			break;
		}

		cvReleaseImage(&srcImage);  
		cvReleaseImage(&Grayimage);

		QThread::msleep(500); //避免CPU过高
	}
}

///////////////////  CLoginQRCode  /////////////////////////
CLoginQRCode::CLoginQRCode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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
	m_pQRDecodThread = new TQRDecode(this);
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
	if(!m_pQRDecodThread->m_frame.data)
		m_cap >> m_pQRDecodThread->m_frame; //输出到线程识别用

	QImage image = QImage((const uchar*)frame.datastart, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
	float scaled = (float)(frame.cols*1.0f / frame.rows);
	int width = 50;
	QImage scaledImg = image.scaled(width, width / scaled);
	scaledImg = image.mirrored(true,false);  
	ui.label_camera->setPixmap(QPixmap::fromImage(scaledImg));

	//QZXing decoder(QZXing::DecoderFormat_None);
	//QString qrmsg = decoder.decodeImage(scaledImg);

	QString text = m_pQRDecodThread->m_sDecode;
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
		m_pQRDecodThread->start();
	}
}

void CLoginQRCode::CloseCamera()
{
	m_pReadFrameTimer->stop();
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
