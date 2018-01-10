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

#define	VERSION		"1.0.0"

enum eDevCommnd
{
	CMD_EMPTY = -1,
	CMD_FEEDER,
	CMD_SET_ALLDATA,
	CMD_REF_ALLDATA,
	CMD_REMOTE_CONTROL,
	CMD_SOFT_STRAP,
	CMD_HARD_STRAP,
	CMD_DISTANT_LOCAL,
	CMD_SIGNALRESET
};

enum eDevRet
{
	RET_SUCCESS = 0,
	RET_FAILED,
	RET_TIMEOUT
};

#endif // COMMON_H