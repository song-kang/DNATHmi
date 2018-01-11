#ifndef CLOGINQRCODE_H
#define CLOGINQRCODE_H

#include <QWidget>
#include "ui_cloginqrcode.h"
#include "opencv.hpp"

#define LoginQRCode		"CLoginQRCode"

class DNATHmi;
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

private:
	DNATHmi *m_pApp;

};

#endif // CLOGINQRCODE_H
