#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>
#include "ui_msgbox.h"

#define RET_YES		0
#define RET_NO		1
#define RET_CANCEL	2

class MsgBox : public QDialog
{
	Q_OBJECT

public:
	static MsgBox *Instance();
	static void DestoryInstance();
	explicit MsgBox(QWidget *parent = 0);
	~MsgBox();

	int GetRet() { return m_iRet; }
	void information(QString text);
	void warning(QString text);
	void critical(QString text);
	int  question(QString text,quint32 itemCount = 2,
		QString item1 = tr("  Yes"),QString item2 = tr("  No"),QString item3 = tr("  Cancel"),
		QChar icon1 = 0xf00c,QChar icon2 = 0xf00d,QChar icon3 = 0xf00d);

private:
	Ui::MsgBox ui;

	static MsgBox *self;
	int m_iRet;

private:
	void Init();
	void InitUi();
	void InitSlot();

private slots:
	void SlotYes();
	void SlotNo();
	void SlotCancel();

};

#endif // MSGBOX_H
