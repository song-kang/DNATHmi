#ifndef QRTHREAD_H
#define QRTHREAD_H

#include <QThread>
#include "zbar.h"
#include "videoio.hpp"
#include "opencv.hpp"
using namespace std;

class DNATHmi;
class QRThread : public QThread
{
	Q_OBJECT

public:
	QRThread(QObject *parent);
	~QRThread();

	void SetQuit(bool b) { m_bQuit = b; }
	bool isQuit() { return m_isQuit; }

public:
	cv::Mat m_frame;
	QString m_sDecode;

protected:
	virtual void run();

private:
	DNATHmi *m_pApp;
	bool m_bQuit;
	bool m_isQuit;

private:
	QString Utf8ToGb2312(std::string &strUtf8);
	string GetQR(cv::Mat img);
	string GetQRInBinImg(cv::Mat binImg);
	string ZbarDecoder(cv::Mat img);
	
};

#endif // QRTHREAD_H
