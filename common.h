#ifndef COMMON_H
#define COMMON_H

#include <QAbstractButton>
#include <QApplication>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QCursor>
#include <QDate>
#include <QDateTime>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFont>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QSound>
#include <QStyleFactory>
#include <QStyleOption>
#include <QTextCodec>
#include <QTime>
#include <QTimer>
#include <QtGui>
#include <QUrl>
#include <QWidget>
#include <qmath.h>

#ifdef WIN32
#include "windows.h"
#endif

#define	VERSION		"1.0.0"

enum eDevCommnd
{
	CMD_EMPTY = -1,
	CMD_DEVLIST,
	CMD_DEVCHECK,
	CMD_FEEDER,
	CMD_SET_ALLDATA,
	CMD_REF_ALLDATA,
	CMD_STRAP_READ,
	CMD_OFFSTRAP_OFF,
	CMD_OFFSTRAP_ON,
	CMD_ONSTRAP_OFF,
	CMD_ONSTRAP_ON,
	CMD_OFFCTRL_SELECT,
	CMD_OFFCTRL_EXEC,
	CMD_OFFCTRL_CANCEL,
	CMD_ONCTRL_SELECT,
	CMD_ONCTRL_EXEC,
	CMD_ONCTRL_CANCEL,
	CMD_SIGNALRESET
};

enum eDevOper
{
	OPER_OPEN = 0, //·Ö
	OPER_CLOSE, //ºÏ
};

enum eDevRet
{
	RET_SUCCESS = 0,
	RET_FAILED,
	RET_TIMEOUT
};

class Common
{
	Common();
	~Common();

public:
	static void UsSleep(long mms)
	{
#ifdef WIN32
		int ms = mms/1000;
		if(ms <= 0)
			ms = 1;
		Sleep(ms);
#else
		usleep(mms);
#endif
	};

	static QString Common::GetCurrentAppPath()
	{
		return QCoreApplication::applicationDirPath()+"/";
	}

	static QString Common::GetCurrentAppName()
	{
		return QCoreApplication::applicationName();
	}

	static bool Common::FolderExists(QString strFolder)
	{
		QDir tempFolder(strFolder);
		if(tempFolder.exists())
			return true;
		return false;
	}

	static bool Common::CreateFolder(QString strFolder)
	{
		QDir dir;
		return dir.mkdir(strFolder);
	}

	static bool Common::FileExists(QString strFile)
	{
		QFileInfo fi(strFile);
		if (fi.exists())
			return true;
		return false;
	}

	static void ClearLayout(QLayout *layout)
	{
		QLayoutItem *item = NULL;
		while((item = layout->takeAt(0)) != 0)
		{
			if(item->widget())
				delete item->widget();

			QLayout *childLayout = item->layout();
			if(childLayout)
				ClearLayout(childLayout);

			delete item;
		}
	}
};

#endif // COMMON_H