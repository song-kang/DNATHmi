#include "dnathmi.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>

#ifdef _DEBUG
#include "vld.h"
#endif

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
	w.showFullScreen();

	return a.exec();
}
