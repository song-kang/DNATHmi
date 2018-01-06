#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>
#include "ui_msgbox.h"

#define RET_YES		0
#define RET_NO		1

class MsgBox : public QDialog
{
	Q_OBJECT

public:
	static MsgBox *Instance();
	static void DestoryInstance();
	explicit MsgBox(QWidget *parent = 0);
	~MsgBox();

	void information(QString text);
	void warning(QString text);
	void critical(QString text);
	int  question(QString text);

private:
	Ui::MsgBox ui;

	static MsgBox *self;

private:
	void Init();
	void InitUi();
	void InitSlot();

private slots:
	void SlotYes();
	void SlotNo();

};

#endif // MSGBOX_H
