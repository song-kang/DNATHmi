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
	void SlotOffSelectClicked();
	void SlotOffExecClicked();
	void SlotOffCancelClicked();
	void SlotOnSelectClicked();
	void SlotOnExecClicked();
	void SlotOnCancelClicked();
	void SlotResetClicked();
	void SlotOffStrapChanged(bool state);
	void SlotOnStrapChanged(bool state);
	void SlotCmdFeeder();
	void SlotCmdStrapRead();
	void SlotCmdOffStrapOff(qint32 ret);
	void SlotCmdOffStrapOn(qint32 ret);
	void SlotCmdOnStrapOff(qint32 ret);
	void SlotCmdOnStrapOn(qint32 ret);
	void SlotCmdSignalReset(qint32 ret);
	void SlotCmdOffCtrlSelect(qint32 ret);
	void SlotCmdOffCtrlExec(qint32 ret);
	void SlotCmdOffCtrlCancel(qint32 ret);
	void SlotCmdOnCtrlSelect(qint32 ret);
	void SlotCmdOnCtrlExec(qint32 ret);
	void SlotCmdOnCtrlCancel(qint32 ret);

private:
	DNATHmi *m_pApp;

};

#endif // CDEVOPER_H
