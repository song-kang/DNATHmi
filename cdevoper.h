#ifndef CDEVOPER_H
#define CDEVOPER_H

#include <QWidget>
#include <QThread>
#include "navbutton.h"
#include "ui_cdevoper.h"

#define DeviceOper	"CDevOper"

class DNATHmi;
class CDevOper : public QWidget
{
	Q_OBJECT

public:
	CDevOper(QWidget *parent = 0);
	~CDevOper();

	void Start();

private:
	Ui::CDevOper ui;

	QList<NavButton*> m_listBtnFeed;
	QList<QToolButton *> m_pToolBtns;
	QTimer *m_pTimer;
	quint32 m_iTimeOut;

private:
	void Init();
	void InitUi();
	void InitSlot();

	void SetFeeder();
	void ShowFeeder();

	void HmiEnable(bool enable);
	void ShowBox(qint32 ret,QString text);

signals:
	void SigWidgetName(QString name);

private slots:
	void SlotTimeout();
	void SlotNavButtonClick();

	void SlotRemoteControlClicked();
	void SlotSoftStrapClicked();
	void SlotHardStrapClicked();
	void SlotDistantLocalClicked();
	void SlotSignalResetClicked();

	void SlotCmdFeeder();
	void SlotCmdRmoteControl(qint32 ret);
	void SlotCmdSoftStrap(qint32 ret);
	void SlotCmdHardStrap(qint32 ret);
	void SlotCmdDistantLocal(qint32 ret);
	void SlotCmdSignalReset(qint32 ret);

private:
	DNATHmi *m_pApp;

};

#endif // CDEVOPER_H
