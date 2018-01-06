#ifndef CLOGINCODE_H
#define CLOGINCODE_H

#include <QWidget>
#include "ui_clogincode.h"

#define LoginCode		"CLoginCode"

class CLoginCode : public QWidget
{
	Q_OBJECT

public:
	CLoginCode(QWidget *parent = 0);
	~CLoginCode();


private:
	Ui::CLoginCode ui;

private:
	void Init();
	void InitUi();
	void InitSlot();
	bool Start(); //可在此完成数据获取工作

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotLoginClicked();
	void SlotOkClicked();
	void SlotCancelClicked();

};

#endif // CLOGINCODE_H
