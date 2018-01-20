#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>
#include "common.h"
#include "cdevlistsee.h"
#include "cdevlistcheck.h"
#include "cdevlook.h"

class DNATHmi;
class CommThread : public QThread
{
	Q_OBJECT

public:
	CommThread(QObject *parent);
	~CommThread();

	void ClearAllData();
	void SetQuit(bool b) { m_bQuit = b; } 
	void SetCommand(eDevCommnd cmd) { m_eCommand = cmd; }
	void SetOper(eDevOper oper) { m_eOper = oper; }
	void SetDevice(QString no) { m_sDevice = no; }
	void SetFeeder(qint32 i) { m_iFeeder = i; }
	bool isQuit() { return m_isQuit; }

public:
	QMutex m_mutex;
	QList<stuDev*> m_listDevice;
	QList<stuDevCheck*> m_listDeviceCheck;
	QList<QString> m_listFeeder;
	QList<stuMeausre*> m_listMeausreCol1;
	QList<stuMeausre*> m_listMeausreCol2;
	QList<stuMeausre*> m_listMeausreCol3;
	QList<stuMeausre*> m_listPowerCol1;
	QList<stuMeausre*> m_listPowerCol2;
	QList<stuDigital*> m_listDigital;
	QList<stuSoe*> m_listSoe;
	bool m_bOffStrap;
	bool m_bOnStrap;
	bool m_bRemoteLocate;
	bool m_bHardStrap;

private:
	DNATHmi *m_pApp;
	bool m_bQuit;
	bool m_isQuit;
	eDevCommnd m_eCommand;
	eDevOper m_eOper;
	QString m_sDevice;
	qint32 m_iFeeder;

private:
	void CmdDevList();
	void CmdDevCheck();
	void CmdFeeder();
	void CmdSetAllData();
	void CmdRefAllData();
	void CmdStrapRead();
	eDevRet CmdOffStarpOff();
	eDevRet CmdOffStarpOn();
	eDevRet CmdOnStarpOff();
	eDevRet CmdOnStarpOn();
	eDevRet CmdOffCtrlSelect();
	eDevRet CmdOffCtrlExec();
	eDevRet CmdOffCtrlCancel();
	eDevRet CmdOnCtrlSelect();
	eDevRet CmdOnCtrlExec();
	eDevRet CmdOnCtrlCancel();
	eDevRet CmdSignalReset();

protected:
	virtual void run();

signals:
	void SigCmdDevList();
	void SigCmdDevCheck();
	void SigCmdFeeder();
	void SigCmdSetAllData();
	void SigCmdRefAllData();
	void SigCmdStrapRead();
	void SigCmdOffStrapOff(qint32 ret);
	void SigCmdOffStrapOn(qint32 ret);
	void SigCmdOnStrapOff(qint32 ret);
	void SigCmdOnStrapOn(qint32 ret);
	void SigCmdSignalReset(qint32 ret);
	void SigCmdOffCtrlSelect(qint32 ret);
	void SigCmdOffCtrlExec(qint32 ret);
	void SigCmdOffCtrlCancel(qint32 ret);
	void SigCmdOnCtrlSelect(qint32 ret);
	void SigCmdOnCtrlExec(qint32 ret);
	void SigCmdOnCtrlCancel(qint32 ret);

private:
	float measure_test;
	bool digital_test;
	
};

#endif // COMMTHREAD_H
