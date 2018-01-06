#ifndef CLOGIN_H
#define CLOGIN_H

#include <QWidget>
#include "ui_clogin.h"

#define Login			"CLogin"
#define LoginQRCode		"CLoginQRCode"

class CLogin : public QWidget
{
	Q_OBJECT

public:
	CLogin(QWidget *parent = 0);
	~CLogin();

private:
	Ui::CLogin ui;

	QList<QToolButton *> m_pToolBtns;

private:
	void Init();
	void InitUi();
	void InitSlot();

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotQRCodeLoginClicked();
	void SlotCodeLoginClicked();

};

#endif // CLOGIN_H
