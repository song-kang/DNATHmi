#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>
#include "common.h"
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
	void SetDevice(QString no) { m_sDevice = no; }
	void SetFeeder(qint32 i) { m_iFeeder = i; }

public:
	QMutex m_mutex;
	QList<QString> m_listFeeder;
	QList<stuMeausre*> m_listMeausreCol1;
	QList<stuMeausre*> m_listMeausreCol2;
	QList<stuMeausre*> m_listMeausreCol3;
	QList<stuMeausre*> m_listPowerCol1;
	QList<stuMeausre*> m_listPowerCol2;
	QList<stuDigital*> m_listDigital;
	QList<stuSoe*> m_listSoe;

private:
	DNATHmi *m_pApp;
	bool m_bQuit;
	eDevCommnd m_eCommand;
	QString m_sDevice;
	qint32 m_iFeeder;

private:
	void CmdFeeder();
	void CmdSetAllData();
	void CmdRefAllData();
	eDevRet CmdRemoteControl();
	eDevRet CmdSoftStrap();
	eDevRet CmdHardStrap();
	eDevRet CmdDistantLocal();
	eDevRet CmdSignalReset();

protected:
	virtual void run();

signals:
	void SigCmdFeeder();
	void SigCmdSetAllData();
	void SigCmdRefAllData();
	void SigCmdRmoteControl(qint32 ret);
	void SigCmdSoftStrap(qint32 ret);
	void SigCmdHardStrap(qint32 ret);
	void SigCmdDistantLocal(qint32 ret);
	void SigCmdSignalReset(qint32 ret);

private:
	float measure_test;
	bool digital_test;
	
};

#endif // COMMTHREAD_H
