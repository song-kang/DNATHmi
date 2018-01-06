#ifndef CLOGINQRCODE_H
#define CLOGINQRCODE_H

#include <QWidget>
#include <QThread>
#include <QTextCodec>
#include "ui_cloginqrcode.h"
#include "zbar.h"
#include "videoio.hpp"
#include "opencv.hpp"
using namespace std;
//using namespace cv;
//using namespace zbar;

#define LoginQRCode		"CLoginQRCode"

///////////////////  TQRDecode  /////////////////////////
class TQRDecode : public QThread
{
	Q_OBJECT

public:
	TQRDecode(QObject *parent);
	~TQRDecode();

	cv::Mat m_frame;
	QString m_sDecode;

protected:
	virtual void run();

};

///////////////////  CLoginQRCode  /////////////////////////
class CLoginQRCode : public QWidget
{
	Q_OBJECT

public:
	CLoginQRCode(QWidget *parent = 0);
	~CLoginQRCode();

	void CloseCamera();

private:
	Ui::CLoginQRCode ui;

	cv::VideoCapture m_cap;
	QTimer *m_pReadFrameTimer;
	TQRDecode *m_pQRDecodThread;

private:
	void Init();
	void InitUi();
	void InitSlot();
	void OpenCamera();
	void ShowDecode(QString text);

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotOkClicked();
	void SlotCancelClicked();
	void SlotReadFrame();

};

#endif // CLOGINQRCODE_H
