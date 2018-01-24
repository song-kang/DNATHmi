#include "maskwidget.h"
#include "qapplication.h"

MaskWidget *MaskWidget::self = 0;
MaskWidget::MaskWidget(QWidget *parent) : QWidget(parent)
{
    mainWidget = 0;
    setOpacity(0.7);
    setBgColor(QColor(0, 0, 0));

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    qApp->installEventFilter(this);
}

void MaskWidget::DestoryInstance()
{
	if (self != NULL) 
	{
		delete self;
		self = NULL;
	}
}

void MaskWidget::setMainWidget(QWidget *mainWidget)
{
    if (this->mainWidget != mainWidget){
        this->mainWidget = mainWidget;
    }
}

void MaskWidget::setDialogNames(const QStringList &dialogNames)
{
    if (this->dialogNames != dialogNames){
        this->dialogNames = dialogNames;
    }
}

void MaskWidget::appendDialogName(const QString dialogName)
{
	bool bFind = false;
	foreach (QString name, dialogNames)
	{
		if (name == dialogName)
		{
			bFind = true;
			break;
		}
	}

	if (!bFind)
		dialogNames.append(dialogName);
}

void MaskWidget::setOpacity(double opacity)
{
    this->setWindowOpacity(opacity);
}

void MaskWidget::setBgColor(const QColor &bgColor)
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, bgColor);
    this->setPalette(palette);
}

void MaskWidget::showEvent(QShowEvent *)
{
    if (mainWidget != 0) {
        this->setGeometry(mainWidget->geometry());
    }
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Hide) {
		if (dialogNames.contains(obj->objectName())) {
			this->hide();
		}
	}

    return QObject::eventFilter(obj, event);
}
