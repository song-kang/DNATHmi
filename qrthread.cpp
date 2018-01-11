#include "qrthread.h"
#include "dnathmi.h"

QRThread::QRThread(QObject *parent)
	: QThread(parent)
{
	m_pApp = (DNATHmi *)parent;
	m_bQuit = false;
}

QRThread::~QRThread()
{

}

void QRThread::run()
{
	m_sDecode = QString::null;
	m_frame.data = NULL; //避免放弃时两次登录
	while(!m_bQuit)
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

QString QRThread::Utf8ToGb2312(std::string &strUtf8)
{
	QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
	QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

	QString strUnicode=utf8Codec->toUnicode(strUtf8.c_str());
	QByteArray ByteGb2312=gb2312Codec->fromUnicode(strUnicode);

	return ByteGb2312.data();
}

string QRThread::GetQR(cv::Mat img)
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

string QRThread::GetQRInBinImg(cv::Mat binImg)
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

string QRThread::ZbarDecoder(cv::Mat img)
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
