#include "dnathmi.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>

#ifdef _DEBUG
#include "vld.h"
#endif

#define PADSCREEN_WIDTH		1280
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setFont(QFont("Microsoft Yahei", 10));

#if _MSC_VER
	QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	QTranslator translator;
	translator.load(":/translator/zh");
	a.installTranslator(&translator);

	DNATHmi w;
	QRect rect = QApplication::desktop()->availableGeometry();
	if (rect.width() > PADSCREEN_WIDTH)
	{
		w.showFullScreen();
	}
	else
	{
		w.setFixedSize(rect.width(),rect.height());
		w.move(0,0);
		w.show();
	}

	return a.exec();
}
